#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 205, INF = 0x7fffffff;

namespace Flow {
    struct edge {
        int to, nxt, flow;  // 剩余容量
        edge(int _to = 0, int _nxt = 0, int _flow = 0) : to(_to), nxt(_nxt), flow(_flow) {}
    };

    int n, s, t, head[N], cur[N], tot = 1;
    vector<edge> e;
    int dep[N], num[N];

    // clang-format off
    inline void add(int u, int v, int f) {
        e.emplace_back(v, head[u], f); head[u] = ++tot;
        e.emplace_back(u, head[v], 0); head[v] = ++tot;
    }

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 1; i <= n; i++) {
            head[i] = 0;
        }
        tot = 1;
        e.resize(2);
    }
    // clang-format on

    void build() {
        for (int i = 1; i <= n; i++) {
            dep[i] = 0;
        }

        queue<int> que;
        que.push(t);
        dep[t] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            num[dep[p]]++;
            for (int i = head[p]; i; i = e[i].nxt) {
                int q = e[i].to;
                if (!dep[q]) {
                    dep[q] = dep[p] + 1;
                    que.push(q);
                }
            }
        }
    }

    int dinic(int p, int lim) {  // 可增广流量
        if (p == t) {
            return lim;
        }
        int used = 0;
        for (int i = cur[p]; i; i = e[i].nxt) {
            int q = e[i].to;
            if (e[i].flow && dep[q] == dep[p] - 1) {
                cur[p] = i;
                int f = dinic(q, min(lim - used, e[i].flow));
                if (f) {
                    e[i].flow -= f;
                    e[i ^ 1].flow += f;
                    used += f;
                    if (used == lim) {
                        return used;
                    }
                }
            }
        }

        if (--num[dep[p]] == 0) {
            dep[s] = n + 1;
        }
        num[++dep[p]]++;

        return used;  // 增广流量
    }

    LL work(int s, int t) {
        LL maxflow = 0;
        int f;
        build();
        while (dep[s] <= n) {
            for (int i = 1; i <= n; i++) {
                cur[i] = head[i];
            }
            maxflow += dinic(s, INF);
        }
        return maxflow;
    }
}  // namespace Flow

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    Flow::init(n, s, t);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        Flow::add(u, v, w);
    }

    cout << Flow::work(s, t) << endl;

    return 0;
}