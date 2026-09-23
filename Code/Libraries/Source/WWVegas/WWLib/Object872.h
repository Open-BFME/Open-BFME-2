#ifndef BFME_OBJECT872_H
#define BFME_OBJECT872_H

// Target layout reconstructed from its copy constructor; original owner unknown.
// The member copy helpers only copy fixed storage and cannot throw.
#include <vector>
#include <stddef.h>

extern "C" void *memcpy(void *, const void *, unsigned);

class BfmeObject872Header
{
    char bytes[16];
public:
    BfmeObject872Header();
    __declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &);
};

class BfmeFixedStorage0004543D
{
    char bytes[28];
public:
    BfmeFixedStorage0004543D();
    __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};

class WeaponTemplateSetHead
{
    char bytes[76];
public:
    WeaponTemplateSetHead();
    __declspec(nothrow) WeaponTemplateSetHead(const WeaponTemplateSetHead &);
};

struct BfmeObject872
{
    int word00;
    BfmeObject872Header member04;
    int words14[6];
    int words2C[6];
    BfmeFixedStorage0004543D records44[6];
    BfmeFixedStorage0004543D recordsEC[6];
    WeaponTemplateSetHead records194[6];
    unsigned char tail35C;
    unsigned char tail35D;
    unsigned int tail360;
    unsigned char tail364;
    BfmeObject872();
};

typedef char Object872Extent[sizeof(BfmeObject872) == 872 ? 1 : -1];
typedef char Object872Records[offsetof(BfmeObject872, records194) == 0x194 ? 1 : -1];
typedef char Object872Tail[offsetof(BfmeObject872, tail360) == 0x360 ? 1 : -1];

namespace _STL {
template<> void _Construct<BfmeObject872, BfmeObject872>(
    BfmeObject872 *, const BfmeObject872 &) throw();
}

#endif
