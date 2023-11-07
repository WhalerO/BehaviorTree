#pragma once

#include <vector>
#include <string>

#include "../MathBase/_MathBase.h"
#include "../MathBase/Coordinate.h"

//=====================================================================================================================
//可燃物类型：苔原、针叶林、次生林、松针、油松、落叶、杂草、灌木、牧草、残火
enum VegetationType{
    Tundra, Coniferous, Secondary, Needle, Pine, Leaves, Grass, Shrub, Pasture, FireRemains
};

//---------------------------------------------------------------------------------------------------------------------
class WildFire
{
private:
    //火场总面积
    float totalArea = 0;
    //火场平均温度
    float fireTemperature = 500;
    //燃烧温度
    float burningTemperature = 500;
    //阴燃温度
    float smolderingTemperature = 200;
    //火场半径
    float fireRadius = 0;
    //火场环宽度
    float fireWidth = 50;
    //火场中心位置
    Position fireCenter;
    //火场蔓延速度
    float fireSpeed = 0;
    //过火面积
    float burnedArea = 0;
    //燃烧面积
    float burningArea = 0;
    //飞火概率
    float flyingFireProb = 0;

    //当前仿真轮投水总重
    float curTurnTotalWater = 0;
    //扑灭火环百分比
    float fireSurpressPercent = 0;

    //可燃物湿度,%
    float humidity = 10;
    //当地风速
    float windSpeed = 0;
    //当地坡度
    float slope = 0;
    //蔓延速度系数
    float speedCoefficient = 0;
    //GPC标准（加仑每百平方英尺）
    float GPC = 4;
    //火场可燃物类型
    VegetationType vegetationType = Pine;

    //蔓延速度系数计算
    float SpeedCoefficientCal();
    //GPC标准确认
    float GPCConfirm();
    //蔓延速度计算
    float FireSpeedCal();
    //火场面积计算
    float FireAreaCal();
    //火场平均温度计算
    float FireTemperatureCal();
    //飞火概率计算
    float FlyingFireProbCal();

    //友元
    friend class AirTanker;

public:
    WildFire();
    ~WildFire();

    //仿真计算步长(min)
    static float timeStep;

    //设置火场位置
    inline void SetFireCenter(Position center){fireCenter = center;};
    //设置仿真步长
    inline static void SetTimeStep(float step){timeStep = step;};
    //获得火场面积
    inline float GetFireArea(){return totalArea;};
    //获得火场面积
    inline float GetFireRadius(){return fireRadius;};
    //输出火场平均温度
    inline float GetFireTemperature(){return fireTemperature;};
    //获得扑灭火环百分比
    inline float GetFireSurpressPercent(){return fireSurpressPercent;};

    //执行仿真更新
    void Update();


};