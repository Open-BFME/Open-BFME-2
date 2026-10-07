// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /DNDEBUG /arch:SSE /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// CreateCrateDie, retail 0x00485444-0x004858F4: Zero Hour's
// GameLogic/Object/Die/CreateCrateDie.cpp (reference/open-bfme-1/inputs/
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/
// Object/Die/CreateCrateDie.cpp) in retail order. testKillerType (0x00485536)
// sits between the constructor and createCrate but is defined in
// CreateCrateDieTestKillerType.cpp: it reads the same kind-of mask through the
// ledger's BitFlags<116> names, onDie through BitFlags<218>::any.
//
// Target evidence, BFME 2 deltas against the donor:
// - onDie (0x004857B3) is slot 0 of the +0x10 DieModuleInterface table
//   0x00C4A744 the constructor stores, so `this` is CreateCrateDie +0x10. It
//   calls the four tests and createCrate with the CreateCrateDie this; the
//   veterancy test is gone, and an empty kind-of mask is tested with any().
//   PLAYER_COMPUTER is Player +0x5C == 1, the default team Player +0x2EC, the
//   AI interface Object +0x258 and its crate slot +0x238.
// - The two lists are STLport lists: the module data's crate names at +0x38,
//   the template's (name, chance) entries at +0x3C. CrateTemplate keeps the
//   name at +0x10 (CrateSystem's rowed setName), the chance at +0x14, the
//   7-dword kind-of mask at +0x1C, the science at +0x38 and isOwnedByMaker at
//   +0x40.
// - createCrate reads the layer first and the position only after the
//   template lookup; FindPositionOptions keeps Zero Hour's order and defaults
//   (-99999.9 start angle, 1e10 z delta). newObject takes a zeroed 16-byte
//   status mask by address and a trailing bool.
// - The random draws carry the retail file name and lines 0x70, 0xA7, 0xE2.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <string.h>
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;
typedef int Int;

#define CREATE_CRATE_DIE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Die\\CreateCrateDie.cpp"

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);
#define GameLogicRandomValueReal(lo, hi, line) GetGameLogicRandomValueReal(lo, hi, CREATE_CRATE_DIE_FILE, line)

#define PI 3.14159265359f

enum ObjectID
{
	INVALID_ID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum TerrainDecalType
{
	TERRAIN_DECAL_CRATE = 5
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

template <int NUMBITS> class BitFlags
{
public:
	Bool any() const;	// 0x002C7501

private:
	unsigned int m_bits[7];
};

typedef BitFlags<218> KindOfMaskType;

class ThingTemplate;
class Team;
class ModuleData;
class Object;

class Player
{
public:
	Bool hasScience(ScienceType t) const;
	PlayerType getPlayerType() const { return m_playerType; }
	Team *getDefaultTeam() const { return m_defaultTeam; }

private:
	unsigned char m_pad000[0x5C];
	PlayerType m_playerType;	// +0x5C
	unsigned char m_pad060[0x2EC - 0x60];
	Team *m_defaultTeam;	// +0x2EC
};

class AIUpdateInterface
{
public:
	void notifyCrate(ObjectID id) { m_crateCreated = id; }

private:
	unsigned char m_pad000[0x238];
	ObjectID m_crateCreated;	// +0x238
};

class Drawable
{
public:
	void rva00272870(Int decalType);	// 0x00272870, setTerrainDecal
	void rva002728C5(Real x, Real y);	// 0x002728C5, setTerrainDecalSize
};

// 0x00270644, setTerrainDecalFadeTarget, rowed under its own address class.
class Rva00270644
{
public:
	void rva00270644(Real target, Real rate);
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }

private:
	void *m_vptr;
	unsigned char m_pad04[0x10 - 0x04];
	Real m_majorRadius;	// +0x10
};

class Thing
{
public:
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;
	Player *getControllingPlayer() const;
	void setTeam(Team *team);
	Int rva0028B511() const;	// 0x0028B511, getLayer
	void rva0028B4CE(PathfindLayerEnum layer);	// 0x0028B4CE, setLayer

	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_pos;	// +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;	// +0x74
	unsigned char m_pad078[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;	// +0xA8
	unsigned char m_pad0BC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;	// +0x258
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct crateCreationEntry
{
	AsciiString crateName;
	Real crateChance;
};

typedef _STL::list<crateCreationEntry> crateCreationEntryList;
typedef crateCreationEntryList::const_iterator crateCreationEntryConstIterator;

typedef _STL::list<AsciiString> AsciiStringList;
typedef AsciiStringList::const_iterator AsciiStringListConstIterator;

class CrateTemplate
{
public:
	unsigned char m_overridable[0x10];	// Overridable
	AsciiString m_name;	// +0x10
	Real m_creationChance;	// +0x14
	Int m_veterancyLevel;	// +0x18
	KindOfMaskType m_killedByTypeKindof;	// +0x1C
	ScienceType m_killerScience;	// +0x38
	crateCreationEntryList m_possibleCrates;	// +0x3C
	Bool m_isOwnedByMaker;	// +0x40
};

class CrateSystem
{
public:
	CrateTemplate *friend_findCrateTemplate(AsciiString name);
};
extern CrateSystem *TheCrateSystem;

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }

	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;

enum
{
	FPF_NONE = 0,
	FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS = 0x00000008
};

struct FindPositionOptions
{
	FindPositionOptions()
	{
		flags = FPF_NONE;
		minRadius = 0.0f;
		maxRadius = 0.0f;
		startAngle = -99999.9f;
		maxZDelta = 1e10f;
		ignoreObject = 0;
		sourceToPathToDest = 0;
		relationshipObject = 0;
	}

	unsigned int flags;
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
	static Bool findPositionAround(const Coord3D *center, const FindPositionOptions *options, Coord3D *result);
};

class DamageInfo
{
public:
	struct In
	{
		ObjectID m_sourceID;
	};

	unsigned char m_pad00[0x08];
	In in;	// +0x08
};

class CreateCrateDieModuleData
{
public:
	unsigned char m_dieModuleData[0x38];	// DieModuleData
	AsciiStringList m_crateNameList;	// +0x38
};

class Thing;

class ObjectModule
{
public:
	virtual void objectModuleAnchor();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

class DieModule : public ObjectModule, public BehaviorModuleInterface, public DieModuleInterface
{
public:
	DieModule(Thing *thing, const ModuleData *moduleData);

protected:
	Bool isDieApplicable(const DamageInfo *damageInfo) const;
};

class CreateCrateDie : public DieModule
{
public:
	CreateCrateDie(Thing *thing, const ModuleData *moduleData);
	static NameKeyType rva0004854AB();

	virtual void onDie(const DamageInfo *damageInfo);

private:
	const CreateCrateDieModuleData *getCreateCrateDieModuleData() const
	{
		return (const CreateCrateDieModuleData *)getModuleData();
	}

	Bool testCreationChance(const CrateTemplate *currentCrateData);
	Bool testKillerType(const CrateTemplate *currentCrateData, Object *killer);
	Bool testKillerScience(const CrateTemplate *currentCrateData, Object *killer);
	Object *createCrate(const CrateTemplate *currentCrateData);
};

// ?testCreationChance@CreateCrateDie@@AAE_NPBVCrateTemplate@@@Z
Bool CreateCrateDie::testCreationChance(const CrateTemplate *currentCrateData)
{
	Real testAgainst = currentCrateData->m_creationChance;
	Real testWith = GameLogicRandomValueReal(0, 1, 0x70);

	return testWith < testAgainst;
}

// ?testKillerScience@CreateCrateDie@@AAE_NPBVCrateTemplate@@PAVObject@@@Z
Bool CreateCrateDie::testKillerScience(const CrateTemplate *currentCrateData, Object *killer)
{
	if (killer == 0)
		return false;

	// killer's player must have the listed science
	Player *killerPlayer = killer->getControllingPlayer();

	if (killerPlayer == 0)
		return false;

	if (!killerPlayer->hasScience(currentCrateData->m_killerScience))
		return false;

	return true;
}

// ?rva0004854AB@CreateCrateDie@@SA?AW4NameKeyType@@XZ
// The cached pool-name key: retail stores nameToKey's result and returns it.
NameKeyType CreateCrateDie::rva0004854AB()
{
	static NameKeyType TheCreateCrateDiePoolKey =
		TheNameKeyGenerator->nameToKey("CreateCrateDie");
	return TheCreateCrateDiePoolKey;
}

// ??0CreateCrateDie@@QAE@PAVThing@@PBVModuleData@@@Z
CreateCrateDie::CreateCrateDie(Thing *thing, const ModuleData *moduleData)
	: DieModule(thing, moduleData)
{
}

// ?createCrate@CreateCrateDie@@AAEPAVObject@@PBVCrateTemplate@@@Z
Object *CreateCrateDie::createCrate(const CrateTemplate *currentCrateData)
{
	PathfindLayerEnum layer = (PathfindLayerEnum)getObject()->rva0028B511();

	// CreationChance is used for the success of this block, but this block can have any number of potential actual crates
	Real multipleCratePick = GameLogicRandomValueReal(0, 1, 0xA7);
	Real multipleCrateRunningTotal = 0;
	AsciiString crateName = "";

	for (crateCreationEntryConstIterator iter = currentCrateData->m_possibleCrates.begin();
			iter != currentCrateData->m_possibleCrates.end();
			iter++)
	{
		multipleCrateRunningTotal += (*iter).crateChance;
		if (multipleCrateRunningTotal > multipleCratePick)
		{
			crateName = (*iter).crateName;
			break;
		}
	}

	const ThingTemplate *crateType = TheThingFactory->findTemplate(crateName);
	if (crateType == 0)
		return 0;

	Coord3D centerPoint;
	centerPoint.x = getObject()->getPosition()->x;
	centerPoint.y = getObject()->getPosition()->y;
	centerPoint.z = getObject()->getPosition()->z;
	Bool spotFound = false;
	Coord3D creationPoint;
	FindPositionOptions fpOptions;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 5.0f;
	fpOptions.relationshipObject = getObject();
	fpOptions.flags = FPF_IGNORE_ALLY_OR_NEUTRAL_UNITS; // So the dead guy won't block, nor will his dead hulk.
	if (layer != LAYER_GROUND)
	{
		creationPoint = centerPoint;
		spotFound = true;
	}
	else if (PartitionManager::findPositionAround(&centerPoint, &fpOptions, &creationPoint))
	{
		spotFound = true;
	}
	else
	{
		// If the tight ignore units scan fails, then try a great big scan so we appear on the edge
		// of the large dead thing (building rubble)
		fpOptions.minRadius = 0.0f;
		fpOptions.maxRadius = 125.0f;
		fpOptions.relationshipObject = 0;
		fpOptions.flags = FPF_NONE;
		if (PartitionManager::findPositionAround(&centerPoint, &fpOptions, &creationPoint))
		{
			spotFound = true;
		}
	}

	if (spotFound)
	{
		CreateMask statusBits;
		Object *newCrate = TheThingFactory->newObject(crateType, 0, &statusBits, false);
		newCrate->setPosition(&creationPoint);
		newCrate->setOrientation(GameLogicRandomValueReal(0, 2 * PI, 0xE2));
		newCrate->rva0028B4CE(layer);

		Drawable *crateDrawable = newCrate->getDrawable();

		if (crateDrawable)
		{
			crateDrawable->rva00272870(TERRAIN_DECAL_CRATE);
			crateDrawable->rva002728C5(2.5f * newCrate->getGeometryInfo().getMajorRadius(),
				2.5f * newCrate->getGeometryInfo().getMajorRadius());
			((Rva00270644 *)crateDrawable)->rva00270644(1.0f, 0.03f);
		}

		return newCrate;
	}
	return 0;
}

// ?onDie@CreateCrateDie@@UAEXPBVDamageInfo@@@Z
void CreateCrateDie::onDie(const DamageInfo *damageInfo)
{
	if (!isDieApplicable(damageInfo))
		return;

	const CrateTemplate *currentCrateData = 0;
	Object *killer = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
	Object *me = getObject();

	if (killer && killer->getRelationship(me) == ALLIES)
		return; //Nope, no crate for killing ally at all.

	for (AsciiStringListConstIterator iter = getCreateCrateDieModuleData()->m_crateNameList.begin();
			iter != getCreateCrateDieModuleData()->m_crateNameList.end();
			iter++)
	{
		currentCrateData = TheCrateSystem->friend_findCrateTemplate(*iter);
		if (currentCrateData)
		{
			if (!testCreationChance(currentCrateData))
				continue; // always test this

			if (currentCrateData->m_killedByTypeKindof.any() && !testKillerType(currentCrateData, killer))
				continue; //If this is set up to test and it fails

			if ((currentCrateData->m_killerScience != SCIENCE_INVALID) && !testKillerScience(currentCrateData, killer))
				continue; //If this is set up to test and it fails

			Object *crate = createCrate(currentCrateData); //Make the crate
			if (crate)
			{
				// Design needs to set ownership of crates sometimes
				if (currentCrateData->m_isOwnedByMaker)
				{
					crate->setTeam(me->getControllingPlayer()->getDefaultTeam());
				}

				if (killer)
				{
					// If the killer is a computer controlled player, notify that the crate exists.
					if (killer->getControllingPlayer() &&
						killer->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
					{
						AIUpdateInterface *ai = killer->getAIUpdateInterface();
						if (ai)
						{
							ai->notifyCrate(crate->getID());
						}
					}
				}
			}
		}
	}
}
