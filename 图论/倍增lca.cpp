#include <bits/stdc++.h>
using namespace std;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 5e5 + 5;
int n, q, root, dep[N];
vector<int> e[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

namespace LCA {
    int fa[20][N];

    void dfs(int p) {
        for (int q : e[p]) {
            if (q == fa[0][p]) {
                continue;
            }
            dep[q] = dep[p] + 1;
            fa[0][q] = p;
            dfs(q);
        }
    }

    void init() {
        dfs(root);

        for (int j = 1; j <= lg(n - 1); j++) {
            for (int i = 1; i <= n; i++) {
                fa[j][i] = fa[j - 1][fa[j - 1][i]];
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        while (dep[u] - dep[v]) {
            u = fa[lg(dep[u] - dep[v])][u];
        }
        if (u == v) {
            return u;
        }
        for (int i = lg(dep[u]); i >= 0; i--) {
            if (fa[i][u] != fa[i][v]) {
                u = fa[i][u];
                v = fa[i][v];
            }
        }
        return fa[0][u];
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