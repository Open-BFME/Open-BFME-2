// cl: /MD /GX /Ireference/shims/bfme2_ascii
//
// AISpellBookShroudReveal.cpp (the unit retail's random-range asserts name,
// 0x00C75EF0).
//
//   0x005D7FA6  AoE target picker slot: once the game frame passes
//               g_00E06648, pick one of the picker's waypoint IDs at random
//               and, when that waypoint is still shrouded for the caster
//               and an alive object allied (flags 4) to the caster stands
//               within 300 of it, offer the waypoint pushed 30..180 along
//               a random direction (0x005EE317) to 0x005EE8DD
//
// The filters are BFME2's partition filter chain (the view
// AIStructureCreepTactic.cpp documents).

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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	// Retail inlines Coord3D::scale here; its one out-of-line body (0x000036D1,
	// region.cpp) has another unit's codegen, so this TU's inline copy carries
	// its own name and never offers the link a second scale.
	void scaleInlined(float s) { x *= s; y *= s; z *= s; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
};

class Player
{
public:
	int getPlayerIndex() const { return m_54; }
	char m_pad00[0x54];
	int m_54;		// +0x54
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
};

class Waypoint
{
public:
	const Coord3D *getLocation() const { return &m_location; }
	unsigned int m_unknown00, m_id04;
	StringBase<char> m_name08;
	Coord3D m_location;	// +0x0C
	unsigned int m_unknown18;
	Waypoint *m_next1c;
};

class TerrainLogic
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual Waypoint *firstWaypoint(); virtual void s34();
	virtual Waypoint *getWaypointByID(int waypointID);
};
extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	unsigned int getFrame() const { return m_40; }
	char m_pad00[0x40];
	unsigned int m_40;	// +0x40
};
extern GameLogic *TheGameLogic;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
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
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;	// 0x007397F0
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// g_00E06648: the frame this unit's picker waits for; only 0x005D7FA6 reads
// it (zero-filled .bss).
unsigned int g_00E06648;

// The waypoint IDs at picker +0x28: a count, then the IDs.
struct Rva005D7FA6Waypoints
{
	int m_count;
	int m_ids[1];
};

// The AoE special-power target picker (AISPecialPowerTargetAoE.cpp holds
// 0x005EE317 and 0x005EE8DD).
class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *source);	// 0x005EE8DD
	void rva005EE317(Coord3D *dir);				// 0x005EE317
	bool rva005D7FA6(Object *source);
private:
	char m_pad00[0x28];
	Rva005D7FA6Waypoints m_waypoints;	// +0x28
};

bool Rva005EE816::rva005D7FA6(Object *source)
{
	if (TheGameLogic->getFrame() > g_00E06648) {
		int index = GetGameLogicRandomValue(0, m_waypoints.m_count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookShroudReveal.cpp", 57);
		Waypoint *wp = TheTerrainLogic->getWaypointByID(m_waypoints.m_ids[index]);
		if (TheShroudManager->getShroudStatusForPlayer(source->getControllingPlayer()->getPlayerIndex(), wp->getLocation()) != CELLSHROUD_CLEAR) {
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(wp->getLocation(), 300.0f, 0,
				Rva0026119DFilter().link(&Rva00261409Filter(source->getControllingPlayer(), true, 4)), 0);
			if (hits.next()) {
				Coord3D target;
				target.set(wp->getLocation());
				Coord3D dir;
				rva005EE317(&dir);
				dir.scaleInlined(GetGameLogicRandomValueReal(30.0f, 180.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookShroudReveal.cpp", 73));
				target.add(&dir);
				return rva005EE8DD(&target, source);
			}
		}
	}
	return false;
}

// Native RVA 0x005D7E45..0x005D7E98, 83B; the preceding destructor ends
// exactly at this entry. The clean inline lookup in the verified initializer
// Rva005D7E98WaypointStarts.cpp is the C++ guide. Retail independently proves
// the first-waypoint slot 33, name +8, next +0x1C and by-value key cleanup.
// The original standalone function name remains unproved.
Waypoint *Rva005D7E45FindWaypoint(AsciiString key)
{
	Waypoint *p = TheTerrainLogic->firstWaypoint();
	for (; p; p = p->m_next1c)
		if (p->m_name08.compare(*(const StringBase<char> *)&key) == 0) break;
	return p;
}
