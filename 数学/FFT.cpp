#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using db = double;
using poly = vector<complex<db>>;

const db pi = acos(-1);

void fft(poly &arr, int n, int type) {
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

    for (int l = 1; l < (1 << bit); l <<= 1) {
        complex<db> gg(cos(pi / l), type * sin(pi / l));
        for (int i = 0; i < (1 << bit); i += l * 2) {
            complex<db> omega(1, 0);
            for (int j = i; j < i + l; j++) {
                complex<db> x = arr[j], y = omega * arr[j + l];
                arr[j] = x + y;
                arr[j + l] = x - y;
                omega *= gg;
            }
        }
    }

    if (type == -1) {
        for (int i = 0; i < n; i++) {
            arr[i] = (LL)(arr[i].real() / n + 0.5);
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

    fft(a, n + m, 1);
    fft(b, n + m, 1);

    poly c(a.size());
    for (int i = 0; i < c.size(); i++) {
        c[i] = a[i] * b[i];
    }
    fft(c, n + m, -1);

    for (int i = 0; i <= n + m; i++) {
        cout << (int)c[i].real() << ' ';
    }
    cout << endl;

    return 0;
}
