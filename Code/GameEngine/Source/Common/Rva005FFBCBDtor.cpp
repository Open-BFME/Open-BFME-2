// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
// Target destructor 0x005FFBCB/91, Ghidra FUN_009ffbcb.
// The served ZH SkirmishGameInfo destructor is not this type: native code
// destroys three 12-byte elements at +0x24, two holders at +0x1C,
// the vector owner at +0xC, then AsciiString at +8. All offsets/counts
// come from the native body; original class and member purposes unknown.
#include "ascii_string.h"

class Rva005FFB89
{
    void *holders[2];
public:
    ~Rva005FFB89();
};

class Rva005FFBC6
{
    Rva005FFB89 refs;
    unsigned int unknown;
public:
    ~Rva005FFBC6();
};

Rva005FFBC6::~Rva005FFBC6() {}

// Same single-vector representation as its defining cleanup unit.
class Rva0052413E
{
public:
    ~Rva0052413E();
private:
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_00;
};

class Rva005FFBCB
{
    char prefix[8];
    AsciiString text08;
    Rva0052413E ownedVector;
    unsigned int unknown18;
    Rva005FFB89 refs;
    Rva005FFBC6 elements[3];
public:
    ~Rva005FFBCB();
};

Rva005FFBCB::~Rva005FFBCB() {}
