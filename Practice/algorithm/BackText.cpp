#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

/// 判断是否是回文字符串
bool Palindrome(const char*);

int main()
{
    string str;
    while (cin >> str)
    {
        if (Palindrome(str.data()))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    std::cin.ignore();
    return 0;
}

bool Palindrome(const char* lpStr)
{
    if(NULL == lpStr){
        return false;
    }
    bool flag = true;
    int l = strlen(lpStr);
    if(l == 0){
        return false;
    }
    for (int i = 0, j = l-1; i <= j; i++,j--)
    {
        if (lpStr[i] != lpStr[j])
        {
            flag = false;
            break;
        }
    }
    return flag;
}