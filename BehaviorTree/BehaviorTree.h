#pragma once

#include "SyncActionNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Inverter.h"
#include "Merger.h"
#include "Root.h"

//=====================================================================================================================

///行为树类
class BehaviorTree
{
private:
    //树名
    std::string name;
    //根节点
    SyncActionNode* root;
    //枝叶节点
    std::vector<SyncActionNode*> branches;
    //运行中节点
    std::vector<SyncActionNode*> runningNodes;
    //行为树状态
    NodeStatus status = Running;

    //更新树结构
    void updateBranches();

public:
    //构造函数
    BehaviorTree(std::string name, SyncActionNode* root);
    BehaviorTree(std::string name);
    BehaviorTree();
    //析构函数
    ~BehaviorTree();

    //展示树结构
    void disp();
    //删除以某节点为根的子树
    void deleteSubTree(SyncActionNode* node);
    //删除以某节点名为根的子树
    void deleteSubTree(std::string name);
    //将树添加至某节点下
    void addSubTree(SyncActionNode* node, BehaviorTree* sub_tree);
    //将节点序列添加至某节点下
    void addSubTree(SyncActionNode *node, SyncActionNode *sub_tree);
    //将树添加至某节点名的节点下
    void addSubTree(std::string name, BehaviorTree* sub_tree);
    //将节点序列添加至某节点名的节点下
    void addSubTree(std::string name, SyncActionNode *sub_tree);    
    //将树添加至根节点下
    void addSubTree(BehaviorTree* sub_tree);
    //将节点序列添加至根节点下
    void addSubTree(SyncActionNode *sub_tree);

    //行为树执行
    void execute();
    
    //执行树重置
    inline void reset()
    { root->clearAllChildren(); }
    //获取树名
    inline std::string getName()
    { return name;}

};