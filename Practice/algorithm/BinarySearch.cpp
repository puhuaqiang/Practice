#include <cstring>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// �򵥵Ķ��ֲ���
int bsearch1(int* s, int n, int v);
int bsearch1Recursive(int* s, int n, int v);

// ����һ�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ��
int bsearch2(int* s, int n, int v);
// ��������������һ��ֵ���ڸ���ֵ��Ԫ��
int bsearch3(int* s, int n, int v);
// �����������ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
int bsearch4(int* s, int n, int v);
// �����ģ��������һ��С�ڵ��ڸ���ֵ��Ԫ��
int bsearch5(int* s, int n, int v);

unsigned int ipToLong(std::string strIp);
std::string longToIP(unsigned int nIP);
struct ips{
    char s[32];//��ʼIp
    char e[32];//����ip
    char n[32];//������
};
struct sort_ip{
    int idx;//��������
    unsigned int sip;//��ʼip
};
// ��������
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
        std::cout<<"����һ�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ��..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch3(s, sizeof(s)/4, 8);
        std::cout<<"��������������һ��ֵ���ڸ���ֵ��Ԫ��..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch4(s, sizeof(s)/4, 8);
        std::cout<<"�����������ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��..."<<i<<std::endl;
    }
    {
        int s[] = {1,3,4,5,6,8,8,8,11,18};
        int i = bsearch5(s, sizeof(s)/4, 8);
        std::cout<<"�����ģ��������һ��С�ڵ��ڸ���ֵ��Ԫ��..."<<i<<std::endl;
    }
    {

        ips _ips[] = {
            {"202.102.133.0", "202.102.133.255", "ɽ����Ӫ��"},
            {"202.102.135.0", "202.102.136.255",  "ɽ����̨" },
            {"202.102.156.34", "202.102.157.255", "ɽ���ൺ" },
            {"202.102.48.0", "202.102.48.255", "������Ǩ" },
            {"202.102.49.15", "202.102.51.251", "����̩��" },
            {"202.102.56.0", "202.102.56.255", "�������Ƹ�"},
        };
        sort_ip _sort_ip[6];
        sort_ip tmp;
        for(int i=0; i<6; i++){
            tmp.idx = i;
            tmp.sip = ipToLong(_ips[i].s);
            _sort_ip[i] = tmp;
        }

        //����
        QuickSort(_sort_ip, 6);
        /*for(int i=0; i<6; i++){
            std::cout<<_ips[_sort_ip[i].idx].s<<std::endl;
        }*/

        //���ֲ���
        int idx = bsearch_ip(_sort_ip, 6, ipToLong("202.102.135.135")).idx;
        std::cout<<_ips[idx].n<<std::endl;
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

/**
 * ����һ�����ҵ�һ��ֵ���ڸ���ֵ��Ԫ��
 * �����Ǵ�С��������Ϊǰ��
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
             * ��� mid ������ 0���� s[mid] ��ǰһ��Ԫ�� a[mid-1] ������ value��
             * ��Ҳ˵��s[mid] ��������Ҫ�ҵĵ�һ��ֵ���ڸ���ֵ��Ԫ�ء�
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
 * ��������������һ��ֵ���ڸ���ֵ��Ԫ��
 * �����Ǵ�С��������Ϊǰ��
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
 * �����������ҵ�һ�����ڵ��ڸ���ֵ��Ԫ��
 * �����Ǵ�С��������Ϊǰ��
*/
int bsearch4(int* s, int n, int v)
{
    int low =0, high = n-1;
    while(low <= high){
        int mid = low + ((high-low) >> 1);
        if(s[mid] >= v){
            /**
             * ��� s[mid-1] Ҳ���ڵ���Ҫ���ҵ�ֵ v
             * ��˵��Ҫ���ҵ�Ԫ���� [low, mid-1] ֮�䣬
             * ���ԣ����ǽ� high ����Ϊ mid-1��
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
 * �����ģ��������һ��С�ڵ��ڸ���ֵ��Ԫ��
 * �����Ǵ�С��������Ϊǰ��
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
     * j ���α���һ������
     * i ��¼������С�� pivot��Ԫ��
    */
    for(int j=p; j<r; j++){
        if(s[j].sip < iPivot.sip){
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
void QuickSortRecursive(sort_ip* s, int p, int r)
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