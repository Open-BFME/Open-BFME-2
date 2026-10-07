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
#include <set>
#include <vector>
#include <math.h>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Libraries/Source/profile/profile.h"

typedef _STL::list<int, _STL::allocator<int> > IntList;

// ZH GameLogic.h ObjectTOCEntry: a thing template name and the 16-bit id
// save games store in its place. Retail list node: name at +8, id at +0xC
// (read by xferObjectTOC below). The allocator is a placeholder class: the
// list's out-of-line members fold onto addresses other lists already name.
struct ObjectTOCEntry
{
	AsciiString name;
	unsigned short id;
};
template <class T> class Rva00245F79Allocator : public _STL::allocator<T>
{
};
typedef _STL::list<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> > ObjectTOCList;

namespace _STL
{
template<> void _List_base<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> >::clear();
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

class Object;
class ThingTemplate;
class Matrix3D;

class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
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
	void rva0023F88C(bool loadingSaveGame);
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
	char m_pad000[0xc];
	AsciiString m_mapName;
	char m_pad010[0xd4 - 0x10];
	float m_d4;
	float m_d8;
	char m_pad0DC[0xbd0 - 0xdc];
	int m_bd0;
	char m_padBD4[0x1110 - 0xbd4];
	bool m_1110;
	char m_pad1111[0x123d - 0x1111];
	bool m_123d;
};

class GameInfo;
class LoadScreen;
class Object;
class MapObject;

// One record per object the map loader created: the object and the map
// object it came from (8 bytes; push_back 0x00539A2E).
struct Rva0024622FEntry
{
	Object *obj;
	MapObject *mapObj;
};

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum ObjectID
{
	INVALID_ID = 0
};

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
	void rva00246422(bool dontCreate);
	void rva00248558(bool loadingSaveGame);
	void rva00241230(bool loadingSaveGame);
	void rva002469A5(bool loadingSaveGame, int *progress);
	void rva002421F5(bool loadingSaveGame, int *progress);
	void rva00248278(bool loadingSaveGame);
	void rva0023F52C(bool loadingSaveGame);
	void rva0024004D(bool loadingSaveGame);
	bool rva0023C8DA(unsigned char loadingSaveGame);
	Object *findObjectByID(ObjectID id);
	void rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
		const KindOfType *requireKind, bool dontCreate);
	void rva00244CB0(bool loadingSaveGame, GameInfo *game);

	Object *getFirstObject(void) const { return m_objList; }
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferObjectTOC(Xfer *xfer);

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
	char m_pad054[0x6d - 0x54];
	bool m_6d;
	char m_pad06E[0x70 - 0x6e];
	bool m_70;
	bool m_71;
	bool m_72;
	char m_pad073[0x94 - 0x73];
	int m_94;
	bool m_98;
	bool m_99;
	bool m_9a;
	bool m_9b;
	bool m_9c;
	bool m_9d;
	char m_pad09E[0x9f - 0x9e];
	bool m_9f;
	int m_a0;
	int m_a4;
	char m_pad0A8[0xac - 0xa8];
	Object *m_objList;
	char m_pad0B0[0xb4 - 0xb0];
	char m_b4[0x10c - 0xb4];
	int m_10c;
	int m_110;
	char m_pad114[0x11d - 0x114];
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
	Object *m_154;
	Object *m_158;
	Object *m_15c;
	Object *m_160;
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
	ObjectTOCList m_objectTOC;
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
// count-down (0x00042212) is expanded at scope exit. Both are defined in the
// class: 0x00248558 keeps the guard in its parameter slot, which MSVC 7.1
// does only for an empty class whose constructor and destructor it can see.
class Rva000421FD
{
public:
	void rva000421FD(void);
};

class Rva0004224C
{
public:
	Rva0004224C(void)
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
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

	m_objectTOC.clear();

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

// ?addTOCEntry@GameLogic@@QAEXVAsciiString@@G@Z @0x00245F14 101B and
// ?xferObjectTOC@GameLogic@@QAEXPAVXfer@@@Z @0x00245F79 330B.
// Target evidence: xferObjectTOC clears the list at this+0x1C0 (0x00239D49),
// walks the object list at this+0xAC (next at +0x8C, template at +4, template
// name at +0x64) and adds a template name through addTOCEntry (0x00245F14)
// only when the name search at 0x00240167 misses (passing the template's own
// name, not the local copy); the store path then
// xfers the count (Xfer slot 30) and each node's name (slot 27) and id
// (slot 32), the load path reads them back into addTOCEntry. Caller 0x00247BC6.
// addTOCEntry copies its by-value name and id into a local entry and appends it
// through the list push_back at 0x00242EE7.
// Donor: ZH GameLogic.cpp xferObjectTOC/addTOCEntry, same control flow;
// BFME 2 opens with the out-of-line Xfer::Version1 (0x000053EE) instead of
// xferVersion and keeps the store path's name local inside its branch.
class Xfer;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class ThingTemplate
{
public:
	const AsciiString &getName(void) const { return m_name; }
	__forceinline bool isKindOf(KindOfType t) const
	{
		unsigned int mask = 1u << (t & 31);
		return (m_kindof[t >> 5] & mask) != 0;
	}

private:
	char m_pad00[0x64];
	AsciiString m_name;
	char m_pad68[0x10c - 0x68];
	unsigned int m_kindof[4];
};

class Dict;

class Drawable;

class Thing
{
public:
	Drawable *getDrawable(void) const;
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }
	Object *getNextObject(void) const { return m_next; }
	void rva00293E64(Dict *properties);

private:
	void *m_vtbl;
	const ThingTemplate *m_template;
	char m_pad08[0x8c - 0x08];
	Object *m_next;
};

void GameLogic::addTOCEntry(AsciiString name, unsigned short id)
{
	ObjectTOCEntry tocEntry;
	tocEntry.name = name;
	tocEntry.id = id;
	m_objectTOC.push_back(tocEntry);
}

void GameLogic::xferObjectTOC(Xfer *xfer)
{
	xfer->Version1();
	m_objectTOC.clear();

	unsigned int tocCount = 0;
	if (xfer->IsStoring()) {
		AsciiString templateName;
		for (Object *obj = getFirstObject(); obj; obj = obj->getNextObject()) {
			templateName = obj->getTemplate()->getName();
			if (findTOCEntryByName(templateName) == 0)
				addTOCEntry(obj->getTemplate()->getName(), ++tocCount);
		}
		*xfer == tocCount;
		for (ObjectTOCList::iterator it = m_objectTOC.begin(); it != m_objectTOC.end(); ++it) {
			ObjectTOCEntry *tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	} else {
		AsciiString templateName;
		unsigned short id;
		*xfer == tocCount;
		for (unsigned int i = 0; i < tocCount; ++i) {
			*xfer == templateName;
			*xfer == id;
			addTOCEntry(templateName, id);
		}
	}
}

// ?rva00246422@GameLogic@@QAEX_N@Z
// @0x00246422 1411B (ret 4 at 0x002469A2; caller 0x0024860E).
// Target evidence: with the flag set the body walks the map object list
// (0x00A00940) and hands every map object whose template carries kind bit 62
// or 63 to one of two TheTerrainLogic members (0x00283642 / 0x00280176) with
// a copy of its location, an identity Matrix3D and 1.0f; it then runs the map
// object loader 0x00244D56 with kind 0x3C excluded and the flag passed as
// true. With the flag clear it runs the same loader with the flag false, then
// makes sure four named objects exist: for each preset ID (99999999,
// 99999998, 99999996, 99999997) findObjectByID (0x00049DC5) fills
// this+0x154/+0x158/+0x15C/+0x160; on a miss the template "TheOneTree",
// "TheNonInteractableTree", "TheGrabbableTree" or "TheHarvestableTree" is
// looked up (0x002D06CA), announced to a fresh asset list unless the
// TheGlobalData+0x1110 flag is set (notify 0x0033CF34, merge 0x0061F010),
// created on the neutral player's default team through newObject (0x002D0A23)
// with a zeroed 16-byte mask temporary and the preset ID, and its drawable is
// given the same ID (0x00271058). The third lookup is the only one not
// preceded by the 0x00A099F8 slot-10 / 0x00133283 pair. Finally every object
// the loader recorded gets 0x00293E64 with its map object's properties.
// Shape: the kind argument is a compiler temporary (retail keeps it in the
// dead parameter slot), so it is passed through a const reference.
class Rva0020AA00Target
{
public:
	void notify(int a, int b);
};

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;

class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

// The second notify argument: the callee picks one of two 0x14-byte asset
// records at +0x3C4 by its first byte.
struct AssetLoadMode
{
	bool m_alternate;
	AssetLoadMode() : m_alternate(false) {}
};

void bfmeMergeReceiverKeys(int value);

class Dict
{
};

class MapObject
{
public:
	MapObject *getNext(void) const { return m_next; }
	const Coord3D *getLocation(void);
	Dict *getProperties(void) { return &m_properties; }
	const ThingTemplate *getThingTemplate(void) const;

private:
	void *m_vtbl;
	MapObject *m_next;
	Coord3D m_location;
	AsciiString m_objectName;
	const ThingTemplate *m_thingTemplate;
	float m_angle;
	int m_flags;
	Dict m_properties;
};

class MapObjectListHolder
{
public:
	MapObject *m_first;
};

extern MapObjectListHolder *BfmeTheMapObjectListHolder;

// newObjects third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
	unsigned int m_bits[4];
};

class Team;

class Player
{
public:
	Team *getDefaultTeam(void) const { return m_defaultTeam; }

private:
	char m_pad00[0x2ec];
	Team *m_defaultTeam;
};

class PlayerList
{
public:
	Player *getNeutralPlayer(void) const { return m_neutralPlayer; }

private:
	char m_pad00[0x18];
	Player *m_neutralPlayer;
};

class ThingFactory
{
public:
	Object *rva002D0A23(const ThingTemplate *tt, Team *team, const CreateMask &mask, ObjectID id);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;
extern PlayerList *ThePlayerList;

class Matrix3D
{
public:
	explicit Matrix3D(bool init)
	{
		if (init) {
			m_row[0][0] = 1.0f; m_row[0][1] = 0.0f; m_row[0][2] = 0.0f; m_row[0][3] = 0.0f;
			m_row[1][0] = 0.0f; m_row[1][1] = 1.0f; m_row[1][2] = 0.0f; m_row[1][3] = 0.0f;
			m_row[2][0] = 0.0f; m_row[2][1] = 0.0f; m_row[2][2] = 1.0f; m_row[2][3] = 0.0f;
		}
	}

private:
	float m_row[3][4];
};

// 0x00271058 compares, unregisters and re-registers the ID at +0x100 (the
// ZH Drawable::setID shape); the row keeps its address name.
class Rva00271058
{
public:
	void rva00271058(void *p);
};

// Binds the kind to a temporary for the loader's pointer argument.
static __forceinline const KindOfType *kindRef(const KindOfType &kind) { return &kind; }

void GameLogic::rva00246422(bool dontCreate)
{
	_STL::vector<Rva0024622FEntry> created;
	if (dontCreate) {
		for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_first; pMapObj; pMapObj = pMapObj->getNext()) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			const ThingTemplate *tt = pMapObj->getThingTemplate();
			if (tt == 0)
				continue;
			if (!tt->isKindOf((KindOfType)62) && !tt->isKindOf((KindOfType)63))
				continue;
			const Coord3D *loc = pMapObj->getLocation();
			Coord3D pos;
			pos.x = loc->x;
			pos.y = loc->y;
			pos.z = loc->z;
			Matrix3D mtx(true);
			if (tt->isKindOf((KindOfType)62))
				TheTerrainLogic->rva00283642(tt, &pos, &mtx, 1.0f);
			else if (tt->isKindOf((KindOfType)63))
				TheTerrainLogic->rva00280176(tt, &pos, &mtx, 1.0f);
		}
		rva00244D56(&created, kindRef((KindOfType)0x3c), 0, true);
	} else {
		rva00244D56(&created, kindRef((KindOfType)0x3c), 0, false);

		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		m_154 = findObjectByID((ObjectID)99999999);
		if (m_154 == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheOneTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((Rva0020AA00Target *)tt)->notify((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_154 = TheThingFactory->rva002D0A23(tt, team, CreateMask(), (ObjectID)99999999);
				if (m_154)
					((Rva00271058 *)m_154->getDrawable())->rva00271058((void *)99999999);
			}
		}

		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		m_158 = findObjectByID((ObjectID)99999998);
		if (m_158 == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheNonInteractableTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((Rva0020AA00Target *)tt)->notify((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_158 = TheThingFactory->rva002D0A23(tt, team, CreateMask(), (ObjectID)99999998);
				if (m_158)
					((Rva00271058 *)m_158->getDrawable())->rva00271058((void *)99999998);
			}
		}

		m_15c = findObjectByID((ObjectID)99999996);
		if (m_15c == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheGrabbableTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((Rva0020AA00Target *)tt)->notify((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_15c = TheThingFactory->rva002D0A23(tt, team, CreateMask(), (ObjectID)99999996);
				if (m_15c)
					((Rva00271058 *)m_15c->getDrawable())->rva00271058((void *)99999996);
			}
		}

		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		m_160 = findObjectByID((ObjectID)99999997);
		if (m_160 == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheHarvestableTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((Rva0020AA00Target *)tt)->notify((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_160 = TheThingFactory->rva002D0A23(tt, team, CreateMask(), (ObjectID)99999997);
				if (m_160)
					((Rva00271058 *)m_160->getDrawable())->rva00271058((void *)99999997);
			}
		}

		for (Rva0024622FEntry *it = created.begin(); it != created.end(); ++it) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			it->obj->rva00293E64(it->mapObj->getProperties());
		}
	}
}

// ?rva00248558@GameLogic@@QAEX_N@Z
// @0x00248558 546B (ret 4 at 0x00248777; callers 0x002B4884 0x003779C4
// 0x0041B5E3, the last passing true).
// The new-game pass: with the main window's close item greyed and the
// 0x009FE6E4 counter referenced, it runs the GameLogic load stages in order
// (0x00241230, the load screen 0x00244CB0, under the FP-mode guard
// 0x002469A5, the map-object pass 0x00246422, 0x002421F5, 0x00248278), stops
// the "newgame" profile range, resets the frame and hero state and, when
// GlobalData+0x123D asks for it, builds "assetload <map>[ (lod)].csv" into
// the 0x00E09B08 buffer. Target facts: the FuncInfo at 0x00D18120 has four
// unwind states; states 0 and 3 destroy objects at [ebp+8], the bool
// parameter's slot, which MSVC 7.1 gives an empty class only when its
// constructor and destructor are both inline in the class; so the close
// guard and the FP-mode guard are written that way and stay out of line
// (0x0023C83B/0x0023C85E, 0x0004224C/0x00042262). The progress int at
// [ebp-0x10] is passed by address to 0x002469A5 and 0x002421F5. Stage
// names are unknown; members keep their addresses.
extern void *ApplicationHWnd;

extern "C" __declspec(dllimport) void *__stdcall GetSystemMenu(void *wnd, int revert);
extern "C" __declspec(dllimport) int __stdcall EnableMenuItem(void *menu, unsigned id, unsigned flags);

// Retail calls strrchr through its import slot while this TU's /D_CRTIMP=
// leaves the header declaration a direct call: a typed view of the slot.
extern "C" char *(__cdecl * const _imp__strrchr)(const char *text, int ch);

class Rva0023C83B
{
public:
	Rva0023C83B(void)
	{
		EnableMenuItem(GetSystemMenu(ApplicationHWnd, 0), 0xF060, 1);
	}
	~Rva0023C83B(void) throw()
	{
		EnableMenuItem(GetSystemMenu(ApplicationHWnd, 0), 0xF060, 0);
	}
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
	virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
	virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v4a(); virtual void v4b();
	virtual void v4c(); virtual void v4d(); virtual void v4e(); virtual void v4f();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
	virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
	virtual void v58(); virtual void v59(); virtual void v5a(); virtual void v5b();
	virtual void v5c(); virtual void v5d(); virtual void v5e(); virtual void v5f();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void slot190(void);                                          // +0x190
};

class BfmeDfe6e4
{
public:
	void _M_rva00625699(void);
};

// Holds a reference on the 0x009FE6E4 counter: the constructor (0x0023D46F)
// stores the pointer and counts it up, the destructor counts it down.
class Rva0023D46F
{
public:
	Rva0023D46F(BfmeDfe6e4 *counter);
	~Rva0023D46F(void)
	{
		if (m_counter)
			m_counter->_M_rva00625699();
	}

private:
	BfmeDfe6e4 *m_counter;
};

// A scope object whose out-of-line constructor and destructor are the shared
// empty bodies 0x0047A6A9 / 0x000B3FD0.
class Rva00248558Scope
{
public:
	Rva00248558Scope(void);
	~Rva00248558Scope(void);
};

class Rva0023D6D5
{
public:
	void rva0023D6D5(bool loadingSaveGame);
};

class Rva0021A54A;

class Rva0021B3FA
{
public:
	void rva0021B3FA(void);
};

class GameLODManager
{
public:
	int getStaticLODLevel(void) const { return m_staticLODLevel; }

private:
	char m_pad0000[0x1768];
	int m_staticLODLevel;
};


void bfmeClearReceiverFlag(int value);

extern AudioManager *TheAudio;
extern BfmeDfe6e4 *theBfmeDfe6e4;
extern Rva0021A54A *TheHeroManager;
extern GameLODManager *TheGameLODManager;
extern int SavedClientFrame;
extern unsigned char g_00DFF004;
extern char g_00E09B08[];
extern int g_00E09A00;

void GameLogic::rva00248558(bool loadingSaveGame)
{
	if (TheWritableGlobalData->m_123d)
		g_00E09B08[0] = '\0';

	Rva0023C83B closeGuard;
	TheAudio->slot190();
	m_9c = true;
	Rva0023D46F counterRef(theBfmeDfe6e4);
	Rva00248558Scope scope;
	if (m_110 == 4)
		TheGameInfo = 0;
	bfmeClearReceiverFlag(0);

	int progress = 3;
	rva00241230(loadingSaveGame);
	rva00244CB0(loadingSaveGame, TheGameInfo);
	Rva0004224C fpModeGuard;
	rva002469A5(loadingSaveGame, &progress);
	rva00246422(loadingSaveGame);
	progress = 0x29;
	rva002421F5(loadingSaveGame, &progress);
	((Rva0023C7D2 *)this)->rva0023C7BB(0x32);
	rva00248278(loadingSaveGame);
	Profile::StopRange("newgame");
	rva0023F52C(loadingSaveGame);
	m_6d = false;
	g_00DFF004 = 0;
	rva0024004D(loadingSaveGame);
	m_72 = false;
	m_44 = true;
	m_9d = false;
	rva0023C8DA(loadingSaveGame);
	((Rva0023D6D5 *)this)->rva0023D6D5(loadingSaveGame);
	((Rva0023E7D9 *)this)->rva0023F88C(loadingSaveGame);
	SavedClientFrame = 0;
	((Rva0021B3FA *)TheHeroManager)->rva0021B3FA();

	if (TheWritableGlobalData->m_123d) {
		strcpy(g_00E09B08, "assetload ");
		const char *mapName = TheWritableGlobalData->m_mapName.str();
		const char *slash = _imp__strrchr(mapName, '\\');
		strcat(g_00E09B08, slash ? slash + 1 : mapName);
		if (TheGameLODManager) {
			switch (TheGameLODManager->getStaticLODLevel()) {
			case 0:
			case 1:
				strcat(g_00E09B08, " (low)");
				break;
			case 2:
				strcat(g_00E09B08, " (medium)");
				break;
			case 3:
			case 4:
				strcat(g_00E09B08, " (high)");
				break;
			}
		}
		strcat(g_00E09B08, ".csv");
		g_00E09A00 = 0;
	}
}
