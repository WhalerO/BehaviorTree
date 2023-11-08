#pragma once

#include <string>
#include <vector>

//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
//节点状态枚举，成功——Success, 失败——Failure，运行中——Running，非激活——Inactive
enum NodeStatus { Success, Failure, Running, Inactive };

//---------------------------------------------------------------------------------------------------------------------
///同步行为树节点基类
class SyncActionNode
{
protected:
    //仿真计算步长
    static float g_fTimeStep;
    //节点的子节点
    std::vector<SyncActionNode*> children;
    //节点的父节点
    SyncActionNode* parent = NULL;
    //默认节点处于非激活状态
    NodeStatus status = Inactive;
    //节点名称
    std::string name;

    //子节点状态重设判断：若子节点均为非运行且尚未激活，则重设节点状态为非激活
    void childrenStatusResetCheck();
    //行为树节点析构函数
    friend void SyncActionNodeDistory(SyncActionNode* node);

public:
    SyncActionNode(/* args */);
    SyncActionNode(std::string name);
    ~SyncActionNode();

    //执行节点逻辑(返回状态)
    virtual NodeStatus execute() = 0;

    //节点准入逻辑
    inline bool entranceCheck()
    {if(parentStatusEntranceCheck()) return true; else return false;}
    //获取节点状态
    inline NodeStatus getStatus()
    { return status;}
    //获取节点名称
    inline std::string getName()
    { return name;}
    //设置节点名称
    inline void setName(std::string name)
    { this->name = name;}
    //获取子节点
    inline std::vector<SyncActionNode*> getChildren()
    { return children;}
    //获取父节点
    inline SyncActionNode* getParent()
    { return parent;}
    //父节点状态准入判断：父节点不为未激活则准入
    inline bool parentStatusEntranceCheck()
    { if(parent->getStatus() != Inactive) return true; else return false;}
    //修改全局仿真时间步长
    static inline void setTimeStep(float timeStep)
    { g_fTimeStep = timeStep;}

    //节点展示
    void disp(int depth = 0);
    void disp(std::vector<SyncActionNode*>& upperList, int depth = 0);
    //返回所有直接、间接子节点
    std::vector<SyncActionNode*> getAllChildren();
    std::vector<SyncActionNode*> getAllChildren(std::vector<SyncActionNode*>& upperList);
    //添加子节点
    void addChild(SyncActionNode* child);
    //设置父节点
    void setParent(SyncActionNode* parent);
    //删除所有子节点
    void clearAllChildren();
    //节点自检更新
    void selfCheck();

};

//---------------------------------------------------------------------------------------------------------------------
//行为树节点析构函数
void SyncActionNodeDistory(SyncActionNode* node);