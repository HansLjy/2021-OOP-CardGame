// This is an incomplete version, containing only the functions used by the game module

#ifndef PORT_H
#define PORT_H

#include "package.h"

class Port {
public:
    void SendGameMsg(const Package &p) const; // sends p according to its header
    Package CollectGameMsg(int s) const; // collect a package from the sender whose index is s
    // If the connection to the sender fails, in which case we assume he/she has quit the game, return a package with false success code and empty payload.
    // If the connection succeeds, in which case he/she may be still not sending any packages, keep waiting until receiving the first package and return it.
};

class Server: public Port {};

#endif
