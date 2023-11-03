
#include <iostream>

#include "BehaviorTree.h"

//---------------------------------------------------------------------------------------------------------------------
//构造与析构
BehaviorTree::BehaviorTree(std::string name, SyncActionNode* root){
    this->name = name;
    this->root = root;
    branches.push_back(root);
}
BehaviorTree::BehaviorTree(std::string name){
    this->name = name;
    root = new Root();
}
BehaviorTree::BehaviorTree(){ root = new Root();}
BehaviorTree::~BehaviorTree(){
    root->clearAllChildren();
    delete root;
}

//---------------------------------------------------------------------------------------------------------------------
//行为树执行
void BehaviorTree::execute(){
    //树结构更新
    updateBranches();
    //若活动节点为空，则执行根节点
    if (runningNodes.empty())
        root->execute();
    //否则执行活动节点
    else
        for (auto node : runningNodes)
            node->execute();
}

//---------------------------------------------------------------------------------------------------------------------
//树结构展示
void BehaviorTree::disp(){
    std::cout << "Behavior Tree: " << name << std::endl;
    root->disp();
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//树结构删除
void BehaviorTree::deleteSubTree(SyncActionNode* node){
    //记录父节点
    SyncActionNode* parentRec = node->getParent();
    //删除节点
    SyncActionNodeDistory(node);
    //执行父节点自检
    parentRec->selfCheck();
    //更新树结构
    updateBranches();
}
void BehaviorTree::deleteSubTree(std::string nodeName){
    //禁止删除根节点、功能节点
    if(nodeName == "Root" || nodeName == "root" ||
       nodeName == "Selector" || nodeName == "selector" ||
       nodeName == "Inverter" || nodeName == "inverter" ||
       nodeName == "Merger" || nodeName == "merger"){
        return;
    }
    for (auto branch : branches)
        if (branch->getName() == nodeName){
            delete branch;
        }
    updateBranches();
}

//---------------------------------------------------------------------------------------------------------------------
//树结构添加
void BehaviorTree::addSubTree(SyncActionNode* node, BehaviorTree* sub_tree){
    for (auto branch : branches)
        if (branch == node){
            branch->addChild(sub_tree->root);
        }
    updateBranches();
}
void BehaviorTree::addSubTree(SyncActionNode *node, SyncActionNode *sub_tree){
    for (auto branch : branches)
        if (branch == node){
            branch->addChild(sub_tree);
        }
    updateBranches();
}

void BehaviorTree::addSubTree(std::string nodeName, BehaviorTree* sub_tree){
    for (auto branch : branches)
        if (branch->getName() == nodeName){
            branch->addChild(sub_tree->root);
        }
    updateBranches();
}
void BehaviorTree::addSubTree(std::string nodeName, SyncActionNode *sub_tree){
    for (auto branch : branches)
        if (branch->getName() == nodeName){
            branch->addChild(sub_tree);
        }
    updateBranches();
}

void BehaviorTree::addSubTree(BehaviorTree* sub_tree){
    root->addChild(sub_tree->root);
    updateBranches();
}
void BehaviorTree::addSubTree(SyncActionNode *sub_tree){
    root->addChild(sub_tree);
    updateBranches();
}

//---------------------------------------------------------------------------------------------------------------------
//树结构更新
void BehaviorTree::updateBranches(){
    //树结构清空
    branches.clear();
    //树结构更新
    branches = root->getAllChildren();
    //更新运行中节点
    runningNodes.clear();
    for (auto child : branches)
        if (child->getStatus() == Running)
            runningNodes.push_back(child);
}
