#pragma once

#include "../MathBase/_MathBase.h"
#include "../MathBase/Coordinate.h"
#include "../BehaviorTree/Sequence.h"

//=====================================================================================================================

///返航飞行节点
class Return : public Sequence
{
private:
    //当前坐标
    Position currentPos;
    //返航点坐标
    Position returnPos;
    //飞行速度
    double flightSpeed;
    //飞行器坐标
    Position* aircraft;

    //准入判断
    bool entranceCheck();

public:
    Return(){};
    Return(Position returnPos, double flightSpeed);
    ~Return(){};

    //执行节点
    NodeStatus executeNode();
    //设置飞行器
    inline void setAircraft(Position* aircraft){ this->aircraft = aircraft; };
};