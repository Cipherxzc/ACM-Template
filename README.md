# Template

<style>
h3 { page-break-before: avoid; }
</style>

## 目录

- [图论](#图论)
  - [2-SAT.cpp](#2-satcpp)
  - [dfn序lca.cpp](#dfn序lcacpp)
  - [倍增lca.cpp](#倍增lcacpp)
  - [强连通分量.cpp](#强连通分量cpp)
- [字符串](#字符串)
  - [AC自动机.cpp](#ac自动机cpp)
  - [exkmp.cpp](#exkmpcpp)
  - [kmp.cpp](#kmpcpp)
  - [Manacher.cpp](#manachercpp)
  - [后缀排序.cpp](#后缀排序cpp)
  - [回文自动机.cpp](#回文自动机cpp)
  - [字符串哈希.cpp](#字符串哈希cpp)
- [数学](#数学)
  - [exgcd.cpp](#exgcdcpp)
  - [FFT.cpp](#fftcpp)
  - [FWT.cpp](#fwtcpp)
  - [Min_25筛.cpp](#min_25筛cpp)
  - [NTT.cpp](#nttcpp)
  - [Pollard_Rho.cpp](#pollard_rhocpp)
  - [多项式乘法逆.cpp](#多项式乘法逆cpp)
  - [矩阵快速幂.cpp](#矩阵快速幂cpp)
  - [线性筛.cpp](#线性筛cpp)
  - [高斯消元.cpp](#高斯消元cpp)
- [数据结构](#数据结构)
  - [ST表.cpp](#st表cpp)
  - [分块.cpp](#分块cpp)
  - [动态开点线段树.cpp](#动态开点线段树cpp)
  - [字典树.cpp](#字典树cpp)
  - [平衡树Splay.cpp](#平衡树splaycpp)
  - [并查集.cpp](#并查集cpp)
  - [文艺平衡树Splay.cpp](#文艺平衡树splaycpp)
  - [李超线段树.cpp](#李超线段树cpp)
  - [树状数组.cpp](#树状数组cpp)
  - [笛卡尔树.cpp](#笛卡尔树cpp)
  - [线段树分裂.cpp](#线段树分裂cpp)
  - [虚树.cpp](#虚树cpp)
  - [重链剖分.cpp](#重链剖分cpp)
- [杂项](#杂项)
  - [pb_ds.cpp](#pb_dscpp)
  - [对拍.cpp](#对拍cpp)
  - [树哈希.cpp](#树哈希cpp)
  - [集合哈希.cpp](#集合哈希cpp)
  - [高精度数.cpp](#高精度数cpp)
- [网络流与二分图](#网络流与二分图)
  - [二分图最大匹配.cpp](#二分图最大匹配cpp)
  - [二分图最大权完美匹配.cpp](#二分图最大权完美匹配cpp)
  - [最小费用最大流.cpp](#最小费用最大流cpp)
  - [有负环的费用流.cpp](#有负环的费用流cpp)
  - [网络最大流.cpp](#网络最大流cpp)
- [计算几何](#计算几何)
  - [平面最近点对.cpp](#平面最近点对cpp)
  - [点.cpp](#点cpp)
  - [线.cpp](#线cpp)




## 图论

### 2-SAT.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 5;
int n, m, a[N], id[N];

// 点的范围为 [2, 2n+1]，其中 2x 对应 x取0，2x+1 对应 x取1
namespace TwoSat {
    int val[N], dfn[N], low[N], tot, num, id[N];
    bool ins[N];
    vector<int> e[N];
    stack<int> st;

    inline void add(int u, int v) { e[u].emplace_back(v); }
    inline void add(int u, int x, int v, int y) {
        u = u << 1 ^ x;
        v = v << 1 ^ y;
        add(u, v);
    }

    void init() {
        for (int i = 2; i <= n * 2 + 1; i++) {
            dfn[i] = 0;
            ins[i] = false;
        }
        tot = num = 0;
    }

    void tarjan(int p) {  // 强连通分量
        low[p] = dfn[p] = ++tot;
        st.push(p);
        ins[p] = true;
        for (int q : e[p]) {
            if (!dfn[q]) {
                tarjan(q);
                low[p] = min(low[p], low[q]);
            } else if (ins[q]) {
                low[p] = min(low[p], low[q]);
            }
        }

        if (dfn[p] == low[p]) {
            num++;
            int q = 0;
            while (q != p) {
                q = st.top();
                st.pop();
                ins[q] = false;
                id[q] = num;
            }
        }
    }

    bool work() {  // tarjan缩点的结果符合拓扑序
        for (int i = 2; i <= n * 2 + 1; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }

        for (int i = 1; i <= n; i++) {
            int x0 = i << 1, x1 = x0 | 1;
            if (id[x0] == id[x1]) {
                return false;
            }
            val[i] = id[x1] < id[x0];  // id小的拓扑序靠后，为真
        }
        return true;
    }
}  // namespace TwoSat

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    TwoSat::init();
    for (int i = 1, u, v, x, y; i <= m; i++) {
        cin >> u >> x >> v >> y;
        TwoSat::add(u, x ^ 1, v, y);
        TwoSat::add(v, y ^ 1, u, x);
    }

    if (TwoSat::work()) {
        cout << "POSSIBLE" << endl;
        for (int i = 1; i <= n; i++) {
            cout << TwoSat::val[i] << ' ';
        }
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
```
### dfn序lca.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 5e5 + 5;
int n, q, root, tot, dfn[N];
vector<int> e[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

namespace LCA {
    struct ST {
        int n, bit;
        vector<vector<int>> st;

        ST(int n = 0) { init(n); }

        void init(int n) {
            this->n = n;
            bit = lg(n);
            st.resize(bit + 1);
            for (int i = 0; i <= bit; i++) {
                st[i].resize(n + 1);
            }
        }

        inline int get(int x, int y) { return (dfn[x] < dfn[y] ? x : y); }

        void build() {
            for (int i = 1; i <= bit; i++) {
                int gg = 1 << (i - 1);
                for (int j = 1; j + (gg << 1) - 1 <= n; j++) {
                    st[i][j] = get(st[i - 1][j], st[i - 1][j + gg]);
                }
            }
        }

        inline int query(int l, int r) {
            int gg = lg(r - l + 1);
            return get(st[gg][l], st[gg][r - (1 << gg) + 1]);
        }
    } st;

    void dfs(int p, int fa) {
        dfn[p] = ++tot;
        st.st[0][dfn[p]] = fa;
        for (int q : e[p]) {
            if (q != fa) {
                dfs(q, p);
            }
        }
    }

    void init() {
        tot = 0;
        st.init(n);
        dfs(root, 0);
        st.build();
    }

    int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        if (dfn[u] > dfn[v]) {
            swap(u, v);
        }
        return st.query(dfn[u] + 1, dfn[v]);
    }
}  // namespace LCA

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q >> root;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
    }

    LCA::init();

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << LCA::lca(u, v) << endl;
    }

    return 0;
}
```
### 倍增lca.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 5e5 + 5;
int n, q, root, dep[N];
vector<int> e[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

namespace LCA {
    int fa[20][N];

    void dfs(int p) {
        for (int q : e[p]) {
            if (q == fa[0][p]) {
                continue;
            }
            dep[q] = dep[p] + 1;
            fa[0][q] = p;
            dfs(q);
        }
    }

    void init() {
        dfs(root);

        for (int j = 1; j <= lg(n - 1); j++) {
            for (int i = 1; i <= n; i++) {
                fa[j][i] = fa[j - 1][fa[j - 1][i]];
            }
        }
    }

    int lca(int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        while (dep[u] - dep[v]) {
            u = fa[lg(dep[u] - dep[v])][u];
        }
        if (u == v) {
            return u;
        }
        for (int i = lg(dep[u]); i >= 0; i--) {
            if (fa[i][u] != fa[i][v]) {
                u = fa[i][u];
                v = fa[i][v];
            }
        }
        return fa[0][u];
    }
}  // namespace LCA

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q >> root;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
    }

    LCA::init();

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << LCA::lca(u, v) << endl;
    }

    return 0;
}
```
### 强连通分量.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
int n, m, a[N], id[N], num, f[N];
vector<int> e[N], point[N];

inline void add(int u, int v) { e[u].emplace_back(v); }

namespace Tarjan {  // 强连通分量
    int dfn[N], low[N], tot;
    bool ins[N];
    stack<int> st;

    void init() {
        for (int i = 1; i <= n; i++) {
            dfn[i] = 0;
            ins[i] = false;
        }
        for (int i = 1; i <= num; i++) {
            point[i].clear();
        }
        tot = num = 0;
    }

    void tarjan(int p) {
        low[p] = dfn[p] = ++tot;
        st.push(p);
        ins[p] = true;
        for (int q : e[p]) {
            if (!dfn[q]) {
                tarjan(q);
                low[p] = min(low[p], low[q]);
            } else if (ins[q]) {
                low[p] = min(low[p], low[q]);
            }
        }

        if (dfn[p] == low[p]) {
            num++;
            int q = 0;
            while (q != p) {
                q = st.top();
                st.pop();
                ins[q] = false;
                id[q] = num;
                point[num].emplace_back(q);
            }
        }
    }

    void work() {  // tarjan缩点的结果符合拓扑序
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
    }
}  // namespace Tarjan

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        add(u, v);
    }

    Tarjan::init();
    Tarjan::work();

    int ans = 0;
    for (int i = 1; i <= num; i++) {
        int val = 0;
        for (int p : point[i]) {
            val += a[p];
            for (int q : e[p]) {
                f[i] = max(f[i], f[id[q]]);
            }
        }
        f[i] += val;
        ans = max(ans, f[i]);
    }

    cout << ans << endl;

    return 0;
}

```

<div style="page-break-after: always;"></div>


## 字符串

### AC自动机.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

struct AC {
    struct node {
        int son[26], cnt, fail;
    };

    vector<node> trie;
    int tot;

    AC() { clear(); }

    void clear() {
        trie.clear();
        trie.emplace_back();
        tot = 0;
    }

    inline void insert(const string &str) {
        int p = 0;
        for (char ch : str) {
            int x = ch - 'a';
            if (!trie[p].son[x]) {
                trie[p].son[x] = ++tot;
                trie.emplace_back();
            }
            p = trie[p].son[x];
        }
        trie[p].cnt++;
    }

    inline void build() {
        queue<int> que;
        for (int p : trie[0].son) {
            if (p) {
                que.push(p);
                trie[p].fail = 0;
            }
        }

        while (!que.empty()) {
            int p = que.front();
            que.pop();
            for (int i = 0; i < 26; i++) {
                int &q = trie[p].son[i];
                if (q) {
                    trie[q].fail = trie[trie[p].fail].son[i];
                    que.push(q);
                } else {
                    q = trie[trie[p].fail].son[i];
                }
            }
        }
    }

    inline int query(const string &str) {
        int p = 0, res = 0;
        for (char ch : str) {
            p = trie[p].son[ch - 'a'];
            for (int i = p; i && trie[i].cnt != -1; i = trie[i].fail) {
                res += trie[i].cnt;
                trie[i].cnt = -1;
            }
        }
        return res;
    }
};

const int N = 1e6 + 5;
int n;
string s[N], t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    AC ac;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        ac.insert(s[i]);
    }

    ac.build();

    cin >> t;
    cout << ac.query(t) << endl;

    return 0;
}
```
### exkmp.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 2e7 + 5;
int nxt[N], ext[N];  // nxt: 每个后缀最长匹配前缀

inline void getnxt(const string &s) {
    int n = s.length(), r = 0, x = 1;  // r: 当前最远匹配位置 x: 匹配至r的后缀
    nxt[0] = n;
    while (r + 1 < n && s[r + 1] == s[r]) {
        r++;
    }
    nxt[1] = r;
    for (int i = 2; i < n; i++) {
        r = x + nxt[x] - 1;
        int len = nxt[i - x];
        if (i + len <= r) {
            nxt[i] = len;
        } else {
            len = max(0, r - i + 1);
            while (i + len < n && s[i + len] == s[len]) {
                len++;
            }
            nxt[i] = len;
            x = i;
        }
    }
}

inline void exkmp(const string &s, const string &t) {
    int n = t.length(), m = s.length(), r = 0, x = 0;
    while (r < n && r < m && s[r] == t[r]) {
        r++;
    }
    ext[0] = r;
    for (int i = 1; i < n; i++) {
        r = x + ext[x] - 1;
        int len = nxt[i - x];
        if (i + len <= r) {
            ext[i] = len;
        } else {
            len = max(0, r - i + 1);
            while (i + len < n && len < m && t[i + len] == s[len]) {
                len++;
            }
            ext[i] = len;
            x = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string a, b;
    cin >> a >> b;

    getnxt(b);
    exkmp(b, a);

    LL ans = 0;
    for (int i = 0; i < b.length(); i++) {
        ans ^= (LL)(i + 1) * (nxt[i] + 1);
    }
    cout << ans << endl;

    ans = 0;
    for (int i = 0; i < a.length(); i++) {
        ans ^= (LL)(i + 1) * (ext[i] + 1);
    }
    cout << ans << endl;

    return 0;
}

```
### kmp.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int fail[N];

inline void KMP(const string &str) {
    fail[0] = -1;
    for (int i = 1; i < str.length(); i++) {
        int p = fail[i - 1];
        while (p >= 0 && str[p + 1] != str[i]) {
            p = fail[p];
        }
        if (str[p + 1] == str[i]) {
            p++;
        }
        fail[i] = p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    KMP(s2);

    int cnt = 0, p = -1;
    for (int i = 0; i < s1.length(); i++) {
        while (p >= 0 && s1[i] != s2[p + 1]) {
            p = fail[p];
        }
        if (s2[p + 1] == s1[i]) {
            p++;
            if (p == s2.length() - 1) {
                cout << i - s2.length() + 2 << endl;
                p = fail[p];
            }
        }
    }

    for (int i = 0; i < s2.length(); i++) {
        cout << fail[i] + 1 << ' ';
    }

    return 0;
}
```
### Manacher.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void manacher(const string &s, vector<int> &l) {  // 回文半径存至l
    vector<char> a;
    a.resize(s.size() * 2 + 3);
    l.resize(s.size() * 2 + 3);
    a.front() = 1;
    a.back() = 2;  // 边界
    for (int i = 0; i < s.size(); i++) {
        a[i * 2 + 1] = 0;
        a[i * 2 + 2] = s[i];
    }
    a[a.size() - 2] = 0;

    int mid = 0, r = 0;
    for (int i = 1; i < a.size() - 1; i++) {
        l[i] = (i >= r) ? 1 : min(r - i, l[(mid << 1) - i]);
        while (a[i + l[i]] == a[i - l[i]]) {
            l[i]++;
        }
        if (i + l[i] > r) {
            r = i + l[i];
            mid = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> s;

    vector<int> l;
    manacher(s, l);

    int ans = 0;
    for (int i = 1; i < l.size() - 1; i++) {
        ans = max(ans, l[i]);
    }
    cout << ans - 1 << endl;

    return 0;
}
```
### 后缀排序.cpp

```cpp
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
```
### 回文自动机.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int len[N], cnt[N], fail[N], trie[N][30];

inline void PAM(const string &s) {
    auto getfail = [&s](int p, int i) {
        while (i == len[p] || s[i - len[p] - 1] != s[i]) {
            p = fail[p];
        }
        return p;
    };

    fail[0] = 1;
    len[1] = -1;
    int tot = 1, p = 0;
    for (int i = 0; i < s.length(); i++) {
        p = getfail(p, i);
        if (!trie[p][s[i] - 'a']) {
            fail[++tot] = trie[getfail(fail[p], i)][s[i] - 'a'];
            trie[p][s[i] - 'a'] = tot;
            len[tot] = len[p] + 2;
            cnt[tot] = cnt[fail[tot]] + 1;
        }
        p = trie[p][s[i] - 'a'];

        cout << cnt[p] << ' ';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string s;
    cin >> s;

    PAM(s);

    return 0;
}
```
### 字符串哈希.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int base = 131, mod1 = 1e9 + 7, mod2 = 998244353;
int n;
string s;

inline LL hashs(const string &str) {
    LL res1 = 0, res2 = 0;
    for (char ch : str) {
        res1 = (res1 * base + ch) % mod1;
        res2 = (res2 * base + ch) % mod2;
    }
    return res1 * 1000000000 + res2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;

    set<LL> vis;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        vis.insert(hashs(s));
    }

    cout << vis.size();

    return 0;
}
```

<div style="page-break-after: always;"></div>


## 数学

### exgcd.cpp

```cpp
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
```
### FFT.cpp

```cpp
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

```
### FWT.cpp

```cpp
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

```
### Min_25筛.cpp

```cpp
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
```
### NTT.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using poly = vector<LL>;

const int mod = 998244353, G = 3, Gi = 332748118;

inline LL qp(LL x, LL y) {
    LL res = 1;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

void ntt(poly &arr, int n, int type) {
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

    for (int l = 1; l < n; l <<= 1) {
        LL gg = qp(type == 1 ? G : Gi, (mod - 1) / (l << 1));
        for (int i = 0; i < n; i += l * 2) {
            LL omega = 1;
            for (int j = i; j < i + l; j++) {
                LL x = arr[j], y = omega * arr[j + l] % mod;
                arr[j] = (x + y) % mod;
                arr[j + l] = (x - y + mod) % mod;
                omega = omega * gg % mod;
            }
        }
    }

    if (type == -1) {
        LL inv = qp(n, mod - 2);
        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * inv % mod;
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

    ntt(a, n + m, 1);
    ntt(b, n + m, 1);

    poly c(a.size());
    for (int i = 0; i < c.size(); i++) {
        c[i] = a[i] * b[i] % mod;
    }
    ntt(c, n + m, -1);

    for (int i = 0; i <= n + m; i++) {
        cout << c[i] << ' ';
    }
    cout << endl;

    return 0;
}
```
### Pollard_Rho.cpp

```cpp
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
```
### 多项式乘法逆.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using poly = vector<LL>;

const int mod = 998244353, G = 3, Gi = 332748118;

inline LL qp(LL x, LL y) {
    LL res = 1;
    while (y) {
        if (y & 1) {
            res = res * x % mod;
        }
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}

inline LL inv(LL x) { return qp(x, mod - 2); }

void ntt(poly &arr, int n, int type) {
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

    for (int l = 1; l < n; l <<= 1) {
        LL gg = qp(type == 1 ? G : Gi, (mod - 1) / (l << 1));
        for (int i = 0; i < n; i += l * 2) {
            LL omega = 1;
            for (int j = i; j < i + l; j++) {
                LL x = arr[j], y = omega * arr[j + l] % mod;
                arr[j] = (x + y) % mod;
                arr[j + l] = (x - y + mod) % mod;
                omega = omega * gg % mod;
            }
        }
    }

    if (type == -1) {
        LL inv = qp(n, mod - 2);
        for (int i = 0; i < n; i++) {
            arr[i] = arr[i] * inv % mod;
        }
    }
}

void polyinv(const poly &arr, int n, poly &res) {
    res.clear();
    res.emplace_back(inv(arr[0]));
    poly tmp(2);
    for (int t = 2; (t >> 1) < n; t <<= 1) {  // 当前为mod x^(t/2) 下的逆元
        int t2 = t << 1;
        for (int i = 0; i < t; i++) {
            tmp[i] = arr[i];
        }

        ntt(tmp, t2 - 1, 1);
        ntt(res, t2 - 1, 1);
        for (int i = 0; i < t2; i++) {
            res[i] = res[i] * (2 - res[i] * tmp[i] % mod) % mod;
        }
        ntt(res, t2 - 1, -1);
        for (int i = t; i < t2; i++) {
            res[i] = 0;
        }
    }

    res.resize(n);
    for (LL &x : res) {
        if (x < 0) {
            x += mod;
        }
    }
}

int n, m;
poly a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    polyinv(a, n, b);
    for (int x : b) {
        cout << x << ' ';
    }
    cout << endl;

    return 0;
}
```
### 矩阵快速幂.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct matrix {
    int siz;
    vector<vector<LL>> mat;

    matrix(int n, int x = 0) {
        siz = n;
        mat.resize(siz);
        for (int i = 0; i < siz; i++) {
            mat[i].resize(siz);
            mat[i][i] = x;
        }
    }

    void init(int x = 0) {
        for (int i = 0; i < siz; i++) {
            mat[i].assign(siz, 0);
            mat[i][i] = x;
        }
    }

    vector<LL> &operator[](int x) { return mat[x]; }

    const vector<LL> &operator[](int x) const { return mat[x]; }
};

const int mod = 1e9 + 7;

matrix operator+(const matrix &a, const matrix &b) {
    matrix c(a.siz);
    for (int i = 0; i < a.siz; i++) {
        for (int j = 0; j < a.siz; j++) {
            c[i][j] = (a[i][j] + b[i][j]) % mod;
        }
    }
    return c;
}

void operator+=(matrix &a, const matrix &b) { a = a + b; }

matrix operator*(const matrix &a, const matrix &b) {
    matrix c(a.siz);
    for (int i = 0; i < a.siz; i++) {
        for (int j = 0; j < a.siz; j++) {
            for (int k = 0; k < a.siz; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return c;
}

void operator*=(matrix &a, const matrix &b) { a = a * b; }

inline matrix matqp(matrix x, LL k) {
    matrix res(x.siz, 1);
    while (k) {
        if (k & 1) {
            res *= x;
        }
        k >>= 1;
        x *= x;
    }
    return res;
}

int n;
LL k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;

    matrix a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    a = matqp(a, k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}

```
### 线性筛.cpp

```cpp
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
```
### 高斯消元.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using db = double;

const db eps = 1e-6;

inline int sign(db x) { return x < -eps ? -1 : x > eps; }
inline int cmp(db x, db y) { return sign(x - y); }

const int N = 105;
int n, m;
db a[N][N];

namespace Gauss {
    inline void swapr(int x, int y) {
        for (int i = 1; i <= m + 1; i++) {
            swap(a[x][i], a[y][i]);
        }
    }

    inline void mul(int x, db k) {
        for (int i = 1; i <= m + 1; i++) {
            a[x][i] *= k;
        }
    }

    inline void add(int y, int x, double k) {
        for (int i = 1; i <= m + 1; i++) {
            a[y][i] += a[x][i] * k;
        }
    }

    int solve() {
        int p = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = p; j <= n; j++) {
                if (cmp(a[j][i], 0) != 0) {
                    if (j != p) {
                        swapr(p, j);
                    }
                    break;
                }
            }
            if (cmp(a[p][i], 0) == 0) {
                continue;
            }

            mul(i, 1 / a[p][i]);
            for (int j = 1; j <= n; j++) {
                if (j != p) {
                    add(j, p, -a[j][i]);
                }
            }
            p++;
        }

        for (int i = p; i <= n; i++) {
            if (cmp(a[i][m + 1], 0) != 0) {
                return -1;  // No Solution
            }
        }
        if (p <= m) {
            return 0;  // Too Many Solutions
        } else {
            return 1;  // One Solution
        }
    }
}  // namespace Gauss

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    m = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> a[i][j];
        }
    }

    int flag = Gauss::solve();

    if (flag == 1) {
        cout << fixed << setprecision(2);
        for (int i = 1; i <= n; i++) {
            cout << 'x' << i << '=' << a[i][m + 1] << endl;
        }
    } else {
        cout << flag << endl;
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>


## 数据结构

### ST表.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

struct ST {
    int n, bit;
    vector<vector<int>> st;

    ST(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        bit = lg(n);
        st.resize(bit + 1);
        for (int i = 0; i <= bit; i++) {
            st[i].resize(n + 1);
        }
    }

    void build() {
        for (int i = 1; i <= bit; i++) {
            int gg = 1 << (i - 1);
            for (int j = 1; j + (gg << 1) - 1 <= n; j++) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + gg]);
            }
        }
    }

    inline int query(int l, int r) {
        int gg = lg(r - l + 1);
        return max(st[gg][l], st[gg][r - (1 << gg) + 1]);
    }
};

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    ST st(n);
    for (int i = 1; i <= n; i++) {
        cin >> st.st[0][i];
    }
    st.build();

    int l, r;
    while (m--) {
        cin >> l >> r;
        cout << st.query(l, r) << endl;
    }

    return 0;
}
```
### 分块.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e5 + 5;
int n, m, a[N];

namespace Block {
    struct block {
        int l, r;
        LL sum, tag;

        inline void spread() {
            if (tag) {
                for (int i = l; i <= r; i++) {
                    a[i] += tag;
                }
                tag = 0;
            }
        }

        inline void add(LL x) {
            sum += x * (r - l + 1);
            tag += x;
        }

        inline void add(int lx, int rx, LL x) {
            sum += x * (rx - lx + 1);
            for (int i = lx; i <= rx; i++) {
                a[i] += x;
            }
        }

        inline LL query(int lx, int rx) {
            spread();
            LL res = 0;
            for (int i = lx; i <= rx; i++) {
                res += a[i];
            }
            return res;
        }
    };

    const int B = 316;
    int num, pos[N];
    block b[B + 5];

    void init() {
        num = (n - 1) / B + 1;
        for (int i = 1; i <= num; i++) {
            b[i].l = b[i - 1].r + 1;
            b[i].r = b[i].l + B - 1;
        }
        b[num].r = min(b[num].r, n);
        for (int i = 1; i <= num; i++) {
            b[i].sum = b[i].tag = 0;
            for (int j = b[i].l; j <= b[i].r; j++) {
                b[i].sum += a[j];
                pos[j] = i;
            }
        }
    }

    void add(int l, int r, LL x) {
        int lx = pos[l], rx = pos[r];
        if (lx == rx) {
            b[lx].add(l, r, x);
        } else {
            b[lx].add(l, b[lx].r, x);
            b[rx].add(b[rx].l, r, x);
            for (int i = lx + 1; i < rx; i++) {
                b[i].add(x);
            }
        }
    }

    LL query(int l, int r) {
        int lx = pos[l], rx = pos[r];
        LL res = 0;
        if (lx == rx) {
            res = b[lx].query(l, r);
        } else {
            res += b[lx].query(l, b[lx].r);
            res += b[rx].query(b[rx].l, r);
            for (int i = lx + 1; i < rx; i++) {
                res += b[i].sum;
            }
        }
        return res;
    }
}  // namespace Block

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    Block::init();

    while (m--) {
        int op, l, r;
        LL x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            Block::add(l, r, x);
        } else {
            cout << Block::query(l, r) << endl;
        }
    }

    return 0;
}
```
### 动态开点线段树.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct SegmentTree {
    struct segment {
        int lson, rson;
        LL val, tag;
    };

    const int MAXN = 5e5;
    int n, tot, root;
    vector<segment> st;

    SegmentTree(int siz = 0) { init(siz); }

    void init(int siz) {
        n = siz;
        root = tot = 0;
        st.resize(MAXN);
    }

    inline void push_up(int p) { st[p].val = st[st[p].lson].val + st[st[p].rson].val; }

    inline void spread(int p, int l, int r) {
        if (!st[p].tag) {
            return;
        }
        if (!st[p].lson) {
            st[p].lson = ++tot;
        }
        if (!st[p].rson) {
            st[p].rson = ++tot;
        }
        int mid = (l + r) >> 1;
        st[st[p].lson].tag += st[p].tag;
        st[st[p].lson].val += st[p].tag * (mid - l + 1);
        st[st[p].rson].tag += st[p].tag;
        st[st[p].rson].val += st[p].tag * (r - mid);
        st[p].tag = 0;
    }

    void add(int &p, int l, int r, int lx, int rx, LL x) {
        if (!p) {
            p = ++tot;
        }
        if (lx <= l && r <= rx) {
            st[p].val += x * (r - l + 1);
            st[p].tag += x;
            return;
        }
        int mid = (l + r) >> 1;
        spread(p, l, r);
        if (lx <= mid) {
            add(st[p].lson, l, mid, lx, rx, x);
        }
        if (mid < rx) {
            add(st[p].rson, mid + 1, r, lx, rx, x);
        }
        push_up(p);
    }

    LL query(int p, int l, int r, int lx, int rx) {
        if (!p) {
            return 0;
        }
        if (lx <= l && r <= rx) {
            return st[p].val;
        }
        int mid = (l + r) >> 1;
        LL res = 0;
        spread(p, l, r);
        if (lx <= mid) {
            res += query(st[p].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(st[p].rson, mid + 1, r, lx, rx);
        }
        return res;
    }

    void add(int lx, int rx, LL x) { add(root, 1, n, lx, rx, x); }

    LL query(int lx, int rx) { return query(root, 1, n, lx, rx); }
};

const int N = 1e5 + 5;
int n, m;
LL a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTree st(n);
    for (int i = 1; i <= n; i++) {
        st.add(i, i, a[i]);
    }

    while (m--) {
        int op, l, r;
        LL x;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> x;
            st.add(l, r, x);
        } else {
            cout << st.query(l, r) << endl;
        }
    }

    return 0;
}

```
### 字典树.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int get(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    if ('A' <= ch && ch <= 'Z') {
        return ch - 'A' + 26;
    }
    return ch - '0' + 52;
}

struct Trie {
    struct node {
        int son[62], cnt;
    };

    vector<node> trie;
    int tot;

    Trie() { clear(); }

    void clear() {
        trie.clear();
        trie.emplace_back();
        tot = 0;
    }

    inline void insert(const string &str) {
        int p = 0;
        for (char ch : str) {
            int gg = get(ch);
            if (!trie[p].son[gg]) {
                trie[p].son[gg] = ++tot;
                trie.emplace_back();
            }
            p = trie[p].son[gg];
            trie[p].cnt++;
        }
    }

    inline int query(const string &str) {
        int p = 0;
        for (char ch : str) {
            int gg = get(ch);
            p = trie[p].son[gg];
            if (!p) {
                return 0;
            }
        }
        return trie[p].cnt;
    }
};

int T, n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T--) {
        string s;
        Trie trie;
        cin >> n >> q;
        for (int i = 1; i <= n; i++) {
            cin >> s;
            trie.insert(s);
        }

        while (q--) {
            cin >> s;
            cout << trie.query(s) << endl;
        }
    }

    return 0;
}
```
### 平衡树Splay.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7fffffff;

struct Splay {
    struct node {
        int lson, rson, fa, cnt, siz, key;
    };

    vector<node> a;
    int root;

    Splay() { clear(); }

    int New(int fa, int key) {  // vector扩展时地址可能会变，因此如果有取地址操作需要特别注意
        a.emplace_back(0, 0, fa, 1, 1, key);
        return a.size() - 1;
    }

    void push_up(int p) { a[p].siz = a[p].cnt + a[a[p].lson].siz + a[a[p].rson].siz; }

    bool get(int p) {  // 是左子则返回 true
        return p == a[a[p].fa].lson;
    }

    // clang-format off
    void zig(int &p) {  // 右旋
        int q = a[p].lson;
        a[p].lson = a[q].rson; a[a[q].rson].fa = p;
        a[q].rson = p; a[q].fa = a[p].fa; a[p].fa = q; p = q;
        push_up(p); push_up(a[p].rson);
    }

    void zag(int &p) {  // 左旋
        int q = a[p].rson;
        a[p].rson = a[q].lson; a[a[q].lson].fa = p;
        a[q].lson = p; a[q].fa = a[p].fa; a[p].fa = q; p = q;
        push_up(p); push_up(a[p].lson);
    }
    // clang-format on

    void rotate(int p) {  // 将 点p 向上旋转
        int q = a[p].fa, r = a[q].fa;
        if (q == root) {
            p == a[q].lson ? zig(root) : zag(root);
        } else {
            int &x = (q == a[r].lson ? a[r].lson : a[r].rson);
            p == a[q].lson ? zig(x) : zag(x);
        }
    }

    void clear() {
        a.clear();
        a.emplace_back();
        root = New(0, -INF);
        a[root].rson = New(root, INF);
        push_up(root);
    }

    void splay(int p, int &tar) {
        int q = a[p].fa;
        while (p != tar) {
            if (q != tar) {
                rotate(get(p) == get(q) ? q : p);
            }
            rotate(p);
            q = a[p].fa;
        }
        tar = p;
    }

    void splay(int p) { splay(p, root); }

    int find(int key) {
        int p = root;
        while (p) {
            if (key < a[p].key) {
                p = a[p].lson;
            } else if (key == a[p].key) {
                splay(p);
                break;
            } else {
                p = a[p].rson;
            }
        }
        return p;
    }

    int pre() {  // 根的前驱
        int p = a[root].lson;
        while (a[p].rson) {
            p = a[p].rson;
        }
        splay(p);
        return p;
    }

    int nxt() {
        int p = a[root].rson;
        while (a[p].lson) {
            p = a[p].lson;
        }
        splay(p);
        return p;
    }

    void insert(int key) {
        int p = root;
        while (true) {
            a[p].siz++;
            if (a[p].key == key) {
                a[p].cnt++;
                splay(p);
                break;
            }
            int q = key < a[p].key ? a[p].lson : a[p].rson;
            if (!q) {
                q = New(p, key);
                (key < a[p].key ? a[p].lson : a[p].rson) = q;
                splay(q);
                break;
            }
            p = q;
        }
    }

    void remove(int key) {
        int p = find(key);
        if (a[p].cnt > 1) {
            a[p].cnt--;
            a[p].siz--;
            return;
        }
        int q = pre();
        a[q].rson = a[p].rson;
        a[a[q].rson].fa = q;
        a[q].siz--;
    }

    int getrank(int key) {
        int res = 0, p = root;
        while (p) {
            if (key < a[p].key) {
                p = a[p].lson;
            } else {
                res += a[a[p].lson].siz;
                if (key == a[p].key) {
                    splay(p);
                    break;
                }
                res += a[p].cnt;
                p = a[p].rson;
            }
        }
        return res;
    }

    int getkth(int k) {
        k++;
        int p = root;
        while (true) {
            if (a[p].lson && k <= a[a[p].lson].siz) {
                p = a[p].lson;
            } else {
                k -= a[p].cnt + a[a[p].lson].siz;
                if (k <= 0) {
                    splay(p);
                    return a[p].key;
                }
                p = a[p].rson;
            }
        }
    }

    int pre(int key) {  // 插入key，并寻找根的前驱，再将key删除
        insert(key);
        int p = pre();
        remove(key);
        return a[p].key;
    }

    int nxt(int key) {
        insert(key);
        int p = nxt();
        remove(key);
        return a[p].key;
    }
};

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;

    Splay splay;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) {
            splay.insert(x);
        } else if (op == 2) {
            splay.remove(x);
        } else if (op == 3) {
            cout << splay.getrank(x) << endl;
        } else if (op == 4) {
            cout << splay.getkth(x) << endl;
        } else if (op == 5) {
            cout << splay.pre(x) << endl;
        } else {
            cout << splay.nxt(x) << endl;
        }
    }

    return 0;
}
```
### 并查集.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct DSU {
    int n;
    vector<int> fa;

    DSU(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        fa.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }

    inline int get(int p) {
        while (p != fa[p]) {
            p = fa[p] = fa[fa[p]];
        }
        return p;
    }

    inline void merge(int u, int v) { fa[get(u)] = get(v); }
};

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;

    DSU dsu(n);
    while (m--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op == 1) {
            dsu.merge(u, v);
        } else {
            if (dsu.get(u) == dsu.get(v)) {
                cout << "Y" << endl;
            } else {
                cout << "N" << endl;
            }
        }
    }

    return 0;
}
```
### 文艺平衡树Splay.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7fffffff;

struct Splay {
    struct node {
        int lson, rson, fa, cnt, siz, key;
        bool tag;
    };

    vector<node> a;
    int root, tot;

    Splay(int n) {
        root = tot = 0;
        a.resize(n + 3);  // 额外添加 0 和 n+1 两个点
        build(root, 0, 0, n + 1);
    }

    int New(int fa, int key) {  // vector扩展时地址可能会变，因此如果有取地址操作需要特别注意
        a[++tot] = {0, 0, fa, 1, 1, key, false};
        return tot;
    }

    void push_up(int p) { a[p].siz = a[p].cnt + a[a[p].lson].siz + a[a[p].rson].siz; }

    void spread(int p) {
        if (a[p].tag) {
            swap(a[p].lson, a[p].rson);
            a[a[p].lson].tag ^= 1;
            a[a[p].rson].tag ^= 1;
            a[p].tag = false;
        }
    }

    bool get(int p) {  // 是左子则返回 true
        spread(a[p].fa);
        return p == a[a[p].fa].lson;
    }

    // clang-format off
    void zig(int &p){ // 右旋
        int q = a[p].lson;
        a[p].lson = a[q].rson; a[a[q].rson].fa = p;
        a[q].rson = p; a[q].fa = a[p].fa; a[p].fa = q; p = q;
        push_up(p); push_up(a[p].rson);
    }

    void zag(int &p){ // 左旋
        int q = a[p].rson;
        a[p].rson = a[q].lson; a[a[q].lson].fa = p;
        a[q].lson = p; a[q].fa = a[p].fa; a[p].fa = q; p = q;
        push_up(p); push_up(a[p].lson);
    }
    // clang-format on

    void rotate(int p) {  // 将 点p 向上旋转
        int q = a[p].fa, r = a[q].fa;
        spread(q);
        spread(r);
        if (q == root) {
            p == a[q].lson ? zig(root) : zag(root);
        } else {
            int &x = (q == a[r].lson ? a[r].lson : a[r].rson);
            p == a[q].lson ? zig(x) : zag(x);
        }
    }

    void splay(int p, int &tar) {
        int q = a[p].fa;
        while (p != tar) {
            if (q != tar) {
                rotate(get(p) == get(q) ? q : p);
            }
            rotate(p);
            q = a[p].fa;
        }
        tar = p;
    }

    void splay(int p) { splay(p, root); }

    void build(int &p, int fa, int l, int r) {
        int mid = (l + r) >> 1;
        p = New(fa, mid);
        if (l < mid) {
            build(a[p].lson, p, l, mid - 1);
        }
        if (mid < r) {
            build(a[p].rson, p, mid + 1, r);
        }
        push_up(p);
    }

    int getkth(int k) {
        k++;
        int p = root;
        while (true) {
            spread(p);
            if (a[p].lson && k <= a[a[p].lson].siz) {
                p = a[p].lson;
            } else {
                k -= a[p].cnt + a[a[p].lson].siz;
                if (k <= 0) {
                    splay(p);
                    return p;
                }
                p = a[p].rson;
            }
        }
    }

    void reverse(int l, int r) {
        int y = getkth(r + 1), x = getkth(l - 1);
        splay(y, a[x].rson);
        a[a[y].lson].tag ^= 1;
    }

    void print(int p, int n) {
        spread(p);
        if (a[p].lson) {
            print(a[p].lson, n);
        }
        if (1 <= a[p].key && a[p].key <= n) {
            cout << a[p].key << ' ';
        }
        if (a[p].rson) {
            print(a[p].rson, n);
        }
    }

    void print(int n) {
        print(root, n);
        cout << endl;
    }
};

int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    Splay splay(n);

    int l, r;
    while (m--) {
        cin >> l >> r;
        splay.reverse(l, r);
    }

    splay.print(n);

    return 0;
}
```
### 李超线段树.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    struct line {
        double k = 0, b = 0;

        double calc(int x) { return k * x + b; }
    };

    struct segment {
        line val;
        int lson = 0, rson = 0;
    };

    const int MAXN = 5e6 + 5;
    const double eps = 1e-12;
    vector<segment> st;
    int lim, root, tot;

    SegmentTree(int n) {
        st.resize(MAXN);
        lim = n;
        tot = root = 0;
    }

    void insert(int &p, int l, int r, int lx, int rx, line x) {
        if (!p) {
            p = ++tot;
        }
        int mid = (l + r) >> 1;
        if (lx <= l && r <= rx) {
            if (x.calc(mid) - st[p].val.calc(mid) > eps) {
                swap(x, st[p].val);
            }
            if (x.calc(l) - st[p].val.calc(l) > eps || x.calc(r) - st[p].val.calc(r) > eps) {
                if (x.k > st[p].val.k) {
                    insert(st[p].rson, mid + 1, r, lx, rx, x);
                } else {
                    insert(st[p].lson, l, mid, lx, rx, x);
                }
            }
        } else {
            if (lx <= mid) {
                insert(st[p].lson, l, mid, lx, rx, x);
            }
            if (mid < rx) {
                insert(st[p].rson, mid + 1, r, lx, rx, x);
            }
        }
    }

    double query(int p, int l, int r, int x) {
        if (!p) {
            return 0;
        }
        if (l == r) {
            return st[p].val.calc(x);
        }
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return max(st[p].val.calc(x), query(st[p].lson, l, mid, x));
        } else {
            return max(st[p].val.calc(x), query(st[p].rson, mid + 1, r, x));
        }
    }

    void insert(int lx, int rx, line x) { insert(root, 1, lim, lx, rx, x); }

    double query(int x) { return query(root, 1, lim, x); }
};

int n = 50000, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    SegmentTree st(n);

    cin >> m;
    while (m--) {
        string op;
        int x;
        double k, b;
        cin >> op;
        if (op[0] == 'Q') {
            cin >> x;
            cout << floor(st.query(x) / 100) << endl;
        } else {
            cin >> b >> k;
            st.insert(1, n, {k, b - k});
        }
    }

    return 0;
}
```
### 树状数组.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct BIT {
    inline int lowbit(int x) { return x & (-x); }

    vector<LL> bit;
    int n;

    BIT(int n) { init(n); }

    void init(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    inline void add(int p, LL x) {
        while (p <= n) {
            bit[p] += x;
            p += lowbit(p);
        }
    }

    inline LL sum(int p) {
        LL res = 0;
        while (p) {
            res += bit[p];
            p -= lowbit(p);
        }
        return res;
    }

    inline LL query(int l, int r) { return sum(r) - sum(l - 1); }
};

const int N = 5e5 + 5;
int n, m, a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        bit.add(i, a[i]);
    }

    int op, l, r, pos, x;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> pos >> x;
            bit.add(pos, x);
        } else {
            cin >> l >> r;
            cout << bit.query(l, r) << endl;
        }
    }

    return 0;
}
```
### 笛卡尔树.cpp

```cpp
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
```
### 线段树分裂.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

struct SegmentTree {
    struct segment {
        int lson = 0, rson = 0;
        LL val = 0;
    };

    const int MAXN = 4e6;
    int n, tot, num;
    stack<int> bin;
    vector<int> root;
    vector<segment> st;

    SegmentTree(int n, int m) {
        this->n = n;
        tot = 0;
        num = 1;
        root.resize(m + 1);
        st.resize(MAXN);
    }

    inline int New() {
        if (bin.empty()) {
            return ++tot;
        } else {
            int tmp = bin.top();
            bin.pop();
            return tmp;
        }
    }

    inline void del(int &p) {
        bin.push(p);
        st[p].lson = st[p].rson = st[p].val = 0;
        p = 0;
    }

    inline void push_up(int p) { st[p].val = st[st[p].lson].val + st[st[p].rson].val; }

    void add(int &p, int l, int r, int tar, LL x) {
        if (!p) {
            p = New();
        }
        if (l == r) {
            st[p].val += x;
            return;
        }
        int mid = (l + r) >> 1;
        if (tar <= mid) {
            add(st[p].lson, l, mid, tar, x);
        } else {
            add(st[p].rson, mid + 1, r, tar, x);
        }
        push_up(p);
    }

    LL query(int p, int l, int r, int lx, int rx) {
        if (!p) {
            return 0;
        }
        if (lx <= l && r <= rx) {
            return st[p].val;
        }
        int mid = (l + r) >> 1;
        LL res = 0;
        if (lx <= mid) {
            res += query(st[p].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(st[p].rson, mid + 1, r, lx, rx);
        }
        return res;
    }

    int kth(int p, int l, int r, int k) {
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        if (st[st[p].lson].val >= k) {
            return kth(st[p].lson, l, mid, k);
        } else {
            return kth(st[p].rson, mid + 1, r, k - st[st[p].lson].val);
        }
    }

    void merge(int &p, int &q) {
        if (!p || !q) {
            p += q;
            q = 0;
            return;
        }
        st[p].val += st[q].val;
        merge(st[p].lson, st[q].lson);
        merge(st[p].rson, st[q].rson);
        del(q);
    }

    void split(int &p, int &q, int l, int r, int lx, int rx) {
        if (!p) {
            return;
        }
        if (!q) {
            q = New();
        }
        if (lx <= l && r <= rx) {
            q = p;
            p = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (lx <= mid) {
            split(st[p].lson, st[q].lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            split(st[p].rson, st[q].rson, mid + 1, r, lx, rx);
        }
        push_up(p);
        push_up(q);
    }

    void add(int p, int tar, LL x) { add(root[p], 1, n, tar, x); }

    LL query(int p, int lx, int rx) { return query(root[p], 1, n, lx, rx); }

    int kth(int p, int k) {
        if (st[root[p]].val < k) {
            return -1;
        } else {
            return kth(root[p], 1, n, k);
        }
    }

    void split(int p, int lx, int rx) { split(root[p], root[++num], 1, n, lx, rx); }
};

const int N = 2e5 + 5;
int n, m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    SegmentTree st(n, m);
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        st.add(1, i, x);
    }

    int opt, p, q, l, r, k, x;
    while (m--) {
        cin >> opt;
        if (opt == 0) {
            cin >> p >> l >> r;
            st.split(p, l, r);
        } else if (opt == 1) {
            cin >> p >> q;
            st.merge(st.root[p], st.root[q]);
        } else if (opt == 2) {
            cin >> p >> k >> x;
            st.add(p, x, k);
        } else if (opt == 3) {
            cin >> p >> l >> r;
            cout << st.query(p, l, r) << endl;
        } else if (opt == 4) {
            cin >> p >> k;
            cout << st.kth(p, k) << endl;
        }
    }

    return 0;
}
```
### 虚树.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define mp make_pair

inline int lg(int x) { return 31 ^ __builtin_clz(x); }

const int N = 2.5e5 + 5;
const LL INF = 1e18;
int n, m, dfn[N];
LL f[N], price[N];
vector<pair<int, int>> e[N];

inline void add(int u, int v, int w) {
    e[u].push_back(mp(v, w));
    e[v].push_back(mp(u, w));
}

namespace LCA {
    int root = 1, tot;

    struct ST {
        int n, bit;
        vector<vector<int>> st;

        ST(int n = 0) { init(n); }

        void init(int n) {
            this->n = n;
            bit = lg(n);
            st.resize(bit + 1);
            for (int i = 0; i <= bit; i++) {
                st[i].resize(n + 1);
            }
        }

        inline int get(int x, int y) { return (dfn[x] < dfn[y] ? x : y); }

        void build() {
            for (int i = 1; i <= bit; i++) {
                int gg = 1 << (i - 1);
                for (int j = 1; j + (gg << 1) - 1 <= n; j++) {
                    st[i][j] = get(st[i - 1][j], st[i - 1][j + gg]);
                }
            }
        }

        inline int query(int l, int r) {
            int gg = lg(r - l + 1);
            return get(st[gg][l], st[gg][r - (1 << gg) + 1]);
        }
    } st;

    void dfs(int p, int fa) {
        dfn[p] = ++tot;
        st.st[0][dfn[p]] = fa;
        for (auto [q, len] : e[p]) {
            if (q != fa) {
                price[q] = min(price[p], (LL)len);
                dfs(q, p);
            }
        }
    }

    void init() {
        tot = 0;
        st.init(n);
        price[root] = INF;
        dfs(root, 0);
        st.build();
    }

    int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        if (dfn[u] > dfn[v]) {
            swap(u, v);
        }
        return st.query(dfn[u] + 1, dfn[v]);
    }
}  // namespace LCA

struct VirtualTree {
    vector<int> point, st;
    vector<vector<int>> e;
    int siz, tot, root;

    VirtualTree(int siz_ = 0) { init(siz_); }

    void init(int siz_) {
        tot = siz = siz_;
        e.clear();
        st.clear();
        e.resize(siz + 1);
        point.resize(siz + 1);
        point[0] = 0;
    }

    inline void add(int u, int v) { e[u].push_back(v); }

    inline void insert(int p) {
        if (st.size() == 1) {
            st.push_back(p);
            return;
        }

        int q = LCA::lca(point[st.back()], point[p]);
        while (dfn[q] <= dfn[point[st[st.size() - 2]]]) {
            add(st[st.size() - 2], st.back());
            st.pop_back();
        }
        if (q != point[st.back()]) {
            point.push_back(q);
            e.push_back({});
            tot++;
            add(tot, st.back());
            st.back() = tot;
        }
        st.push_back(p);
    }

    void build() {
        auto cmp = [](int a, int b) { return dfn[a] < dfn[b]; };
        sort(point.begin() + 1, point.end(), cmp);

        st.push_back(0);
        for (int i = 1; i <= siz; i++) {
            insert(i);
        }
        for (int i = 1; i < st.size() - 1; i++) {
            add(st[i], st[i + 1]);
        }
        root = st[1];
    }

    LL solve(int p) {
        if (p <= siz) {
            return price[point[p]];
        }
        LL res = 0;
        for (int q : e[p]) {
            res += solve(q);
        }
        return min(res, price[point[p]]);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 1, u, v, w; i < n; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }

    LCA::init();

    cin >> m;
    while (m--) {
        int cnt;
        cin >> cnt;
        VirtualTree vt(cnt);
        for (int i = 1; i <= cnt; i++) {
            cin >> vt.point[i];
        }
        vt.build();

        cout << vt.solve(vt.root) << endl;
    }

    return 0;
}
```
### 重链剖分.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int mod;

struct SegmentTree {
    struct segment {
        LL val, tag;
    };

    int n;
    vector<segment> st;
    vector<int> a;

    SegmentTree(int n) {
        this->n = n;
        st.resize(n * 4);
        a.resize(n + 1);
    }

    inline void push_up(int p) {
        int lson = p << 1, rson = p << 1 | 1;
        st[p].val = (st[lson].val + st[rson].val) % mod;
    }

    inline void spread(int p, int l, int r) {
        if (!st[p].tag) {
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        st[lson].tag = (st[lson].tag + st[p].tag) % mod;
        st[rson].tag = (st[rson].tag + st[p].tag) % mod;
        st[lson].val = (st[lson].val + st[p].tag * (mid - l + 1) % mod) % mod;
        st[rson].val = (st[rson].val + st[p].tag * (r - mid) % mod) % mod;
        st[p].tag = 0;
    }

    void build(int p, int l, int r) {
        st[p].tag = 0;
        if (l == r) {
            st[p].val = a[l];
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        build(lson, l, mid);
        build(rson, mid + 1, r);
        push_up(p);
    }

    void add(int p, int l, int r, int lx, int rx, LL x) {
        if (lx <= l && r <= rx) {
            st[p].val += x * (r - l + 1);
            st[p].tag += x;
            return;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        spread(p, l, r);
        if (lx <= mid) {
            add(lson, l, mid, lx, rx, x);
        }
        if (mid < rx) {
            add(rson, mid + 1, r, lx, rx, x);
        }
        push_up(p);
    }

    LL query(int p, int l, int r, int lx, int rx) {
        if (lx <= l && r <= rx) {
            return st[p].val;
        }
        int mid = (l + r) >> 1, lson = p << 1, rson = p << 1 | 1;
        LL res = 0;
        spread(p, l, r);
        if (lx <= mid) {
            res += query(lson, l, mid, lx, rx);
        }
        if (mid < rx) {
            res += query(rson, mid + 1, r, lx, rx);
        }
        return res % mod;
    }

    void build() { build(1, 1, n); }

    void add(int lx, int rx, LL x) { add(1, 1, n, lx, rx, x); }

    LL query(int lx, int rx) { return query(1, 1, n, lx, rx); }
};

const int N = 1e5 + 5;
int n, m, root, a[N], head[N], to[N * 2], nxt[N * 2], tot;
int fa[N], dep[N], siz[N], son[N], dfn[N], top[N];

inline void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs1(int p) {
    siz[p] = 1;
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa[p]) {
            continue;
        }
        fa[q] = p;
        dep[q] = dep[p] + 1;
        dfs1(q);
        if (siz[q] > siz[son[p]]) {
            son[p] = q;
        }
        siz[p] += siz[q];
    }
}

void dfs2(int p, int tp) {
    top[p] = tp;
    dfn[p] = ++tot;
    if (son[p]) {
        dfs2(son[p], tp);
    }
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa[p] || q == son[p]) {
            continue;
        }
        dfs2(q, q);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> root >> mod;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs1(root);
    tot = 0;
    dfs2(root, root);

    SegmentTree st(n);
    for (int i = 1; i <= n; i++) {
        st.a[dfn[i]] = a[i] % mod;
    }
    st.build();

    int op, x, y, z;
    while (m--) {
        cin >> op;
        if (op == 1) {
            cin >> x >> y >> z;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) {
                    swap(x, y);
                }
                st.add(dfn[top[x]], dfn[x], z);
                x = fa[top[x]];
            }
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            st.add(dfn[y], dfn[x], z);
        } else if (op == 2) {
            LL ans = 0;
            cin >> x >> y;
            while (top[x] != top[y]) {
                if (dep[top[x]] < dep[top[y]]) {
                    swap(x, y);
                }
                ans = (ans + st.query(dfn[top[x]], dfn[x])) % mod;
                x = fa[top[x]];
            }
            if (dep[x] < dep[y]) {
                swap(x, y);
            }
            ans = (ans + st.query(dfn[y], dfn[x])) % mod;
            cout << ans << endl;
        } else if (op == 3) {
            cin >> x >> z;
            st.add(dfn[x], dfn[x] + siz[x] - 1, z);
        } else {
            cin >> x;
            cout << st.query(dfn[x], dfn[x] + siz[x] - 1) << endl;
        }
    }

    return 0;
}
```

<div style="page-break-after: always;"></div>


## 杂项

### pb_ds.cpp

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // 各种类的定义 必须引用
#include <ext/pb_ds/hash_policy.hpp> // 哈希表
#include <ext/pb_ds/priority_queue.hpp> // 堆
#include <ext/pb_ds/tree_policy.hpp> // 红黑树
using namespace __gnu_pbds;
using namespace std;
#define LL long long

int n;
gp_hash_table<LL, int> mp;
__gnu_pbds::priority_queue<int> que;
tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> rbt;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    cout << n << endl;

    return 0;
}
```
### 对拍.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int cnt=0;
    while (1){ //一直循环，直到找到不一样的数据
        system("data.exe > in");
        system("test.exe < in > A.txt");
        system("std.exe < in > B.txt");
        cnt++;
        if (system("fc A.txt B.txt")){ //当 fc 返回 1 时，说明这时数据不一样
            cout<<"test "<<cnt<<" WA\n"; //不一样就跳出循环
            break;
        }                       
        else cout<<"test "<<cnt<<" AC\n";
    }
    return 0;
}
```
### 树哈希.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using ULL = unsigned long long;

const int N = 1000005;
const ULL base = std::chrono::steady_clock::now().time_since_epoch().count();
int n, head[N], to[N * 2], nxt[N * 2], tot;
ULL th[N];
set<ULL> tree;

inline void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

inline ULL shift(ULL x) {
    x ^= base;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= base;
    return x;
}

void dfs(int p, int fa) {
    th[p] = 1;
    for (int i = head[p]; i; i = nxt[i]) {
        int q = to[i];
        if (q == fa) {
            continue;
        }
        dfs(q, p);
        th[p] += shift(th[q]);
    }
    tree.insert(th[p]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    int u, v;
    for (int i = 1; i < n; i++) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs(1, 0);
    cout << tree.size() << endl;

    return 0;
}
```
### 集合哈希.cpp

```cpp
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

```
### 高精度数.cpp

```cpp
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

const int bit = 4, base = 1e4, LIM = 20;

struct BigInt {
    int len;
    bool sign;
    vector<int> val;

    BigInt() {
        len = sign = 0;
        val.clear();
    }

    BigInt(LL x) {
        clear();
        sign = x < 0;
        x = abs(x);
        while (x) {
            len++;
            val.push_back(x % base);
            x /= base;
        }
    }

    BigInt(const BigInt &x) { *this = x; }

    BigInt(const string &num) {
        clear();
        int gg = 0;
        if (num[0] == '-') {
            sign = gg = 1;
        }
        int i;
        for (i = num.length(); i - bit >= gg; i -= bit) {
            int tmp = 0;
            for (int j = bit; j >= 1; j--) {
                tmp *= 10;
                tmp += num[i - j] - '0';
            }
            val.push_back(tmp);
        }
        if (i > gg) {
            int tmp = 0;
            for (int j = gg; j < i; j++) {
                tmp *= 10;
                tmp += num[j] - '0';
            }
            val.push_back(tmp);
        }
        len = val.size();
    }

    void operator=(const BigInt &x) {
        len = x.len;
        sign = x.sign;
        val = x.val;
    }

    inline void clear() {
        len = sign = 0;
        val.clear();
    }

    inline void fix() {
        while (len && !val.back()) {
            len--;
            val.pop_back();
        }
        if (!len) {
            sign = 0;
        }
    }

    inline void print() {
        if (len) {
            if (sign) {
                cout << '-';
            }
            cout << val.back();
            for (int i = len - 2; i >= 0; i--) {
                cout << setw(4) << setfill('0') << val[i];
            }
        } else {
            cout << 0;
        }
    }

    static int cmp_abs(const BigInt &a, const BigInt &b) {
        if (a.len != b.len) {
            return a.len < b.len ? -1 : 1;
        }
        for (int i = a.len - 1; i >= 0; i--) {
            if (a.val[i] != b.val[i]) {
                return a.val[i] < b.val[i] ? -1 : 1;
            }
        }
        return 0;
    }

    static int cmp(const BigInt &a, const BigInt &b) {
        if (a.sign != b.sign) {
            return b.sign - a.sign;
        }
        return a.sign ? -cmp_abs(a, b) : cmp_abs(a, b);
    }

    void add_abs(const BigInt &x) {
        val.resize(len = max(len, x.len) + 1);
        for (int i = 0; i < x.len; ++i) {
            val[i] += x.val[i];
            if (val[i] >= base) {
                val[i] -= base;
                val[i + 1]++;
            }
        }
        for (int i = x.len; i < len && val[i] >= base; i++) {
            val[i] -= base;
            val[i + 1]++;
        }
        fix();
    }

    void sub_abs(const BigInt &x) {
        if (cmp_abs(*this, x) < 0) {
            BigInt tmp = *this;
            *this = x;
            sign = tmp.sign;
            sub_abs(tmp);
            sign ^= 1;
            return;
        }
        for (int i = 0; i < x.len; i++) {
            val[i] -= x.val[i];
            if (val[i] & 0x80000000) {
                val[i] += base;
                val[i + 1]--;
            }
        }
        for (int i = x.len; i < len && (val[i] & 0x80000000); i++) {
            val[i] += base;
            val[i + 1]--;
        }
        fix();
    }

    void add(const BigInt &x) {
        if (sign ^ x.sign) {
            sub_abs(x);
        } else {
            add_abs(x);
        }
    }

    void sub(const BigInt &x) {
        if (sign ^ x.sign) {
            add_abs(x);
        } else {
            sub_abs(x);
        }
    }

    void mul(const BigInt &x) {
        vector<int> vec = val;
        val.assign(val.size(), 0);
        val.resize(x.len + len);
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < x.len; j++) {
                LL tmp = (LL)vec[i] * x.val[j] + val[i + j];
                val[i + j] = tmp % base;
                val[i + j + 1] += tmp / base;
            }
        }
        len += x.len;
        sign ^= x.sign;
        fix();
    }

    void mul_fast(const BigInt &x) {
        if (!x.len || !len) {
            clear();
            return;
        }

        int siz = len + x.len - 2;
        vector<complex<db>> a(len), b(x.len);
        for (int i = 0; i < len; i++) {
            a[i] = val[i];
        }
        for (int i = 0; i < x.len; i++) {
            b[i] = x.val[i];
        }
        fft(a, siz, 1);
        fft(b, siz, 1);
        vector<complex<db>> c(a.size());
        for (int i = 0; i < a.size(); i++) {
            c[i] = a[i] * b[i];
        }
        fft(c, siz, -1);

        val.resize(c.size());
        len = c.size();
        LL tmp = 0;
        for (int i = 0; i < c.size(); ++i) {
            tmp += c[i].real();
            val[i] = tmp % base;
            tmp /= base;
        }
        while (tmp) {
            len++;
            val.push_back(tmp % base);
            tmp /= base;
        }
        sign ^= x.sign;
        fix();
    }

    void mul(int x) {
        if (x & 0x80000000) {
            x = -x;
            sign ^= 1;
        }
        LL tmp = 0;
        for (int i = 0; i < len; ++i) {
            tmp += (LL)val[i] * x;
            val[i] = tmp % base;
            tmp /= base;
        }
        while (tmp) {
            len++;
            val.push_back(tmp % base);
            tmp /= base;
        }
        fix();
    }

    void div(const BigInt &x, BigInt &remainder) {
        remainder = *this;
        if (x.len > len) {
            clear();
            return;
        }
        val.assign(val.size(), 0);
        int shift = len - x.len;
        while (shift >= 0) {
            int l = 0, r = base - 1;
            BigInt tmp, now;
            now.val.assign(remainder.val.begin() + shift, remainder.val.end());
            now.len = remainder.len - shift;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                tmp = x;
                tmp.mul(mid);
                if (cmp_abs(tmp, now) <= 0) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            val[shift] = l;
            tmp = x;
            tmp.mul(l);
            now.sub_abs(tmp);
            for (int i = 0; i < now.len; i++) {
                remainder.val[shift + i] = now.val[i];
            }
            remainder.len = now.len + shift;
            remainder.val.resize(remainder.len);
            shift--;
        }
        sign ^= x.sign;
        fix();
    }

    void div(int x) {
        if (x & 0x80000000) {
            x = -x;
            sign ^= 1;
        }
        LL tmp = 0;
        for (int i = len - 1; i >= 0; i--) {
            tmp = tmp * base + val[i];
            val[i] = tmp / x;
            tmp %= x;
        }
        fix();
    }
};

BigInt operator+(const BigInt &a, const BigInt &b) {
    BigInt c(a);
    c.add(b);
    return c;
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    BigInt c(a);
    c.sub(b);
    return c;
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt c(a);
    if (a.len <= LIM || b.len <= LIM) {
        c.mul(b);
    } else {
        c.mul_fast(b);
    }
    return c;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
    BigInt c(a), r;
    c.div(b, r);
    return c;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
    BigInt c(a), r;
    c.div(b, r);
    return r;
}

string s1, s2;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> s1 >> s2;
    BigInt a(s1), b(s2);

    (a + b).print();
    cout << endl;
    (a - b).print();
    cout << endl;
    (a * b).print();
    cout << endl;
    (a / b).print();
    cout << endl;
    (a % b).print();
    cout << endl;

    return 0;
}
```

<div style="page-break-after: always;"></div>


## 网络流与二分图

### 二分图最大匹配.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e3 + 5;
int n1, n2, m, match[N];
vector<int> e[N];
bool vis[N];

inline void add(int u, int v) {
    e[u].emplace_back(v);
    e[v].emplace_back(u);
}

bool dfs(int p) {
    for (int q : e[p]) {
        if (vis[q]) {
            continue;
        }
        vis[q] = true;
        if (!match[q] || dfs(match[q])) {
            match[p] = q;
            match[q] = p;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n1 >> n2 >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        v += n1;
        add(u, v);
    }

    int cnt = 0;
    for (int i = 1; i <= n1; i++) {
        for (int j = n1 + 1; j <= n1 + n2; j++) {
            vis[j] = false;
        }
        cnt += dfs(i);
    }

    cout << cnt << endl;

    return 0;
}
```
### 二分图最大权完美匹配.cpp

```cpp
// KM算法，当且仅当图中存在完备匹配时可用（求完美匹配，但可通过添加虚边求非完美匹配）
// 复杂度 O(n^3)，优于费用流
// 判无解：添加虚边，边权为-INF
// 非完美匹配：添加虚边，边权为0

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define mp make_pair

const int N = 1e3 + 5;
const LL INF = 1e12;
int n, m, match[N], pre[N];  // pre: 右端点被谁最早到达
LL val[N], slack[N];         // slack: 顶标减少多少可以加入交错树
vector<pair<int, LL>> e[N];
bool vis[N];

inline void add(int u, int v, LL w) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
}

void update(int p) {
    while (p) {
        int tmp = match[pre[p]];
        match[p] = pre[p];
        match[pre[p]] = p;
        p = tmp;
    }
}

void bfs(int s) {
    for (int i = 1; i <= n; i++) {
        vis[i] = vis[n + i] = 0;
        slack[n + i] = INF;
    }
    queue<int> que;
    que.push(s);

    while (true) {
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            vis[p] = true;
            for (auto [q, len] : e[p]) {
                if (vis[q]) {
                    continue;
                }
                if (val[p] + val[q] - len < slack[q]) {
                    slack[q] = val[p] + val[q] - len;
                    pre[q] = p;  // 由于右端点q可能在后面由于顶标改变而进入交错树，记录遍历中的前驱pre用于更新match
                    if (!slack[q]) {  // 边可用
                        vis[q] = true;
                        if (!match[q]) {
                            update(q);
                            return;
                        } else {
                            que.push(match[q]);
                        }
                    }
                }
            }
        }

        LL delta = INF;
        for (int i = n + 1; i <= n * 2; i++) {
            if (!vis[i]) {
                delta = min(delta, slack[i]);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (vis[i]) {
                val[i] -= delta;
            }
            if (vis[n + i]) {
                val[n + i] += delta;
            } else {  // 维护由于顶标val改变引起的slack值变化
                slack[n + i] -= delta;
            }
        }

        for (int i = n + 1; i <= n * 2; i++) {
            if (!vis[i] && !slack[i]) {
                vis[i] = true;
                if (!match[i]) {
                    update(i);
                    return;
                } else {
                    que.push(match[i]);
                }
            }
        }
    }
}

LL KM() {
    for (int i = 1; i <= n; i++) {
        val[i] = -INF;
        val[n + i] = 0;
        for (auto [j, len] : e[i]) {
            val[i] = max(val[i], len);
        }
    }

    for (int i = 1; i <= n; i++) {
        bfs(i);
    }

    LL res = 0;
    for (int i = 1; i <= n; i++) {
        for (auto [j, len] : e[i]) {
            if (j == match[i]) {
                res += len;
                break;
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        v += n;
        add(u, v, w);
    }

    cout << KM() << endl;
    for (int i = n + 1; i <= n * 2; i++) {
        cout << match[i] << ' ';
    }
    cout << endl;

    return 0;
}
```
### 最小费用最大流.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5e3 + 5;
const LL INF = 1e18;
int n, m;

namespace Flow {
    struct edge {
        int to, nxt;  // 剩余容量
        LL cost, flow;
        edge(int _to = 0, int _nxt = 0, LL _cost = 0, LL _flow = 0) : to(_to), nxt(_nxt), cost(_cost), flow(_flow) {}
    };

    int n, s, t, head[N], tot = 1;
    vector<edge> e;
    LL minf[N], dis[N], pre[N];
    bool inq[N];

    // clang-format off
    inline void add(int u, int v, LL w, LL f) {
        e.emplace_back(v, head[u], w, f); head[u] = ++tot;
        e.emplace_back(u, head[v], -w, 0); head[v] = ++tot;
    }

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 1; i <= n; i++) {
            head[i] = 0;
        }
        tot = 1;
        e.resize(2);
    }
    // clang-format on

    bool spfa() {
        for (int i = 1; i <= n; i++) {
            inq[i] = false;
            dis[i] = INF;
        }
        queue<int> que;
        que.push(s);
        inq[s] = true;
        dis[s] = 0;
        minf[s] = INF;

        while (!que.empty()) {
            int p = que.front();
            que.pop();
            inq[p] = false;
            for (int i = head[p]; i; i = e[i].nxt) {
                int q = e[i].to;
                if (!e[i].flow) {
                    continue;
                }
                if (dis[p] + e[i].cost < dis[q]) {
                    dis[q] = dis[p] + e[i].cost;
                    pre[q] = i;
                    minf[q] = min(minf[p], e[i].flow);
                    if (!inq[q]) {
                        que.push(q);
                        inq[q] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    pair<LL, LL> EK() {
        LL maxflow = 0, res = 0;

        auto update = [&maxflow, &res]() {
            LL f = minf[t];
            for (int p = t; p != s; p = e[pre[p] ^ 1].to) {
                int from = pre[p];
                e[from].flow -= f;
                e[from ^ 1].flow += f;
            }
            maxflow += f;
            res += dis[t] * f;
        };

        while (spfa()) {
            update();
        }

        return {maxflow, res};
    }
}  // namespace Flow

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    Flow::init(n, s, t);
    for (int i = 1, u, v, w, f; i <= m; i++) {
        cin >> u >> v >> f >> w;
        Flow::add(u, v, w, f);
    }

    auto [maxflow, res] = Flow::EK();

    cout << maxflow << ' ' << res << endl;

    return 0;
}
```
### 有负环的费用流.cpp

```cpp
// 带负环时，需要建立虚拟源汇点，并将负边初始满流

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5e3 + 5;
const LL INF = 1e18;
int n, m;

namespace Flow {
    struct edge {
        int to, nxt;  // 剩余容量
        LL cost, flow;
        edge(int _to = 0, int _nxt = 0, LL _cost = 0, LL _flow = 0) : to(_to), nxt(_nxt), cost(_cost), flow(_flow) {}
    };

    int n, s, t, ss, tt, head[N], tot = 1;
    vector<edge> e;
    LL minf[N], dis[N], pre[N], sum[N], res0;
    bool inq[N];

    // clang-format off
    inline void add(int u, int v, LL w, LL f) {
        if (w < 0){  // 初始满流
            sum[v] += f; sum[u] -= f;
            res0 += w * f;
            swap(u, v);
            w = -w;
        }
        e.emplace_back(v, head[u], w, f); head[u] = ++tot;
        e.emplace_back(u, head[v], -w, 0); head[v] = ++tot;
    }

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 1; i <= n; i++) {
            sum[i] = head[i] = 0;
        }
        res0 = 0;
        tot = 1;
        e.resize(2);
    }
    // clang-format on

    bool spfa(int s, int t) {
        for (int i = 1; i <= n; i++) {
            inq[i] = false;
            dis[i] = INF;
        }
        queue<int> que;
        que.push(s);
        inq[s] = true;
        dis[s] = 0;
        minf[s] = INF;

        while (!que.empty()) {
            int p = que.front();
            que.pop();
            inq[p] = false;
            for (int i = head[p]; i; i = e[i].nxt) {
                int q = e[i].to;
                if (!e[i].flow) {
                    continue;
                }
                if (dis[p] + e[i].cost < dis[q]) {
                    dis[q] = dis[p] + e[i].cost;
                    pre[q] = i;
                    minf[q] = min(minf[p], e[i].flow);
                    if (!inq[q]) {
                        que.push(q);
                        inq[q] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    void build() {
        ss = n + 1;
        tt = n + 2;
        for (int i = 1; i <= n; i++) {
            if (sum[i] > 0) {
                add(ss, i, 0, sum[i]);
            } else if (sum[i] < 0) {
                add(i, tt, 0, -sum[i]);
            }
        }
        n += 2;
    }

    pair<LL, LL> EK() {
        LL maxflow = 0, res = 0;

        auto update = [&maxflow, &res](int s, int t) {
            LL f = minf[t];
            for (int p = t; p != s; p = e[pre[p] ^ 1].to) {
                int from = pre[p];
                e[from].flow -= f;
                e[from ^ 1].flow += f;
            }
            maxflow += f;
            res += dis[t] * f;
        };

        while (spfa(ss, tt)) {
            update(ss, tt);
        }
        maxflow = 0;
        while (spfa(s, t)) {
            update(s, t);
        }

        return {maxflow, res0 + res};
    }
}  // namespace Flow

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    Flow::init(n, s, t);
    for (int i = 1, u, v, w, f; i <= m; i++) {
        cin >> u >> v >> f >> w;
        Flow::add(u, v, w, f);
    }
    Flow::build();

    auto [maxflow, res] = Flow::EK();

    cout << maxflow << ' ' << res << endl;

    return 0;
}
```
### 网络最大流.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 205, INF = 0x7fffffff;
int n, m;

namespace Flow {
    struct edge {
        int to, nxt, flow;  // 剩余容量
        edge(int _to = 0, int _nxt = 0, int _flow = 0) : to(_to), nxt(_nxt), flow(_flow) {}
    };

    int n, s, t, head[N], cur[N], tot = 1;
    vector<edge> e;
    int dep[N], num[N];

    // clang-format off
    inline void add(int u, int v, int f) {
        e.emplace_back(v, head[u], f); head[u] = ++tot;
        e.emplace_back(u, head[v], 0); head[v] = ++tot;
    }

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 1; i <= n; i++) {
            head[i] = 0;
        }
        tot = 1;
        e.resize(2);
    }
    // clang-format on

    void build() {
        for (int i = 1; i <= n; i++) {
            dep[i] = 0;
        }

        queue<int> que;
        que.push(t);
        dep[t] = 1;
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            num[dep[p]]++;
            for (int i = head[p]; i; i = e[i].nxt) {
                int q = e[i].to;
                if (!dep[q]) {
                    dep[q] = dep[p] + 1;
                    que.push(q);
                }
            }
        }
    }

    int dinic(int p, int lim) {  // 可增广流量
        if (p == t) {
            return lim;
        }
        int used = 0;
        for (int i = cur[p]; i; i = e[i].nxt) {
            int q = e[i].to;
            if (e[i].flow && dep[q] == dep[p] - 1) {
                cur[p] = i;
                int f = dinic(q, min(lim - used, e[i].flow));
                if (f) {
                    e[i].flow -= f;
                    e[i ^ 1].flow += f;
                    used += f;
                    if (used == lim) {
                        return used;
                    }
                }
            }
        }

        if (--num[dep[p]] == 0) {
            dep[s] = n + 1;
        }
        num[++dep[p]]++;

        return used;  // 增广流量
    }

    LL work(int s, int t) {
        LL maxflow = 0;
        int f;
        build();
        while (dep[s] <= n) {
            for (int i = 1; i <= n; i++) {
                cur[i] = head[i];
            }
            maxflow += dinic(s, INF);
        }
        return maxflow;
    }
}  // namespace Flow

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int s, t;
    cin >> n >> m >> s >> t;
    Flow::init(n, s, t);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        Flow::add(u, v, w);
    }

    cout << Flow::work(s, t) << endl;

    return 0;
}
```

<div style="page-break-after: always;"></div>


## 计算几何

### 平面最近点对.cpp

```cpp
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
```
### 点.cpp

```cpp
#include <bits/stdc++.h>
using namespace std;
using db = double;  // 换long double时，需要同时替换alpha、abs、getTheta函数
const db eps = 1e-9;

inline int sign(db x) { return x < -eps ? -1 : x > eps; }
inline int cmp(db x, db y) { return sign(x - y); }

// 点 Point
struct Point {
    db x, y;

    Point() : x(0), y(0) {}
    Point(db _x, db _y) : x(_x), y(_y) {}

    Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator*(const db &d) const { return {x * d, y * d}; }
    Point operator/(const db &d) const { return {x / d, y / d}; }

    bool operator<(Point p) const {
        int gg = cmp(x, p.x);
        if (gg) {
            return gg == -1;
        } else {
            return cmp(y, p.y) == -1;
        }
    }

    // 这里的比较可能不满足传递性，因为这是基于eps的比较
    bool operator==(Point p) const { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }

    db dot(Point p) { return x * p.x + y * p.y; }
    db det(Point p) { return x * p.y - y * p.x; }

    db alpha() { return atan2(y, x); }
    db abs() { return sqrt(abs2()); }
    db abs2() { return x * x + y * y; }
    Point unit() { return *this / abs(); }
    Point rot90() { return {-y, x}; }
    Point rot(db theta) { return {x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)}; }
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

inline db dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
inline db det(Point p, Point q) { return p.x * q.y - p.y * q.x; }  // 判断 向量p 是否在 向量q 的顺时针方向
inline db dis(Point p, Point q) { return (p - q).abs(); }
// 判断 向量p1p2 是否在 向量p1p3 的顺时针方向
inline db cross(Point p1, Point p2, Point p3) { return det(p2 - p1, p3 - p1); }
inline int cross_S(Point p1, Point p2, Point p3) { return sign(cross(p1, p2, p3)); }
```
### 线.cpp

```cpp
// 判断 直线p1p2 和 直线q1q2 是否相交
bool isLL(Point p1, Point p2, Point q1, Point q2) { return sign(cross(q1, q2, p1) - cross(q1, q2, p2)) != 0; }

// 判断 直线p1p2 和 直线q1q2 是否严格相交
bool isLL_strict(Point p1, Point p2, Point q1, Point q2) { return cross_S(p1, p2, q1) * cross_S(p1, p2, q2) < 0; }

// 求交点
Point getLL(Point p1, Point p2, Point q1, Point q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 判断区间是否相交
bool intersect(db l1, db r1, db l2, db r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}

// 线段相交
bool isSS(Point p1, Point p2, Point q1, Point q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) && intersect(p1.y, p2.y, q1.y, q2.y) &&
           cross_S(p1, p2, q1) * cross_S(p1, p2, q2) <= 0 && cross_S(q1, q2, p1) * cross_S(q1, q2, p2) <= 0;
}

// 线段严格相交(不能交于端点)
bool isSS_strict(Point p1, Point p2, Point q1, Point q2) {
    return cross_S(p1, p2, q1) * cross_S(p1, p2, q2) < 0 && cross_S(q1, q2, p1) * cross_S(q1, q2, p2) < 0;
}

// x 是否在 l 和 r 之间
bool isMiddle(db x, db l, db r) {
    if (l > r) swap(l, r);
    return cmp(l, x) <= 0 && cmp(x, r) <= 0;
}

// 点q 是否在 点p1 和 点p2 之间
bool isMiddle(Point q, Point p1, Point p2) { return isMiddle(q.x, p1.x, p2.x) && isMiddle(q.y, p1.y, p2.y); }

// 点q 是否在 直线p1p2 上
bool onLine(Point q, Point p1, Point p2) { return cross_S(p1, p2, q) == 0; }

// 点q 是否在 线段p1p2 上
bool onSeg(Point q, Point p1, Point p2) { return cross_S(p1, p2, q) == 0 && isMiddle(q, p1, p2); }

// 点q 是否在 线段p1p2 上(严格)
bool onSeg_strict(Point q, Point p1, Point p2) {
    return cross_S(p1, p2, q) == 0 && sign(dot(q - p1, p1 - p2)) * sign(dot(q - p2, p1 - p2));
}

// 求 q 到 直线p1p2 的投影(垂足)
Point proj(Point q, Point p1, Point p2) {
    Point dir = p2 - p1;
    return p1 + dir * (dot(dir, q - p1) / dir.abs2());
}

// 求 q 以 直线p1p2 为轴的反射
Point reflect(Point q, Point p1, Point p2) { return proj(p1, p2, q) * 2 - q; }

// 求 q 到 线段p1p2 的最小距离
db disPS(Point q, Point p1, Point p2) {
    if (p1 == p2) {
        return dis(p1, q);
    }
    Point v1 = p2 - p1, v2 = q - p1, v3 = q - p2;
    if (sign(dot(v1, v2)) == -1) {
        return v2.abs();
    } else if (sign(dot(v1, v3)) == 1) {
        return v3.abs();
    } else {
        return fabs(det(v1, v2) / v1.abs());
    }
}

// 求 线段p1p2 与 线段q1q2 的距离
db disSS(Point p1, Point p2, Point q1, Point q2) {
    if (isSS(p1, p2, q1, q2)) {
        return 0;
    } else {
        return min(min(disPS(p1, p2, q1), disPS(p1, p2, q2)), min(disPS(q1, q2, p1), disPS(q1, q2, p2)));
    }
}
```

<div style="page-break-after: always;"></div>
