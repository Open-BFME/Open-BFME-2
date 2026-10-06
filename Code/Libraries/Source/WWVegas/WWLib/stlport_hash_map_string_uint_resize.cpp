// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_HASHTABLE_NEW_NODE_NOFORCEINLINE /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
//
// hashtable<string, unsigned int>::resize at retail 0x0060CD36 (194B).
// String-keyed rehash: old bucket count from +4/+8, _M_next_size growth,
// fresh vector<void*> then per-node __stl_string_hash div new_n rechain,
// swap and free. Callers 0x0060D1BD (insert_unique shape); neighbours
// 0x0060CD16 (string bkt_num) and 0x0060CFFF (_Construct pair<string,I>).

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <string>
#include <hash_map>

template class _STL::hash_map<_STL::string, unsigned int,
	_STL::hash<_STL::string>, _STL::equal_to<_STL::string>,
	_STL::allocator<_STL::pair<const _STL::string, unsigned int> > >;
