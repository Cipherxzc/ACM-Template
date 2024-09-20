#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct SegmentTree {
    struct segment {
        int lson, rson;
        LL val, tag;
    };

    const int MAXN = 5e5;
    int n, tot, root;
    vector<segment> st;

    SegmentTree(int siz = 0) { init(siz); }

    void init(int siz) {
        n = siz;
        root = tot = 0;
        st.resize(MAXN);
    }

    inline void push_up(int p) { st[p].val = st[st[p].lson].val + st[st[p].rson].val; }

    inline void spread(int p, int l, int r) {
        if (!st[p].tag) {
            return;
        }
        if (!st[p].lson) {
            st[p].lson = ++tot;
        }
        if (!st[p].rson) {
            st[p].rson = ++tot;
        }
        int mid = (l + r) >> 1;
        st[st[p].lson].tag += st[p].tag;
        st[st[p].lson].val += st[p].tag * (mid - l + 1);
        st[st[p].rson].tag += st[p].tag;
        st[st[p].rson].val += st[p].tag * (r - mid);
        st[p].tag = 0;
    }

    void add(int &p, int l, int r, int lx, int rx, LL x) {
        if (!p) {
            p = ++tot;
        }
        if (lx <= l && r <= rx) {
            st[p].val += x * (r - l + 1);
            st[p].tag += x;
            return;
        }
        int mid = (l + r) >> 1;
        spread(p, l, r);
        if (lx <= mid) {
            add(st[p].lson, l, mid, lx, rx, x);
        }
        if (mid < rx) {
            add(st[p].rson, mid + 1, r, lx, rx, x);
        }
        push_up(p);
    }

    LL query(int p, int l, int r, int lx, int rx) {
        if (!p) {
            return 0;
        }
        if (lx <= l && r <= rx) {
            return st[p].val;
        }
        int mid = (l + r) >> 1;
        LL res = 0;
        spread(p, l, r);
        if (lx <= mid) {
            res += query(st[p].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(st[p].rson, mid + 1, r, lx, rx);
        }
        return res;
    }

    void add(int lx, int rx, LL x) { add(root, 1, n, lx, rx, x); }

    LL query(int lx, int rx) { return query(root, 1, n, lx, rx); }
};

const int N = 1e5 + 5;
int n, m;
LL a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTree st(n);
    for (int i = 1; i <= n; i++) {
        st.add(i, i, a[i]);
    }

    while (m--) {
        int op, l, r;
        LL x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            st.add(l, r, x);
        } else {
            cout << st.query(l, r) << endl;
        }
    }

    return 0;
}
