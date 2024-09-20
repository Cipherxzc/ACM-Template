#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int mod;

struct SegmentTree {
    struct segment {
        LL val, tag;
    };

    int n;
    vector<segment> st;
    vector<int> a;

    SegmentTree(int n) {
        this->n = n;
        st.resize(n * 4);
        a.resize(n + 1);
    }

    inline void push_up(int p) {
        int lson = p << 1, rson = p << 1 | 1;
        st[p].val = (st[lson].val + st[rson].val) % mod;
    }

    inline void spread(int p, int l, int r) {
        if (!st[p].tag) {
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        st[lson].tag = (st[lson].tag + st[p].tag) % mod;
        st[rson].tag = (st[rson].tag + st[p].tag) % mod;
        st[lson].val = (st[lson].val + st[p].tag * (mid - l + 1) % mod) % mod;
        st[rson].val = (st[rson].val + st[p].tag * (r - mid) % mod) % mod;
        st[p].tag = 0;
    }

    void build(int p, int l, int r) {
        st[p].tag = 0;
        if (l == r) {
            st[p].val = a[l];
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        push_up(p);
    }

    void add(int p, int l, int r, int lx, int rx, LL x) {
        if (lx <= l && r <= rx) {
            st[p].val += x * (r - l + 1);
            st[p].tag += x;
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        spread(p, l, r);
        if (lx <= mid) {
            add(lson, l, mid, lx, rx, x);
        }
        if (mid < rx) {
            add(rson, mid + 1, r, lx, rx, x);
        }
        push_up(p);
    }

    LL query(int p, int l, int r, int lx, int rx) {
        if (lx <= l && r <= rx) {
            return st[p].val;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        LL res = 0;
        spread(p, l, r);
        if (lx <= mid) {
            res += query(lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(rson, mid + 1, r, lx, rx);
        }
        return res % mod;
    }

    void build() { build(1, 1, n); }

    void add(int lx, int rx, LL x) { add(1, 1, n, lx, rx, x); }

    LL query(int lx, int rx) { return query(1, 1, n, lx, rx); }
};

const int N = 1e5 + 5;
int n, m, root, a[N], head[N], to[N * 2], nxt[N * 2], tot;
int fa[N], dep[N], siz[N], son[N], dfn[N], top[N];

inline void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int p) {
    siz[p] = 1;
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa[p]) {
            continue;
        }
        fa[q] = p;
        dep[q] = dep[p] + 1;
        dfs1(q);
        if (siz[q] > siz[son[p]]) {
            son[p] = q;
        }
        siz[p] += siz[q];
    }
}

void dfs2(int p, int tp) {
    top[p] = tp;
    dfn[p] = ++tot;
    if (son[p]) {
        dfs2(son[p], tp);
    }
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa[p] || q == son[p]) {
            continue;
        }
        dfs2(q, q);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> root >> mod;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs1(root);
    tot = 0;
    dfs2(root, root);

    SegmentTree st(n);
    for (int i = 1; i <= n; i++) {
        st.a[dfn[i]] = a[i] % mod;
    }
    st.build();

    int op, x, y, z;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) {
                    swap(x, y);
                }
                st.add(dfn[top[x]], dfn[x], z);
                x = fa[top[x]];
            }
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            st.add(dfn[y], dfn[x], z);
        } else if (op == 2) {
            LL ans = 0;
            cin >> x >> y;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) {
                    swap(x, y);
                }
                ans = (ans + st.query(dfn[top[x]], dfn[x])) % mod;
                x = fa[top[x]];
            }
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            ans = (ans + st.query(dfn[y], dfn[x])) % mod;
            cout << ans << endl;
        } else if (op == 3) {
            cin >> x >> z;
            st.add(dfn[x], dfn[x] + siz[x] - 1, z);
        } else {
            cin >> x;
            cout << st.query(dfn[x], dfn[x] + siz[x] - 1) << endl;
        }
    }

    return 0;
}