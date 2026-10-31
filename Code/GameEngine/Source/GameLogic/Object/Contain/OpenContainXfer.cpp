// cl: /G7 /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// OpenContain::xfer, slot 3 of the OpenContain module vftable, reviewed against
// the BFME1 reference OpenContain::xfer (reference/open-bfme-1 revision
// ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f, game/GameEngine/Source/GameLogic/
// Object/Contain/OpenContain.cpp).
//
// Target facts (0x00465EF1, 1191 bytes): UpdateModule::xfer 0x0044DF9F, then
// the light-CRC gate (Xfer slot +0x10) and Version 1/1. The contain list at
// +0x54 is saved as object IDs read from Object +0x74; on load an occupied
// list is emptied through list<int>::erase 0x00438539, GameLogic::destroyObject
// 0x00242C09 and clear 0x0023DAA5 before the IDs are queued in the list at
// +0x74 (push_back 0x0005548F). The id->name map at +0x3C is filled through
// the subscript 0x004650A0 and the two id->int maps at +0x48 and +0x5C (the
// latter with a 16-bit count, raw 4-byte values and XferException(5) 0x0060C36E
// when it is not empty on load) and the counted map at +0xF0 through
// map<int,int>::operator[] 0x0028932C. Scalars at +0x78/+0x7C/+0x80/+0x68/
// +0x70, BitFlags<591>::xfer 0x000BB710 on +0x84, Coord3D +0xD0, Bool +0xDC,
// ObjectIDs +0xE4/+0xE8 (XferObjectID 0x003060B2), Int +0xEC, the exit path
// at +0x6C and Bools +0xDE/+0xE1/+0xDD.
//
// Carried from the donor: the contain-list, enter/exit-info and rally-point
// names and the save/load split. The other member names are offset labels.
// /G7 is required: without it the 16-bit count load gains a xor eax,eax.
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


#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::_Node *list<int, allocator<int> >::_M_create_node(const int &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Lib/Coord3DBase.h"
#include "../../../Common/GameLogicObjectLookupView.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class UnicodeString;
class PooledString;
struct XferUnknown11;
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

class AsciiString;
struct Coord3DBase;
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

void XferObjectID(Xfer *xfer, ObjectID *value);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

extern GameLogic *TheGameLogic;

#include "../object.h"

template <int NUMBITS> class BitFlags
{
public:
	void xfer(Xfer *xfer);
private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<591> ModelConditionFlags;

class Rva004650A0 : public _STL::map<int, AsciiString>
{
public:
	AsciiString &rva004650A0(const int &key);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	char m_pad04[0x38 - 0x04];
};

class OpenContain : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Int m_unk38;
	Rva004650A0 m_objectNames; // +0x3C
	_STL::map<Int, Int> m_objectValues; // +0x48
	_STL::list<Int> m_containList; // +0x54
	UnsignedInt m_containListSize; // +0x58
	_STL::map<Int, Int> m_objectEnterExitInfo; // +0x5C
	UnsignedInt m_unk68;
	Int m_whichExitPath; // +0x6C
	UnsignedInt m_unk70;
	_STL::list<Int> m_xferContainIDList; // +0x74
	UnsignedInt m_unk78;
	UnsignedInt m_unk7C;
	UnsignedInt m_unk80;
	ModelConditionFlags m_conditionState; // +0x84
	Coord3D m_rallyPoint; // +0xD0
	Bool m_rallyPointExists; // +0xDC
	Bool m_unkDD;
	Bool m_unkDE;
	Bool m_unkDF;
	Bool m_unkE0;
	Bool m_unkE1;
	ObjectID m_unkE4;
	ObjectID m_unkE8;
	Int m_unkEC;
	_STL::map<Int, Int> m_objectCounts; // +0xF0
};

void OpenContain::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);

	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 1);
	*xfer == version;

	Int objectID;
	if (xfer->IsStoring())
	{
		*xfer == m_containListSize;
		for (_STL::list<Int>::const_iterator it = m_containList.begin(); it != m_containList.end(); ++it)
		{
			objectID = ((Object *)*it)->getID();
			XferObjectID(xfer, (ObjectID *)&objectID);
		}
	}
	else
	{
		if (!m_containList.empty())
		{
			m_containListSize = 0;
			for (_STL::list<Int>::iterator it = m_containList.begin(); it != m_containList.end(); )
			{
				Object *object = (Object *)*it;
				it = m_containList.erase(it);
				TheGameLogic->destroyObject(object);
			}
			m_containList.clear();
		}

		*xfer == m_containListSize;
		for (UnsignedInt i = 0; i < m_containListSize; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&objectID);
			m_xferContainIDList.push_back(objectID);
		}
	}

	if (xfer->IsStoring())
	{
		Int nameCount = m_objectNames.size();
		*xfer == nameCount;
		for (Rva004650A0::const_iterator it = m_objectNames.begin(); it != m_objectNames.end(); ++it)
		{
			AsciiString name;
			Int id = (*it).first;
			name = (*it).second;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == name;
		}
	}
	else
	{
		Int nameCount;
		*xfer == nameCount;
		for (Int i = 0; i < nameCount; ++i)
		{
			Int id;
			AsciiString name;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == name;
			m_objectNames.rva004650A0(id) = name;
		}
	}

	if (xfer->IsStoring())
	{
		Int count = m_objectValues.size();
		*xfer == count;
		for (_STL::map<Int, Int>::const_iterator it = m_objectValues.begin(); it != m_objectValues.end(); ++it)
		{
			Int id = (*it).first;
			Int value = (*it).second;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == value;
		}
	}
	else
	{
		Int count;
		*xfer == count;
		for (Int i = 0; i < count; ++i)
		{
			Int id;
			Int value;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == value;
			m_objectValues[id] = value;
		}
	}

	*xfer == m_unk78;
	*xfer == m_unk7C;
	*xfer == m_unk80;
	*xfer == m_unk68;
	*xfer == m_unk70;
	m_conditionState.xfer(xfer);
	*xfer == asBase(m_rallyPoint);
	*xfer == m_rallyPointExists;
	XferObjectID(xfer, &m_unkE4);
	XferObjectID(xfer, &m_unkE8);
	*xfer == m_unkEC;

	UnsignedShort enterExitCount = m_objectEnterExitInfo.size();
	*xfer == enterExitCount;
	Int enterExitType;
	if (xfer->IsStoring())
	{
		for (_STL::map<Int, Int>::const_iterator it = m_objectEnterExitInfo.begin(); it != m_objectEnterExitInfo.end(); ++it)
		{
			objectID = (*it).first;
			XferObjectID(xfer, (ObjectID *)&objectID);
			enterExitType = (*it).second;
			xfer->XferRawBytes(&enterExitType, sizeof(enterExitType));
		}
	}
	else
	{
		if (m_objectEnterExitInfo.size() != 0)
			throw XferException(5, 0);

		for (UnsignedShort i = 0; i < enterExitCount; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&objectID);
			xfer->XferRawBytes(&enterExitType, sizeof(enterExitType));
			m_objectEnterExitInfo[objectID] = enterExitType;
		}
	}

	*xfer == m_whichExitPath;

	UnsignedInt countCount = m_objectCounts.size();
	*xfer == countCount;
	if (xfer->IsLoading())
	{
		Int id = 0;
		UnsignedInt value = 0;
		for (UnsignedInt i = 0; i < countCount; ++i)
		{
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == value;
			m_objectCounts[id] = value;
		}
	}
	else
	{
		for (_STL::map<Int, Int>::const_iterator it = m_objectCounts.begin(); it != m_objectCounts.end(); ++it)
		{
			Int id = (*it).first;
			UnsignedInt value = (*it).second;
			XferObjectID(xfer, (ObjectID *)&id);
			*xfer == value;
		}
	}

	*xfer == m_unkDE;
	*xfer == m_unkE1;
	*xfer == m_unkDD;
}

