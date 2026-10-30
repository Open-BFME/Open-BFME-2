// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
struct Rva004DA329Element {
 Rva004DA329Element(); Rva004DA329Element(const Rva004DA329Element&);
 ~Rva004DA329Element(); Rva004DA329Element&operator=(const Rva004DA329Element&);
 // The native header allocation is 56 bytes; its tree-node links take 16.
 // Independently rowed voice-tree nodes also carry 40-byte values.
 // This reserves storage only; the original element identity remains unknown.
 char bytes[40];
};
bool operator<(const Rva004DA329Element&,const Rva004DA329Element&);
namespace _STL {
typedef _Rb_tree<Rva004DA329Element, Rva004DA329Element,
    _Identity<Rva004DA329Element>, less<Rva004DA329Element>,
    allocator<Rva004DA329Element> > NativeTreeView;

// This constructor-only unit needs no local destruction machinery.
template <> NativeTreeView::~_Rb_tree();

template <> NativeTreeView::_Rb_tree(const less<Rva004DA329Element> &compare,
                                    const allocator<Rva004DA329Element> &alloc)
    : _Base(alloc), _M_node_count(0), _M_key_compare(compare)
{
    // Retail copies this representation byte even for an empty comparator.
    // Its value and the original comparator's identity are not established.
    *reinterpret_cast<unsigned char *>(&_M_key_compare) =
        *reinterpret_cast<const unsigned char *>(&compare);
    _M_empty_initialize();
}
}

template _STL::set<Rva004DA329Element>::set();
