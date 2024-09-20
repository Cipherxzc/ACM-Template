#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct SegmentTree {
    struct segment {
        int lson = 0, rson = 0;
        LL val = 0;
    };

    const int MAXN = 4e6;
    int n, tot, num;
    stack<int> bin;
    vector<int> root;
    vector<segment> st;

    SegmentTree(int n, int m) {
        this->n = n;
        tot = 0;
        num = 1;
        root.resize(m + 1);
        st.resize(MAXN);
    }

    inline int New() {
        if (bin.empty()) {
            return ++tot;
        } else {
            int tmp = bin.top();
            bin.pop();
            return tmp;
        }
    }

    inline void del(int &p) {
        bin.push(p);
        st[p].lson = st[p].rson = st[p].val = 0;
        p = 0;
    }

    inline void push_up(int p) { st[p].val = st[st[p].lson].val + st[st[p].rson].val; }

    void add(int &p, int l, int r, int tar, LL x) {
        if (!p) {
            p = New();
        }
        if (l == r) {
            st[p].val += x;
            return;
        }
        int mid = (l + r) >> 1;
        if (tar <= mid) {
            add(st[p].lson, l, mid, tar, x);
        } else {
            add(st[p].rson, mid + 1, r, tar, x);
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
        if (lx <= mid) {
            res += query(st[p].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(st[p].rson, mid + 1, r, lx, rx);
        }
        return res;
    }

    int kth(int p, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        if (st[st[p].lson].val >= k) {
            return kth(st[p].lson, l, mid, k);
        } else {
            return kth(st[p].rson, mid + 1, r, k - st[st[p].lson].val);
        }
    }

    void merge(int &p, int &q) {
        if (!p || !q) {
            p += q;
            q = 0;
            return;
        }
        st[p].val += st[q].val;
        merge(st[p].lson, st[q].lson);
        merge(st[p].rson, st[q].rson);
        del(q);
    }

    void split(int &p, int &q, int l, int r, int lx, int rx) {
        if (!p) {
            return;
        }
        if (!q) {
            q = New();
        }
        if (lx <= l && r <= rx) {
            q = p;
            p = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (lx <= mid) {
            split(st[p].lson, st[q].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            split(st[p].rson, st[q].rson, mid + 1, r, lx, rx);
        }
        push_up(p);
        push_up(q);
    }

    void add(int p, int tar, LL x) { add(root[p], 1, n, tar, x); }

    LL query(int p, int lx, int rx) { return query(root[p], 1, n, lx, rx); }

    int kth(int p, int k) {
        if (st[root[p]].val < k) {
            return -1;
        } else {
            return kth(root[p], 1, n, k);
        }
    }

    void split(int p, int lx, int rx) { split(root[p], root[++num], 1, n, lx, rx); }
};

const int N = 2e5 + 5;
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    SegmentTree st(n, m);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        st.add(1, i, x);
    }

    int opt, p, q, l, r, k, x;
    while (m--) {
        cin >> opt;
        if (opt == 0) {
            cin >> p >> l >> r;
            st.split(p, l, r);
        } else if (opt == 1) {
            cin >> p >> q;
            st.merge(st.root[p], st.root[q]);
        } else if (opt == 2) {
            cin >> p >> k >> x;
            st.add(p, x, k);
        } else if (opt == 3) {
            cin >> p >> l >> r;
            cout << st.query(p, l, r) << endl;
        } else if (opt == 4) {
            cin >> p >> k;
            cout << st.kth(p, k) << endl;
        }
    }

    return 0;
}