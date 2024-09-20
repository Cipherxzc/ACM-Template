#include <bits/stdc++.h>
using namespace std;
using LL = long long;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

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

    void build() {
        for (int i = 1; i <= bit; i++) {
            int gg = 1 << (i - 1);
            for (int j = 1; j + (gg << 1) - 1 <= n; j++) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + gg]);
            }
        }
    }

    inline int query(int l, int r) {
        int gg = lg(r - l + 1);
        return max(st[gg][l], st[gg][r - (1 << gg) + 1]);
    }
};

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    ST st(n);
    for (int i = 1; i <= n; i++) {
        cin >> st.st[0][i];
    }
    st.build();

    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << st.query(l, r) << endl;
    }

    return 0;
}