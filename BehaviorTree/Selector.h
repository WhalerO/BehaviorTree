#pragma once

#include "SyncActionNode.h"

//=====================================================================================================================

///同步行为树选择节点基类：用于对子节点状态进行集合（或）
class Selector : public SyncActionNode
{
private:
    //标识为成功的节点
    std::vector<SyncActionNode*> success_nodes;
    //标识为失败的节点
    std::vector<SyncActionNode*> failure_nodes;
    //标识为运行中的节点
    std::vector<SyncActionNode*> running_nodes;
    //标识为非激活的节点
    std::vector<SyncActionNode*> inactive_nodes;
    
public:
    Selector(/* args */) : SyncActionNode("Selector") {};
    ~Selector() {};

    //执行节点逻辑(返回状态)
    NodeStatus execute() override;
    
    //返回成功节点
    std::vector<SyncActionNode*> getSuccessNodes();
    //返回失败节点
    std::vector<SyncActionNode*> getFailureNodes();
    //返回运行中节点
    std::vector<SyncActionNode*> getRunningNodes();
    //返回非激活节点
    std::vector<SyncActionNode*> getInactiveNodes();

};