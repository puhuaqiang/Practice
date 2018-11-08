#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
using namespace std;

/**
 * �����һ��ʵ�ַ�����
 * �����д洢���������������Ҵ洢���ǲ��ظ��ġ�
 *
 * ����JAVA�汾 ԭ���� 
 * 
 * Author��puhuaqiang
 */

const int MAX_LEVEL = 6;

/**
 * @brief �ڵ�
*/
class CNode
{
public:
    CNode();
    ~CNode();

    std::string toString();
    /**
     * @brief ��ȡ��������
    */
    CNode** GetIdxList();

    /**
     * @brief ��������
    */
    void SetData(int v);
    /**
     * @brief ��ȡ����
    */
    int GetData();
    /**
    * @brief ���������������
    */
    void SetLevel(int l);
private:
    int m_data;
    /** 
     * ��ǰ�ڵ��ÿ���ȼ�����һ���ڵ�.
     * ��2�� N1 N2
     * ��1�� N1 N2
     * ���N1�Ǳ��ڵ�,�� m_lpForwards[x] �������N2
     */
    CNode* m_lpForwards[MAX_LEVEL];
    int m_iMaxLevel;
};

/**
 * @brief ����
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
     * ����
     * ��ͷ/����(�ڵ�)
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
    /// �½ڵ�
    CNode* lpNewNode = new CNode();
    if(NULL == lpNewNode){
        return;
    }

    /**
     * �½ڵ����ֲ��ڵ��������������
     * ������� 3,�� �µĽڵ��������1��2��3�ϵ���������
    */
    int level = RandomLevel();
    lpNewNode->SetData(v);
    lpNewNode->SetLevel(level);

    /**
     * ��ʱ��������
     * ��Ҫ�ǵõ��µĽڵ���ÿ�����������ϵ�λ��
    */
    CNode *lpUpdateNode[level];
    for(int i=0; i<level; i++){
        /// ÿ�����������ͷ�ڵ�
        lpUpdateNode[i] =m_lpHead;
    }
    CNode* lpFind = m_lpHead;
    for(int i= level-1; i >= 0; --i){
        /**
         * ����λ��
         *   eg.  ��1��  1  7  10
         *   ���������� 6
         *   lpFind->GetIdxList()[i]->GetData() : ��ʾ�ڵ�lpFind�ڵ�1����������һ���ڵ������
         *   �� "lpFind->GetIdxList()[i]->GetData() < v"��������ʱ��,
         *   �½ڵ��Ҫ���뵽 lpFind�ڵ�ĺ���, lpFind->GetIdxList()[i] �ڵ��ǰ��
         *   �������� lpFind����1  lpFind->GetIdxList()[i] ����7
        */
        while((NULL != lpFind->GetIdxList()[i]) && (lpFind->GetIdxList()[i]->GetData() < v)){
            lpFind = lpFind->GetIdxList()[i];
        }
        /// lpFind ���½ڵ��� ��i����������ĺ�һ���ڵ�
        lpUpdateNode[i] = lpFind;
    }

    for(int i=0; i<level; ++i){
        /**
         * ������������ָ��λ��
         *   eg  ��1������ 1  7  10
         *      ����6.
         *      lpUpdateNode[i] �ڵ���1; lpUpdateNode[i]->GetIdxList()[i]�ڵ���7
         *  
         *  ��2�������� ��6���� 1��7֮��
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
        std::cout<<"��"<<i<<"��:"<<std::endl;
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