
#include "Engage.h"

//=====================================================================================================================
//-----------------------------------------------------------------------------------------------------
Engage::Engage(Position startPos, Position targetPos, double rescueRadius, double flightSpeed){
    this->startPos = startPos;
    this->targetPos = targetPos;
    this->rescueRadius = rescueRadius;
    this->flightSpeed = flightSpeed;
}

//-----------------------------------------------------------------------------------------------------
//执行节点
NodeStatus Engage::executeNode(){
    //更新位置坐标
    currentPos = *aircraft;
    //计算起飞点、目标点方向
    Position direction = (targetPos - startPos) / (targetPos - startPos).norm();
    //计算当次飞行距离
    double flightDistance = flightSpeed * g_fTimeStep;
    //更新当前坐标
    currentPos = currentPos + direction * flightDistance;
    //判断距目标点距离
    double targetDistance = (targetPos - currentPos).norm();
    //更新飞行器坐标
    *aircraft = currentPos;
    //若距离在搜救距离内，返回成功
    if (targetDistance < rescueRadius){
        status = Success; return Success;
    }
    status = Running; 
    return Running;
}

//准入判断
bool Engage::entranceCheck(){
    //若父节点状态为成功，则返回True
    if (parent->getStatus() == Success)    return true;
    return false;
}