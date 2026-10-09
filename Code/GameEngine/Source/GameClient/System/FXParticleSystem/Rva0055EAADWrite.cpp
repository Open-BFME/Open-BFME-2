// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055EAAD@SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x0055EAAD 197B chain lane writeINI via WriteVelocityHeader.
// Evidence: vslot 3 of SphericalEmissionVelocityModuleTemplate 0x0081BC40; calls rowed WriteVelocityHeader 0x0055E891 then ostringstream then rowed IsZero 0x001F3744 gated Speed 0x001F8B5F then rowed str plus FileWrite plus free plus footer; same shape as TerrainFire rva0055E6D4.
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

void Rva0055E891WriteVelocityHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

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

class SphericalEmissionVelocityModuleTemplate {
public:
    virtual void rva0055EAAD(File *file, unsigned int flags);
private:
    char m_pad04[12 - 4];
    S001F87D5 m_speed;
};

void SphericalEmissionVelocityModuleTemplate::rva0055EAAD(File *file, unsigned int flags)
{
    Rva0055E891WriteVelocityHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_speed))
        Rva001F8B5FWrite(oss, flags, "Speed", m_speed);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
