#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e5 + 5;
int n, m, a[N];

namespace Block {
    struct block {
        int l, r;
        LL sum, tag;

        inline void spread() {
            if (tag) {
                for (int i = l; i <= r; i++) {
                    a[i] += tag;
                }
                tag = 0;
            }
        }

        inline void add(LL x) {
            sum += x * (r - l + 1);
            tag += x;
        }

        inline void add(int lx, int rx, LL x) {
            sum += x * (rx - lx + 1);
            for (int i = lx; i <= rx; i++) {
                a[i] += x;
            }
        }

        inline LL query(int lx, int rx) {
            spread();
            LL res = 0;
            for (int i = lx; i <= rx; i++) {
                res += a[i];
            }
            return res;
        }
    };

    const int B = 316;
    int num, pos[N];
    block b[B + 5];

    void init() {
        num = (n - 1) / B + 1;
        for (int i = 1; i <= num; i++) {
            b[i].l = b[i - 1].r + 1;
            b[i].r = b[i].l + B - 1;
        }
        b[num].r = min(b[num].r, n);
        for (int i = 1; i <= num; i++) {
            b[i].sum = b[i].tag = 0;
            for (int j = b[i].l; j <= b[i].r; j++) {
                b[i].sum += a[j];
                pos[j] = i;
            }
        }
    }

    void add(int l, int r, LL x) {
        int lx = pos[l], rx = pos[r];
        if (lx == rx) {
            b[lx].add(l, r, x);
        } else {
            b[lx].add(l, b[lx].r, x);
            b[rx].add(b[rx].l, r, x);
            for (int i = lx + 1; i < rx; i++) {
                b[i].add(x);
            }
        }
    }

    LL query(int l, int r) {
        int lx = pos[l], rx = pos[r];
        LL res = 0;
        if (lx == rx) {
            res = b[lx].query(l, r);
        } else {
            res += b[lx].query(l, b[lx].r);
            res += b[rx].query(b[rx].l, r);
            for (int i = lx + 1; i < rx; i++) {
                res += b[i].sum;
            }
        }
        return res;
    }
}  // namespace Block

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Block::init();

    while (m--) {
        int op, l, r;
        LL x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            Block::add(l, r, x);
        } else {
            cout << Block::query(l, r) << endl;
        }
    }

    return 0;
}