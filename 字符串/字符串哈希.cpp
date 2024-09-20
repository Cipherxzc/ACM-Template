#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int base = 131, mod1 = 1e9 + 7, mod2 = 998244353;
int n;
string s;

inline LL hashs(const string &str) {
    LL res1 = 0, res2 = 0;
    for (char ch : str) {
        res1 = (res1 * base + ch) % mod1;
        res2 = (res2 * base + ch) % mod2;
    }
    return res1 * 1000000000 + res2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;

    set<LL> vis;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        vis.insert(hashs(s));
    }

    cout << vis.size();

    return 0;
}