
#include "Root.h"

//---------------------------------------------------------------------------------------------------------------------
Root::Root(/* args */) : SyncActionNode("Root"){
    status = Success;
}
Root::~Root() {
}

//---------------------------------------------------------------------------------------------------------------------
//执行节点逻辑
NodeStatus Root::execute(){
    //并行执行子节点
    for (auto child : children){
        child->execute();
    }
    return Inactive;
}
