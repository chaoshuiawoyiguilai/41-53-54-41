#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool paren(const string str) { //参考课件
    stack<char> S;
    for (int i = 0; i < str.size(); i++) {
        switch (str[i]) {
        case '(': case'[': case'{': S.push(str[i]); break;
        case ')': if ((S.empty()) || ('(' != S.top()))
            return false; S.pop(); break;
        case ']': if ((S.empty()) || ('[' != S.top()))
            return false; S.pop(); break;
        case '}': if ((S.empty()) || ('{' != S.top()))
            return false; S.pop(); break;
        default: break;
        }
    }
    return S.empty();
}

int main()
{
    string str;
    int n;
    cin >> n;
    int* p = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> str;
        p[i] = (paren(str));
    }
    for (int i = 0; i < n; i++) {
        cout << p[i] << endl;
    }
    delete []p;
}

