#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 5e5 + 5;
int n, q, root, tot, dfn[N];
vector<int> e[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

namespace LCA {
    struct ST {
        int n, bit;
        vector<vector<int>> st;

        ST(int n = 0) { init(n); }

        void init(int n) {
            this->n = n;
            bit = lg(n);
            st.resize(bit + 1);
            for (int i = 0; i <= bit; i++) {
                st[i].resize(n + 1);
            }
        }

        inline int get(int x, int y) { return (dfn[x] < dfn[y] ? x : y); }

        void build() {
            for (int i = 1; i <= bit; i++) {
                int gg = 1 << (i - 1);
                for (int j = 1; j + (gg << 1) - 1 <= n; j++) {
                    st[i][j] = get(st[i - 1][j], st[i - 1][j + gg]);
                }
            }
        }

        inline int query(int l, int r) {
            int gg = lg(r - l + 1);
            return get(st[gg][l], st[gg][r - (1 << gg) + 1]);
        }
    } st;

    void dfs(int p, int fa) {
        dfn[p] = ++tot;
        st.st[0][dfn[p]] = fa;
        for (int q : e[p]) {
            if (q != fa) {
                dfs(q, p);
            }
        }
    }

    void init() {
        tot = 0;
        st.init(n);
        dfs(root, 0);
        st.build();
    }

    int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        if (dfn[u] > dfn[v]) {
            swap(u, v);
        }
        return st.query(dfn[u] + 1, dfn[v]);
    }
}  // namespace LCA

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q >> root;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
    }

    LCA::init();

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << LCA::lca(u, v) << endl;
    }

    return 0;
}