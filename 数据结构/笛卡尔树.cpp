#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct DTree {
    struct node {
        int key, fa, lson, rson;
    };

    const int INF = 1e9;
    int n, root;
    vector<node> a;

    DTree(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        root = 0;
        a.assign(n + 1, {0, 0, 0, 0});
    }

    void build() {
        a[0].key = -INF;
        for (int i = 1; i <= n; i++) {
            int p = i - 1;
            while (a[p].key > a[i].key) {
                p = a[p].fa;
            }
            a[i].fa = p;
            a[i].lson = a[p].rson;
            a[a[i].rson].fa = i;
            a[p].rson = i;
        }
        root = a[0].rson;
    }
};

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    DTree dt(n);
    for (int i = 1; i <= n; i++) {
        cin >> dt.a[i].key;
    }
    dt.build();

    LL res1 = 0, res2 = 0;
    for (int i = 1; i <= n; i++) {
        res1 ^= (LL)i * (dt.a[i].lson + 1);
        res2 ^= (LL)i * (dt.a[i].rson + 1);
    }
    cout << res1 << ' ' << res2 << endl;

    return 0;
}