// cl: -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// stlport

// STLport hashtable<string,int,...>::_M_bkt_num_key(const key_type&, size_t) is
// an inline member of the hash_map's _Ht in <hash_map>:
//     size_type _M_bkt_num_key(const key_type& __key, size_t __n) const
//     { return _M_hash(__key) % __n; }
// The BFME1 donor XferBlockWriter_rva009D86E0.cpp only emits it through the
// map's own instantiation. Retail 0x0060CB97 pushes the key, calls
// __stl_string_hash (0x0060C9F0) and divides by n; the member is emitted here
// by instantiating only this member of the same hashtable.
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
// <memory> before the access override keeps __node_alloc's _M_allocate and
// _M_deallocate private (CAPAXI/CAXPAXI), the spelling of their rowed owners.
#include <memory>
#define private public
#include <hash_map>
#undef private
#include <string>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D86E0String;
typedef _STL::pair<const Rva009D86E0String, int> Rva009D86E0Pair;

template unsigned int _STL::hashtable<
	Rva009D86E0Pair,
	Rva009D86E0String,
	_STL::hash<Rva009D86E0String>,
	_STL::_Select1st<Rva009D86E0Pair>,
	_STL::equal_to<Rva009D86E0String>,
	_STL::allocator<Rva009D86E0Pair> >::_M_bkt_num_key(const Rva009D86E0String &, unsigned int) const;
