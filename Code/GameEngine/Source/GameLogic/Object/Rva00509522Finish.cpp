// ??0Made002CC774@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ??0Made002CC774@@QAE@XZ, retail 0x00509522 38B.
// Base Rva00507823 plus vtable 0x00864520 plus three members at
// +0x128/+0x12c/+0x130 zeroed. AsciiString at +0x130 is the non-trivial
// member, so the derived vptr store lands first. Made002CCBCA precedent.
#include "ascii_string.h"

class Rva00507823
{
public:
    virtual ~Rva00507823();
    Rva00507823();
private:
    char m_pad04[0x128 - 4];
};
class Made002CC774 : public Rva00507823
{
public:
    Made002CC774();
private:
    int m_128;
    int m_12c;
    AsciiString m_130;
};
Made002CC774::Made002CC774()
{
    m_128 = 0;
    m_12c = 0;
}
