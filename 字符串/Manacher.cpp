#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void manacher(const string &s, vector<int> &l) {  // 回文半径存至l
    vector<char> a;
    a.resize(s.size() * 2 + 3);
    l.resize(s.size() * 2 + 3);
    a.front() = 1;
    a.back() = 2;  // 边界
    for (int i = 0; i < s.size(); i++) {
        a[i * 2 + 1] = 0;
        a[i * 2 + 2] = s[i];
    }
    a[a.size() - 2] = 0;

    int mid = 0, r = 0;
    for (int i = 1; i < a.size() - 1; i++) {
        l[i] = (i >= r) ? 1 : min(r - i, l[(mid << 1) - i]);
        while (a[i + l[i]] == a[i - l[i]]) {
            l[i]++;
        }
        if (i + l[i] > r) {
            r = i + l[i];
            mid = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> s;

    vector<int> l;
    manacher(s, l);

    int ans = 0;
    for (int i = 1; i < l.size() - 1; i++) {
        ans = max(ans, l[i]);
    }
    cout << ans - 1 << endl;

    return 0;
}