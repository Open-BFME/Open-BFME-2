// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// STLport4.5.3 _vector.h, BFME1 reference6583b3c1ff21db4a561285717028fdafc780b7db.
// Native C1D98 five-argument vector growth / RET14; construction BBA1A
// reaches verified466EA7 ASCII+raw-dword copy, const range BBBA8 and fill
// BBBCE use that same constructor. Full helper aliases verified separately.
// Rva name identifies this native construction family. BfmeAsciiScalarValue8
// also has legacy pins to a different destructor/growth family; no application
// type or equivalence to that family is asserted. The existing home remains
// unchanged. Real native cleanup uses the rowed4C3D8B provider below.
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <memory>
#include "ascii_string.h"
#include "unicode_string.h"

// Retail466EA7 copies an AsciiString and one raw dword. Its bytes are already
// held under the tree-pair identity; use an independently verified alias.
// Application meaning and scalar signedness are not established.
#include <vector>
struct Rva000BBA1ARecord8 {
    AsciiString text;
    unsigned int value;
    Rva000BBA1ARecord8();
    Rva000BBA1ARecord8(const Rva000BBA1ARecord8 &o)
        : text(o.text), value(o.value) {}
};

// Observed native clear provider: 004C3D8B reads start/finish at0/4,
// destroys each eight-byte record's ASCII member via0032C0CA, then frees start.
// Original record payload semantics are irrelevant to this call-only view.
class Rva004C3D8BVectorClearView {
public: void clear();
private: void *start,*finish,*end;
};
#pragma comment(linker, "/alternatename:?clear@Rva004C3D8BVectorClearView@@QAEXXZ=?_M_clear@?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@IAEXXZ")

namespace _STL {
template<> void vector<Rva000BBA1ARecord8, allocator<Rva000BBA1ARecord8> >::_M_insert_overflow(
    pointer __position, const Rva000BBA1ARecord8 &__x, const __false_type &,
    size_type __fill_len, bool __atend) {
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);

    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = __uninitialized_copy((const_pointer)this->_M_start, (const_pointer)__position, __new_start, __false_type());
      // handle insertion
      if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
      } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
      if (!__atend)
        // copy remainder
        __new_finish = __uninitialized_copy((const_pointer)__position, (const_pointer)this->_M_finish, __new_finish, __false_type());
    }
    _STLP_UNWIND((_Destroy(__new_start,__new_finish),
                  this->_M_end_of_storage.deallocate(__new_start,__len)));
    ((Rva004C3D8BVectorClearView *)this)->clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }
}
template void _STL::vector<Rva000BBA1ARecord8>::push_back(const Rva000BBA1ARecord8 &);
