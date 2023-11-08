
#include "Sequence.h"

//---------------------------------------------------------------------------------------------------------------------
//执行节点（返回状态）
NodeStatus Sequence::execute(){
    //节点准入判断
    if (!entranceCheck()) return Inactive;
    //子节点状态重设判断
    childrenStatusResetCheck();
    //若当前状态为成功，则向下执行子节点
    if (status == Success){
        for (auto child : children){
            child->execute();
        }
    }
    //执行节点具体逻辑
    status = executeNode();
    return status;
}
