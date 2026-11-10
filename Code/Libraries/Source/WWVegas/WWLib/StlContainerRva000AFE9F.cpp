// Pristine STLport4.5.3 byte storage operations; target byte stride, memmove/fill calls and vector fields establish family.
// Unsigned byte spelling is donor source provenance; signedness is not distinguished by these target operations.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned char * allocator<unsigned char>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end

// Keep the retail growth body (0x000AFB2E, stlport_pod_vector_bodies.cpp)
// visible for caller alias analysis; an opaque declaration changes fill_insert.
template <> inline void _STL::vector<unsigned char, _STL::allocator<unsigned char> >::_M_insert_overflow(
    unsigned char *position, const unsigned char &value, const _STL::__true_type &,
    unsigned int fill_len, bool at_end)
{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    unsigned char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = (unsigned char *)_STL::allocator<char>::allocate(new_len, 0);
    else
        new_start = 0;
    unsigned char *new_finish = (unsigned char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (unsigned char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}

template void _STL::vector<unsigned char>::_M_fill_insert(unsigned char*,unsigned int,const unsigned char&);
template void _STL::vector<unsigned char>::insert(unsigned char*,unsigned int,const unsigned char&);
