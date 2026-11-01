// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?xfer@HordeSiegeEngineContain@@MAEXPAVXfer@@@Z, retail 0x0047D36A, 464 bytes.
// Slot 3 of ??_7HordeSiegeEngineContain 0x00C474A0 (installed by the rowed
// ctor 0x0047D247 and dtor 0x0047CFB2). The SiegeEngineContainXfer body
// over the HordeTransportContain base (xfer 0x0047714A first), with the
// members 0x0C further on: the rider list at +0x128 with its count at
// +0x12C (the HordeSiegeEngineContainRiders view), the bool at +0x130, the
// map<int,int> at +0x134 and the queued-id list at +0x140. Member names not
// recovered.

#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>
namespace _STL {
}


namespace _STL {
typedef _Rb_tree_iterator<pair<const int,int>,_Nonconst_traits<pair<const int,int> > > CBIterator;
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator++(){_M_node=_Rb_global_inst::_M_increment(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator--(){_M_node=_Rb_global_inst::_M_decrement(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator::_Rb_tree_iterator(const CBIterator&x){_M_node=x._M_node;}
}


namespace _STL {
typedef pair<CBIterator,bool> CBInsertResult;
template<> __declspec(dllimport) __forceinline CBInsertResult::pair(const CBIterator&a,const bool&b):first(a),second(b){}
}


namespace _STL {
typedef _Rb_tree<int,pair<const int,void*>,_Select1st<pair<const int,void*> >,less<int>,allocator<pair<const int,void*> > > CBPointerTree;
template<> CBPointerTree::~_Rb_tree();
}


namespace _STL {
typedef _Rb_tree_node<pair<const int,int> > CBNode;
typedef _STLP_alloc_proxy<CBNode*,CBNode,allocator<CBNode> > CBNodeProxy;
template<> __declspec(dllimport) __forceinline CBNode* allocator<CBNode>::allocate(size_type n,const void*)const {return n ? reinterpret_cast<CBNode*>(allocator<char>::allocate(n*sizeof(CBNode),0)) : 0;}
template<> __declspec(dllimport) __forceinline CBNode* CBNodeProxy::allocate(size_t n){return static_cast<allocator<CBNode>&>(*this).allocate(n,0);}
template<> __declspec(dllimport) __forceinline void CBNodeProxy::deallocate(CBNode*p,size_t n){static_cast<allocator<CBNode>&>(*this).deallocate(p,n);}
}

namespace _STL {
template<> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned&a,const unsigned&b)const{return a<b;}
template<> __declspec(dllimport) __forceinline pair<const int,int>::pair(const int&a,const int&b):first(a),second(b){}
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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

#include "../../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *id);

#include "../object.h"


extern GameLogic *TheGameLogic;

class HordeTransportContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x128 - 0x04];
};

class HordeSiegeEngineContain : public HordeTransportContain
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	_STL::list<int> m_128;
	unsigned int m_12C;
	bool m_130;
	_STL::map<int, int> m_134;
	_STL::list<int> m_140;
};

// ?xfer@HordeSiegeEngineContain@@MAEXPAVXfer@@@Z @0x0047C322
void HordeSiegeEngineContain::xfer(Xfer *xfer)
{
	HordeTransportContain::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	ObjectID id;
	if (xfer->IsStoring())
	{
		*xfer == m_12C;
		for (_STL::list<int>::iterator it = m_128.begin(); it != m_128.end(); ++it)
		{
			id = ((Object *)*it)->getID();
			XferObjectID(xfer, &id);
		}
	}
	else
	{
		if (!m_128.empty())
		{
			m_12C = 0;
			for (_STL::list<int>::iterator it = m_128.begin(); it != m_128.end(); )
			{
				Object *rider = (Object *)*it;
				it = m_128.erase(it);
				TheGameLogic->destroyObject(rider);
			}
			m_128.clear();
		}
		*xfer == m_12C;
		for (unsigned int i = 0; i < m_12C; ++i)
		{
			XferObjectID(xfer, &id);
			m_140.push_back(reinterpret_cast<const int &>(id));
		}
	}

	*xfer == m_130;

	if (xfer->IsStoring())
	{
		int count = m_134.size();
		*xfer == count;
		for (_STL::map<int, int>::iterator it = m_134.begin(); it != m_134.end(); ++it)
		{
			ObjectID key = (ObjectID)it->first;
			int value = it->second;
			XferObjectID(xfer, &key);
			*xfer == value;
		}
	}
	else
	{
		int count;
		*xfer == count;
		for (int i = 0; i < count; ++i)
		{
			ObjectID key;
			int value;
			XferObjectID(xfer, &key);
			*xfer == value;
			m_134[reinterpret_cast<const int &>(key)] = value;
		}
	}
}
