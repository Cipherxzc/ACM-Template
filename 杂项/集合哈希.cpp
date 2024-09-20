#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const LL INF = 0x7fffffffffffffff;
const int N = 2e5 + 5;
mt19937 mt_rnd(random_device{}());
uniform_int_distribution<LL> mt_dist(100ll, INF);
unordered_map<LL, LL> num;
int n;

inline LL rnd() { return mt_dist(mt_rnd); }

inline LL hashset(vector<LL> &arr) {
    LL res = 0;
    unordered_map<LL, int> cnt;
    for (LL x : arr) {
        if (!num[x]) {
            num[x] = rnd();
        }
        x = num[x];
        res ^= x * cnt[x];
        cnt[x]++;
        res ^= x * cnt[x];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    vector<LL> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    cout << hashset(a) << endl;
    cout << hashset(b) << endl;

    return 0;
}
