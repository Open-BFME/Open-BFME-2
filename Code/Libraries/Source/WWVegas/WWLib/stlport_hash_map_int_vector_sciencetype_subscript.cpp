// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// hash_map<int, vector<ScienceType>>::operator[] @0x0041EB1A 179B.
// Retail finds the key via hashtable find (rowed dup 0x00148B27), inserts a
// default pair on miss via _M_insert 0x0041EAD1 and returns the mapped vector.
// Caller 0x0041EC73 pushes key+value and reuses the value push for the
// following vector assign 0x0021C21B; callee itself takes one arg (ret 4).
// Evidence: STLport _hash_map.h operator[] shape, prev/next rows in this
// family, callers at 0x0041ECEF/0x0041ED6A.

#include <hash_map>
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

template _STL::vector<ScienceType> &_STL::hash_map<int, _STL::vector<ScienceType>, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, _STL::vector<ScienceType> > > >::operator[](const int &);
