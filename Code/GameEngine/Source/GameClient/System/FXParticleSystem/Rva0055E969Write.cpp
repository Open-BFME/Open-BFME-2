// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055E969@OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x0055E969 275B chain lane writeINI via WriteVelocityHeader.
// Evidence: vslot 3 of OrthoEmissionVelocityModuleTemplate 0x0081BC10 and 0x0081BFFC; calls rowed WriteVelocityHeader 0x0055E891 then ostringstream then rowed IsZero 0x001F3744 gated 3 fields via rowed 0x001F8B5F then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B; same shape as Cylindrical Rva0055EBFA plus one field.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

extern const char g_00BBE3C8[];
extern const char g_00BBE3C4[];
extern const char g_00BBE3C0[];

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

class OrthoEmissionVelocityModuleTemplate {
public:
    virtual void rva0055E969(File *file, unsigned int flags);
private:
    char m_pad04[12 - 4];
    S001F87D5 m_field0C;
    S001F87D5 m_field18;
    S001F87D5 m_field24;
};

void OrthoEmissionVelocityModuleTemplate::rva0055E969(File *file, unsigned int flags)
{
    Rva0055E891WriteVelocityHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_field0C))
        Rva001F8B5FWrite(oss, flags, g_00BBE3C8, m_field0C);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_field18))
        Rva001F8B5FWrite(oss, flags, g_00BBE3C4, m_field18);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_field24))
        Rva001F8B5FWrite(oss, flags, g_00BBE3C0, m_field24);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
