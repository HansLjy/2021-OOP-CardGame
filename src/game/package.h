#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

using namespace std;

#define rec_server -1

class Header {
    bool suc;
    int rec;
    int spe;
public:
    Header(bool s, int r, int sp = 0);
    bool IsSuccess() const;
    int GetRecipient() const;
    int GetSpecial() const;
};

class Package {
    Header head;
    string data;
public:
    Package(const Header &h, const string &d);
    Header GetHeader() const;
    string GetData() const;
};

#endif
