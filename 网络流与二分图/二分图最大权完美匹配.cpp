// KM算法，当且仅当图中存在完备匹配时可用（求完美匹配，但可通过添加虚边求非完美匹配）
// 复杂度 O(n^3)，优于费用流
// 判无解：添加虚边，边权为-INF
// 非完美匹配：添加虚边，边权为0

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e3 + 5;
const LL INF = 1e12;
int n, m, match[N], pre[N];  // pre: 右端点被谁最早到达
LL val[N], slack[N];         // slack: 顶标减少多少可以加入交错树
vector<pair<int, LL>> e[N];
bool vis[N];

inline void add(int u, int v, LL w) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
}

void update(int p) {
    while (p) {
        int tmp = match[pre[p]];
        match[p] = pre[p];
        match[pre[p]] = p;
        p = tmp;
    }
}

void bfs(int s) {
    for (int i = 1; i <= n; i++) {
        vis[i] = vis[n + i] = 0;
        slack[n + i] = INF;
    }
    queue<int> que;
    que.push(s);

    while (true) {
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = true;
            for (auto [q, len] : e[p]) {
                if (vis[q]) {
                    continue;
                }
                if (val[p] + val[q] - len < slack[q]) {
                    slack[q] = val[p] + val[q] - len;
                    pre[q] = p;  // 由于右端点q可能在后面由于顶标改变而进入交错树，记录遍历中的前驱pre用于更新match
                    if (!slack[q]) {  // 边可用
                        vis[q] = true;
                        if (!match[q]) {
                            update(q);
                            return;
                        } else {
                            que.push(match[q]);
                        }
                    }
                }
            }
        }

        LL delta = INF;
        for (int i = n + 1; i <= n * 2; i++) {
            if (!vis[i]) {
                delta = min(delta, slack[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (vis[i]) {
                val[i] -= delta;
            }
            if (vis[n + i]) {
                val[n + i] += delta;
            } else {  // 维护由于顶标val改变引起的slack值变化
                slack[n + i] -= delta;
            }
        }

        for (int i = n + 1; i <= n * 2; i++) {
            if (!vis[i] && !slack[i]) {
                vis[i] = true;
                if (!match[i]) {
                    update(i);
                    return;
                } else {
                    que.push(match[i]);
                }
            }
        }
    }
}

LL KM() {
    for (int i = 1; i <= n; i++) {
        val[i] = -INF;
        val[n + i] = 0;
        for (auto [j, len] : e[i]) {
            val[i] = max(val[i], len);
        }
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    LL res = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [j, len] : e[i]) {
            if (j == match[i]) {
                res += len;
                break;
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        v += n;
        add(u, v, w);
    }

    cout << KM() << endl;
    for (int i = n + 1; i <= n * 2; i++) {
        cout << match[i] << ' ';
    }
    cout << endl;

    return 0;
}