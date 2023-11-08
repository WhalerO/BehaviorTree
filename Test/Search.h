#pragma once

#include "../MathBase/_MathBase.h"
#include "../MathBase/Coordinate.h"
#include "../BehaviorTree/Sequence.h"

//=====================================================================================================================

///搜寻探测节点
class Search : public Sequence
{
private:
    //当前坐标
    Position currentPos;
    //搜救半径
    double rescueRadius;
    //搜救速度
    double rescueSpeed;
    //发现概率
    double discoverProb;
    //搜救中心点坐标
    Position rescueCenter;
    //搜救速度
    double searchSpeed;
    //搜救间隔
    double scanRange;
    //搜救节点集合
    vector<Position> searchPoints;
    //当前航迹段标记
    int trackIndex = 0;
    //飞行器坐标
    Position* aircraft;

    //搜救节点计算
    vector<Position> PointsCal();
    //当前位置计算
    Position curSearchPositionCal();
    //准入判断
    bool entranceCheck();

public:
    Search(){};
    Search(double rescueRadius, double rescueSpeed, double discoverProb, Position rescueCenter, double searchSpeed, double scanRange);
    ~Search(){};

    //执行节点
    NodeStatus executeNode();
    //设置飞行器
    inline void setAircraft(Position* aircraft){ this->aircraft = aircraft; };
};
