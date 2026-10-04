// cl: -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// stlport

// STLport hashtable<string,int,...>::_M_bkt_num_key(const key_type&, size_t) is
// an inline member of the hash_map's _Ht in <hash_map>:
//     size_type _M_bkt_num_key(const key_type& __key, size_t __n) const
//     { return _M_hash(__key) % __n; }
// The BFME1 donor XferBlockWriter_rva009D86E0.cpp only emits it through the
// map's own instantiation. Retail 0x0060CB97 pushes the key, calls
// __stl_string_hash (0x0060C9F0) and divides by n; the member is emitted here
// by explicit instantiation of the same hashtable, donor's own body omitted.
#define _STLP_NO_EXCEPTIONS 1
#define private public
#include <hash_map>
#undef private
#include <string>
#include <string.h>

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva009D86E0String;
typedef _STL::pair<const Rva009D86E0String, int> Rva009D86E0Pair;

template class _STL::hashtable<
	Rva009D86E0Pair,
	Rva009D86E0String,
	_STL::hash<Rva009D86E0String>,
	_STL::_Select1st<Rva009D86E0Pair>,
	_STL::equal_to<Rva009D86E0String>,
	_STL::allocator<Rva009D86E0Pair> >;
