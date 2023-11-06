
#include <cmath>

#include "WildFire.h"

//=====================================================================================================================
static float QA = 57.29578;

//---------------------------------------------------------------------------------------------------------------------
//蔓延速度计算（王正非林火蔓延模型）
float WildFire::FireSpeedCal()
{
    //蔓延速度系数计算
    float k_speed = 0;
    switch (vegetationType){
        case Coniferous:{
            k_speed = 0.4; break; }
        case Secondary:{
            k_speed = 0.7; break; }
        case Needle:{
            k_speed = 0.8; break; }
        case Pine:{
            k_speed = 1.0; break; }
        case Leaves:{
            k_speed = 1.2; break; }
        case Grass:{
            k_speed = 1.6; break; }
        case Shrub:{
            k_speed = 1.8; break; }
        case Pasture:{
            k_speed = 2.0; break; }
        default:{
            k_speed = 1.0; break; }
    }
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