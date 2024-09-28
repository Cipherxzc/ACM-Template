#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> p;

void Euler(int n) {
    vector<bool> notp(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!notp[i]) {
            p.push_back(i);
        }
        for (int j = 0; j < p.size() && p[j] <= n / i; j++) {
            notp[i * p[j]] = true;
            if (i % p[j] == 0) {
                break;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;

    Euler(n);

    int k;
    while (q--) {
        cin >> k;
        cout << p[k - 1] << '\n';
    }

    return 0;
}