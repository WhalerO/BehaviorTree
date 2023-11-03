
#include "Merger.h"


//---------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
NodeStatus Merger::execute()
{
    NodeStatus status_child = NodeStatus::Inactive;
    //当存在节点不为成功时，返回失败
    for (auto child : children)
    {
        status_child = child->execute();
        if (status_child != NodeStatus::Success)
            return NodeStatus::Failure;
    }
    //否则返回成功
    return NodeStatus::Success;
}