// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva005F75C9@@QAE@XZ retail 0x005F75C9 139B
// Evidence: non-virtual dtor over members at +0x08 narrow via 0x36410 plus +0x0c wide via 0x36E70 plus rowed dtors 0x52413E 0x5242D7 0x524265 plus rowed clear 0x5F74A0 plus 7x array of rowed 0x5F74BA via EH vector dtor plus +0x58 wide; pin pre-existed.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva005F6A58
{
public:
    virtual ~Rva005F6A58();
};

class Rva005F6AB0
{
public:
    virtual ~Rva005F6AB0();
};

class Rva0052413E
{
public:
    ~Rva0052413E();
private:
    char m_pad[12];
};

class Rva005242D7
{
public:
    ~Rva005242D7();
private:
    char m_pad[12];
};

class Rva00524265
{
public:
    ~Rva00524265();
private:
    char m_pad[12];
};

class Rva005F74A0
{
public:
    Rva005F6A58 *m_ptr;
    void clear();
// ??1Rva005F74A0@@QAE@XZ absent-from-retail
    __forceinline ~Rva005F74A0() { clear(); }
};

struct Rva005F74BA
{
    Rva005F6AB0 *m_ptr;
    ~Rva005F74BA();
};

struct Rva005F75C9
{
    unsigned char _pad00[0x08];
    AsciiString m_08;
    UnicodeString m_0c;
    unsigned int _pad10;
    Rva0052413E m_14;
    Rva005242D7 m_20;
    Rva00524265 m_2c;
    Rva005F74A0 m_38;
    Rva005F74BA m_3c[7];
    UnicodeString m_58;
    ~Rva005F75C9();
};

Rva005F75C9::~Rva005F75C9()
{
}
