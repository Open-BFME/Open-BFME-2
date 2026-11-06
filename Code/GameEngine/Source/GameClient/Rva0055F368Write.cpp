// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?writeINI@?$DefaultModuleTemplate@$02@FXParticleSystem@@UBEXAAVFile@@I@Z @0x0055F368 326B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of DefaultModuleTemplate $02 0x0081BCC0 and ConcreteModuleTag $02 0x0081BF60; calls rowed WriteHeader 0x0055F290 then ostringstream then rowed t4IsZero float Gravity via rowed float Write 0x003A5D34 then rowed IsZero 0x001F3744 VelocityDamping via rowed 0x001F8B5F then rowed RGB IsZero 0x0055CCEF DriftVelocity via rowed Vec 0x001F89E2 then bool Swirly ParticlesAttachToBone via rowed 0x001F89C3 then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
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
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include "ascii_string.h"

#include "../../Include/Common/File.h"
#include "../../Include/GameClient/Rva001F458BText.h"
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
#include <stdlib.h>

void Rva0055F290WriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

int __cdecl t4IsZero005F4180(const float *v);
void Rva003A5D34Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    float const &value);

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

#include "../../../Libraries/Include/Lib/RGBColor.h"
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
struct Vec001F8810 {
    float x;
    float y;
    float z;
};
int Rva0055CCEFIsZero(const RGBColor &color);
void Rva001F89E2Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    const Vec001F8810 &value);
void Rva001F89C3Write(
    _STL::basic_ostream<char, _STL::char_traits<char> > &os,
    unsigned int pad,
    char const *key,
    bool const *value);

namespace FXParticleSystem {

template <int Category> class DefaultModuleTemplate;

template <> class DefaultModuleTemplate<3> {
public:
    virtual void writeINI(File &file, unsigned int flags) const;
private:
    char m_pad[8];
    Vec001F8810 m_driftVelocity;
    float m_gravity;
    S001F87D5 m_velocityDamping;
    bool m_swirly;
    bool m_particlesAttachToBone;
};

void DefaultModuleTemplate<3>::writeINI(File &file, unsigned int flags) const
{
    Rva0055F290WriteHeader(this, &file, &flags);
    _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
    if (!(unsigned char)t4IsZero005F4180(&m_gravity))
        Rva003A5D34Write(oss, flags, "Gravity", m_gravity);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_velocityDamping))
        Rva001F8B5FWrite(oss, flags, "VelocityDamping", m_velocityDamping);
    if (!(unsigned char)Rva0055CCEFIsZero((const RGBColor &)m_driftVelocity))
        Rva001F89E2Write(oss, flags, "DriftVelocity", m_driftVelocity);
    Rva001F89C3Write(oss, flags, "Swirly", &m_swirly);
    Rva001F89C3Write(oss, flags, "ParticlesAttachToBone", &m_particlesAttachToBone);
    Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem
