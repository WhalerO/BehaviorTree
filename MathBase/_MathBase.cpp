#include <random>
#include <ctime>

#include "_MathBase.h"


//==============================================================================
//vector矩阵/向量运算重载
vector<double> operator* (double p1, vector<double>& p2)
{
    vector<double> result;
    for (int i = 0; i < p2.size(); i++)	result.push_back(p1 * p2[i]);
    return result;
}

//==============================================================================
//随机数生成
double randomGenerate(float min, float max)
{
    std::default_random_engine RE(time(0));
    std::uniform_real_distribution<double> RD(min, max);

    return(RD(RE));
}
