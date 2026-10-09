// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055E39E@LightningEmissionModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x0055E39E 582B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of LightningEmissionModuleTemplate 0x0081BBB0 and 0x0081C154; calls rowed WriteHeader 0x0055CB5D then ostringstream then rowed RGB IsZero 0x0055CCEF gated StartPoint EndPoint via rowed Vec Write 0x001F89E2 then 9x rowed IsZero 0x001F3744 gated Amplitude Frequency Phase via rowed 0x001F8B5F then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B; same shape as Ortho plus RGB head.
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

void Rva0055CB5DWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

struct RGBColor {
    float red;
    float green;
    float blue;
};
struct Vec001F8810 {
    float x;
    float y;
    float z;
};
int __cdecl Rva0055CCEFIsZero(const RGBColor &color);
void Rva001F89E2Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const Vec001F8810 &value);

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

namespace FXParticleSystem {

class LightningEmissionModuleTemplate {
public:
    virtual void rva0055E39E(File *file, unsigned int flags);
private:
    char m_pad04[16 - 4];
    Vec001F8810 m_startPoint;
    Vec001F8810 m_endPoint;
    S001F87D5 m_amplitude1;
    S001F87D5 m_frequency1;
    S001F87D5 m_phase1;
    S001F87D5 m_amplitude2;
    S001F87D5 m_frequency2;
    S001F87D5 m_phase2;
    S001F87D5 m_amplitude3;
    S001F87D5 m_frequency3;
    S001F87D5 m_phase3;
};

void LightningEmissionModuleTemplate::rva0055E39E(File *file, unsigned int flags)
{
    Rva0055CB5DWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!(unsigned char)Rva0055CCEFIsZero((const RGBColor &)m_startPoint))
        Rva001F89E2Write(oss, flags, "StartPoint", m_startPoint);
    if (!(unsigned char)Rva0055CCEFIsZero((const RGBColor &)m_endPoint))
        Rva001F89E2Write(oss, flags, "EndPoint", m_endPoint);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_amplitude1))
        Rva001F8B5FWrite(oss, flags, "Amplitude1", m_amplitude1);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_frequency1))
        Rva001F8B5FWrite(oss, flags, "Frequency1", m_frequency1);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_phase1))
        Rva001F8B5FWrite(oss, flags, "Phase1", m_phase1);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_amplitude2))
        Rva001F8B5FWrite(oss, flags, "Amplitude2", m_amplitude2);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_frequency2))
        Rva001F8B5FWrite(oss, flags, "Frequency2", m_frequency2);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_phase2))
        Rva001F8B5FWrite(oss, flags, "Phase2", m_phase2);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_amplitude3))
        Rva001F8B5FWrite(oss, flags, "Amplitude3", m_amplitude3);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_frequency3))
        Rva001F8B5FWrite(oss, flags, "Frequency3", m_frequency3);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_phase3))
        Rva001F8B5FWrite(oss, flags, "Phase3", m_phase3);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
