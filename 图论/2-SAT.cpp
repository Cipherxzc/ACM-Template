#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;

// 点的范围为 [2, 2n+1]，其中 2x 对应 x取0，2x+1 对应 x取1
namespace TwoSat {
    int n, val[N], dfn[N], low[N], tot, num, id[N];
    bool ins[N];
    vector<int> e[N];
    stack<int> st;

    inline void add(int u, int v) { e[u].emplace_back(v); }
    inline void add(int u, int x, int v, int y) {
        u = u << 1 ^ x;
        v = v << 1 ^ y;
        add(u, v);
    }

    void init(int n_) {
        n = n_;
        for (int i = 2; i <= n * 2 + 1; i++) {
            dfn[i] = 0;
            ins[i] = false;
        }
        tot = num = 0;
    }

    void tarjan(int p) {  // 强连通分量
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
            }
        }
    }

    bool work() {  // tarjan缩点的结果符合拓扑序
        for (int i = 2; i <= n * 2 + 1; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }

        for (int i = 1; i <= n; i++) {
            int x0 = i << 1, x1 = x0 | 1;
            if (id[x0] == id[x1]) {
                return false;
            }
            val[i] = id[x1] < id[x0];  // id小的拓扑序靠后，为真
        }
        return true;
    }
}  // namespace TwoSat

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    TwoSat::init(n);
    for (int i = 1, u, v, x, y; i <= m; i++) {
        cin >> u >> x >> v >> y;
        TwoSat::add(u, x ^ 1, v, y);
        TwoSat::add(v, y ^ 1, u, x);
    }

    if (TwoSat::work()) {
        cout << "POSSIBLE" << endl;
        for (int i = 1; i <= n; i++) {
            cout << TwoSat::val[i] << ' ';
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}