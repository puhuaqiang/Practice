#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;

/**
 * 跳表的一种实现方法。
 * 跳表中存储的是正整数，并且存储的是不重复的。
 *
 * 翻译JAVA版本 原作者 
 * 
 * Author：puhuaqiang
 */

const int MAX_LEVEL = 6;

/**
 * @brief 节点
*/
class CNode
{
public:
    CNode();
    ~CNode();

    std::string toString();
    /**
     * @brief 获取索引链表
    */
    CNode** GetIdxList();

    /**
     * @brief 设置数据
    */
    void SetData(int v);
    /**
     * @brief 获取数据
    */
    int GetData();
    /**
    * @brief 设置最大索引级别
    */
    void SetLevel(int l);
private:
    int m_data;
    /** 
     * 当前节点的每个等级的下一个节点.
     * 第2级 N1 N2
     * 第1级 N1 N2
     * 如果N1是本节点,则 m_lpForwards[x] 保存的是N2
     */
    CNode* m_lpForwards[MAX_LEVEL];
    int m_iMaxLevel;
};

/**
 * @brief 跳表
*/
class CSkipList
{
public:
    CSkipList();
    ~CSkipList();

    CNode* Find(int v);
    void Insert(int v);
    void Delete(int v);
    void PrintAll();
    void PrintAll(int l);
    int RandomLevel();

private:
    int levelCount;
    /**
     * 链表
     * 带头/哨所(节点)
    */
    CNode* m_lpHead;
};

int main()
{
    CSkipList skipList;
    for(int i=1; i< 10; i++){
        if((i%3) == 0){
            skipList.Insert(i);
        }
    }
    for(int i=1; i< 10; i++){
        if((i%3) == 1){
            skipList.Insert(i);
        }
    }
    skipList.PrintAll();
    std::cout<<std::endl;
    skipList.PrintAll(-1);
    std::cin.ignore();
    return 0;
}

CNode::CNode()
{
    m_data = -1;
    m_iMaxLevel = 0;
    for(int i=0; i<MAX_LEVEL; i++){
        m_lpForwards[i] = NULL;
    }
}
CNode::~CNode()
{

}
CNode** CNode::GetIdxList()
{
    return m_lpForwards;
}

void CNode::SetData(int v)
{
    m_data = v;
}
int CNode::GetData()
{
    return m_data;
}
void CNode::SetLevel(int l)
{
    m_iMaxLevel = l;
}
std::string CNode::toString()
{
    char tmp[32];
    std::string ret;

    ret.append("{ data: ");
    sprintf(tmp, "%d", m_data);
    ret.append(tmp);
    ret.append("; levels: ");
    sprintf(tmp, "%d", m_iMaxLevel);
    ret.append(tmp);
    ret.append(" }");
    return ret;
}

CSkipList::CSkipList()
{
    levelCount = 1;
    m_lpHead = new CNode();
}
CSkipList::~CSkipList()
{

}
CNode* CSkipList::Find(int v)
{

}
void CSkipList::Insert(int v)
{
    /// 新节点
    CNode* lpNewNode = new CNode();
    if(NULL == lpNewNode){
        return;
    }

    /**
     * 新节点最大分布在的索引链表的上限
     * 如果返回 3,则 新的节点会在索引1、2、3上的链表都存在
    */
    int level = RandomLevel();
    lpNewNode->SetData(v);
    lpNewNode->SetLevel(level);

    /**
     * 临时索引链表
     * 主要是得到新的节点在每个索引链表上的位置
    */
    CNode *lpUpdateNode[level];
    for(int i=0; i<level; i++){
        /// 每个索引链表的头节点
        lpUpdateNode[i] =m_lpHead;
    }
    CNode* lpFind = m_lpHead;
    for(int i= level-1; i >= 0; --i){
        /**
         * 查找位置
         *   eg.  第1级  1  7  10
         *   如果插入的是 6
         *   lpFind->GetIdxList()[i]->GetData() : 表示节点lpFind在第1级索引的下一个节点的数据
         *   当 "lpFind->GetIdxList()[i]->GetData() < v"不成立的时候,
         *   新节点就要插入到 lpFind节点的后面, lpFind->GetIdxList()[i] 节点的前面
         *   即在这里 lpFind就是1  lpFind->GetIdxList()[i] 就是7
        */
        while((NULL != lpFind->GetIdxList()[i]) && (lpFind->GetIdxList()[i]->GetData() < v)){
            lpFind = lpFind->GetIdxList()[i];
        }
        /// lpFind 是新节点在 第i级索引链表的后一个节点
        lpUpdateNode[i] = lpFind;
    }

    for(int i=0; i<level; ++i){
        /**
         * 重新设置链表指针位置
         *   eg  第1级索引 1  7  10
         *      插入6.
         *      lpUpdateNode[i] 节点是1; lpUpdateNode[i]->GetIdxList()[i]节点是7
         *  
         *  这2句代码就是 把6放在 1和7之间
        */
        lpNewNode->GetIdxList()[i] = lpUpdateNode[i]->GetIdxList()[i];
        lpUpdateNode[i]->GetIdxList()[i] = lpNewNode;
    }
    if(levelCount < level){
        levelCount = level;
    }
}
void CSkipList::Delete(int v)
{

}
void CSkipList::PrintAll()
{
    CNode* lpNode = m_lpHead;
    while(NULL != lpNode->GetIdxList()[0]){
        std::cout<<lpNode->GetIdxList()[0]->toString().data()<<std::endl;
        lpNode = lpNode->GetIdxList()[0];
    }
}
void CSkipList::PrintAll(int l)
{
    for(int i=MAX_LEVEL-1; i>=0;--i){
        CNode* lpNode = m_lpHead;
        std::cout<<"第"<<i<<"级:"<<std::endl;
        if((l < 0) || ((l >= 0) && (l == i))){
            while(NULL != lpNode->GetIdxList()[i]){
                std::cout<<lpNode->GetIdxList()[i]->GetData()<<" ";
                lpNode = lpNode->GetIdxList()[i];
            }
            std::cout<<std::endl;
            if(l >= 0){
                break;
            }
        }
    }
}
int GetRandom()
{
    static int _count = 1;
	std::default_random_engine generator(time(0) + (_count++));
	std::uniform_int_distribution<int> distribution(1,99999/*0x7FFFFFFF*/);
	int dice_roll = distribution(generator);
	return dice_roll;
}
int CSkipList::RandomLevel()
{
    int level = 1;
    for(int i=1; i<MAX_LEVEL; ++i){
        if(1 == (GetRandom()%2)){
            level++;
        }
    }
    return level;
}