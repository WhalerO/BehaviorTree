

#include "AirTanker.h"

//=====================================================================================================================

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
        if(position.inRange(wildFire->fireCenter, 10)){
            wildFire->curTurnTotalWater += loadWeight;
            isWaterLoaded = false;
        }
        //若未抵达火场，执行吊桶飞行
        else    position.transToPosition(wildFire->fireCenter, WildFire::timeStep, bucketSpeed);
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //若吊桶中无水，执行取水
    else{
        //若抵达取水点，执行取水
        if(position.inRange(waterPoint, 10)){
            //若取水未完成，执行取水
            if(loadTimeRec < reLoadTime){
                loadTimeRec += WildFire::timeStep;
                return;
            }
            isWaterLoaded = true;
            loadTimeRec = 0;
        }
        //若未抵达取水点，执行飞行
        else    position.transToPosition(waterPoint, WildFire::timeStep, cruiseSpeed);
    }


}
