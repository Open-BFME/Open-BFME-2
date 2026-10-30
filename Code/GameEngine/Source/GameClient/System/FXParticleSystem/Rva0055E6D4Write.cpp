// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?rva0055E6D4@TerrainFireEmissionModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z @0x0055E6D4 313B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of TerrainFireEmissionModuleTemplate 0x0081BBE0; calls rowed WriteHeader 0x0055CB5D then ostringstream then rowed IsZero 0x001F3744 gated Xoffset/Yoffset/Zoffset 0x001F8B5F then rowed t4IsZero 0x0055D3D9 gated CellEmissionChance 0x003A5D34 then rowed str plus FileWrite plus free plus footer; same shape as Lightning rva00561DB3.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <stdlib.h>
#include <sstream>
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ??1?$basic_ostringstream@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@UAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_ostringstream<char,char_traits<char>,allocator<char> >::~basic_ostringstream(); }
// Suppress this TU's non-retail copy of ?xsputn@?$basic_stringbuf@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@MAEHPBDH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> int basic_stringbuf<char,char_traits<char>,allocator<char> >::xsputn(char const *,int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}

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
    virtual void rva0055E6D4(File *file, unsigned int flags);
private:
    char m_pad04[16 - 4];
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
