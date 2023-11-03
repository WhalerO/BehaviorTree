
#include "Selector.h"

//---------------------------------------------------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------------------------------------------------
NodeStatus Selector::execute()
{
    NodeStatus status_child = NodeStatus::Inactive;
    //重新初始化容器
    success_nodes.clear();
    failure_nodes.clear();
    running_nodes.clear();
    inactive_nodes.clear();
    
    //对各子节点状态进行记录
    for (auto child : children)
    {
        status_child = child->execute();
        if (status_child == NodeStatus::Success)
            success_nodes.push_back(child);
        else if (status_child == NodeStatus::Failure)
            failure_nodes.push_back(child);
        else if (status_child == NodeStatus::Running)
            running_nodes.push_back(child);
        else if (status_child == NodeStatus::Inactive)
            inactive_nodes.push_back(child);
    }

    //返回状态（或）
    if(success_nodes.size() > 0)
        return NodeStatus::Success;
    else return NodeStatus::Failure;
}
