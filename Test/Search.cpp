
#include "Search.h"

//---------------------------------------------------------------------------------------------------------------------
using namespace std;

//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
Search::Search(double rescueRadius, double rescueSpeed, double discoverProb, Position rescueCenter, double searchSpeed, double scanRange){
	this->rescueRadius = rescueRadius;
	this->rescueSpeed = rescueSpeed;
	this->discoverProb = discoverProb;
	this->rescueCenter = rescueCenter;
	this->searchSpeed = searchSpeed;
	this->scanRange = scanRange;
}
//---------------------------------------------------------------------------------------------------------------------

//执行节点
NodeStatus Search::executeNode(){
	//更新位置坐标
	currentPos = *aircraft;
    //计算搜救点位序列
    //if(searchPoints.size() <= 0)    searchPoints = PointsCal();
    //当前搜救点位计算
    //currentPos = curSearchPositionCal();
	//更新飞行器坐标
	*aircraft = currentPos;
    //发现概率计算
	float randomNum = randomGenerate();
    if(randomNum < discoverProb)	status = Success;
	else    status = Running;
    return status;
}

//---------------------------------------------------------------------------------------------------------------------
//准入判断
bool Search::entranceCheck(){
    //若父节点状态为成功，则返回True
    if (parent->getStatus() == Success)    return true;
	return false;
}

//---------------------------------------------------------------------------------------------------------------------
//搜救节点计算
vector<Position> Search::PointsCal(){
    double theta, delta;
	vector<Position> result;
	vector<double> xofPoints, yofPoints;
	vector<double> xofReverse, yofReverse;

	int leaderRec = 2 * rescueRadius / scanRange;
	int halfLeader = leaderRec / 2;

	xofPoints.resize(2 * halfLeader);
	yofPoints.resize(2 * halfLeader);

	for (int i = 1; i <= halfLeader; i++) {
		theta = acos(1. - 2. * i / leaderRec);
		delta = sqrt(1. - pow((1. - 2. * i / leaderRec), 2)) + 
				sqrt(1. - pow((1. - 2. * (i + 1) / leaderRec), 2));
		delta *= rescueRadius;
		xofPoints[2 * i - 1 - 1] = pow(-1, i) * rescueRadius * sin(theta);
		yofPoints[2 * i - 1 - 1] = (1. - 2. * i / leaderRec) * rescueRadius;
		xofPoints[2 * i - 1] = xofPoints[2 * i - 1 - 1] - pow(-1, i) * delta;
		yofPoints[2 * i - 1] = yofPoints[2 * i - 1 - 1];
	}

	if (!(leaderRec % 2)) {
		xofPoints.pop_back();
		yofPoints.pop_back();
		xofPoints.push_back(pow(-1, halfLeader) * rescueRadius * sin(theta));
		yofPoints.push_back((1. - 2. * halfLeader / leaderRec) * rescueRadius);
		xofReverse = -1 * xofPoints; reverse(xofReverse.begin(), xofReverse.end());
		yofReverse = -1 * yofPoints; reverse(yofReverse.begin(), yofReverse.end());
	}
	else {
		xofReverse = xofPoints;	reverse(xofReverse.begin(), xofReverse.end());
		yofReverse = -1 * yofPoints; reverse(yofReverse.begin(), yofReverse.end());
	}
	xofPoints.insert(xofPoints.end(), xofReverse.begin(), xofReverse.end());
	yofPoints.insert(yofPoints.end(), yofReverse.begin(), yofReverse.end());

	for (int i = 0; i < xofPoints.size(); i++) {
		static Position pointTemp;
		pointTemp.xPos = xofPoints[i];
		pointTemp.yPos = yofPoints[i];
		result.push_back(pointTemp);
	}

	//旋转-平移坐标
	Position initArrow = currentPos - rescueCenter;
	Position oriArrow = result[0];
	float deltaAngle = -acos(initArrow * oriArrow / (initArrow.norm() * oriArrow.norm()));
	float fTemp[2] = { sin(deltaAngle), cos(deltaAngle)};
	for (auto& member : result){
		static float rec[2];
		rec[0] = member.xPos; rec[1] = member.yPos;
		member.xPos = rec[0] * fTemp[1] - rec[1] * fTemp[0];
		member.yPos = rec[0] * fTemp[0] + rec[1] * fTemp[1];
		member = member + rescueCenter;
	}
	result.insert(result.begin(), currentPos);

	//重复点去除
	for (int i = 0; i < result.size() - 1; i++)
		if ((result[i] - result[i + 1]).norm() < EPS)
			result.erase(result.begin() + i);

	return result;

}

//当前位置计算
Position Search::curSearchPositionCal(){
    Position velocity;
    //完成一轮搜索：反转搜救序列
	if (trackIndex >= searchPoints.size() - 1) {
		trackIndex = 0;
		reverse(searchPoints.begin(), searchPoints.end());
	}
	//搜救点预计算
	Position trackJudge[2];
	trackJudge[0] = searchPoints[trackIndex + 1] - searchPoints[trackIndex];
	velocity = trackJudge[0] / trackJudge[0].norm() * searchSpeed;
	//更新航迹段预测
	Position searchPointPredict = currentPos + velocity * g_fTimeStep;
	trackJudge[1] = searchPointPredict - searchPoints[trackIndex];
	//已超出当前航迹段
	if (trackJudge[1].norm() >= trackJudge[0].norm()) {
		//所属航迹段更新
		trackIndex++;
		//时间步进计算
		float timeCost = (searchPoints[trackIndex] - currentPos).norm() / searchSpeed;
		float localTimeRemain = g_fTimeStep - timeCost;
		//位置更新至下一节点
		currentPos = searchPoints[trackIndex];
		//递归计算
		return curSearchPositionCal();
	}
	//在当前航迹段内
	else
		//位置更新至预计位置
		return searchPointPredict;


}
