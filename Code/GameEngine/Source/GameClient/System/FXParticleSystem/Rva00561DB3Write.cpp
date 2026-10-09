// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00561DB3@LightningDrawModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x00561DB3 340B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of LightningDrawModuleTemplate 0x0081BD90; calls rowed WriteHeader 0x0055C9A0 then ostringstream then rowed IsZero 0x001F3744 gated OffsetX/Y/Z 0x001F8B5F then rowed t4IsZero 0x0055D3D9 gated MultiChance 0x003A5D34 then TileTexture 0x001F89C3 then rowed str plus FileWrite plus free plus footer; same shape as GpuDrawModuleTemplate rva00563D3F.
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

void Rva0055C9A0WriteHeader(const void *self, File *file, unsigned int *flags);
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
void Rva003A5D34Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    float const &value);
void Rva001F89C3Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const bool *value);
int t4IsZero005F4180(const float *v);

namespace FXParticleSystem {

class LightningDrawModuleTemplate {
public:
    virtual void rva00561DB3(File *file, unsigned int flags);
private:
    char m_pad04[12 - 4];
    S001F87D5 m_offsetX;
    S001F87D5 m_offsetY;
    S001F87D5 m_offsetZ;
    float m_multiChance;
    bool m_tileTexture;
};

void LightningDrawModuleTemplate::rva00561DB3(File *file, unsigned int flags)
{
    Rva0055C9A0WriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_offsetX))
        Rva001F8B5FWrite(oss, flags, "OffsetX", m_offsetX);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_offsetY))
        Rva001F8B5FWrite(oss, flags, "OffsetY", m_offsetY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_offsetZ))
        Rva001F8B5FWrite(oss, flags, "OffsetZ", m_offsetZ);
    if (!(unsigned char)t4IsZero005F4180(&m_multiChance))
        Rva003A5D34Write(oss, flags, "MultiChance", m_multiChance);
    Rva001F89C3Write(oss, flags, "TileTexture", &m_tileTexture);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
