#include <iostream>
#include <cstring>
using namespace std;

// 简单的二分查找
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
     * low、high、mid 都是指数组下标
     * 其中 low 和 high 表示当前查找的区间范围，初始 low=0,high=n-1。
     * mid 表示 [low, high] 的中间位置。
    */
    int low = 0;
    int high = n - 1;
    
    /**
     * 注意是 low<=high，而不是 low<high
    */
    while (low <= high){
        /**
         * 如果 low 和 high 比较大的话，两者之和就有可能会溢出。
         * 改进的方法是将 mid 的计算方式写成 low+(high-low)/2。
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