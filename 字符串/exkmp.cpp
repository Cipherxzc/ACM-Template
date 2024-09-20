#include <iostream>
#include <string>
using namespace std;
using LL = long long;

const int N = 2e7 + 5;
int nxt[N], ext[N];  // nxt: 每个后缀最长匹配前缀

inline void getnxt(const string &s) {
    int n = s.length(), r = 0, x = 1;  // r: 当前最远匹配位置 x: 匹配至r的后缀
    nxt[0] = n;
    while (r + 1 < n && s[r + 1] == s[r]) {
        r++;
    }
    nxt[1] = r;
    for (int i = 2; i < n; i++) {
        r = x + nxt[x] - 1;
        int len = nxt[i - x];
        if (i + len <= r) {
            nxt[i] = len;
        } else {
            len = max(0, r - i + 1);
            while (i + len < n && s[i + len] == s[len]) {
                len++;
            }
            nxt[i] = len;
            x = i;
        }
    }
}

inline void exkmp(const string &s, const string &t) {
    int n = t.length(), m = s.length(), r = 0, x = 0;
    while (r < n && r < m && s[r] == t[r]) {
        r++;
    }
    ext[0] = r;
    for (int i = 1; i < n; i++) {
        r = x + ext[x] - 1;
        int len = nxt[i - x];
        if (i + len <= r) {
            ext[i] = len;
        } else {
            len = max(0, r - i + 1);
            while (i + len < n && len < m && t[i + len] == s[len]) {
                len++;
            }
            ext[i] = len;
            x = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string a, b;
    cin >> a >> b;

    getnxt(b);
    exkmp(b, a);

    LL ans = 0;
    for (int i = 0; i < b.length(); i++) {
        ans ^= (LL)(i + 1) * (nxt[i] + 1);
    }
    cout << ans << endl;

    ans = 0;
    for (int i = 0; i < a.length(); i++) {
        ans ^= (LL)(i + 1) * (ext[i] + 1);
    }
    cout << ans << endl;

    return 0;
}
