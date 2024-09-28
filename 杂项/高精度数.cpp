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