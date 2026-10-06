// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1Rva00509D4C@@UAE@XZ retail 0x00509D4C 89B
// Novtable derived of Rva00507823 base rowed at 0x00507823. Destroys
// three AsciiStrings at +0x130/+0x134/+0x138 via pinned ??1AsciiString
// at 0x00036410 (same address as releaseBuffer) EH states 2/1/0 then
// base dtor. No derived vptr store novtable. Trivial +0x128/+0x12c.
#include "ascii_string.h"

class Rva00507823
{
public:
    virtual ~Rva00507823();
private:
    unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Rva00509D4C : public Rva00507823
{
public:
    virtual ~Rva00509D4C();
private:
    int m_128;
    int m_12c;
    AsciiString m_130;
    AsciiString m_134;
    AsciiString m_138;
};

Rva00509D4C::~Rva00509D4C()
{
}
