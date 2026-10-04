// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
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
