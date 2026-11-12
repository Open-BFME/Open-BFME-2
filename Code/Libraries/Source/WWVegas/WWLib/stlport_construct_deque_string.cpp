// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// STLport placement-copy helpers and distinct native copy owners, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// The nested deque reuses the established 4-byte BfmeWordValue4 model; the
// string pair uses the real STLport basic_string with an unsigned payload,
// preserving the established trivial-dword reference model. The original
// application mapped type and helper spelling remain unknown.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <memory>
#include <deque>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAUBfmeWordValue4@@@_STL@@QBEXPAPAUBfmeWordValue4@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> void allocator<BfmeWordValue4 *>::deallocate(BfmeWordValue4 * *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeWordValue4@@@_STL@@QBEXPAUBfmeWordValue4@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> void allocator<BfmeWordValue4>::deallocate(BfmeWordValue4 *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPAUBfmeWordValue4@@PAU1@V?$allocator@PAUBfmeWordValue4@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> BfmeWordValue4 * * _STLP_alloc_proxy<BfmeWordValue4 * *,BfmeWordValue4 *,allocator<BfmeWordValue4 *> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAPAV?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> deque<BfmeWordValue4,allocator<BfmeWordValue4> > * * _STLP_alloc_proxy<deque<BfmeWordValue4,allocator<BfmeWordValue4> > * *,deque<BfmeWordValue4,allocator<BfmeWordValue4> > *,allocator<deque<BfmeWordValue4,allocator<BfmeWordValue4> > *> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@V?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> void allocator<deque<BfmeWordValue4,allocator<BfmeWordValue4> > >::deallocate(deque<BfmeWordValue4,allocator<BfmeWordValue4> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@PAV?$deque@UBfmeWordValue4@@V?$allocator@UBfmeWordValue4@@@_STL@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeWordValue4;
namespace _STL { template <> void allocator<deque<BfmeWordValue4,allocator<BfmeWordValue4> > *>::deallocate(deque<BfmeWordValue4,allocator<BfmeWordValue4> > * *,unsigned int) const; }
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

#include "../../../../GameEngine/Include/Common/BfmeWordValue4.h"

typedef _STL::deque<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > ConstructInnerDeque;
typedef _STL::deque<ConstructInnerDeque, _STL::allocator<ConstructInnerDeque> > ConstructOuterDeque;
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > ConstructStdString;
typedef _STL::pair<const ConstructStdString, unsigned int> ConstructPairSU;

template void _STL::_Construct<ConstructOuterDeque, ConstructOuterDeque>(ConstructOuterDeque *, const ConstructOuterDeque &);
void StringUnsignedPairCopyAtRva0060CFFF(void *dest, const void *source)
{
    ::new (dest) ConstructPairSU(*static_cast<const ConstructPairSU *>(source));
}
