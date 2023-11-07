
#include <cmath>

#include "WildFire.h"

//=====================================================================================================================
static float QA = 57.29578;
static float RHO_WATER = 1000;

//---------------------------------------------------------------------------------------------------------------------
float WildFire::timeStep = 1.0f;
WildFire::WildFire()
{
    //蔓延速度系数计算
    SpeedCoefficientCal();
    //GPC标准确认
    GPCConfirm();
    //蔓延速度计算
    FireSpeedCal();
}
WildFire::~WildFire(){}


//---------------------------------------------------------------------------------------------------------------------
//蔓延速度计算（王正非林火蔓延模型）
float WildFire::FireSpeedCal()
{
    //蔓延速度系数计算
    float k_speed = speedCoefficient;
    //初始蔓延速度计算
    float initSpeed = 0;
    initSpeed = 1.0372 * exp(-0.057 * humidity);
    //风力修正系数计算
    float k_wind = exp(0.1783 * windSpeed);
    //坡度修正系数计算
    float k_slope = 1 / cos(slope / QA);
    //蔓延速度计算
    fireSpeed = k_speed * initSpeed * k_wind * k_slope;
    return fireSpeed;
}

//---------------------------------------------------------------------------------------------------------------------
//火场面积计算（环形火场蔓延）
float WildFire::FireAreaCal()
{
    //投水总加仑数计算
    float totalWaterGallon = curTurnTotalWater / 3.7854;
    //有效扑灭面积计算
    float effectiveArea = totalWaterGallon / GPC / 10.7639 * 100;
    //本轮扑灭火环百分比计算
    fireSurpressPercent += effectiveArea / (burningArea + EPS);
    //本轮剩余火环百分比计算
    float fireRemainsPercent = 1 - fireSurpressPercent;
    fireRemainsPercent = max(0, fireRemainsPercent);
    //当前火场半径更新
    fireRadius = fireSpeed * timeStep + fireRadius;
    //过火环半径更新
    float burnedRadius = fireRadius - 0.5 * fireWidth;
    burnedRadius = max(0, burnedRadius);
    //过火面积计算
    if(burnedRadius > 0){
        float burnedEdgeForward = timeStep * fireSpeed;
        burnedArea += fireRemainsPercent * PI * (2 * burnedEdgeForward*burnedRadius + burnedEdgeForward * burnedEdgeForward);
    }
    //燃烧面积计算
    burningArea = PI * 4 * fireRadius * fireWidth;
    //火场总面积计算
    totalArea = burningArea + burnedArea;
    return burningArea;
}

//---------------------------------------------------------------------------------------------------------------------
//火场平均温度计算
float WildFire::FireTemperatureCal()
{
    //火场平均温度计算
    fireTemperature = burningTemperature * burningArea / totalArea + smolderingTemperature * (totalArea - burningArea) / totalArea;
    return fireTemperature;
}

//---------------------------------------------------------------------------------------------------------------------
//蔓延速度系数计算
float WildFire::SpeedCoefficientCal()
{
    //蔓延速度系数计算
    switch (vegetationType){
        case Tundra:{
            speedCoefficient = 0.2; break;}
        case Coniferous:{
            speedCoefficient = 0.4; break; }
        case Secondary:{
            speedCoefficient = 0.7; break; }
        case Needle:{
            speedCoefficient = 0.8; break; }
        case Pine:{
            speedCoefficient = 1.0; break; }
        case Leaves:{
            speedCoefficient = 1.2; break; }
        case Grass:{
            speedCoefficient = 1.6; break; }
        case Shrub:{
            speedCoefficient = 1.8; break; }
        case Pasture:{
            speedCoefficient = 2.0; break; }
        default:{
            speedCoefficient = 1.0; break; }
    }
    return speedCoefficient;
}

//---------------------------------------------------------------------------------------------------------------------
//GPC标准确认
float WildFire::GPCConfirm()
{
    //GPC标准确认
    switch (vegetationType){
        case Tundra:{
            GPC = 1; break;}
        case Coniferous:{
            GPC = 2; break; }
        case Secondary:{
            GPC = 3; break; }
        case Needle:{
            GPC = 4; break; }
        case Pine:{
            GPC = 4; break; }
        case Leaves:{
            GPC = 5; break; }
        case Grass:{
            GPC = 5; break; }
        case Shrub:{
            GPC = 6; break; }
        case Pasture:{
            GPC = 6; break; }
        case FireRemains:{
            GPC = 8; break; }
        default:{
            GPC = 4; break; }
    }
    return GPC;
}

//---------------------------------------------------------------------------------------------------------------------
//执行仿真更新
void WildFire::Update()
{
    //蔓延速度计算
    FireSpeedCal();
    //火场面积计算
    FireAreaCal();
    //火场平均温度计算
    FireTemperatureCal();
    //本轮末重初始化
    curTurnTotalWater = 0;
}