// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#define _STLP_NO_METHOD_SPECIALIZATION
#include <cstddef>
#include <stl/type_traits.h>

struct BfmeFalseBE
{
    BfmeFalseBE() {}
};

struct BfmeElemBE
{
    BfmeElemBE(const BfmeElemBE &);
};

BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
    const BfmeElemBE &value, const BfmeFalseBE &);

namespace _STL
{
template <>
struct __type_traits<BfmeElemBE>
{
    typedef __false_type has_trivial_default_constructor;
    typedef __false_type has_trivial_copy_constructor;
    typedef __false_type has_trivial_assignment_operator;
    typedef __false_type has_trivial_destructor;
    typedef BfmeFalseBE is_POD_type;
};

static __forceinline BfmeElemBE *__uninitialized_fill_n(
    BfmeElemBE *first, unsigned count, const BfmeElemBE &value, const BfmeFalseBE &tag)
{
    return bfmeFillBE(first, count, value, tag);
}
}

#include <istream>
#include <memory>

typedef _STL::_Eq_int_bound<_STL::char_traits<char> > NarrowEqIntBound;
typedef _STL::istreambuf_iterator<char, _STL::char_traits<char> > NarrowIstreambufIterator;
typedef _STL::_Scan_for_char_val<_STL::char_traits<char> > NarrowScanForCharVal;

template <typename T>
struct BfmeStreambufGbump
{
    static void (T::*ptr())(int) { return &T::_M_gbump; }
};

template NarrowEqIntBound::_Eq_int_bound(int);
template NarrowIstreambufIterator::istreambuf_iterator(
    _STL::basic_streambuf<char, _STL::char_traits<char> > *);
template struct BfmeStreambufGbump<_STL::basic_streambuf<char, _STL::char_traits<char> > >;
template NarrowScanForCharVal::_Scan_for_char_val(char);
template BfmeElemBE *_STL::uninitialized_fill_n<BfmeElemBE *, unsigned, BfmeElemBE>(
    BfmeElemBE *, unsigned, const BfmeElemBE &);
