#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5e3 + 5;
const LL INF = 1e18;

namespace Flow {
    struct edge {
        int to, nxt;  // 剩余容量
        LL cost, flow;
        edge(int _to = 0, int _nxt = 0, LL _cost = 0, LL _flow = 0) : to(_to), nxt(_nxt), cost(_cost), flow(_flow) {}
    };

    int n, s, t, head[N], tot = 1;
    vector<edge> e;
    LL minf[N], dis[N], pre[N];
    bool inq[N];

    // clang-format off
    inline void add(int u, int v, LL w, LL f) {
        e.emplace_back(v, head[u], w, f); head[u] = ++tot;
        e.emplace_back(u, head[v], -w, 0); head[v] = ++tot;
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

    bool spfa() {
        for (int i = 1; i <= n; i++) {
            inq[i] = false;
            dis[i] = INF;
        }
        queue<int> que;
        que.push(s);
        inq[s] = true;
        dis[s] = 0;
        minf[s] = INF;

        while (!que.empty()) {
            int p = que.front();
            que.pop();
            inq[p] = false;
            for (int i = head[p]; i; i = e[i].nxt) {
                int q = e[i].to;
                if (!e[i].flow) {
                    continue;
                }
                if (dis[p] + e[i].cost < dis[q]) {
                    dis[q] = dis[p] + e[i].cost;
                    pre[q] = i;
                    minf[q] = min(minf[p], e[i].flow);
                    if (!inq[q]) {
                        que.push(q);
                        inq[q] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    pair<LL, LL> EK() {
        LL maxflow = 0, res = 0;

        auto update = [&maxflow, &res]() {
            LL f = minf[t];
            for (int p = t; p != s; p = e[pre[p] ^ 1].to) {
                int from = pre[p];
                e[from].flow -= f;
                e[from ^ 1].flow += f;
            }
            maxflow += f;
            res += dis[t] * f;
        };

        while (spfa()) {
            update();
        }

        return {maxflow, res};
    }
}  // namespace Flow

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    Flow::init(n, s, t);
    for (int i = 1, u, v, w, f; i <= m; i++) {
        cin >> u >> v >> f >> w;
        Flow::add(u, v, w, f);
    }

    auto [maxflow, res] = Flow::EK();

    cout << maxflow << ' ' << res << endl;

    return 0;
}