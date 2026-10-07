// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// The insert path of map<int, vector<vector<BfmePod88> >>: its pair copy (0x0050118D) calls the rowed vector<vector<BfmePod88>> copy constructor (VectorPod88CopyConstructor.cpp), after a
// one-word key copy. The key is a signed 32-bit type (the inserts compare it
// signed); int stands in, as in stlport_map_int_int_os.cpp. Recipe and flags
// are stlport_map_int_vector_pod128.cpp's.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>

struct BfmePod88
{
	char m_body[88];
};

typedef _STL::map<int, _STL::vector<_STL::vector<BfmePod88> > > IntPod88VectorVectorMap;

template class _STL::map<int, _STL::vector<_STL::vector<BfmePod88> > >;
