#pragma once

#include "../MathBase/_MathBase.h"
#include "../MathBase/Coordinate.h"
#include "../BehaviorTree/Sequence.h"

//=====================================================================================================================

///抵近飞行次序节点
class Engage : public Sequence
{
private:
    //当前坐标
    Position currentPos;
    //出发点坐标
    Position startPos;
    //目标位置坐标
    Position targetPos;
    //搜救半径
    double rescueRadius;
    //飞行速度
    double flightSpeed;
    //飞行器坐标
    Position* aircraft;

    //准入判断
    bool entranceCheck();

public:
    Engage(){};
    Engage(Position startPos, Position targetPos, double rescueRadius, double flightSpeed);
    ~Engage(){};

    //执行节点
    NodeStatus executeNode();
    //设置飞行器
    inline void setAircraft(Position* aircraft){ this->aircraft = aircraft; };
};

