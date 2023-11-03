
#include "Return.h"

//=====================================================================================================================
//-----------------------------------------------------------------------------------------------------
Return::Return(Position returnPos, double flightSpeed){
    this->returnPos = returnPos;
    this->flightSpeed = flightSpeed;
}

//-----------------------------------------------------------------------------------------------------
//执行节点
NodeStatus Return::executeNode(){
    //更新位置坐标
    currentPos = *aircraft;
    //计算起飞点、目标点方向
    Position direction = (returnPos - currentPos) / (returnPos - currentPos).norm();
    //计算当次飞行距离
    double flightDistance = flightSpeed * g_fTimeStep;
    //更新当前坐标
    currentPos = currentPos + direction * flightDistance;
    //判断距目标点距离
    double targetDistance = (returnPos - currentPos).norm();
    //更新飞行器坐标
    *aircraft = currentPos;
    //若距离小于飞行距离，返回成功
    if (targetDistance < flightDistance){
        status = Success; return Success;
    }
    status = Running; 
    return Running;
}

//---------------------------------------------------------------------------------------------------------------------
//准入判断
bool Return::entranceCheck(){
    //若父节点状态为成功，则返回True
    if (parent->getStatus() == Success)    return true;
    return false;
}