// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// hash_map<int, vector<ScienceType>>: its pair copy (0x0041E7D5) calls the rowed vector<ScienceType> copy constructor (ProductionPrerequisiteCopyCtor.cpp) for the value, and its node constructor (0x0041EA07) zeroes the next link and places the pair at +4.
// The key is a 32-bit int-hashed type; int stands in, as in
// stlport_pod_hash_bodies.cpp, whose whole-class instantiation this follows.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

template class _STL::hash_map<int, _STL::vector<ScienceType>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::vector<ScienceType> > > >;

template bool _STL::operator!=(const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &, const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &);
