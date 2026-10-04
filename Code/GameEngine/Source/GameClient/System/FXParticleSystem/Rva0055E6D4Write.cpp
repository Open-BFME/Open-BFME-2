// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva0055E6D4@TerrainFireEmissionModuleTemplate@FXParticleSystem@@QAEXPAVFile@@I@Z @0x0055E6D4 313B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of TerrainFireEmissionModuleTemplate 0x0081BBE0; calls rowed WriteHeader 0x0055CB5D then ostringstream then rowed IsZero 0x001F3744 gated Xoffset/Yoffset/Zoffset 0x001F8B5F then rowed t4IsZero 0x0055D3D9 gated CellEmissionChance 0x003A5D34 then rowed str plus FileWrite plus free plus footer; same shape as Lightning rva00561DB3.
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
int t4IsZero005F4180(const float *v);

namespace FXParticleSystem {

class TerrainFireEmissionModuleTemplate {
public:
    void rva0055E6D4(File *file, unsigned int flags);
private:
    char m_pad[16];
    S001F87D5 m_xoffset;
    S001F87D5 m_yoffset;
    S001F87D5 m_zoffset;
    float m_cellEmissionChance;
};

void TerrainFireEmissionModuleTemplate::rva0055E6D4(File *file, unsigned int flags)
{
    Rva0055CB5DWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_xoffset))
        Rva001F8B5FWrite(oss, flags, "Xoffset", m_xoffset);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_yoffset))
        Rva001F8B5FWrite(oss, flags, "Yoffset", m_yoffset);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_zoffset))
        Rva001F8B5FWrite(oss, flags, "Zoffset", m_zoffset);
    if (!(unsigned char)t4IsZero005F4180(&m_cellEmissionChance))
        Rva003A5D34Write(oss, flags, "CellEmissionChance", m_cellEmissionChance);
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
