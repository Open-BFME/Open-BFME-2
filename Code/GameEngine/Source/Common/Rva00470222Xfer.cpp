// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport46
// 0x00470222 217B evidence: map<int int> Xfer twin of vector sister Rva0046EFDBXfer; version {1,1} via slot 0x28
// typename "std::map" via slot 0x2c count via slot 0x78 isSaving via slot 8; save loop via rowed _M_increment
// 0x0024250 with per-item Rva00469124Xfer 0x00469124; load throws "Map must be empty on load" via bfmeFormatText
// 0x0060C36E then per-item operator[] 0x0028932C; caller 0x00473F81.
#include <map>

// Preserve STLport's inlined walk without emitting a competing size-profile
// wrapper. stlport_map_int_int.cpp owns the complete retail entry at 0x169ED0.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > > &
_Rb_tree_iterator<pair<const int, int>, _Nonconst_traits<pair<const int, int> > >::operator++()
{
    _M_node = _Rb_global_inst::_M_increment(_M_node);
    return *this;
}
}
// Inline the iterator steps as retail's speed-form tree bodies do.
namespace _STL { template <> __declspec(dllimport) __forceinline _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--() { _M_node = _Rb_global_inst::_M_decrement(_M_node); return *this; } }
namespace _STL { template <> __declspec(dllimport) __forceinline pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &a, bool const &b) : first(a), second(b) {} }
// empty() too: stlport_map_int_int.cpp owns the retail entry at 0x620050.
namespace _STL { template <> __declspec(dllimport) __forceinline bool _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::empty() const { return _M_node_count == 0; } }
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

// Same tag as the rowed pair helper so the call resolves, but the key is int
// rather than ObjectID: retail pushes &pair straight into map<int,int>::operator[](const int &),
// which needs an int lvalue (an ObjectID would force a temp copy elsewhere).
struct Rva00469124Pair
{
	int m_id;
	int m_value;
};
extern Xfer &Rva00469124Xfer(Xfer *xfer, Rva00469124Pair *pair);

typedef _STL::map<int, int> IntIntMap;

Xfer *Rva00470222Xfer(Xfer *xfer, IntIntMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = map->size();
	(*xfer == "std::map") == count;

	if (xfer->IsStoring()) {
		IntIntMap::iterator cur = map->begin();
		IntIntMap::iterator last = map->end();
		for (; cur != last; ++cur) {
			Rva00469124Pair item;
			item.m_id = cur->first;
			item.m_value = cur->second;
			Rva00469124Xfer(xfer, &item);
		}
	} else {
		if (!map->empty()) {
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		Rva00469124Pair item;
		item.m_id = 0;
		item.m_value = 0;
		while (count != 0) {
			--count;
			Rva00469124Xfer(xfer, &item);
			(*map)[item.m_id] = item.m_value;
		}
	}
	return xfer;
}

// ?g_guardTargetTypeThrowInfo@@3HA: matched references place it at VA 0xcffd18; also referenced as ?g_rva008ffd18ThrowInfo@@3HA, ?g_rva005c5100ThrowInfo@@3HA.
int g_guardTargetTypeThrowInfo = 0;
#pragma comment(linker, "/alternatename:?g_rva008ffd18ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")

// The (void *, void *) declaration above is a C++ overload, so calls spell
// ?_CxxThrowException@@YGXPAX0@Z; retail calls the MSVC 7.1 throw helper
// __CxxThrowException@8 (its import thunk at 0x00629094). Same ABI: bind the spelling.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
