// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
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
#include "ascii_string.h"
#include "unicode_string.h"

// Retail466EA7 copies an AsciiString and one raw dword. Its bytes are already
// held under the tree-pair identity; use an independently verified alias.
// Application meaning and scalar signedness are not established.
#include <vector>
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UBfmeAsciiScalarValue8@@@_STL@@QBEXPAUBfmeAsciiScalarValue8@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeAsciiScalarValue8;
namespace _STL { template <> void allocator<BfmeAsciiScalarValue8>::deallocate(BfmeAsciiScalarValue8 *,unsigned int); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
struct BfmeAsciiScalarValue8 {
    AsciiString text;
    unsigned int value;
    BfmeAsciiScalarValue8();
    BfmeAsciiScalarValue8(const BfmeAsciiScalarValue8 &other)
        : text(other.text), value(other.value) {}
};
namespace _STL {template<> vector<BfmeAsciiScalarValue8>& vector<BfmeAsciiScalarValue8>::operator=(const vector<BfmeAsciiScalarValue8>&);}

template _STL::vector<BfmeAsciiScalarValue8>::vector(const _STL::vector<BfmeAsciiScalarValue8>&);
template BfmeAsciiScalarValue8* _STL::__uninitialized_fill_n<BfmeAsciiScalarValue8*,unsigned int,BfmeAsciiScalarValue8>(BfmeAsciiScalarValue8*,unsigned int,const BfmeAsciiScalarValue8&,const _STL::__false_type&);

// The worker at 0x0031BA18 assigns a scalar followed by a reference member,
// unlike this record's AsciiString-first layout. Its native owner is
// Rva0031BA18Copy.cpp; do not instantiate this record's assignment there.
