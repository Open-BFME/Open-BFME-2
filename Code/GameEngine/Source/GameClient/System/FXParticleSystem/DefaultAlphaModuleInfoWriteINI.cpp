// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?rva0055B735@DefaultAlphaModuleInfo@FXParticleSystem@@QAEXPAVFile@@I@Z @0x0055B735 302B writeINI via WriteHeader.
// Evidence: vslot 7 of DefaultAlphaModuleInfo 0x0081BA60 (slot 0 its rowed
// ??_E 0x003A61B3; slot 2 the rowed GetSnapshotName 0x003A611B) and of
// ConcreteModuleTemplate DefaultModuleTag $01 0x0081BF10; calls rowed
// WriteHeader 0x0055B65D (category 1) then ostringstream then for each of
// 8 keyframes (random variable plus frame; 16 bytes from +0x0C) gated by
// rowed IsZero 0x001F3744 or a non-zero frame: Pad 0x001F6951 "Alpha"
// index+1 " = " then the rowed variable Put 0x001F87D5 ' ' frame '\n'
// (_M_put_nowiden _M_put_num<unsigned long> _M_put_char) then rowed str plus
// FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
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
// Declared, not defined here: the link keeps the rowed retail copy (this unit's own copy differs).
namespace _STL { template <> basic_ostream<char,char_traits<char> > & _M_put_num<char,char_traits<char>,unsigned long>(basic_ostream<char,char_traits<char> > &,unsigned long); }
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::basic_ostream(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_ostream<char, char_traits<char> >::~basic_ostream(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> void basic_stringbuf<char, char_traits<char>, allocator<char> >::_M_append_buffer() const; }
namespace _STL { template <> bool basic_ios<char, char_traits<char> >::_S_eof(int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::append(unsigned int, char); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::clear(int); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> bool ostreambuf_iterator<char, char_traits<char> >::failed() const; }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::push_back(char); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > num_put<char, ostreambuf_iterator<char, char_traits<char> > >::put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, unsigned long) const; }
namespace _STL { template <> basic_streambuf<char, char_traits<char> > * basic_ios<char, char_traits<char> >::rdbuf(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_ostringstream<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > basic_stringbuf<char, char_traits<char>, allocator<char> >::str() const; }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::append<char const *>(char const *,char const *,forward_iterator_tag const &); }
// Suppress this TU's non-retail copy of ?_M_put_char@?$basic_ostream@DV?$char_traits@D@_STL@@@_STL@@QAEXD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void basic_ostream<char,char_traits<char> >::_M_put_char(char); }
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

#include "../../../../Include/Common/File.h"
#include "../../../../Include/GameClient/Rva001F458BText.h"
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
#include <stdlib.h>

void Rva0055B65DWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F6951Pad(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int n);

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
_STL::basic_ostream<char, _STL::char_traits<char> > &Rva001F87D5Put(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    const S001F87D5 &s);

namespace FXParticleSystem {

struct AlphaKeyframe {
    S001F87D5 m_alpha;
    unsigned int m_frame;
};

class DefaultAlphaModuleInfo {
public:
    void rva0055B735(File *file, unsigned int flags);
private:
    char m_pad[12];
    AlphaKeyframe m_alphaKey[8]; // +0x0C
};

void DefaultAlphaModuleInfo::rva0055B735(File *file, unsigned int flags)
{
    Rva0055B65DWriteHeader(this, file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    for (unsigned int i = 0; i < 8; ++i)
    {
        if (!Rva001F3744IsZero((const S001F3744 *)&m_alphaKey[i].m_alpha) || m_alphaKey[i].m_frame != 0)
        {
            Rva001F6951Pad(oss, flags) << "Alpha" << i + 1 << " = ";
            Rva001F87D5Put(oss, m_alphaKey[i].m_alpha) << ' ' << m_alphaKey[i].m_frame << '\n';
        }
    }
    Rva001F458BWrite(*file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(file, &flags);
}

} // namespace FXParticleSystem
