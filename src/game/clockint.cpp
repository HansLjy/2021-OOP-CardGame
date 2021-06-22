#include "clockint.h"

template <int m> ci<m>::ci(int x): val(x) {
    val = x % m;
    if (val < 0) {
        val += m;
    }
}
template <int m> ci<m>::operator int() const {
    return val;
}
template <int m> ci<m> ci<m>::operator++() {
    if (++val == m) {
        val = 0;
    }
    return *this;
}
template <int m> ci<m> ci<m>::operator++(int) {
    ci<m> r = *this;
    if (++val == m) {
        val = 0;
    }
    return r;
}
template <int m> ci<m> ci<m>::operator--() {
    if (!val--) {
        val = m - 1;
    }
    return *this;
}
template <int m> ci<m> ci<m>::operator--(int) {
    ci<m> r = *this;
    if (!val--) {
        val = m - 1;
    }
    return r;
}
template <int m> ci<m> ci<m>::operator+=(int x) {
    val += x;
    val %= m;
    if (val < 0) {
        val += m;
    }
    return *this;
}
template <int m> ci<m> ci<m>::operator-=(int x) {
    return *this += -x;
}
template <int m> ci<m> ci<m>::operator+(int x) const {
    ci<m> r = *this;
    return r += x;
}
template <int m> ci<m> ci<m>::operator-(int x) const {
    return *this + -x;
}

template class ci<3>;
template class ci<4>;

// test code, expected all 1's

// #include <iostream>
// using namespace std;
// int main() {
//     ci<10> a = 1;
//     cout << a;
//     cout << ((a = 8) == 8);
//     cout << (a == 8);
//     cout << (++a == 9);
//     cout << (a == 9);
//     cout << (++a == 0);
//     cout << (a == 0);
//     cout << (++a == 1);
//     cout << (a == 1);
//     cout << (++a == 2);
//     cout << (a == 2);
//     cout << (--a == 1);
//     cout << (a == 1);
//     cout << (--a == 0);
//     cout << (a == 0);
//     cout << (--a == 9);
//     cout << (a == 9);
//     cout << ((a += 1) == 0);
//     cout << ((a -= 1) == 9);
//     cout << ((a += 101) == 0);
//     cout << ((a -= 201) == 9);
//     cout << (a + 1 == 0);
//     cout << (a == 9);
//     cout << (a - 11 == 8);
//     cout << (a == 9);
//     cout << (1 + a == 10);
//     cout << (1 - a == -8);
//     cout << (ci<5>() + a == 4);
//     cout << (ci<9>() != a);
//     cout << (ci<11>(9) == a);
//     return 0;
// }
