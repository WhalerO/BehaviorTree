
#include "Inverter.h"


//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
NodeStatus Inverter::execute()
{
    NodeStatus status_child = NodeStatus::Inactive;  
    //接收子节点状态
    status_child = children[0]->execute();
    //若子节点正在运行或未激活，保持不变
    if (status_child == NodeStatus::Running || status_child == NodeStatus::Inactive)
        return status_child;
    //若子节点成功，则反转为失败
    else if (status_child == NodeStatus::Success)
        return NodeStatus::Failure;
    //若子节点失败，则反转为成功
    else if (status_child == NodeStatus::Failure)
        return NodeStatus::Success;
    //否则保持不变（异常情况）
    else    return status_child;
    
}