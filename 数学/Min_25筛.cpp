#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// 积性函数f(p^c) = p^2c - p^c
// pk: 第k小的素数，特别地，我们定义p0 = 1
// lpf(n): n的最小质因数，特别地，我们定义lpf(1) = 1
// Fprime(n): sigma[2<=p<=n](f(p))
// F(k, n): 对 2<=i<=n 中，所有满足 lpf(i)>=pk 的i, 求sigma(f(i))
// G(k, n)[ci = c]: 对 1<=i<=n 中, 所有满足 lpf(i)>pk 或 i是质数 的i, 求 sigma(i^c);
const int N = 1e6, mod = 1e9 + 7, inv3 = 333333336;
int tot, id1[N], id2[N];  // id1和id2分别记录当用到的 num<=sqrt 与 num>sqrt 时，在G数组中的位置
LL n, Sqrn, num[N], g1[N], g2[N];  // num[i]: 第i个数的值，对应G函数中需要用到的n; gi[n]: 幂次为ci时的G(k, n)
vector<LL> prime, sp1, sp2;  // sp1: 质数前缀和; sp2: 质数前缀平方和
bool notp[N];

inline LL f(LL x) { return x * (x - 1) % mod; }

void Euler(int n) {
    prime.emplace_back(1);
    sp1.emplace_back(0);
    sp2.emplace_back(0);
    for (int i = 2; i <= n; i++) {
        if (!notp[i]) {
            prime.emplace_back(i);
            sp1.emplace_back((sp1.back() + i) % mod);
            sp2.emplace_back((sp2.back() + (LL)i * i) % mod);
        }
        for (int j = 1; j < prime.size() && prime[j] <= n / i; j++) {
            notp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

void Min_25() {
    for (LL i = 1; i <= n; i = n / num[tot] + 1) {  // 初始化num、id1、id2，并g1、g2赋边界值
        num[++tot] = n / i;
        LL v = num[tot] % mod;
        g2[tot] = v * (v + 1) / 2 % mod * (2 * v + 1) % mod * inv3 % mod - 1;
        g1[tot] = v * (v + 1) / 2 % mod - 1;
        if (num[tot] <= Sqrn) {
            id1[num[tot]] = tot;
        } else {
            id2[n / num[tot]] = tot;
        }
    }
    // G(k, n) = G(k-1, n) - [pk^2 <= n]pk^c * (G(k-1, n/pk) - G(k-1, p(k-1)))
    // 注意根据G定义，显然有 G(k-1, p(k-1)) = sigma(p^c), 即我们求出的sp
    for (int i = 1; i < prime.size(); i++) {
        for (int j = 1; j <= tot && prime[i] * prime[i] <= num[j]; j++) {
            LL k = num[j] / prime[i];
            k = (k <= Sqrn) ? id1[k] : id2[n / k];
            g1[j] -= prime[i] * (g1[k] - sp1[i - 1]) % mod;
            g2[j] -= prime[i] * prime[i] % mod * (g2[k] - sp2[i - 1]) % mod;
            g1[j] = (g1[j] % mod + mod) % mod;
            g2[j] = (g2[j] % mod + mod) % mod;
        }
    }
}

LL sumF(int k, LL x) {
    if (k < prime.size() && x < prime[k] || x <= 1) {
        return 0;
    }
    LL id = (x <= Sqrn) ? id1[x] : id2[n / x], res;
    // 注意到, 我们有Fprime[n] = g2[id] - g1[id], Fprime[p(k-1)] = sp2[k-1] - sp1[k-1]
    res = ((g2[id] - g1[id] - (sp2[k - 1] - sp1[k - 1])) % mod + mod) % mod;
    for (int i = k; i < prime.size() && prime[i] * prime[i] <= x; i++) {
        for (LL p = prime[i]; p <= x; p = p * prime[i]) {
            LL v = p % mod;
            res = (res + f(v) % mod * (sumF(i + 1, x / p) + (p != prime[i]))) % mod;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    Sqrn = sqrt(n);

    Euler(Sqrn);
    Min_25();

    cout << (sumF(1, n) + 1) % mod << endl;

    return 0;
}