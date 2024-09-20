#include <bits/stdc++.h>
using namespace std;

inline int get(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    if ('A' <= ch && ch <= 'Z') {
        return ch - 'A' + 26;
    }
    return ch - '0' + 52;
}

struct Trie {
    struct node {
        int son[62], cnt;
    };

    vector<node> trie;
    int tot;

    Trie() { clear(); }

    void clear() {
        trie.clear();
        trie.emplace_back();
        tot = 0;
    }

    inline void insert(const string &str) {
        int p = 0;
        for (char ch : str) {
            int gg = get(ch);
            if (!trie[p].son[gg]) {
                trie[p].son[gg] = ++tot;
                trie.emplace_back();
            }
            p = trie[p].son[gg];
            trie[p].cnt++;
        }
    }

    inline int query(const string &str) {
        int p = 0;
        for (char ch : str) {
            int gg = get(ch);
            p = trie[p].son[gg];
            if (!p) {
                return 0;
            }
        }
        return trie[p].cnt;
    }
};

int T, n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T--) {
        string s;
        Trie trie;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> s;
            trie.insert(s);
        }

        while (q--) {
            cin >> s;
            cout << trie.query(s) << endl;
        }
    }

    return 0;
}