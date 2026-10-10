// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>
#include <memory>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

struct Rva0047BAF7Element { unsigned opaque;bool operator<(const Rva0047BAF7Element&)const;bool operator==(const Rva0047BAF7Element&)const; };


// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva0047BAF7Element *, _STL::allocator<Rva0047BAF7Element *> >::remove(Rva0047BAF7Element *const &);
