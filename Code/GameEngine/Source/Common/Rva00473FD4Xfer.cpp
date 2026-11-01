// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva00473FD4Xfer@@YAPAVXfer@@PAV1@PAV?$map@H_NU?$less@H@_STL@@V?$allocator@U?$pair@$$CBH_N@_STL@@@2@@_STL@@@Z 0x00473FD4 217B evidence: map<int bool> Xfer twin of rowed map<int int> Rva00470222Xfer 0x00470222; version {1,1} via slot 0x28 typename std::map via slot 0x2c count via slot 0x78 isSaving via slot 8; save loop via rowed _M_increment 0x00024250 with per-item Rva00469103Xfer 0x00469103; load throws Map must be empty on load via bfmeFormatText 0x0060C36E then per-item operator[] 0x00470353; caller 0x00474EA8
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,bool> > * _Rb_tree<int,_STL::pair<int const,bool>,_STL::_Select1st<_STL::pair<int const,bool> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,bool> > >::_M_create_node(_STL::pair<int const,bool> const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,bool> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,bool> > *,_STL::_Rb_tree_node<_STL::pair<int const,bool> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,bool> > > >::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,bool> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,bool> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,bool> > *,_STL::_Rb_tree_node<_STL::pair<int const,bool> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,bool> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,bool> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<int const,bool> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,bool> > *,unsigned int) const; }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const,bool>,_STL::_Nonconst_traits<_STL::pair<int const,bool> > >,bool> _Rb_tree<int,_STL::pair<int const,bool>,_STL::_Select1st<_STL::pair<int const,bool> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,bool> > >::insert_unique(_STL::pair<int const,bool> const &); }
namespace _STL { template <> bool & map<int,bool,_STL::less<int>,_STL::allocator<_STL::pair<int const,bool> > >::operator[](int const &); }
// bfme link decl-only end

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

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see System/XferException.cpp).
#include "../../Include/Common/XferException.h"


// Same tag as the rowed pair helper so the call resolves, but the value is
// bool rather than int: retail loads the node value with a byte mov and
// stores through operator[] with a byte mov, which needs a bool lvalue.
struct Rva00469103Pair
{
	int m_id;
	bool m_value;
};
extern Xfer &Rva00469103Xfer(Xfer *xfer, Rva00469103Pair *pair);

typedef _STL::map<int, bool> IntBoolMap;

Xfer *Rva00473FD4Xfer(Xfer *xfer, IntBoolMap *map)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	*xfer == reinterpret_cast<Xfer::Version &>(version);

	UnsignedInt count = map->size();
	(*xfer == "std::map") == count;

	if (xfer->IsStoring()) {
		IntBoolMap::iterator cur = map->begin();
		IntBoolMap::iterator last = map->end();
		for (; cur != last; ++cur) {
			Rva00469103Pair item;
			item.m_id = cur->first;
			item.m_value = cur->second;
			Rva00469103Xfer(xfer, &item);
		}
	} else {
		if (!map->empty()) {
			throw XferException(4, "Map must be empty on load");
		}
		Rva00469103Pair item;
		item.m_id = 0;
		item.m_value = 0;
		while (count != 0) {
			--count;
			Rva00469103Xfer(xfer, &item);
			(*map)[item.m_id] = item.m_value;
		}
	}
	return xfer;
}
