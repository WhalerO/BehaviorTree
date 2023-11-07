#pragma once

#include "../WildFire/WildFire.h"

//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//灭火机类
class AirTanker
{
private:
    //初次出动准备时间
    float readyTime = 0;
    //补给时间
    float supplyTime = 0;
    //载荷装载时间
    float reLoadTime = 0;
    //航程
    float range = 0;
    //航时
    float endurance = 0;
    //燃油容量
    float fuelCapacity = 0;
    //当前燃油重量
    float fuelWeight = 0;
    //燃油消耗率
    float fuelCost = 0;
    //载荷重量
    float loadWeight = 0;
    //空投精度
    float accuracy = 0;
    //有效投放率
    float effectiveRate = 0;
    //巡航速度
    float cruiseSpeed = 0;
    //吊桶飞行速度
    float bucketSpeed = 0;
    //任务总油耗
    float totalFuelCost = 0;
    //飞行器位置
    Position position;
    //取水点
    Position waterPoint;

    //火场指针
    WildFire* wildFire = nullptr;

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

    //设置仿真步长
    inline static void SetTimeStep(float step){timeStep = step;};

    //执行仿真计算
    void Update();

};