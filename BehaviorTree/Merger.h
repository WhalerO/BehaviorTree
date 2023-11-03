#pragma once

#include "SyncActionNode.h"

//=====================================================================================================================

///同步行为树合并节点基类：用于对子节点状态进行合并（与）
class Merger : public SyncActionNode
{

public:
    Merger(/* args */) : SyncActionNode("Merger") {};
    ~Merger() {};

    //执行节点逻辑(返回状态)
    NodeStatus execute() override;

};