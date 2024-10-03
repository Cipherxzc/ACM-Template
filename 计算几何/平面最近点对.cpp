#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct node {
    LL x, y;
};

const int N = 4e5 + 5;
int n;
node a[N];

inline LL sqr(LL x) { return x * x; }
inline LL dis2(const node &a, const node &b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    auto cmp1 = [](const node &a, const node &b) { return a.x < b.x; };
    auto cmp2 = [](const node &a, const node &b) { return a.y < b.y; };

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a + 1, a + n + 1, cmp1);

    int p = 1;
    LL ans = 1e18;
    multiset<node, decltype(cmp2)> used;
    for (int i = 1; i <= n; i++) {
        while (p <= i && sqr(a[i].x - a[p].x) >= ans) {
            used.extract(a[p]);
            p++;
        }

        auto now = used.insert(a[i]);
        for (auto it = next(now); it != used.end() && sqr(it->y - a[i].y) < ans; it++) {
            ans = min(ans, dis2(a[i], *it));
        }
        if (now != used.begin()) {
            for (auto it = prev(now); sqr(a[i].y - it->y) < ans; it--) {
                ans = min(ans, dis2(a[i], *it));
                if (it == used.begin()) {
                    break;
                }
            }
        }
    }

    cout << ans << endl;

    return 0;
}