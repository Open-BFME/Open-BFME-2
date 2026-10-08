// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
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

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Libraries/Source/profile/profile.h"

// STLport's __copy_trivial is a memmove wrapper the shipped header defined
// inline; retail calls it out of line at 0x000179B0 but the compiler still saw
// it could not throw: the vector copy at 0x002CFAB9 has no EH frame, and
// populateRandomSideAndColor frees its copied vector through the _M_start it
// already holds in a register (the copy never spills `this`).
namespace _STL { void *__copy_trivial(const void *__first, const void *__last, void *__result) throw(); }

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
	virtual void update(void);                                           // +0x28
	void setName(AsciiString name);

private:
	int m_04;
	AsciiString m_name;
};

class PartitionManager : public SubsystemInterface
{
public:
	virtual void update(void);                                           // +0x28
	void setRegion(const Region3D *extent, float cellSize);
	void rva00625310(int value);
	void rva00625300(const Region3D *extent);
	void revealMapForPlayerPermanently(int playerIndex);

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

class Rva00240000;

class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
		bool newGame);                                                   // +0x10
	virtual void newMap(bool loadingSaveGame);                           // +0x14
	virtual void t06(void); virtual void t07(void);
	virtual void getExtent(Region3D *extent) const;                      // +0x20
	void rva002817F2(const AsciiString &filename);
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
	virtual void setLocalPlayerIndex(int playerIndex);                   // +0x14
};

class Pathfinder
{
public:
	void rva002E8DAA(void);
	void rva002F0F07(void);
};

class AI : public SubsystemInterface
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	int m_0c;
	Pathfinder *m_pathfinder;                                            // +0x10
};

class AssetList;
struct AssetLoadMode;

// 0x00203BB1 is rowed as a free function but runs on TheScriptEngine; the
// member-pointer union loads ecx for it (BFME 1 GameLogic::update precedent).
void Rva00203BB1ForceAppContinue(void);

class ScriptEngine : public SubsystemInterface
{
public:
	void rva00205358(AssetList *assets, AssetLoadMode *mode);
	void rva00207C02(void);
	void rva002047CF(void);
	void forceAppContinue(void)
	{
		union
		{
			void (*entry)(void);
			void (ScriptEngine::*method)(void);
		} fn;
		fn.entry = &Rva00203BB1ForceAppContinue;
		(this->*fn.method)();
	}
};

class Rva00203B08
{
public:
	bool rva00203AE5(void);
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
	void update(void);
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
	void rva00439965(void);

private:
	int m_body[6];
};

class Dict;

// One 16-byte record of the indexed team list at SidesList+0xF44: +0 links
// the live list (record 0 heads it), +6 is the per-key chain link that
// TeamsInfoRec::bfmeRelease (0x0032C26D) repairs.
struct TeamsInfoNode
{
	short m_previous;
	short m_next;
	short m_chainNext;
	short m_chainPrevious;
	int m_entry;
	int m_extra;
};

class TeamsInfoRec
{
public:
	void bfmeRelease(int index);
	TeamsInfoNode *getNode(int index) { return &m_nodes[index]; }
	int addTeam(const Dict *d);

private:
	char m_tree[0xc];
	TeamsInfoNode *m_nodes;                                              // +0x0C
	char m_pad10[0x1c - 0x10];
};

class Dict
{
public:
	Dict(int numPairs = 0);
	~Dict() { releaseData(); }
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	void setInt(int key, int value);
	void setBool(int key, bool value);
	void setAsciiString(int key, const AsciiString &value);
	void setUnicodeString(int key, const UnicodeString &value);
	void clear(void);

private:
	void releaseData(void);

	void *m_data;
};

class SidesInfo
{
public:
	Dict *getDict(void) { return &m_dict; }

	void *m_pBuildList;
	Dict m_dict;                                                         // +0x04
	char m_pad08[0x60 - 8];
};

class SidesList
{
public:
	void rva0032D554(void);
	void rva0032F84F(void);
	void rva0032C991(void);
	void rva0032FF91(void);
	void rva0032FD8E(void);
	TeamsInfoRec *getTeamInfo(void) { return &m_teams; }
	int addSide(const Dict *d);
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	void addTeam(const Dict *d) { m_teams.addTeam(d); }
	void rva0032E02B(void);
	int getNumSides(void) const { return m_numSides; }
	// The header body the compiler sees but does not inline (retail calls the
	// 0x002035BA copy): knowing it stores nothing, SetUpCampaignPlayers keeps
	// TheSidesList in esi across the call. The copy emitted here is
	// byte-identical to retail's.
	__declspec(noinline) SidesInfo *getSideInfo(int side)
	{
		if (side >= 0 && side < m_numSides)
			return &m_sides[side];
		return 0;
	}

	char m_pad000[0x3c];
	int m_numSides;                                                      // +0x3C
	SidesInfo m_sides[(0xf44 - 0x40) / 0x60];                            // +0x40
	char m_padSides[(0xf44 - 0x40) % 0x60];
	TeamsInfoRec m_teams;                                                // +0xF44
	char m_padF60[0xf7c - 0xf60];
	bool m_f7c;
};

class GlobalData
{
public:
	char m_pad000[0xc];
	AsciiString m_mapName;
	char m_pad010[0x26 - 0x10];
	bool m_26;
	char m_pad027[0xd4 - 0x27];
	float m_d4;
	float m_d8;
	char m_pad0DC[0x9c1 - 0xdc];
	bool m_9c1;
	char m_pad9C2[0xaf5 - 0x9c2];
	bool m_af5;
	char m_padAF6[0xbd0 - 0xaf6];
	int m_bd0;
	char m_padBD4[0xc18 - 0xbd4];
	unsigned int m_c18;
	char m_padC1C[0xc30 - 0xc1c];
	int m_c30;
	char m_padC34[0xd45 - 0xc34];
	bool m_d45;
	char m_padD46[0xd48 - 0xd46];
	int m_d48;
	char m_padD4C[0xddc - 0xd4c];
	bool m_ddc;
	char m_padDDD[0xe94 - 0xddd];
	int m_e94;
	char m_padE98[0x1110 - 0xe98];
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

class GameMessage;
class BfmeThingEC;
struct Rva00241529Record;
struct PlayerLeaveStatus;
class PlayerTemplate;

enum KindOfType
{
	KINDOF_INVALID = -1
};

class UpdateModule;
typedef _STL::vector<UpdateModule *> UpdateModuleList;

// The object embedded at GameLogic+0x184 (0x2C bytes); its member 0x0040CA98
// never reads this.
class Rva0040CA98
{
public:
	void rva0040CA98(void);

private:
	char m_body[0x2c];
};

enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic : public SubsystemInterface
{
public:
	virtual void init(void);
	virtual void v11(void); virtual void v12(void);
	virtual void update(int phase);                                      // +0x34
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
	void startNewGame_Init(bool loadingSaveGame);
	void rva002469A5(bool loadingSaveGame, int *progress);
	void startNewGame_PlaceMPBuildings(bool loadingSaveGame, int *progress);
	void rva00248278(bool loadingSaveGame);
	void rva0023F52C(bool loadingSaveGame);
	void rva0024004D(bool loadingSaveGame);
	void loadMapINI(AsciiString mapName);
	void rva0023E628(AsciiString mapName);
	void CreateMPPlayers(bool isSkirmish, int progress);
	void SetUpCampaignPlayers(void);
	void rva0023E0C7(void);
	void lastHeardFrom(int playerIndex);
	bool rva001DCD1C(void);
	void rva0024622F(bool loadingSaveGame);
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }
	bool rva0023C8DA(unsigned char loadingSaveGame);
	Object *findObjectByID(ObjectID id);
	void rva00244D56(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
		const KindOfType *requireKind, bool dontCreate);
	void startNewGame_OpenLoadScreen(bool loadingSaveGame, GameInfo *game);
	bool isInMultiplayerGame(void);
	bool rva00085124(void);
	void formatPlayerStartWaypointName(AsciiString *name);
	void ProcessCRC(unsigned int crc, int player, unsigned int frame, GameMessage *message,
		bool forced, BfmeThingEC *stream);
	void rva0023F8DA(void);
	const AsciiString &rva0023FB58(int index);
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
	void rva002401DD(BfmeThingEC *stream, unsigned int frame, int player);
	bool rva002259F3(void);
	bool rva0042219(void);
	void processCommandList(void);
	void processDestroyList(void);
	void logicMessageDispatcher(GameMessage *msg, void *userData);
	unsigned int getCRC(int mode);
	void rva00240EBC(void);

	Object *getFirstObject(void) const { return m_objList; }
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferObjectTOC(Xfer *xfer);

private:
	LoadScreen *getLoadScreen(bool saveGame);

public:

	char m_pad00C[0x10 - 0x0c];
	char m_10[0x24 - 0x10];
	char m_24[0x30 - 0x24];
	float m_width;
	float m_height;
	unsigned int m_38;
	char m_pad03C[0x40 - 0x3c];
	unsigned int m_40;
	unsigned int getFrame(void) const { return m_40; }
	bool m_44;
	char m_pad045[0x48 - 0x45];
	Rva00241529Record *m_48;
	IntList::iterator m_4c;
	IntList m_50;
	AsciiString m_54;
	_STL::vector<AsciiString> m_58;
	AsciiString m_64;
	AsciiString m_68;
	bool m_6c;
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
	bool m_9e;
	bool m_9f;
	int m_a0;
	int m_a4;
	bool m_a8;
	char m_pad0A9[0xac - 0xa9];
	Object *m_objList;
	char m_pad0B0[0xb4 - 0xb0];
	char m_b4[0xc8 - 0xb4];
	UpdateModuleList m_updates[4];                                       // +0xC8
	UpdateModuleList m_sleeping;                                         // +0xF8
	UpdateModule *m_104;
	char m_pad108[0x10c - 0x108];
	int m_10c;
	int m_110;
	int m_114;
	int m_118;
	bool m_11c;
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
	_STL::vector<void *> m_164;
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva00243177 *m_178;
	int m_17c;
	int m_180;
	Rva0040CA98 m_184;
	int m_1b0;
	int m_1b4;
	int m_1b8;
	bool m_1bc;
	char m_pad1BD[0x1c0 - 0x1bd];
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

// One 0x14-byte start-position record of the map metadata (array at +0x54);
// CreateMPPlayers tests only the byte at +2, populateRandomSideAndColor reads the
// set of faction names allowed at the position (+8, node count at +0xC).
struct MapStartPosition
{
	char m_pad00[2];
	bool m_2;
	char m_pad03[8 - 3];
	_STL::set<AsciiString> m_factions;                                   // +0x08
};
typedef char MapStartPositionSizeCheck[sizeof(MapStartPosition) == 0x14 ? 1 : -1];

class MapMetaData
{
public:
	char m_pad00[0x20];
	int m_numPlayers;
	char m_pad24[0x38 - 0x24];
	WaypointMap m_waypoints;
	char m_padWaypoints[0x54 - 0x38 - sizeof(WaypointMap)];
	MapStartPosition m_startPositions[8];                                // +0x54
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

// Create-a-hero record of a slot (+0x64, valid when the byte at +0x60 is
// set): class and subclass indices passed to GetFactionMaskType.
struct GameSlotHeroInfo
{
	char m_pad00[0x0c];
	unsigned int m_classIndex;                                           // +0x0C
	unsigned int m_subClassIndex;                                        // +0x10
};

class GameSlot
{
public:
	bool isOccupied() const;
	bool isAI() const;
	void saveOffOriginalInfo();
	int getStartPos() const { return m_10; }
	void setStartPos(int startPos) { m_10 = startPos; }
	int getPlayerTemplate() const { return m_18; }
	int getTeamNumber() const { return m_1c; }
	int getColor() const { return m_c; }
	void setColor(int color) { m_c = color; }
	void setPlayerTemplate(int playerTemplate);
	bool isHuman() const;
	const unsigned short *getNameStr() const { return m_name.str(); }
	const GameSlotHeroInfo *getHero() const { return m_hasHero ? &m_hero : 0; }

	char m_pad00[0x4];
	int m_state;                                                         // +0x04
	char m_pad08[0xc - 0x8];
	int m_c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_bfme20;                                                        // +0x20
	char m_pad24[0x30 - 0x24];
	UnicodeString m_name;                                                // +0x30
	AsciiString m_34;
	char m_pad38[0x4c - 0x38];
	int m_livingWorldPlayerID;                                           // +0x4C
	char m_pad50[0x60 - 0x50];
	bool m_hasHero;                                                      // +0x60
	GameSlotHeroInfo m_hero;                                             // +0x64
};

class GameInfo
{
public:
	virtual ~GameInfo(void);
	virtual void gi04(void); virtual void gi08(void); virtual void gi0C(void);
	virtual void gi10(void); virtual void gi14(void); virtual void gi18(void);
	virtual void gi1C(void); virtual void gi20(void); virtual void gi24(void);
	virtual void gi28(void); virtual void gi2C(void); virtual void gi30(void);
	virtual int getLocalSlotNum(void) const;                             // +0x34
	GameSlot *getSlot(int index);
	bool isPlayerPreorder(int index);
	const GameSlot *getConstSlot(int index) const;
	AsciiString getMap() const;
	bool isStartPositionTaken(int positionIdx, int slotToIgnore = -1) const;
	bool isColorTaken(int colorIdx, int slotToIgnore = -1) const;

	char m_pad04[0x0c - 4];
	int m_0c;                                                            // +0x0C
	char m_pad10[0x54 - 0x10];
	int m_54;                                                            // +0x54
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

// ?startNewGame_OpenLoadScreen@GameLogic@@QAEX_NPAVGameInfo@@@Z @0x00244CB0 166B (ret 8 at
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
	virtual void slot28();
	void rva001DC5EC(void);
	void reverse(AsciiString groupName);
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

void GameLogic::startNewGame_OpenLoadScreen(bool loadingSaveGame, GameInfo *game)
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

// DisabledMaskType: one word; its constructors memset, so it returns
// through a hidden pointer.
template <int NUM_BITS>
class BitFlags
{
public:
	BitFlags(const BitFlags &src);
	bool any(void) const;
	bool test(const void *other) const;
	bool anyIntersectionWith(const BitFlags &that) const { return that.test(this); }

private:
	unsigned int m_bits[(NUM_BITS + 31) / 32];
};
typedef BitFlags<11> DisabledMaskType;

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE
};

class AIUpdateInterface
{
public:
	bool isMoving(void) const;
	void destroyPath(void);
};

class Object : public Thing
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }
	Object *getNextObject(void) const { return m_next; }
	void rva00293E64(Dict *properties);
	bool testStatus(ObjectStatusTypes bit) const;
	bool isDisabled(void) const { return m_disabledMask.any(); }
	const DisabledMaskType &getDisabledFlags(void) const { return m_disabledMask; }
	AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
	void rva0023D3AF(void *frame);
	void rva00290357(void);
	void rva002903C3(void);
	void rva002903EF(void);
	void rva00297612(void);

private:
	void *m_vtbl;
	const ThingTemplate *m_template;
	char m_pad08[0x8c - 0x08];
	Object *m_next;
	char m_pad090[0x94 - 0x90];

public:
	unsigned int m_94;                                                   // +0x94
	char m_pad098[0x188 - 0x98];
	unsigned int m_188;                                                  // +0x188
	char m_pad18C[0x1c8 - 0x18c];

private:
	DisabledMaskType m_disabledMask;                                     // +0x1C8
	char m_pad1CC[0x258 - 0x1cc];
	AIUpdateInterface *m_ai;                                             // +0x258
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

// The +0x08 member of Player: 0x003805BB takes a point value and a flag
// (Player::addSkillPointsForKill passes true), 0x002E6A93 stores its +0x18.
class Rva003805BB
{
public:
	bool rva003805BB(float value, bool flag);
	void rva002E6A93(int value);

	char m_pad00[0x14];
	int m_14;
	int m_18;
};

enum PlayerType
{
	PLAYER_HUMAN
};

class Player
{
public:
	Team *getDefaultTeam(void) const { return m_defaultTeam; }
	PlayerType getPlayerType(void) const { return m_playerType; }
	int getPlayerIndex(void) const { return m_playerIndex; }
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;

	char m_pad00[0x8];
	Rva003805BB m_skillPoints;
	char m_pad24[0x34 - 0x24];
	PlayerTemplate *m_34;
	char m_pad38[0x4c - 0x38];
	AsciiString m_4c;
	char m_pad50[0x54 - 0x50];
	int m_playerIndex;                                                   // +0x54
	char m_pad58[0x5c - 0x58];
	PlayerType m_playerType;
	char m_pad60[0x2ec - 0x60];
	Team *m_defaultTeam;
	char m_pad2F0[0x3bc - 0x2f0];
	int m_3bc;
	char m_pad3C0[0x4ac - 0x3c0];
	int m_4ac;
};

enum NameKeyType
{
	NAMEKEY_INVALID
};

class PlayerList : public SubsystemInterface
{
public:
	virtual void p0b(void); virtual void p0c(void);
	virtual void p0d(void); virtual void p0e(void);
	virtual void newMap(void);                                           // +0x3C

	Player *getNeutralPlayer(void) const { return m_neutralPlayer; }
	Player *getLocalPlayer(void) const { return m_local; }
	Player *getNthPlayer(int index);
	Player *findPlayerWithNameKey(NameKeyType key);
	void setLocalPlayer(Player *player);

private:
	char m_pad0C[0x10 - 0x0c];
	Player *m_local;
	char m_pad14[0x18 - 0x14];
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
	startNewGame_Init(loadingSaveGame);
	startNewGame_OpenLoadScreen(loadingSaveGame, TheGameInfo);
	Rva0004224C fpModeGuard;
	rva002469A5(loadingSaveGame, &progress);
	rva00246422(loadingSaveGame);
	progress = 0x29;
	startNewGame_PlaceMPBuildings(loadingSaveGame, &progress);
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

// ?rva00248278@GameLogic@@QAEX_N@Z
// @0x00248278 736B (ret 4 at 0x00248555; sole caller 0x00248632, the
// new-game pass). The tail of BFME 1's startNewGame from the asset preload
// on (GameLogic.cpp: hideCommunicator, progress, default camera angle and
// zoom, TheRecorder's controls, the InitialCameraPosition waypoint or a
// 50/50/0 fallback, the partition update, ThePlayerList->newMap unless
// loading, the skill-point pass for human players). Target facts: each of
// the first steps is followed by Sleep(1); progress 0x5F/0x60/0x61 goes
// through 0x0023C7BB; the waypoint name is a StringBase copy formatted by
// formatPlayerStartWaypointName; the skill pass runs only when 0x0023C666
// says so and hands (float)this+0x94 with false to the player's +0x08
// member, then stores that member's +0x14 into its +0x18 (0x002E6A93);
// 0x0023C6FD gates this+0x118 = TheGlobalData+0xE94; in a network game
// TheNetwork slots 0x90 and 0x3C(0) run; unless TheGlobalData+0x1110 the
// script engine (0x00205358) fills a fresh AssetList that 0x0061F010
// merges. Slot meanings past the donor's are unknown. Shape: the waypoint
// location is copied member by member (retail moves each float through
// xmm0); a whole-struct copy becomes rep movsd and shifts the register
// assignment of the whole body.
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

class ParticleSystemManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10(); virtual void v11(); virtual void v12();
	virtual void preloadAssets(void);                                    // +0x4C
};

class ControlBar
{
public:
	void rva0031D64F(void);
	void rva0031AD48(bool flag);
	void rva0031C40E(Player *player);
	void rva0031BAC3(Player *player);

	char m_pad000[0x210];
	Player *m_210;
};

class G00DFF080Obj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04();
	virtual void slot14(void);                                           // +0x14
};

class View
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15();
	virtual void initHeightForMap(void);                                 // +0x58
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v1a();
	virtual void v1b(); virtual void v1c(); virtual void v1d();
	virtual bool slot78(void);                                           // +0x78
	virtual void v1f(); virtual void v20(); virtual void v21(); virtual void v22();
	virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(); virtual void v28(); virtual void v29(); virtual void v2a();
	virtual void v2b(); virtual void v2c(); virtual void v2d(); virtual void v2e();
	virtual void v2f(); virtual void v30(); virtual void v31();
	virtual void lookAtPosition(const Coord3D *pos, int frames, float easeIn, float easeOut); // +0xC8
	virtual void v33(); virtual void v34(); virtual void v35();
	virtual bool slotD8(void);                                           // +0xD8
	virtual void v37(); virtual void v38(); virtual void v39(); virtual void v3a();
	virtual void v3b(); virtual void v3c(); virtual void v3d(); virtual void v3e();
	virtual void v3f(); virtual void v40(); virtual void v41(); virtual void v42();
	virtual void v43(); virtual void v44();
	virtual void setAngleAndPitchToDefault(void);                        // +0x114
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v4a(); virtual void v4b(); virtual void v4c(); virtual void v4d();
	virtual void v4e();
	virtual void setZoomToDefault(void);                                 // +0x13C
	virtual void v50();
	virtual void setOkToAdjustHeight(bool ok);                           // +0x144
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v5a(); virtual void v5b(); virtual void v5c(); virtual void v5d();
	virtual void v5e(); virtual void v5f(); virtual void v60(); virtual void v61();
	virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
	virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v6a(); virtual void v6b(); virtual void v6c(); virtual void v6d();
	virtual void v6e(); virtual void v6f(); virtual void v70(); virtual void v71();
	virtual void v72();
	virtual bool v73(void);                                              // +0x1CC
	virtual void v74(void *a, int b, int c, bool d);                     // +0x1D0
};

// 0x00A02290 is TheRecorder. Its member 0x0037BD81 is rowed as
// InGameUI::createReplayControl; the body is ZH's RecorderClass::initControls
// (hide ReplayControl.wnd unless the +0x1C mode is playback).
class RecorderClass;

class InGameUI
{
	friend class GameLogic;

public:
	void setClientQuiet(bool quiet) { m_clientQuiet = quiet; }

protected:
	void createReplayControl(void);

private:
	char m_pad000[0x8c5];
	bool m_clientQuiet;                                                  // +0x8C5
};

// A lazily resolved name key: 0x00148F5E fills m_key from m_name.
class StaticNameKey
{
public:
	mutable int m_key;
	const char *m_name;
};

class Rva00148F5ECache
{
public:
	NameKeyType get(void);
};

static __forceinline NameKeyType staticKey(const StaticNameKey &key)
{
	return ((Rva00148F5ECache *)&key)->get();
}

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

class Waypoint
{
public:
	const Coord3D *getLocation(void) const { return &m_location; }

private:
	char m_pad00[0xc];
	Coord3D m_location;
};

Waypoint *Rva00506CC3FindWaypoint(const AsciiString &name);

class Rva00E02F3CObj
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d();
	virtual void slot38(void);                                           // +0x38
};

class Rva002A8F24 : public SubsystemInterface
{
public:
	void rva002A95F9(void);
};

class TeamFactory : public SubsystemInterface
{
public:
	void rva003A262C(void);
};

class Rva0023C666
{
public:
	bool rva0023C666(void);
};

class BfmeGlob939D
{
public:
	char bfmeCall939D(void);
};

class NetworkInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e();
	virtual void slot3C(int arg);                                        // +0x3C
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void slot90(void);                                           // +0x90
	virtual void slot94(void);                                           // +0x94
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v2a();
	virtual bool slotAC(void);                                           // +0xAC
	virtual void v2c();
	virtual int slotB4(void);                                            // +0xB4
};

extern ParticleSystemManager *TheParticleSystemManager;
extern ControlBar *TheControlBar;
extern G00DFF080Obj *g_00DFF080;
extern View *TheTacticalView;
extern RecorderClass *TheRecorder;
extern NameKeyGenerator *TheNameKeyGenerator;
extern const StaticNameKey TheKey_InitialCameraPosition;
class VictorySystem;
extern VictorySystem *TheVictorySystem;
extern Rva002A8F24 *g_00DFEEF8;
extern TeamFactory *TheTeamFactory;
extern NetworkInterface *TheNetwork;

void rva0043D467(void);

void GameLogic::rva00248278(bool loadingSaveGame)
{
	TheParticleSystemManager->preloadAssets();
	Sleep(1);
	TheControlBar->rva0031D64F();
	TheControlBar->rva0031AD48(false);
	rva0043D467();
	g_00DFF080->slot14();
	Sleep(1);
	((Rva0023C7D2 *)this)->rva0023C7BB(0x5f);
	Sleep(1);
	TheTacticalView->setAngleAndPitchToDefault();
	Sleep(1);
	TheTacticalView->setZoomToDefault();
	Sleep(1);
	if (TheRecorder)
		((InGameUI *)TheRecorder)->createReplayControl();

	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	AsciiString startingCamName = TheNameKeyGenerator->keyToName(staticKey(TheKey_InitialCameraPosition));
	formatPlayerStartWaypointName(&startingCamName);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	((Rva0023C7D2 *)this)->rva0023C7BB(0x60);
	TheTacticalView->initHeightForMap();
	TheTacticalView->setAngleAndPitchToDefault();
	TheTacticalView->setZoomToDefault();

	Waypoint *way = Rva00506CC3FindWaypoint(startingCamName);
	if (way) {
		Coord3D pos;
		pos.x = way->getLocation()->x;
		pos.y = way->getLocation()->y;
		pos.z = way->getLocation()->z;
		TheTacticalView->lookAtPosition(&pos, 0, 0.0f, 0.0f);
	} else {
		Coord3D pos;
		pos.x = 50.0f;
		pos.y = 50.0f;
		pos.z = 0.0f;
		TheTacticalView->lookAtPosition(&pos, 0, 0.0f, 0.0f);
	}

	((Rva0023C7D2 *)this)->rva0023C7BB(0x61);
	ThePartitionManager->update();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	if (!loadingSaveGame)
		ThePlayerList->newMap();
	((Rva00E02F3CObj *)TheVictorySystem)->slot38();
	g_00DFEEF8->rva002A95F9();
	TheTeamFactory->rva003A262C();

	if (!loadingSaveGame && ((Rva0023C666 *)this)->rva0023C666()) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		for (int i = 0; i < 20; ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player && player->getPlayerType() == PLAYER_HUMAN) {
				player->m_skillPoints.rva003805BB((float)m_94, false);
				player->m_skillPoints.rva002E6A93(player->m_skillPoints.m_14);
			}
		}
	}

	if (((BfmeGlob939D *)this)->bfmeCall939D())
		m_118 = TheWritableGlobalData->m_e94;

	if (isInMultiplayerGame() && TheNetwork) {
		TheNetwork->slot90();
		TheNetwork->slot3C(0);
	}

	if (!TheWritableGlobalData->m_1110) {
		AssetLoadMode mode;
		AssetList assets;
		TheScriptEngine->rva00205358(&assets, &mode);
		bfmeMergeReceiverKeys((int)&assets);
	}
}

// ?startNewGame_Init@GameLogic@@QAEX_N@Z @0x00241230 431B (EH frame, ret 4; next
// body 0x002413DF). Called from the new-game pass 0x00248558.
// Target evidence: TheWindowManager (0x009FEF1C) virtual +0x28, the
// GlobalData +0xDDC byte copied to +0x11C, bfmeClearReceiverFlag(2), the
// argument stored at +0x9E, GlobalData +0x26 set when the +0x110 mode is 0 or
// 6, g_00DFF004 and +0x6D set, TheMouse engine visibility off, the
// transition-handler wait 0x001DC5EC under +0x72; then, for a new map only,
// TheGameState (0x009FF08C) takes the map name by value (0x001EB298) and
// tests a UnicodeString copy of it (0x002DC7C1, result unused) before +0xA8
// is set. The "newgame" profile range, the 1000 at +0x118, the defaults pass
// 0x00240E18, GlobalData +0xAF5 and the -1/1/1/1 field resets follow, and
// the body ends with the inlined slot colour check over TheGameInfo (slot
// colour +0x0C, TheMultiplayerSettings colour count cached +0x40 from +0x38,
// isColorTaken 0x003FF34A).
// Donor: BFME 1 GameLogic.cpp startNewGame (setPristineMapName,
// isInSaveDirectory sanity check, m_rankLevelLimit = 1000, setDefaults,
// m_loadScreenRender, the marker/icon/LOD flags and hulk override -1) and
// its static checkForDuplicateColors, which retail inlines verbatim (and also
// keeps out of line, with no callers, at 0x0023E064). BFME 2
// splits the rest of startNewGame into the stages 0x0024004D onwards; field
// names stay offset names.
class GameWindowManager : public SubsystemInterface
{
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

class GameState;

class Rva001EB298
{
public:
	void rva001EB298(AsciiString mapName);
};

class Rva002DC7C1
{
public:
	bool rva002DC7C1(const UnicodeString &path) const;
};

class MultiplayerSettings
{
public:
	int getNumColors()
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}
	bool isShroudInMultiplayer() const { return m_shroudInMultiplayer; }
	class MultiplayerColorDefinition *getColor(int which);
private:
	char m_pad00[0x1c];
	bool m_shroudInMultiplayer;                                          // +0x1C
	char m_pad1D[0x38 - 0x1d];
	int m_colorCount;                                                    // +0x38
	int m_3c;
	int m_numColors;                                                     // +0x40
};

extern GameWindowManager *TheWindowManager;
extern Mouse *TheMouse;
extern GameState *TheGameState;
extern MultiplayerSettings *TheMultiplayerSettings;

static void checkForDuplicateColors(GameInfo *game)
{
	if (!game)
		return;
	int i;

	for (i = 8 - 1; i >= 0; --i) {
		GameSlot *slot = game->getSlot(i);

		if (!slot || !slot->isOccupied())
			continue;

		int colorIdx = slot->getColor();
		if (colorIdx < 0 || colorIdx >= TheMultiplayerSettings->getNumColors())
			continue;

		slot->setColor(-1);
		if (!game->isColorTaken(colorIdx))
			slot->setColor(colorIdx);
	}
}

void GameLogic::startNewGame_Init(bool loadingSaveGame)
{
	TheWindowManager->update();
	m_11c = TheWritableGlobalData->m_ddc;
	bfmeClearReceiverFlag(2);
	m_9e = loadingSaveGame;
	if (m_110 == 0 || m_110 == 6)
		TheWritableGlobalData->m_26 = true;
	g_00DFF004 = 1;
	m_6d = true;
	TheMouse->_bfme_setEngineVisibility(false);
	if (m_72)
		TheTransitionHandler->rva001DC5EC();

	if (!loadingSaveGame) {
		((Rva001EB298 *)TheGameState)->rva001EB298(TheWritableGlobalData->m_mapName);
		((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(TheWritableGlobalData->m_mapName));
		m_a8 = true;
	}

	Profile::StartRange("newgame");
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	m_118 = 1000;
	rva00240E18(loadingSaveGame);
	TheWritableGlobalData->m_af5 = true;
	m_a0 = -1;
	m_99 = true;
	m_9a = true;
	m_9b = true;
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	checkForDuplicateColors(TheGameInfo);
}

// ?startNewGame_PlaceMPBuildings@GameLogic@@QAEX_NPAH@Z @0x002421F5 494B (EH frame, ret 8;
// next body 0x002423E1). Called from the new-game pass 0x00248558 with the
// load-progress counter.
// Target evidence: progress 0x28 first; for a new game with TheGameInfo set,
// the eight "Player_%d_Start" waypoints (Rva00506CC3FindWaypoint) are summed
// into a zeroed local whose result nothing reads, then each slot is fetched
// (device interfaces flushed per slot) and, when occupied, its player is
// found by the slot's +0x34 name key. An observer slot (template -2) gets
// template 0 and then the index of "FactionObserver" in
// ThePlayerTemplateStore (0x1DC-byte templates between +0x0C and +0x10,
// flushing per index); any other slot goes to 0x00241C75 with its slot
// number, player and nth template. Progress advances once per occupied slot.
// Donor: BFME 1 GameLogic.cpp startNewGame's "place initial network
// buildings/units" loop (observer template fix-up, placeNetworkBuildingsForPlayer);
// BFME 2 keys players by the slot's name rather than "player%d" and drops
// the locked-general check. Field names stay offset names.
class PlayerTemplate;

class PlayerTemplateBody
{
	char m_bytes[0x1dc];
};

class PlayerTemplateStore
{
public:
	int getPlayerTemplateCount() { return m_finish - m_start; }
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;

private:
	char m_pad00[0x0c];
	PlayerTemplateBody *m_start;                                         // +0x0C
	PlayerTemplateBody *m_finish;                                        // +0x10
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

void rva00241C75(int slotNum, const GameSlot *slot, Player *player, const PlayerTemplate *pt);

static inline void zeroCoord(Coord3D *c)
{
	c->x = 0.0f;
	c->y = 0.0f;
	c->z = 0.0f;
}

static inline void addCoord(Coord3D *dst, const Coord3D *src)
{
	dst->x += src->x;
	dst->y += src->y;
	dst->z += src->z;
}

void GameLogic::startNewGame_PlaceMPBuildings(bool loadingSaveGame, int *progress)
{
	((Rva0023C7D2 *)this)->rva0023C7BB(0x28);
	if (TheGameInfo && !loadingSaveGame) {
		Coord3D center;
		zeroCoord(&center);
		for (int i = 0; i < 8; ++i) {
			AsciiString waypointName;
			waypointName.format("Player_%d_Start", i + 1);
			Waypoint *waypoint = Rva00506CC3FindWaypoint(waypointName);
			if (waypoint)
				addCoord(&center, waypoint->getLocation());
		}

		for (int i = 0; i < 8; ++i) {
			GameSlot *slot = TheGameInfo->getSlot(i);
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			if (!slot || !slot->isOccupied())
				continue;

			Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(slot->m_34));
			if (player) {
				if (slot->getPlayerTemplate() == -2) {
					slot->setPlayerTemplate(0);
					const PlayerTemplate *pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
					if (pt) {
						for (int j = 0; j < ThePlayerTemplateStore->getPlayerTemplateCount(); ++j) {
							Rva0134FAA0->slot28();
							bfmeReleaseQueuedDeviceInterfaces();
							if (pt == ThePlayerTemplateStore->getNthPlayerTemplate(j)) {
								slot->setPlayerTemplate(j);
								break;
							}
						}
					}
				} else {
					rva00241C75(i, slot, player, ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate()));
				}
			}
			((Rva0023C7D2 *)this)->rva0023C7BB((*progress)++);
		}
	}
}

// ?rva0023F52C@GameLogic@@QAEX_N@Z @0x0023F52C 864B (EH frame, ret 4; next
// body 0x0023F88C). Called from the new-game pass 0x00248558.
// Target evidence: mode 4 (+0x110) pushes "MainMenu.apt" on TheShell when
// its +0x4C screen count is zero, else shows and raises the top layout
// (virtuals +0x10/+0x14), then HideControlBar(true); mode 7 does the same
// minus the push. Otherwise the stats collector at 0x00E032F8 is reset (and
// first new'd, 0x68 bytes, when GlobalData +0xC30 > 0); mode 3 makes
// "ReplayObserver" the local player, stores the recorder's +0xE6C player in
// TheControlBar +0x210, sets TheRadar +0x11 and refreshes the shroud, while
// other modes re-set the local player around the neutral one and clear
// +0x210; both hand the local player to TheControlBar 0x0031C40E. Then
// TheTacticalView +0x144 (true), the 0x009FE7A8 flag pass, the
// command-centre selection for every active player in a multiplayer
// recording (iterateObjects 0x0023D6FA), TheControlBar 0x0031BAC3,
// theRadarWindowOverrideSource 0x002D55EF for a new game, the control bar
// shown or hidden by 0x00085124, the GameSpy buddy status 5 with the
// staging room's name in mode 5, each drawable's level start for a new
// game, TheTacticalView +0x1CC/+0x1D0 and the wait for 0x0061F090 to reach
// 100 with Sleep(1).
// Donor: BFME 1 GameLogic.cpp startNewGame's shell/replay tail (shell push
// or top hide/bringForward, StatsCollector reset or NEW, ReplayObserver,
// radar forceOn, refreshShroudForLocalPlayer, setControlBarSchemeByPlayer,
// setOkToAdjustHeight, findAndSelectCommandCenter, initSpecialPowershortcutBar,
// Hide/ShowControlBar, updateBuddyStatus, Drawable onLevelStart). Field and
// method names stay offset names where only the donor knows them.
class WindowLayout
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void hide(bool hide);                                        // +0x10
	virtual void bringForward(void);                                     // +0x14
};

class Shell
{
public:
	void push(AsciiString filename, bool shutdownImmediate = false);
	WindowLayout *top(void);
	int getScreenCount(void) const { return m_screenCount; }

private:
	char m_pad00[0x4c];
	int m_screenCount;                                                   // +0x4C
};

class StatsCollector
{
public:
	StatsCollector(void);
	void rva00437DF8(void);

private:
	char m_pad00[0x68];
};

// ZH File: open/close/read/write/seek after the destructor.
class File
{
public:
	enum seekMode
	{
		START,
		CURRENT,
		END
	};

	virtual ~File(void);
	virtual bool open(const char *filename, int access);                 // +0x04
	virtual void close(void);                                            // +0x08
	virtual int read(void *buffer, int bytes);                           // +0x0C
	virtual int write(const void *buffer, int bytes);                    // +0x10
	virtual int seek(int bytes, seekMode mode);                          // +0x14
};

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class RecorderClass : public SubsystemInterface
{
public:
	bool isMultiplayer(void);
	RecorderModeType getMode(void);
	void logCRCMismatch(void);
	void rva0037BE15(File *output, unsigned int frame);

	char m_pad00C[0xe68 - 0xc];
	int m_e68;
	int m_e6c;
};

class Radar
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
	virtual void refreshTerrain(TerrainLogic *terrain);                  // +0x10
	virtual void r05();
	virtual void newMap(TerrainLogic *terrain);                          // +0x18
	void forceOn(bool force) { m_11 = force; }

private:
	char m_pad04[0x11 - 4];
	bool m_11;
};

class Rva007397D0
{
public:
	void rva007397D0(void);
};

class Rva006C0820
{
public:
	void rva006C0820(void);
};

class Rva0023D494
{
public:
	void rva0023D494(void);
};

class BfmeMemberRV
{
public:
	bool bfmeAskRV(void);
};

class RadarWindowOverrideSource
{
public:
	void rva002D55EF(void);
};

class Rva0022C4DF
{
public:
	UnicodeString rva0022C4DF(void) const;
};

class GameSpyStagingRoom;

class Drawable
{
public:
	void rva00278C6B(void);
	Drawable *getNextDrawable(void) const { return m_next; }

private:
	char m_pad000[0x104];
	Drawable *m_next;                                                    // +0x104
};

class ClientFrameSubsystem
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
	virtual void v20(); virtual void v21(); virtual void v22();
	virtual Drawable *getDrawableList(void);                             // +0x8C

	char m_pad004[0xc8 - 4];
	bool m_c8;
};

enum GameSpyBuddyStatus
{
	GAMESPY_BUDDY_STATUS_5 = 5
};

extern Shell *TheShell;
extern Radar *TheRadar;
extern unsigned int g_Va00DFE7A8;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern GameSpyStagingRoom *TheGameSpyGame;
extern ClientFrameSubsystem *TheGameClient;

void HideControlBar(bool immediate);
void ShowControlBar(bool immediate);
int rva0023D6FA(Object *obj);
int rva0061F090(void);
_STL::string WideCharStringToMultiByte(const unsigned short *orig);
void updateBuddyStatus(GameSpyBuddyStatus status, int sleepTime, _STL::string mapName);

void GameLogic::rva0023F52C(bool loadingSaveGame)
{
	if (m_110 == 4) {
		if (TheShell->getScreenCount() == 0)
			TheShell->push(AsciiString("MainMenu.apt"));
		else if (TheShell->top()) {
			TheShell->top()->hide(false);
			TheShell->top()->bringForward();
		}
		HideControlBar(true);
	} else if (m_110 == 7) {
		if (TheShell->top()) {
			TheShell->top()->hide(false);
			TheShell->top()->bringForward();
		}
		HideControlBar(true);
	} else {
		if (g_00E032F8)
			g_00E032F8->rva00437DF8();
		else if (TheWritableGlobalData->m_c30 > 0) {
			g_00E032F8 = new StatsCollector;
			g_00E032F8->rva00437DF8();
		}

		if (m_110 == 3) {
			ThePlayerList->setLocalPlayer(ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("ReplayObserver")));
			TheControlBar->m_210 = ThePlayerList->getNthPlayer(TheRecorder->m_e6c);
			TheRadar->forceOn(true);
			((Rva007397D0 *)TheShroudManager)->rva007397D0();
			if (g_Va00DFE750)
				((Rva006C0820 *)g_Va00DFE750)->rva006C0820();
			TheControlBar->rva0031C40E(ThePlayerList->getLocalPlayer());
		} else {
			Player *localPlayer = ThePlayerList->getLocalPlayer();
			ThePlayerList->setLocalPlayer(ThePlayerList->getNeutralPlayer());
			ThePlayerList->setLocalPlayer(localPlayer);
			TheControlBar->rva0031C40E(ThePlayerList->getLocalPlayer());
			TheControlBar->m_210 = 0;
		}
	}
	TheTacticalView->setOkToAdjustHeight(true);

	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	if (*(unsigned char *)&g_Va00DFE7A8)
		((Rva0023D494 *)&g_Va00DFE7A8)->rva0023D494();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	if (TheRecorder->isMultiplayer()) {
		for (int i = 0; i < 20; ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player && ((BfmeMemberRV *)player)->bfmeAskRV())
				player->iterateObjects((int (*)(Object *, void *))rva0023D6FA, 0);
		}
	}
	TheControlBar->rva0031BAC3(ThePlayerList->getLocalPlayer());

	if (!loadingSaveGame)
		theRadarWindowOverrideSource->rva002D55EF();

	if (rva00085124())
		HideControlBar(true);
	else
		ShowControlBar(false);

	if (TheGameSpyGame && m_110 == 5)
		updateBuddyStatus(GAMESPY_BUDDY_STATUS_5, 0,
			WideCharStringToMultiByte(((Rva0022C4DF *)TheGameSpyGame)->rva0022C4DF().str()));

	if (!loadingSaveGame) {
		Drawable *drawable = TheGameClient->getDrawableList();
		while (drawable) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			drawable->rva00278C6B();
			drawable = drawable->getNextDrawable();
		}
	}

	if (TheTacticalView && TheTacticalView->v73())
		TheTacticalView->v74(0, 0, 0, true);

	while ((unsigned)rva0061F090() < 100) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		Sleep(1);
	}
}

// ?rva002469A5@GameLogic@@QAEX_NPAH@Z @0x002469A5 1484B (EH frame, ret 8;
// next body 0x00246F71). Called from the new-game pass 0x00248558 under the
// FP-mode guard with the address of its progress int.
// Target evidence: with GlobalData +0x9C1 set, the "NewMap" export of the
// module at 0x009FE158 is called when present; TheGameInfo's slots mark an
// AI slot (0x003FF127), else modes 0 and 6 drop TheSkirmishGameInfo through
// its virtual destructor and the global operator delete. Progress 1 follows
// with +0xA8 cleared and the frame +0x40 zeroed; the map name goes by value
// to 0x0023E3CE, by reference to TheLuaScriptEngine 0x003387DC, an
// AssetList to bfmeStepReceiverRecord, and to the 0x00240000 stream's
// opener 0x00308050, whose success hands the stream to TheTerrainLogic
// virtual +0x10 (with false and !loadingSaveGame) inside a 1..2 progress
// range (0x00355C8E/0x00355CD8). TheSidesList 0x0032C991 and the by-value
// 0x0023E628 come before progress 2. With TheGameInfo, the live records of
// the indexed team list at TheSidesList+0xF44 whose chain link is set are
// released (0x0032C26D), TheSidesList 0x0032FF91 runs for a multiplayer
// session (TheGameEngine +0x58) or an AI slot, 0x0023EE5B takes the AI flag
// and the progress value and 0x00E03138's reset follows; without it
// 0x00200084 gates 0x0023FED9. Then 0x0023E0C7, TheSidesList 0x0032FD8E
// unless 0x001DCD1C (when +0xF7C is set), TheTeamFactory reset,
// ThePlayerList +0x38, TheScriptEngine 0x00207C02, TheRadar +0x18 and
// TheInGameUI +0x8C5, 0x00E03138 +0x44, and the extent from TheTerrainLogic
// +0x20 sets TheGameLogic's +0x30/+0x34 and is handed to TheShroudManager
// (setRegion, 0x007397D0), ThePartitionManager 0x00625300, 0x009FE750,
// TheDisplay +0x180 and +0x170's 0x0035A2DC (with GlobalData +0xD8);
// TheGhostObjectManager gets the local player index and a reset,
// TheTerrainLogic +0x14 the flag, TheLargeGroupAudio 0x0020D7F9, TheAI's
// +0x10 0x002E8DAA, TheTriggerManager 0x00287015; the bridge pass
// 0x0024622F, TheRadar +0x10, and the map revealed for "ReplayObserver"
// and, per occupied slot, for observers (template -2) permanently or for
// everyone else (0x00739780) unless TheMultiplayerSettings +0x1C.
// Donor: BFME 1 GameLogic.cpp startNewGame (the NewMap debug hook, the
// isSkirmishOrSkirmishReplay scan, TheSkirmishGameInfo cleanup,
// m_startNewGame/m_frame resets, loadMapINI, loadMap, prepareForMP_or_Skirmish,
// TheRadar->newMap, setClientQuiet, the world extent, ghost-manager reset,
// TheTerrainLogic->newMap, the bridge pass and ReplayObserver/observer
// reveals). Callee and field names stay offset names where only the donor
// knows them.
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(void *module, const char *name);

typedef void (*NewMapProc)(void);

class LuaScriptEngine : public SubsystemInterface
{
public:
	void rva003387DC(const AsciiString &mapName);
};

// The map file stream: 0x00240000 builds it, 0x00308050 opens a path and
// 0x0023F4F0 tears it down.
class Rva00240000
{
public:
	Rva00240000(void);
	~Rva00240000(void);
	bool rva00308050(AsciiString path);

private:
	char m_body[0x20];
};

// Progress range (BFME 1 donor Rva00490350ProgressRange): 0x00355C8E builds it
// over the two endpoints, 0x00355CD8 ends it.
class Rva00355CD8
{
public:
	Rva00355CD8(int lo, int hi);
	virtual ~Rva00355CD8(void);

private:
	int m_body[3];
};

class GameEngine
{
public:
	virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
	virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
	virtual void e08(); virtual void e09(); virtual void e0a(); virtual void e0b();
	virtual void e0c(); virtual void e0d(); virtual void e0e(); virtual void e0f();
	virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13();
	virtual void setQuitting(bool quitting);                             // +0x50
	virtual void e15();
	virtual bool isMultiplayerSession(void);                             // +0x58
};

class Rva00E03138 : public SubsystemInterface
{
public:
	virtual void c0b(); virtual void c0c(); virtual void c0d();
	virtual void c0e(); virtual void c0f(); virtual void c10();
	virtual void slot44(void);                                           // +0x44
};

class Display
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d0a(); virtual void d0b();
	virtual void d0c(); virtual void d0d(); virtual void d0e(); virtual void d0f();
	virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
	virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
	virtual void d18(); virtual void d19(); virtual void d1a(); virtual void d1b();
	virtual void d1c(); virtual void d1d(); virtual void d1e(); virtual void d1f();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d2a(); virtual void d2b();
	virtual void d2c(); virtual void d2d(); virtual void d2e(); virtual void d2f();
	virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
	virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
	virtual void d38(); virtual void d39(); virtual void d3a(); virtual void d3b();
	virtual void d3c(); virtual void d3d(); virtual void d3e(); virtual void d3f();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
	virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
	virtual void d48(); virtual void d49(); virtual void d4a(); virtual void d4b();
	virtual void d4c(); virtual void d4d(); virtual void d4e(); virtual void d4f();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
	virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57();
	virtual void d58(); virtual void d59(); virtual void d5a(); virtual void d5b();
	virtual void d5c(); virtual void d5d(); virtual void d5e(); virtual void d5f();
	virtual void slot180(const Region3D *extent);                        // +0x180
};

class Rva0023C6A4
{
public:
	bool rva00200084(void);
};

class Rva0020DXXX
{
public:
	void rva0020D7F9(void);
};

class Rva002872BA : public SubsystemInterface
{
public:
	void rva00287015(void);
};

class Rva00739780
{
public:
	void rva00739780(int playerIndex);
};

extern int g_00DFE158;
extern GameInfo *TheSkirmishGameInfo;
extern LuaScriptEngine *TheLuaScriptEngine;
extern GameEngine *TheGameEngine;
extern Rva00E03138 *g_00E03138;
extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern Rva002872BA *TheTriggerManager;

void bfmeStepReceiverRecord(int source);

void GameLogic::rva002469A5(bool loadingSaveGame, int *progress)
{
	if (TheWritableGlobalData->m_9c1) {
		NewMapProc proc = (NewMapProc)GetProcAddress((void *)g_00DFE158, "NewMap");
		if (proc)
			proc();
	}

	bool isSkirmish = false;
	if (TheGameInfo) {
		for (int i = 0; i < 8; ++i) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			if (TheGameInfo->getSlot(i)->isAI())
				isSkirmish = true;
		}
	} else if (m_110 == 0 || m_110 == 6) {
		if (TheSkirmishGameInfo) {
			::delete TheSkirmishGameInfo;
			TheSkirmishGameInfo = 0;
		}
	}

	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	m_a8 = false;
	((Rva0023C7D2 *)this)->rva0023C7BB(1);
	m_40 = 0;
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	loadMapINI(TheWritableGlobalData->m_mapName);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	TheLuaScriptEngine->rva003387DC(TheWritableGlobalData->m_mapName);
	{
		AssetList assets;
		bfmeStepReceiverRecord((int)&assets);
	}
	{
		Rva00240000 stream;
		if (stream.rva00308050(TheWritableGlobalData->m_mapName)) {
			Rva00355CD8 range(1, 2);
			TheTerrainLogic->loadMap(TheWritableGlobalData->m_mapName, &stream, false, !loadingSaveGame);
		}
	}
	TheSidesList->rva0032C991();
	rva0023E628(TheWritableGlobalData->m_mapName);
	((Rva0023C7D2 *)this)->rva0023C7BB(2);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	if (TheGameInfo) {
		int index = TheSidesList->getTeamInfo()->getNode(0)->m_previous;
		while (index) {
			int next = TheSidesList->getTeamInfo()->getNode(index)->m_previous;
			if (TheSidesList->getTeamInfo()->getNode(index)->m_chainPrevious)
				TheSidesList->getTeamInfo()->bfmeRelease(index);
			index = next;
		}
		if (TheGameEngine->isMultiplayerSession() || isSkirmish)
			TheSidesList->rva0032FF91();
		CreateMPPlayers(isSkirmish, *progress);
		g_00E03138->reset();
	} else if (((Rva0023C6A4 *)this)->rva00200084()) {
		SetUpCampaignPlayers();
	}

	rva0023E0C7();
	if (!rva001DCD1C() && TheSidesList && TheSidesList->m_f7c)
		TheSidesList->rva0032FD8E();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xc);
	TheTeamFactory->reset();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	ThePlayerList->p0e();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xd);
	TheScriptEngine->rva00207C02();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xe);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x10);
	TheRadar->newMap(TheTerrainLogic);
	TheInGameUI->setClientQuiet(false);
	g_00E03138->slot44();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x11);

	Region3D extent;
	TheTerrainLogic->getExtent(&extent);
	TheGameLogic->setWidth(extent.hi.x - extent.lo.x);
	TheGameLogic->setHeight(extent.hi.y - extent.lo.y);
	TheShroudManager->setRegion(&extent, 0.0f);
	((Rva007397D0 *)TheShroudManager)->rva007397D0();
	ThePartitionManager->rva00625300(&extent);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	if (g_Va00DFE750) {
		((Rva006C0810 *)g_Va00DFE750)->rva006C0810(&extent, 0.0f);
		((Rva006C0820 *)g_Va00DFE750)->rva006C0820();
	}
	TheDisplay->slot180(&extent);
	TheGhostObjectManager->setLocalPlayerIndex(ThePlayerList->getLocalPlayer()->getPlayerIndex());
	TheGhostObjectManager->reset();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x12);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	TheTerrainLogic->newMap(loadingSaveGame);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x13);
	((Rva0020DXXX *)TheLargeGroupAudio)->rva0020D7F9();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x14);
	TheAI->pathfinder()->rva002E8DAA();
	TheTriggerManager->rva00287015();
	((Rva0035A2DC *)m_170)->rva0035A2DC(&extent, TheWritableGlobalData->m_d8);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	rva0024622F(loadingSaveGame);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x1e);
	TheRadar->refreshTerrain(TheTerrainLogic);

	TheShroudManager->revealMapForPlayerPermanently(ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey("ReplayObserver"))->getPlayerIndex());
	if (TheGameInfo) {
		for (int i = 0; i < 8; ++i) {
			GameSlot *slot = TheGameInfo->getSlot(i);
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			if (!slot || !slot->isOccupied())
				continue;

			Player *player = ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(slot->m_34));
			if (!player)
				continue;

			if (slot->getPlayerTemplate() == -2)
				TheShroudManager->revealMapForPlayerPermanently(player->getPlayerIndex());
			else if (!TheMultiplayerSettings->isShroudInMultiplayer())
				((Rva00739780 *)TheShroudManager)->rva00739780(player->getPlayerIndex());
		}
	}
}

// ---------------------------------------------------------------------------
// 0x0023E323 (171B): the timed transition reverse. startNewGame's stage
// 0x002423E3 packs a transition group name and a frame into this 8-byte
// value (0x00242731 and 0x00242901, through 0x002419AB), which the
// ref-counted holder 0x0023FC98 (vtable 0x00BEDC94) copies to its +0x08 and
// whose slot 1 (0x0023FCD3) forwards its (float, int) arguments here.
// Target evidence: until TheGameLogic's frame (+0x40) reaches the stored
// frame it answers 1; then, under the handler lock 0x0023C565 (the
// destructor inline: unlock 0x001DBBC8 when TheTransitionHandler is set), it
// clears the handler's byte flag (the folded setter 0x001DBB87), runs the
// handler's slot 10, reverses the named group (0x001DC345) and runs slot
// 10 again; in game modes 2 and 3 (+0x110) it shows the engine cursor and
// answers 3. The answer codes and the unused arguments are not identified.
class Rva001DBB87ZeroSetter
{
public:
	void disable(void);
};

class Rva001DBAA4
{
public:
	void unlock(void);
};

class Rva0023C565
{
public:
	Rva0023C565();
	~Rva0023C565()
	{
		if (TheTransitionHandler)
			((Rva001DBAA4 *)TheTransitionHandler)->unlock();
	}
};

class Rva0023E323
{
public:
	int rva0023E323(float, int);

private:
	AsciiString m_groupName;                                             // +0x00
	unsigned int m_frame;                                                // +0x04
};

int Rva0023E323::rva0023E323(float, int)
{
	int result = 1;
	if (TheGameLogic->getFrame() >= m_frame) {
		{
			Rva0023C565 lock;
			((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
			TheTransitionHandler->slot28();
			TheTransitionHandler->reverse(m_groupName);
			TheTransitionHandler->slot28();
		}

		if (TheGameLogic->m_110 >= 2 && TheGameLogic->m_110 <= 3)
			TheMouse->_bfme_setEngineVisibility(true);
		result = 3;
	}
	return result;
}

// ---------------------------------------------------------------------------
// GameLogic::loadMapINI (0x0023E3CE, 602B). BFME 1 donor GameLogic.cpp: copy the
// map name (or, when TheGameState 0x002DC7C1 places it in the save directory,
// the pristine name at TheGameState +0x2C), strip the file part and load the
// folder's map.ini and solo.ini as overrides and its map.str string file.
// BFME 2 drops the donor's AssetUsage.txt preload.
// ---------------------------------------------------------------------------
class GameState
{
	char m_pad00[0x2c];
public:
	AsciiString m_pristineMapName;                                       // +0x2C
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

class GameTextInterface
{
public:
	virtual void g00(void) = 0;
	virtual void g01(void) = 0;
	virtual void g02(void) = 0;
	virtual void g03(void) = 0;
	virtual void g04(void) = 0;
	virtual void g05(void) = 0;
	virtual void g06(void) = 0;
	virtual void g07(void) = 0;
	virtual void g08(void) = 0;
	virtual void g09(void) = 0;
	virtual void g10(void) = 0;
	virtual void g11(void) = 0;
	virtual void g12(void) = 0;
	virtual void g13(void) = 0;
	virtual void g14(void) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0; // +0x3C
	virtual void g16(void) = 0;
	virtual void g17(void) = 0;
	virtual void g18(void) = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;  // +0x4C
};

extern GameTextInterface *TheGameText;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);

private:
	char m_body[0x87c];
};

extern "C" int (__cdecl * const _imp__sprintf)(char *buffer, const char *format, ...);

void GameLogic::loadMapINI(AsciiString mapName)
{
	if (!TheMapCache)
		return;

	char filename[260];
	char fullFledgeFilename[260];

	memset(filename, 0, 260);
	strcpy(filename, mapName.str());

	if (((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(AsciiString(filename))))
		strcpy(filename, TheGameState->m_pristineMapName.str());

	int length = strlen(filename);
	if (length < 4)
		return;

	char *extension = filename + length - 4;
	while (extension > filename && *extension != '\\' && *extension != '/')
		--extension;
	*extension = 0;

	// One load of the msvcrt sprintf import slot serves all three formats.
	int (__cdecl *format)(char *, const char *, ...) = _imp__sprintf;
	format(fullFledgeFilename, "%s\\map.ini", filename);
	if (TheFileSystem->doesFileExist(fullFledgeFilename)) {
		INI ini;
		ini.loadFile(AsciiString(fullFledgeFilename), INI_LOAD_CREATE_OVERRIDES, 0);
	}

	format(fullFledgeFilename, "%s\\solo.ini", filename);
	if (TheFileSystem->doesFileExist(fullFledgeFilename)) {
		INI ini;
		ini.loadFile(AsciiString(fullFledgeFilename), INI_LOAD_CREATE_OVERRIDES, 0);
	}

	format(fullFledgeFilename, "%s\\map.str", filename);
	if (TheFileSystem->doesFileExist(fullFledgeFilename))
		TheGameText->initMapStringFile(fullFledgeFilename);
}

// ---------------------------------------------------------------------------
// GameLogic 0x0023E628 (396B), called by 0x002469A5 right after the map load:
// the loadMapINI path walk for the folder's ambientlightmap.tga, which
// TheTerrainLogic loads (0x002817F2, which first clears through 0x0027DA58)
// or, when the file is missing, just clears (0x0027DA58).
// ---------------------------------------------------------------------------
class Rva0062AF7
{
public:
	void Rva0027DA58(void);
};

void GameLogic::rva0023E628(AsciiString mapName)
{
	if (!TheMapCache)
		return;

	char filename[260];
	char fullFledgeFilename[260];

	memset(filename, 0, 260);
	strcpy(filename, mapName.str());

	if (((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(AsciiString(filename))))
		strcpy(filename, TheGameState->m_pristineMapName.str());

	int length = strlen(filename);
	if (length < 4)
		return;

	char *extension = filename + length - 4;
	while (extension > filename && *extension != '\\' && *extension != '/')
		--extension;
	*extension = 0;

	_imp__sprintf(fullFledgeFilename, "%s\\ambientlightmap.tga", filename);
	if (TheFileSystem->doesFileExist(fullFledgeFilename))
		TheTerrainLogic->rva002817F2(fullFledgeFilename);
	else
		((Rva0062AF7 *)TheTerrainLogic)->Rva0027DA58();
}

// ---------------------------------------------------------------------------
// GameLogic::SetUpCampaignPlayers (0x0023FED9, 295B; WorldBuilder name and
// statement order). Outside a linear campaign, for the living world's current
// battle (TheLivingWorldLogic +0xB0 region manager, 0x0020E6B7), each map
// side whose playerName matches a battle entry's +4 name gets that entry's
// living-world player id (0x002B6AEC lookup by the entry's +0 name, id at
// +0x14) as livingWorldPlayerID. The entry and list types are not established
// and keep address-derived names.
// ---------------------------------------------------------------------------

class LinearCampaignManager
{
public:
	bool hasCampaign(void) const { return m_campaign != 0; }

private:
	char m_pad00[0x10];
	void *m_campaign;                                                    // +0x10
};

extern LinearCampaignManager *TheLinearCampaignManager;

struct Rva0023FED9Entry
{
	AsciiString m_playerName;
	AsciiString m_sideName;
};

struct Rva0023FED9List
{
	char m_pad00[0x1c];
	Rva0023FED9Entry **m_begin;                                          // +0x1C
	Rva0023FED9Entry **m_end;                                            // +0x20
};

class Rva003F468D
{
public:
	char m_pad00[0x24];
	Rva0023FED9List *m_entries;                                          // +0x24
};

class Rva0020E6B7RegionManager
{
public:
	Rva003F468D *rva0020E6B7(void);
};

class Rva002E2903Player
{
public:
	char m_pad00[0x14];
	int m_id;                                                            // +0x14
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(const AsciiString &name, unsigned int *outIndex);
	Rva002E2903Player *find(int id, unsigned int *outIndex);
	struct Rva002B3740Item *rva002B2B2D(void);
	Rva0020E6B7RegionManager *getRegionManager(void) const { return m_regionManager; }

private:
	char m_pad00[0xb0];
	Rva0020E6B7RegionManager *m_regionManager;                           // +0xB0
};

extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_livingWorldPlayerID;

void GameLogic::SetUpCampaignPlayers(void)
{
	if (TheLinearCampaignManager->hasCampaign())
		return;
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) == 0)
		return;
	Rva0020E6B7RegionManager *regions = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager();
	if (regions == 0)
		return;
	Rva003F468D *battle = regions->rva0020E6B7();
	if (battle == 0)
		return;
	Rva0023FED9List *entries = battle->m_entries;
	if (entries->m_begin == entries->m_end)
		return;
	if (TheSidesList == 0)
		return;
	for (int i = 0; i < TheSidesList->getNumSides(); ++i) {
		SidesInfo *info = TheSidesList->getSideInfo(i);
		if (info) {
			Dict *dict = info->getDict();
			if (dict) {
				AsciiString name = dict->getAsciiString(staticKey(TheKey_playerName));
				Rva0023FED9Entry **it = entries->m_begin;
				Rva0023FED9Entry **end = entries->m_end;
				for (; it != end; ++it) {
					if ((*it)->m_sideName == name) {
						Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find((*it)->m_playerName, 0);
						if (player)
							dict->setInt(((Rva00148F5ECache *)&TheKey_livingWorldPlayerID)->get(), player->m_id);
						break;
					}
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------
// GameLogic 0x0023E0C7 (579B), called by 0x002469A5 after the side setup:
// BFME 1 startNewGame's "always add in an observer Player" block, now its
// own member: the ReplayObserver side (human, "Observer", FactionObserver,
// no allies or enemies, colour 0's day and night colours, start index 0,
// not local) and its singleton teamReplayObserver, then 0x0032E02B on
// TheSidesList where BFME 1 calls validateSides.
// ---------------------------------------------------------------------------
class PlayerTemplate
{
public:
	NameKeyType getNameKey(void) const { return m_nameKey; }
	int rva001FD234() const;
	AsciiString getName() const;
	bool isPlayableSide() const { return m_playableSide; }

private:
	char m_pad00[0x10];
	NameKeyType m_nameKey;                                               // +0x10
	char m_pad14[0x151 - 0x14];
	bool m_playableSide;                                                 // +0x151
};

class MultiplayerColorDefinition
{
public:
	int getColor(void) const { return m_color; }
	int getNightColor(void) const { return m_colorNight; }

private:
	char m_pad00[0x10];
	int m_color;                                                         // +0x10
	char m_pad14[0x20 - 0x14];
	int m_colorNight;                                                    // +0x20
};

extern Rva00148F5ECache TheKey_playerIsHuman;
extern Rva00148F5ECache TheKey_playerDisplayName;
extern Rva00148F5ECache TheKey_playerFaction;
extern Rva00148F5ECache TheKey_playerAllies;
extern Rva00148F5ECache TheKey_playerEnemies;
extern Rva00148F5ECache TheKey_playerColor;
extern Rva00148F5ECache TheKey_playerNightColor;
extern Rva00148F5ECache TheKey_multiplayerStartIndex;
extern Rva00148F5ECache TheKey_multiplayerIsLocal;
extern Rva00148F5ECache TheKey_teamName;
extern Rva00148F5ECache TheKey_teamOwner;
extern Rva00148F5ECache TheKey_teamIsSingleton;

// An inline key read is evaluated before a sibling argument's call; a direct
// get() keeps MSVC's right-to-left argument order.
static __forceinline NameKeyType cacheKey(Rva00148F5ECache &key)
{
	return key.get();
}

void GameLogic::rva0023E0C7(void)
{
	Dict d;
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get(), "ReplayObserver");
	d.setBool(TheKey_playerIsHuman.get(), true);
	d.setUnicodeString(TheKey_playerDisplayName.get(), UnicodeString(L"Observer"));
	const PlayerTemplate *pt;
	pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
	if (pt)
		d.setAsciiString(cacheKey(TheKey_playerFaction), TheNameKeyGenerator->keyToName(pt->getNameKey()));
	d.setAsciiString(TheKey_playerAllies.get(), AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerEnemies.get(), AsciiString::TheEmptyString);
	d.setInt(TheKey_playerColor.get(), TheMultiplayerSettings->getColor(0)->getColor());
	d.setInt(TheKey_playerNightColor.get(), TheMultiplayerSettings->getColor(0)->getNightColor());
	d.setInt(TheKey_multiplayerStartIndex.get(), 0);
	d.setBool(TheKey_multiplayerIsLocal.get(), false);

	TheSidesList->addSide(&d);
	d.clear();
	d.setAsciiString(TheKey_teamName.get(), "teamReplayObserver");
	d.setAsciiString(TheKey_teamOwner.get(), "ReplayObserver");
	d.setBool(TheKey_teamIsSingleton.get(), true);
	TheSidesList->addTeam(&d);
	TheSidesList->rva0032E02B();
}

// ---------------------------------------------------------------------------
// ?CreateMPPlayers@GameLogic@@QAEX_NH@Z @0x0023EE5B 1685B (ret 8; called from
// rva002469A5 with the skirmish flag and the progress base).
// BFME 1 / Zero Hour startNewGame's slot-to-side pass, now its own member:
// first every occupied slot is given its side name (Observer_N for an
// observer template, Player_<start+1> in game mode 3, otherwise Player_1 for
// the living-world player the 0x002B2B2D entry's +0x13C names and Player_N+2
// for the rest), then each slot becomes a side Dict (name, human, display
// name, faction, preorder, allies and enemies by team, slot +0x20, day and
// night colours, start index, local flag, the GameInfo +0x54 value, the
// AI-type reset when the start position's byte +2 is clear, skirmish flag
// and difficulty from the slot state, living-world id) and a singleton
// "team<name>" team. Every slot name goes into PlyrCreeps' enemy list when
// the map has that side, and PlyrCreeps lands in each player's enemies.
// Key names follow BFME 1's WellKnownKeys order; the slot +0x20 and
// GameInfo +0x54 keys are structural guesses.
// ---------------------------------------------------------------------------
struct Rva002B3740Item
{
	char m_pad000[0x13c];
	int m_13c;                                                           // +0x13C
};

extern Rva00148F5ECache TheKey_playerIsSkirmish;
extern Rva00148F5ECache TheKey_playerSlot20;
extern Rva00148F5ECache TheKey_playerStartMoney;
extern Rva00148F5ECache TheKey_skirmishDifficulty;
extern Rva00148F5ECache TheKey_playerIsPreorder;
extern Rva00148F5ECache TheKey_playerAIType;

void GameLogic::CreateMPPlayers(bool isSkirmish, int progressCount)
{
	if (!TheGameInfo)
		return;
	GameInfo *game = TheGameInfo;

	int i;
	for (i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied())
			continue;

		AsciiString playerName;
		if (slot->getPlayerTemplate() >= 0)
		{
			if (m_114 != 3)
			{
				int playerID = slot->m_livingWorldPlayerID;
				Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(playerID, 0);
				Rva002B3740Item *item = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B2B2D();
				if (player && item)
				{
					if (item->m_13c == player->m_id)
						playerName.set("Player_1");
					else
						playerName.format("Player_%d", i + 2);
				}
			}
			else
				playerName.format("Player_%d", slot->getStartPos() + 1);
		}
		else
			playerName.format("Observer_%d", i + 1);
		slot->m_34 = playerName;
	}

	AsciiString creepsName("PlyrCreeps");
	AsciiString creepsEnemies;
	bool hasCreeps = TheSidesList->findSideInfo(creepsName) != 0;

	for (i = 0; i < 8; ++i)
	{
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();

		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isHuman())
		{
			m_128[i] = true;
			lastHeardFrom(i);
		}
		if (!slot || !slot->isOccupied())
			continue;

		Dict d;
		d.clear();
		const AsciiString &name = slot->m_34;
		creepsEnemies.concat(" ");
		creepsEnemies.concat(name);
		d.setAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get(), name);
		d.setBool(cacheKey(TheKey_playerIsHuman), slot->isHuman());
		d.setUnicodeString(TheKey_playerDisplayName.get(), slot->m_name);

		const PlayerTemplate *pt;
		if (slot->getPlayerTemplate() >= 0)
			pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate());
		else
			pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
		if (pt)
			d.setAsciiString(cacheKey(TheKey_playerFaction), TheNameKeyGenerator->keyToName(pt->getNameKey()));

		if (game->isPlayerPreorder(i))
			d.setBool(TheKey_playerIsPreorder.get(), true);

		AsciiString enemiesString;
		AsciiString alliesString;
		int team = slot->getTeamNumber();
		for (int j = 0; j < 8; ++j)
		{
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();

			GameSlot *teamSlot = game->getSlot(j);
			if (i == j || !teamSlot->isOccupied())
				continue;

			const AsciiString &teamPlayer = teamSlot->m_34;
			bool isEnemy = team == -1 || teamSlot->getTeamNumber() != team;
			if (isEnemy)
			{
				if (!enemiesString.isEmpty())
					enemiesString.concat(" ");
				enemiesString.concat(teamPlayer);
			}
			else
			{
				if (!alliesString.isEmpty())
					alliesString.concat(" ");
				alliesString.concat(teamPlayer);
			}
		}

		if (hasCreeps)
		{
			enemiesString.concat(" ");
			enemiesString.concat(creepsName);
		}

		d.setAsciiString(TheKey_playerAllies.get(), alliesString);
		d.setAsciiString(TheKey_playerEnemies.get(), enemiesString);
		d.setInt(TheKey_playerSlot20.get(), slot->m_bfme20);
		d.setInt(TheKey_playerColor.get(), TheMultiplayerSettings->getColor(slot->getColor())->getColor());
		d.setInt(TheKey_playerNightColor.get(), TheMultiplayerSettings->getColor(slot->getColor())->getNightColor());
		d.setInt(TheKey_multiplayerStartIndex.get(), slot->getStartPos());
		d.setBool(TheKey_multiplayerIsLocal.get(), slot->isHuman() &&
			slot->m_name.compare(game->getSlot(game->getLocalSlotNum())->getNameStr()) == 0);

		if (game->m_54 >= 0)
			d.setInt(TheKey_playerStartMoney.get(), game->m_54);

		int startPos = slot->getStartPos();
		if (startPos >= 0 && startPos < 8)
		{
			const MapMetaData *md = TheMapCache->findMap(game->getMap());
			if (md)
			{
				const MapStartPosition *pos = &md->m_startPositions[startPos];
				if (!pos->m_2)
					d.setAsciiString(TheKey_playerAIType.get(), AsciiString::TheEmptyString);
			}
		}

		if (isSkirmish)
		{
			d.setBool(TheKey_playerIsSkirmish.get(), true);
			switch (slot->m_state)
			{
			case 2: d.setInt(TheKey_skirmishDifficulty.get(), 0); break;
			case 3: d.setInt(TheKey_skirmishDifficulty.get(), 1); break;
			case 4: d.setInt(TheKey_skirmishDifficulty.get(), 2); break;
			case 5: d.setInt(TheKey_skirmishDifficulty.get(), 3); break;
			}
		}

		d.setInt(((Rva00148F5ECache *)&TheKey_livingWorldPlayerID)->get(), slot->m_livingWorldPlayerID);

		TheSidesList->findSideInfo(name);
		TheSidesList->addSide(&d);

		AsciiString teamName;
		teamName = "team";
		teamName.concat(name);
		d.clear();
		d.setAsciiString(TheKey_teamName.get(), teamName);
		d.setAsciiString(TheKey_teamOwner.get(), name);
		d.setBool(TheKey_teamIsSingleton.get(), true);
		TheSidesList->addTeam(&d);

		((Rva0023C7D2 *)this)->rva0023C7BB(progressCount + i);
	}

	if (hasCreeps)
	{
		SidesInfo *creeps = TheSidesList->findSideInfo(creepsName);
		creeps->getDict()->setAsciiString(TheKey_playerAllies.get(), AsciiString(""));
		creeps->getDict()->setAsciiString(TheKey_playerEnemies.get(), creepsEnemies);
	}
}

// ---------------------------------------------------------------------------
// populateRandomSideAndColor @0x002444BE 926B (ret at 0x0024485B; next body
// populateRandomStartPosition). Target evidence: the GameLogic.cpp __FILE__
// literal with lines 1923/1988/2011, GetGameLogicRandomSeed() % 7 discards,
// GameInfo::getSlot/isOccupied/setPlayerTemplate/isColorTaken and
// MapCache::findMap(getMap()). Donor: BFME 1 GameLogic.cpp
// populateRandomSideAndColor (same slot walk, the start position's faction
// set, the color pick). BFME 2 differs: the playable byte is
// PlayerTemplate+0x151, a second vector keeps each template's 0x001FD234
// value (7 without a template), the side pool is a copy narrowed in place
// (swap) by the faction set and then by the slot's hero faction mask
// (CreateAHeroManager::GetFactionMaskType on the hero record when it is set),
// and the observer/out-of-range fallback is gone. The vector helpers are ICF
// folds shared with other element types; the address-named allocator and
// the enum below only give those folded instantiations a placeholder name.
// ---------------------------------------------------------------------------
template <class T> class Rva002444BEAllocator : public _STL::allocator<T>
{
};
typedef _STL::vector<int, Rva002444BEAllocator<int> > Rva002444BEIndexVector;

enum Rva002444BEFaction
{
	RVA002444BE_FACTION_NONE = 7
};

unsigned int GetGameLogicRandomSeed(void);

class CreateAHeroManager
{
public:
	void *GetFactionMaskType(unsigned int classIndex, unsigned int subClassIndex);
};

void populateRandomSideAndColor(GameInfo *game)
{
	if (!game)
		return;
	int i;

	Rva002444BEIndexVector startSlots;
	_STL::vector<Rva002444BEFaction> templateFactions;
	for (i = 0; i < ThePlayerTemplateStore->getPlayerTemplateCount(); ++i)
	{
		const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(i);
		templateFactions.push_back((Rva002444BEFaction)(pt ? pt->rva001FD234() : RVA002444BE_FACTION_NONE));
		if (pt && pt->isPlayableSide())
			startSlots.push_back(i);
	}

	for (i = 0; i < 8; ++i)
	{
		GameSlot *slot = game->getSlot(i);
		if (!slot || !slot->isOccupied())
			continue;

		int playerTemplateIdx = slot->getPlayerTemplate();
		while (playerTemplateIdx != -2 && (playerTemplateIdx < 0 || playerTemplateIdx >= ThePlayerTemplateStore->getPlayerTemplateCount()))
		{
			unsigned int silly = GetGameLogicRandomSeed() % 7;
			for (int poo = 0; poo < silly; ++poo)
				GetGameLogicRandomValue(0, 1, GAMELOGIC_SOURCE_FILE, 1923);

			Rva002444BEIndexVector candidates(startSlots);
			const MapMetaData *md = TheMapCache->findMap(game->getMap());
			if (md)
			{
				const MapStartPosition &position = md->m_startPositions[slot->getStartPos()];
				const _STL::set<AsciiString> &factions = position.m_factions;
				if (factions.size() != 0)
				{
					Rva002444BEIndexVector possible;
					for (Rva002444BEIndexVector::iterator it = candidates.begin(); it != candidates.end(); ++it)
					{
						int idx = *it;
						AsciiString name = ThePlayerTemplateStore->getNthPlayerTemplate(idx)->getName();
						if (factions.find(name) != factions.end())
							possible.push_back(idx);
					}
					candidates.swap(possible);
				}
			}

			const GameSlotHeroInfo *hero = slot->getHero();
			if (hero)
			{
				unsigned int classIndex = hero->m_classIndex;
				const unsigned int *mask = (const unsigned int *)((CreateAHeroManager *)TheHeroManager)->GetFactionMaskType(classIndex, hero->m_subClassIndex);
				Rva002444BEIndexVector allowed;
				for (Rva002444BEIndexVector::iterator it = candidates.begin(); it != candidates.end(); ++it)
				{
					int idx = *it;
					unsigned int faction = templateFactions[idx];
					if (mask[faction >> 5] & (1 << (faction & 31)))
						allowed.push_back(idx);
				}
				candidates.swap(allowed);
			}

			unsigned int count = candidates.size();
			int *pool = candidates.begin();
			playerTemplateIdx = pool[GetGameLogicRandomValue(0, 1000, GAMELOGIC_SOURCE_FILE, 1988) % count];
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(playerTemplateIdx);
			if (pt && pt->isPlayableSide())
				slot->setPlayerTemplate(playerTemplateIdx);
			else
				playerTemplateIdx = -1;
		}

		int colorIdx = slot->getColor();
		if (colorIdx < 0 || colorIdx >= TheMultiplayerSettings->getNumColors())
		{
			while (colorIdx == -1)
			{
				colorIdx = GetGameLogicRandomValue(0, TheMultiplayerSettings->getNumColors() - 1, GAMELOGIC_SOURCE_FILE, 2011);
				if (game->isColorTaken(colorIdx))
					colorIdx = -1;
			}
			slot->setColor(colorIdx);
		}
	}
}

// ?ProcessCRC@GameLogic@@QAEXIHIPAVGameMessage@@_NPAVBfmeThingEC@@@Z
// @0x00241529 948B (Ghidra FUN_00641529, ret 0x18 at 0x002418DA). Callers:
// 0x002458E3, 0x0037AA44 and 0x0037D0E4; all six argument slots are read.
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicPeerCRC.cpp
// (bfme_processLogicCRC, BFME 1 0x0038B430 1078B): per-frame CRC reports kept
// as a frame-sorted singly linked list of 0x18-byte records at this+0x48, a
// player bitmask and count per record, and a window of diagnostic streams
// (list at this+0x50, cursor at this+0x4C) trimmed to the GlobalData field at
// +0xC18 plus three. Target deltas from the donor: the record list, cursor and
// stream list sit 4 bytes later, the desync message is 0x44A and carries two
// timestamps (this+0x38 and this+0x40), and the Network slots are +0x3C,
// +0x94, +0xAC and +0xB4. Record field names come from the donor.
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendTimestampArgument(unsigned int arg);
	void appendBooleanArgument(bool arg);
	GameMessage *next(void) const { return m_next; }

private:
	void *m_vtbl;
	GameMessage *m_next;                                                 // +0x04
};

// MessageStreamSubsystem (0x00A00950); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17();
	virtual GameMessage *appendMessage(int type);                        // +0x48
	void propagateMessages(void);
};
extern MessageStream *MessageStreamSubsystem;

// The diagnostic stream: 0x006021A4 hands back its buffer and its size; the
// desync reporter names its file after the string at +4.
class BfmeThingEC
{
public:
	virtual void e00(void);
	int bfmeTakeEC(int *size);

	AsciiString m_04;
};

struct Rva00241529Record
{
	unsigned int frame;
	unsigned int crc;
	int count;
	unsigned int mask;
	BfmeThingEC *stream;
	Rva00241529Record *next;
};

// 0x009C116C: -1 unless a desync frame was forced from the command line.
extern int g_value12A6F38;
// 0x00A02D8A: keep playing after a CRC mismatch was logged.
extern bool ignoreCRCMismatches;

void GameLogic::ProcessCRC(unsigned int crc, int player, unsigned int frame, GameMessage *message,
	bool forced, BfmeThingEC *stream)
{
	Rva00241529Record *entry = m_48;
	Rva00241529Record *previous = 0;
	while (entry && frame > entry->frame)
	{
		previous = entry;
		entry = entry->next;
	}
	if (!forced && g_value12A6F38 != m_40 && (!entry || frame != entry->frame))
	{
		if (message)
			message->appendBooleanArgument(false);
		entry = new Rva00241529Record;
		if (!entry)
			return;
		entry->frame = frame;
		entry->crc = crc;
		entry->stream = 0;
		if (stream)
		{
			entry->stream = stream;
			entry->count = 0;
			entry->mask = 0;
			m_50.push_back((const int &)entry->stream);
			if (m_50.size() > TheWritableGlobalData->m_c18 + 3)
			{
				m_4c = m_50.begin();
				BfmeThingEC *oldStream = (BfmeThingEC *)*m_4c;
				if (oldStream)
				{
					int size;
					free((void *)oldStream->bfmeTakeEC(&size));
				}
				m_50.pop_front();
			}
		}
		else
		{
			entry->count = 1;
			entry->mask = 1 << player;
		}
		if (!previous)
		{
			entry->next = m_48;
			m_48 = entry;
		}
		else
		{
			entry->next = previous->next;
			previous->next = entry;
		}
		return;
	}
	bool fake = g_value12A6F38 != -1 && g_value12A6F38 != m_40;
	if (forced || g_value12A6F38 == m_40 || (!fake && crc != entry->crc && !TheGameLogic->m_71))
	{
		rva0023F8DA();
		if (!ignoreCRCMismatches || g_value12A6F38 == m_40)
		{
			m_4c = m_50.begin();
			if (m_4c != m_50.end())
			{
				if (TheNetwork)
				{
					if (!m_71 && (!forced || TheNetwork->slotAC()))
					{
						if (TheNetwork->slotAC() && forced)
						{
							GameMessage *out = MessageStreamSubsystem->appendMessage(0x44a);
							out->appendIntegerArgument(crc);
							out->appendTimestampArgument(m_38);
							out->appendTimestampArgument(m_40);
							out->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
							out->appendBooleanArgument(true);
						}
						else if (message && !forced)
							message->appendBooleanArgument(true);
					}
					MessageStreamSubsystem->propagateMessages();
					if (TheNetwork)
						TheNetwork->slot3C(0);
				}
				for (; m_4c != m_50.end(); ++m_4c)
				{
					rva002401DD((BfmeThingEC *)*m_4c, frame, player);
					if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK)
					{
						GameMessage *out = MessageStreamSubsystem->appendMessage(0x44a);
						out->appendIntegerArgument(crc);
						out->appendTimestampArgument(m_38);
						out->appendTimestampArgument(m_40);
						out->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
						out->appendBooleanArgument(true);
						MessageStreamSubsystem->propagateMessages();
						if (TheNetwork)
							TheNetwork->slot3C(0);
					}
				}
				m_50.clear();
				if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK)
					if (TheNetwork)
						TheNetwork->slot94();
			}
			else
				rva002401DD(entry->stream, 0, player);
			return;
		}
	}
	if (message && !forced)
		message->appendBooleanArgument(false);
	if (!(entry->mask & (1 << player)))
	{
		++entry->count;
		entry->mask |= (1 << player);
	}
	if (TheRecorder && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK)
	{
		if (entry->count == TheRecorder->m_e68)
		{
			if (previous)
				previous->next = entry->next;
			else
				m_48 = entry->next;
			delete entry;
		}
	}
	else if (entry->count == TheNetwork->slotB4())
	{
		if (previous)
			previous->next = entry->next;
		else
			m_48 = entry->next;
		delete entry;
	}
}

// ?rva0023F8DA@GameLogic@@QAEXXZ @0x0023F8DA 484B (Ghidra FUN_0063f8da, ret at
// 0x0023FABD). Called by the CRC vote above (0x00241671) and 0x00377A14.
// Donor: BFME 1 bfme_appendGameOverDetails (b1 0x00387A50, banked 0.99 in
// Open-BFME-1 attempt history): once per game, append a "Game Over Details"
// block to the last line of the string vector at this+0x58, one line per
// slot from its PlayerLeaveStatus. Target deltas: the vector and its done flag
// (+0x6C) sit 4 bytes later, the leave-status accessor is out of line
// (0x0023D1E3), the player template pointer is Player+0x34, the address check
// is Player+0x3BC and the quit frame is stored at Player+0x4AC.
struct PlayerLeaveStatus
{
	int m_status;
	int m_quitFrame;
	int m_defeatFrame;
	int m_victoryFrame;
	bool m_notPresent;
	unsigned char m_unknown11[3];
	int m_isHuman;
	AsciiString m_playerName;
};

// Inside the 0x009FE7A8 data block: the last formatted player template name.
extern char g_Va00DFE840[];
extern "C" __declspec(dllimport) __declspec(nothrow) int __cdecl sprintf(char *buffer, const char *format, ...);

void GameLogic::rva0023F8DA(void)
{
	if (m_6c || m_58.size() == 0)
		return;
	AsciiString *last = &m_58[m_58.size() - 1];
	if (!last)
		return;
	m_6c = true;
	AsciiString line;
	*last += "    Game Over Details:\n";
	for (int i = 0; i < 8; ++i)
	{
		PlayerLeaveStatus *info = getPlayerLeaveStatus(i);
		if (info)
		{
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player && &player->m_3bc && player->m_34)
			{
				sprintf(g_Va00DFE840, "%s", player->m_34->getName().str());
				player->m_4ac = info->m_quitFrame;
			}
			AsciiString reason;
			switch (info->m_status)
			{
				case 0: reason.format("n/a"); break;
				case 1: reason.format("graceful"); break;
				case 2: reason.format("voted out"); break;
				default: reason.format("unknown"); break;
			}
			if (info->m_victoryFrame)
				line.format("      Slot %d: Victory frame: %d, Quit frame: %d(%s)\n", i, info->m_victoryFrame, info->m_quitFrame, reason.str());
			else if (info->m_defeatFrame)
				line.format("      Slot %d: Defeat frame: %d, Quit frame: %d(%s)\n", i, info->m_defeatFrame, info->m_quitFrame, reason.str());
			else if (info->m_notPresent)
				line.format("      Slot %d: n/a\n", i);
			else
				line.format("      Slot %d: Present at final frame\n", i);
		}
		else
			line.format("      Slot %d: PlayerLeaveStatus does not exist.\n", i);
		*last += line;
	}
}

// ?rva0023FB58@GameLogic@@QAEABVAsciiString@@H@Z @0x0023FB58 104B (Ghidra
// FUN_0063fb58). Indexed read of the string vector at this+0x58 with a
// function-local "Invalid Slot" fallback (object 0x009FE940, guard bit
// 0x009FE944); the desync reporter 0x002401DD reads every entry through it.
const AsciiString &GameLogic::rva0023FB58(int index)
{
	if (index >= 0 && index < m_58.size())
		return m_58[index];
	static AsciiString invalid("Invalid Slot");
	return invalid;
}

// The update modules GameLogic keeps per phase (vector<UpdateModule *> at
// this+0xC8, four of them, and the sleeping list at +0xF8): BehaviorModule
// is 0x10 bytes with the object at +8, the UpdateModuleInterface vptr sits
// at +0x10 (update, getDisabledTypesToProcess), then the wake frame, the
// index in its list and the phase (-1 when sleeping).
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update(void) = 0;
	virtual DisabledMaskType getDisabledTypesToProcess(void) const = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule(void);
	Object *getObject(void) const { return m_object; }

private:
	const void *m_moduleData;
	Object *m_object;                                                    // +0x08
	void *m_vtbl0C;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	unsigned int getWakeFrame(void) const { return m_nextCallFrame; }
	void setWakeFrame(unsigned int frame)
	{
		if (frame > UPDATE_SLEEP_FOREVER)
			frame = UPDATE_SLEEP_FOREVER;
		m_nextCallFrame = frame;
	}
	void setIndexInLogic(int index, int phase)
	{
		m_phase = phase;
		m_indexInLogic = index;
	}
	void setIndexInLogic(int index)
	{
		m_phase = -1;
		m_indexInLogic = index;
	}

private:
	unsigned int m_nextCallFrame;                                        // +0x14
	int m_indexInLogic;                                                  // +0x18
	int m_phase;                                                         // +0x1C
};

// ZH LatchRestore: restores the latched value when the scope ends.
template <class T>
class LatchRestore
{
public:
	LatchRestore(T &dest, const T &src) : m_whereToRestore(dest)
	{
		m_valueToRestore = dest;
		dest = src;
	}
	virtual ~LatchRestore(void) { m_whereToRestore = m_valueToRestore; }

protected:
	T m_valueToRestore;
	T &m_whereToRestore;
};

class CommandList : public SubsystemInterface
{
public:
	virtual void c0b(); virtual void c0c(); virtual void c0d();
	virtual void c0e(); virtual void c0f(); virtual void c10();
	virtual bool containsMessageOfType(int type);                        // +0x44
	GameMessage *getFirstMessage(void) const { return m_firstMessage; }

private:
	GameMessage *m_firstMessage;                                         // +0x0C
};

class Rva00DFE1C8Host
{
public:
	bool rva00210DC9(void);
};

class Rva002431CB
{
public:
	void rva002431CB(void);
};

class Rva002CEC0A
{
public:
	void rva002CEC34(void);
};

class Rva002747F9
{
public:
	void rva002747F9(int mode);
};

class Rva00238FF3Arg;

class Rva00238E1B
{
public:
	void rva00238FF3(Rva00238FF3Arg *xfer);
};

class XferSave
{
public:
	XferSave(void);
	virtual ~XferSave(void);
	unsigned char Open(Xfer *file, int mode, bool flag);
	void close(void);

private:
	char m_body[0x3c];
};

class CopyProtect
{
public:
	static bool rva00232D38(void);
};

class StatsCollectorUpdate
{
public:
	void rva00437BB6(void);
};

class GlobalWeatherSystem : public SubsystemInterface
{
};

class WeaponStore : public SubsystemInterface
{
};

class LocomotorStore : public SubsystemInterface
{
};

class Rva00A027B8 : public SubsystemInterface
{
};

// 0x00A03144: GameEngine::init registers it as
// "TheDelayedExperienceLevelGrantSystem" (site 0x0022F1A4).
class DelayedExperienceLevelGrantSystem : public SubsystemInterface
{
};

class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *text);
void Rva00225A0C(int msec);

extern CommandList *TheCommandList;
extern Rva00DFE1C8Host *g_00DFE1C8;
extern bool TheDeepCRC;
extern bool TheLiteCRC;
extern void *g_00DFEFF0;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
extern Rva00A027B8 *g_00A027B8;
extern WeaponStore *TheWeaponStore;
extern LocomotorStore *TheLocomotorStore;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;
extern void *g_Va00E01EDC;
extern "C" int (__cdecl * const _imp___unlink)(const char *path);

// ?update@GameLogic@@UAEXH@Z @0x0024555A 2437B (vslot +0x34; ret 4 at
// 0x00245EDC). One frame phase of the logic: phase 1 runs the script,
// recorder, CRC and command-list work, phase 2 the partition and collision
// managers and each object's per-frame hook, phases 3..6 the update-module
// lists (3/4 split list 0 in halves, 5 runs lists 1..2, 6 list 3), and
// phase 5 the remaining subsystems. Donor: BFME 1 GameLogic::update
// (0x0038DA10) for the phase layout, module sleep handling, CRC message and
// latch; BFME 2 adds the FP-mode scope guard, the frame-advance predicate
// 0x002259F3 at the top, more subsystems and the scenecapture.dat dump.
// Codegen evidence: retail multiplies by constants with imul (`m_40 * 10`
// at 0x00245D38, the 12-byte list stride at 0x00245A3C), which this
// compiler emits only under /G7, hence the TU flag. The CRC block and the
// module wake add read the frame through the inline getFrame(); with the
// raw field the allocator caches zero in edi from 0x002458FD on and moves
// every later register. The module loop tests `i + 1` and lets the
// optimizer keep the incremented copy at [ebp-0x24], stored after the
// entry test as at 0x00245A6F.
void GameLogic::update(int phase)
{
	Rva0004224C fpModeGuard;

	if (phase == 1) {
		TheScriptEngine->rva002047CF();
		bool freeze = (TheTacticalView->slotD8() && !TheTacticalView->slot78())
			|| ((Rva00203B08 *)TheScriptEngine)->rva00203AE5();
		if (TheNetwork)
			TheNetwork->slotAC();
		if (rva002259F3() && !freeze)
			++m_40;
		if (freeze) {
			if (TheCommandList->containsMessageOfType(0x1d))
				TheScriptEngine->forceAppContinue();
			else {
				TheGameClient->m_c8 = false;
				return;
			}
		}
	}

	m_164.clear();

	if (m_125 && !isInMultiplayerGame()) {
		if (phase == 1) {
			processCommandList();
			TheGameClient->m_c8 = true;
		}
		m_17c = phase;
		return;
	}

	m_17c = phase;
	bool first = (phase == 1);
	LatchRestore<bool> inUpdate(m_70, true);

	if (*(bool *)&g_Va00DFE7A8 && first)
		((Rva002431CB *)&g_Va00DFE7A8)->rva002431CB();

	if (first && getFrame() == 2 && g_00DFE1C8->rva00210DC9()
		&& ((Rva0023C666 *)TheGameLogic)->rva0023C666()) {
		for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai && ai->isMoving())
				ai->destroyPath();
		}
	}

	TheAI->pathfinder()->rva002F0F07();
	setFPMode();

	if (first) {
		TheScriptEngine->update();
		TheLuaScriptEngine->update();
		TheTerrainLogic->update();
		if (TheVictorySystem)
			((SubsystemInterface *)TheVictorySystem)->update();
	}

	if (rva0042219() && TheRecorder && first) {
		bool generate = false;
		if (TheRecorder->isMultiplayer()) {
			unsigned int interval = TheGameInfo->m_0c;
			generate = (getFrame() % interval) == 0;
			if (m_110 == 2)
				generate = false;
		}
		if (g_value12A6F38 != -1)
			generate = getFrame() >= g_value12A6F38 - TheWritableGlobalData->m_c18 - 2
				&& getFrame() <= (unsigned int)g_value12A6F38;
		if (generate) {
			int player = ThePlayerList->getLocalPlayer()->getPlayerIndex();
			BfmeThingEC *stream = 0;

			unsigned int crc;
			if (TheDeepCRC) {
				AsciiString name;
				name.format("%d", getFrame());
				stream = (BfmeThingEC *)bfmeMake_009CB5F0((void *)name.str());
				Profile::StartRange("crc");
				crc = getCRC((int)stream);
				Profile::StopRange("crc");
			} else {
				TheLiteCRC = true;
				crc = getCRC(0);
				TheLiteCRC = false;
			}
			GameMessage *msg = MessageStreamSubsystem->appendMessage(0x44a);
			msg->appendIntegerArgument(crc);
			msg->appendTimestampArgument(m_38);
			msg->appendTimestampArgument(getFrame());
			msg->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
			if (!TheDeepCRC && !TheLiteCRC)
				msg->appendBooleanArgument(false);
			else
				ProcessCRC(crc, player, m_40, msg, false, stream);
		}
		if (g_00DFEFF0)
			((Rva002CEC0A *)g_00DFEFF0)->rva002CEC34();
	}

	if (g_00E032F8 && first)
		((StatsCollectorUpdate *)g_00E032F8)->rva00437BB6();

	if (first) {
		TheRecorder->update();
		TheTriggerManager->update();
		TheGlobalWeatherSystem->update();
		((DOTManager *)m_174)->update();
		m_178->rva00439965();
		for (GameMessage *msg = TheCommandList->getFirstMessage(); msg; msg = msg->next())
			logicMessageDispatcher(msg, 0);
		TheCommandList->reset();
		for (Object *obj = m_objList; obj; obj = obj->getNextObject()) {
			if (obj->getDrawable())
				((Rva002747F9 *)obj->getDrawable())->rva002747F9(0);
		}
	}

	if (phase == 2) {
		ThePartitionManager->update();
		TheCollisionManager->update();
		for (Object *obj = m_objList; obj; obj = obj->getNextObject()) {
			unsigned int last = obj->m_188;
			if (last != m_40)

				obj->rva0023D3AF((void *)m_40);
		}
	}

	if (phase > 2) {
		int start = 0;
		int end = 0;
		switch (phase) {
		case 3:
		case 4:
			start = 0;
			end = 1;
			break;
		case 5:
			start = 1;
			end = 3;
			break;
		case 6:
			start = 3;
			end = 4;
			break;
		}
		for (int p = start; p < end; ++p) {
			int i = phase == 4 ? m_updates[p].size() / 2 - 1 : -1;
			while (i + 1 < m_updates[p].size()) {
				++i;
				if (phase == 3 && i == m_updates[p].size() / 2)
					break;
				UpdateModule *u = m_updates[p][i];
				if (!u || u->getWakeFrame() > TheGameLogic->getFrame())
					continue;
				UpdateSleepTime sleep = UPDATE_SLEEP_NONE;
				const DisabledMaskType &dis = u->getObject()->getDisabledFlags();
				if (!dis.any() || dis.anyIntersectionWith(u->getDisabledTypesToProcess())) {
					m_104 = u;
					if (u->getObject()->m_94 & 1)
						sleep = UPDATE_SLEEP_FOREVER;
					else {
						sleep = u->update();
						if (sleep < UPDATE_SLEEP_NONE)
							sleep = UPDATE_SLEEP_NONE;
					}
					m_104 = 0;
				}
				u->setWakeFrame(TheGameLogic->getFrame() + sleep);
			}
			if (phase > 3) {
				for (unsigned int j = m_updates[p].size(); j > 0;) {
					UpdateModule *u = m_updates[p][--j];
					if (u && u->getWakeFrame() >= UPDATE_SLEEP_FOREVER) {
						if (j < m_updates[p].size() - 1) {
							m_updates[p][j] = m_updates[p].back();
							m_updates[p][j]->setIndexInLogic(j, p);
						}
						m_updates[p].pop_back();
						u->setIndexInLogic(m_sleeping.size());
						m_sleeping.push_back(u);
					}
				}
			}
		}
	}

	if (phase == 5)
		TheAI->update();

	rva00240EBC();

	if (phase == 5) {
		TheShroudManager->update();
		((SubsystemInterface *)g_Va00DFE750)->update();
		g_00A027B8->update();
		TheLargeGroupAudio->update();
		processDestroyList();
		TheWeaponStore->update();
		TheLocomotorStore->update();
		g_00E03138->update();
		TheDelayedExperienceLevelGrantSystem->update();
		m_184.rva0040CA98();
		g_00DFEEF8->update();
		((SubsystemInterface *)g_Va00E01EDC)->update();
		TheTeamFactory->update();
	}

	if (rva0042219() && m_40 == 0x400 && !CopyProtect::rva00232D38()) {
		GameMessage *msg = MessageStreamSubsystem->appendMessage(0x448);
		msg->appendBooleanArgument(false);
	}

	if (first) {
		for (Object *obj = m_objList; obj; obj = obj->getNextObject()) {
			if (obj->isDisabled())
				obj->rva00290357();
			if (obj->testStatus((ObjectStatusTypes)0x4a))
				obj->rva002903C3();
			if (obj->testStatus((ObjectStatusTypes)4))
				obj->rva002903EF();
			obj->rva00297612();
		}
		if (!m_a8 && m_44) {
			Rva00225A0C((int)m_40 * 10);
			if (TheWritableGlobalData->m_123d)
				g_00E09A00 = m_40;
			if (TheWritableGlobalData->m_d45 && TheWritableGlobalData->m_d48 > 0) {
				if (m_40 <= TheWritableGlobalData->m_d48) {
					char path[260];
					strcpy(path, TheWritableGlobalData->m_mapName.str());
					int length = strlen(path);
					if (length >= 4) {
						char *p = path + length - 4;
						while (p > path && *p != '\\' && *p != '/')
							--p;
						*p = 0;
						strcat(path, "\\scenecapture.dat");
						if (m_40 == 1)
							_imp___unlink(path);
						File *file = TheFileSystem->openFile(path, 0x4b, 0);
						if (file) {
							int start = file->seek(0, File::END);
							int size = 0;
							file->write(&size, sizeof(size));
							XferSave xfer;
							xfer.Open((Xfer *)file, 0, false);
							((Rva00238E1B *)TheGameClient)->rva00238FF3((Rva00238FF3Arg *)&xfer);
							xfer.close();
							size = file->seek(0, File::CURRENT);
							file->seek(start, File::START);
							file->write(&size, sizeof(size));
							file->close();
						}
					}
				} else
					TheGameEngine->setQuitting(true);
			}
		}
		TheGameClient->m_c8 = true;
	}
}
