// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// The insert path of map<int, vector<BfmePod128> >. Target evidence: the pair
// copy it places calls the rowed vector<BfmePod128> copy constructor
// (0x0032ADC8, stlport_pod_vector_bodies.cpp) for the value at +4, after a
// one-word key copy, and the node constructor allocates 0x20 bytes (a 0x10-byte
// tree header plus the 0x10-byte pair). The tree bodies are the int-keyed ones
// stlport_map_int_int_os.cpp lands for map<int, int>, with its flags.

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>

struct BfmePod128 { int a[32]; };

typedef _STL::map<int, _STL::vector<BfmePod128> > IntPod128VectorMap;

template class _STL::map<int, _STL::vector<BfmePod128> >;

// Retail 0x0032C58A, 27 bytes: build the map's value pair by value through its
// (const int &, const vector &) constructor (0x0032BFCB). Rva0033BEF5Make's
// shape, over this pair; the name keeps the address.
IntPod128VectorMap::value_type Rva0032C58AMake(const int &key, const _STL::vector<BfmePod128> &value);
IntPod128VectorMap::value_type Rva0032C58AMake(const int &key, const _STL::vector<BfmePod128> &value)
{
	return IntPod128VectorMap::value_type(key, value);
}
