
#include "TestNode.h"

//=====================================================================================================================
TestNode::TestNode(/* args */)
{
    name = "TestNode";
}

//---------------------------------------------------------------------------------------------------------------------
bool TestNode::entranceCheck(){
    return true;
}

//---------------------------------------------------------------------------------------------------------------------
NodeStatus TestNode::execute(){
    return Running;
}

//---------------------------------------------------------------------------------------------------------------------
void TestNode::setStatus(NodeStatus status) {
	this->status = status;
}