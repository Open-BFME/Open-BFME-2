// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <map>
#include <set>
#include <string>
#include <vector>
#include <math.h>
// Retail calls _mbscpy and _mbscat through the msvcr71 import thunks at
// 0x00629176 and 0x0062988C; it never imports strcpy or strcat.
#include <mbstring.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Libraries/Source/profile/profile.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
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

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

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
template void _List_base<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> >::clear();
}

#include "../../../../Libraries/Include/Lib/Region3D.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString *>(AsciiString *, AsciiString *); }
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::clear(); }
// bfme link decl-only end

void setFPMode(void);

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset(void);                                            // +0x24
	virtual void update(void) {}                                         // +0x28
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

class Object;
enum PathfindLayerEnum { LAYER_GROUND = 1 };

class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
		bool newGame);                                                   // +0x10
	virtual void newMap(bool loadingSaveGame);                           // +0x14
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
	                            Coord3D *normal = 0, bool clip = true) const;
	virtual void getExtent(Region3D *extent) const;                      // +0x20
	virtual void bridgeSlot09();
	virtual void bridgeSlot0A();
	virtual void bridgeSlot0B();
	virtual void bridgeSlot0C();
	virtual void bridgeSlot0D();
	virtual void bridgeSlot0E();
	virtual void bridgeSlot0F();
	virtual void bridgeSlot10();
	virtual void bridgeSlot11();
	virtual void bridgeSlot12();
	virtual void bridgeSlot13();
	virtual void bridgeSlot14();
	virtual void bridgeSlot15();
	virtual void bridgeSlot16();
	virtual void bridgeSlot17();
	virtual void bridgeSlot18();
	virtual void bridgeSlot19();
	virtual void bridgeSlot1A();
	virtual void bridgeSlot1B();
	virtual void bridgeSlot1C();
	virtual void bridgeSlot1D();
	virtual void bridgeSlot1E();
	virtual void bridgeSlot1F();
	virtual void bridgeSlot20();
	virtual void bridgeSlot21();
	virtual void bridgeSlot22();
	virtual void bridgeSlot23();
	virtual void bridgeSlot24();
	virtual void bridgeSlot25();
	virtual void bridgeSlot26();
	virtual void bridgeSlot27();
	virtual void bridgeSlot28();
	virtual void bridgeSlot29();
	virtual void bridgeSlot2A();
	virtual void bridgeSlot2B();
	virtual void bridgeSlot2C();
	virtual void bridgeSlot2D();
	virtual void bridgeSlot2E();
	virtual void addLandmarkBridgeToLogic(Object *bridgeObj); // +0xBC; donor name
	void LoadAmbientLightmap(const AsciiString &filename);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
	void rva0027D3D9(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void addTree(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
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
	void NewMap(void);
	void ProcessPathfindQueue(void);
	void AddObjectToPathfindMap(Object *obj);
};

// loadAllObjects reads the three tree names at +0xDC..E4 and scale at +0xE8.
// The field offsets are retail facts; the tree meanings follow the donor.
class AIData
{
	char m_pad00[0xd8];
public:
	bool m_d8;
	AsciiString m_treeName[3];
	float m_treeScale;
	bool m_ec;
};

class AI : public SubsystemInterface
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }
	const AIData *getAiData(void) const { return m_aiData; }

private:
	int m_0c;
	Pathfinder *m_pathfinder;                                            // +0x10
	char m_pad14[0x18 - 0x14];
	AIData *m_aiData;
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
	void newMap(void);	// 0x00207C02
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

#include "../../../Include/Common/Overridable.h"

struct Rva00200BD9Holder;

class StatsCollector;

class Rva0048BA39StatsCollector
{
public:
	~Rva0048BA39StatsCollector(void) {}
private:
	AsciiString m_name;
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

class Rva004DFC20
{
public:
	void clear(void);
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

class SpawnArmy { public: virtual void loadPostProcess(); };
class Rva0043B660
{
public:
	Rva0043B660(void);
	/* the rowed SpawnArmy::loadPostProcess */ __declspec(dllimport) __forceinline void rva000B3FD0() { ((SpawnArmy *)this)->SpawnArmy::loadPostProcess(); }

private:
	int m_body[4];
};

class Rva0043821C
{
public:
	void rva0043821C(void);
};

class Rva000D3FA0Map
{
public:
	Rva000D3FA0Map(void);
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
	bool getBool(int key, bool *exists = 0) const;
	float getReal(int key, bool *exists = 0) const;
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
	void parseCastleTemplateMaps(void);	// 0x0032F84F
	void discardOverriddenScriptsAndTeams(void);
	void rva0032FF91(void);
	void addMusicScriptReference(void);
	TeamsInfoRec *getTeamInfo(void) { return &m_teams; }
	int addSide(const Dict *d);
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	void addTeam(const Dict *d) { m_teams.addTeam(d); }
	bool validateSides(void);
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
	char m_pad0DC[0x9ad - 0xdc];
	bool m_9ad;
	char m_pad9AE[0x9c1 - 0x9ae];
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
	char m_pad1111[0x11c8 - 0x1111];
	bool m_11c8;
	char m_pad11C9[0x123d - 0x11c9];
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

// Constructor members (native 0x002470AE). The 0x14-byte hash wrappers at
// +0x10 and +0xB4 are built by the rowed 31B ctor 0x00246FD7; the map at +0x24
// by the out-of-line default map constructor 0x0024613C; the pooled
// Object* list at +0x108 by its list-base constructor 0x001EB984; the
// Snapshot member at +0x184 by 0x0040E039. Type names are address views.
class Rva00246FD7
{
public:
	Rva00246FD7(void);
	~Rva00246FD7(void);
private:
	char m_body[0x14];
};
// The unwind map selects separate destructors for the two table wrappers.
struct Rva00243B48
{
    ~Rva00243B48();
    Rva00246FD7 m_table;
};
struct Rva00240E13
{
    ~Rva00240E13();
    Rva00246FD7 m_table;
};
struct BfmePod8 { int a[2]; };
namespace _STL {
template <> map<int, BfmePod8, less<int>, allocator<pair<const int, BfmePod8> > >::map();
}
template <class T> class Rva001EB984PoolAllocator { public: Rva001EB984PoolAllocator(void) {} };
namespace _STL {
template <> class _List_base<Object *, Rva001EB984PoolAllocator<Object *> >
{
public:
	_List_base(const Rva001EB984PoolAllocator<Object *> &);
	~_List_base(void);
private:
	void *m_node;
};
}
// The pooled Object* list: like STLport's list(const allocator_type & =
// allocator_type()), the default argument feeds the out-of-line base.
class Rva001EB984ObjectList : public _STL::_List_base<Object *, Rva001EB984PoolAllocator<Object *> >
{
public:
	__forceinline explicit Rva001EB984ObjectList(
		const Rva001EB984PoolAllocator<Object *> &a = Rva001EB984PoolAllocator<Object *>())
		: _STL::_List_base<Object *, Rva001EB984PoolAllocator<Object *> >(a)
	{
	}
};
class Rva0040DB52
{
public:
	Rva0040DB52(void);
	virtual ~Rva0040DB52(void);
private:
	char m_body[0x28];
};
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

// Retail folds this record's vector growth onto the no-EH STLport provider.
// Keep that provider's algorithm visible without emitting an EH-enabled copy.
namespace _STL {
template<> inline void vector<Rva0024622FEntry>::_M_insert_overflow(
    pointer position, const Rva0024622FEntry &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}

class Rva002259F3 { public: int rva002259F3() const; };
class Rva00240E18 { public: void rva00240E18(bool); };
class GameLogic : public SubsystemInterface, public Snapshot
{
public:
	GameLogic(void);
	virtual ~GameLogic(void);
	virtual void init(void);
	virtual bool v11(int) { return false; }
	virtual void v12(void) {}
	virtual void update(int phase);                                      // +0x34
	virtual TerrainLogic *createTerrainLogic(void) = 0;                      // +0x38
	virtual GhostObjectManager *createGhostObjectManager(void) = 0;          // +0x3C
	virtual BuffLogic *createBuffLogic(void) = 0;                            // +0x40

	virtual void reset(void);

	/* the rowed Rva00240E18::rva00240E18 */ __declspec(dllimport) __forceinline void rva00240E18(bool p0) { ((Rva00240E18 *)this)->rva00240E18(p0); }
	void rva0023D17D(void);
	void destroyAllObjectsImmediate(void);
	void rva00376D49(void);
	void rva00246422(bool dontCreate);
	void startNewGame(bool loadingSaveGame);
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
	bool rva002423E3(void);
	void rva0024622F(bool loadingSaveGame);
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }
	bool rva0023C8DA(unsigned char loadingSaveGame);
	Object *findObjectByID(ObjectID id);
	void loadAllObjects(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
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
	__declspec(dllimport) __forceinline bool rva002259F3(void) { return (unsigned char)((const Rva002259F3 *)this)->rva002259F3() != 0; }
	bool rva0042219(void);
	void processCommandList(void);
	void processDestroyList(void);
	void destroyObject(Object *obj);
	bool rva0024877A(void);
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

	Rva00243B48 m_10;
	_STL::map<int, BfmePod8> m_24;
	float m_width;
	float m_height;
	unsigned int m_38;
	bool m_3c;
	char m_pad03D[0x40 - 0x3d];
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
	bool m_6e;
	bool m_6f;
	bool m_70;
	bool m_71;
	bool m_72;
	AsciiString m_74;
	bool m_78;
	AsciiString m_7c;
	AsciiString m_80;
	AsciiString m_84;
	AsciiString m_88;
	AsciiString m_8c;
	int m_90;
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
	int m_b0;
	Rva00240E13 m_b4;
	UpdateModuleList m_updates[4];                                       // +0xC8
	UpdateModuleList m_sleeping;                                         // +0xF8
	UpdateModule *m_104;
	Rva001EB984ObjectList m_108;
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
	// Retail builds it through the folded vector base constructor 0x00211E58
	// and update() clears it through vector<UpdateModule*>::erase 0x0031BD55.
	UpdateModuleList m_164;
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva000D3FA0Map *m_178;
	int m_17c;
	int m_180;
	Rva0040DB52 m_184;
	int m_1b0;
	int m_1b4;
	int m_1b8;
	bool m_1bc;
	char m_pad1BD[0x1c0 - 0x1bd];
	ObjectTOCList m_objectTOC;
	PlayerLeaveStatus m_1c4[8];
	int m_2a4;
};

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;
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
template <class T> class OVERRIDE;
class WaterTransparencySetting;
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;

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

// ??0GameLogic@@QAE@XZ @0x002470AE 714B (native 0x002470AE..0x00247378,
// RET0 thiscall). WB CF06F0 is the same constructor with debug member order;
// ZH GameLogic.cpp GameLogic::GameLogic is the semantic donor (scalar
// initializers in declaration order, then the leave-status reset). Target
// facts: SubsystemInterface 0x001B4E63 then Snapshot at +0x0C, the
// "LoadingRing"/"TitleScreen" strings at +0x7C/+0x80, 4 vector update
// buckets at +0xC8, eight 0x1C leave-status records at +0x1C4, the closing
// list clear 0x0023DAA5 on +0x50, reset 0x0023D17D and +0x2A4 = 2.
GameLogic::GameLogic(void)
	: m_width(0.0f), m_height(0.0f), m_38(0), m_3c(false), m_40(0), m_44(false), m_48(0),
	  m_64(), m_68(), m_6c(false), m_6d(false), m_6e(false), m_6f(false),
	  m_70(false), m_71(false), m_72(false), m_78(false),
	  m_7c("LoadingRing"), m_80("TitleScreen"), m_90(7), m_94(0),
	  m_98(false), m_99(false), m_9a(false), m_9b(false),
	  m_9c(false), m_9d(false), m_9e(false), m_9f(false),
	  m_a0(0), m_a4(1), m_a8(false), m_objList(0), m_b0(0),
	  m_104(0), m_10c(0), m_110(9), m_114(3), m_118(1000),
	  m_11c(false), m_11d(false), m_120(0), m_124(false), m_125(false),
	  m_126(true), m_127(true), m_150(false),
	  m_154(0), m_158(0), m_15c(0), m_160(0),
	  m_170(0), m_174(0), m_178(0), m_17c(0), m_180(0),
	  m_1b4(0), m_1b8(0), m_1bc(false)
{
	for (int i = 0; i < 8; ++i) {
		m_128[i] = false;
		m_130[i] = 0;
	}
	m_50.clear();
	rva0023D17D();
	m_2a4 = 2;
}

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
	((Rva006C0810 *)TheTaintManager)->rva006C0810(&extent, TheWritableGlobalData->m_d4);

	m_170 = new Rva00359E13;
	m_170->rva0035AA3E();
	((Rva0035A2DC *)m_170)->rva0035A2DC(&extent, TheWritableGlobalData->m_d8);

	m_174 = new Rva0043B660;
	m_174->rva000B3FD0();

	m_178 = new Rva000D3FA0Map;
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
	TheSidesList->parseCastleTemplateMaps();

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

	((Rva000427195 *)&m_10)->rva003A2A41();
	((Rva00240CAB *)&m_24)->rva0024191A();
	((Rva004DFC20 *)&m_b4)->clear();
	((Rva0053F1ECSub *)&m_b4)->note(0x2000);

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
	((SubsystemInterface *)TheTaintManager)->reset();
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

	reinterpret_cast<Overridable *&>(TheWaterTransparency) = reinterpret_cast<Overridable *&>(TheWaterTransparency)->deleteOverrides();

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
	void setTeamNumber(int teamNumber);
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
	void setGroup(AsciiString groupName, bool immidiate = false);
	bool isFinished(void);
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

#include "../../../Include/Common/BfmeXfer.h"

class ThingTemplate
{
public:
	const AsciiString &getName(void) const { return m_name; }
	void GetAssetList(int a, int b);
	bool isKindOf(KindOfType t) const;

private:
	char m_pad00[0x64];
	AsciiString m_name;
	char m_pad68[0x108 - 0x68];
public:
	unsigned int m_108;
	unsigned int m_kindof[4];
	unsigned int m_11c;
	unsigned int m_120;
	char m_pad124[0x4a0 - 0x124];
	float m_fenceWidth;
	char m_pad4A4[0x4e0 - 0x4a4];
	float m_4e0;
	char m_pad4E4[0x5e5 - 0x4e4];
	bool m_5e5;
	char m_pad5E6[0x5eb - 0x5e6];
	bool m_5eb;
	bool m_5ec;
};

class Dict;

class Drawable;
class Team;
class ContainModuleInterface;
class ExperienceTracker;


class Matrix3D
{
	// The donor's three Vector4 rows, restricted to the operations used here.
	struct MatrixRow
	{
		float X, Y, Z, W;
		__forceinline void Set(float x, float y, float z, float w)
		{ X = x; Y = y; Z = z; W = w; }
		__forceinline float &operator[](int i) { return (&X)[i]; }
	};

public:
	__forceinline Matrix3D(void) {}
	// Retain the existing inline-only constructor view; no competing COMDAT.
	__declspec(dllimport) __forceinline explicit Matrix3D(bool init)
	{ if (init) Make_Identity(); }

	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}

	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float cosine, s;
		const float &c = cosine;
		cosine = cosf(theta);
		s = sinf(theta);
		// The cosine reference and final product conversion preserve retail's
		// MSVC 7.1 x87/SSE scheduling. They are codegen adaptations, not a
		// claim that the donor used reference storage for its cosine local.
		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)(c * tmp1 + s * tmp2);
		Row[0][1] = (float)(-s * tmp1 + c * tmp2);
		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)(c * tmp1 + s * tmp2);
		Row[1][1] = (float)(-s * tmp1 + c * tmp2);
		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)(c * tmp1 + (float)(s * tmp2));
		Row[2][1] = (float)(-s * tmp1 + c * tmp2);
	}

	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0].X = m.Row[0].X; Row[0].Y = m.Row[0].Y; Row[0].Z = m.Row[0].Z; Row[0].W = m.Row[0].W;
		Row[1].X = m.Row[1].X; Row[1].Y = m.Row[1].Y; Row[1].Z = m.Row[1].Z; Row[1].W = m.Row[1].W;
		Row[2].X = m.Row[2].X; Row[2].Y = m.Row[2].Y; Row[2].Z = m.Row[2].Z; Row[2].W = m.Row[2].W;
		return *this;
	}

private:
	MatrixRow Row[3];
};

class Thing
{
public:
	Drawable *getDrawable(void) const;
	void setTransformMatrix(const Matrix3D *mtx);
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
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
	__declspec(dllimport) __forceinline bool anyIntersectionWith(const BitFlags &that) const { return that.test(this); }

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
	void updateObjValuesFromMapProperties(Dict *properties);
	void setLayer(PathfindLayerEnum layer);
	void rva00293E64(Dict *properties);
	bool testStatus(ObjectStatusTypes bit) const;
	bool isDisabled_(void) const { return m_disabledMask.any(); }
	const DisabledMaskType &getDisabledFlags(void) const { return m_disabledMask; }
	AIUpdateInterface *getAIUpdateInterface(void) const { return m_ai; }
	void rva0023D3AF(void *frame);
	void checkDisabledStatus(void);
	void rva002903C3(void);
	void rva002903EF(void);
	void rva00297612(void);
	const Matrix3D *getTransformMatrix(void) const { return &m_transform; }
	ObjectID getID(void) const { return m_id; }
	Team *getTeam(void) const { return m_team; }
	ContainModuleInterface *getContain(void) const { return m_contain; }
	ExperienceTracker *getExperienceTracker(void) const { return m_experienceTracker; }
	Object *getContainedBy(void) const { return m_containedBy; }
	bool rva0028C428(void) const;
	void *rva0028C197(void) const;
	void rva0028D412(const Matrix3D *transform);
	void *rva0029439D(void);
	void setProducer(Object *obj);

private:
	void *m_vtbl;
	const ThingTemplate *m_template;
	Matrix3D m_transform;                                                // +0x08
	char m_pad38[0x74 - 0x38];
	ObjectID m_id;                                                       // +0x74
	char m_pad78[0x8c - 0x78];
	Object *m_next;
	char m_pad090[0x94 - 0x90];

public:
	unsigned int m_94;                                                   // +0x94
	char m_pad098[0x188 - 0x98];
	unsigned int m_188;                                                  // +0x188
	char m_pad18C[0x1c8 - 0x18c];

private:
	DisabledMaskType m_disabledMask;                                     // +0x1C8
	char m_pad1CC[0x250 - 0x1cc];
	ContainModuleInterface *m_contain;                                   // +0x250
	char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai;                                             // +0x258
	char m_pad25C[0x264 - 0x25c];
public: ExperienceTracker *m_experienceTracker; private:                              // +0x264
	char m_pad268[0x274 - 0x268];
	Object *m_containedBy;                                               // +0x274
	char m_pad278[0x304 - 0x278];
	Team *m_team;                                                        // +0x304
};

// ZH GameLogic::findTOCEntryByName, the same 89B shape as GameClient's
// drawable twin 0x00239C5E: StringBase compare 0x000069D6 per node.
ObjectTOCEntry *GameLogic::findTOCEntryByName(AsciiString name)
{
	for (ObjectTOCList::iterator it = m_objectTOC.begin(); it != m_objectTOC.end(); ++it)
		if ((*it).name == name)
			return &(*it);
	return 0;
}

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
struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;

class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}
	void clear(void)
	{
		// Pointer-set and int-map clear/erase are whole-body relocation twins
		// at 0x6AA1C/0x692F5. Their trivial payload cleanup shares this provider.
		((_STL::map<int, int> *)&m_prototypes)->clear();
		m_changed = true;
	}

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

class BfmeRetBWF;
class Rva0030D631 { public: BfmeRetBWF *rva0030D631(); };

class MapObject
{
public:
	MapObject *getNext_(void) const { return m_next; }
	__declspec(dllimport) __forceinline const Coord3D *getLocation(void)
	{ return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631(); }
	float getAngle(void) const { return m_angle; }
	int getFlags(void) const { return m_flags; }
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

class BfmeMapObjectListHolder
{
public:
	MapObject *m_head;
};

// The map-object list head all readers share (other TUs spell the class
// BfmeMapObjectListHolder with m_head at the same +0x00); defined once here,
// retail zeros at VA 0x00E00940.
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;
BfmeMapObjectListHolder *BfmeTheMapObjectListHolder = 0;

// newObjects third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
	unsigned int m_bits[4];
};

class Team;

// The +0x08 member of Player: 0x003805BB takes a point value and a flag
// (Player::addSkillPointsForKill passes true); the 10-byte store of its +0x18
// at 0x002E6A93 is ICF-folded with GameSlot::setTeamNumber and called by that
// row name.
// 0x003805BB is rowed as Rva00380200::rva003805BB (Rva00380200Getter.cpp).
class Rva00380200 { public: bool rva003805BB(float value, bool flag); };

class Rva003805BB
{
public:
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
	Team *validateTeam(AsciiString owner, MapObject *mapObj);

private:
	char m_pad0C[0x10 - 0x0c];
	Player *m_local;
	char m_pad14[0x18 - 0x14];
	Player *m_neutralPlayer;
};

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tt, Team *team, const CreateMask *mask, ObjectID id);
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;
extern PlayerList *ThePlayerList;


// 0x00271058 compares, unregisters and re-registers the ID at +0x100 (the
// ZH Drawable::setID shape; WB names it Drawable::setID).
class Drawable
{
public:
	void rva00278C6B(void);
	void setID(void *p);	// 0x00271058
	Drawable *getNextDrawable(void) const { return m_next; }
	void setDrawableStatus(unsigned int bits) { m_status |= bits; }
	bool isVisible(void) const { return m_visible; }

private:
	char m_pad000[0x104];
	Drawable *m_next;                                                    // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status;
	char m_pad118[0x43c - 0x118];
	bool m_visible;                                                      // +0x43C
};

// Binds the kind to a temporary for the loader's pointer argument.
static __forceinline const KindOfType *kindRef(const KindOfType &kind) { return &kind; }

void GameLogic::rva00246422(bool dontCreate)
{
	_STL::vector<Rva0024622FEntry> created;
	if (dontCreate) {
		for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_head; pMapObj; pMapObj = pMapObj->getNext_()) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			const ThingTemplate *tt = pMapObj->getThingTemplate();
			if (tt == 0)
				continue;
			if (!((tt->m_kindof[62 >> 5] & (1u << (62 & 31))) != 0) && !((tt->m_kindof[63 >> 5] & (1u << (63 & 31))) != 0))
				continue;
			const Coord3D *loc = pMapObj->getLocation();
			Coord3D pos;
			pos.x = loc->x;
			pos.y = loc->y;
			pos.z = loc->z;
			Matrix3D mtx(true);
			if (((tt->m_kindof[62 >> 5] & (1u << (62 & 31))) != 0))
				TheTerrainLogic->addTree(tt, &pos, &mtx, 1.0f);
			else if (((tt->m_kindof[63 >> 5] & (1u << (63 & 31))) != 0))
				TheTerrainLogic->rva00280176(tt, &pos, &mtx, 1.0f);
		}
		loadAllObjects(&created, kindRef((KindOfType)0x3c), 0, true);
	} else {
		loadAllObjects(&created, kindRef((KindOfType)0x3c), 0, false);

		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		m_154 = findObjectByID((ObjectID)99999999);
		if (m_154 == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheOneTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_154 = TheThingFactory->newObject(tt, team, &CreateMask(), (ObjectID)99999999);
				if (m_154)
					m_154->getDrawable()->setID((void *)99999999);
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
					((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_158 = TheThingFactory->newObject(tt, team, &CreateMask(), (ObjectID)99999998);
				if (m_158)
					m_158->getDrawable()->setID((void *)99999998);
			}
		}

		m_15c = findObjectByID((ObjectID)99999996);
		if (m_15c == 0) {
			const ThingTemplate *tt = TheThingFactory->findTemplate("TheGrabbableTree");
			if (tt) {
				if (!TheWritableGlobalData->m_1110) {
					AssetLoadMode mode;
					AssetList assets;
					((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_15c = TheThingFactory->newObject(tt, team, &CreateMask(), (ObjectID)99999996);
				if (m_15c)
					m_15c->getDrawable()->setID((void *)99999996);
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
					((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
					bfmeMergeReceiverKeys((int)&assets);
				}
				Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
				m_160 = TheThingFactory->newObject(tt, team, &CreateMask(), (ObjectID)99999997);
				if (m_160)
					m_160->getDrawable()->setID((void *)99999997);
			}
		}

		for (Rva0024622FEntry *it = created.begin(); it != created.end(); ++it) {
			Rva0134FAA0->slot28();
			bfmeReleaseQueuedDeviceInterfaces();
			it->obj->rva00293E64(it->mapObj->getProperties());
		}
	}
}

// ?startNewGame@GameLogic@@QAEX_N@Z
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
		void *menu = GetSystemMenu(ApplicationHWnd, 0);
		EnableMenuItem(menu, 0xF060, 1);
	}
	~Rva0023C83B(void) throw()
	{
		void *menu = GetSystemMenu(ApplicationHWnd, 0);
		EnableMenuItem(menu, 0xF060, 0);
	}
};

struct BfmeAudioEventPrefix136;
struct MiscAudio;

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10();
	virtual void slot44(int a, int b, int c);                            // +0x44
	virtual void v12(); virtual void v13();
	virtual void slot50(bool enable);                                    // +0x50
	virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18();
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd); // +0x64
	virtual void v1a(); virtual void v1b();
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
	virtual void v4c(); virtual void v4d();
	virtual MiscAudio *getMiscAudio(void);                               // +0x138
	virtual void v4f();
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
	int get1774(void) const { return m_1774; }

private:
	char m_pad0000[0x1768];
	int m_staticLODLevel;
	char m_pad176C[0x1774 - 0x176c];
	int m_1774;
};

void bfmeClearReceiverFlag(int value);

extern AudioManager *TheAudio;
extern BfmeDfe6e4 *theBfmeDfe6e4;
// TheHeroManager is only an alias of the owned global TheCreateAHeroManager (ledger names column); this unit reads the owner through its own view type.
extern class CreateAHeroManager *TheCreateAHeroManager;
#define TheHeroManager (*(Rva0021A54A * *)&TheCreateAHeroManager)
extern GameLODManager *TheGameLODManager;
extern int SavedClientFrame;
extern unsigned char isLoadingMap;
extern char g_00E09B08[];
int g_00E09A00;	// retail RVA 0x00A09A00 (.bss), defined here

void GameLogic::startNewGame(bool loadingSaveGame)
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
	isLoadingMap = 0;
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
		_mbscpy(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>("assetload "));
		const char *mapName = TheWritableGlobalData->m_mapName.str();
		const char *slash = _imp__strrchr(mapName, '\\');
		_mbscat(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>(slash ? slash + 1 : mapName));
		if (TheGameLODManager) {
			switch (TheGameLODManager->getStaticLODLevel()) {
			case 0:
			case 1:
				_mbscat(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>(" (low)"));
				break;
			case 2:
				_mbscat(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>(" (medium)"));
				break;
			case 3:
			case 4:
				_mbscat(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>(" (high)"));
				break;
			}
		}
		_mbscat(reinterpret_cast<unsigned char *>(g_00E09B08), reinterpret_cast<const unsigned char *>(".csv"));
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
	void setControlBarSchemeByPlayer(Player *player);
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

// 0x00A02290 is TheRecorder; 0x0037BD81 is RecorderClass::initControls (hide
// ReplayControl.wnd unless the +0x1C mode is playback).
class File;

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class CommandDumpFile0037BE15;

class RecorderClass : public SubsystemInterface
{
	friend class GameLogic;
public:
	bool isMultiplayer(void);
	RecorderModeType getMode(void);
	void logCRCMismatch(void);
	void initControls(void);

	char m_pad00C[0xe68 - 0xc];
	int m_e68;
	int m_e6c;

protected:
	void dumpCommandHistory(CommandDumpFile0037BE15 *output, unsigned int frame);
};


class InGameUI
{
	friend class GameLogic;

public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void __cdecl message(UnicodeString format, ...);            // +0x40
	void setClientQuiet(bool quiet) { m_clientQuiet = quiet; }

private:
	char m_pad004[0x8c5 - 4];
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
	const Coord3D *getLocation_(void) const { return &m_location; }

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
	virtual void tf0b(); virtual void tf0c(); virtual void tf0d(); virtual void tf0e(); virtual void tf0f(); virtual void tf10(); virtual void tf11();
	void rva003A262C(void);
	Team *findTeamByID(unsigned int id);
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
	virtual void v2e(); virtual void v2f();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual bool slotD0(void);                                           // +0xD0
};

extern ParticleSystemManager *TheParticleSystemManager;
extern ControlBar *TheControlBar;
extern G00DFF080Obj *TheTerrainVisual;
extern View *TheTacticalView;
extern RecorderClass *TheRecorder;
extern NameKeyGenerator *TheNameKeyGenerator;
extern const StaticNameKey TheKey_InitialCameraPosition;
class VictorySystem;
extern VictorySystem *TheVictorySystem;
extern Rva002A8F24 *TheSkirmishAIManager;
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
	TheTerrainVisual->slot14();
	Sleep(1);
	((Rva0023C7D2 *)this)->rva0023C7BB(0x5f);
	Sleep(1);
	TheTacticalView->setAngleAndPitchToDefault();
	Sleep(1);
	TheTacticalView->setZoomToDefault();
	Sleep(1);
	if (TheRecorder)
		TheRecorder->initControls();

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
		pos.x = way->getLocation_()->x;
		pos.y = way->getLocation_()->y;
		pos.z = way->getLocation_()->z;
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
	TheSkirmishAIManager->rva002A95F9();
	TheTeamFactory->rva003A262C();

	if (!loadingSaveGame && ((Rva0023C666 *)this)->rva0023C666()) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		for (int i = 0; i < 20; ++i) {
			Player *player = ThePlayerList->getNthPlayer(i);
			if (player && player->getPlayerType() == PLAYER_HUMAN) {
				((Rva00380200 *)&player->m_skillPoints)->rva003805BB((float)m_94, false);
				((GameSlot *)&player->m_skillPoints)->setTeamNumber(player->m_skillPoints.m_14);
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
	isLoadingMap = 1;
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

void placeNetworkBuildingsForPlayer(int slotNum, const GameSlot *slot, Player *player, const PlayerTemplate *pt);

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
				addCoord(&center, waypoint->getLocation_());
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
					placeNetworkBuildingsForPlayer(i, slot, player, ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate()));
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
	void update(void);	// 0x00437BB6

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

class Rva0023C641
{
public:
	void rva0023D494(void);	// 0x0023D494 (Rva0023C641Write.cpp)
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

	char m_pad004[0xb8 - 4];
	int m_b8;
	char m_padBC[0xc8 - 0xbc];
	bool m_c8;
};

enum GameSpyBuddyStatus
{
	GAMESPY_BUDDY_STATUS_5 = 5
};

extern Shell *TheShell;
extern Radar *TheRadar;
extern unsigned char g_00DFE7A8;	// canonical byte owner, Rva003B9EC4.cpp
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern GameSpyStagingRoom *TheGameSpyGame;
// TheGameClient is only an alias of the owned global TheGameClient (ledger names column); this unit reads the owner through its own view type.
extern class GameClient *TheGameClient;
#define TheGameClient (*(ClientFrameSubsystem * *)&TheGameClient)

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
			if (TheTaintManager)
				((Rva006C0820 *)TheTaintManager)->rva006C0820();
			TheControlBar->setControlBarSchemeByPlayer(ThePlayerList->getLocalPlayer());
		} else {
			Player *localPlayer = ThePlayerList->getLocalPlayer();
			ThePlayerList->setLocalPlayer(ThePlayerList->getNeutralPlayer());
			ThePlayerList->setLocalPlayer(localPlayer);
			TheControlBar->setControlBarSchemeByPlayer(ThePlayerList->getLocalPlayer());
			TheControlBar->m_210 = 0;
		}
	}
	TheTacticalView->setOkToAdjustHeight(true);

	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	if (*(unsigned char *)&g_00DFE7A8)
		((Rva0023C641 *)&g_00DFE7A8)->rva0023D494();
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
extern "C" const void *const __identifier("??_7Rva00527827Base@@6B@")[];

class Rva0084EF80Base
{
public:
	virtual void rva0084EF80_slot0() {}
	virtual void rva0084EF80_slot1() {}
	virtual void rva0084EF80_slot2() {}
	virtual void rva0084EF80_slot3() {}
	~Rva0084EF80Base()
	{
		*(const void **)this = __identifier("??_7Rva00527827Base@@6B@");
	}
};

struct Rva00240000Vector
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva00240000Vector()
	{
		if (m_start)
			free(m_start);
	}
};

class __declspec(novtable) Rva00240000 : public Rva0084EF80Base
{
public:
	Rva00240000(void);
	~Rva00240000(void);
	bool rva00308050(AsciiString path);

private:
	Rva00240000Vector m_04;
	Rva0084EF80Base m_10;
	int m_14;
	int m_18;
	int m_1c;
};

Rva00240000::~Rva00240000(void)
{
}

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
	virtual void slot5C(void);                                           // +0x5C
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
	virtual void d40(); virtual void d41(); virtual void d42();
	virtual void slot10C(AsciiString movie, int a, int b);              // +0x10C
	virtual void slot110(void);                                          // +0x110
	virtual bool slot114(void);                                          // +0x114
	virtual void d46(); virtual void d47();
	virtual void d48(); virtual void d49(); virtual void d4a(); virtual void d4b();
	virtual void d4c(); virtual void d4d(); virtual void d4e(); virtual void d4f();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
	virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57();
	virtual void d58(); virtual void d59(); virtual void d5a(); virtual void d5b();
	virtual void d5c(); virtual void d5d(); virtual void d5e(); virtual void d5f();
	virtual void slot180(const Region3D *extent);                        // +0x180
	char m_pad004[0x115 - 0x4];
	bool m_115;                                                          // +0x115
	char m_pad116[0x13c - 0x116];
	int m_13c;                                                           // +0x13C
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
	void NewMap(void);
};

class Rva00739780
{
public:
	void rva00739780(int playerIndex);
};

extern int st_DebugDLL;
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;
extern LuaScriptEngine *TheLuaScriptEngine;
extern GameEngine *TheGameEngine;
class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;
extern InGameUI *TheInGameUI;
extern Display *TheDisplay;
extern Rva002872BA *TheTriggerManager;
// Its NewMap 0x00287015 is the rowed FireLogicSystem::NewMap.
class FireLogicSystem
{
public:
	void NewMap(void);
};

void bfmeStepReceiverRecord(int source);

void GameLogic::rva002469A5(bool loadingSaveGame, int *progress)
{
	if (TheWritableGlobalData->m_9c1) {
		NewMapProc proc = (NewMapProc)GetProcAddress((void *)st_DebugDLL, "NewMap");
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
		if ((*(GameInfo **)&TheSkirmishGameInfo)) {
			::delete (*(GameInfo **)&TheSkirmishGameInfo);
			(*(GameInfo **)&TheSkirmishGameInfo) = 0;
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
	TheSidesList->discardOverriddenScriptsAndTeams();
	rva0023E628(TheWritableGlobalData->m_mapName);
	((Rva0023C7D2 *)this)->rva0023C7BB(2);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();

	if (TheGameInfo) {
		int index = TheSidesList->getTeamInfo()->getNode(0)->m_previous;
		while (index) {
			int next = TheSidesList->getTeamInfo()->getNode(index)->m_previous;
			if (TheSidesList->getTeamInfo()->getNode(index)->m_chainPrevious)
				TheSidesList->getTeamInfo()->removeTeam(index);
			index = next;
		}
		if (TheGameEngine->isMultiplayerSession() || isSkirmish)
			TheSidesList->rva0032FF91();
		CreateMPPlayers(isSkirmish, *progress);
		((Rva00E03138 *)TheVictoryConditions)->reset();
	} else if (((Rva0023C6A4 *)this)->rva00200084()) {
		SetUpCampaignPlayers();
	}

	rva0023E0C7();
	if (!rva001DCD1C() && TheSidesList && TheSidesList->m_f7c)
		TheSidesList->addMusicScriptReference();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xc);
	TheTeamFactory->reset();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	ThePlayerList->p0e();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xd);
	TheScriptEngine->newMap();
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0xe);
	Rva0134FAA0->slot28();
	bfmeReleaseQueuedDeviceInterfaces();
	((Rva0023C7D2 *)this)->rva0023C7BB(0x10);
	TheRadar->newMap(TheTerrainLogic);
	TheInGameUI->setClientQuiet(false);
	((Rva00E03138 *)TheVictoryConditions)->slot44();
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
	if (TheTaintManager) {
		((Rva006C0810 *)TheTaintManager)->rva006C0810(&extent, 0.0f);
		((Rva006C0820 *)TheTaintManager)->rva006C0820();
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
	TheAI->pathfinder()->NewMap();
	((FireLogicSystem *)TheTriggerManager)->NewMap();
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
	__forceinline Rva0023E323(const AsciiString &groupName, int frame)
	  : m_groupName(groupName), m_frame(frame) {}
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
	_mbscpy(reinterpret_cast<unsigned char *>(filename), reinterpret_cast<const unsigned char *>(mapName.str()));

	if (((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(AsciiString(filename))))
		_mbscpy(reinterpret_cast<unsigned char *>(filename), reinterpret_cast<const unsigned char *>(TheGameState->m_pristineMapName.str()));

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
class W3DTerrainLogic
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
	_mbscpy(reinterpret_cast<unsigned char *>(filename), reinterpret_cast<const unsigned char *>(mapName.str()));

	if (((Rva002DC7C1 *)TheGameState)->rva002DC7C1(UnicodeString(AsciiString(filename))))
		_mbscpy(reinterpret_cast<unsigned char *>(filename), reinterpret_cast<const unsigned char *>(TheGameState->m_pristineMapName.str()));

	int length = strlen(filename);
	if (length < 4)
		return;

	char *extension = filename + length - 4;
	while (extension > filename && *extension != '\\' && *extension != '/')
		--extension;
	*extension = 0;

	_imp__sprintf(fullFledgeFilename, "%s\\ambientlightmap.tga", filename);
	if (TheFileSystem->doesFileExist(fullFledgeFilename))
		TheTerrainLogic->LoadAmbientLightmap(fullFledgeFilename);
	else
		((W3DTerrainLogic *)TheTerrainLogic)->Rva0027DA58();
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
extern const StaticNameKey TheKey_playerColor;
extern const StaticNameKey TheKey_playerNightColor;
extern const StaticNameKey TheKey_multiplayerStartIndex;
extern const StaticNameKey TheKey_multiplayerIsLocal;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;
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
	d.setInt(((Rva00148F5ECache *)&TheKey_playerColor)->get(), TheMultiplayerSettings->getColor(0)->getColor());
	d.setInt(((Rva00148F5ECache *)&TheKey_playerNightColor)->get(), TheMultiplayerSettings->getColor(0)->getNightColor());
	d.setInt(((Rva00148F5ECache *)&TheKey_multiplayerStartIndex)->get(), 0);
	d.setBool(((Rva00148F5ECache *)&TheKey_multiplayerIsLocal)->get(), false);

	TheSidesList->addSide(&d);
	d.clear();
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get(), "teamReplayObserver");
	d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get(), "ReplayObserver");
	d.setBool(TheKey_teamIsSingleton.get(), true);
	TheSidesList->addTeam(&d);
	TheSidesList->validateSides();
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

extern const StaticNameKey TheKey_playerIsSkirmish;
extern const StaticNameKey TheKey_playerHandicap;
extern const StaticNameKey TheKey_playerStartMoney;
extern const StaticNameKey TheKey_skirmishDifficulty;
extern const StaticNameKey TheKey_playerIsPreorder;
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
			d.setBool(((Rva00148F5ECache *)&TheKey_playerIsPreorder)->get(), true);

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
		d.setInt(((Rva00148F5ECache *)&TheKey_playerHandicap)->get(), slot->m_bfme20);
		d.setInt(((Rva00148F5ECache *)&TheKey_playerColor)->get(), TheMultiplayerSettings->getColor(slot->getColor())->getColor());
		d.setInt(((Rva00148F5ECache *)&TheKey_playerNightColor)->get(), TheMultiplayerSettings->getColor(slot->getColor())->getNightColor());
		d.setInt(((Rva00148F5ECache *)&TheKey_multiplayerStartIndex)->get(), slot->getStartPos());
		d.setBool(((Rva00148F5ECache *)&TheKey_multiplayerIsLocal)->get(), slot->isHuman() &&
			slot->m_name.compare(game->getSlot(game->getLocalSlotNum())->getNameStr()) == 0);

		if (game->m_54 >= 0)
			d.setInt(((Rva00148F5ECache *)&TheKey_playerStartMoney)->get(), game->m_54);

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
			d.setBool(((Rva00148F5ECache *)&TheKey_playerIsSkirmish)->get(), true);
			switch (slot->m_state)
			{
			case 2: d.setInt(((Rva00148F5ECache *)&TheKey_skirmishDifficulty)->get(), 0); break;
			case 3: d.setInt(((Rva00148F5ECache *)&TheKey_skirmishDifficulty)->get(), 1); break;
			case 4: d.setInt(((Rva00148F5ECache *)&TheKey_skirmishDifficulty)->get(), 2); break;
			case 5: d.setInt(((Rva00148F5ECache *)&TheKey_skirmishDifficulty)->get(), 3); break;
			}
		}

		d.setInt(((Rva00148F5ECache *)&TheKey_livingWorldPlayerID)->get(), slot->m_livingWorldPlayerID);

		TheSidesList->findSideInfo(name);
		TheSidesList->addSide(&d);

		AsciiString teamName;
		teamName = "team";
		teamName.concat(name);
		d.clear();
		d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get(), teamName);
		d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get(), name);
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
extern class MessageStream *TheMessageStream;

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
							GameMessage *out = TheMessageStream->appendMessage(0x44a);
							out->appendIntegerArgument(crc);
							out->appendTimestampArgument(m_38);
							out->appendTimestampArgument(m_40);
							out->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
							out->appendBooleanArgument(true);
						}
						else if (message && !forced)
							message->appendBooleanArgument(true);
					}
					TheMessageStream->propagateMessages();
					if (TheNetwork)
						TheNetwork->slot3C(0);
				}
				for (; m_4c != m_50.end(); ++m_4c)
				{
					rva002401DD((BfmeThingEC *)*m_4c, frame, player);
					if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK)
					{
						GameMessage *out = TheMessageStream->appendMessage(0x44a);
						out->appendIntegerArgument(crc);
						out->appendTimestampArgument(m_38);
						out->appendTimestampArgument(m_40);
						out->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
						out->appendBooleanArgument(true);
						TheMessageStream->propagateMessages();
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

// Inside the 0x009FE7A8 data block: the last formatted player template name.
char g_Va00DFE840[256] = { 0 };
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

// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z @0x002401DD 1424B = the
// desync reporter GameLogic::setSawCRCMismatch (WorldBuilder twin 0xD0CA20,
// called from ProcessCRC). Records the mismatch once (recorder log, closes the
// script windows, desync message box outside a forced playback desync, script
// engine copy), then writes DESYNC-<frame>-<map>-<player>.txt from the CRC
// stream and, under TheBinaryDeepCRC, BIN_DESYNC-....bin. The recorder test
// keeps WorldBuilder's if/else with 'm_1b8 = 0' in both arms: the compiler
// tail-merges the two stores, which confines the zero register to the m_1bc
// block as retail does. Retail folds "" with StringBase<char>'s function-local
// TheNullChr (0x7BAC1C), so every str() here goes through StringBase<char>.
class ScriptActions;
class ScriptActionsWindowView
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e();
	virtual void closeWindows(bool suppressNewWindows);                  // +0x3C
};
extern ScriptActions *TheScriptActions;

class Rva002036B4GlobalCopier
{
public:
	void apply(void);
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
File *createMemoryReadFile(char *buffer, int size);
bool Rva0060DFB5(File *input, File *output);

extern "C" __declspec(dllimport) int __stdcall GetComputerNameA(char *buffer, unsigned long *size);

bool g_fakeDesync = false;
extern bool TheBinaryDeepCRC;

// --- body_r1.inc ---
static inline const char *nullChrStr(const AsciiString &s)
{
	return ((const StringBase<char> &)s).str();
}

void GameLogic::rva002401DD(BfmeThingEC *stream, unsigned int frame, int player)
{
	m_71 = true;
	if (ignoreCRCMismatches && g_value12A6F38 != m_40)
		return;
	if (!m_1bc)
	{
		m_1bc = true;
		TheRecorder->logCRCMismatch();
		((ScriptActionsWindowView *)TheScriptActions)->closeWindows(true);
		if (TheRecorder && TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK && g_value12A6F38 != m_40)
		{
			m_1b8 = 0;
		}
		else
		{
			Rva00437E84(4, TheGameText->fetch("GUI:DesyncTitle"), TheGameText->fetch("GUI:DesyncText"));
			m_1b8 = 0;
		}
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	}
	if (!stream)
		return;

	const char *map = ((const StringBase<char> &)TheWritableGlobalData->m_mapName).reverseFind('\\');
	if (!map)
		map = "";
	else
		++map;

	AsciiString playerName = ThePlayerList->getLocalPlayer()->m_4c;
	if (playerName.isEmpty())
	{
		char computerName[256] = { 0 };
		unsigned long size = 256;
		GetComputerNameA(computerName, &size);
		playerName = computerName;
	}

	AsciiString frameName;
	if (nullChrStr(stream->m_04))
		frameName.format("Frame%s", nullChrStr(stream->m_04));
	else
		frameName.format("Frame%d", frame);

	AsciiString filename;
	if (frame > 0)
		filename.format("DESYNC-%s-%s-%s.txt", nullChrStr(frameName), map, nullChrStr(playerName));
	else
		filename.format("DESYNC-%s-%s.txt", map, nullChrStr(playerName));

	File *output = TheFileSystem->openFile(nullChrStr(filename), 0x2a, 0);
	if (!output)
		return;

	int size;
	char *buffer = (char *)stream->bfmeTakeEC(&size);
	File *input = createMemoryReadFile(buffer, size);
	if (!input)
		return;

	AsciiString text;
	if (frame > 0)
	{
		if (g_fakeDesync)
			text.format("*** Frame #%d -- THIS IS A FAKE DESYNC THAT WAS TRIGGERED INTENTIONALLY BY THIS PLAYER! IGNORE!\n\n", frame);
		else if (g_value12A6F38 == m_40)
			text.format("*** Frame #%d -- THIS IS A FORCED DESYNC TRIGGERED ON FRAME %d USING COMMANDLINE -forceDesyncOnFrame %d! IGNORE!!!!\n\n", frame, m_40);
		else
			text.format("Frame #%d\n\n", frame);
		output->write(nullChrStr(text), text.getLength());
	}
	text = m_54;
	output->write(nullChrStr(text), text.getLength());
	for (unsigned int i = 0; i < m_58.size(); ++i)
	{
		text = rva0023FB58(i);
		output->write(nullChrStr(text), text.getLength());
	}
	text = m_64;
	output->write(nullChrStr(text), text.getLength());
	text = m_68;
	output->write(nullChrStr(text), text.getLength());
	text.format("\n");
	output->write(nullChrStr(text), text.getLength());
	text.format("\n--------------------------------------------------------\nREPLAY FILE\n---------------------------------------------------------\n");
	output->write(nullChrStr(text), text.getLength());
	TheRecorder->dumpCommandHistory((CommandDumpFile0037BE15 *)output, frame);
	text.format("---------------------------------------------------------\n\n");
	output->write(nullChrStr(text), text.getLength());
	Rva0060DFB5(input, output);
	input->close();
	output->close();
	if (TheBinaryDeepCRC)
	{
		if (frame > 0)
			filename.format("BIN_DESYNC-%s-%s-%s.bin", nullChrStr(frameName), map, nullChrStr(playerName));
		else
			filename.format("BIN_DESYNC-%s-%s.bin", map, nullChrStr(playerName));
		File *binFile = TheFileSystem->openFile(nullChrStr(filename), 0x4a, 0);
		if (!binFile)
			return;
		binFile->write(buffer, size);
		binFile->close();
	}
	free(buffer);
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

// Bind the close calls to the existing whole 45-byte provider at RVA 0x0060C8CD.
class Gen009D6DD0 { public: void bfmeClose(); };

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
// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)
extern bool TheDeepCRC;
extern bool TheLiteCRC;
// Owned here: toggled around the lite-CRC computation below; retail .data
// starts it at 0 (VA 0x00A02D87).
bool TheLiteCRC = false;
extern "C" void *theLogicRandomLogFile;
extern GlobalWeatherSystem *TheGlobalWeatherSystem;
class BuildAssistant;
extern BuildAssistant *TheBuildAssistant;
extern WeaponStore *TheWeaponStore;
extern LocomotorStore *TheLocomotorStore;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;
extern void *TheMineshaftPortalNetworkManager;
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

	if (*(bool *)&g_00DFE7A8 && first)
		((Rva002431CB *)&g_00DFE7A8)->rva002431CB();

	if (first && getFrame() == 2 && g_00DFE1C8->rva00210DC9()
		&& ((Rva0023C666 *)TheGameLogic)->rva0023C666()) {
		for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (ai && ai->isMoving())
				ai->destroyPath();
		}
	}

	TheAI->pathfinder()->ProcessPathfindQueue();
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
			GameMessage *msg = TheMessageStream->appendMessage(0x44a);
			msg->appendIntegerArgument(crc);
			msg->appendTimestampArgument(m_38);
			msg->appendTimestampArgument(getFrame());
			msg->appendBooleanArgument(TheRecorder->getMode() == RECORDERMODETYPE_PLAYBACK);
			if (!TheDeepCRC && !TheLiteCRC)
				msg->appendBooleanArgument(false);
			else
				ProcessCRC(crc, player, m_40, msg, false, stream);
		}
		if (theLogicRandomLogFile)
			((Rva002CEC0A *)theLogicRandomLogFile)->rva002CEC34();
	}

	if (g_00E032F8 && first)
		((StatsCollector *)g_00E032F8)->update();

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
		((SubsystemInterface *)TheTaintManager)->update();
		((Rva00A027B8 *)TheBuildAssistant)->update();
		TheLargeGroupAudio->update();
		processDestroyList();
		TheWeaponStore->update();
		TheLocomotorStore->update();
		((Rva00E03138 *)TheVictoryConditions)->update();
		TheDelayedExperienceLevelGrantSystem->update();
		((Rva0040CA98 *)&m_184)->rva0040CA98();
		TheSkirmishAIManager->update();
		((SubsystemInterface *)TheMineshaftPortalNetworkManager)->update();
		TheTeamFactory->update();
	}

	if (rva0042219() && m_40 == 0x400 && !CopyProtect::rva00232D38()) {
		GameMessage *msg = TheMessageStream->appendMessage(0x448);
		msg->appendBooleanArgument(false);
	}

	if (first) {
		for (Object *obj = m_objList; obj; obj = obj->getNextObject()) {
			if (obj->isDisabled_())
				obj->checkDisabledStatus();
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
					_mbscpy(reinterpret_cast<unsigned char *>(path), reinterpret_cast<const unsigned char *>(TheWritableGlobalData->m_mapName.str()));
					int length = strlen(path);
					if (length >= 4) {
						char *p = path + length - 4;
						while (p > path && *p != '\\' && *p != '/')
							--p;
						*p = 0;
						_mbscat(reinterpret_cast<unsigned char *>(path), reinterpret_cast<const unsigned char *>("\\scenecapture.dat"));
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
							((Gen009D6DD0 *)&xfer)->bfmeClose();
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

// Native23E99A..23EE5B complete RET; WB CF3EA0 names CreateWOTRMPPlayers.
// The matched CreateMPPlayers pass supplies existing Dict/key/slot/team APIs.
// Target globals independently identify PlayerList DFEEE8 / SidesList E01D58 /
// TeamFactory E028BC and the established opaque subsystem E03138.
// Target adds three subsystem resets, marks every slot at1A4, drops linked
// nonfinal teams and uses index names; faction/team/color settings keep the
// independently verified provider calls of the existing player builder.
struct Rva0023E99ASlotFlag { char prefix[0x1a4]; bool flag; };
void GameLogic::CreateWOTRMPPlayers()
{
 if(!TheGameInfo) return;
 GameInfo *game=TheGameInfo;
 ThePlayerList->reset();
 ((SubsystemInterface*)TheSidesList)->reset();
 TheTeamFactory->reset();
 for(int i=0;i<8;++i) ((Rva0023E99ASlotFlag*)game->getSlot(i))->flag=true;
 int teamID=TheSidesList->getTeamInfo()->getNode(0)->m_previous;
 while(teamID){
  int next=TheSidesList->getTeamInfo()->getNode(teamID)->m_previous;
  if(TheSidesList->getTeamInfo()->getNode(teamID)->m_chainPrevious)
   TheSidesList->getTeamInfo()->removeTeam(teamID);
  teamID=next;
 }
 for(int i=0;i<8;++i){
  GameSlot *slot=game->getSlot(i);
  if(!slot||!slot->isOccupied()||m_114==3)continue;
  AsciiString playerName;
  if(slot->getPlayerTemplate()>=0)playerName.format("Player_%d",i+1);else playerName.format("Observer_%d",i+1);
  slot->m_34=playerName;
 }
 for(int i=0;i<8;++i){
  GameSlot *slot=game->getSlot(i);
  if(!slot||!slot->isOccupied())continue;
  Dict d;d.clear();
  const AsciiString &name=slot->m_34;
  d.setAsciiString(((Rva00148F5ECache *)&TheKey_playerName)->get(),name);
  d.setBool(cacheKey(TheKey_playerIsHuman),slot->isHuman());
  d.setUnicodeString(TheKey_playerDisplayName.get(),slot->m_name);
  const PlayerTemplate *pt;
  if(slot->getPlayerTemplate()>=0)pt=ThePlayerTemplateStore->getNthPlayerTemplate(slot->getPlayerTemplate());
  else pt=ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
  if(pt)d.setAsciiString(cacheKey(TheKey_playerFaction),TheNameKeyGenerator->keyToName(pt->getNameKey()));
  if(game->isPlayerPreorder(i))d.setBool(((Rva00148F5ECache *)&TheKey_playerIsPreorder)->get(),true);
  AsciiString enemiesString;
  AsciiString alliesString;
  int team=slot->getTeamNumber();
  for(int j=0;j<8;++j){
   GameSlot *other=game->getSlot(j);
   if(i==j||!other->isOccupied())continue;
   const AsciiString &otherName=other->m_34;
   bool isEnemy=team==-1||other->getTeamNumber()!=team;
   if(isEnemy){
    if(!enemiesString.isEmpty())enemiesString.concat(" ");
    enemiesString.concat(otherName);
   }else{
    if(!alliesString.isEmpty())alliesString.concat(" ");
    alliesString.concat(otherName);
   }
  }
  d.setAsciiString(TheKey_playerAllies.get(),alliesString);
  d.setAsciiString(TheKey_playerEnemies.get(),enemiesString);
  d.setInt(((Rva00148F5ECache *)&TheKey_playerHandicap)->get(),slot->m_bfme20);
  d.setInt(((Rva00148F5ECache *)&TheKey_playerColor)->get(),TheMultiplayerSettings->getColor(slot->getColor())->getColor());
  d.setInt(((Rva00148F5ECache *)&TheKey_playerNightColor)->get(),TheMultiplayerSettings->getColor(slot->getColor())->getNightColor());
  d.setBool(((Rva00148F5ECache *)&TheKey_multiplayerIsLocal)->get(),slot->isHuman()&&slot->m_name.compare(game->getSlot(game->getLocalSlotNum())->getNameStr())==0);
  d.setInt(((Rva00148F5ECache*)&TheKey_livingWorldPlayerID)->get(),slot->m_livingWorldPlayerID);
  TheSidesList->findSideInfo(name);
  TheSidesList->addSide(&d);
  AsciiString teamName;
  teamName="team";
  teamName.concat(name);
  d.clear();
  d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamName)->get(),teamName);
  d.setAsciiString(((Rva00148F5ECache *)&TheKey_teamOwner)->get(),name);
  d.setBool(TheKey_teamIsSingleton.get(),true);
  TheSidesList->addTeam(&d);
 }
 ((Rva00E03138 *)TheVictoryConditions)->reset();
 TheTeamFactory->reset();
 ThePlayerList->p0e();
 ((Rva00E03138 *)TheVictoryConditions)->slot44();
}

// Retail 0x0023DD48, 796 bytes: the load screen the game mode picks (the
// target mode is at +0x110 with an eight-entry jump table; the window
// manager's +0x31C flag selects the shell variant for modes 4 and 7). The
// default single-player screen (Rva0035615D, 0x28 bytes) takes the
// +0x84/+0x88/+0x8C strings unless loading a save, in mode 3, or the image
// name is empty, in which case it takes a fresh image (0x0023D614) and default
// or audio-settings (+0xA0 of TheAudio slot 0x138's result) string handles;
// modes 1/2/5 use the Apt load screen (0xD4 bytes, constructed with the mode)
// when +0x114 is set. Names are unknown: the strings at +0x7C..+0x8C are read
// through casts and the screens keep their addresses.
// The whole body sits in a tautology on the mode (no bytes): it gives retail's
// block layout instead of cl's default.
#include "../../../Include/Common/BfmeAudioEventPrefix136.h"
class Rva0036CA00Str
{
public:
	__forceinline Rva0036CA00Str() : m_ref(0) {}
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};
class Rva0043A278
{
public:
	Rva0043A278();
private:
	char m_storage[0x10];
};
class Rva003560ED
{
public:
	Rva003560ED(const AsciiString &a, const AsciiString &b);
private:
	char m_storage[0x18];
};
class Rva0035615D
{
public:
	Rva0035615D(const AsciiString &a, const Rva0036CA00Str &b, const Rva0036CA00Str &c, bool d);
private:
	char m_storage[0x28];
};
class AptLoadScreen
{
public:
	AptLoadScreen(void *mode);
private:
	char m_storage[0xD4];
};
void Rva0023D614Set(StringBase<char> *image);
class BfmeAptWindowManagerLS
{
public:
	char m_pad[0x31C];
	void *m_31c;
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva0023DD48AudioSettings
{
	char m_pad[0xA0];
	Rva0036CA00Str m_loadScreenMusic;
};
class Rva0023DD48AudioView
{
public:
#define X1_V(n) virtual void slot##n();
	X1_V(00) X1_V(01) X1_V(02) X1_V(03) X1_V(04) X1_V(05) X1_V(06) X1_V(07) X1_V(08) X1_V(09)
	X1_V(10) X1_V(11) X1_V(12) X1_V(13) X1_V(14) X1_V(15) X1_V(16) X1_V(17) X1_V(18) X1_V(19)
	X1_V(20) X1_V(21) X1_V(22) X1_V(23) X1_V(24) X1_V(25) X1_V(26) X1_V(27) X1_V(28) X1_V(29)
	X1_V(30) X1_V(31) X1_V(32) X1_V(33) X1_V(34) X1_V(35) X1_V(36) X1_V(37) X1_V(38) X1_V(39)
	X1_V(40) X1_V(41) X1_V(42) X1_V(43) X1_V(44) X1_V(45) X1_V(46) X1_V(47) X1_V(48) X1_V(49)
	X1_V(50) X1_V(51) X1_V(52) X1_V(53) X1_V(54) X1_V(55) X1_V(56) X1_V(57) X1_V(58) X1_V(59)
	X1_V(60) X1_V(61) X1_V(62) X1_V(63) X1_V(64) X1_V(65) X1_V(66) X1_V(67) X1_V(68) X1_V(69)
	X1_V(70) X1_V(71) X1_V(72) X1_V(73) X1_V(74) X1_V(75) X1_V(76) X1_V(77)
#undef X1_V
	virtual Rva0023DD48AudioSettings *getAudioSettings();
};

#define LS_STR(off) (*(AsciiString *)((char *)this + (off)))
#define LS_MODE ((unsigned int)m_110)
LoadScreen *GameLogic::getLoadScreen(bool loadingSaveGame)
{
if ((LS_MODE != 0 || LS_MODE == 0)) {
	switch (LS_MODE)
	{
	case 4:
		if (((BfmeAptWindowManagerLS *)g_bfmeAptWindowManager)->m_31c)
			return (LoadScreen *)new Rva0043A278;
		return (LoadScreen *)new Rva003560ED((const AsciiString &)LS_STR(0x7C), (const AsciiString &)LS_STR(0x80));

	case 7:
		if (((BfmeAptWindowManagerLS *)g_bfmeAptWindowManager)->m_31c)
		{
			AsciiString image;
			Rva0023D614Set((StringBase<char> *)&image);
			return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(), Rva0036CA00Str(), true);
		}
		return (LoadScreen *)new Rva003560ED((const AsciiString &)LS_STR(0x7C), (const AsciiString &)LS_STR(0x80));

	case 0:
	case 3:
	case 6:
		if (loadingSaveGame || LS_MODE == 3 ||
			((const StringBase<char> *)&LS_STR(0x84))->isEmpty())
		{
			AsciiString image;
			Rva0023D614Set((StringBase<char> *)&image);
			return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(),
				((Rva0023DD48AudioView *)TheAudio)->getAudioSettings()->m_loadScreenMusic, false);
		}
		return (LoadScreen *)new Rva0035615D(LS_STR(0x84),
			*(const Rva0036CA00Str *)&LS_STR(0x88), *(const Rva0036CA00Str *)&LS_STR(0x8C), false);

	case 1:
	case 2:
	case 5:
		if (m_114 == 0)
		{
			if (loadingSaveGame || ((const StringBase<char> *)&LS_STR(0x84))->isEmpty())
			{
				AsciiString image;
				Rva0023D614Set((StringBase<char> *)&image);
				return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(),
					((Rva0023DD48AudioView *)TheAudio)->getAudioSettings()->m_loadScreenMusic, false);
			}
			return (LoadScreen *)new Rva0035615D(LS_STR(0x84),
				*(const Rva0036CA00Str *)&LS_STR(0x88), *(const Rva0036CA00Str *)&LS_STR(0x8C), false);
		}
		return (LoadScreen *)new AptLoadScreen((void *)LS_MODE);
	}
	return 0;
}
}
#undef LS_STR
#undef LS_MODE

// GameLogic::loadAllObjects, retail 0x00244D56..0x0024555A (2052 bytes).
// WorldBuilder 0x00D00E20 names this routine and shows the same prop/object
// split and the if(obj) scope. Retail calls validateTeam at 0x002A851D and
// supplies the same two-pointer created-object records consumed by the callers.
// Donor: BFME 1 GameLogic.cpp and WWMath/matrix3d.h at
// cee35b7d8ca077d7255f1c39cb69e9fd9627aa85; target offsets and all callees are
// established independently from the retail body. EH states own AssetList
// at EBP-0x94 and originalOwner at EBP-0x30. The object guard must retain its
// lexical scope even though the initial rejection guards are early continues.
struct BfmeE8 { int a, b; };
// Retail's push_back calls the no-EH provider 0x00057C80; spell its
// algorithm out so this TU's copy is that provider instead of an EH copy.
namespace _STL {
template<> inline void vector<BfmeE8>::_M_insert_overflow(
    pointer position, const BfmeE8 &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}
class GameClient { public: void rva0023B383(Dict *, ThingTemplate *, const Coord3D *); };
extern "C" int (__cdecl * const _imp__strncmp)(const char *s1, const char *s2, unsigned int count);
class Rva0028CBFD
{
public:
	void rva0028CBFD(void);
};
class Rva0033A68A
{
public:
	Overridable *rva0033A68A(void);
};
static __forceinline const ThingTemplate *finalOverride(const ThingTemplate *tt)
{
	return (const ThingTemplate *)((Rva0033A68A *)tt)->rva0033A68A();
}
class Team
{
public:
	void setActive(void)
	{
		if (!m_active) {
			m_created = true;
			m_active = true;
		}
	}
	unsigned int getID(void) const { return m_id; }
private:
	char m_pad00[0x34];
	unsigned int m_id;                                                   // +0x34
	char m_pad38[0x5d - 0x38];
	bool m_active;
	bool m_created;
};
extern const StaticNameKey TheKey_objectName;
extern Rva00148F5ECache TheKey_objectPrototypeScale;
StaticNameKey TheKey_alignToTerrain = { 0, "alignToTerrain" };
extern const StaticNameKey TheKey_originalOwner;
float normalizeAngle(float angle);
void alignToTerrain(float angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);
void GameLogic::loadAllObjects(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
                               const KindOfType *requireKind, bool dontCreate)
{
	bool useTrees = true;
	const ThingTemplate *treeA = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[0]);
	const ThingTemplate *treeB = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[1]);
	if (treeB == 0)
		treeA = 0;
	const ThingTemplate *treeC = TheThingFactory->findTemplate(TheAI->getAiData()->m_treeName[2]);
	if (treeC == 0)
		treeA = 0;
	bool useOverrides = false;
	bool multiplayer = TheRecorder->isMultiplayer();
	if (TheGameLogic->m_110 == 2)
		multiplayer = false;
	if (!multiplayer) {
		if (TheAI->getAiData()->m_d8 && TheGameLODManager->get1774() <= 0 && treeA) {
			useOverrides = true;
			treeA = finalOverride(treeA);
			treeB = finalOverride(treeB);
			treeC = finalOverride(treeC);
		}
		useTrees = !TheAI->getAiData()->m_ec;
	}
	AssetList assets;
	int count = 0;
	for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_head; pMapObj; pMapObj = pMapObj->getNext_()) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		if (pMapObj->getFlags() & 0x36)
			continue;
		const ThingTemplate *thingTemplate = pMapObj->getThingTemplate();
		if (thingTemplate == 0)
			continue;
		if (thingTemplate->m_5e5)
			continue;
		if (excludeKind && (char)thingTemplate->isKindOf(*excludeKind))
			continue;
		if (requireKind && !(char)thingTemplate->isKindOf(*requireKind))
			continue;
		if ((thingTemplate->m_108 & 0x40) && !useTrees)
			continue;
		const Coord3D *loc = pMapObj->getLocation();
		Coord3D pos;
		pos.x = loc->x;
		pos.y = loc->y;
		pos.z = loc->z;
		pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
		float angle = normalizeAngle(pMapObj->getAngle());
		bool isProp = (thingTemplate->m_kindof[2] >> 4) & 1;
		if ((thingTemplate->m_kindof[0] & 0x80000) && thingTemplate->m_fenceWidth == 0.0f)
			isProp = true;
		bool unnamed = false;
		if (thingTemplate->m_120 & 1) {
			bool exists;
			AsciiString name = pMapObj->getProperties()->getAsciiString(staticKey(TheKey_objectName), &exists);
			if (!exists || name.isEmpty())
				unnamed = true;
		}
		if (isProp || unnamed || (thingTemplate->m_kindof[1] & 0xc0000000)) {
			Dict *props = pMapObj->getProperties();
			bool hasScale;
			float scale = props->getReal(TheKey_objectPrototypeScale.get(), &hasScale);
			Matrix3D mtx(true);
			bool align;
			if (props->getBool(staticKey(TheKey_alignToTerrain), &align) && align) {
				Coord3D normal;
				TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
				Coord3D zero;
				zero.x = 0.0f;
				zero.y = 0.0f;
				zero.z = 0.0f;
				alignToTerrain(angle, zero, normal, mtx);
			} else {
				mtx.Rotate_Z(pMapObj->getAngle());
			}
			float propScale = thingTemplate->m_4e0;
			if (hasScale)
				propScale *= scale;
			AssetLoadMode mode;
			((ThingTemplate *)thingTemplate)->GetAssetList((int)&assets, (int)&mode);
			if (++count == 20) {
				count = 0;
				bfmeMergeReceiverKeys((int)&assets);
				assets.clear();
			}
			if (dontCreate)
				continue;
			if (thingTemplate->m_kindof[1] & 0x40000000) {
				if (treeA && useOverrides) {
					if (thingTemplate->m_5eb && thingTemplate->m_5ec)
						thingTemplate = treeA;
					else if (!thingTemplate->m_5eb && thingTemplate->m_5ec)
						thingTemplate = treeB;
					else
						thingTemplate = treeC;
					propScale = TheAI->getAiData()->m_treeScale;
				}
				if (useTrees)
					TheTerrainLogic->addTree(thingTemplate, &pos, &mtx, propScale);
			} else if (thingTemplate->m_kindof[1] & 0x80000000) {
				TheTerrainLogic->rva00280176(thingTemplate, &pos, &mtx, propScale);
			} else if (unnamed) {
				((GameClient *)TheGameClient)->rva0023B383(props, (ThingTemplate *)thingTemplate, &pos);
			} else {
				TheTerrainLogic->rva0027D3D9(thingTemplate, &pos, &mtx, propScale);
			}
		} else {
			Dict *props = pMapObj->getProperties();
			AsciiString originalOwner = props->getAsciiString(staticKey(TheKey_originalOwner));
			Team *team = ThePlayerList->validateTeam(originalOwner, pMapObj);
			if (ThePlayerList->getNeutralPlayer()->getDefaultTeam() == team
			    && _imp__strncmp("Player_", originalOwner.str(), 7) == 0
			    && !(thingTemplate->m_120 & 0x20000))
				continue;
			AssetLoadMode mode;
			((ThingTemplate *)thingTemplate)->GetAssetList((int)&assets, (int)&mode);
			if (++count == 20) {
				count = 0;
				bfmeMergeReceiverKeys((int)&assets);
				assets.clear();
			}
			if (dontCreate)
				continue;
			CreateMask mask;
			Object *obj = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
			if (obj) {

				if ((pMapObj->getFlags() & 1) || (obj->getTemplate()->m_108 & 0x20)) {
					Drawable *draw = obj->getDrawable();
					if (draw)
						draw->setDrawableStatus(1);
				}
				bool align;
				if (props->getBool(staticKey(TheKey_alignToTerrain), &align) && align) {
					Coord3D zero;
					zero.x = 0.0f;
					zero.y = 0.0f;
					zero.z = 0.0f;
					Coord3D normal;
					TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND, &normal, true);
					Matrix3D mtx;
					alignToTerrain(angle, zero, normal, mtx);
					obj->setTransformMatrix(&mtx);
				} else {
					obj->setOrientation(angle);
				}
				obj->setPosition(&pos);
				obj->updateObjValuesFromMapProperties(props);
				obj->setLayer(TheTerrainLogic->getLayerForDestination(obj, &pos));
				Rva0134FAA0->slot28();
				bfmeReleaseQueuedDeviceInterfaces();
				((Rva0028CBFD *)obj)->rva0028CBFD();
				team->setActive();
				TheAI->pathfinder()->AddObjectToPathfindMap(obj);
				Rva0024622FEntry entry;
				entry.obj = obj;
				// Keep the native map-object spill at this vector insertion.
				entry.mapObj = *(MapObject *volatile *)&pMapObj;
				((_STL::vector<BfmeE8> *)created)->push_back(*(const BfmeE8 *)&entry);
			}
		}
	}
	bfmeMergeReceiverKeys((int)&assets);
}

// ?rva0024622F@GameLogic@@QAEX_N@Z
// @0x0024622F 499B (ret 4 at 0x0024641F; caller 0x00246E74).
// Target evidence: the body walks the map object list skipping flagged
// objects (0x36), template-less objects and templates whose +0x5E5 flag is
// clear. Each survivor's template is announced to a fresh asset list
// (notify 0x0033CF34, merge 0x0061F010); unless the flag argument is set it
// is created through 0x002D0A23 on the neutral player's default team,
// dropped to the ground (TerrainLogic +0x18), oriented by normalizeAngle,
// positioned, passed to TerrainLogic +0xBC, recorded with its map object
// and given the map properties (0x002951AB). The rest of the map objects
// follow through loadAllObjects (0x00244D56) restricted to kind 0x3C, then every recorded
// object gets 0x00293E64 with its map properties. Donor: BFME 1
// GameLogic::startNewGame's bridge pass ("Special case, load any bridge map
// objects": isBridge, neutral default team, getGroundHeight, normalizeAngle,
// setOrientation, setPosition, addLandmarkBridgeToLogic). BFME 2 split it
// into this helper; the helper names stay address names.
// Keep the two nested creation scopes: with the real loadAllObjects visible,
// these reproduce retail's EBX object lifetime and unescaped created vector.
void GameLogic::rva0024622F(bool dontCreate)
{
	_STL::vector<Rva0024622FEntry> created;
	for (MapObject *pMapObj = BfmeTheMapObjectListHolder->m_head; pMapObj; pMapObj = pMapObj->getNext_()) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();

		if (pMapObj->getFlags() & 0x36)
			continue;

		const ThingTemplate *thingTemplate = pMapObj->getThingTemplate();
		if (thingTemplate == 0)
			continue;
		if (!thingTemplate->m_5e5)
			continue;

		AssetLoadMode mode;
		AssetList assets;
		((ThingTemplate *)thingTemplate)->GetAssetList((int)&assets, (int)&mode);
		bfmeMergeReceiverKeys((int)&assets);
		if (!dontCreate) {
			Team *team = ThePlayerList->getNeutralPlayer()->getDefaultTeam();
			CreateMask mask;
			Object *obj = TheThingFactory->newObject(thingTemplate, team, &mask, (ObjectID)0);
			if (obj) {
				const Coord3D *loc = pMapObj->getLocation();
				Coord3D pos;
				pos.x = loc->x;
				pos.y = loc->y;
				pos.z = loc->z;
				pos.z += TheTerrainLogic->getGroundHeight(pos.x, pos.y);
				obj->setOrientation(normalizeAngle(pMapObj->getAngle()));
				obj->setPosition(&pos);
				if (thingTemplate->m_5e5)
					TheTerrainLogic->addLandmarkBridgeToLogic(obj);

				Rva0024622FEntry entry;
				entry.obj = obj;
				entry.mapObj = pMapObj;
				created.push_back(entry);
				obj->updateObjValuesFromMapProperties(pMapObj->getProperties());
			}
		}
	}

	{
		KindOfType kind = (KindOfType)0x3c;
		loadAllObjects(&created, 0, &kind, dontCreate);
	}

	for (Rva0024622FEntry *it = created.begin(); it != created.end(); ++it) {
		Rva0134FAA0->slot28();
		bfmeReleaseQueuedDeviceInterfaces();
		it->obj->rva00293E64(it->mapObj->getProperties());
	}
}

// ?rva0024004D@GameLogic@@QAEX_N@Z @0x0024004D 247B (ebp frame without EH,
// ret 4; next body 0x00240144). Called from the new-game pass 0x00248558.
// Target evidence: unless +0x72 or +0x78 is set or the Apt window manager's
// +0x31C is non-zero, TheTransitionHandler takes the "FadeWholeScreen"
// group (rowed setGroup 0x001DC252) and waits (0x001DC5EC); GlobalData
// +0xAF5 is cleared and 0x00376D49 runs; when TheDisplay's virtual +0x114
// holds, the load screen at +0x120 is polled through its virtual +0x14 with
// Sleep(5). In modes 2, 1 and 5 (+0x110) a timed operation is queued through
// the rowed registry 0x003FE7E6 with a callback built by the holder
// constructor 0x0023E8AC from an empty local functor and the id slot
// 0x00E02EC4; the load screen's +0x0C flag is cleared, 98.0 goes to the
// float at 0x00DFE788 and TheAudio's virtual +0xF0 gets (0.0, true).
// Donor (semantic guide only): BFME 1 GameLogic.cpp startNewGame's closing
// steps (fade-in transition, load-screen wait); names stay offset names.
class Bfme5RefHolderA
{
public:
	Bfme5RefHolderA(int unused);
	void *m_bfmeNode;
};

struct Rva0024004DFunctor
{
};

class Rva00211E75Callback : public Bfme5RefHolderA
{
public:
	Rva00211E75Callback(const Rva0024004DFunctor &functor) : Bfme5RefHolderA((int)&functor) {}
	Rva00211E75Callback(Rva0023E323 value);
	Rva00211E75Callback(const Rva00211E75Callback &other);
};

bool Rva003FE7E6(Rva00211E75Callback callback, int *id);

class Rva0024004DDisplayView
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
	virtual void v44();
	virtual bool v45(void);                                              // +0x114
};

class Rva0024004DLoadScreenView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04();
	virtual bool v05(void);                                              // +0x14
	char m_pad04[0xc - 0x4];
	bool m_c;
};

class Rva0024004DAudioView
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
	virtual void v3c(float value, bool flag);                            // +0xF0
};

extern int g_00E02EC4;
static float g_00DFE788;


void GameLogic::rva0024004D(bool loadingSaveGame)
{
	if (!m_72 && !m_78 && !((BfmeAptWindowManagerLS *)g_bfmeAptWindowManager)->m_31c) {
		TheTransitionHandler->setGroup(AsciiString("FadeWholeScreen"));
		TheTransitionHandler->rva001DC5EC();
	}
	TheWritableGlobalData->m_af5 = false;
	rva00376D49();

	if (((Rva0024004DDisplayView *)TheDisplay)->v45() && m_120) {
		while (!((Rva0024004DLoadScreenView *)m_120)->v05())
			Sleep(5);
	}

	if (m_110 == 2 || m_110 == 1 || m_110 == 5) {
		// Retail passes EBP-4, independently of the empty functor's sizeof.
		// Align this local storage; giving the class a four-byte payload or
		// class alignment changes its temporary-slot sharing instead.
		__declspec(align(4)) Rva0024004DFunctor functor;
		Rva003FE7E6(Rva00211E75Callback(functor), &g_00E02EC4);
		if (m_120)
			((Rva0024004DLoadScreenView *)m_120)->m_c = false;
		g_00DFE788 = 98.0f;
		((Rva0024004DAudioView *)TheAudio)->v3c(0.0f, true);
	}
}

// ?rva002423E3@GameLogic@@QAE_NXZ @0x002423E3 1436B (SEH; every exit is
// mov al,1). Called once per client-subsystem update 0x00225C12, which
// ignores the result. Target evidence: while +0x9C is set it pumps the
// engine (+0x5C); in modes 1, 5 and 2 of a network game it reports load
// progress (0x0023C7BB) for the first five frames, stepping the float at
// 0x00DFE788 by 0.25, and answers early. Otherwise it clears +0x9C and,
// with a load screen (+0x120) on a display whose +0x114 holds, fades the
// screen through TheTransitionHandler's "FadeWholeScreen" group by mode
// (+0x110): a saved game (+0x9E) fades out under the handler lock, modes
// 2/3 and 0/6 queue the timed reverse 0x0023E323 through the event
// sequencer 0x003FE7E6, 0/6 also plays the movie at +0x74 (Display +0x10C),
// and 4/7 waits unless the Apt window manager's +0x31C is set. It then
// deletes the load screen (0x0023C7D2), shows the cursor, sets the audio
// mode from 0x001DCD1C and clears the +0x84 string and its two handles
// (0x0023DCCE) and the +0x?? string (0x0023DC8E). WB 0x00CFF490 is the
// identity lead; BFME 1 (deleteLoadScreen, naked dump only) and Zero Hour
// (deleteLoadScreen is 0x0023C7D2 here) guide purpose only.
class Rva001DBB82OneSetter
{
public:
	void enable(void);
};

class W3DDisplay
{
public:
	void rva0025D2F6(void);
};

class Rva00222A8BTarget
{
public:
	void rva00222F55(bool flag);
	char m_pad[0x31C];
	int m_31c;
};

// The handle and holder operations of 0x00239099 / 0x000A8C9B stay visible
// (out of line) so the unit knows 0x0023DCCE keeps no pointer to the
// caller's empty handles: retail releases neither temporary on the normal
// path.
struct OpaqueRefCountView
{
	void *m_vtbl;
	long m_refs;
};

inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
	if (this != &other) {
		if (other.referent)
			InterlockedIncrement(&((OpaqueRefCountView *)other.referent)->m_refs);
		if (referent)
			referent->Release_Ref();
		referent = other.referent;
	}
	return *this;
}

inline __declspec(noinline) void Rva000A8C9B::clear(void)
{
	OpaqueRefCounted *&ptr = *(OpaqueRefCounted **)this;
	if (ptr) {
		ptr->Release_Ref();
		ptr = 0;
	}
}

struct Rva002423E3NullRef : public OpaqueRefElement4
{
	Rva002423E3NullRef() { referent = 0; }
	~Rva002423E3NullRef() { if (referent) referent->Release_Ref(); }
};

// GameLogic's conditional string-and-handles setter 0x0023DCCE. Retail emits the
// body as an inline COMDAT in GameLogic's unit (it sits at 0x0023DCCE); this TU
// is that home and the caller at 0x002423E3 inlines the same body.
class Rva0023DCCE
{
public:
	void rva0023DCCE(const AsciiString &a, const OpaqueRefElement4 &b, const OpaqueRefElement4 &c)
	{
		if (((const StringBase<char> *)&a)->isEmpty() || TheWritableGlobalData->m_9ad)
		{
			m_flag = 0;
			// Retail's clear is the StringBase<char>::releaseBuffer worker
			// (0x36410); the inline destructor is that same one-call body, so
			// this copy relocates to releaseBuffer rather than to the
			// AsciiString::clear alternatename spelling.
			m_str.~AsciiString();
			((Rva000A8C9B *)&m_a)->clear();
			((Rva000A8C9B *)&m_b)->clear();
		}
		else
		{
			m_flag = 1;
			m_str = a;
			m_a = b;
			m_b = c;
		}
	}
	char m_00[0x72];
	unsigned char m_flag;
	char m_01[0x11];
	AsciiString m_str;
	OpaqueRefElement4 m_a;
	OpaqueRefElement4 m_b;
};

class Rva0023DC8E
{
public:
	void rva0023DC8E(const AsciiString &a);
};

// The mode gate 0x001DCD1C stays visible (out of line) so the unit knows it
// leaves TheAudio alone: retail keeps the pointer in a register across it.
inline __declspec(noinline) bool GameLogic::rva001DCD1C(void)
{
	return m_110 == 8 || (m_110 == 9 && m_114 != 3);
}

// Queues the timed reverse of a transition group at the given frame.
static __forceinline void queueTransitionReverse(const AsciiString &group, int frame)
{
	Rva003FE7E6(Rva0023E323(group, frame), &g_00E02EC4);
}

bool GameLogic::rva002423E3(void)
{
	if (!m_9c)
		return true;

	TheGameEngine->slot5C();

	if (TheNetwork && !TheNetwork->slotD0())
	{
		int mode = m_110;
		if (mode == 1 || mode == 5 || mode == 2)
		{
			unsigned int frame = TheGameLogic->getFrame();
			if (frame < 6)
			{
				if (frame >= 5)
				{
					((Rva0023C7D2 *)this)->rva0023C7BB(100);
					return true;
				}
				((Rva0023C7D2 *)this)->rva0023C7BB((int)g_00DFE788);
				g_00DFE788 += 0.25f;
				return true;
			}
		}
	}

	bool restoreMouse = false;
	m_9c = false;

	if (m_120 && TheDisplay->slot114() && !TheWritableGlobalData->m_11c8)
	{
		if (m_9e)
		{
			{
				Rva0023C565 lock;
				TheTransitionHandler->slot24();
				TheTransitionHandler->setGroup("FadeWholeScreen");
				((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
				TheTransitionHandler->slot28();
			}
			while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
			{
				TheGameEngine->slot5C();
				Sleep(1);
			}
			((W3DDisplay *)TheDisplay)->rva0025D2F6();
			TheTransitionHandler->reverse("FadeWholeScreen");
			TheTransitionHandler->slot28();
			((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
			m_9e = false;
			restoreMouse = true;
		}
		else
		{
			switch (m_110)
			{
				case 0:
				case 6:
				{
					((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(true);
					TheTransitionHandler->setGroup("FadeWholeScreen");
					((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
					while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
					{
						TheGameEngine->slot5C();
						Sleep(5);
					}
					((Rva0023C7D2 *)this)->rva0023C7D2();
					if (!((const StringBase<char> *)&m_74)->isEmpty())
					{
						((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
						TheTransitionHandler->slot24();
						TheTransitionHandler->slot28();
						TheDisplay->slot10C(m_74, 1, 0xa0);
						m_74.clear();
					}
					else
					{
						TheDisplay->slot110();
					}
					restoreMouse = true;
					queueTransitionReverse(AsciiString("FadeWholeScreen"), m_90);
				}
					break;
				case 2:
				case 3:
					TheTransitionHandler->setGroup("FadeWholeScreen");
					((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
					TheTransitionHandler->slot28();
					while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
					{
						TheGameEngine->slot5C();
						Sleep(5);
					}
					{
						AsciiString fadeGroup("FadeWholeScreen");
						Rva003FE7E6(Rva0023E323(fadeGroup, m_90), &g_00E02EC4);
					}
					TheTransitionHandler->slot28();
					break;

				case 4:
				case 7:
					TheTransitionHandler->slot24();
					if (!g_bfmeAptWindowManager || !((Rva00222A8BTarget *)g_bfmeAptWindowManager)->m_31c)
					{
						TheTransitionHandler->setGroup("FadeWholeScreen");
						TheTransitionHandler->slot28();
						while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
						{
							TheGameEngine->slot5C();
							Sleep(1);
						}
					}
					restoreMouse = true;
					break;

				default:
					TheDisplay->slot110();
					((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
					restoreMouse = true;
					break;

			}
		}
	}
	else
	{
		((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
		restoreMouse = true;
	}

	if (m_120)
		((Rva0023C7D2 *)this)->rva0023C7D2();
	if (restoreMouse)
		TheMouse->_bfme_setEngineVisibility(true);
	TheDisplay->m_115 = false;
	TheGameEngine->slot5C();
	if (TheAudio)
	{
		if (rva001DCD1C())
		{
			TheAudio->slot50(true);
			TheAudio->slot44(0x3f, 6, 0);
		}
		else
		{
			TheAudio->slot50(false);
			TheAudio->slot44(0x3f, 5, 0);
		}
	}
	((Rva0023DCCE *)this)->rva0023DCCE(AsciiString::TheEmptyString, Rva002423E3NullRef(), Rva002423E3NullRef());
	((Rva0023DC8E *)this)->rva0023DC8E(AsciiString::TheEmptyString);
	m_90 = 7;
	return true;
}



// The audio manager's +0x138 result holds the refresh sound reference at +0xCC.
struct MiscAudio
{
	char m_pad000[0xcc];
	OpaqueRefElement4 m_cc;                                              // +0xCC
};


class ExperienceLevelSystem
{
public:
	bool getFlag24(void) const { return m_24; }

private:
	char m_pad00[0x24];
	bool m_24;                                                           // +0x24
};

// TheExperienceLevelSystem is read through the ExperienceLevelStore view at its
// rank lookup 0x00288CA6.
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceLevelStore
{
public:
	int rva00288CA6(const ExperienceTracker *tracker, int level, int *required) const;
};

class ExperienceTracker
{
public:
	int getLevel(void) const { return m_level; }
	bool isTrainable(void) const;                                        // 0x0039ADAF
	void setExperienceSink(ObjectID sink);                               // 0x003B23AF

private:
	char m_pad00[0x24];
	int m_level;                                                         // +0x24
	char m_pad28[0x38 - 0x28];
	ObjectID m_38;                                                       // +0x38
};

class RevivalExperienceView
{
public:
	int rva000B49A1(void) const;
};

class Rva003BD306Target
{
public:
	void rva0039B3D1(float level, bool flag);
};

class Rva0039B20C
{
public:
	void rva0039B227(int value);
};

// The interface the +0x250 contain module's slot 31 (and Object 0x0029439D)
// returns.
class Rva0024877AProducer
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p0a();
	virtual void slot2C(Object *obj);                                    // +0x2C
	virtual void p0c(); virtual void p0d(); virtual void p0e(); virtual void p0f();
	virtual void slot40(void);                                           // +0x40
	virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14();
	virtual void p15(); virtual void p16(); virtual void p17();
	virtual void slot60(void);                                           // +0x60
};

class ContainModuleInterface
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08(); virtual void c09(); virtual void c0a(); virtual void c0b();
	virtual void c0c(); virtual void c0d(); virtual void c0e(); virtual void c0f();
	virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13();
	virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17();
	virtual void c18(); virtual void c19(); virtual void c1a(); virtual void c1b();
	virtual void c1c(); virtual void c1d(); virtual void c1e();
	virtual Rva0024877AProducer *slot7C(void);                           // +0x7C
	virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
	virtual void c24(); virtual void c25(); virtual void c26();
	virtual void slot9C(Object *obj);                                    // +0x9C
	virtual void c28(); virtual void c29();
	virtual void slotA8(int arg);                                        // +0xA8
	virtual void c2b(); virtual void c2c(); virtual void c2d(); virtual void c2e();
	virtual void c2f(); virtual void c30(); virtual void c31(); virtual void c32();
	virtual void c33(); virtual void c34(); virtual void c35(); virtual void c36();
	virtual void c37(); virtual void c38(); virtual void c39(); virtual void c3a();
	virtual void c3b(); virtual void c3c(); virtual void c3d(); virtual void c3e();
	virtual void c3f(); virtual void c40(); virtual void c41(); virtual void c42();
	virtual void c43();
	virtual void slot110(void (*func)(void *, IntList *), IntList *ids, int mask); // +0x110
};

// The interface Object 0x0028C197 returns.
class Rva0024877ABody
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
	virtual void b04(); virtual void b05(); virtual void b06(); virtual void b07();
	virtual void b08(); virtual void b09(); virtual void b0a(); virtual void b0b();
	virtual void b0c(); virtual void b0d(); virtual void b0e(); virtual void b0f();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13();
	virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17();
	virtual void b18(); virtual void b19(); virtual void b1a(); virtual void b1b();
	virtual void b1c(); virtual void b1d(); virtual void b1e(); virtual void b1f();
	virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23();
	virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27();
	virtual void b28(); virtual void b29(); virtual void b2a(); virtual void b2b();
	virtual void b2c(); virtual void b2d(); virtual void b2e(); virtual void b2f();
	virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33();
	virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37();
	virtual void b38(); virtual void b39(); virtual void b3a(); virtual void b3b();
	virtual void b3c(); virtual void b3d(); virtual void b3e(); virtual void b3f();
	virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43();
	virtual void b44(); virtual void b45(); virtual void b46();
	virtual int slot11C(void);                                           // +0x11C
	virtual void slot120(int value);                                    // +0x120
};

void Rva0024080FAdd(void *obj, IntList *ids);

// The 0x50-byte snapshot 0x0024877A records per object (ctor 0x0024076D, dtor
// 0x00240831): template name, transform, team, ID, container ID, the +0x40
// value of the 0x0028C197 interface, the contained IDs and the experience
// tracker's level and experience.
class Rva0024076D
{
public:
	Rva0024076D();
	// The native member-wise copy is owned by Rva0024314ARecordCopy.cpp.
	Rva0024076D(const Rva0024076D &);
	~Rva0024076D();

	AsciiString m_name;                                                  // +0x00
	Matrix3D m_transform;                                                // +0x04
	unsigned int m_teamID;                                               // +0x34
	ObjectID m_id;                                                       // +0x38
	ObjectID m_containerID;                                              // +0x3C
	int m_40;                                                            // +0x40
	IntList m_contained;                                                 // +0x44
	int m_level;                                                         // +0x48
	int m_experience;                                                    // +0x4C
};

// Keep the native node-construction call visible to the list insert body.
namespace _STL {
template <> void _Construct<Rva0024076D, Rva0024076D>(Rva0024076D *, const Rva0024076D &);
template <> __declspec(noinline) inline
_List_node<Rva0024076D> *list<Rva0024076D>::_M_create_node(const Rva0024076D &value)
{
    _Node *node = this->_M_node.allocate(1);
    _Construct(&node->_M_data, value);
    return node;
}
}

// 0x0024877A, once per logic frame: snapshot and destroy every object (only
// those with a visible drawable, or contained in one, when TheGameClient's
// +0xB8 is set; only 0x0028C428 objects unless TheExperienceLevelSystem's
// +0x24 is set), then recreate each from its snapshot ("The object, '%S' was
// refreshed.") and relink the containers and their contents.
bool GameLogic::rva0024877A(void)
{
	static unsigned int lastFrame;
	if (lastFrame < m_40) {
	lastFrame = m_40;

	bool destroyed = false;
	_STL::list<Rva0024076D> records;
	bool all = false;
	bool visibleOnly = TheGameClient->m_b8 != 0;
	if (TheExperienceLevelSystem->getFlag24()) {
		all = true;
		visibleOnly = false;
	}

	for (Object *obj = getFirstObject(); obj; obj = obj->getNextObject()) {
		if (visibleOnly) {
			bool hidden = true;
			if (obj->getDrawable() && obj->getDrawable()->isVisible())
				hidden = false;
			if (obj->getContainedBy() && obj->getContainedBy()->getDrawable()
				&& obj->getContainedBy()->getDrawable()->isVisible())
				hidden = false;
			if (hidden)
				continue;
		}
		if (!all && !obj->rva0028C428())
			continue;

		Rva0024076D record;
		record.m_name = obj->getTemplate()->getName();
		record.m_transform = *obj->getTransformMatrix();
		record.m_teamID = obj->getTeam()->getID();
		record.m_id = obj->getID();
		if (obj->getExperienceTracker()) {
			record.m_level = obj->getExperienceTracker()->getLevel();
			record.m_experience = ((RevivalExperienceView *)obj->getExperienceTracker())->rva000B49A1();
		}
		if (obj->getContain()) {
			obj->getContain()->slot110(Rva0024080FAdd, &record.m_contained, 1);
			obj->getContain()->slot110(Rva0024080FAdd, &record.m_contained, 0x10);
			obj->getContain()->slotA8(0);
		}
		if (obj->getContainedBy())
			record.m_containerID = obj->getContainedBy()->getID();
		if (obj->rva0028C197())
			record.m_40 = ((Rva0024877ABody *)obj->rva0028C197())->slot11C();
		records.push_back(record);
		destroyObject(obj);
		destroyed = true;
	}
	if (destroyed)
		processDestroyList();

	for (_STL::list<Rva0024076D>::iterator it = records.begin(); it != records.end(); ++it) {
		Rva0024076D &record = *it;
		const ThingTemplate *tt = TheThingFactory->findTemplate(record.m_name);
		Team *team = TheTeamFactory->findTeamByID(record.m_teamID);
		if (!tt || !team)
			continue;

		TheInGameUI->message(UnicodeString(L"The object, '%S' was refreshed."), record.m_name.str());
		BfmeAudioEventPrefix136 sound(TheAudio->getMiscAudio()->m_cc, 0);
		TheAudio->addAudioEvent(&sound);
		Object *obj = TheThingFactory->newObject(tt, team, &CreateMask(), record.m_id);
		if (obj) {
			obj->rva0028D412(&record.m_transform);
			if (obj->rva0028C197())
				((Rva0024877ABody *)obj->rva0028C197())->slot120(record.m_40);
			if (obj->getExperienceTracker() && obj->getExperienceTracker()->isTrainable()) {
				int level = ((const ExperienceLevelStore *)TheExperienceLevelSystem)->rva00288CA6(
					obj->getExperienceTracker(), record.m_level, 0);
				((Rva003BD306Target *)obj->getExperienceTracker())->rva0039B3D1((float)level, true);
				((Rva0039B20C *)obj->m_experienceTracker)->rva0039B227(record.m_experience);
			}
		}
	}

	for (_STL::list<Rva0024076D>::iterator it = records.begin(); it != records.end(); ++it) {
		Object *obj = findObjectByID(it->m_id);
		if (!obj)
			continue;
		Object *container = findObjectByID(it->m_containerID);
		if (container && container->getContain()) {
			container->getContain()->slot9C(obj);
			if (container->getContain()->slot7C()) {
				obj->setProducer(container);
				obj->getExperienceTracker()->setExperienceSink(container->getID());
				container->getContain()->slot7C()->slot2C(obj);
				container->getContain()->slot7C()->slot60();
				container->getContain()->slot7C()->slot60();
			}
		}
		for (IntList::iterator id = it->m_contained.begin(); id != it->m_contained.end(); ++id) {
			Object *rider = findObjectByID((ObjectID)*id);
			if (rider && obj->getContain()) {
				obj->getContain()->slot9C(rider);
				if (obj->rva0029439D()) {
					rider->setProducer(obj);
					rider->getExperienceTracker()->setExperienceSink(obj->getID());
					((Rva0024877AProducer *)obj->rva0029439D())->slot2C(rider);
				}
			}
		}
		if (obj->getContain() && obj->getContain()->slot7C())
			obj->getContain()->slot7C()->slot40();
	}
	return destroyed;
	}
	return false;
}

// ?setExperienceSink@ExperienceTracker@@QAEXW4ObjectID@@@Z @0x003B23AF 10B:
// store the argument at +0x38 and return. Retail folds this body with
// AIUpdateInterface::setLastCommandSource (rowed in AIUpdate.cpp); the name was
// only pinned, so nothing defined it for this unit's two calls above, which
// retail makes out of line.
__declspec(noinline) void ExperienceTracker::setExperienceSink(ObjectID sink)
{
	m_38 = sink;
}
