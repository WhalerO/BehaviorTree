#pragma once

#include <vector>
#include <string>

#include "../MathBase/_MathBase.h"

//=====================================================================================================================
//可燃物类型：针叶林、次生林、松针、油松、落叶、杂草、灌木、牧草
enum VegetationType{
    Coniferous, Secondary, Needle, Pine, Leaves, Grass, Shrub, Pasture
};

//---------------------------------------------------------------------------------------------------------------------
class WildFire
{
private:
    //火场总面积
    float totalArea = 0;
    //火场平均温度
    float fireTemperature = 500;
    //火场蔓延速度
    float fireSpeed = 0;
    //过火面积
    float burnedArea = 0;
    //燃烧面积
    float burningArea = 0;
    //飞火概率
    float flyingFireProb = 0;
    //可燃物湿度
    float humidity = 0.1;
    //当地风速
    float windSpeed = 0;
    //当地坡度
    float slope = 0;
    //火场可燃物类型
    VegetationType vegetationType = Pine;

    //蔓延速度计算
    float FireSpeedCal();
    //飞火概率计算
    float FlyingFireProbCal();


public:
    //执行仿真更新
    void Update();


};