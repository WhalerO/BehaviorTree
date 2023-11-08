#pragma once

#include "SyncActionNode.h"

//=====================================================================================================================

///同步行为树次序节点基类：用于执行具体任务
class Sequence : public SyncActionNode
{

public:
    Sequence(/* args */) : SyncActionNode() {};
    Sequence(std::string name) : SyncActionNode(name){};
    ~Sequence() {};

    //执行节点逻辑(返回状态)
    NodeStatus execute();

    //执行节点具体逻辑
    virtual NodeStatus executeNode() = 0;
    //节点准入逻辑
    virtual bool entranceCheck() = 0;
};
