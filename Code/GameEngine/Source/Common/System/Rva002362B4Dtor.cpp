// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002362B4@@QAE@XZ @0x002362B4 104B
// Non-virtual dtor: vector<AsciiString> at +0x14 via rowed 0x0002CC70,
// five AsciiString at +0x00 +0x04 +0x08 +0x0C +0x10 via rowed releaseBuffer
// ?releaseBuffer@?$StringBase@D@@AAEXXZ at 0x00036410.
// Destruction reverse of declaration: +0x14 then +0x10..+0x00 with EH states
// 4 3 2 1 0 -1. Callers in 0x002376CC. Flags copy prev GlobalDataRva002360DE
// plus stlport flags from StlportAsciiStringVectorDtor.
#include <vector>

#include "ascii_string.h"


class Rva002362B4
{
public:
    ~Rva002362B4();
private:
    AsciiString m_00;
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0C;
    AsciiString m_10;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_14;
};

Rva002362B4::~Rva002362B4()
{
}
