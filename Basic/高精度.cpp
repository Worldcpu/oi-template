#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int MN = 3520;
string a,b;

struct Bigint {
    bool minus;
    int num[MN];

    Bigint() {
        minus = false;
        memset(num, 0, sizeof(num));
    }

    template<typename T>
    Bigint(T x) {
        minus = false;
        memset(num, 0, sizeof(num));
        set(x);
    }

    void clear() {
        minus = false;
        memset(num, 0, sizeof(num));
    }

    bool isZero() const {
        for (int i = 0; i < MN; ++i) if (num[i] != 0) return false;
        return true;
    }

    void set(const string &st) {
        clear();
        if (st.empty()) return;
        int start = 0;
        if (st[0] == '-') {
            minus = true;
            start = 1;
        } else {
            minus = false;
            start = 0;
        }
        int idx = 0;
        for (int i = (int)st.size() - 1; i >= start && idx < MN; --i, ++idx) {
            if (!isdigit(st[i])) { clear(); return; } 
            num[idx] = st[i] - '0';
        }
        if (isZero()) minus = false;
    }

    template<typename T>
    void set(T x) {
        clear();
        if (x == 0) { num[0] = 0; minus = false; return; }
        if (x < 0) { minus = true; x = -x; }
        else minus = false;
        int idx = 0;
        while (x && idx < MN) {
            num[idx++] = int(x % 10);
            x /= 10;
        }
        if (isZero()) minus = false;
    }

    void print(bool flag = true) const {
        if (minus && !isZero()) cout << '-';
        int i;
        for (i = MN - 1; i >= 0; --i) {
            if (num[i] != 0) break;
        }
        if (i < 0) { cout << '0'; if (flag) cout << '\n'; else cout << ' '; return; }
        for (; i >= 0; --i) cout << num[i];
        if (flag) cout << '\n'; else cout << ' ';
    }

    ll toll() const {
        ll ret = 0;
        int i;
        for (i = MN - 1; i >= 0; --i) if (num[i] != 0) break;
        for (; i >= 0; --i) {
            ret = ret * 10 + num[i];
        }
        return minus ? -ret : ret;
    }

    friend bool operator==(const Bigint &x, const Bigint &y) {
        if (x.minus != y.minus) return false;
        for (int i = 0; i < MN; ++i) if (x.num[i] != y.num[i]) return false;
        return true;
    }

    friend bool operator<(const Bigint &x, const Bigint &y) {
        if (x.minus != y.minus) return x.minus; 
        if (!x.minus) {
            for (int i = MN - 1; i >= 0; --i) {
                if (x.num[i] != y.num[i]) return x.num[i] < y.num[i];
            }
            return false;
        } else {
            for (int i = MN - 1; i >= 0; --i) {
                if (x.num[i] != y.num[i]) return x.num[i] > y.num[i];
            }
            return false;
        }
    }

    friend bool operator<=(const Bigint &x, const Bigint &y) {
        return (x < y) || (x == y);
    }

    friend bool operator>=(const Bigint &x, const Bigint &y) {
        return (y < x) || (x == y);
    }

    friend bool operator>(const Bigint &x, const Bigint &y) {
        return y < x;
    }

    friend Bigint operator-(const Bigint &x) {
        Bigint tmp = x;
        if (!tmp.isZero()) tmp.minus = !tmp.minus;
        else tmp.minus = false;
        return tmp;
    }

    Bigint abs() const {
        Bigint t = *this;
        t.minus = false;
        return t;
    }

    friend Bigint operator+(const Bigint &x, const Bigint &y) {
        if (x.minus == y.minus) {
            Bigint ret;
            ret.minus = x.minus;
            int carry = 0;
            for (int i = 0; i < MN; ++i) {
                int s = x.num[i] + y.num[i] + carry;
                ret.num[i] = s % 10;
                carry = s / 10;
            }
            if (ret.isZero()) ret.minus = false;
            return ret;
        } else {
            if (x.minus) {
                return y - x.abs();
            } else {
                return x - y.abs();
            }
        }
    }

    friend Bigint operator-(const Bigint &x, const Bigint &y) {
        if (x.minus != y.minus) {
            Bigint t = x + (-y);
            return t;
        }
        if (!x.minus) {
            if (x < y) return -(y - x);
            Bigint ret;
            int borrow = 0;
            for (int i = 0; i < MN; ++i) {
                int d = x.num[i] - y.num[i] - borrow;
                if (d < 0) { d += 10; borrow = 1; } else borrow = 0;
                ret.num[i] = d;
            }
            if (ret.isZero()) ret.minus = false;
            return ret;
        } else {
            return (y.abs() - x.abs());
        }
    }

    friend Bigint operator*(const Bigint &x, const Bigint &y) {
        Bigint ret;
        if (x.isZero() || y.isZero()) { ret.clear(); return ret; }
        ret.minus = x.minus ^ y.minus;
        for (int i = 0; i < MN; ++i) {
            if (x.num[i] == 0) continue;
            long long carry = 0;
            for (int j = 0; j + i < MN; ++j) {
                long long cur = ret.num[i + j] + 1LL * x.num[i] * y.num[j] + carry;
                ret.num[i + j] = int(cur % 10);
                carry = cur / 10;
            }
        }
        if (ret.isZero()) ret.minus = false;
        return ret;
    }

    friend Bigint operator*(const Bigint &x, const int &yy) {
        Bigint ret;
        if (x.isZero() || yy == 0) { ret.clear(); return ret; }
        long long y = yy;
        bool yneg = false;
        if (y < 0) { yneg = true; y = -y; }
        ret.minus = x.minus ^ yneg;
        long long carry = 0;
        for (int i = 0; i < MN; ++i) {
            long long cur = 1LL * x.num[i] * y + carry + ret.num[i];
            ret.num[i] = int(cur % 10);
            carry = cur / 10;
        }
        if (ret.isZero()) ret.minus = false;
        return ret;
    }

    pair<Bigint, int> divint(int y) const {
        Bigint ret;
        if (y == 0) throw runtime_error("division by zero");
        long long ay = y;
        bool yneg = false;
        if (ay < 0) { yneg = true; ay = -ay; }
        long long rem = 0;
        for (int i = MN - 1; i >= 0; --i) {
            rem = rem * 10 + num[i];
            ret.num[i] = int(rem / ay);
            rem %= ay;
        }
        ret.minus = minus ^ yneg;
        if (ret.isZero()) ret.minus = false;
        return {ret, int(rem)};
    }

    string toString() const {
        stringstream ss;
        if (minus && !isZero()) ss << '-';
        int i;
        for (i = MN - 1; i >= 0; --i) if (num[i] != 0) break;
        if (i < 0) return "0";
        for (; i >= 0; --i) ss << char('0' + num[i]);
        return ss.str();
    }
}x,y;


int main(){
    cin>>a>>b;
    x.set(a);
    y.set(b);
    (x*y).print();

    return 0;
}