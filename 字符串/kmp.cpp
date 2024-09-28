#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int fail[N];

inline void KMP(const string &str) {
    fail[0] = -1;
    for (int i = 1; i < str.length(); i++) {
        int p = fail[i - 1];
        while (p >= 0 && str[p + 1] != str[i]) {
            p = fail[p];
        }
        if (str[p + 1] == str[i]) {
            p++;
        }
        fail[i] = p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    KMP(s2);

    int cnt = 0, p = -1;
    for (int i = 0; i < s1.length(); i++) {
        while (p >= 0 && s1[i] != s2[p + 1]) {
            p = fail[p];
        }
        if (s2[p + 1] == s1[i]) {
            p++;
            if (p == s2.length() - 1) {
                cout << i - s2.length() + 2 << endl;
                p = fail[p];
            }
        }
    }

    for (int i = 0; i < s2.length(); i++) {
        cout << fail[i] + 1 << ' ';
    }

    return 0;
}