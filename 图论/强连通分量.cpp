#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;

namespace Tarjan {  // 强连通分量
    int n, dfn[N], low[N], tot, id[N], num;
    bool ins[N];
    stack<int> st;
    vector<int> e[N], point[N];

    inline void add(int u, int v) { e[u].emplace_back(v); }

    void init(int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) {
            dfn[i] = 0;
            ins[i] = false;
            e[i].clear();
        }
        for (int i = 1; i <= num; i++) {
            point[i].clear();
        }
        tot = num = 0;
    }

    void tarjan(int p) {
        low[p] = dfn[p] = ++tot;
        st.push(p);
        ins[p] = true;
        for (int q : e[p]) {
            if (!dfn[q]) {
                tarjan(q);
                low[p] = min(low[p], low[q]);
            } else if (ins[q]) {
                low[p] = min(low[p], low[q]);
            }
        }

        if (dfn[p] == low[p]) {
            num++;
            int q = 0;
            while (q != p) {
                q = st.top();
                st.pop();
                ins[q] = false;
                id[q] = num;
                point[num].emplace_back(q);
            }
        }
    }

    void work() {  // tarjan缩点的结果符合拓扑序
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
    }
}  // namespace Tarjan
using Tarjan::num, Tarjan::point, Tarjan::e, Tarjan::id;

int n, m, a[N], f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    Tarjan::init(n);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        Tarjan::add(u, v);
    }

    Tarjan::work();

    int ans = 0;
    for (int i = 1; i <= num; i++) {
        int val = 0;
        for (int p : point[i]) {
            val += a[p];
            for (int q : e[p]) {
                f[i] = max(f[i], f[id[q]]);
            }
        }
        f[i] += val;
        ans = max(ans, f[i]);
    }

    cout << ans << endl;

    return 0;
}