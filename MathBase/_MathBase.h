#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using std::vector;

const double PI = 3.141592653;
const double EPS = 1e-6;

//==============================================================================
//最大、最小值比较
inline double min(double p1, double p2)
{ return p1 < p2 ? p1 : p2; }
inline double max(double p1, double p2)
{ return p1 > p2 ? p1 : p2; }

//==============================================================================
//vector矩阵/向量运算重载
vector<double> operator* (double p1, vector<double>& p2);

//==============================================================================
//浮点数相等判断运算符重载
template<typename T>
inline bool operator== (T p1, T p2)
{ return abs(p1 - p2) < EPS ? true : false; }

//==============================================================================
//随机数生成
double randomGenerate(float min = 0, float max = 1);

//==============================================================================
//标准正态分布概率计算
inline double normalDistribution(double p1)
{ return (0.5 + 0.5 * erf(p1 / 1.41421356)); }

//==============================================================================
//vector删除元素
template<typename T>
inline void vectorErase(std::vector<T>& oriVec, T toErase) {
    auto it = std::find(oriVec.begin(), oriVec.end(), toErase);
    oriVec.erase(it);
}

//==============================================================================
//线性插值
template<typename T>
inline T linearInterpolation(T* var, T* ref, T input)
{ return ((var[1] - var[0]) * (input - ref[0]) / (ref[1] - ref[0] + EPS) + var[0]); }
template<typename T>
inline T linearInterpolation(vector<T> var, vector<T> ref, T input)
{ return ((var[1] - var[0]) * (input - ref[0]) / (ref[1] - ref[0] + EPS) + var[0]); }

//==============================================================================
//顺序查询返回序列坐标
template<typename T>
int arrayPosition(vector<T>& array, T input, int initPos = 0, int endPos = 0)
{
    if (endPos == 0 && initPos == 0) endPos = array.size() - 1;
    int iTemp = max(int((initPos + endPos) / 2), 0);
    iTemp = min(iTemp, array.size() - 1);
    if (initPos > endPos)            return arrayPosition(array, input);
    else if (endPos - initPos <= 1)  return initPos;
    else if (array[iTemp] == input)  return iTemp;
    else if (array[iTemp] < input)   return arrayPosition(array, input, iTemp, endPos);
    else if (array[iTemp] > input)   return arrayPosition(array, input, initPos, iTemp);
}
