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