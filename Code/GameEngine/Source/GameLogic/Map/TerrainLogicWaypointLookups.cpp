// cl: /O1 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// TerrainLogic's waypoint and trigger-area lookups, slots 34..39 of the
// TerrainLogic vftable (0x007FB2C8): getWaypointByName, getWaypointByID,
// getClosestWaypointOnPath, getWaypointByPath, isPurposeOfPath and
// getTriggerAreaByName. All but
// getWaypointByPath are Zero Hour's (GameLogic/Map/TerrainLogic.cpp); that
// one has no Zero Hour body and carries Open-BFME-1's name for the same slot
// (its TerrainLogicNameLookups.cpp), which getClosestWaypointOnPath calls for
// a NULL position.
//
// Target facts: every string argument arrives by reference (the callee reads
// the string through the stack slot and never destroys it). The waypoint list
// is the global head at VA 0x00DFEC54 (the data ledger's g_waypointListHead);
// a waypoint keeps its id at +0x04, its name at +0x08, its location at +0x0C,
// the next waypoint at +0x1C and the waypoint linking to it at +0x40 (as
// WaypointLinks.cpp lays it out); its three path labels come back by value
// from the rowed getters 0x0027F5A6, 0x0027F5C1 and 0x0027F5DC (+0x50, +0x54,
// +0x58). BFME 2 adds an empty-name test to getWaypointByName and caches
// getWaypointByID's answers in a map at TerrainLogic+0x56C. The polygon
// trigger list head sits behind the holder pointer at VA 0x00DBD0F4; a
// trigger keeps its next link at +0x3C and its name at +0x40.
//
// Retail registers no unwind state around a compareNoCase whose temporary is
// the only live object, so StringBase<char>'s compareNoCase is declared not
// to throw (as AptSkirmishCallbacks.cpp does for the wide string).
#include "ascii_string.h"
#include "Coord3D.h"

#include <map>

// map/set<unsigned> internals otherwise emit the less<unsigned>::operator()
// COMDAT in a register shape retail's 0x00758C50 does not have. The compare
// is inlined into the map's _M_find (retail's 0x00357180 compares in place),
// so an inline-only specialization keeps it there and emits no copy; a
// declaration-only one would turn this TU's _M_find into a call.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
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

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

template <> int StringBase<char>::compareNoCase(const StringBase<char> &str) const throw();

// The rowed path-label getters (Waypoint::getPathLabel1..3), each named for
// its address; called through a cast because an inline forwarder returning
// the string is not expanded under /EHsc.
class Rva0027F5A6
{
public:
	AsciiString rva0027F5A6();
	char m_pad00[0x50];
private:
	AsciiString m_str; // +0x50
};
class Rva0027F5C1
{
public:
	AsciiString rva0027F5C1();
	char m_pad00[0x54];
private:
	AsciiString m_str; // +0x54
};
class Rva0027F5DC
{
public:
	AsciiString rva0027F5DC();
	char m_pad00[0x58];
private:
	AsciiString m_str; // +0x58
};

class Waypoint
{
public:
	UnsignedInt getID() const { return m_id; }
	const AsciiString &getName() const { return m_name; }
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getNext() const { return m_next; }
	Waypoint *getLinkSource() const { return m_linkSource; }
private:
	void *m_vtbl; // +0x00
	UnsignedInt m_id; // +0x04
	AsciiString m_name; // +0x08
	Coord3D m_location; // +0x0C
	char m_pad18[0x1C - 0x18];
	Waypoint *m_next; // +0x1C
	Waypoint *m_links[8]; // +0x20
	Waypoint *m_linkSource; // +0x40
};

extern Waypoint *g_waypointListHead;

class PolygonTrigger;

struct Rva002E373CHolder
{
	PolygonTrigger *m_head;
};

extern Rva002E373CHolder *g_Va00DBD0F4; // ThePolygonTriggerListPtr holder

class PolygonTrigger
{
public:
	static PolygonTrigger *getFirstPolygonTrigger() { return g_Va00DBD0F4->m_head; }
	PolygonTrigger *getNext() { return m_nextPolygonTrigger; }
	const AsciiString &getTriggerName() const { return m_triggerName; }
private:
	char m_pad00[0x3C];
	PolygonTrigger *m_nextPolygonTrigger; // +0x3C
	AsciiString m_triggerName; // +0x40
};

typedef _STL::map<unsigned int, void *, _STL::less<unsigned int>, _STL::allocator<_STL::pair<const unsigned int, void *> > > WaypointIDMap;

class Image;

// The shared unsigned-key pointer-map operator[] (0x002077D6) that retail
// calls for every such map; the id cache is subscripted through it.
class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual Waypoint *getFirstWaypoint(); // +0x84
	virtual Waypoint *getWaypointByName(const AsciiString &name); // +0x88
	virtual Waypoint *getWaypointByID(UnsignedInt id); // +0x8C
	virtual Waypoint *getClosestWaypointOnPath(const Coord3D *pos, const AsciiString &label); // +0x90
	virtual Waypoint *getWaypointByPath(const AsciiString &label); // +0x94
	virtual Bool isPurposeOfPath(Waypoint *pWay, const AsciiString &label); // +0x98
	virtual PolygonTrigger *getTriggerAreaByName(const AsciiString &name); // +0x9C
private:
	Image *&cachedWaypoint(const UnsignedInt &id) { return (*(ImageSubscriptMap *)&m_waypointsByID)[id]; }

	char m_pad04[0x56C - 0x04];
	WaypointIDMap m_waypointsByID; // +0x56C
};

// ?getWaypointByName@TerrainLogic@@UAEPAVWaypoint@@ABVAsciiString@@@Z @0x00281D4C
Waypoint *TerrainLogic::getWaypointByName( const AsciiString &name )
{
	if (((const StringBase<char> *)&name)->isEmpty())
		return NULL;

	for( Waypoint *way = g_waypointListHead; way; way = way->getNext() )
		if (way->getName() == name)
			return way;

	return NULL;
}

// ?getWaypointByID@TerrainLogic@@UAEPAVWaypoint@@I@Z @0x0028333F
// Zero Hour's walk behind a cache: BFME 2 remembers each id it was asked for,
// a miss included.
Waypoint *TerrainLogic::getWaypointByID( UnsignedInt id )
{
	WaypointIDMap::iterator it = m_waypointsByID.find(id);
	if (it != m_waypointsByID.end())
		return (Waypoint *)(*it).second;

	for( Waypoint *way = g_waypointListHead; way; way = way->getNext() )
		if (way->getID() == id) {
			cachedWaypoint(id) = (Image *)way;
			return way;
		}

	cachedWaypoint(id) = NULL;
	return NULL;
}

// ?getClosestWaypointOnPath@TerrainLogic@@UAEPAVWaypoint@@PBUCoord3D@@ABVAsciiString@@@Z @0x002812BF
// Zero Hour's search; with no position it hands the label to getWaypointByPath.
// The distance reads the location in place, y term first, as Open-BFME-1's
// reconstruction of the same body does.
Waypoint *TerrainLogic::getClosestWaypointOnPath( const Coord3D *pos, const AsciiString &label )
{
	if (pos == NULL)
		return getWaypointByPath(label);

	Real distSqr = 0;
	Waypoint *pClosestWay = NULL;
	if (((const StringBase<char> *)&label)->isEmpty()) {
		return NULL;
	}

	for( Waypoint *way = g_waypointListHead; way; way = way->getNext() ) {
		Bool match = false;
		if (label.compareNoCase(((Rva0027F5A6 *)way)->rva0027F5A6())==0) match = true;
		if (label.compareNoCase(((Rva0027F5C1 *)way)->rva0027F5C1())==0) match = true;
		if (label.compareNoCase(((Rva0027F5DC *)way)->rva0027F5DC())==0) match = true;
		if (match) {
			Real x = way->getLocation()->x;
			Real y = way->getLocation()->y;
			Real newDistSqr = (y-pos->y)*(y-pos->y) + (x-pos->x)*(x-pos->x);
			if (pClosestWay==NULL) {
				pClosestWay = way;
				distSqr = newDistSqr;
			} else if (newDistSqr < distSqr) {
				pClosestWay = way;
				distSqr = newDistSqr;
			}
		}
	}

	return pClosestWay;
}

// ?getWaypointByPath@TerrainLogic@@UAEPAVWaypoint@@ABVAsciiString@@@Z @0x002813EA
// The first waypoint carrying the label, walked back to the start of its path.
Waypoint *TerrainLogic::getWaypointByPath( const AsciiString &label )
{
	if (((const StringBase<char> *)&label)->isEmpty())
		return NULL;

	for( Waypoint *way = g_waypointListHead; way; way = way->getNext() ) {
		Bool match = label.compareNoCase(((Rva0027F5A6 *)way)->rva0027F5A6())==0 ||
			label.compareNoCase(((Rva0027F5C1 *)way)->rva0027F5C1())==0 ||
			label.compareNoCase(((Rva0027F5DC *)way)->rva0027F5DC())==0;
		if (match) {
			while (way->getLinkSource())
				way = way->getLinkSource();
			return way;
		}
	}
	return NULL;
}

// ?isPurposeOfPath@TerrainLogic@@UAE_NPAVWaypoint@@ABVAsciiString@@@Z @0x00281D92
Bool TerrainLogic::isPurposeOfPath( Waypoint *pWay, const AsciiString &label )
{
	if (((const StringBase<char> *)&label)->isEmpty() || pWay==NULL) {
		return false;
	}

	Bool match = false;
	if (label == ((Rva0027F5A6 *)pWay)->rva0027F5A6()) match = true;
	if (label == ((Rva0027F5C1 *)pWay)->rva0027F5C1()) match = true;
	if (label == ((Rva0027F5DC *)pWay)->rva0027F5DC()) match = true;

	return match;
}

// ?getTriggerAreaByName@TerrainLogic@@UAEPAVPolygonTrigger@@ABVAsciiString@@@Z @0x00281E47
PolygonTrigger *TerrainLogic::getTriggerAreaByName( const AsciiString &name )
{
	for (PolygonTrigger* pTrig = PolygonTrigger::getFirstPolygonTrigger(); pTrig; pTrig = pTrig->getNext()) {
		AsciiString trigName = pTrig->getTriggerName();
		if (name == trigName)
			return pTrig;
	}
	return NULL;
}
