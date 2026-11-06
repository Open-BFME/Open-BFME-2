// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?writeINI@?$DefaultModuleTemplate@$01@FXParticleSystem@@UBEXAAVFile@@I@Z @0x0055FB37 504B chain lane writeINI via WriteHeader.
// Evidence: vslot 3 of DefaultModuleTemplate $01 0x0081BCF0 and ConcreteModuleTag $01 0x0081BF84; calls rowed WriteHeader 0x0055FA5F then ostringstream then 8x rowed IsZero 0x001F3744 gated SizeRate SizeRateDamping AngleZ AngularRateZ AngularDamping AngleXY AngularRateXY AngularDampingXY via rowed 0x001F8B5F plus Rotation enum via rowed 0x001F82AB with table FXParticleSystem::RotationTypeNames (RVA 0x0081B6D8) then rowed str plus FileWrite 0x001F458B plus free plus footer 0x003AFC6B.
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
// basic_stringbuf<char>'s constructor is the rowed body 0x001F6813
// (stlport_narrow_ostringstream_dtor.cpp); declared so this unit does not emit
// its own constructor chain with a non-retail basic_streambuf<char> constructor.
namespace _STL { template <> basic_stringbuf<char, char_traits<char>, allocator<char> >::basic_stringbuf(int); }
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

#include "../../Include/Common/File.h"
#include "../../Include/GameClient/Rva001F458BText.h"
File &Rva001F458BWrite(File &file, const Rva001F458BText &text);
#include <stdlib.h>

void Rva0055FA5FWriteHeader(const void *self, File *file, unsigned int *flags);
void Rva003AFC6BWrite(File *file, unsigned int *flags);

namespace FXParticleSystem { extern const char *const RotationTypeNames[]; }	// defined in FXParticleSystemModuleParsers.cpp

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

namespace FXParticleSystem {

template <int Category> class DefaultModuleTemplate;

template <> class DefaultModuleTemplate<2> {
public:
    virtual void writeINI(File &file, unsigned int flags) const;
private:
    char m_pad[8];
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

void DefaultModuleTemplate<2>::writeINI(File &file, unsigned int flags) const
{
    Rva0055FA5FWriteHeader(this, &file, &flags);
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
        Rva001F82ABWrite(oss, flags, "Rotation", const_cast<const char **>(&FXParticleSystem::RotationTypeNames[m_rotation]));
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angleXY))
        Rva001F8B5FWrite(oss, flags, "AngleXY", m_angleXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularRateXY))
        Rva001F8B5FWrite(oss, flags, "AngularRateXY", m_angularRateXY);
    if (!Rva001F3744IsZero((const S001F3744 *)&m_angularDampingXY))
        Rva001F8B5FWrite(oss, flags, "AngularDampingXY", m_angularDampingXY);
    Rva001F458BWrite(file, (const Rva001F458BText &)oss.str());
    Rva003AFC6BWrite(&file, &flags);
}

} // namespace FXParticleSystem

// Native5625C5..56285E is a complete665B INI serializer. The retail
// field-parse table C6C710 independently agrees with all12 variable names
// and offsets0C..90 and the Rotation field9C. BF1 donor874e38488c7d
// DefaultModuleTemplate_writeINI and the verified BF2 sibling55FB37 give
// the writer/ostringstream pattern. Retail export 1956 identifies the writer.
namespace FXParticleSystem {

class RenderObjectUpdateModuleTemplate {
public:
    virtual void writeINI(File &file, unsigned int flags) const;
private:
    char m_pad[8];
 S001F87D5 m_StartSizeX;
 S001F87D5 m_StartSizeY;
 S001F87D5 m_StartSizeZ;
 S001F87D5 m_SizeRateX;
 S001F87D5 m_SizeRateY;
 S001F87D5 m_SizeRateZ;
 S001F87D5 m_SizeDampingX;
 S001F87D5 m_SizeDampingY;
 S001F87D5 m_SizeDampingZ;
 S001F87D5 m_AngleZ;
 S001F87D5 m_AngularRateZ;
 S001F87D5 m_AngularDamping;
 int rotation;
};

void RenderObjectUpdateModuleTemplate::writeINI(File &file, unsigned int flags) const
{
 Rva0055FA5FWriteHeader(this,&file,&flags);
 _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> > oss(16);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeX))
  Rva001F8B5FWrite(oss,flags,"StartSizeX",m_StartSizeX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeY))
  Rva001F8B5FWrite(oss,flags,"StartSizeY",m_StartSizeY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_StartSizeZ))
  Rva001F8B5FWrite(oss,flags,"StartSizeZ",m_StartSizeZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateX))
  Rva001F8B5FWrite(oss,flags,"SizeRateX",m_SizeRateX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateY))
  Rva001F8B5FWrite(oss,flags,"SizeRateY",m_SizeRateY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeRateZ))
  Rva001F8B5FWrite(oss,flags,"SizeRateZ",m_SizeRateZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingX))
  Rva001F8B5FWrite(oss,flags,"SizeDampingX",m_SizeDampingX);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingY))
  Rva001F8B5FWrite(oss,flags,"SizeDampingY",m_SizeDampingY);
 if(!Rva001F3744IsZero((const S001F3744*)&m_SizeDampingZ))
  Rva001F8B5FWrite(oss,flags,"SizeDampingZ",m_SizeDampingZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngleZ))
  Rva001F8B5FWrite(oss,flags,"AngleZ",m_AngleZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngularRateZ))
  Rva001F8B5FWrite(oss,flags,"AngularRateZ",m_AngularRateZ);
 if(!Rva001F3744IsZero((const S001F3744*)&m_AngularDamping))
  Rva001F8B5FWrite(oss,flags,"AngularDamping",m_AngularDamping);
 if(rotation!=1)Rva001F82ABWrite(oss,flags,"Rotation",const_cast<const char **>(&FXParticleSystem::RotationTypeNames[rotation]));
 Rva001F458BWrite(file,(const Rva001F458BText&)oss.str());
 Rva003AFC6BWrite(&file,&flags);
}

} // namespace FXParticleSystem
