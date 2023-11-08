

#include "AirTanker.h"

//=====================================================================================================================
float AirTanker::timeStep = 1;

//---------------------------------------------------------------------------------------------------------------------
//执行仿真计算
void AirTanker::Update()
{
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //仿真初判断是否有油
    if(!isFuelRemain){
        if(reFuelTimeRec >= supplyTime){
            reFuelTimeRec = 0;
            fuelWeight = fuelCapacity;
            isFuelRemain = true;
            reFuelRec++;
        }
        else{
            reFuelTimeRec += WildFire::timeStep;
            return;
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //若尚未完成初次出动，则进行整备
    if(!isEngaged){
        if(readyTimeRec >= readyTime){
            readyTimeRec = 0;
            isEngaged = true;
        }
        else{
            readyTimeRec += WildFire::timeStep;
            return;
        }
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //若吊桶中有水，执行吊桶洒水
    if(isWaterLoaded){
        //若抵达火场，执行灭火
        if(position.inRange(wildFire->fireCenter, 0.01)){
            wildFire->curTurnTotalWater += fleetNum * loadWeight * effectiveRate / 100 * accuracy / 100;
            isWaterLoaded = false;
            flightRec += fleetNum;
        }
        //若未抵达火场，执行吊桶飞行
        else    position.transToPosition(wildFire->fireCenter, (WildFire::timeStep / 60), bucketSpeed);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //若吊桶中无水，执行取水
    else{
        //若抵达取水点，执行取水
        if(position.inRange(waterPoint, 0.01)){
            //若取水未完成，执行取水
            if(loadTimeRec < reLoadTime){
                loadTimeRec += WildFire::timeStep;
                return;
            }
            isWaterLoaded = true;
            loadTimeRec = 0;
        }
        //若未抵达取水点，执行飞行
        else    position.transToPosition(waterPoint, (WildFire::timeStep / 60), cruiseSpeed);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //油耗计算
    fuelWeight -= fuelCost * WildFire::timeStep;
    if(fuelWeight < EPS)    isFuelRemain = false;
}

//---------------------------------------------------------------------------------------------------------------------
//输出当前飞机状态
std::string AirTanker::StatusDisp()
{
    std::string result;

    if(!isFuelRemain)   result = "正在加油";
    else if(!isEngaged)  result = "准备中";
    else{
        if(isWaterLoaded)   result = "正在灭火";
        else    result = "正在汲水";
    }

    return result;
}
