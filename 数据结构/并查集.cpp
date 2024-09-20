#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct DSU {
    int n;
    vector<int> fa;

    DSU(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        fa.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }

    inline int get(int p) {
        while (p != fa[p]) {
            p = fa[p] = fa[fa[p]];
        }
        return p;
    }

    inline void merge(int u, int v) { fa[get(u)] = get(v); }
};

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;

    DSU dsu(n);
    while (m--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1) {
            dsu.merge(u, v);
        } else {
            if (dsu.get(u) == dsu.get(v)) {
                cout << "Y" << endl;
            } else {
                cout << "N" << endl;
            }
        }
    }

    return 0;
}