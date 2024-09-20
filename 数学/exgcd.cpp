#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    LL gcd = exgcd(b, a % b, x, y), c = x;
    x = y;
    y = c - (a / b) * y;
    return gcd;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        LL a, b, c, gcd, x, y;
        cin >> a >> b >> c;
        gcd = exgcd(a, b, x, y);
        if (c % gcd) {
            cout << -1 << endl;
            continue;
        }
        x *= c / gcd;
        y *= c / gcd;
        LL p = b / gcd, q = a / gcd;
        if (x < 0) {
            LL k = (p - x) / p;
            x += k * p;
            y -= k * q;
        } else {
            LL k = (x - 1) / p;
            x -= k * p;
            y += k * q;
        }
        if (y > 0) {
            LL k = (y - 1) / q;
            cout << k + 1 << ' ' << x << ' ' << y - k * q << ' ' << x + k * p << ' ' << y << endl;
        } else {
            cout << x << ' ' << y + (q - y) / q * q << endl;
        }
    }

    return 0;
}