#ifndef CLOCKINT_H
#define CLOCKINT_H

template <int m> class ci {
    int val;
public:
    ci(int x = 0);
    operator int() const;
    ci<m> operator++();
    ci<m> operator++(int);
    ci<m> operator--();
    ci<m> operator--(int);
    ci<m> operator+=(int x);
    ci<m> operator-=(int x);
    ci<m> operator+(int x) const;
    ci<m> operator-(int x) const;
};

#endif
