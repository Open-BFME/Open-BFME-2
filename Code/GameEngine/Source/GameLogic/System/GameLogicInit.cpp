// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?init@GameLogic@@UAEXXZ @0x00243EE7 957B (Ghidra FUN_00643ee7, ret at
// 0x002442A3; next body 0x002442A4).
// Target evidence: the setName literals name every subsystem it creates and
// the global each is stored in: ThePartitionManager (0x009FE748, ctor
// 0x006253F0), TheShroudManager (0x009FE74C, ctor 0x007398D0) and
// TheCollisionManager (0x009FE754, ctor 0x00758250), each new'd at 0x14 bytes,
// then TheTerrainLogic (0x009FEC50, own virtual 0x38, SubsystemInterface at
// +4), TheLargeGroupAudio (0x009FE1A8, new 0x40 with ctor 0x0020DD59) and
// TheBuffLogic (0x009FF190, own virtual 0x40, base at +4); TheGhostObjectManager
// (0x009FF188) comes from own virtual 0x3C. setName is the out-of-line
// SubsystemInterface member 0x0006F3CC taking an AsciiString by value.
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (GameLogic::init, same subsystem order, region zero, partition 7, sides
// list pair and the trailing field resets). BFME 2 differs from the donor
// with three owned members new'd at +0x170/+0x174/+0x178 between the region
// setup and the ghost manager, an out-of-line player-leave reset
// (0x0023D17D through TheGameLogic) and moved field offsets. Field names
// stay offset names: only the donor knows their meaning.
#include <list>
#include <map>
#include <math.h>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

struct Rva00239D49Element { Rva00239D49Element();Rva00239D49Element(const Rva00239D49Element&);~Rva00239D49Element();Rva00239D49Element&operator=(const Rva00239D49Element&);char bytes[1]; bool operator<(const Rva00239D49Element&)const; bool operator==(const Rva00239D49Element&)const; };
typedef _STL::list<Rva00239D49Element, _STL::allocator<Rva00239D49Element> > TocList;

namespace _STL
{
template<> void _List_base<Rva00239D49Element, allocator<Rva00239D49Element> >::clear();
}

struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

void setFPMode(void);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;
	virtual void s02(void); virtual void s03(void); virtual void s04(void);
	virtual void s05(void); virtual void s06(void); virtual void s07(void);
	virtual void s08(void);
	virtual void reset(void);                                            // +0x24
	void setName(AsciiString name);

private:
	int m_04;
	AsciiString m_name;
};

class PartitionManager : public SubsystemInterface
{
public:
	void setRegion(const Region3D *extent, float cellSize);
	void rva00625310(int value);

private:
	int m_impl[2];
};

class Rva006253F0 : public PartitionManager
{
public:
	Rva006253F0(void);
	virtual void init(void);
};

class Open2Store8F75D0 : public PartitionManager
{
public:
	Open2Store8F75D0(void);
	virtual void init(void);
};

class Rva00739720
{
public:
	void rva00739720(int value);
};

class CollisionManager : public SubsystemInterface
{
public:
	CollisionManager(void);
	virtual void init(void);

private:
	int m_impl[2];
};

class Rva00758210
{
public:
	void rva00758210(void);
};

class Rva006C0810
{
public:
	void rva006C0810(const Region3D *extent, float cellSize);
};

class TerrainLogic : public Snapshot, public SubsystemInterface
{
};

class BuffLogic : public Snapshot, public SubsystemInterface
{
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager(void);
	virtual void g01(void); virtual void g02(void); virtual void g03(void);
	virtual void reset(void);                                            // +0x10
};

class AI : public SubsystemInterface
{
};

class ScriptEngine : public SubsystemInterface
{
};

class Overridable
{
public:
	Overridable *deleteOverrides(void);
};

struct Rva00200BD9Holder;

class StatsCollector;

class Rva0048BA39StatsCollector
{
public:
	~Rva0048BA39StatsCollector(void);
};

class Rva000427195
{
public:
	void rva003A2A41(void);
};

class Rva00240CAB
{
public:
	void rva0024191A(void);
};

class Rva001DBCDCTarget
{
public:
	void rva001DBCDC(void);
};

class Rva0053F1ECSub
{
public:
	void note(int buckets);
};

class Rva0023E7D9
{
public:
	void rva0023E7D9(void);
};

class Rva0035A1D8
{
public:
	void rva0035A1D8(void);
};

class DOTManager
{
public:
	void rva0043B725(void);
};

class Rva00439920
{
public:
	void rva00439920(void);
};

class LargeGroupAudio : public SubsystemInterface
{
public:
	LargeGroupAudio(void);
	virtual void init(void);

private:
	int m_body[13];
};

class Rva0035A2DC
{
public:
	void rva0035A2DC(Region3D *extent, float cellSize);
};

class Rva00359E13
{
public:
	Rva00359E13(void);
	void rva0035AA3E(void);

private:
	int m_body[17];
};

class Rva0043B660
{
public:
	Rva0043B660(void);
	void rva000B3FD0(void);

private:
	int m_body[4];
};

class Rva0043821C
{
public:
	void rva0043821C(void);
};

class Rva00243177
{
public:
	Rva00243177(void);

private:
	int m_body[6];
};

class SidesList
{
public:
	void rva0032D554(void);
	void rva0032F84F(void);
};

class GlobalData
{
public:
	char m_pad000[0xd4];
	float m_d4;
	float m_d8;
	char m_pad0DC[0xbd0 - 0xdc];
	int m_bd0;
};

class GameInfo;
class LoadScreen;

class GameLogic : public SubsystemInterface
{
public:
	virtual void init(void);
	virtual void v10(void); virtual void v11(void); virtual void v12(void); virtual void v13(void);
	virtual TerrainLogic *createTerrainLogic(void);                      // +0x38
	virtual GhostObjectManager *createGhostObjectManager(void);          // +0x3C
	virtual BuffLogic *createBuffLogic(void);                            // +0x40

	virtual void reset(void);

	void rva00240E18(bool loadingSaveGame);
	void rva0023D17D(void);
	void destroyAllObjectsImmediate(void);
	void rva00376D49(void);
	void rva00244CB0(bool loadingSaveGame, GameInfo *game);

private:
	LoadScreen *getLoadScreen(bool saveGame);

public:

	char m_pad00C[0x10 - 0x0c];
	char m_10[0x24 - 0x10];
	char m_24[0x40 - 0x24];
	int m_40;
	bool m_44;
	char m_pad045[0x48 - 0x45];
	int m_48;
	int m_4c;
	IntList m_50;
	char m_pad054[0x70 - 0x54];
	bool m_70;
	bool m_71;
	bool m_72;
	char m_pad073[0x94 - 0x73];
	int m_94;
	bool m_98;
	bool m_99;
	bool m_9a;
	bool m_9b;
	char m_pad09C[0x9f - 0x9c];
	bool m_9f;
	int m_a0;
	int m_a4;
	char m_pad0A8[0xb4 - 0xa8];
	char m_b4[0x10c - 0xb4];
	int m_10c;
	char m_pad110[0x11d - 0x110];
	bool m_11d;
	char m_pad11E[0x120 - 0x11e];
	LoadScreen *m_120;
	bool m_124;
	bool m_125;
	bool m_126;
	bool m_127;
	bool m_128[8];
	int m_130[8];
	bool m_150;
	char m_pad151[0x154 - 0x151];
	int m_154;
	int m_158;
	int m_15c;
	int m_160;
	char m_pad164[0x170 - 0x164];
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva00243177 *m_178;
	int m_17c;
	int m_180;
	char m_pad184[0x1b0 - 0x184];
	int m_1b0;
	int m_1b4;
	char m_pad1B8[0x1c0 - 0x1b8];
	TocList m_1c0;
	char m_pad1C4[0x2a4 - 0x1c4];
	int m_2a4;
};

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern void *g_Va00DFE750;
extern CollisionManager *TheCollisionManager;
extern GlobalData *TheWritableGlobalData;
extern GhostObjectManager *TheGhostObjectManager;
extern TerrainLogic *TheTerrainLogic;
extern LargeGroupAudio *TheLargeGroupAudio;
extern BuffLogic *TheBuffLogic;
extern SidesList *TheSidesList;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ScriptEngine *TheScriptEngine;
extern StatsCollector *g_00E032F8;
extern Rva00200BD9Holder *g_rva00200BD9Holder;

// 0x0004224C (rowed as a this-returning member) is the out-of-line
// constructor of a scope guard: when TheGameLogic exists it sets the FP mode
// on the first nesting level and counts TheGameLogic+0x1B4 up. The matching
// count-down (0x00042212) is expanded at scope exit.
class Rva0004224C
{
public:
	Rva0004224C(void);
	~Rva0004224C(void)
	{
		if (TheGameLogic)
			TheGameLogic->m_1b4--;
	}
};

void GameLogic::init(void)
{
	setFPMode();

	rva00240E18(false);

	ThePartitionManager = new Rva006253F0;
	ThePartitionManager->init();
	ThePartitionManager->setName("ThePartitionManager");

	TheShroudManager = new Open2Store8F75D0;
	TheShroudManager->init();
	TheShroudManager->setName("TheShroudManager");

	TheCollisionManager = new CollisionManager;
	TheCollisionManager->init();
	TheCollisionManager->setName("TheCollisionManager");
	((Rva00758210 *)TheCollisionManager)->rva00758210();

	Region3D extent;
	extent.lo.x = 0.0f;
	extent.lo.y = 0.0f;
	extent.lo.z = 0.0f;
	extent.hi.x = 0.0f;
	extent.hi.y = 0.0f;
	extent.hi.z = 0.0f;
	TheShroudManager->setRegion(&extent, TheWritableGlobalData->m_d4);
	((Rva00739720 *)TheShroudManager)->rva00739720(TheWritableGlobalData->m_bd0);
	ThePartitionManager->rva00625310(7);
	((Rva006C0810 *)g_Va00DFE750)->rva006C0810(&extent, TheWritableGlobalData->m_d4);

	m_170 = new Rva00359E13;
	m_170->rva0035AA3E();
	((Rva0035A2DC *)m_170)->rva0035A2DC(&extent, TheWritableGlobalData->m_d8);

	m_174 = new Rva0043B660;
	m_174->rva000B3FD0();

	m_178 = new Rva00243177;
	((Rva0043821C *)m_178)->rva0043821C();

	TheGhostObjectManager = createGhostObjectManager();

	TheTerrainLogic = createTerrainLogic();
	TheTerrainLogic->init();
	TheTerrainLogic->setName("TheTerrainLogic");

	TheLargeGroupAudio = new LargeGroupAudio;
	if (TheLargeGroupAudio) {
		TheLargeGroupAudio->init();
		TheLargeGroupAudio->setName("TheLargeGroupAudio");
	}

	TheBuffLogic = createBuffLogic();
	TheBuffLogic->init();
	TheBuffLogic->setName("TheBuffLogic");

	TheSidesList->rva0032D554();
	TheSidesList->rva0032F84F();

	m_11d = false;
	m_124 = false;
	m_125 = false;
	m_126 = true;
	m_127 = true;
	for (int i = 0; i < 8; ++i) {
		m_128[i] = false;
		m_130[i] = 0;
	}
	m_150 = false;

	m_98 = true;
	m_99 = true;
	m_9a = true;
	m_9b = true;
	m_a0 = -1;
	m_a4 = 1;

	m_70 = false;
	m_94 = 0;
	m_48 = 0;
	m_50.clear();

	TheGameLogic->rva0023D17D();
	m_1b0 = -1;
	m_2a4 = 2;
}

// ?reset@GameLogic@@UAEXXZ @0x002442A4 538B (ret at 0x002444BD; next body
// 0x002444BE). Donor: BFME 1 GameLogicReset.cpp (GameLogic::reset), same
// order: map clears, flag resets, setFPMode, destroyAllObjectsImmediate, the
// subsystem resets, progress arrays, StatsCollector delete, TOC list clear,
// the defaults call 0x00240E18 (shared with init) and the trailing field
// resets. BFME 2 resets every SubsystemInterface through slot 0x24 and the
// ghost manager through slot 0x10, resets the three owned members at
// +0x170/+0x174/+0x178 when present, wraps the body in the FP-mode guard
// 0x0004224C, and deletes StatsCollector through its out-of-line destructor
// (ICF-folded with the AsciiString release at 0x0048BA39).
void GameLogic::reset(void)
{
	Rva0004224C fpModeGuard;

	((Rva000427195 *)m_10)->rva003A2A41();
	((Rva00240CAB *)m_24)->rva0024191A();
	((Rva001DBCDCTarget *)m_b4)->rva001DBCDC();
	((Rva0053F1ECSub *)m_b4)->note(0x2000);

	m_11d = false;
	m_124 = false;
	m_125 = false;
	m_126 = true;
	m_127 = true;
	m_9f = true;

	setFPMode();
	m_154 = 0;
	m_158 = 0;
	m_15c = 0;
	m_160 = 0;
	destroyAllObjectsImmediate();
	m_10c = 1;
	m_180 = 0;

	TheGhostObjectManager->reset();
	ThePartitionManager->reset();
	TheShroudManager->reset();
	TheCollisionManager->reset();
	((SubsystemInterface *)g_Va00DFE750)->reset();
	TheTerrainLogic->reset();
	TheAI->reset();
	TheScriptEngine->reset();
	if (m_170)
		((Rva0035A1D8 *)m_170)->rva0035A1D8();
	if (m_174)
		((DOTManager *)m_174)->rva0043B725();
	if (m_178)
		((Rva00439920 *)m_178)->rva00439920();
	TheLargeGroupAudio->reset();
	TheBuffLogic->reset();

	for (int i = 0; i < 8; ++i) {
		m_128[i] = false;
		m_130[i] = 0;
	}
	m_150 = false;

	if (g_00E032F8) {
		delete (Rva0048BA39StatsCollector *)g_00E032F8;
		g_00E032F8 = 0;
	}

	m_1c0.clear();

	rva00240E18(false);

	m_a0 = -1;
	m_98 = true;
	m_99 = true;
	m_9a = true;
	m_9b = true;
	m_a4 = 1;

	g_rva00200BD9Holder = (Rva00200BD9Holder *)((Overridable *)g_rva00200BD9Holder)->deleteOverrides();

	m_94 = 0;
	m_17c = 0;
	((Rva0023E7D9 *)this)->rva0023E7D9();
	m_71 = false;
	rva00376D49();
	m_44 = false;
	m_40 = 0;
	m_2a4 = 2;
}

// populateRandomStartPosition @0x0024485C 1108B (Ghidra FUN_0064485c, ret at
// 0x00244CAF; next body 0x00244CB0). Target evidence: the GameLogic.cpp
// __FILE__ literal with lines 2166/2203, "Player_%d_Start" formatted twice per
// pair and looked up in the MapMetaData+0x38 waypoint map (find worker
// 0x001F8437), MapCache::findMap(getMap()) with the player count at +0x20,
// sqrt (0x0062921C), GameInfo::getSlot/getConstSlot/isOccupied/
// isStartPositionTaken and TheGameInfo (0x00A02EEC). Donor: Zero Hour
// GameLogic.cpp populateRandomStartPosition (distance table, taken flags,
// first-pick random loop, observer pass). BFME 2 differs: the distance table is
// built only with a map, a start spot already in range now counts as picked
// (ZH's `>= 0 ||` test), a per-spot slot index replaces ZH's per-team position
// table, and a later spot scores by the closest same-team neighbour (team from
// TheGameInfo's slots, GameSlot+0x1C) while no teammate was met, else by the
// summed distance. Slot fields: +0x10 start position, +0x18 template (-2 is
// the observer), as in the ZH accessors.
#define GAMELOGIC_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\GameLogic.cpp"

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

template <class T> class Rva0024485CAllocator : public _STL::allocator<T>
{
};

class WaypointMap : public _STL::map<AsciiString, Coord3D, _STL::less<AsciiString>, Rva0024485CAllocator<_STL::pair<const AsciiString, Coord3D> > >
{
public:
	int m_numStartSpots;
};

class MapMetaData
{
public:
	char m_pad00[0x20];
	int m_numPlayers;
	char m_pad24[0x38 - 0x24];
	WaypointMap m_waypoints;
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

class GameSlot
{
public:
	bool isOccupied() const;
	void saveOffOriginalInfo();
	int getStartPos() const { return m_10; }
	void setStartPos(int startPos) { m_10 = startPos; }
	int getPlayerTemplate() const { return m_18; }
	int getTeamNumber() const { return m_1c; }

	char m_pad00[0x10];
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
	const GameSlot *getConstSlot(int index) const;
	AsciiString getMap() const;
	bool isStartPositionTaken(int positionIdx, int slotToIgnore = -1) const;
};

extern MapCache *TheMapCache;
extern GameInfo *TheGameInfo;

static inline float sqr(float x)
{
	return x * x;
}

void populateRandomStartPosition(GameInfo *game)
{
	if (!game)
		return;

	int i;
	int numPlayers = 8;
	const MapMetaData *md = TheMapCache->findMap(game->getMap());
	if (md)
		numPlayers = md->m_numPlayers;

	float startSpotDistance[8][8];
	for (i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (md && i != j && i < numPlayers && j < numPlayers) {
				AsciiString w1, w2;
				w1.format("Player_%d_Start", i + 1);
				w2.format("Player_%d_Start", j + 1);
				WaypointMap::const_iterator c1 = md->m_waypoints.find(w1);
				WaypointMap::const_iterator c2 = md->m_waypoints.find(w2);
				if (c1 == md->m_waypoints.end() || c2 == md->m_waypoints.end()) {
					startSpotDistance[i][j] = 1000000.0f;
				} else {
					float x1 = c1->second.x;
					float y1 = c1->second.y;
					float x2 = c2->second.x;
					float y2 = c2->second.y;
					startSpotDistance[i][j] = sqrt(sqr(x1 - x2) + sqr(y1 - y2));
				}
			} else {
				startSpotDistance[i][j] = 0.0f;
			}
		}
	}

	bool hasStartSpotBeenPicked = false;
	bool taken[8];
	int slotForPos[8];
	for (i = 0; i < 8; ++i) {
		slotForPos[i] = -1;
		taken[i] = (i < numPlayers) ? false : true;
	}

	for (i = 0; i < 8; ++i) {
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied() || slot->getPlayerTemplate() == -2)
			continue;
		int posIdx = slot->getStartPos();
		if (posIdx >= 0 && posIdx < numPlayers) {
			hasStartSpotBeenPicked = true;
			taken[posIdx] = true;
			slotForPos[posIdx] = i;
		}
	}

	for (i = 0; i < 8; ++i) {
		bool teammateFound = false;
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied() || slot->getPlayerTemplate() == -2)
			continue;
		int posIdx = slot->getStartPos();
		if (posIdx >= 0 && posIdx < numPlayers)
			continue;

		if (hasStartSpotBeenPicked) {
			float farthestDistance = 0.0f;
			int farthestIndex = -1;
			for (posIdx = 0; posIdx < numPlayers; ++posIdx) {
				if (taken[posIdx])
					continue;
				if (farthestIndex < 0) {
					farthestIndex = posIdx;
					for (int n = 0; n < numPlayers; ++n) {
						if (taken[n] && n != posIdx)
							farthestDistance += startSpotDistance[posIdx][n];
					}
				} else {
					float dist = 0.0f;
					for (int n = 0; n < numPlayers; ++n) {
						if (!taken[n] || n == posIdx)
							continue;
						if (TheGameInfo->getSlot(i)->getTeamNumber() > -1 &&
							TheGameInfo->getSlot(slotForPos[n])->getTeamNumber() == TheGameInfo->getSlot(i)->getTeamNumber()) {
							teammateFound = true;
							if (farthestDistance > startSpotDistance[posIdx][n]) {
								farthestDistance = startSpotDistance[posIdx][n];
								farthestIndex = posIdx;
							}
						} else if (!teammateFound) {
							dist += startSpotDistance[posIdx][n];
							if (dist > farthestDistance) {
								farthestDistance = dist;
								farthestIndex = posIdx;
							}
						}
					}
				}
			}
			slot->setStartPos(farthestIndex);
			taken[farthestIndex] = true;
			slotForPos[farthestIndex] = i;
		} else {
			while (posIdx == -1) {
				posIdx = GetGameLogicRandomValue(0, numPlayers - 1, GAMELOGIC_SOURCE_FILE, 2166);
				if (game->isStartPositionTaken(posIdx))
					posIdx = -1;
			}
			slot->setStartPos(posIdx);
			taken[posIdx] = true;
			slotForPos[posIdx] = i;
			hasStartSpotBeenPicked = true;
		}
	}

	int numPlayersInGame = 0;
	for (i = 0; i < 8; ++i) {
		const GameSlot *slot = game->getConstSlot(i);
		if (slot->isOccupied() && slot->getPlayerTemplate() != -2)
			++numPlayersInGame;
	}
	for (i = 0; i < 8; ++i) {
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied())
			continue;
		if (slot->getPlayerTemplate() != -2)
			continue;
		int posIdx = -1;
		if (numPlayersInGame == 0)
			posIdx = 0;
		while (posIdx == -1) {
			posIdx = GetGameLogicRandomValue(0, numPlayers - 1, GAMELOGIC_SOURCE_FILE, 2203);
			if (!game->isStartPositionTaken(posIdx))
				posIdx = -1;
		}
		slot->setStartPos(posIdx);
	}
}

// ?rva00244CB0@GameLogic@@QAEX_NPAVGameInfo@@@Z @0x00244CB0 166B (ret 8 at
// 0x00244D53; Ghidra's 20-byte FUN_00644cb0 stops at the first call). Called
// once, from 0x002485EE in the BFME 2 new-game setup (0x00248558). Target
// evidence: it is the ZH startNewGame stretch that saves off each slot's
// original info (0x003FF0D4) unless loading a save, populates the random start
// positions (0x0024485C) and then sides and colors (0x002444BE; ZH calls them in
// the other order), and stores getLoadScreen(saveGame) (0x0023DD48, the switch
// on m_gameMode at +0x110 that news each mode's load screen) in m_loadScreen
// (+0x120), calling its slot-2 init(game). BFME 2 brackets it with the
// 0x00A099F8 singleton's slot 10 and the queued device-interface release
// (0x00133283), runs the GameLogic helpers 0x0023C7D2 and 0x0023C7BB(0), pokes
// TheTransitionHandler slot 9 unless the +0x72 flag is set, and ends with
// setFPMode. The helper and flag meanings are not established.
class LoadScreen
{
public:
	virtual ~LoadScreen(void);
	virtual void v01(void);
	virtual void init(GameInfo *game);                                   // +0x08
};

class Rva009EB960
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void slot28();
};

class GameWindowTransitionsHandler
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual void slot24();
};

class Rva0023C7D2
{
public:
	void rva0023C7D2(void);
	void rva0023C7BB(int value);
};

extern Rva009EB960 *Rva0134FAA0;
extern GameWindowTransitionsHandler *TheTransitionHandler;

void bfmeReleaseQueuedDeviceInterfaces(void);
void populateRandomSideAndColor(GameInfo *game);

void GameLogic::rva00244CB0(bool loadingSaveGame, GameInfo *game)
{
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7D2();
	if (!m_72)
		TheTransitionHandler->slot24();

	if (game && !loadingSaveGame) {
		for (int i = 0; i < 8; ++i) {
			GameSlot *slot = game->getSlot(i);
			if (slot)
				slot->saveOffOriginalInfo();
		}
	}

	populateRandomStartPosition(game);
	populateRandomSideAndColor(game);

	m_120 = getLoadScreen(loadingSaveGame);
	if (m_120)
		m_120->init(game);

	((Rva0023C7D2 *)this)->rva0023C7BB(0);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	setFPMode();
}
