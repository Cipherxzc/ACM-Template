#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL gcd(LL x, LL y) {
    if (!y) {
        return x;
    }
    return gcd(y, x % y);
}

inline LL qp(LL x, LL y, LL mod) {
    LL res = 1;
    while (y) {
        if (y & 1) {
            res = (__int128)res * x % mod;
        }
        y >>= 1;
        x = (__int128)x * x % mod;
    }
    return res;
}

inline LL f(LL x, LL c, LL p) { return ((__int128)x * x + c) % p; }

const LL test[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

inline bool Miller_Rabin(LL p) {
    LL d = p - 1, bit = 0;
    while (!(d & 1)) {
        bit++;
        d >>= 1;
    }
    for (LL x : test) {
        if (p == x) {
            return true;
        }
        LL gg = qp(x, d, p);
        if (x % p == 0 || gg == 1 || gg == p - 1) {
            continue;
        }
        for (int i = 1; i < bit; i++) {
            gg = (__int128)gg * gg % p;
            if (gg == p - 1) {
                break;
            }
        }
        if (gg != p - 1) {
            return false;
        }
    }
    return true;
}

inline LL Pollard_Rho(LL x) {
    LL t = 0, c = rand() % (x - 1) + 1, s, val = 1;
    for (int goal = 1;; goal <<= 1, s = t, val = 1) {
        for (int step = 1; step <= goal; step++) {
            t = f(t, c, x);
            val = (__int128)val * abs(t - s) % x;
            if (!val) {
                return x;
            }
            if (step % 127 == 0) {
                LL d = gcd(val, x);
                if (d > 1) {
                    return d;
                }
            }
        }
        LL d = gcd(val, x);
        if (d > 1) {
            return d;
        }
    }
}

LL solve(LL x) {
    if (x == 1 || Miller_Rabin(x)) {
        return x;
    }
    LL y = x;
    while (y == x) {
        y = Pollard_Rho(x);
    }
    while (x % y == 0) {
        x /= y;
    }
    return max(solve(x), solve(y));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    srand((unsigned)time(0));

    int T;
    cin >> T;
    while (T--) {
        LL x, p;

        cin >> x;
        p = solve(x);

        if (p == x) {
            cout << "Prime" << endl;
        } else {
            cout << p << endl;
        }
    }

    return 0;
}