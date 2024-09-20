#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    struct line {
        double k = 0, b = 0;

        double calc(int x) { return k * x + b; }
    };

    struct segment {
        line val;
        int lson = 0, rson = 0;
    };

    const int MAXN = 5e6 + 5;
    const double eps = 1e-12;
    vector<segment> st;
    int lim, root, tot;

    SegmentTree(int n) {
        st.resize(MAXN);
        lim = n;
        tot = root = 0;
    }

    void insert(int &p, int l, int r, int lx, int rx, line x) {
        if (!p) {
            p = ++tot;
        }
        int mid = (l + r) >> 1;
        if (lx <= l && r <= rx) {
            if (x.calc(mid) - st[p].val.calc(mid) > eps) {
                swap(x, st[p].val);
            }
            if (x.calc(l) - st[p].val.calc(l) > eps || x.calc(r) - st[p].val.calc(r) > eps) {
                if (x.k > st[p].val.k) {
                    insert(st[p].rson, mid + 1, r, lx, rx, x);
                } else {
                    insert(st[p].lson, l, mid, lx, rx, x);
                }
            }
        } else {
            if (lx <= mid) {
                insert(st[p].lson, l, mid, lx, rx, x);
            }
            if (mid < rx) {
                insert(st[p].rson, mid + 1, r, lx, rx, x);
            }
        }
    }

    double query(int p, int l, int r, int x) {
        if (!p) {
            return 0;
        }
        if (l == r) {
            return st[p].val.calc(x);
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return max(st[p].val.calc(x), query(st[p].lson, l, mid, x));
        } else {
            return max(st[p].val.calc(x), query(st[p].rson, mid + 1, r, x));
        }
    }

    void insert(int lx, int rx, line x) { insert(root, 1, lim, lx, rx, x); }

    double query(int x) { return query(root, 1, lim, x); }
};

int n = 50000, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    SegmentTree st(n);

    cin >> m;
    while (m--) {
        string op;
        int x;
        double k, b;
        cin >> op;
        if (op[0] == 'Q') {
            cin >> x;
            cout << floor(st.query(x) / 100) << endl;
        } else {
            cin >> b >> k;
            st.insert(1, n, {k, b - k});
        }
    }

    return 0;
}