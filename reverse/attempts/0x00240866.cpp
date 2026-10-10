// ?rva00240866@GameLogic@@QAEXPAVRva0023E928@@_N@Z
// partial score=0.9985668177569269 date=2026-10-10
template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /I.
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
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "reference/shims/moduledata/Common/Snapshot.h"
#include "Code/Libraries/Source/profile/profile.h"

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
// TeamsInfoRec::removeTeam (0x0032C26D) repairs.
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
	void removeTeam(int index);
	TeamsInfoNode *getNode(int index) { return &m_nodes[index]; }
	int addTeam(const Dict *d);

private:
	_STL::map<_STL::pair<AsciiString,AsciiString>,int> m_tree;
	_STL::vector<TeamsInfoNode> m_nodes;
	short m_count;short m_freeHead;
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

unsigned char __cdecl Rva0023D32DGet();
void __stdcall Rva0023D30FCall(int,int,int);
class GameLogic : public SubsystemInterface
{
public:
 void rva00240866(class Rva0023E928 *msg,bool frozen);
 __forceinline unsigned char rva0023D32D(){
 typedef unsigned char(GameLogic::*Member)();
 union NativeCallView {unsigned char(__cdecl *function)();Member member;} call;
 call.function=Rva0023D32DGet;
 return (this->*call.member)();
}
 void rva0023D30F(int a,int b,UnicodeString*name);

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
	void CreateWOTRMPPlayers();
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
LargeGroupAudio *TheLargeGroupAudio = 0;
BuffLogic *TheBuffLogic = 0;
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

extern GameInfo *TheGameInfo;
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
 virtual int slotB8();

};

extern NetworkInterface *TheNetwork;
class GameState
{
	char m_pad00[0x2c];
public:
 void rva002DDE43(const UnicodeString&,const UnicodeString&,int,int);

	AsciiString m_pristineMapName;                                       // +0x2C
};
extern GameState *TheGameState;
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
// The network request 0x00240866 answers: the sending player at +0x0C, the
// request kind at +0x1C, an argument at +0x20 and the save name through the
// rowed RVO getter 0x0023E928.
class Rva0023E928
{
public:
	UnicodeString rva0023E928(void) const;

	unsigned char m_pad00[0x0c];
	int m_player;                                                        // +0x0C
	unsigned char m_pad10[0x1c - 0x10];
	int m_kind;                                                          // +0x1C
	int m_20;                                                            // +0x20
};

// The save screen (0x00E032E0 while the saved-game prompt is up) and its
// rowed members.
class AptSaveLoad
{
public:
	void MultiplayerSaveGameDenied(int reason);
};

class Rva00433FDD
{
public:
	void rva00433D96(void);
};

extern int g_Va00E032E0;
extern UnicodeString g_Va00E032E8;
void __cdecl Rva004341D8(int button);
void __cdecl Rva00435CCC(void);

// TheGameState's rowed save-directory free-space check and save-exists test.
class Rva002DC267
{
public:
	bool rva002DC681(void) const;
};

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString name);
};

// The refcounted prompt callback (0x0023E8D8 builds it from a pointer to
// the function pointer) and the two prompt forwarders.
struct TargetRef00217D4C;
extern void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class Rva0023E8D8
{
	void *m_ptr;
public:
	Rva0023E8D8(void *p);
	Rva0023E8D8(const Rva0023E8D8 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva0023E8D8()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
extern "C" void __cdecl Rva00437F61(int type, const UnicodeString &title,
	const UnicodeString &text, Rva0023E8D8 callback);

typedef void (__cdecl *Rva00240866Answer)(int button);

// ?rva00240866@GameLogic@@QAEXPAVRva0023E928@@_N@Z @0x00240866 961B (Ghidra
// FUN_00640866). The multiplayer save request handler 0x0025E661 calls for
// message 0x1E. Kind 1 asks to save: a remote request is refused (2, 3)
// unless 0x0023D32D allows it, then the local player confirms through the
// "APT:SaveGameMultiplayerConfirmationTitle" prompt answered by 0x004341D8,
// or refuses (2, 1) with "APT:SaveFileDiskFullMultiplayer"; kind 2 is a
// refusal the save screen reports; kind 5 saves through TheGameState.
void GameLogic::rva00240866(Rva0023E928 *msg, bool frozen)
{
	if (!TheGameInfo || !msg || !TheNetwork || !TheGameState)
		return;
	int player = msg->m_player;
	switch (msg->m_kind) {
	case 1:
		if ((msg?p4Operand(TheGameLogic->m_11d):p4Operand(TheGameLogic->m_11d)))
			break;
		if (player != TheNetwork->slotB8()) {
			if (!rva0023D32D()) {
				if (frozen)
					++m_40;
				rva0023D30F(2, 3, &msg->rva0023E928());
				if (frozen)
					--m_40;
				break;
			}
			if (g_Va00E032E0)
				((Rva00433FDD *)g_Va00E032E0)->rva00433D96();
		}
		TheGameLogic->m_11d = true;
		if (player == TheNetwork->slotB8() || !TheGameState)
			break;
		if (!((Rva002DC267 *)TheGameState)->rva002DC681()) {
			if (frozen)
				++m_40;
			rva0023D30F(2, 1, &msg->rva0023E928());
			if (frozen)
				--m_40;
			Rva00437E84(0, TheGameText->fetch("GUI:Error"),
				TheGameText->fetch("APT:SaveFileDiskFullMultiplayer"));
		} else {
			UnicodeString text = TheGameText->fetch("APT:ConfirmMultiplayerSave");
			if (((Rva002DCCFB *)TheGameState)->rva002DCCFB(msg->rva0023E928()))
				text = TheGameText->fetch("APT:ConfirmMultiplayerSaveWithOverwrite");
			if (text.find('%')) {
				UnicodeString name = msg->rva0023E928();
				if (name.reverseFind('.'))
					name = UnicodeString(name, 0, name.reverseFind('.') - name.str());
				text.format(&text, name.str());
			}
			g_Va00E032E8 = msg->rva0023E928();
			{
				Rva00240866Answer answer = Rva004341D8;
				Rva00437F61(2, TheGameText->fetch("APT:SaveGameMultiplayerConfirmationTitle"), text,
					Rva0023E8D8(&answer));
			}
		}
		break;
	case 5:
		TheGameState->rva002DDE43(msg->rva0023E928(), msg->rva0023E928(), 0, 1);
		Rva00435CCC();
		TheGameLogic->m_11d = false;
		break;
	case 2:
		if (player != TheNetwork->slotB8() && g_Va00E032E0)
			((AptSaveLoad *)g_Va00E032E0)->MultiplayerSaveGameDenied(msg->m_20);
		TheGameLogic->m_11d = false;
		break;
	}
}
