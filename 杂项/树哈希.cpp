#include <bits/stdc++.h>
using namespace std;
using ULL = unsigned long long;

const int N = 1000005;
const ULL base = std::chrono::steady_clock::now().time_since_epoch().count();
int n, head[N], to[N * 2], nxt[N * 2], tot;
ULL th[N];
set<ULL> tree;

inline void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

inline ULL shift(ULL x) {
    x ^= base;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= base;
    return x;
}

void dfs(int p, int fa) {
    th[p] = 1;
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa) {
            continue;
        }
        dfs(q, p);
        th[p] += shift(th[q]);
    }
    tree.insert(th[p]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs(1, 0);
    cout << tree.size() << endl;

    return 0;
}