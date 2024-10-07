#include <bits/stdc++.h>
using namespace std;
using db = double;

const db eps = 1e-6;

inline int sign(db x) { return x < -eps ? -1 : x > eps; }

namespace Gauss {
    int n, m;
    vector<vector<db>> a;

    void init(int n_, int m_) {
        n = n_, m = m_;
        a.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            a[i].resize(m + 2);
        }
    }

    inline void swapr(int x, int y) {
        for (int i = 1; i <= m + 1; i++) {
            swap(a[x][i], a[y][i]);
        }
    }

    inline void mul(int x, db k) {
        for (int i = 1; i <= m + 1; i++) {
            a[x][i] *= k;
        }
    }

    inline void add(int y, int x, db k) {
        for (int i = 1; i <= m + 1; i++) {
            a[y][i] += a[x][i] * k;
        }
    }

    int solve() {
        int p = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = p; j <= n; j++) {
                if (sign(a[j][i]) != 0) {
                    if (j != p) {
                        swapr(p, j);
                    }
                    break;
                }
            }
            if (sign(a[p][i]) == 0) {
                continue;
            }

            mul(i, 1 / a[p][i]);
            for (int j = 1; j <= n; j++) {
                if (j != p) {
                    add(j, p, -a[j][i]);
                }
            }
            p++;
        }

        for (int i = p; i <= n; i++) {
            if (sign(a[i][m + 1]) != 0) {
                return -1;  // No Solution
            }
        }
        if (p <= m) {
            return 0;  // Too Many Solutions
        } else {
            return 1;  // One Solution
        }
    }
}  // namespace Gauss

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    Gauss::init(n, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> Gauss::a[i][j];
        }
    }

    int flag = Gauss::solve();

    if (flag == 1) {
        cout << fixed << setprecision(2);
        for (int i = 1; i <= n; i++) {
            cout << 'x' << i << '=' << Gauss::a[i][n + 1] << endl;
        }
    } else {
        cout << flag << endl;
    }

    return 0;
}