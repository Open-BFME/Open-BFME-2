// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055FB37@Rva0055FB37@@QAEXPAVFile@@I@Z @0x0055FB37 504B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of DefaultModuleTemplate $01 0x0081BCF0 and ConcreteModuleTag $01 0x0081BF84; calls rowed WriteHeader 0x0055FA5F then ostringstream then 8x rowed IsZero 0x001F3744 gated SizeRate SizeRateDamping AngleZ AngularRateZ AngularDamping AngleXY AngularRateXY AngularDampingXY via rowed 0x001F8B5F plus Rotation enum via rowed 0x001F82AB with table g_00C1B6D8 then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <sstream>
#include "ascii_string.h"

class File {
public:
    virtual ~File();
    virtual bool open(const char *n, int a = 0);
    virtual void close();
    virtual int read(void *b, int bsz);
    virtual int write(const void *b, int bsz);
};
struct Rva001F458BText {
    const char *m_start;
    const char *m_finish;
};
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
extern "C" void __cdecl free(void *p);

void Rva0055FA5FWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

extern const char *g_00C1B6D8[];

struct S001F87D5 {
    char _0[4];
    float x;
    float y;
};
struct S001F3744 {
    char m_00[4];
    float m_04;
    float m_08;
};
bool __cdecl Rva001F3744IsZero(const S001F3744 *p);
void Rva001F8B5FWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const S001F87D5 &value);
void Rva001F82ABWrite(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    char const **value);

class Rva0055FB37 {
public:
    void rva0055FB37(File *file, unsigned int flags);
private:
    char m_pad[12];
    S001F87D5 m_sizeRate;
    S001F87D5 m_sizeRateDamping;
    S001F87D5 m_angleZ;
    S001F87D5 m_angularRateZ;
    S001F87D5 m_angularDamping;
    int m_rotation;
    S001F87D5 m_angleXY;
    S001F87D5 m_angularRateXY;
    S001F87D5 m_angularDampingXY;
};

void Rva0055FB37::rva0055FB37(File *file, unsigned int flags)
{
    Rva0055FA5FWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_sizeRate))
        Rva001F8B5FWrite(oss, flags, "SizeRate", m_sizeRate);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_sizeRateDamping))
        Rva001F8B5FWrite(oss, flags, "SizeRateDamping", m_sizeRateDamping);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angleZ))
        Rva001F8B5FWrite(oss, flags, "AngleZ", m_angleZ);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularRateZ))
        Rva001F8B5FWrite(oss, flags, "AngularRateZ", m_angularRateZ);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularDamping))
        Rva001F8B5FWrite(oss, flags, "AngularDamping", m_angularDamping);
    if (m_rotation != 1)
        Rva001F82ABWrite(oss, flags, "Rotation", &g_00C1B6D8[m_rotation]);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angleXY))
        Rva001F8B5FWrite(oss, flags, "AngleXY", m_angleXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularRateXY))
        Rva001F8B5FWrite(oss, flags, "AngularRateXY", m_angularRateXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularDampingXY))
        Rva001F8B5FWrite(oss, flags, "AngularDampingXY", m_angularDampingXY);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}
