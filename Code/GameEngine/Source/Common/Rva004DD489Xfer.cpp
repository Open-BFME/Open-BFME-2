// cl: /O1 /G7 /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?xfer@Rva004DD489@@UAEXPAVXfer@@@Z @0x004DD489 400B.
// Slot 3 xfer of the EmotionTracker entry objects listed at 0x004B1ECB (m_90):
// ObjectID at +0x08 via XferObjectID, int-int map at +0x14, unsigned-short/int
// map at +0x20 (loader inserts, saver copies each key by word before the
// value). Evidence: same-this caller 0x004B1ECB serializes the entry list;
// map pair types and offsets from the loader's insert and the saver's word
// copy. /G7 is load-bearing: the natural unsigned-short key copy emits
// `mov ax,[mem]` only under /G7; without it cl uses the P4 xor+mov idiom and
// the body is 402B (the previous bank's int-cast trick forced movzx, 7 ops).
// Reference: Open-BFME / EmotionTracker.
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
#include <set>
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned short>::operator()(unsigned short const &x,unsigned short const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> pair<unsigned short const, int>::pair(unsigned short const &, int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> bool less<unsigned short>::operator()(unsigned short const &, unsigned short const &) const; }
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
namespace _STL { template <> _Rb_tree_node<pair<int const, int> > * _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::_M_create_node(pair<int const, int> const &); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBGH@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_node<pair<unsigned short const ,int> > * allocator<_Rb_tree_node<pair<unsigned short const ,int> > >::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }

// Keep the already-inlined node comparison local instead of emitting the
// incompatible shared _Rb_tree_base_iterator::operator!= COMDAT.
namespace _STL {
template<class Value, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<Value, LeftTraits>& left,
                              const _Rb_tree_iterator<Value, RightTraits>& right)
{
	return left._M_node != right._M_node;
}
}

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
#include "../../Include/Common/BfmeXfer.h"
#include "../../Include/Common/XferVersion.h"
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *id);
struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};
// Suppress this TU's copy of the ushort/int map's insert_unique: it differs
// from the one ConnectionManager_fileTransfer.cpp emits first, which the link
// keeps. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned short const, int>, _Nonconst_traits<pair<unsigned short const, int> > >, bool> _Rb_tree<unsigned short, pair<unsigned short const, int>, _Select1st<pair<unsigned short const, int> >, Gen_lt_00940b40, allocator<pair<unsigned short const, int> > >::insert_unique(pair<unsigned short const, int> const &); }
class Rva004DD489
{
public:
	virtual void xfer(Xfer *xfer);
private:
	int m_04;
	ObjectID m_08;
	unsigned short m_0C;
	unsigned int m_10;
	_STL::map<int, int> m_14;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_20;
	unsigned int m_2C;
	unsigned int m_30;
};
void Rva004DD489::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	XferObjectID(xfer, &m_08);
	*xfer == m_0C;
	*xfer == m_10;
	int count = (int)m_14.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		int key = 0;
		unsigned int val = 0;
		for (int i = 0; i < count; ++i) {
			XferObjectID(xfer, (ObjectID*)&key);
			*xfer == val;
			m_14[key] = (int)val;
		}
	} else {
		for (_STL::map<int, int>::iterator it = m_14.begin(); it != m_14.end(); ++it) {
			ObjectID key = (ObjectID)(*it).first;
			unsigned int val = (unsigned int)(*it).second;
			XferObjectID(xfer, &key);
			*xfer == val;
		}
	}
	count = (int)m_20.size();
	*xfer == count;
	if (xfer->IsLoading()) {
		unsigned short key2 = 0;
		unsigned int val2 = 0;
		for (int j = 0; j < count; ++j) {
			*xfer == key2;
			*xfer == val2;
			m_20[key2] = (int)val2;
		}
	} else {
		for (_STL::map<unsigned short, int, Gen_lt_00940b40>::iterator jt = m_20.begin(); jt != m_20.end(); ++jt) {
			unsigned short key2 = (*jt).first;
			unsigned int val2 = (unsigned int)(*jt).second;
			*xfer == key2;
			*xfer == val2;
		}
	}
	*xfer == m_2C;
	*xfer == m_30;
}
