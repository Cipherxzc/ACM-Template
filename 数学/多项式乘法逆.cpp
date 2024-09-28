#include <bits/stdc++.h>
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

inline LL inv(LL x) { return qp(x, mod - 2); }

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

void polyinv(const poly &arr, int n, poly &res) {
    res.clear();
    res.emplace_back(inv(arr[0]));
    poly tmp(2);
    for (int t = 2; (t >> 1) < n; t <<= 1) {  // 当前为mod x^(t/2) 下的逆元
        int t2 = t << 1;
        for (int i = 0; i < t; i++) {
            tmp[i] = arr[i];
        }

        ntt(tmp, t2 - 1, 1);
        ntt(res, t2 - 1, 1);
        for (int i = 0; i < t2; i++) {
            res[i] = res[i] * (2 - res[i] * tmp[i] % mod) % mod;
        }
        ntt(res, t2 - 1, -1);
        for (int i = t; i < t2; i++) {
            res[i] = 0;
        }
    }

    res.resize(n);
    for (LL &x : res) {
        if (x < 0) {
            x += mod;
        }
    }
}

int n, m;
poly a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    polyinv(a, n, b);
    for (int x : b) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}