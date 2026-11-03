// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME1 revision 6583b3c1 supplies the sawMatchbot purpose and value-string ABI.
// Target 0x38AD81..0x38ADC6 (69 bytes) is called by enum callback 0x38B5DB:
// it sets +0x48D and assigns the string at +0x490 then destroys the argument.
// Fields before +0x48C remain opaque. This declaration supplies only the method
// ABI; it does not claim a complete PeerThreadClass layout. Native _free and
// the unwind-state store require the established BFME STL allocator settings.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>
// Keep _String_base<char>::~_String_base inline-only: no call here leaves it out
// of line, and this TU's COMDAT copy is not retail's 0x0000B3C0 body.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); }
}
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
struct BfmePeerEnumState { unsigned char unknown[0x48c]; bool sawEnd; bool sawMatchbot; unsigned char alignment[2]; std::string name; };
#include "../../../../Include/GameNetwork/GameSpy/PeerThreadClass.h"
void PeerThreadClass::sawMatchbot(std::string bot) { BfmePeerEnumState *state = reinterpret_cast<BfmePeerEnumState *>(this); state->sawMatchbot = true; state->name = bot; }