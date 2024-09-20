#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e3 + 5;
int n1, n2, m, match[N];
vector<int> e[N];
bool vis[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

bool dfs(int p) {
    for (int q : e[p]) {
        if (vis[q]) {
            continue;
        }
        vis[q] = true;
        if (!match[q] || dfs(match[q])) {
            match[p] = q;
            match[q] = p;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n1 >> n2 >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        v += n1;
        add(u, v);
    }

    int cnt = 0;
    for (int i = 1; i <= n1; i++) {
        for (int j = n1 + 1; j <= n1 + n2; j++) {
            vis[j] = false;
        }
        cnt += dfs(i);
    }

    cout << cnt << endl;

    return 0;
}