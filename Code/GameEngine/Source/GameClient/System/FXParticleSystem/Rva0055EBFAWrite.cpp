// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055EBFA@CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z @0x0055EBFA 237B chain lane writeINI via WriteVelocityHeader.
// Evidence: vslot 3 of CylindricalEmissionVelocityModuleTemplate 0x0081BC70 and 0x0081C058; calls rowed WriteVelocityHeader 0x0055E891 then ostringstream then rowed IsZero 0x001F3744 gated Radial Normal via rowed 0x001F8B5F then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B; same shape as Spherical Rva0055EAAD.
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

class CylindricalEmissionVelocityModuleTemplate {
public:
    void rva0055EBFA(File *file, unsigned int flags);
private:
    char m_pad[12];
    S001F87D5 m_radial;
    S001F87D5 m_normal;
};

void CylindricalEmissionVelocityModuleTemplate::rva0055EBFA(File *file, unsigned int flags)
{
    Rva0055E891WriteVelocityHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_radial))
        Rva001F8B5FWrite(oss, flags, "Radial", m_radial);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_normal))
        Rva001F8B5FWrite(oss, flags, "Normal", m_normal);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
