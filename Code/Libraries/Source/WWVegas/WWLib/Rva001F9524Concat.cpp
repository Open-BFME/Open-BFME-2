// cl: /O1 /Ob2 /D_CRTIMP= /arch:SSE /G7 /Oy- /MD /EHs /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <string>

// Retail boundary 001F9524 160B; caller 001FB46F appends the template name.
// STLport string concatenation lead; copied/reserved narrow storage and forward-iterator append
// are target facts. The shared empty allocator getter is the rowed wide provider at 001627F0.
typedef _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > NarrowString;
typedef _STL::basic_string<unsigned short,_STL::char_traits<unsigned short>,_STL::allocator<unsigned short> > WideString;
NarrowString Rva001F9524Concat(const NarrowString &first,const char *second) {
 unsigned n=strlen(second);
 NarrowString tmp(_STL::_String_reserve_t(),first.size()+n,*(const _STL::allocator<char>*)&((const WideString&)first).get_allocator());
 tmp.append(first); tmp.append(second,second+n); return tmp;
}
