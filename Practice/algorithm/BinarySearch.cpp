#include <iostream>
#include <cstring>
using namespace std;

// �򵥵Ķ��ֲ���
int bsearch1(int* s, int n, int v);
int bsearch1Recursive(int* s, int n, int v);

int main()
{
    int s[] = {1,2,3,4,5,6,7,8};
    {
        int i = bsearch1(s, sizeof(s)/4, 7);
        std::cout<<i<<std::endl;
        i = bsearch1(s, sizeof(s)/4, 8);
        std::cout<<i<<std::endl;
    }
    std::cin.ignore();
    return 0;
}

int bsearch1(int* s, int n, int v)
{
    /**
     * low��high��mid ����ָ�����±�
     * ���� low �� high ��ʾ��ǰ���ҵ����䷶Χ����ʼ low=0,high=n-1��
     * mid ��ʾ [low, high] ���м�λ�á�
    */
    int low = 0;
    int high = n - 1;
    
    /**
     * ע���� low<=high�������� low<high
    */
    while (low <= high){
        /**
         * ��� low �� high �Ƚϴ�Ļ�������֮�;��п��ܻ������
         * �Ľ��ķ����ǽ� mid �ļ��㷽ʽд�� low+(high-low)/2��
        */
        int mid = (low + high) / 2;
        if (s[mid] == v) {
            return mid;
        }else if (s[mid] < v) {
            low = mid + 1;
        }else {
            high = mid - 1;
        }
    }
    return -1;
}

int bsearch1RecursiveIter(int* s, int n, int l, int h, int v)
{
    if(l > h){
        return -1;
    }
    int mid = l + ((h-l) >> 1);
    if(s[mid] == v){
        return mid;
    }else if(s[mid] < v){
        bsearch1RecursiveIter(s, n, mid+1, h, v);
    }else{
        bsearch1RecursiveIter(s, n, l, mid-1, v);
    }
}

int bsearch1Recursive(int* s, int n, int v)
{
    return bsearch1RecursiveIter(s, n, 0, n-1, v);
}