#ifndef DISCONNECTION_H
#define DISCONNECTION_H

#include "clockint.h"

template <int np> class Disconn {
    ci<np> index;
public:
    Disconn(ci<np> i);
    ci<np> GetIndex() const;
};

#endif
