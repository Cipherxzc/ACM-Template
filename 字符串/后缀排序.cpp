#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int x1[N], x2[N], cnt[N], sa[N];
// x1[i]: 编号为i的后缀的第一关键字
// x2[i]: 第二关键字排名为i的后缀的编号
// sa[i]: 排名为i的后缀的编号

void SA(const string &s) {
    int n = s.size(), m = 122;  // 第一关键字的种类数
    auto Count = [&n, &m]() {
        for (int i = 1; i <= m; i++) {
            cnt[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cnt[x1[i]]++;
        }
        for (int i = 2; i <= m; i++) {
            cnt[i] += cnt[i - 1];
        }
    };

    for (int i = 0; i < n; i++) {
        x1[i] = s[i];
    }
    Count();
    for (int i = n - 1; i >= 0; i--) {
        sa[cnt[x1[i]]--] = i;  // 此时我们已经通过前缀和处理出了每一种第一关键字的后缀所处的排名区间
    }

    for (int k = 1; k <= n; k <<= 1) {
        int tot = 0;
        for (int i = n - k; i < n; i++) {  // 第二关键字超出n的部分，可以认为拥有最小的第二关键字
            x2[++tot] = i;
        }
        for (int i = 1; i <= n; i++) {
            // 编号为 sa[i] - k 的后缀，拥有当前最小的第二关键字，因为它的第二关键字是编号为 sa[i] 的后缀
            if (sa[i] >= k) {
                x2[++tot] = sa[i] - k;
            }
        }

        Count();
        for (int i = n; i >= 1; i--) {
            sa[cnt[x1[x2[i]]]--] = x2[i];  // 对于第一关键字相同的后缀，按照第二关键字排序。注意同上所述，排名区间已确定
            x2[i] = 0;
        }

        // 使用x2作为临时存储空间储存第一关键字，用于后续处理。注意此时第二关键字已经不重要了，因为我们已经利用它得到了所有后缀的当前排名sa
        swap(x1, x2);
        x1[sa[1]] = tot = 1;
        for (int i = 2; i <= n; i++) {  // 重新确定第一关键字，将已经通过第二关键字确定大小关系的后缀区分开
            if (x2[sa[i]] == x2[sa[i - 1]] && x2[sa[i] + k] == x2[sa[i - 1] + k]) {
                x1[sa[i]] = tot;
            } else {
                x1[sa[i]] = ++tot;
            }
        }

        if (tot == n) {
            break;
        } else {
            m = tot;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> s;

    SA(s);

    for (int i = 1; i <= s.size(); i++) {
        cout << sa[i] + 1 << ' ';
    }
    cout << endl;

    return 0;
}