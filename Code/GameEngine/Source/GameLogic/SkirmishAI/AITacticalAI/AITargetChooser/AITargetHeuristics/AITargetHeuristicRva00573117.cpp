// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /arch:SSE
//
// The target heuristic whose class keeps its address-derived name
// Rva00573117 (ctor 0x005730FF, dtor 0x00573117, vftable 0x00C6E0B8: slot 0
// the deleting dtor 0x0057320F, slot 1 below); retail file unknown, it sits
// among the AITargetHeuristics (AITargetHeuristicBaseDefense.cpp follows).
//
// Slot 1 (0x0057327E): when the heuristic's 0x00573122 gate passes for the
// player, of the "Player_%d_Start" waypoints of the other players (1..20,
// stopping at the first missing one) the one nearest (2D) the player's base
// centre (the skirmish-AI record 0x002A8AB1, 0x004EBF4B) round which no
// alive object the relationship filter passes (flags 6) is either an ally of
// the player or lacks bit 0x10 of its +0x04 data's +0x120 within the AI
// data's +0x884 radius is handed to the choice (0x002C5CF7) with that radius.
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents): a vptr, the +0x04 link to the next
// filter (PartitionFilter::link 0x00625790), then each filter's members;
// address-derived names after allow (slot 1).
#include "ascii_string.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// The base filter's slot 2 is the trivial virtual retail shares across many
// vftable slots (0x0036CC7A); bind the declaration to that row.
#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum Relationship
{
	ENEMIES,
	NEUTRAL,
	ALLIES
};

struct Rva0057327EInfo
{
	char m_pad000[0x120];
	unsigned char m_120;	// +0x120
};

class Object
{
public:
	char m_pad00[0x04];
	Rva0057327EInfo *m_04;	// +0x04
	const Rva0057327EInfo *getInfo() const { return m_04; }
};

class Player
{
public:
	Relationship getRelationship(const Object *that) const;	// 0x002AD11E
	int getPlayerIndex() const { return m_54; }
	char m_pad00[0x54];
	int m_54;	// +0x54
};

// A waypoint: +0x08 its name, +0x0C its location, +0x1C the next one.
class Waypoint
{
public:
	const AsciiString &getName() const { return m_name; }
	const Coord3D *getLocation() const { return &m_location; }
	Waypoint *getNext() const { return m_pNext; }
private:
	int m_00;
	int m_04;
	AsciiString m_name;	// +0x08
	Coord3D m_location;	// +0x0C
	int m_18;
	Waypoint *m_pNext;	// +0x1C
};

class TerrainLogic
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32();
	virtual Waypoint *getFirstWaypoint();	// +0x84
	__forceinline Waypoint *findWaypoint(AsciiString name)
	{
		for (Waypoint *way = getFirstWaypoint(); way; way = way->getNext())
			if (way->getName() == name)
				return way;
		return 0;
	}
};
extern TerrainLogic *TheTerrainLogic;

// The skirmish-AI manager's record per player: 0x004EBF4B gives its base
// centre.
class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();	// 0x004EBF4B
};

struct Rva002A8AB1Record : public Rva004EBF4B
{
};

// The AI data the manager keeps at +0x10: +0x874 the scan radius.
struct Rva002A8F24Data
{
	char m_pad000[0x874];
	float m_874;	// +0x874
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
	const Rva002A8F24Data *getData() const { return &m_data; }
	char m_pad00[0x10];
	Rva002A8F24Data m_data;	// +0x10
};
extern Rva002A8F24 *g_00DFEEF8;

// What slot 1 hands the pick to (0x002C5D8B forwards to 0x002C5CF7).
class Rva002C5D8B
{
public:
	void rva002C5CF7(const Coord3D *pos, float radius, int id);	// 0x002C5CF7
};

struct Rva005CB22A
{
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();
};

struct Rva00573117 : Rva005CB22A
{
	Rva00573117();
	virtual ~Rva00573117();
	virtual void rva0057327E(Rva002C5D8B *choice, Player *player, int unused);
	bool rva00573122(Player *player);	// 0x00573122
};

void Rva00573117::rva0057327E(Rva002C5D8B *choice, Player *player, int unused)
{
	if (!rva00573122(player))
		return;
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(player);
	Coord3D base = record->rva004EBF4B();
	Coord3D best;
	best.x = 0.0f;
	best.y = 0.0f;
	best.z = 0.0f;
	float bestDist = -1.0f;
	for (int i = 0; i < 20; ++i) {
		if (i == player->getPlayerIndex())
			continue;
		AsciiString name;
		name.format("Player_%d_Start", i + 1);
		Waypoint *way = TheTerrainLogic->findWaypoint(name);
		if (!way)
			break;
		const Coord3D *pos = way->getLocation();
		float dx = pos->x - base.x;
		float dy = pos->y - base.y;
		float dist = dx * dx + dy * dy;
		if (bestDist < 0.0f || dist < bestDist) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(pos,
				g_00DFEEF8->getData()->m_874, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(player, true, 6)), 1);
			unsigned count = 0;
			for (Object *obj = hits.next(); obj; obj = hits.next())
				if (player->getRelationship(obj) == ALLIES || !(obj->getInfo()->m_120 & 0x10))
					++count;
			if (count == 0) {
				best = *pos;
				bestDist = dist;
			}
		}
	}
	if (bestDist > 0.0f)
		choice->rva002C5CF7(&best, g_00DFEEF8->getData()->m_874, 0);
}
