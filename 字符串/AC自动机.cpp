#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct AC {
    struct node {
        int son[26], cnt, fail;
    };

    vector<node> trie;
    int tot;

    AC() { clear(); }

    void clear() {
        trie.clear();
        trie.emplace_back();
        tot = 0;
    }

    inline void insert(const string &str) {
        int p = 0;
        for (char ch : str) {
            int x = ch - 'a';
            if (!trie[p].son[x]) {
                trie[p].son[x] = ++tot;
                trie.emplace_back();
            }
            p = trie[p].son[x];
        }
        trie[p].cnt++;
    }

    inline void build() {
        queue<int> que;
        for (int p : trie[0].son) {
            if (p) {
                que.push(p);
                trie[p].fail = 0;
            }
        }

        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (int i = 0; i < 26; i++) {
                int &q = trie[p].son[i];
                if (q) {
                    trie[q].fail = trie[trie[p].fail].son[i];
                    que.push(q);
                } else {
                    q = trie[trie[p].fail].son[i];
                }
            }
        }
    }

    inline int query(const string &str) {
        int p = 0, res = 0;
        for (char ch : str) {
            p = trie[p].son[ch - 'a'];
            for (int i = p; i && trie[i].cnt != -1; i = trie[i].fail) {
                res += trie[i].cnt;
                trie[i].cnt = -1;
            }
        }
        return res;
    }
};

const int N = 1e6 + 5;
int n;
string s[N], t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    AC ac;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        ac.insert(s[i]);
    }

    ac.build();

    cin >> t;
    cout << ac.query(t) << endl;

    return 0;
}