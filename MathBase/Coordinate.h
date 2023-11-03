#pragma once

#include "Position.h"

//==============================================================================
class Coordinate
{
public:
    //默认初始化
    Coordinate();
    //坐标初始化：G/g--经纬度坐标，C/c--笛卡尔坐标
    Coordinate(const char* marker, double p1, double p2, double p3 = 0);
    //坐标初始化：默认经纬度坐标
    Coordinate(double p1, double p2, double p3 = 0);

    //调用参考点坐标
    inline double* getRefPointCart()
    { return refCartCoordinate; }
    //调用经纬度坐标
    inline double* getGeoCoordinate()
    { return geoCoordinate; }
    //调用笛卡尔坐标
    inline double* getCartCoordinate()
    { return cartCoordinate; }
    //设置参考点坐标
    void setRefPoint(double refCart[3], double refGeo[3]);
    //设置经纬度坐标
    void setGeoCoordinate(double geo[3]);
    //设置笛卡尔坐标
    void setCartCoordinate(double cart[3]);

private:
    //笛卡尔坐标
    double cartCoordinate[3];
    //经纬度坐标
    double geoCoordinate[3];
    //参考点笛卡尔坐标
    double refCartCoordinate[3] = { 0.0 };
    //参考点经纬度坐标
    double refGeoCoordinate[3] = { 0.0 };
    //参考点坐标集
    double refPoint[2][3] = { 0.0 };

    //友元函数：球面两点距离计算
    friend double coorDistanceCal(Coordinate& p1, Coordinate& p2);

};
//------------------------------------------------------------------------------
//球面两点距离计算
double coorDistanceCal(Coordinate& p1, Coordinate& p2);
//球面两点距离计算
double coorDistanceCal(double* p1, double* p2);
//球面两点距离计算
double coorDistanceCal(Position p1, Position p2);

//==============================================================================
//经纬度-笛卡尔坐标转换（角度制）
void geo2cart(double ref[2][3], double geo[3], double cart[3]);
//笛卡尔坐标-经纬度转换（角度制）
void cart2geo(double ref[2][3], double cart[2], double geo[3]);
//经纬度-笛卡尔坐标转换（角度制-以0,0为原点）
void geo2cart(double geo[3], double cart[3]);
//笛卡尔坐标-经纬度转换（角度制-以0,0为原点）
void cart2geo(double cart[3], double geo[3]);
//经纬度-笛卡尔坐标转换（角度制）
void geo2cart(Position& geo, Position& cart);
Position geo2cart(Position& geo);
//笛卡尔坐标-经纬度转换（角度制）
void cart2geo(Position& cart, Position& geo);
Position cart2geo(Position& cart);


//某地笛笛卡尔速度-经纬度速度转换（角度制）
void cart2geoVel(double geo[3], double cartVel[3], double geoVel[3]);
