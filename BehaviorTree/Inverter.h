#pragma once

#include "SyncActionNode.h"

//=====================================================================================================================

///同步行为树反转节点基类：用于对子节点状态进行反转（非）
class Inverter : public SyncActionNode
{
private:

public:
    Inverter(/* args */) : SyncActionNode("Inverter") {};
    ~Inverter() {};

    //执行节点逻辑(返回状态)
    NodeStatus execute() override;

};