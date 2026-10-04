// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
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

typedef bool Bool;
typedef int Int;

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

struct Coord2D
{
	float x;
	float y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct Coord3D
{
	float x;
	float y;
	float z;
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
};

// What Object +0x04 points at, as findSupplyCenter tests its KindOf bytes:
// +0x108 bit 7 (KINDOF_STRUCTURE) and +0x112 bit 6 (the supply source).
struct ObjectKindBytes
{
	unsigned char m_pad000[0x108];
	unsigned char m_108;
	unsigned char m_pad109[0x112 - 0x109];
	unsigned char m_112;
};

class Object
{
public:
	bool isKindOfStructure() const { return (m_template->m_108 & 0x80) != 0; }
	bool isKindOfSupplySource() const { return (m_template->m_112 & 0x40) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	Object *getNextObject() const { return m_next; }
	Team *getTeam() const { return m_team; }
	float getBoundingCircleRadius() const { return m_boundingCircleRadius; }
protected:
	Module *findModule(NameKeyType key) const;
	friend class AIPlayer;
private:
	void *m_vptr;
	const ObjectKindBytes *m_template;	// +0x04
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

class Player
{
public:
	Relationship getRelationship(const Team *team) const;	// 0x002AD0C6
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_pad[0x54];
	Int m_playerIndex;			// +0x54
};

class GameLogic
{
public:
	Object *getFirstObject();	// 0x0023CAD2
};
extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char m_pad[0xA5C];
	Int m_baseValuePerSupplyBox;		// +0xA5C
};
extern GlobalData *TheGlobalData;

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

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
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

private:
	unsigned char m_pre[0x18];
	TAiData *m_aiData;			// +0x18
};

// Matched DIR32 references in AIPlayer, Object and GettingBuiltBehavior place
// TheAI at VA 0x00DFF0F8; the retail image's zero-filled slot starts null.
AI *TheAI = 0;

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
class AIPlayer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual Player *getAiEnemy();				// +0x30
	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);	// 0x004F1B8C

protected:
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
	Object *findSupplyCenter(Int minimumCash);

private:
	unsigned char m_pre[0x0C - 0x04];
	Player *m_player;					// +0x0C
	unsigned char m_mid[0x2C - 0x10];
	GameDifficulty m_difficulty;				// +0x2C
	unsigned char m_pad30[0x34 - 0x30];
	Coord3D m_baseCenter;					// +0x34
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
				Int availableCash = warehouseModule->getBoxesStored() * TheGlobalData->m_baseValuePerSupplyBox;
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
