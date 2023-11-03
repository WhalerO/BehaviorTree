
//-----------------------------------------------------------------------------------------------------
#include <iostream>

#include "./BehaviorTree/BehaviorTree.h"
#include "./Test/TestNode.h"
#include "./Test/Search.h"
#include "./Test/Engage.h"
#include "./Test/Return.h"

//-----------------------------------------------------------------------------------------------------
using std::cout; using std::endl;

//-----------------------------------------------------------------------------------------------------
int main() 
{
    //创建树
    BehaviorTree* tree = new BehaviorTree("TreeTest");
    /*
    //创建各测试节点
    TestNode *node1 = new TestNode("TestNode1");
    TestNode *node2 = new TestNode("TestNode2");
    TestNode *node3 = new TestNode("TestNode3");
    TestNode *node4 = new TestNode("TestNode4");
    TestNode *node5 = new TestNode("TestNode5");
    TestNode *node6 = new TestNode("TestNode6");
    TestNode *node7 = new TestNode("TestNode7");
    TestNode *node8 = new TestNode("TestNode8");
    //创建各中间节点
    Selector *selector1 = new Selector();
    Merger *merger1 = new Merger();
    Inverter *inverter1 = new Inverter();

    //拼接子节点
    node1->addChild(node2);
    node2->addChild(selector1);
    selector1->addChild(node3);
    selector1->addChild(node4);
    node5->addChild(merger1);
    merger1->addChild(node6);
    node7->addChild(inverter1);
    inverter1->addChild(node8);
    node2->setStatus(Success);
    node4->setStatus(Failure);
    node6->setStatus(Running);

    //添加节点至行为树
    tree->addSubTree(node1);
    tree->addSubTree(node5);
    tree->addSubTree(node7);

    //树展示
    tree->disp();
    //树重置
    tree->reset();
    tree->disp();
    */

    //设置仿真步长
    SyncActionNode::setTimeStep(0.1);
    //搜救出发点、目标点、返回点
    Position startPos(0, 0);
    Position targetPos(10, 10);
    Position returnPos(0, 0);
    //搜索半径、发现概率、搜救间隔
    double rescueRadius = 4;
    double discoverProb = 0.5;
    double scanRange = 10;
    //搜救速度、飞行速度
    double rescueSpeed = 10;
    double flightSpeed = 10;
    //飞行器
    Position aircraft(startPos);

    //创建抵近、搜索、返回节点
    Engage *engage = new Engage(startPos, targetPos, rescueRadius, flightSpeed);
    Search *search = new Search(rescueRadius, rescueSpeed, discoverProb, targetPos, flightSpeed, scanRange);
    Return *ret = new Return(returnPos, flightSpeed);
    engage->setName("Engage");
    search->setName("Search");
    ret->setName("Return");
    engage->setAircraft(&aircraft);
    search->setAircraft(&aircraft);
    ret->setAircraft(&aircraft);

    //连接行为树
    ret->addChild(engage);
    search->addChild(ret);
    engage->addChild(search);
    tree->addSubTree(engage);
    tree->disp();

    //节点删除
    tree->deleteSubTree(engage);
    tree->disp();
    return 0;

    //树运行
    while(ret->getStatus() != Success){
        tree->execute();
        tree->disp();
    }

    return 0;
}

