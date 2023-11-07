
//-----------------------------------------------------------------------------------------------------
#include <iostream>

#include "./BehaviorTree/BehaviorTree.h"
#include "./Test/TestNode.h"
#include "./Test/Search.h"
#include "./Test/Engage.h"
#include "./Test/Return.h"
#include "./WildFire/WildFire.h"
#include "./AirTanker/AirTanker.h"

//-----------------------------------------------------------------------------------------------------
using std::cout; using std::endl; using std::string;

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
    
    /*
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
    */

    /*
    //创建火场
    WildFire *fire = new WildFire();
    //设置仿真步长
    fire->SetTimeStep(1);
    //逐步仿真至第60分钟
    for(int i = 0; i < 60; i++){
        fire->Update();
        cout << "第" << i << "分钟" << '\t';
        cout << "火场面积" << fire->GetFireArea() << endl ;
        cout << endl;
    }
    */

    //创建火场
    WildFire *fire = new WildFire();
    //创建灭火机
    AirTanker *tanker = new AirTanker();
    //初始火场位置（0，0）
    Position fireCenter(0, 0);
    //初始飞机位置（50， 50）
    Position aircraft(50, 50);
    //初始取水点位置（10，10）
    Position waterPoint(10, 10);
    //设置仿真步长
    WildFire::SetTimeStep(1);
    AirTanker::SetTimeStep(1);
    //设置火场位置
    fire->SetFireCenter(fireCenter);
    //设置飞机位置
    tanker->SetPosition(aircraft);
    //设置取水点
    tanker->SetWaterPoint(waterPoint); 
    //设置火场指针
    tanker->SetWildFire(fire);

    float timeRec = 1;
    string tankerSatuation;
    while(timeRec <= 600 && fire->GetFireSurpressPercent() < 1){
        tanker->Update();
        fire->Update();
        if(timeRec == 1 || tankerSatuation != tanker->StatusDisp()){
            cout << "第" << timeRec << "分钟" << '\t';
            cout << "火场面积\t" << fire->GetFireArea() / 1000 << "公顷\t" ;
            cout << "火环扑灭百分比\t" << 100 * fire->GetFireSurpressPercent() << "%\t" ;
            cout << tanker->StatusDisp() << endl;
            tankerSatuation = tanker->StatusDisp();
        }
        timeRec += 1;
    }
    cout << "共执行往返灭火架次：" << tanker->GetFlightRec() << endl;
    cout << "消防共耗时：" << timeRec << "分钟" << endl;

    return 0;
}

