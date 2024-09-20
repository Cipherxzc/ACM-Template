#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct BIT {
    inline int lowbit(int x) { return x & (-x); }

    vector<LL> bit;
    int n;

    BIT(int n) { init(n); }

    void init(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    inline void add(int p, LL x) {
        while (p <= n) {
            bit[p] += x;
            p += lowbit(p);
        }
    }

    inline LL sum(int p) {
        LL res = 0;
        while (p) {
            res += bit[p];
            p -= lowbit(p);
        }
        return res;
    }

    inline LL query(int l, int r) { return sum(r) - sum(l - 1); }
};

const int N = 5e5 + 5;
int n, m, a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.add(i, a[i]);
    }

    int op, l, r, pos, x;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> pos >> x;
            bit.add(pos, x);
        } else {
            cin >> l >> r;
            cout << bit.query(l, r) << endl;
        }
    }

    return 0;
}