// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"

// ?rva00580316@Rva00580316@@QAEXPAX@Z 0x00580316 170B
// Saves three column sorts into prefs via virtual slot 0x2c (setInt-like):
// PrimarySort/SecondarySort/StatusColumn string literals with ints at +0xc/+0x10/+0x18.
// Donor: BFME1 OnlineCustomMatchDestructor.cpp (PrimarySort/SecondarySort setInt shape).
// Callers: 0x00446783 (this=esi+0x668 arg=esi+0x684) 0x0059EFBC.

class Rva00580316Prefs
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void v5() = 0;
    virtual int getInt(const AsciiString &key, int def) = 0;
    virtual void v7() = 0;
    virtual void v8() = 0;
    virtual void v9() = 0;
    virtual void v10() = 0;
    virtual void setInt(const AsciiString &key, int value) = 0;
};

class Rva00580316
{
public:
    void rva00580316(void *prefsVoid);
    void rva00580263(void *prefsVoid);

private:
    char m_pad00[12];
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
};

void Rva00580316::rva00580316(void *prefsVoid)
{
    Rva00580316Prefs *prefs = (Rva00580316Prefs *)prefsVoid;
    prefs->setInt(AsciiString("PrimarySort"), m_0c);
    prefs->setInt(AsciiString("SecondarySort"), m_10);
    prefs->setInt(AsciiString("StatusColumn"), m_18);
}

// ?rva00580263@Rva00580316@@QAEXPAX@Z @0x00580263 179B.
// Loads three column sorts via virtual slot 0x18 (getInt-like):
// PrimarySort/SecondarySort/StatusColumn string literals with ints at +0xc/+0x10/+0x18.
// Same class and offsets as rowed saver 0x00580316; caller 0x005A6189.
void Rva00580316::rva00580263(void *prefsVoid)
{
    Rva00580316Prefs *prefs = (Rva00580316Prefs *)prefsVoid;
    m_0c = prefs->getInt(AsciiString("PrimarySort"), m_0c);
    m_10 = prefs->getInt(AsciiString("SecondarySort"), m_10);
    m_18 = prefs->getInt(AsciiString("StatusColumn"), m_18);
}
