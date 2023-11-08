#pragma once

#include "../BehaviorTree/Sequence.h"


//=====================================================================================================================

//测试类：序列节点
class TestNode : public Sequence
{
private:


public:
    TestNode(/* args */);
    TestNode(std::string name) : Sequence(name){};
    ~TestNode() {};

    //节点准入逻辑
    bool entranceCheck() override;
    //节点执行逻辑
    NodeStatus execute() override;
    //设置节点状态
    void setStatus(NodeStatus status);

};