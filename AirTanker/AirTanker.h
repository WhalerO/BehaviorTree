#pragma once

#include "../WildFire/WildFire.h"

//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//灭火机类
class AirTanker
{
private:
    //初次出动准备时间
    float readyTime = 25;
    //补给时间
    float supplyTime = 10;
    //载荷装载时间
    float reLoadTime = 5;
    //航程
    float range = 500;
    //航时
    float endurance = 5;
    //燃油容量
    float fuelCapacity = 2400;
    //当前燃油重量
    float fuelWeight = 2400;
    //燃油消耗率
    float fuelCost = 8;
    //载荷重量
    float loadWeight = 3000;
    //空投精度
    float accuracy = 85;
    //有效投放率
    float effectiveRate = 85;
    //巡航速度
    float cruiseSpeed = 240;
    //吊桶飞行速度
    float bucketSpeed = 80;
    //任务总油耗
    float totalFuelCost = 0;
    //飞行器位置
    Position position;
    //取水点
    Position waterPoint;

    //火场指针
    WildFire* wildFire = nullptr;

    //往返架次纪录
    int flightRec = 0;
    //加油次数纪录
    int reFuelRec = 0;
    //时间记录：加油时间
    float reFuelTimeRec = 0;
    //时间记录：整备时间
    float readyTimeRec = 0;
    //时间记录：取水时间
    float loadTimeRec = 0;

    //状态：已完成初次出动
    bool isEngaged = false;
    //状态：吊桶中有水
    bool isWaterLoaded = false;
    //状态：油箱中有余油
    bool isFuelRemain = true;

    //重新加油判断
    bool ReFuelJudge();
    //初次飞抵火场
    bool Engage();
    //重新取水
    void WaterLoad();
    //投水
    void DropWater();

public:
    //仿真计算步长(min)
    static float timeStep;

    //设置飞机位置
    inline void SetPosition(Position pos){position = pos;};
    //设置取水点
    inline void SetWaterPoint(Position pos){waterPoint = pos;};
    //设置火场指针
    inline void SetWildFire(WildFire* fire){wildFire = fire;};
    //输出架次纪录
    inline int GetFlightRec(){return flightRec;};
    //输出加油次数
    inline int GetReFuelRec(){return reFuelRec;};
    //设置仿真步长
    inline static void SetTimeStep(float step){timeStep = step;};

    //执行仿真计算
    void Update();
    //输出当前飞机状态
    std::string StatusDisp();

};