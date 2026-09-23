#pragma once
// Target owning record views; original application and ordering-policy names are unknown.
// Copy and cleanup establish the members below; no comparison operation is claimed.
#include <stddef.h>
#include <map>
#include <vector>
#include "FixedStorage128.h"

class OpaqueRefCounted { public: virtual ~OpaqueRefCounted(); void Release_Ref(); };
class AsciiString { void *text_ref; public: AsciiString(const AsciiString &); ~AsciiString(); };
class Rva002390CB {
    void *unknown_00;
    OpaqueRefCounted *owner_04;
public:
    __declspec(nothrow) Rva002390CB(const Rva002390CB &);
    ~Rva002390CB() { if (owner_04) owner_04->Release_Ref(); }
};
class BfmeOwnedRecordArray56 {
    Rva002390CB records[56];
public:
    BfmeOwnedRecordArray56();
};
struct BfmeStringRecord002CF550 {
    AsciiString text;
    Rva002390CB ref;
    BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &other)
        : text(other.text), ref(other.ref) {}
    ~BfmeStringRecord002CF550();
};
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550,
    _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>,
    _STL::allocator<BfmeStringRecord002CF550> > BfmeStringRecordTree900;
bool operator<(const BfmeStringRecord002CF550 &, const BfmeStringRecord002CF550 &);
class WeaponTemplateSetHead {
    unsigned char bytes[0x4C];
public:
    WeaponTemplateSetHead(const WeaponTemplateSetHead &);
};
struct BfmeRecordOwner900 {
    BfmeFixedStorage128 fixed_000;
    BfmeFixedStorage128 fixed_080;
    _STL::vector<AsciiString> strings_100;
    _STL::vector<AsciiString> strings_10C;
    WeaponTemplateSetHead fixed_118;
    WeaponTemplateSetHead fixed_164;
    BfmeOwnedRecordArray56 records_1B0;
    BfmeStringRecordTree900 tree_370;
    unsigned int unknown_37C;
    unsigned char unknown_380, unknown_381, unknown_382;
    BfmeRecordOwner900();
    BfmeRecordOwner900(const BfmeRecordOwner900 &);
    ~BfmeRecordOwner900();
};
typedef char Owner900Size[(sizeof(BfmeRecordOwner900) == 900) ? 1 : -1];
typedef char TreeRecord12[(sizeof(BfmeStringRecord002CF550) == 12) ? 1 : -1];

typedef char Owner900Alignment[__alignof(BfmeRecordOwner900) == 4 ? 1 : -1];
typedef char Owner900VectorOffset[offsetof(BfmeRecordOwner900, strings_100) == 0x100 ? 1 : -1];
typedef char Owner900FixedOffset[offsetof(BfmeRecordOwner900, fixed_118) == 0x118 ? 1 : -1];
typedef char Owner900ArrayOffset[offsetof(BfmeRecordOwner900, records_1B0) == 0x1B0 ? 1 : -1];
typedef char Owner900TreeOffset[offsetof(BfmeRecordOwner900, tree_370) == 0x370 ? 1 : -1];
typedef char Owner900TailOffset[offsetof(BfmeRecordOwner900, unknown_37C) == 0x37C ? 1 : -1];
