#include <iostream>
#include <string>
using namespace std;

// ð������
void BubbleSort(int* s, int n);
// ��������
void InsertionSort(int* s, int n);
// ѡ������
void SelectionSort(int* s, int n);
// �鲢����
void MergeSort(int* s, int n);
// ��������
void QuickSort(int* s, int n);
// ���K���Ԫ��
int QueryNumber(int* s, int n, int k);

int main()
{
    int s[] = {10,5,3,1,7,6,2,8};
    {
        // ð������
        BubbleSort(s,sizeof(s)/4);
        std::cout<<"ð������:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;
    }

    {
        // ��������
        InsertionSort(s,sizeof(s)/4);
        std::cout<<"��������:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }
    {
        // ѡ������
        SelectionSort(s,sizeof(s)/4);
        std::cout<<"ѡ������:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }
    {
        // �鲢����
        MergeSort(s,sizeof(s)/4);
        std::cout<<"�鲢����:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }  
    {
        // ��������
        QuickSort(s,sizeof(s)/4);
        std::cout<<"��������:";
        for(int i=0; i<sizeof(s)/4; i++){
            std::cout<<s[i]<<" ";
        }
        std::cout<<std::endl;        
    }   
    {
        // ���K���Ԫ��
        int v = QueryNumber(s,sizeof(s)/4,3);
        std::cout<<"���3���Ԫ��:"<<v<<std::endl;      
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
        // ��ǰ�˳�ð��ѭ���ı�־λ
        bool flag = false;
        // n-i-1 ������Ѿ��������
        for(int j=0; j<n-i-1; ++j){
            if(s[j] > s[j+1]){
                int tmp = s[j];
                s[j] = s[j+1];
                s[j+1] = tmp;
                flag = true;///��ʾ�����ݽ���
            }
        }
        if(!flag){
            break;//û�����ݽ�������ǰ�˳�
        }
    }
}
void InsertionSort(int* s, int n)
{
    if(n <= 1){
        return;
    }
    for(int i=1;i<n;++i){
        int v = s[i];
        //���Ҳ����λ��
        int j = i-1;
        /* 
         ��: 4 5 6 1 3 2
         i=3 ʱ s[i]=1 ��ʼ�������ƶ�.
         j=(i=3)-1 = 2;
         forѭ�������δ� 6 5 4,��������ƶ�һλ
         ��һ��.j=2, s[j]=6 > 1 ,��s[j]�ƶ��� j+1��λ��
         �ڶ���.j=1, s[j]=5 > 1 ,��s[j]�ƶ��� j+1��λ��
         �ڶ���.j=0, s[j]=4 > 1 ,��s[j]�ƶ��� j+1��λ��
        */
        for(; j >= 0; --j){
            if(s[j] > v){
                s[j+1] = s[j]; //�����ƶ�
            }else{
                break;
            }
        }
        s[j+1] = v;//��������
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
            i֮ǰΪ����������
            i֮��Ϊδ��������
        */
        int j=i;
        int idx = -1;
        int tmp = s[j];
        // δ�����������ҵ���С��Ԫ��
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

// �ϲ�
void Merge(int* s, int p, int q, int r)
{
    int i = p, j = q+1, k = 0;
    int* lpS = new int[r-p+1];

    /**
     * �������� s[p...r]
     * ǰ�벿�� s[p..q]  ��벿�� s[q+1...r]
    */
    while((i <= q) && (j <= r)){
        if(s[i] <= s[j]){
            lpS[k++] = s[i++];
        }else{
            lpS[k++] = s[j++];
        }
    }
    // �ж��ĸ�����������ʣ�������
    int iStart = i, iEnd = q;
    if(j <= r){
        iStart = j;
        iEnd = r;
    }
    //��ʣ������鿽������ʱ���� lpS
    while(iStart <= iEnd){
        lpS[k++] = s[iStart++];
    }
    //�� lpS �е����鿽���� s[p...r]
    for(i=0; i<k; i++){
        s[p+i] = lpS[i];
    }
}

// �ݹ���ú���
void MergeSortRecursive(int* s, int p, int r)
{
    // �ݹ���ֹ����
    if(p >= r){
        return;
    }
    // ȡ p �� r֮����м�λ�� q
    int q = (p + r) /2;
    // ���εݹ�
    MergeSortRecursive(s, p, q);
    MergeSortRecursive(s, q+1, r);
    // �ϲ�
    Merge(s, p, q, r);
}

// �鲢�����㷨, s �����飬n ��ʾ�����С
void MergeSort(int* s, int n)
{
    MergeSortRecursive(s, 0, n-1);
}

int Partition(int* s, int p, int r)
{
    int iPivot = s[r];
    int i= p, tmp=0;
    /**
     * j ���α���һ������
     * i ��¼������С�� pivot��Ԫ��
    */
    for(int j=p; j<r; j++){
        if(s[j] < iPivot){
            tmp = s[i];
            s[i] = s[j];
            s[j] = tmp;
            i += 1;
        }
    }
    // ���� pivot�� i�±��Ԫ��,ʹ pivotλ���м�.
    tmp = s[i];
    s[i] = s[r];
    s[r] = tmp;
    return i;
}

// ��������ݹ麯��
void QuickSortRecursive(int* s, int p, int r)
{
    // �ݹ���ֹ����
    if(p >= r){
        return;
    }
    // ȡ������
    int q = Partition(s, p, r);
    // ���εݹ�
    QuickSortRecursive(s, p, q-1);
    QuickSortRecursive(s, q+1, r);
}
void QuickSort(int* s, int n)
{
    QuickSortRecursive(s, 0, n-1);
}

int QueryNumberRecursive(int* s, int p, int r, int k)
{
    // �ݹ���ֹ����
    if(p >= r){
        return -1;
    }
    // ȡ������
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