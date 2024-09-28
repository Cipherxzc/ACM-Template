#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using poly = vector<LL>;

const int mod = 998244353;

void FWTor(poly &arr, int n, int type) {
    int bit = 0;
    while ((1 << bit) <= n) {
        bit++;
    }
    n = 1 << bit;
    arr.resize(n);

    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i += l << 1) {
            for (int j = i; j < (i ^ l); j++) {
                arr[j ^ l] = (arr[j ^ l] + arr[j] * type + mod) % mod;
            }
        }
    }
}

void FWTand(poly &arr, int n, int type) {
    int bit = 0;
    while ((1 << bit) <= n) {
        bit++;
    }
    n = 1 << bit;
    arr.resize(n);

    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i += l << 1) {
            for (int j = i; j < (i ^ l); j++) {
                arr[j] = (arr[j] + arr[j ^ l] * type + mod) % mod;
            }
        }
    }
}

void FWTxor(poly &arr, int n, int type) {  // type 为 1 或 (mod + 1) >> 2
    int bit = 0;
    while ((1 << bit) <= n) {
        bit++;
    }
    n = 1 << bit;
    arr.resize(n);

    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i += l << 1) {
            for (int j = i; j < (i ^ l); j++) {
                LL x = arr[j], y = arr[j ^ l];
                arr[j] = (x + y) % mod;
                arr[j ^ l] = (x - y + mod) % mod;
                arr[j] = arr[j] * type % mod;
                arr[j ^ l] = arr[j ^ l] * type % mod;
            }
        }
    }
}

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    n = 1 << n;
    poly a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    FWTor(a, n - 1, 1);
    FWTor(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i] % mod;
    }
    FWTor(a, n - 1, -1);
    FWTor(b, n - 1, -1);
    FWTor(c, n - 1, -1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;

    FWTand(a, n - 1, 1);
    FWTand(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i] % mod;
    }
    FWTand(a, n - 1, -1);
    FWTand(b, n - 1, -1);
    FWTand(c, n - 1, -1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;

    FWTxor(a, n - 1, 1);
    FWTxor(b, n - 1, 1);
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * b[i] % mod;
    }
    FWTxor(a, n - 1, (mod + 1) >> 1);
    FWTxor(b, n - 1, (mod + 1) >> 1);
    FWTxor(c, n - 1, (mod + 1) >> 1);
    for (int i = 0; i < n; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;

    return 0;
}
