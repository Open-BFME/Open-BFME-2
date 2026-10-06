// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ?rva004FAFF2@Rva004FAFF2@@QAEAAU1@ABU1@@Z, retail 0x004FAFF2, 213 bytes.
// Copy-assign over twelve AsciiStrings plus string vector plus int/byte tail.
// Evidence: thirteen AsciiString assigns via pin 0x366F0 plus vector assign rowed 0xBDB46; ret-4 one-arg thiscall; callers 4 incl 951B/1050B; unblocks 3.
#include "ascii_string.h"
namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector {
public:
    vector &operator=(const vector &other);
private:
    void *m_start;
    void *m_finish;
    void *m_end;
};
}
struct Rva004FAFF2 {
    char m_pad00[4];
    AsciiString m04;
    AsciiString m08;
    AsciiString m0C;
    AsciiString m10;
    AsciiString m14;
    AsciiString m18;
    AsciiString m1C;
    int m20;
    int m24;
    AsciiString m28;
    AsciiString m2C;
    AsciiString m30;
    AsciiString m34;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m38;
    int m44;
    int m48;
    int m4C;
    AsciiString m50;
    unsigned char m54;
    unsigned char m55;
    Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2 &other);
};
Rva004FAFF2 &Rva004FAFF2::rva004FAFF2(const Rva004FAFF2 &other)
{
    m04 = other.m04;
    m08 = other.m08;
    m0C = other.m0C;
    m10 = other.m10;
    m14 = other.m14;
    m18 = other.m18;
    m1C = other.m1C;
    m20 = other.m20;
    m24 = other.m24;
    m28 = other.m28;
    m2C = other.m2C;
    m30 = other.m30;
    m34 = other.m34;
    m38 = other.m38;
    m44 = other.m44;
    m48 = other.m48;
    m4C = other.m4C;
    m50 = other.m50;
    m54 = other.m54;
    m55 = other.m55;
    return *this;
}
