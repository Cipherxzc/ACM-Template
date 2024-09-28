#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int len[N], cnt[N], fail[N], trie[N][30];

inline void PAM(const string &s) {
    auto getfail = [&s](int p, int i) {
        while (i == len[p] || s[i - len[p] - 1] != s[i]) {
            p = fail[p];
        }
        return p;
    };

    fail[0] = 1;
    len[1] = -1;
    int tot = 1, p = 0;
    for (int i = 0; i < s.length(); i++) {
        p = getfail(p, i);
        if (!trie[p][s[i] - 'a']) {
            fail[++tot] = trie[getfail(fail[p], i)][s[i] - 'a'];
            trie[p][s[i] - 'a'] = tot;
            len[tot] = len[p] + 2;
            cnt[tot] = cnt[fail[tot]] + 1;
        }
        p = trie[p][s[i] - 'a'];

        cout << cnt[p] << ' ';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> s;

    PAM(s);

    return 0;
}