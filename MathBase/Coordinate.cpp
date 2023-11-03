#include "Coordinate.h"
#include "_MathBase.h"

//==============================================================================
//经纬度-笛卡尔坐标转换（角度制）
void geo2cart(double ref[2][3], double geo[3], double cart[3])
{
    static double REarth = 6371;
    static double QAngle = 57.29578;
    //北向笛卡尔坐标（纬度）
    cart[1] = ref[0][1] + REarth * (geo[1] - ref[1][1]) / QAngle;
    //东向笛卡尔坐标（经度）
    cart[0] = ref[0][0] + REarth * cos(geo[1] / QAngle) * (geo[0] - ref[1][0]) / QAngle;
    //高度坐标
    cart[2] = geo[2] - ref[1][2];
}
//经纬度-笛卡尔坐标转换（角度制，以0,0,0为原点）
void geo2cart(double geo[3], double cart[3])
{
    double ref[2][3] = { 0.0 };
    geo2cart(ref, geo, cart);
}

//笛卡尔坐标-经纬度转换（角度制）
void cart2geo(double ref[2][3], double cart[2], double geo[3])
{
    static double REarth = 6371;
    static double QAngle = 57.29578;
    //纬度坐标（北向笛卡尔坐标）
    geo[1] = (cart[1] - ref[0][1]) / REarth * QAngle + ref[1][1];
    //经度坐标（东向笛卡尔坐标）
    geo[0] = (cart[0] - ref[0][0]) * QAngle / (REarth * cos(geo[1] / QAngle)) + ref[1][0];
    //高度坐标
    geo[2] = cart[2] - ref[0][2];
}
//笛卡尔坐标-经纬度转换（角度制，以0,0,0为原点）
void cart2geo(double cart[3], double geo[3])
{
    double ref[2][3] = { 0.0 };
    cart2geo(ref, cart, geo);
}

//经纬度-笛卡尔坐标转换（角度制）
void geo2cart(Position& geo, Position& cart)
{
    double dGeo[3] = { geo.xPos, geo.yPos, 0 };
    double dCart[3] = { 0 };
    geo2cart(dGeo, dCart);
    cart.xPos = dCart[0];
	cart.yPos = dCart[1];
}
Position geo2cart(Position& geo)
{
	Position cart;
	geo2cart(geo, cart);
	return cart;
}

//笛卡尔坐标-经纬度转换（角度制）
void cart2geo(Position& cart, Position& geo)
{
    double dGeo[3] = { 0 };
    double dCart[3] = { cart.xPos, cart.yPos, 0 };
	cart2geo(dCart, dGeo);
	geo.xPos = dGeo[0];
	geo.yPos = dGeo[1];
}
Position cart2geo(Position& cart)
{
	Position geo;
	cart2geo(cart, geo);
	return geo;
}

//==============================================================================
//初始化设置
Coordinate::Coordinate() { }
//坐标初始化：G/g--经纬度坐标，C/c--笛卡尔坐标
Coordinate::Coordinate(const char* marker, double p1, double p2, double p3)
{
    const char* cTemp = &marker[0];
    double dTemp[3] = { p1, p2, p3 };
    if (cTemp == "C" || cTemp == "c")   setCartCoordinate(dTemp);
    else setGeoCoordinate(dTemp);
}
//默认为经纬度坐标
Coordinate::Coordinate(double p1, double p2, double p3)
{
    double dTemp[3] = { p1, p2, p3 };
    setGeoCoordinate(dTemp);
}
//设置参考点坐标
void Coordinate::setRefPoint(double refCart[3], double refGeo[3])
{
    for (int i = 0; i < 3; i++) {
        refCartCoordinate[i] = refCart[i];
        refGeoCoordinate[i] = refGeo[i];
    }
    for (int i = 0; i < 3; i++) {
        refPoint[0][i] = refCart[i];
        refPoint[1][i] = refGeo[i];
    }
}
//设置笛卡尔坐标
void Coordinate::setCartCoordinate(double cart[3])
{
    for (int i = 0; i < 3; i++) cartCoordinate[i] = cart[i];
    cart2geo(refPoint, cartCoordinate, geoCoordinate);
}
//设置经纬度坐标
void Coordinate::setGeoCoordinate(double geo[3])
{
    for (int i = 0; i < 3; i++) geoCoordinate[i] = geo[i];
    geo2cart(refPoint, geoCoordinate, cartCoordinate);
}

//------------------------------------------------------------------------------
//球面两点距离计算
double coorDistanceCal(Coordinate& p1, Coordinate& p2)
{
    static double REarth = 6371;
    static double QAngle = 57.29578;
    double p1Geo[2] = { p1.geoCoordinate[0], p1.geoCoordinate[1] };
    double p2Geo[2] = { p2.geoCoordinate[0], p2.geoCoordinate[1] };
    double result = cos(p1Geo[1] / QAngle) * cos(p2Geo[1] / QAngle);
    result *= cos((p2Geo[0] - p1Geo[0]) / QAngle);
    result += sin(p1Geo[1] / QAngle) * sin(p2Geo[1] / QAngle);
    result = REarth * acos(result);
    if (abs(result) > 1) result = result / abs(result);
    return result;
}
//球面两点距离计算
double coorDistanceCal(double* p1, double* p2)
{
    static double REarth = 6371;
    static double QAngle = 57.29578;
    double result = cos(p1[1] / QAngle) * cos(p2[1] / QAngle);
    result *= cos((p2[0] - p1[0]) / QAngle);
    result += sin(p1[1] / QAngle) * sin(p2[1] / QAngle);
    if (abs(result) > 1) result = result / abs(result);
    result = REarth * acos(result);
    return result;
}
//球面两点距离计算
double coorDistanceCal(Position p1, Position p2)
{
    double p1Geo[2] = { p1.xPos, p1.yPos };
	double p2Geo[2] = { p2.xPos, p2.yPos };
	return coorDistanceCal(p1Geo, p2Geo);
}

//------------------------------------------------------------------------------
//某地笛笛卡尔速度-经纬度速度转换（角度制）
void cart2geoVel(double geo[3], double cartVel[3], double geoVel[3])
{
    static double REarth = 6371;
	static double QAngle = 57.29578;
	//纬向速度（北向笛卡尔坐标）
	geoVel[1] = cartVel[1] / REarth * QAngle;
	//经向速度（东向笛卡尔坐标）
	geoVel[0] = cartVel[0] * QAngle / (REarth * cos(geo[1] / QAngle));
	//高度坐标
	geoVel[2] = cartVel[2];
}