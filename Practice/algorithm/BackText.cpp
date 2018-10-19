#include <iostream>
#include <string>
using namespace std;
 
int main()
{
    string str;
    int flag = 1;
 
    while (cin >> str)
    {
        int l = str.length();
        for (int i = 0, j = l-1; i <= j; i++,j--)
        {
            if (str[i] != str[j])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        flag = true;
    }
    std::cin.ignore();
 
    return 0;
}