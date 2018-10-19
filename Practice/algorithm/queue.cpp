#include <iostream>
#include <string>
using namespace std;

class CArrayQueue
{
public:
    /**
     * @brief 申请一个大小为 capacity 的数组
    */
    CArrayQueue(int capacity);
    ~CArrayQueue();
    /**
     * @brief 入队
    */
    bool enqueue(int v);
    /**
     * @brief 入队,空间不足,搬移数据
    */
    bool enqueue2(int v);
    /**
     * @brief 出队
    */
    int dequeue(int* lpError);
    /**
     * @brief 是否空
    */
    bool empty();
private:
    /**数组*/
    int* m_lpValues;
    /**数组大小*/
    int m_iValueCnt;
    /**对头下标*/
    int m_iHead;
    /**队尾下标*/
    int m_iTail;
};

int main()
{
    CArrayQueue queue(10);
    for(int i=1;i<10;i+=2){
        queue.enqueue(i);
    }
    while(!queue.empty()){
        std::cout<<queue.dequeue(NULL)<<std::endl;
    }
    std::cin.ignore();
    return 0;
}

CArrayQueue::CArrayQueue(int capacity)
:m_iHead(0),
m_iValueCnt(0),
m_iTail(0),
m_lpValues(NULL)
{
    if(capacity > 0){
        m_iValueCnt = capacity;
        m_lpValues = new int[m_iValueCnt];
    }
}
CArrayQueue::~CArrayQueue()
{
    if(NULL != m_lpValues){
        delete[] m_lpValues;
        m_lpValues = NULL;
    }
}
bool CArrayQueue::enqueue(int v)
{
    if((m_iTail == m_iValueCnt) || (NULL == m_lpValues)){
        //队列已经满了
        return false;
    }
    m_lpValues[m_iTail] = v;
    ++m_iTail;
    return true;
}
/**
 * @brief 入队,空间不足,搬移数据
*/
bool CArrayQueue::enqueue2(int v)
{
    if(NULL == m_lpValues){
        return false;
    }
    if(m_iTail == m_iValueCnt){
        //表示队列末尾没有空间了
        if(0 == m_iHead){
            //表示整个队列都占满了
            return false;
        }
        // 数据搬移
        for(int i=m_iHead; i< m_iTail; ++i){
            m_lpValues[i-m_iHead] = m_lpValues[i];
        }
        // 搬移完之后重新更新 head 和 tail
        m_iTail -= m_iHead;
        m_iHead = 0;
        return false;
    }
    m_lpValues[m_iTail] = v;
    ++m_iTail;
    return true;
}
int CArrayQueue::dequeue(int* lpError)
{
    if(NULL != lpError){
        *lpError = -1;
    }
    if(empty() || (NULL == m_lpValues)){
        /// 队列为空
        return 0;
    }
    int ret = m_lpValues[m_iHead];
    ++m_iHead;
    return ret;
}
bool CArrayQueue::empty()
{
    return m_iTail == m_iHead;
}