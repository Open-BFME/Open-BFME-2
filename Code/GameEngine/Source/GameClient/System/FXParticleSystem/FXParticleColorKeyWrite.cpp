// ?writeINI@?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UBEXAAVFile@@I@Z
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// Native full body 55C263..55C414, RET8. Retail export ordinal 1940 names it
// DefaultModuleTemplate<0>::writeINI. Literal Color and ColorScale plus eight
// 16-byte records at +0xC establish this serializer's measured view.
// Primary C++ guides: matched Rva00563D3FWrite.cpp stream serialization and
// Rva0055C18BWrite.cpp stream/header setup. Target helpers supply the key RGB,
// float-pair, indentation, File write, and trailing-record operations.
// The independent key cursor keeps ESI at RGB's first member as retail does;
// an indexed reference anchors it at the frame and grows this body by two bytes.
#include <stl/_algobase.h>
namespace _STL {template<> const unsigned int& max<unsigned int>(const unsigned int&,const unsigned int&);}
#include <sstream>
// basic_ostringstream<char>'s constructor is the rowed body 0x001FA85C
// (stlport_narrow_ostringstream_ctor.cpp). Declared here so this unit calls it
// instead of emitting its own constructor chain, whose _STLP_NO_EXCEPTIONS
// basic_streambuf<char> constructor is not retail's.
namespace _STL { template <> basic_ostringstream<char, char_traits<char>, allocator<char> >::basic_ostringstream(int); }
#include <cstddef>
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
#include "../../../../Include/Common/File.h"
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
// Declared, not defined here: the link keeps the rowed retail copy (this unit's own copy differs).
namespace _STL { template <> basic_ostream<char,char_traits<char> > & _M_put_num<char,char_traits<char>,unsigned long>(basic_ostream<char,char_traits<char> > &,unsigned long); }
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
struct ColorKey {RGBColor color;unsigned long frame;};
struct S001F87D5 {unsigned int first;float x,y;};
#include "../../../../Include/GameClient/Rva001F458BText.h"
typedef _STL::basic_ostream<char,_STL::char_traits<char> > OutputStream;
OutputStream& Rva001F6951Pad(OutputStream&,unsigned int);
OutputStream& Rva0055C0E1Write(OutputStream&,const RGBColor&);
OutputStream& Rva001F87D5Put(OutputStream&,const S001F87D5&);
void Rva0055C18BWriteHeader(const void*,File*,unsigned int*);
void Rva003AFC6BWrite(File*,unsigned int*);
File& Rva001F458BWrite(File&,const Rva001F458BText&);
namespace FXParticleSystem {
template <int Category> class DefaultModuleTemplate;
template <> class DefaultModuleTemplate<0> {public: virtual void writeINI(File&,unsigned int) const; private:char pad[8];ColorKey keys[8];S001F87D5 scale;};
void DefaultModuleTemplate<0>::writeINI(File& file,unsigned int flags) const {
 Rva0055C18BWriteHeader(this,&file,&flags);
 _STL::basic_ostringstream<char,_STL::char_traits<char>,_STL::allocator<char> > oss(16);
 const ColorKey* cursor=keys;
 for(unsigned int i=0;i<8;i++,cursor++) {
  const ColorKey& key=*cursor;
  if(key.color.red!=0.0f || key.color.green!=0.0f || key.color.blue!=0.0f || key.frame!=0) {
   Rva001F6951Pad(oss,flags)<<"Color"<<(unsigned long)(i+1)<<" = ";
   Rva0055C0E1Write(oss,key.color)<<' '<<key.frame<<'\n';
  }
 }
 if(scale.x!=0.0f || scale.y!=0.0f) {
  Rva001F6951Pad(oss,flags)<<"ColorScale = ";
  Rva001F87D5Put(oss,scale)<<'\n';
 }
 Rva001F458BWrite(file,(const Rva001F458BText&)oss.str());
 Rva003AFC6BWrite(&file,&flags);
}
}
