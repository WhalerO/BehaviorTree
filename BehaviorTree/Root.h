#pragma once

#include "SyncActionNode.h"

//=====================================================================================================================

///同步行为树次序节点基类：用于执行具体任务
class Root : public SyncActionNode
{
    
public:
    Root(/* args */);
    ~Root();

    //执行节点逻辑(返回状态)
    NodeStatus execute() override;
    
};
