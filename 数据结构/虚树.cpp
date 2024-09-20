#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define mp make_pair

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 2.5e5 + 5;
const LL INF = 1e18;
int n, m, dfn[N];
LL f[N], price[N];
vector<pair<int, int>> e[N];

inline void add(int u, int v, int w) {
    e[u].push_back(mp(v, w));
    e[v].push_back(mp(u, w));
}

namespace LCA {
    int root = 1, tot;

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
        for (auto [q, len] : e[p]) {
            if (q != fa) {
                price[q] = min(price[p], (LL)len);
                dfs(q, p);
            }
        }
    }

    void init() {
        tot = 0;
        st.init(n);
        price[root] = INF;
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

struct VirtualTree {
    vector<int> point, st;
    vector<vector<int>> e;
    int siz, tot, root;

    VirtualTree(int siz_ = 0) { init(siz_); }

    void init(int siz_) {
        tot = siz = siz_;
        e.clear();
        st.clear();
        e.resize(siz + 1);
        point.resize(siz + 1);
        point[0] = 0;
    }

    inline void add(int u, int v) { e[u].push_back(v); }

    inline void insert(int p) {
        if (st.size() == 1) {
            st.push_back(p);
            return;
        }

        int q = LCA::lca(point[st.back()], point[p]);
        while (dfn[q] <= dfn[point[st[st.size() - 2]]]) {
            add(st[st.size() - 2], st.back());
            st.pop_back();
        }
        if (q != point[st.back()]) {
            point.push_back(q);
            e.push_back({});
            tot++;
            add(tot, st.back());
            st.back() = tot;
        }
        st.push_back(p);
    }

    void build() {
        auto cmp = [](int a, int b) { return dfn[a] < dfn[b]; };
        sort(point.begin() + 1, point.end(), cmp);

        st.push_back(0);
        for (int i = 1; i <= siz; i++) {
            insert(i);
        }
        for (int i = 1; i < st.size() - 1; i++) {
            add(st[i], st[i + 1]);
        }
        root = st[1];
    }

    LL solve(int p) {
        if (p <= siz) {
            return price[point[p]];
        }
        LL res = 0;
        for (int q : e[p]) {
            res += solve(q);
        }
        return min(res, price[point[p]]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }

    LCA::init();

    cin >> m;
    while (m--) {
        int cnt;
        cin >> cnt;
        VirtualTree vt(cnt);
        for (int i = 1; i <= cnt; i++) {
            cin >> vt.point[i];
        }
        vt.build();

        cout << vt.solve(vt.root) << endl;
    }

    return 0;
}