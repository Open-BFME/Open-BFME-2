// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/open-bfme-1/inputs/vendor/stlport/stl
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
// Use the pristine algorithms while retaining BFME2's allocation shim.
// The shim's algorithm header forces the copy-backward aux layer inline,
// producing a competing 65-byte body instead of retail's 63-byte wrapper.
#include <_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
// Suppress this TU's non-retail copy of ??$__uninitialized_copy_copy@U?$_Deque_iterator@UBfmeE12@@U?$_Nonconst_traits@UBfmeE12@@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE12;
namespace _STL { template <> _Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> > __uninitialized_copy_copy<_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> > >(_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,__false_type); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy_copy@U?$_Deque_iterator@UBfmeE12@@U?$_Const_traits@UBfmeE12@@@_STL:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> _Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> > __uninitialized_copy_copy<_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> > >(_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Const_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,_Deque_iterator<BfmeE12,_Nonconst_traits<BfmeE12> >,__false_type); }
struct BfmeE12 { float x, y, z; };
#include "DequeE12Copy.h"

// Native2CA82C: null-checked, field-wise placement construction of12 bytes.
// Keep the native out-of-line operation instead of this TU's POD copy helper.
__declspec(noinline) void rva002CA82C(BfmeE12 *out, const BfmeE12 &in) throw()
{
    if (out)
    {
        ::new ((void *)out) BfmeE12;
        out->x = in.x;
        out->y = in.y;
        out->z = in.z;
    }
}

// Construction is provided by the matched no-exceptions unit.  The /EHsc
// copies here carry a different frame and must not compete at link time.
namespace _STL {
template <> void _Deque_base<BfmeE12, allocator<BfmeE12> >::_M_initialize_map(size_t);
template <> void _Deque_base<BfmeE12, allocator<BfmeE12> >::_M_create_nodes(BfmeE12 **, BfmeE12 **);
template <> deque<BfmeE12>::deque(const deque<BfmeE12> &);
}

// The no-exceptions unit supplies these retail deque helpers.
namespace _STL {
typedef deque<BfmeE12>::iterator E12Iterator;
typedef deque<BfmeE12>::const_iterator E12ConstIterator;
// The no-exceptions unit supplies the rowed forward-range insertion bodies.
template <> template <class ForwardIter> void deque<BfmeE12>::_M_insert_aux(E12Iterator, ForwardIter, ForwardIter, size_type);
template <> template <class ForwardIter> void deque<BfmeE12>::insert(E12Iterator, ForwardIter, ForwardIter, const forward_iterator_tag &);
template <> void deque<BfmeE12>::_M_new_elements_at_front(size_t);
template <> void deque<BfmeE12>::_M_new_elements_at_back(size_t);
template <> E12Iterator __uninitialized_copy_copy<E12ConstIterator, E12Iterator, E12Iterator>(E12ConstIterator, E12ConstIterator, E12Iterator, E12Iterator, E12Iterator, __false_type);
template <> E12Iterator __uninitialized_copy_copy<E12Iterator, E12ConstIterator, E12Iterator>(E12Iterator, E12Iterator, E12ConstIterator, E12ConstIterator, E12Iterator, __false_type);
}

template _STL::E12Iterator _STL::uninitialized_copy<_STL::E12ConstIterator, _STL::E12Iterator>(_STL::E12ConstIterator, _STL::E12ConstIterator, _STL::E12Iterator);
template class _STL::deque<BfmeE12, _STL::allocator<BfmeE12 > >;
