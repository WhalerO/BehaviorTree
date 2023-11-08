
#include <iostream>
#include <algorithm>

#include "SyncActionNode.h"

using std::cout; using std::endl;

//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
float SyncActionNode::g_fTimeStep = 0.1;

//---------------------------------------------------------------------------------------------------------------------
SyncActionNode::SyncActionNode(/* args */) {}
SyncActionNode::SyncActionNode(std::string name){
    this->name = name;
}
SyncActionNode::~SyncActionNode(){
    children.clear();
}

//---------------------------------------------------------------------------------------------------------------------
//节点展示
void SyncActionNode::disp(int depth){
    //展示当前节点
    for (int i = 0; i < depth; i++) {
        if (depth)   cout << '|';
        cout << "----";
    }
    //状态展示：成功-√，失败-×，运行中-○，未运行/默认-□
    cout << name << ' ';
    switch (getStatus())
    {
    case Success: {
        cout << "\u221a" << endl; 
        break;
    }
    case Failure: {
        cout << "\u00d7" << endl; 
        break;
    }
    case Running: {
        cout << "\u25cb" << endl; 
        break;
    }
    default: {
        cout << "\u25a1" << endl; 
        break;
    }
    }
    //已展示节点纪录
    std::vector<SyncActionNode*> dispRec;
    dispRec.push_back(this);
    //展示子节点
    for (auto child : children){
        child->disp(dispRec, depth + 1);
    }
    return;
}
void SyncActionNode::disp(std::vector<SyncActionNode*>& upperList, int depth){
    //展示当前节点
    for (int i = 0; i < depth; i++) {
        if (depth)   cout << '|';
        cout << "----";
    }
    //状态展示：成功-√，失败-×，运行中-○，未运行/默认-□
    cout << name << ' ';
    switch (getStatus())
    {
    case Success: {
        cout << "\u221a" << endl; 
        break;
    }
    case Failure: {
        cout << "\u00d7" << endl; 
        break;
    }
    case Running: {
        cout << "\u25cb" << endl; 
        break;
    }
    default: {
        cout << "\u25a1" << endl; 
        break;
    }
    }
    //已展示节点纪录
    std::vector<SyncActionNode*> dispRec = upperList;
    //子节点闭合标识
    bool childClosed = false;
    //循环判断
    for (auto child : children){
        //若当前子节点在子节点列表中，则跳过
        for (auto child_ : dispRec) {
            if (child_ == child) {
                childClosed = true; 
                continue;
            }
        }
        if(childClosed) continue;
        //展示子节点（保留一级循环项，体现循环关系）
        dispRec.push_back(child);
        child->disp(dispRec, depth + 1);
    }
    return;
}

//---------------------------------------------------------------------------------------------------------------------
//返回所有直接、间接子节点
std::vector<SyncActionNode*> SyncActionNode::getAllChildren(){
    std::vector<SyncActionNode*> allChildren;
    for (auto child : children){
        //当前层子节点
        allChildren.push_back(child);
        //下层子节点
        std::vector<SyncActionNode*> childChildren = child->getAllChildren(allChildren);
        allChildren.insert(allChildren.end(), childChildren.begin(), childChildren.end());
    }
    return allChildren;
}
std::vector<SyncActionNode*> SyncActionNode::getAllChildren(std::vector<SyncActionNode*>& upperList){
    std::vector<SyncActionNode*> allChildren;
    std::vector<SyncActionNode*> recList = upperList;
    //子节点闭合标识
    bool childClosed = false;
    //循环判断
    for (auto child : children){
        //若当前子节点在子节点列表中，则跳过
        for (auto child_ : recList) {
            if (child_ == child) {
                childClosed = true; 
                continue;
            }
        }
        if(childClosed) continue;
        //当前层子节点
        allChildren.push_back(child);
        recList.push_back(child);
        //下层子节点
        std::vector<SyncActionNode*> childChildren = child->getAllChildren(recList);
        allChildren.insert(allChildren.end(), childChildren.begin(), childChildren.end());
    }
    return allChildren;
}

//---------------------------------------------------------------------------------------------------------------------
//子节点状态重设判断：若子节点均为非运行且尚未激活，则重设节点状态为非激活
void SyncActionNode::childrenStatusResetCheck(){
    //获取所有子节点
    std::vector<SyncActionNode*> allChildren = getAllChildren();
    //子节点判断
    for (auto child : allChildren){
        if (child->getStatus() == Running || child->getStatus() == Inactive) return;
    }
    for(auto child : allChildren)
        child->status = Inactive;
}

//---------------------------------------------------------------------------------------------------------------------
//添加子节点
void SyncActionNode::addChild(SyncActionNode* child){
    //避免重复添加
    for (auto child_ : children) {
		if (child_ == child) return;
	}
    children.push_back(child);
    //设置父节点
    if(child->getParent() == this) return;
    child->setParent(this);
}
//设置父节点
void SyncActionNode::setParent(SyncActionNode* parent) {
    //避免重复设置
    if (this->parent == parent) return;
    this->parent = parent;
    //设置子节点
    parent->addChild(this);
}

//---------------------------------------------------------------------------------------------------------------------
//删除所有子节点
void SyncActionNode::clearAllChildren() {
    for (auto child : children)
        SyncActionNodeDistory(child);
    children.clear();
}

//---------------------------------------------------------------------------------------------------------------------
//行为树节点析构函数
void SyncActionNodeDistory(SyncActionNode* node){
    if (!node)   return;
    //保存子节点地址
    auto childrenAddr = node->children;
    node->children.clear();
    //对根析构
    delete node;
    //对子节点析构
    for (auto child : childrenAddr){
        if(child->getStatus() == Success || child->getStatus() == Failure || 
            child->getStatus() == Inactive || child->getStatus() == Running)
            continue;
        SyncActionNodeDistory(child);
    }
}

//---------------------------------------------------------------------------------------------------------------------
//节点自检更新
void SyncActionNode::selfCheck(){
    //遍历子节点，若其状态非成功、失败、运行中、未激活，则从子节点列表中删除
    for (auto child : children){
        if (child->getStatus() == Success || child->getStatus() == Failure || 
            child->getStatus() == Inactive || child->getStatus() == Running)
            continue;
        //删除子节点
        auto it = std::find(children.begin(), children.end(), child);
        children.erase(it);
    }
}
