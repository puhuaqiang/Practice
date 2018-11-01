#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// 简单的二分查找
int bsearch1(int* s, int n, int v);
int bsearch1Recursive(int* s, int n, int v);

// 变体一：查找第一个值等于给定值的元素
int bsearch2(int* s, int n, int v);
// 变体二：查找最后一个值等于给定值的元素
int bsearch3(int* s, int n, int v);
// 变体三：查找第一个大于等于给定值的元素
int bsearch4(int* s, int n, int v);
// 变体四：查找最后一个小于等于给定值的元素
int bsearch5(int* s, int n, int v);

unsigned int ipToLong(std::string strIp);
std::string longToIP(unsigned int nIP);
struct ips{
    char s[32];//开始Ip
    char e[32];//结束ip
    char n[32];//所属地
};
struct sort_ip{
    int idx;//数组索引
    unsigned int sip;//开始ip
};
// 快速排序
void QuickSort(sort_ip* s, int n);
sort_ip bsearch_ip(sort_ip* s, int n, unsigned int sip);

int main()
{
    int s[] = {1,2,3,4,5,6,7,8};
    {
        int i = bsearch1(s, sizeof(s)/4, 7);
        std::cout<<i<<std::endl;
        i = bsearch1(s, sizeof(s)/4, 8);
        std::cout<<i<<std::endl;
    }
    
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch2(s, sizeof(s)/4, 8);
        std::cout<<"变体一：查找第一个值等于给定值的元素..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch3(s, sizeof(s)/4, 8);
        std::cout<<"变体二：查找最后一个值等于给定值的元素..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch4(s, sizeof(s)/4, 8);
        std::cout<<"变体三：查找第一个大于等于给定值的元素..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch5(s, sizeof(s)/4, 8);
        std::cout<<"变体四：查找最后一个小于等于给定值的元素..."<<i<<std::endl;
    }
    {

        ips _ips[] = {
            {"202.102.133.0", "202.102.133.255", "山东东营市"},
            {"202.102.135.0", "202.102.136.255",  "山东烟台" },
            {"202.102.156.34", "202.102.157.255", "山东青岛" },
            {"202.102.48.0", "202.102.48.255", "江苏宿迁" },
            {"202.102.49.15", "202.102.51.251", "江苏泰州" },
            {"202.102.56.0", "202.102.56.255", "江苏连云港"},
        };
        sort_ip _sort_ip[6];
        sort_ip tmp;
        for(int i=0; i<6; i++){
            tmp.idx = i;
            tmp.sip = ipToLong(_ips[i].s);
            _sort_ip[i] = tmp;
        }

        //快排
        QuickSort(_sort_ip, 6);
        /*for(int i=0; i<6; i++){
            std::cout<<_ips[_sort_ip[i].idx].s<<std::endl;
        }*/

        //二分查找
        int idx = bsearch_ip(_sort_ip, 6, ipToLong("202.102.135.135")).idx;
        std::cout<<_ips[idx].n<<std::endl;
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

/**
 * 变体一：查找第一个值等于给定值的元素
 * 数据是从小到大排列为前提
*/
int bsearch2(int* s, int n, int v)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid] > v){
            high = mid - 1;
        }else if(s[mid] < v){
            low = mid + 1;
        }else{
            /**
             * 如果 mid 不等于 0，但 s[mid] 的前一个元素 a[mid-1] 不等于 value，
             * 那也说明s[mid] 就是我们要找的第一个值等于给定值的元素。
            */
            if((0 == mid) || (s[mid-1] != v)){
                return mid;
            }else{
                high = mid - 1;
            }
        }
    }
    return -1;
}

/**
 * 变体二：查找最后一个值等于给定值的元素
 * 数据是从小到大排列为前提
*/
int bsearch3(int* s, int n, int v)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid] > v){
            high = mid - 1;
        }else if(s[mid] < v){
            low = mid + 1;
        }else{
            if((n-1 == mid) || (s[mid+1] != v)){
                return mid;
            }else{
                low = mid + 1;
            }
        }
    }
    return -1;
}

/**
 * 变体三：查找第一个大于等于给定值的元素
 * 数据是从小到大排列为前提
*/
int bsearch4(int* s, int n, int v)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid] >= v){
            /**
             * 如果 s[mid-1] 也大于等于要查找的值 v
             * 那说明要查找的元素在 [low, mid-1] 之间，
             * 所以，我们将 high 更新为 mid-1。
            */
            if((0 == mid) || (s[mid-1] < v)){
                return mid;
            }else{
                high = mid -1;
            }
        }else{
            low = mid + 1;
        }
    }
    return -1;
}

/**
 * 变体四：查找最后一个小于等于给定值的元素
 * 数据是从小到大排列为前提
*/
int bsearch5(int* s, int n, int v)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid] > v){
            high = mid - 1;
        }else{
            if((n-1 == mid) || (s[mid+1] > v)){
                return mid;
            }else{
                low = mid + 1;
            }
        }
    }
    return -1;
}

std::string longToIP(unsigned int nIP)
{
    std::string ip;
    char szTmp[32];
    sprintf(szTmp, "%d", (nIP >> 24));
    ip.append(szTmp);  
    ip.append(".");
    sprintf(szTmp, "%d", (nIP & 0x00FFFFFF) >> 16);
    ip.append(szTmp);
    ip.append(".");  
    sprintf(szTmp, "%d", (nIP & 0x0000FFFF) >> 8);
    ip.append(szTmp);  
    ip.append(".");  
    sprintf(szTmp, "%d", (nIP & 0x000000FF));
    ip.append(szTmp);  
    return ip;
}

unsigned int ipToLong(std::string strIp) 
{
    std::string ip1,ip2,ip3,ip4;
    int idx =0, fd=0;
    std::string tmp;
    int iCnt = 0;
    while(true){
        fd = strIp.find(".",idx);
        if(fd < 0){
            tmp = strIp.substr(idx,-1);
            break;
        }
        tmp = strIp.substr(idx, fd-idx);
        idx = fd+1;
        switch(iCnt++){
            case 0:ip1=tmp;break;
            case 1:ip2=tmp;break;
            case 2:ip3=tmp;break;
            case 3:ip4=tmp;break;
        }
    }
    if(iCnt == 3){
        ip4=tmp;
    }
    unsigned int ret = (atoi(ip1.data()) << 24) + (atoi(ip2.data()) << 16) + (atoi(ip3.data()) << 8) + (atoi(ip4.data()));
    return ret;  
}  

int Partition(sort_ip* s, int p, int r)
{
    sort_ip iPivot = s[r];
    int i= p;
    sort_ip tmp;
    /**
     * j 依次遍历一遍数组
     * i 记录数组中小于 pivot的元素
    */
    for(int j=p; j<r; j++){
        if(s[j].sip < iPivot.sip){
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i += 1;
        }
    }
    // 交换 pivot与 i下标的元素,使 pivot位于中间.
    tmp = s[i];
    s[i] = s[r];
    s[r] = tmp;
    return i;
}

// 快速排序递归函数
void QuickSortRecursive(sort_ip* s, int p, int r)
{
    // 递归终止条件
    if(p >= r){
        return;
    }
    // 取分区点
    int q = Partition(s, p, r);
    // 分治递归
    QuickSortRecursive(s, p, q-1);
    QuickSortRecursive(s, q+1, r);
}
void QuickSort(sort_ip* s, int n)
{
    QuickSortRecursive(s, 0, n-1);
}

sort_ip bsearch_ip(sort_ip* s, int n, unsigned int sip)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid].sip > sip){
            high = mid - 1;
        }else{
            if((n-1 == mid) || (s[mid+1].sip > sip)){
                return s[mid];
            }else{
                low = mid + 1;
            }
        }
    }
    return sort_ip();
}