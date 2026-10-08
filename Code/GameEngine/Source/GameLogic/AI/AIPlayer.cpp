// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 BuildListInfo desired-gatherers getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp).
// Retail BFME2 keeps the field at the same offset (+0x84); the layout
// authority is reference/shims/buildlistinfo/GameLogic/SidesList.h.
//
// AIPlayer::checkForSupplyCenter (211B @0x004F29E9), after the BFME1 donor
// GameEngine/Source/GameLogic/AI/AIPlayerSupply.cpp
// (?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z,
// 259B @0x00162410 there). The shape is donor-verbatim except for four
// BFME2 divergences, all read straight off retail:
// - The side string sits at player+0x58 (donor +0x28); BFME2's Player grew.
// - The AI chain is TheAI->[+0x18]->[+0xF4] (donor +0x14/+0xEC).
// - The side address is recomputed at the top of every loop iteration
//   (retail reloads this->m_player through the volatile slot, adds 0x58,
//   and calls compare each time round), so the volatile read lives inside
//   the loop here instead of above it as in the donor.
// - The resInfo loop is a plain while (retail jumps to the test first);
//   the donor's if-guard plus do-while is the same walk written the other
//   way and does not reproduce retail's test-first layout.
// All four callees were already rowed: NameKeyGenerator::nameToKey
// (0x00148E1A), Object::findModule (0x0028B6D6, reached through a TU-local
// befriended Object the way CastleMemberBehaviorFind.cpp does it),
// StringBase<char>::compare (0x000069D6), and __EH_prolog (0x00629188).
//
// LAYOUT PUZZLE (bytes are exact; names may need a second pass):
// checkForSupplyCenter stores supply/count/minus-one at +0x46/+0x78/+0x7C,
// which is the donor's setSupplyBuilding/setDesiredGatherers/
// setCurrentGatherers mapping, but the pre-existing getDesiredGatherers row
// in this TU reads +0x84. Both are byte-proven, so the TU keeps both fields
// side by side until BuildListInfo archaeology settles which int is which.
//
// AIPlayer::findSupplyCenter (655B @0x004F21D5) is at the end; its scalar
// SSE float code is why the unit builds with /arch:SSE (the two bodies
// above have no floats and compile the same either way).
//
// The superweapon trio sits ahead of it in retail's order:
// getPlayerSuperweaponValue (386B @0x004F1256), getPlayerStructureBounds
// (400B @0x004F1B8C) and computeSuperweaponTarget (811B @0x004F1D38, AIPlayer
// vtable 0x00C62DC8 slot 4). Donor: BFME1's
// GameEngine/Source/GameLogic/AI/AIPlayerComputeSuperweaponTarget.cpp (the
// Generals bodies), here on BFME2's team walk: the +0x32C prototype list,
// the +0x334 instance list advanced through the 0x009C4AF5 member pointer
// and the out-of-line 24-byte member iterator (0x00263864/0x00263526).
// BFME2 divergences read off retail: the cost helper 0x0033A69A is called
// (player, 0, -1); the KindOf bits are 0x1000 (+0x109 bit 4) and 0x20000
// (+0x10A bit 1); computeSuperweaponTarget nudges with findPositionAround
// (max radius 300) for special power types 0x7C and 0x7B, reading the type
// at +0x1C of friend_getFinalOverride (0x00288609), and returns nothing
// (retail never loads eax).
//
// AIPlayer::guardSupplyCenter (306B @0x004F2ABC) follows findSupplyCenter:
// Zero Hour's body, non-virtual in BFME 2 (absent from the AIPlayer vtable),
// with the check frame at +0x6C and the attacked centre at +0x70. It guards
// 0.8 bounding radii short of the warehouse on the side facing the skirmish
// enemy's structure bounds.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

#include "ascii_string.h"


class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class Team;
class Player;

#include "../../../../Libraries/Include/Lib/Coord2D.h"

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

struct Coord3D
{
	float x;
	float y;
	float z;
	// Retail copies positions member by member (getPlayerStructureBounds
	// loads pos.x and pos.y but never pos.z), as BFME 1's view does.
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	void set(float ax, float ay, float az)
	{
		x = ax;
		y = ay;
		z = az;
	}
	void normalize();	// 0x000035B6
};

enum ObjectID
{
	INVALID_ID = 0
};

enum GuardMode
{
	GUARDMODE_NORMAL
};

enum CommandSourceType
{
	CMD_FROM_PLAYER,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

class AIGroup
{
public:
	void groupGuardPosition(const Coord3D *pos, GuardMode guardMode, CommandSourceType cmdSource);	// 0x003703CF
};

// What Object +0x04 points at: the KindOf mask at +0x108 (bit 7
// KINDOF_STRUCTURE, +0x112 bit 6 the supply source) and the cost-to-build
// helper 0x0033A69A.
class ThingTemplate
{
public:
	Int rva0033A69A(const Player *player, Int a, Int b) const;	// 0x0033A69A
	unsigned char m_pad000[0x108];
	unsigned char m_kindOf[0x1C];		// +0x108
};

class Object
{
public:
	bool isKindOfStructure() const { return (m_template->m_kindOf[0] & 0x80) != 0; }
	bool isKindOfSupplySource() const { return (m_template->m_kindOf[10] & 0x40) != 0; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isSignificantlyAboveTerrain() const;	// 0x0030ADDC
	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }
	Team *getTeam() const { return m_team; }
	float getBoundingCircleRadius() const { return m_boundingCircleRadius; }
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIPlayer;
private:
	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position;			// +0x38
	unsigned char m_pad44[0x8C - 0x44];
	Object *m_next;				// +0x8C
	unsigned char m_pad90[0xB8 - 0x90];
	float m_boundingCircleRadius;		// +0xB8
	unsigned char m_padBC[0x304 - 0xBC];
	Team *m_team;				// +0x304
};

class SupplyWarehouseDockUpdate : public Module
{
public:
	Int getBoxesStored() const { return m_boxesStored; }
private:
	unsigned char m_pad[0x88];
	Int m_boxesStored;			// +0x88
};

enum Relationship
{
	ENEMIES = 0
};

// Zero Hour's DLINK_ITERATOR for team instances (advance through the member
// pointer) and BFME2's 24-byte member iterator with its out-of-line advance,
// as in PlayerRva002AD93A.cpp.
template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

template <>
class DLINK_ITERATOR<Object>
{
public:
	void advance();				// 0x00263526
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void getTeamAsAIGroup(AIGroup *group);	// 0x003A0F62
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList;	// +0x334
};

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;	// 0x002AD0C6
	Int getPlayerIndex() const { return m_playerIndex; }

	class PlayerTeamList
	{
	public:
		class const_iterator
		{
		public:
			const_iterator() {}
			const_iterator(PlayerTeamNode *node) : m_node(node) {}
			TeamPrototype *operator*() const { return m_node->m_value; }
			Bool operator!=(const const_iterator &that) const { return m_node != that.m_node; }
			const_iterator &operator++() { m_node = m_node->m_next; return *this; }
		private:
			PlayerTeamNode *m_node;
		};
		const_iterator begin() const { return const_iterator(m_head->m_next); }
		const_iterator end() const { return const_iterator(m_head); }
	private:
		PlayerTeamNode *m_head;
	};
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
private:
	unsigned char m_pad[0x54];
	Int m_playerIndex;			// +0x54
	unsigned char m_pad58[0x32C - 0x58];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);	// 0x002A7A29
};
extern PlayerList *ThePlayerList;

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	Int getSpecialPowerType() const
	{
		return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_type;
	}
private:
	unsigned char m_pad[0x1C];
	Int m_type;				// +0x1C
};

class TerrainLogic
{
public:
	virtual void tl00(); virtual void tl01(); virtual void tl02();
	virtual void tl03(); virtual void tl04(); virtual void tl05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;	// +0x18
};
extern TerrainLogic *TheTerrainLogic;

extern "C" __declspec(dllimport) double __cdecl ceil(double);
extern "C" double __cdecl sqrt(double);

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_CEIL(x) (fast_float2long_round((Real)ceil(x)))

class GameLogic
{
public:
	Object *getFirstObject();	// 0x0023CAD2
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char m_pad[0xA5C];
	Int m_baseValuePerSupplyBox;		// +0xA5C
};
extern class GlobalData *TheWritableGlobalData;

// BFME2's partition filter chain (the view AIStructureCreepTactic.cpp
// documents): a vptr, the +0x04 link to the next filter, then each
// filter's members; address-derived names after allow (slot 1).
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

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// vftable 0x00BFAD1C, allow 0x002611DD: no members (ZH's
// PartitionFilterOnMap).
class Rva002611DDFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BFAD28, allow 0x0026137E, slot 2 0x00261368: +0x08 a
// player, +0x0C whether a hit allows (ZH's PartitionFilterPlayer).
class Rva0026137EFilter : public Rva000421C8
{
public:
	Rva0026137EFilter(Player *player, bool match) : m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// The 224-bit KindOf mask (unused, bit) constructor 0x00045411.
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

// vftable 0x00BC2908, allow 0x002610DE: every kind of the first mask and
// none of the second (ZH's PartitionFilterAcceptByKindOf).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

// Zero Hour's FindPositionOptions (PartitionManager.h).
struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = 0;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}
	Int flags;
	Real minRadius;
	Real maxRadius;
	Real startAngle;
	Real maxZDelta;
	const Object *ignoreObject;
	const Object *sourceToPathToDest;
	const Object *relationshipObject;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
	static Bool findPositionAround(const Coord3D *center,
		const FindPositionOptions *options, Coord3D *result);	// 0x00285202
};
extern PartitionManager *ThePartitionManager;

class AISideInfo
{
public:
	void *m_vtable;				// +0x00
	AsciiString m_side;			// +0x04
	Int m_easy;				// +0x08
	Int m_normal;				// +0x0C
	Int m_hard;				// +0x10
	unsigned char m_pad[0x1BC - 0x14];
	AISideInfo *m_next;			// +0x1BC
};

struct TAiData
{
	unsigned char m_pad[0xF4];
	AISideInfo *m_sideInfo;			// +0xF4
};

class AI
{
public:
	TAiData *getAiData() const { return m_aiData; }
	AIGroup *createGroup();	// 0x002FEC4B

private:
	unsigned char m_pre[0x18];
	TAiData *m_aiData;			// +0x18
};

// Matched DIR32 references in AIPlayer, Object and GettingBuiltBehavior place
// TheAI at VA 0x00DFF0F8; the retail image's zero-filled slot starts null.
extern class AI *TheAI;

class ScriptEngine
{
public:
	Player *getSkirmishEnemyPlayer();	// 0x00356F6E
};
extern ScriptEngine *TheScriptEngine;

class Player;

class BuildListInfo
{
public:
	int getDesiredGatherers();
	void setSupplyBuilding(Bool value) { m_isSupplyBuilding = value; }
	void setDesiredGatherers(Int value) { m_desiredGatherers = value; }
	void setCurrentGatherers(Int value) { m_currentGatherers = value; }

private:
	unsigned char m_preSupply[0x46];
	Bool m_isSupplyBuilding;		// +0x46
	unsigned char m_supplyPad[0x78 - 0x47];
	Int m_desiredGatherers;			// +0x78
	Int m_currentGatherers;			// +0x7C
	unsigned char m_gathererPad[0x84 - 0x80];
	int m_desiredGatherersReadback;		// +0x84 (pre-existing getter target)
};

// ?getDesiredGatherers@BuildListInfo@@QAEHXZ
int BuildListInfo::getDesiredGatherers()
{
	return m_desiredGatherersReadback;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class ThingTemplate;
class AIPlayer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void computeSuperweaponTarget(const SpecialPowerTemplate *power,
		Coord3D *retPos, Int playerNdx, Real weaponRadius);	// +0x10
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual Player *getAiEnemy();				// +0x30
	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);	// 0x004F1B8C
	bool isLocationSafe(const Coord3D *pos, const ThingTemplate *tmpl);
	Bool isSupplySourceAttacked();	// 0x004F1138
	void guardSupplyCenter(Team *team, Int minSupplies);

protected:
	static Int getPlayerSuperweaponValue(Coord3D *center, Int playerNdx, Real radius);
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
	Object *findSupplyCenter(Int minimumCash);
	bool rva004F2BEE(int minimumCash);

private:
	unsigned char m_pre[0x0C - 0x04];
	Player *m_player;					// +0x0C
	unsigned char m_mid[0x2C - 0x10];
	GameDifficulty m_difficulty;				// +0x2C
	unsigned char m_pad30[0x34 - 0x30];
	Coord3D m_baseCenter;					// +0x34
	unsigned char m_pad40[0x6C - 0x40];
	unsigned int m_supplySourceAttackCheckFrame;		// +0x6C
	ObjectID m_attackedSupplyCenter;			// +0x70
};

// ?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z
void AIPlayer::checkForSupplyCenter(BuildListInfo *info, Object *bldg)
{
	if (info)
	{
		if (bldg)
		{
			static const NameKeyType key_centerUpdate =
				TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
			Module *centerModule = bldg->findModule(key_centerUpdate);
			if (centerModule)
			{
				info->setSupplyBuilding(true);
				Int desiredGatherers = 0;
				const AISideInfo *resInfo = TheAI->getAiData()->m_sideInfo;
				while (resInfo)
				{
					// VC7 otherwise folds this into a shorter non-retail address calculation.
					void *playerStorage = *reinterpret_cast<void *volatile *>(
						reinterpret_cast<char *>(this) + 0x0c);
					const AsciiString *side = reinterpret_cast<const AsciiString *>(
						reinterpret_cast<char *>(playerStorage) + 0x58);
					if (resInfo->m_side == *side)
					{
						GameDifficulty difficulty = m_difficulty;
						if (difficulty == DIFFICULTY_EASY)
							desiredGatherers = resInfo->m_easy;
						if (difficulty == DIFFICULTY_NORMAL)
							desiredGatherers = resInfo->m_normal;
						if (difficulty == DIFFICULTY_HARD)
							desiredGatherers = resInfo->m_hard;
					}
					resInfo = resInfo->m_next;
				}

				info->setSupplyBuilding(true);
				info->setCurrentGatherers(-1);
				info->setDesiredGatherers(desiredGatherers + 1);
			}
		}
	}
}

// ?getPlayerSuperweaponValue@AIPlayer@@KAHPAUCoord3D@@HM@Z present-unmatched
// 0x004F1256, 386 bytes; this body compiles to 410. Its logic and frame match
// retail, but the aircraft KindOf test ahead of isSignificantlyAboveTerrain
// makes VC7.1 keep &pObj->m_template in esi and rotate the member loop. The
// near miss is banked in reverse/attempts/0x004f1256.cpp. The body stays here
// because computeSuperweaponTarget (0x004F1D38) matches only when it can see
// that this callee keeps no copy of the position address: that is what lets
// VC7.1 hoist the pos.x and pos.z stores out of the inner grid loop.
Int AIPlayer::getPlayerSuperweaponValue(Coord3D *searchCenter, Int playerIndex, Real searchRadius)
{
	if (searchRadius < 4 * 10.0f)
		searchRadius = 4 * 10.0f;
	Player::PlayerTeamList::const_iterator it;
	Real cash = 0;
	Real radSqr = searchRadius * searchRadius;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerIndex);
	if (pPlayer == 0)
		return 0;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it)
	{
		TeamPrototype *proto = *it;
		for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList(); !members.done(); members.advance())
			{
				Object *pObj = members.cur();
				if ((pObj->getTemplate()->m_kindOf[1] & 0x10) != 0)	// KindOf bit 12
				{
					if (pObj->isSignificantlyAboveTerrain())
						continue;
				}
				Coord3D pos = *pObj->getPosition();
				Real dx = searchCenter->x - pos.x;
				Real dy = searchCenter->y - pos.y;
				if (dx * dx + dy * dy < radSqr)
				{
					Real dist = sqrt(dx * dx + dy * dy);
					Real factor = 1.0f - (dist / (2 * searchRadius));
					Real cost = pObj->getTemplate()->rva0033A69A(pPlayer, 0, -1);
					if ((pObj->getTemplate()->m_kindOf[2] & 0x02) != 0)	// KindOf bit 17
						cost = cost / 10;
					if (cost > 3000)
						cost = cost / 10;
					cash += factor * cost;
				}
			}
		}
	}
	return cash;
}

// ?getPlayerStructureBounds@AIPlayer@@SAXPAURegion2D@@H@Z (0x004F1B8C)
void AIPlayer::getPlayerStructureBounds(Region2D *bounds, Int playerNdx)
{
	Bool firstObject = true;
	Bool firstStructure = true;
	bounds->hi.x = bounds->lo.x = bounds->hi.y = bounds->lo.y = 0;
	Region2D objBounds;
	objBounds.hi.x = objBounds.lo.x = objBounds.hi.y = objBounds.lo.y = 0;

	Player *pPlayer = ThePlayerList->getNthPlayer(playerNdx);
	if (pPlayer == 0)
		return;
	Player::PlayerTeamList::const_iterator it;
	for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it)
	{
		TeamPrototype *proto = *it;
		for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			for (DLINK_ITERATOR<Object> members = team->iterate_TeamMemberList(); !members.done(); members.advance())
			{
				Object *pObj = members.cur();
				if (!pObj)
					continue;
				if (pObj->isKindOfStructure())
				{
					Coord3D pos = *pObj->getPosition();
					if (firstObject) {
						objBounds.lo.x = objBounds.hi.x = pos.x;
						objBounds.lo.y = objBounds.hi.y = pos.y;
						firstObject = false;
					} else {
						if (objBounds.lo.x > pos.x) objBounds.lo.x = pos.x;
						if (objBounds.lo.y > pos.y) objBounds.lo.y = pos.y;
						if (objBounds.hi.x < pos.x) objBounds.hi.x = pos.x;
						if (objBounds.hi.y < pos.y) objBounds.hi.y = pos.y;
					}
					if (firstStructure) {
						bounds->lo.x = bounds->hi.x = pos.x;
						bounds->lo.y = bounds->hi.y = pos.y;
						firstStructure = false;
					} else {
						if (bounds->lo.x > pos.x) bounds->lo.x = pos.x;
						if (bounds->lo.y > pos.y) bounds->lo.y = pos.y;
						if (bounds->hi.x < pos.x) bounds->hi.x = pos.x;
						if (bounds->hi.y < pos.y) bounds->hi.y = pos.y;
					}
				}
			}
		}
	}
	if (!firstStructure) {
		*bounds = objBounds;
	}
}

// ?computeSuperweaponTarget@AIPlayer@@UAEXPBVSpecialPowerTemplate@@PAUCoord3D@@HM@Z
// (0x004F1D38)
void AIPlayer::computeSuperweaponTarget(const SpecialPowerTemplate *power,
	Coord3D *retPos, Int playerNdx, Real weaponRadius)
{
	Region2D bounds;
	getPlayerStructureBounds(&bounds, playerNdx);

	if (weaponRadius < 1.0f) {
		weaponRadius = 1.0f; // sanity to avoid divide by 0.
	}

	Int xCount, yCount;
	bounds.lo.x += weaponRadius;
	bounds.hi.x -= weaponRadius;
	if (bounds.hi.x < bounds.lo.x) {
		bounds.hi.x = bounds.lo.x = (bounds.hi.x + bounds.lo.x) / 2.0f;
	}
	if (bounds.hi.y < bounds.lo.y) {
		bounds.hi.y = bounds.lo.y = (bounds.hi.y + bounds.lo.y) / 2.0f;
	}

	xCount = REAL_TO_INT_CEIL(bounds.width() / weaponRadius) + 1;
	yCount = REAL_TO_INT_CEIL(bounds.height() / weaponRadius) + 1;

	if (xCount > 10) xCount = 10;
	if (yCount > 10) yCount = 10;

	Int cash = -1;
	Coord3D pos;
	Coord3D bestPos;
	Int i, j;

	for (i = 0; i < xCount; i++) {
		for (j = 0; j < yCount; j++) {
			pos.x = bounds.lo.x + (bounds.width() * i) / xCount;
			pos.y = bounds.lo.y + (bounds.height() * j) / yCount;
			pos.z = 0;
			Int curCash = getPlayerSuperweaponValue(&pos, playerNdx, 2 * weaponRadius);
			if (curCash > cash) {
				cash = curCash;
				bestPos = pos;
			}
		}
	}

	Coord3D veryBestPos;
	xCount = 11;
	yCount = 11;
	cash = -1;
	Int count = 0;
	for (i = 0; i < xCount; i++) {
		for (j = 0; j < yCount; j++) {
			pos.x = bestPos.x + (i - 5) * (weaponRadius / 10);
			pos.y = bestPos.y + (j - 5) * (weaponRadius / 10);
			pos.z = 0;
			Int curCash = getPlayerSuperweaponValue(&pos, playerNdx, weaponRadius);
			if (curCash > cash) {
				cash = curCash;
				veryBestPos = pos;
				count = 1;
			} else if (curCash == cash) {
				veryBestPos.x += pos.x;
				veryBestPos.y += pos.y;
				count++;
			}
		}
	}
	if (count > 1) {
		veryBestPos.x /= count;
		veryBestPos.y /= count;
	}

	// Special power types 0x7C and 0x7B (enumerator names unknown).
	if (power->getSpecialPowerType() == 0x7C || power->getSpecialPowerType() == 0x7B) {
		FindPositionOptions fpOptions;
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 300.0f;
		PartitionManager::findPositionAround(&veryBestPos, &fpOptions, &veryBestPos);
	}

	veryBestPos.z = TheTerrainLogic->getGroundHeight(veryBestPos.x, veryBestPos.y, 0);
	*retPos = veryBestPos;
}

// ?findSupplyCenter@AIPlayer@@IAEPAVObject@@H@Z (0x004F21D5, callers the
// guardSupplyCenter pair 0x004F2ABC / 0x004F2BEE): Zero Hour's and the BFME1
// donor's (AIPlayerFindSupplyCenter.cpp) body on BFME2's layout: the KindOf
// bytes read straight off the template at +0x04, the object list linked at
// +0x8C, the bounding radius at +0xB8 and the team at +0x304, and the
// filters BFME2's chain.
Object *AIPlayer::findSupplyCenter(Int minimumCash)
{
	Object *bestSupplyWarehouse = 0;
	float bestDistSqr = 0;
	Object *obj;
	Coord3D enemyCenter;
	enemyCenter.zero();
	Region2D bounds;
	Player *enemy = getAiEnemy();
	if (enemy) {
		getPlayerStructureBounds(&bounds, enemy->getPlayerIndex());
		enemyCenter.set((bounds.lo.x + bounds.hi.x) * 0.5f, (bounds.lo.y + bounds.hi.y) * 0.5f, 0);
	}

	do {
		for (obj = TheGameLogic->getFirstObject(); obj; obj = obj->getNextObject()) {
			if (!obj->isKindOfStructure())
				continue;
			if (!obj->isKindOfSupplySource())
				continue;
			static const NameKeyType key_warehouseUpdate =
				TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
			SupplyWarehouseDockUpdate *warehouseModule =
				(SupplyWarehouseDockUpdate *)obj->findModule(key_warehouseUpdate);
			if (warehouseModule) {
				Int availableCash = warehouseModule->getBoxesStored() * TheWritableGlobalData->m_baseValuePerSupplyBox;
				if (availableCash < minimumCash)
					continue;
				if (m_player->getRelationship(obj->getTeam()) == ENEMIES)
					continue;

				Coord3D center;
				center.x = obj->getPosition()->x;
				center.y = obj->getPosition()->y;
				center.z = obj->getPosition()->z;
				float radius = obj->getBoundingCircleRadius() + 200.0f;

				Object *supplyCenter;
				{
					Rva002611DDFilter filterMapStatus;
					Rva0026137EFilter f2(m_player, true);
					supplyCenter = ThePartitionManager->getClosestObject(&center, radius, 1,
						Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 34),
							*(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
							.link(f2.link(&filterMapStatus)));
				}
				if (supplyCenter)
					continue;

				float dx, dy;
				dx = obj->getPosition()->x - m_baseCenter.x;
				dy = obj->getPosition()->y - m_baseCenter.y;
				float distSqr = dx * dx + dy * dy;
				if (enemy) {
					dx = obj->getPosition()->x - enemyCenter.x;
					dy = obj->getPosition()->y - enemyCenter.y;
					if (distSqr * 0.4 > (dx * dx + dy * dy) * 0.6f)
						continue;
				}

				if (bestSupplyWarehouse == 0) {
					bestSupplyWarehouse = obj;
					bestDistSqr = distSqr;
				} else if (bestDistSqr > distSqr) {
					bestSupplyWarehouse = obj;
					bestDistSqr = distSqr;
				}
			}
		}
		if (bestSupplyWarehouse)
			break;
		minimumCash /= 2;
	} while (minimumCash > 100);

	return bestSupplyWarehouse;
}

bool AIPlayer::rva004F2BEE(int minimumCash)
{
	Object *supply = findSupplyCenter(minimumCash);
	if (supply == 0)
		return true;
	return isLocationSafe(supply->getPosition(), (const ThingTemplate *)supply->m_template);
}

void AIPlayer::guardSupplyCenter(Team *team, Int minSupplies)
{
	m_supplySourceAttackCheckFrame = 0;
	Object *warehouse = 0;
	if (isSupplySourceAttacked())
		warehouse = TheGameLogic->findObjectByID(m_attackedSupplyCenter);
	if (warehouse == 0)
		warehouse = findSupplyCenter(minSupplies);
	if (warehouse) {
		AIGroup *theGroup = TheAI->createGroup();
		if (!theGroup)
			return;
		team->getTeamAsAIGroup(theGroup);
		Coord3D location = *warehouse->getPosition();
		Region2D bounds;
		Int enemyNdx = TheScriptEngine->getSkirmishEnemyPlayer()->getPlayerIndex();
		getPlayerStructureBounds(&bounds, enemyNdx);
		Coord3D offset;
		offset.zero();
		offset.x = location.x - (bounds.lo.x + bounds.hi.x) * 0.5f;
		offset.y = location.y - (bounds.lo.y + bounds.hi.y) * 0.5f;
		offset.normalize();
		Real radius = warehouse->getBoundingCircleRadius() * 0.8f;
		location.x -= offset.x * radius;
		location.y -= offset.y * radius;
		theGroup->groupGuardPosition(&location, GUARDMODE_NORMAL, CMD_FROM_SCRIPT);
	}
}
