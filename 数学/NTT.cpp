#include <iostream>
#include <vector>
using namespace std;
using LL = long long;
using poly = vector<LL>;

const int mod = 998244353, G = 3, Gi = 332748118;

inline LL qp(LL x, LL y) {
    LL res = 1;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

void ntt(poly &arr, int n, int type) {
    int bit = 0;
    while ((1 << bit) <= n) {
        bit++;
    }
    n = 1 << bit;
    arr.resize(n);

    vector<int> rev(n);
    for (int i = 1; i < n; i++) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        if (i < rev[i]) {
            swap(arr[i], arr[rev[i]]);
        }
    }

    for (int l = 1; l < n; l <<= 1) {
        LL gg = qp(type == 1 ? G : Gi, (mod - 1) / (l << 1));
        for (int i = 0; i < n; i += l * 2) {
            LL omega = 1;
            for (int j = i; j < i + l; j++) {
                LL x = arr[j], y = omega * arr[j + l] % mod;
                arr[j] = (x + y) % mod;
                arr[j + l] = (x - y + mod) % mod;
                omega = omega * gg % mod;
            }
        }
    }

    if (type == -1) {
        LL inv = qp(n, mod - 2);
        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * inv % mod;
        }
    }
}

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    poly a(n + 1), b(m + 1);
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> b[i];
    }

    ntt(a, n + m, 1);
    ntt(b, n + m, 1);

    poly c(a.size());
    for (int i = 0; i < c.size(); i++) {
        c[i] = a[i] * b[i] % mod;
    }
    ntt(c, n + m, -1);

    for (int i = 0; i <= n + m; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;

    return 0;
}