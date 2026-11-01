// cl: /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xferTheSellList@BuildAssistant@@QAEXPAVXfer@@@Z, retail 0x003924FE
// (204 bytes).
// Identity (target): WorldBuilder's debug BuildAssistant.cpp:497
// BuildAssistant::xferTheSellList (align lead) and Zero Hour's body agree
// with retail: count the sell list, move the count as an Int, then on load
// clear the list and append a new ObjectSellInfo per entry (id through
// XferObjectID, sell frame as an unsigned int), on save move each entry.
// Layout (target): the sell list at BuildAssistant+0x0C; a 0x0C-byte
// ObjectSellInfo (vtable, id +0x04, frame +0x08) from plain operator new.
// The list's clear and push_back are the folded four-byte STLport bodies
// (0x0023DAA5, 0x0005548F).
#include "Common/Snapshot.h"
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
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

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};



enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

typedef unsigned int UnsignedInt;
class ObjectSellInfo
{
public:
	ObjectSellInfo( void ) : m_id( INVALID_OBJECT_ID ), m_sellFrame( 0 ) {}
	// Empty, as rowed in BuildAssistantXfer.cpp (0x003916A4): visible here so the
	// scalar deleting dtor this unit emits inlines it like retail's 0x003919D9.
	virtual ~ObjectSellInfo( void ) {}
	__forceinline void deleteInstance() { ::delete this; }

	ObjectID m_id;				// +0x04
	UnsignedInt m_sellFrame;		// +0x08
};

typedef _STL::list< ObjectSellInfo * > ObjectSellList;
typedef ObjectSellList::iterator ObjectSellListIterator;

// Retail insert (0x005925E2) calls the node creator at 0x000B6447 out of line.
namespace _STL {
template <> __declspec(noinline) _List_node<ObjectSellInfo *> *
list<ObjectSellInfo *>::_M_create_node(ObjectSellInfo *const &value)
{
    _Node *node = this->_M_node.allocate(1);
    _STLP_TRY {
        _Construct(&node->_M_data, value);
    }
    _STLP_UNWIND(this->_M_node.deallocate(node, 1));
    return node;
}
}


typedef bool Bool;
typedef int Int;
typedef float Real;
class Object;
class Player;
class ThingTemplate;
class Rva0039205C;
struct Coord3D;
enum LegalBuildCode;
enum CanMakeType;
class BuildAssistant
{
public:
	void xferTheSellList(Xfer *xfer);
	bool rva00392DC0(Object *builder, const ThingTemplate *what, const Coord3D *pos, Player *player, unsigned kind, Object **result);
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual void reset( void );		// +0x24
	virtual void update( void );		// +0x28
	virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Object *buildObjectNow(Object *constructorObject, const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer);	// +0x38
	virtual void slot15();
	virtual LegalBuildCode isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, Real angle, UnsignedInt options, Object *builderObject, Player *player);	// +0x40
	virtual Bool isLocationClearOfObjects(const Coord3D *worldPos, const ThingTemplate *build, Real angle, Object *builderObject, UnsignedInt options, Player *player, Bool flag);	// +0x44
	virtual Bool rva0039361E(const Coord3D *pos, const ThingTemplate *whatToBuild, Real angle, Object *builder, Player *unused);	// +0x48
	virtual void addBibs(const Coord3D *worldPos, const ThingTemplate *build);	// +0x4C
	virtual bool slot20(Rva0039205C *tiles, Object *builder, const ThingTemplate *what, const Coord3D *pos, unsigned kind);
	virtual Bool rva0039321C(Rva0039205C *info, Object *first, Object *second, UnsignedInt key, Bool recursed);	// +0x54
	virtual void slot22();
	virtual Bool rva00391A70(const ThingTemplate *whatToBuild, const Object *builder);	// +0x5C
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x60
	virtual Bool isPossibleToMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int revivalIndex) const;	// +0x64
	virtual void sellObject(Object *obj);	// +0x68

	void iterateFootprint(const ThingTemplate *build, Real buildOrientation, const Coord3D *worldPos, Real sampleResolution, void (*func)(const Coord3D *samplePoint, void *userData), void *userData);
	Bool isRemovableForConstruction(Object *obj);
	Bool rva00391AA1(const ThingTemplate *builder, const ThingTemplate *what);
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *owningPlayer);

private:
	unsigned char m_pad04[0x0C - 0x04];
	ObjectSellList m_sellList;		// +0x0C
};

void BuildAssistant::xferTheSellList(Xfer *xfer)
{
	ObjectSellInfo *sellInfo;

	int count = 0;
	ObjectSellListIterator it;
	for (it = m_sellList.begin(); it != m_sellList.end(); ++it)
		count++;
	*xfer == count;

	if (xfer->IsLoading())
	{
		m_sellList.clear();
		int i;
		for (i = 0; i < count; i++)
		{
			sellInfo = new ObjectSellInfo;
			XferObjectID(xfer, &sellInfo->m_id);
			*xfer == sellInfo->m_sellFrame;
			m_sellList.push_back(sellInfo);
		}
	}
	else
	{
		for (it = m_sellList.begin(); it != m_sellList.end(); ++it)
		{
			sellInfo = (*it);
			XferObjectID(xfer, &sellInfo->m_id);
			*xfer == sellInfo->m_sellFrame;
			count--;
		}
	}
}
