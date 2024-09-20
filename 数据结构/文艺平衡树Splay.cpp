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