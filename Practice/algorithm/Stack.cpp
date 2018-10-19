#include <iostream>
#include <string>
using namespace std;

class CArrayStack
{
public:
    CArrayStack(int n);
    ~CArrayStack();
    /**
     * @brief 入栈操作
    */
    bool push(int v);
    /**
     * @brief 出栈操作
    */
    int pop(int* lpError);
    /**
     * @brief 是否空
    */
    bool empty();
private:
    /**数组*/
    int* m_lpValues;
    /**数组大小*/
    int m_iValueCnt;
    /**数据元素个数*/
    int m_iDataCnt;
};

int main()
{
    CArrayStack stack(10);
    for(int i=1;i<10;i+=2){
        stack.push(i);
    }
    while(!stack.empty()){
        std::cout<<stack.pop(NULL)<<std::endl;
    }
    std::cin.ignore();
    return 0;
}

CArrayStack::CArrayStack(int n)
:m_iDataCnt(0),
m_iValueCnt(0)
{
    m_lpValues = NULL;
    if(n > 0){
        m_iValueCnt = n;
        m_lpValues = new int[m_iValueCnt];
    }
}
CArrayStack::~CArrayStack()
{
    if(NULL != m_lpValues){
        delete[] m_lpValues;
        m_lpValues = NULL;
    }
}
bool CArrayStack::push(int v)
{
    if((m_iValueCnt == m_iDataCnt) || (NULL == m_lpValues)){
        /// 数组空间不够.
        return false;
    }
    /// 将 v 放到下标为 m_iDataCnt 的位置,并且 m_iDataCnt 加 1
    m_lpValues[m_iDataCnt] = v;
    ++m_iDataCnt;
    return true;
}
int CArrayStack::pop(int* lpError)
{
    if(NULL != lpError){
        *lpError = -1;
    }
    if((m_iDataCnt == 0) || (NULL == m_lpValues)){
        /// 栈为空
        return 0;
    }
    /// 返回下标为 m_iDataCnt-1的数组元素,并栈中元素个数 m_iDataCnt减1
    int ret = m_lpValues[m_iDataCnt-1];
    --m_iDataCnt;
    if(NULL != lpError){
        *lpError = 0;
    }
    return ret;
}
bool CArrayStack::empty()
{
    return m_iDataCnt == 0;
}