// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// Full native BDE85..BDF17 constructor; caller C838F passes AsciiString ref and float.
// Existing149B copy and68B destructor own the same64B record. Float stores
// prove14/18/20/24/28/34/38 types; original class and field meanings remain unknown.
// String and vector headers use canonical existing ABI; EH state0 owns names.
#include "ascii_string.h"
#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}
#include "../../../Include/Common/BfmeVectorRecord000BDF17.h"
BfmeVectorRecord000BDF17::BfmeVectorRecord000BDF17(const AsciiString&text,float value):text0(text),word14(value),word18(-1.0f),word1C(1),word20(5.0f),word24(1.0f),word28(1.0f),flag2C(false),flag2D(false),word30(1),word34(-1.0f),word38(-1.0f),flag3C(false){}

// Native C697B..C6A35 vector assignment; BfmePod248::operator= (0xC6C54) calls it
// for its BDF17 member vector. Its helpers stay calls to their rowed copies.
// Keep the assignment's allocator helpers out of this TU: the two members bind
// the kept copies, and __node_alloc<true,0>::deallocate stays inline-only.
namespace _STL {
template <> BfmeVectorRecord000BDF17 *_STLP_alloc_proxy<BfmeVectorRecord000BDF17*, BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::allocate(size_t);
template <> void allocator<BfmeVectorRecord000BDF17>::deallocate(BfmeVectorRecord000BDF17*, size_t) const;
template <> void _STLP_alloc_proxy<BfmeVectorRecord000BDF17*, BfmeVectorRecord000BDF17, allocator<BfmeVectorRecord000BDF17> >::deallocate(BfmeVectorRecord000BDF17*, size_t);
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
template _STL::vector<BfmeVectorRecord000BDF17>&_STL::vector<BfmeVectorRecord000BDF17>::operator=(const _STL::vector<BfmeVectorRecord000BDF17>&);
