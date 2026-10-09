// ?rva002F4115@Pathfinder@@QAE_NPAVObject@@HHPAVLocomotorSet@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva002F4115@Pathfinder@@QAE_NPAVObject@@HHPAVLocomotorSet@@@Z, retail
// 0x002F4115..0x002F436F (602 bytes, EH, ret 0x10).
//
// Waypoint-graph zone reachability (WB twin 0x00D5F260, callgraph score
// 2.0): fails at once for an object whose byte getter 0x0028B984 is set or
// that has neither an AI (+0x258) nor a waypoint. The locomotor surfaces
// come from the waypoint (+0x10) or the AI (+0x1DC); with the template's
// +0x56C/+0x634 values and Object 0x0028AC62/0x0028AFBB they form the zone
// query passed with each cell zone to the zone manager at +0x460 (rowed
// 0x0053241F). Every path waypoint (0x002E6ECA) valid for the unit is
// filed by the effective zone of its cell (getLayerForDestination
// 0x002802FE, cell lookup 0x001E3647) in a zone->waypoint multimap and a
// waypoint->zone map. A breadth-first walk over zones from the start zone
// then follows each waypoint's links (Waypoint::getLink 0x00085404) and
// returns whether the goal zone is reached.
// The containers are STLport 4.5.3 instantiations whose out-of-line members
// are rowed under folded spellings; each is reached by that spelling
// (casts below) and kept out of line by an explicit specialization
// declaration. Names are address-derived.

#include <map>
#include <set>
#include <deque>

typedef int Int;
typedef bool Bool;

class Object;
struct Coord3D { float x, y, z; };

enum PathfindLayerEnum { LAYER_INVALID = 0 };

class ThingTemplate
{
public:
	char m_pad000[0x56C];
	Int m_56C;
	char m_pad570[0x634 - 0x570];
	Bool m_634;
};

struct Rva0028B984ByteField
{
	unsigned char get() const;
};

class AIUpdateInterface
{
public:
	char m_pad000[0x1DC];
	Int m_locomotorSurfaces; // +0x1DC
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAI() { return m_ai; }
	bool rva0028AC62() const;
	bool rva0028AFBB() const;
private:
	char m_pad000[4];
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0x258 - 0x08];
	AIUpdateInterface *m_ai; // +0x258
};

class LocomotorSet
{
public:
	char m_pad00[0x10];
	Int m_validSurfaces; // +0x10
};

class Waypoint
{
public:
	bool isValidUnitType(Object *obj);
	Waypoint *getLink(Int index) const;
	Int getNumLinks() const { return m_numLinks; }
	char m_pad00[0x0C];
	Coord3D m_location; // +0x0C
	char m_pad18[0x1C - 0x18];
	Waypoint *m_next; // +0x1C
	char m_pad20[0x4C - 0x20];
	Int m_numLinks; // +0x4C
};

struct Rva002E6ECA
{
	int get() const;
};

class TerrainLogic
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21)
	G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29) G(30) G(31) G(32)
#undef G
	virtual Waypoint *getFirstWaypoint(); // +0x84
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct PathfindCellView
{
	char m_pad00[8];
	unsigned short m_zone; // +0x08
};

struct ZoneQuery
{
	Int m_surfaces;      // +0x00
	Bool m_04;           // +0x04
	Bool m_05;           // +0x05
	Int m_08;            // +0x08
	Bool m_0C;           // +0x0C
};

class Rva002E99F9Sub460
{
public:
	unsigned short rva0053241F(void *query, unsigned short zone);
};

// Folded element spellings of the rowed STLport members.
struct Rva002F307AElement {
	Rva002F307AElement(); Rva002F307AElement(const Rva002F307AElement &);
	~Rva002F307AElement(); Rva002F307AElement &operator=(const Rva002F307AElement &);
	char bytes[8];
};
bool operator<(const Rva002F307AElement &, const Rva002F307AElement &);
struct Rva002F0BB5Element { char bytes[1]; bool operator<(const Rva002F0BB5Element &) const; bool operator==(const Rva002F0BB5Element &) const; };
struct Rva002F0B8AElement { char bytes[1]; bool operator<(const Rva002F0B8AElement &) const; bool operator==(const Rva002F0B8AElement &) const; };
struct Rva002F1DA1Mapped { int a; };
struct Rva002F3759Compare { bool operator()(unsigned int a, unsigned int b) const { return a < b; } };
struct BfmeWordValue4
{
	unsigned int bits;
	BfmeWordValue4() {}
	~BfmeWordValue4() {}
};

typedef _STL::multiset<int> FoldZoneTreeCtor;                         // 0x002F3039
typedef _STL::map<int, Rva002F0B8AElement> FoldZoneTreeDtorMap;       // 0x002F0B8A
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F0B8AElement >, _STL::_Select1st<_STL::pair<const int, Rva002F0B8AElement > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F0B8AElement > > > FoldZoneTreeDtor;
typedef _STL::multimap<int, Rva002F1DA1Mapped> FoldZoneInsertMap;     // 0x002F1DA1
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F1DA1Mapped >, _STL::_Select1st<_STL::pair<const int, Rva002F1DA1Mapped > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F1DA1Mapped > > > FoldZoneInsert;
typedef _STL::multimap<int, int> FoldZoneRangeMap;                    // 0x002F1C89
typedef _STL::_Rb_tree<int, _STL::pair<const int, int >, _STL::_Select1st<_STL::pair<const int, int > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, int > > > FoldZoneRange;
typedef _STL::set<Rva002F307AElement> FoldWayTreeCtor;                // 0x002F307A
typedef _STL::map<int, Rva002F0BB5Element> FoldWayTreeDtorMap;        // 0x002F0BB5
typedef _STL::_Rb_tree<int, _STL::pair<const int, Rva002F0BB5Element >, _STL::_Select1st<_STL::pair<const int, Rva002F0BB5Element > >, _STL::less<int >, _STL::allocator<_STL::pair<const int, Rva002F0BB5Element > > > FoldWayTreeDtor;
typedef _STL::map<unsigned int, unsigned int, Rva002F3759Compare> FoldWayIndex; // 0x002F3759
typedef _STL::map<unsigned int, void *> FoldWayFindMap;               // 0x00357180
typedef _STL::_Rb_tree<unsigned int, _STL::pair<const unsigned int, void * >, _STL::_Select1st<_STL::pair<const unsigned int, void * > >, _STL::less<unsigned int >, _STL::allocator<_STL::pair<const unsigned int, void * > > > FoldWayFind;
typedef _STL::map<unsigned char, short> FoldVisitedCtor;              // 0x000D3A71
typedef _STL::set<int> FoldVisited;                                   // 0x000BC15D 0x00388F63
typedef _STL::_Rb_tree<int, int, _STL::_Identity<int>, _STL::less<int>, _STL::allocator<int> > FoldVisitedTree;
typedef _STL::_Deque_base<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > FoldQueueCtor; // 0x00605464
typedef _STL::deque<void *> FoldQueue;                                // 0x00423BD8 0x002EE9A0
typedef _STL::_Deque_base<void *, _STL::allocator<void *> > FoldQueueDtor; // 0x0054FAAC

class Rva00072FE6
{
public:
	~Rva00072FE6();
};

namespace _STL {
template <> FoldZoneTreeCtor::multiset();
template <> FoldZoneTreeDtor::~_Rb_tree();
template <> FoldZoneInsert::iterator FoldZoneInsert::insert_equal(const FoldZoneInsert::value_type &);
template <> _STL::pair<FoldZoneRange::iterator, FoldZoneRange::iterator> FoldZoneRange::equal_range(const int &);
template <> FoldWayTreeCtor::set();
template <> FoldWayTreeDtor::~_Rb_tree();
template <> unsigned int &FoldWayIndex::operator[](const unsigned int &);
template <> FoldVisitedCtor::map();
template <> _STL::pair<FoldVisited::iterator, bool> FoldVisited::insert(const int &);
template <> FoldQueueCtor::_Deque_base(const _STL::allocator<BfmeWordValue4> &, size_t);
template <> void FoldQueue::push_back(void *const &);
template <> void FoldQueue::pop_front();
template <> FoldQueueDtor::~_Deque_base();
}

struct ZoneWaypointMap
{
	ZoneWaypointMap() { reinterpret_cast<FoldZoneTreeCtor *>(this)->FoldZoneTreeCtor::multiset(); }
	~ZoneWaypointMap() { reinterpret_cast<FoldZoneTreeDtor *>(this)->~FoldZoneTreeDtor(); }
	FoldZoneInsertMap &tree() { return *reinterpret_cast<FoldZoneInsertMap *>(this); }
	char m_storage[sizeof(FoldZoneInsertMap)];
};

struct WaypointZoneMap
{
	WaypointZoneMap() { reinterpret_cast<FoldWayTreeCtor *>(this)->FoldWayTreeCtor::set(); }
	~WaypointZoneMap() { reinterpret_cast<FoldWayTreeDtor *>(this)->~FoldWayTreeDtor(); }
	char m_storage[sizeof(FoldWayIndex)];
};

struct ZoneQueue
{
	ZoneQueue() { reinterpret_cast<FoldQueueCtor *>(this)->FoldQueueCtor::_Deque_base(_STL::allocator<BfmeWordValue4>(), 0); }
	~ZoneQueue() { reinterpret_cast<FoldQueueDtor *>(this)->~FoldQueueDtor(); }
	FoldQueue &q() { return *reinterpret_cast<FoldQueue *>(this); }
	char m_storage[sizeof(FoldQueue)];
};

struct VisitedZones
{
	VisitedZones() { reinterpret_cast<FoldVisitedCtor *>(this)->FoldVisitedCtor::map(); }
	~VisitedZones() { reinterpret_cast<Rva00072FE6 *>(this)->~Rva00072FE6(); }
	FoldVisited &s() { return *reinterpret_cast<FoldVisited *>(this); }
	char m_storage[sizeof(FoldVisited)];
};

class Pathfinder
{
public:
	Bool rva002F4115(Object *obj, Int startZone, Int goalZone, LocomotorSet *locoSet);
	void *rva001E3647Pos(int layer, const Coord3D *pos);
private:
	char m_pad000[0x460];
	Rva002E99F9Sub460 m_zoneManager; // +0x460
};

Bool Pathfinder::rva002F4115(Object *obj, Int startZone, Int goalZone, LocomotorSet *locoSet)
{
	if (reinterpret_cast<Rva0028B984ByteField *>(obj)->get())
		return false;
	AIUpdateInterface *ai = obj->getAI();
	if (ai == 0 && locoSet == 0)
		return false;
	Int surfaces;
	if (locoSet)
		surfaces = locoSet->m_validSurfaces;
	else
		surfaces = ai->m_locomotorSurfaces;
	Int crusherLevel = obj->getTemplate()->m_56C;
	Bool b634 = obj->getTemplate()->m_634;
	Bool flagA = obj->rva0028AC62();
	Bool flagB = obj->rva0028AFBB();
	ZoneQuery query;
	query.m_surfaces = surfaces;
	query.m_04 = !b634;
	query.m_05 = flagB;
	query.m_08 = crusherLevel - 1;
	query.m_0C = flagA;

	ZoneWaypointMap zoneWaypoints;
	WaypointZoneMap waypointZones;
	for (Waypoint *wp = TheTerrainLogic->getFirstWaypoint(); wp; wp = wp->m_next) {
		if (!(unsigned char)reinterpret_cast<Rva002E6ECA *>(wp)->get())
			continue;
		if (!wp->isValidUnitType(obj))
			continue;
		PathfindCellView *cell = (PathfindCellView *)rva001E3647Pos(
			TheTerrainLogic->getLayerForDestination(0, &wp->m_location), &wp->m_location);
		if (!cell)
			continue;
		Int zone = m_zoneManager.rva0053241F(&query, cell->m_zone);
		Rva002F1DA1Mapped mapped;
		mapped.a = (int)wp;
		zoneWaypoints.tree().insert(FoldZoneInsertMap::value_type(zone, mapped));
		(*reinterpret_cast<FoldWayIndex *>(&waypointZones))[(unsigned int)wp] = zone;
	}

	ZoneQueue queue;
	VisitedZones visited;
	queue.q().push_back((void *const &)startZone);
	visited.s().insert(startZone);
	while (!queue.q().empty()) {
		Int zone = (Int)queue.q().front();
		queue.q().pop_front();
		if (zone == goalZone)
			return true;
		_STL::pair<FoldZoneRangeMap::iterator, FoldZoneRangeMap::iterator> range =
			reinterpret_cast<FoldZoneRangeMap *>(&zoneWaypoints)->equal_range(zone);
		for (FoldZoneRangeMap::iterator it = range.first; it != range.second; ) {
			Waypoint *wp = (Waypoint *)(*it).second;
			++it;
			for (Int i = 0; i < wp->getNumLinks(); ++i) {
				zone = (Int)wp->getLink(i);
				FoldWayFindMap::iterator found = reinterpret_cast<FoldWayFindMap *>(&waypointZones)->find((const unsigned int &)zone);
				if (found != reinterpret_cast<FoldWayFindMap *>(&waypointZones)->end()) {
					zone = (Int)(*found).second;
					if (visited.s().find(zone) == visited.s().end()) {
						visited.s().insert(zone);
						queue.q().push_back((void *const &)zone);
					}
				}
			}
		}
	}
	return false;
}
