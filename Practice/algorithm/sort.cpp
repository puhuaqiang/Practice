#include <iostream>
#include <cstring>
using namespace std;

// 冒泡排序
void BubbleSort(int* s, int n);
// 插入排序
void InsertionSort(int* s, int n);
// 选择排序
void SelectionSort(int* s, int n);
// 归并排序
void MergeSort(int* s, int n);
// 快速排序
void QuickSort(int* s, int n);
// 求第K大的元素
int QueryNumber(int* s, int n, int k);
// 计数排序
void CountingSort(int* s, int n);
// 基数排序
void RadixSort(char s[][32], int n, int c);

int main()
{
    int s[] = {10,5,3,1,7,6,2,8};
    {
        // 冒泡排序
        BubbleSort(s,sizeof(s)/4);
        std::cout<<"冒泡排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;
    }

    {
        // 插入排序
        InsertionSort(s,sizeof(s)/4);
        std::cout<<"插入排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }
    {
        // 选择排序
        SelectionSort(s,sizeof(s)/4);
        std::cout<<"选择排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }
    {
        // 归并排序
        MergeSort(s,sizeof(s)/4);
        std::cout<<"归并排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }  
    {
        // 快速排序
        QuickSort(s,sizeof(s)/4);
        std::cout<<"快速排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }   
    {
        // 求第K大的元素
        int v = QueryNumber(s,sizeof(s)/4,3);
        std::cout<<"求第3大的元素:"<<v<<std::endl;      
    }  
    {
        // 计数排序
        CountingSort(s,sizeof(s)/4);
        std::cout<<"计数排序:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    } 
    {
        // 基数排序
        char str[16][32] = {
            "13412341234","13512341231",
            "13112341534","13712341234",
            "13412351231","13512341232",
            "13912341234","13812341234",
            "13412361232","13512341233",
            "13112341244","13912341234",
            "13412371234","13512341234",
            "13112341234","13913341234",
        };
        RadixSort(str,16, 11);
        std::cout<<"基数排序:"<<std::endl;
        for(int i=0; i<16; i++){
            std::cout<<str[i]<<std::endl;
        }
        std::cout<<std::endl;        
    } 
    std::cin.ignore();
 
    return 0;
}

void BubbleSort(int* s, int n)
{
    if(n <= 1){
        return;
    }
    for(int i=0; i<n; ++i){
        // 提前退出冒泡循环的标志位
        bool flag = false;
        // n-i-1 后面的已经排序好了
        for(int j=0; j<n-i-1; ++j){
            if(s[j] > s[j+1]){
                int tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
                flag = true;///表示有数据交换
            }
        }
        if(!flag){
            break;//没有数据交换，提前退出
        }
    }
}
void InsertionSort(int* s, int n)
{
    if(n <= 1){
        return;
    }
    /**
     * i 表示未排序区间
     * j 表示已排序区间
    */
    for(int i=1;i<n;++i){
        int v = s[i];
        //查找插入的位置
        int j = i-1;
        /* 
         如: 4 5 6 1 3 2
         i=3 时 s[i]=1 开始有数据移动.
         j=(i=3)-1 = 2;
         for循环会依次从 6 5 4,挨着向后移动一位
         第一次.j=2, s[j]=6 > 1 ,把s[j]移动到 j+1的位置
         第二次.j=1, s[j]=5 > 1 ,把s[j]移动到 j+1的位置
         第二次.j=0, s[j]=4 > 1 ,把s[j]移动到 j+1的位置
        */
        for(; j >= 0; --j){
            if(s[j] > v){
                s[j+1] = s[j]; //数据移动
            }else{
                break;
            }
        }
        s[j+1] = v;//插入数据
    }
}

void SelectionSort(int* s, int n)
{
    if(n <= 1){
        return;
    }
    for(int i=0;i<n;++i){
        int v = s[i];
        /*
            i之前为已排序区间
            i之后为未排序区间
        */
        int j=i;
        int idx = -1;
        int tmp = s[j];
        // 未排序区间中找到最小的元素
        for(; j <n; ++j){
            if(tmp > s[j]){
                tmp =s[j];
                idx = j;
            }
        }
        if(idx >= 0){
            s[i] = tmp;
            s[j] = v;
        }
    }
}

// 合并
void Merge(int* s, int p, int q, int r)
{
    int i = p, j = q+1, k = 0;
    int* lpS = new int[r-p+1];

    /**
     * 整个数组 s[p...r]
     * 前半部分 s[p..q]  后半部分 s[q+1...r]
    */
    while((i <= q) && (j <= r)){
        if(s[i] <= s[j]){
            lpS[k++] = s[i++];
        }else{
            lpS[k++] = s[j++];
        }
    }
    // 判断哪个字数组中有剩余的数据
    int iStart = i, iEnd = q;
    if(j <= r){
        iStart = j;
        iEnd = r;
    }
    //将剩余的数组拷贝到临时数组 lpS
    while(iStart <= iEnd){
        lpS[k++] = s[iStart++];
    }
    //将 lpS 中的数组拷贝回 s[p...r]
    for(i=0; i<k; i++){
        s[p+i] = lpS[i];
    }
}

// 递归调用函数
void MergeSortRecursive(int* s, int p, int r)
{
    // 递归终止条件
    if(p >= r){
        return;
    }
    // 取 p 到 r之间的中间位置 q
    int q = (p + r) /2;
    // 分治递归
    MergeSortRecursive(s, p, q);
    MergeSortRecursive(s, q+1, r);
    // 合并
    Merge(s, p, q, r);
}

// 归并排序算法, s 是数组，n 表示数组大小
void MergeSort(int* s, int n)
{
    MergeSortRecursive(s, 0, n-1);
}

int Partition(int* s, int p, int r)
{
    int iPivot = s[r];
    int i= p, tmp=0;
    /**
     * j 依次遍历一遍数组
     * i 记录数组中小于 pivot的元素
    */
    for(int j=p; j<r; j++){
        if(s[j] < iPivot){
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
void QuickSortRecursive(int* s, int p, int r)
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
void QuickSort(int* s, int n)
{
    QuickSortRecursive(s, 0, n-1);
}

int QueryNumberRecursive(int* s, int p, int r, int k)
{
    // 递归终止条件
    if(p >= r){
        return -1;
    }
    // 取分区点
    int q = Partition(s, p, r);
    if(k == q+1){
        return s[q];
    }else if(k > q+1){
        return QueryNumberRecursive(s, q+1, r, k);
    }else{
        return QueryNumberRecursive(s, p, q-1, k);
    }
    return -1;
}
int QueryNumber(int* s, int n, int k)
{
    return QueryNumberRecursive(s, 0, n-1,k);
}

void CountingSort(int* s, int n)
{
    if (n <= 1){
        return;
    }
    // 查找数组中数据的范围
    int iMax = s[0];
    for (int i = 1; i < n; ++i) {
        if (iMax < s[i]) {
            iMax = s[i];
        }
    }
    // 申请一个计数数组 c，下标大小 [0,max]
    int* lpC = new int[iMax + 1]; 
    for (int i = 0; i <= iMax; ++i) {
        lpC[i] = 0;
    }
    // 计算每个元素的个数，放入 c 中
    for (int i = 0; i < n; ++i) {
        lpC[s[i]]++;
    }

    // 依次累加
    for (int i = 1; i <= iMax; ++i) {
        lpC[i] = lpC[i-1] + lpC[i];
    }

    // 临时数组 r，存储排序之后的结果
    int* lpR = new int[n];
    // 计算排序的关键步骤，有点难理解
    for (int i = n - 1; i >= 0; --i) {
        int index = lpC[s[i]]-1;
        lpR[index] = s[i];
        lpC[s[i]]--;
    }
    // 将结果拷贝给 a 数组
    for (int i = 0; i < n; ++i) {
        s[i] = lpR[i];
    }
}

void RadixSort(char s[][32], int n, int c)
{
    for(int k=c-1; k>= 0; --k){
        char tmp[32];
        for(int i=1;i<n;++i){
            char v = s[i][k];
            memcpy(tmp, s[i],strlen(s[i]));
            tmp[strlen(s[i])] = '\0';
            //查找插入的位置
            int j = i-1;
            for(; j >= 0; --j){
                if(s[j][k] > v){
                    //数据移动
                    memcpy(s[j+1],s[j],strlen(s[j])); 
                }else{
                    break;
                }
            }
            //数据移动
            memcpy(s[j+1],tmp,strlen(tmp)); 
        }
    }
}