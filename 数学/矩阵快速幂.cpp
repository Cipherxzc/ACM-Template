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
