// cl: /I. /O1 /Ob1 /G7 /arch:SSE /Oy- /Ireference/shims/moduledata /ICode/GameEngine/Source/Common /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ow
// platformsdk
// stlport
// AIPlayer::queueSupplyTruck, RVA 0x004F37B0..0x004F3DB1.
// ZH donor logic with BFME2 layouts, three temporary filters and native call order.
// /Ow is local to this unit; it changes the repeated filter-vtable allocation.
// See reverse/attempt_support/queue-supply-truck-20261023-max/readme.md.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <windows.h>
#include <list>
#include <vector>

// GameLogic comes from the canonical GameLogicObjectLookupView.h.
#include "ascii_string.h"
typedef bool Bool;
typedef int Int;
typedef float Real;
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include <math.h>
class ThingTemplate;
class Player;
class Team;
template <class OBJCLASS> class DLINK_ITERATOR;

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13,
	OBJECT_STATUS_RECONSTRUCTING = 0x15
};

template <int N>
class BitFlags
{
public:
	Bool any() const;
	Bool test(Int bit) const { return (m_bits[0] & (1 << bit)) != 0; }
	unsigned int m_bits[1];
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Int rva0033A69A(const Player *player, Int a, Int b) const;
	const AsciiString &getName() const { return m_name; }
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
	ThingTemplate *friend_getNextTemplate() const { return m_nextThingTemplate; }
	unsigned char m_pad000[0x64];
	AsciiString m_name;				// +0x64
	unsigned char m_pad068[0xB0 - 0x68];
	Real m_boundingCircleRadius;			// +0xB0
	unsigned char m_padB4[0x109 - 0xB4];
	unsigned char m_kindOf109;			// +0x109, bit 0x40 = KINDOF_DOZER
	unsigned char m_kindOf10A;unsigned char m_pad10B;unsigned char m_kindOf10C;unsigned char m_pad10D[0x10F - 0x10D];
	unsigned char m_kindOf10F;			// +0x10F, bit 0x80 = factory
	unsigned char m_pad110[0x11B - 0x110];
	unsigned char m_bfme11B;			// +0x11B, bit 0x20 = free to build
	unsigned char m_pad11C[0x484 - 0x11C];
	ThingTemplate *m_nextThingTemplate;		// +0x484
	unsigned char m_pad488[0x633 - 0x488];
	unsigned char m_bfme633;			// +0x633
};

class Object;
enum BodyDamageType { BODY_PRISTINE = 0 };
class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *thing, Int a, Int b);
};
class Rva0037E6E8
{
public:
	Int rva0037E649(Int index, Object *obj);
};

enum ScienceType { SCIENCE_INVALID = -1 };
enum NameKeyType { NAMEKEY_INVALID = 0 };

class TeamPrototype;
// Retail calls the team list's base destructor (0x002ABB44) with no EH state
// transition before it, here and in Player at 0x002AE8BC, so cl saw it as
// nothrow; list<int>'s 0x004EC395 keeps the stores everywhere.
namespace _STL {
template <> inline _List_base<TeamPrototype *, allocator<TeamPrototype *> >::~_List_base() throw()
{
	clear();
	_M_node.deallocate(_M_node._M_data, 1);
}
}
typedef _STL::list<TeamPrototype *> PlayerTeamList;

class StaticNameKey
{
public:
	NameKeyType key() const;
	operator NameKeyType() const { return key(); }
private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;
extern const StaticNameKey TheKey_objectInitialHealth;
extern const StaticNameKey TheKey_objectUnsellable;

class Dict
{
public:
	Dict(Int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }
	void setBool(Int key, Bool value);
	void setInt(Int key, Int value);
	void setAsciiString(Int key, const AsciiString &value);
private:
	void releaseData();
	void *m_data;
};

class BuildListInfo
{
public:
	// getBuildingName and getTemplateName: retail calls the folded by-value
	// AsciiString copies of +4 and +8.
	AsciiString rva00564DF2() const;
	AsciiString rva000AF1DD() const;
	Int getHealth() const { return m_health; }
	Bool getUnsellable() const { return m_unsellable; }
	void setUnderConstruction(Bool construction) { m_underConstruction = construction; }
	BuildListInfo *getNext() const { return m_next; }
	const Coord3D *getLocation() const { return &m_location; }
	ObjectID getObjectID() const { return m_objectID; }
	Bool isSupplyBuilding() const { return m_isSupplyBuilding; }
	Int getDesiredGatherers() const { return m_desiredGatherers; }
	Int getCurrentGatherers() const { return m_currentGatherers; }
	void setCurrentGatherers(Int count) { m_currentGatherers = count; }

	unsigned char m_pad00[0x0C];
	Coord3D m_location;			// +0x0C
	unsigned char m_pad18[0x2C - 0x18];
	BuildListInfo *m_next;			// +0x2C
	unsigned char m_pad30[0x34 - 0x30];
	Int m_health;				// +0x34
	unsigned char m_pad38[0x39 - 0x38];
	Bool m_unsellable;			// +0x39
	unsigned char m_pad3A[0x45 - 0x3A];
	Bool m_underConstruction;		// +0x45
	Bool m_isSupplyBuilding;		// +0x46
	unsigned char m_pad47[0x48 - 0x47];
	ObjectID m_objectID;			// +0x48
	unsigned char m_pad4C[0x78 - 0x4C];
	Int m_desiredGatherers;			// +0x78
	Int m_currentGatherers;			// +0x7C
};

enum Relationship {ENEMIES=0};
class Player
{
public:
	BuildListInfo *getBuildList() const { return m_buildList; }
	const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
	Int getSciencePurchasePoints() const { return m_sciencePurchasePoints; }
	NameKeyType getPlayerNameKey() const { return m_playerNameKey; }
	Relationship getRelationship(const Team *)const;
	Team *getDefaultTeam()const{return m_defaultTeam;}
	const AsciiString &getSide() const { return m_side; }
	Bool isCapableOfPurchasingScience(ScienceType science) const;
	Bool attemptToPurchaseScience(ScienceType science);

	unsigned char m_pad000[0x24];
	Int m_sciencePurchasePoints;		// +0x24
	unsigned char m_pad028[0x50 - 0x28];
	NameKeyType m_playerNameKey;		// +0x50
	unsigned char m_pad054[0x58 - 0x54];
	AsciiString m_side;			// +0x58
	unsigned char m_pad05C[0x94 - 0x5C];
	unsigned int m_money;				// +0x94
	unsigned char m_pad098[0x278 - 0x98];
	BuildListInfo *m_buildList;		// +0x278
	unsigned char m_pad27C[0x2EC - 0x27C];
	Team *m_defaultTeam;			// +0x2EC
	unsigned char m_pad2F0[0x32C - 0x2F0];
	PlayerTeamList m_playerTeamPrototypes;	// +0x32C
	unsigned char m_pad330[0x338 - 0x330];
	Bool m_canBuildUnits;			// +0x338
	Bool getCanBuildUnits() const { return m_canBuildUnits; }
	void setCanBuildUnits(Bool canBuild) { m_canBuildUnits = canBuild; }
	unsigned char m_pad339[0x735 - 0x339];
	Bool m_bfme735;					// +0x735
	unsigned char m_pad736[0x738 - 0x736];
	union
	{
		Rva0037EE4C m_738;			// +0x738
		Rva0037E6E8 m_738b;
	};
};

class DozerAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual Bool isTaskPending(int task);		// +0x18
	virtual void slot1c();
	virtual Bool isAnyTaskPending();		// +0x20
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual Bool isCurrentlyFerryingSupplies();	// +0x14
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void setForceWantingState(Bool forceWanting);	// +0x2C
	virtual Bool isForcedIntoWantingState();	// +0x30
	virtual void slot34();virtual void slot38();virtual ObjectID getPreferredDockID() const;
};

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };

// The rowed wrapper at 0x0047971C takes the exit path by reference; its
// placeholder class is this vector of points.
class Rva0035149F : public _STL::vector<Coord3D>
{
};

class Object;

class LocomotorSet;

class AICommandInterface
{
public:
	void rva0047971C(const Rva0035149F &path, Object *ignoreObject, CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void aiDock(Object *obj, CommandSourceType cmdSource);
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);	// ZH aiRepair
};

class StateMachine
{
public:
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }

	unsigned char m_pad00[0x24];
	Coord3D m_goalPosition;			// +0x24
};

class AIUpdateInterface
{
public:
	// The AICommandInterface base sits at +0x20.
	AICommandInterface *getCommandInterface() { return (AICommandInterface *)((char *)this + 0x20); }
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)((const char *)this + 0x1CC); }
	Bool isMoving() const;
	StateMachine *getStateMachine() const { return m_stateMachine; }
	const Coord3D *getGoalPosition() const { return getStateMachine()->getGoalPosition(); }

	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00c();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01c();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02c();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03c();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04c();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05c();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06c();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07c();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08c();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09c();
	virtual void slot0a0();
	virtual void slot0a4();
	virtual void slot0a8();
	virtual void slot0ac();
	virtual void slot0b0();
	virtual void slot0b4();
	virtual void slot0b8();
	virtual void slot0bc();
	virtual void slot0c0();
	virtual void slot0c4();
	virtual void slot0c8();
	virtual void slot0cc();
	virtual void slot0d0();
	virtual void slot0d4();
	virtual void slot0d8();
	virtual void slot0dc();
	virtual void slot0e0();
	virtual void slot0e4();
	virtual void slot0e8();
	virtual void slot0ec();
	virtual void slot0f0();
	virtual void slot0f4();
	virtual void slot0f8();
	virtual void slot0fc();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10c();
	virtual void slot110();
	virtual void slot114();
	virtual void slot118();
	virtual void slot11c();
	virtual void slot120();
	virtual void slot124();
	virtual void slot128();
	virtual void slot12c();
	virtual void slot130();
	virtual void slot134();
	virtual void slot138();
	virtual void slot13c();
	virtual void slot140();
	virtual void slot144();
	virtual void slot148();
	virtual void slot14c();
	virtual void slot150();
	virtual void slot154();
	virtual void slot158();
	virtual void slot15c();
	virtual void slot160();
	virtual void slot164();
	virtual void slot168();
	virtual void slot16c();
	virtual void slot170();
	virtual DozerAIInterface *getDozerAIInterface();		// +0x174
	virtual void slot178();
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface();	// +0x17C
	virtual void slot180();
	virtual void slot184();
	virtual void slot188();
	virtual void slot18c();
	virtual void slot190();
	virtual void slot194();
	virtual void slot198();
	virtual void joinTeam();					// +0x19C
	virtual void slot1a0();
	virtual void slot1a4();
	virtual void slot1a8();
	virtual void slot1ac();
	virtual void slot1b0();
	virtual void slot1b4();
	virtual Bool isIdle() const;					// +0x1B8

	unsigned char m_pad004[0x30 - 0x04];
	StateMachine *m_stateMachine;			// +0x30
	unsigned char m_pad034[0x3BE - 0x34];
	Bool m_bfme3BE;					// +0x3BE
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual BodyDamageType getDamageState() const;	// +0x20
};

class Object
{
public:
	Player *getControllingPlayer() const;
	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getID() const { return m_id; }
	Bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BC58(Int which);
	AIUpdateInterface *getAI() const { return m_ai; }
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool isKindOfDozer() const { return (getTemplate()->m_kindOf109 & 0x40) != 0; }
	__forceinline class Module *queryModule(NameKeyType key) const {return findModule(key);}
protected: class Module *findModule(NameKeyType) const;
public:
	void setTeam(Team *team);
	void rva00291298(AsciiString name, Int value);
	void updateObjValuesFromMapProperties(Dict *properties);
	void setStatus(ObjectStatusTypes status, Bool set);
	void clearStatus(ObjectStatusTypes status) { setStatus(status, false); }

	void *m_vtable;
	ThingTemplate *m_template;			// +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_pos;					// +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id;					// +0x74
	unsigned char m_pad078[0x8C - 0x78];
	Object *m_next;					// +0x8C
	unsigned char m_pad090[0xB8-0x90];Real m_geometryRadius;unsigned char m_padBC[0x1C8-0xBC];
	Real getGeometryRadius() const { return m_geometryRadius; }
	BitFlags<11> m_disabledMask;			// +0x1C8
	unsigned char m_pad1CC[0x254 - 0x1CC];
	BodyModuleInterface *m_body;			// +0x254
	AIUpdateInterface *m_ai;			// +0x258
	unsigned char m_pad25C[0x304 - 0x25C];
	Team *m_team;					// +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_privateStatus;			// +0x438
};

class BuildAssistant
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual Bool isPossibleToMakeUnit(Object *factory, const ThingTemplate *thing, Int buildIndex);	// +0x64
};
extern BuildAssistant *TheBuildAssistant;

class ProductionEntry
{
public:
	void *m_vtable;
	Int m_type;
	ThingTemplate *m_thing;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Int requestUniqueUnitID(Int a, Int b, const AsciiString &name, Int d);	// +0x08
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual Bool queueCreateUnit(const ThingTemplate *unitType, Int quantity, Int productionID);	// +0x20
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual Int getProductionCount() const;		// +0x44
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual ProductionEntry *firstProduction() const;	// +0x54
};

class ThingFactory
{
public:
	void *rva002D06CA(const AsciiString *name);
	const ThingTemplate *findTemplate(const AsciiString &name) { return (const ThingTemplate *)rva002D06CA(&name); }
	ThingTemplate *firstTemplate() const { return m_firstTemplate; }
private:
	char m_pad00[0x0C];
	ThingTemplate *m_firstTemplate;		// +0x0C
};
extern ThingFactory *TheThingFactory;

struct Rva002A8AB1Record
{
	void *rva004EC088(Int kind, void *list, const void *name);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
	Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name);
};
extern TeamFactory *TheTeamFactory;

enum { MAX_KEY_SKILLS = 20 };
struct TSkillSet
{
	Int m_numSkills;
	ScienceType m_skills[MAX_KEY_SKILLS];
};

class AISideInfo
{
public:
	void *m_vtable;
	AsciiString m_side;			// +0x04
	Int m_easy;				// +0x08
	Int m_normal;				// +0x0C
	Int m_hard;				// +0x10
	TSkillSet m_skillSet1;			// +0x14
	TSkillSet m_skillSet2;			// +0x68
	TSkillSet m_skillSet3;			// +0xBC
	TSkillSet m_skillSet4;			// +0x110
	TSkillSet m_skillSet5;			// +0x164
	AsciiString m_baseDefenseStructure1;	// +0x1B8
	AISideInfo *m_next;			// +0x1BC
};

struct TAiData
{
	char m_pad000[0x0C];
	unsigned int m_resourcesWealthy;	// +0x0C
	unsigned int m_resourcesPoor;	// +0x10
	char m_pad014[0x1C - 0x14];
	Real m_teamWealthyMod;		// +0x1C
	char m_pad020[0x24 - 0x20];
	Real m_teamPoorMod;		// +0x24
	float m_teamResourcesToBuild;	// +0x28
	char m_pad02C[0x5C - 0x2C];
	Real m_maxRecruitDistance;	// +0x5C
	char m_pad060[0xF4 - 0x60];
	AISideInfo *m_sideInfo;		// +0xF4
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// The rowed body at 0x001FF5F2 under its pinned address spelling
// (Zero Hour's getInternalNameForScience).
class ScienceStore
{
public:
	AsciiString rva001FF5F2(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Pathfinder
{
public:
	Bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

class AI
{
public:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;	// +0x10
	char m_pad14[0x18 - 0x14];
	TAiData *m_aiData;		// +0x18
	const TAiData *getAiData() const { return m_aiData; }
	Pathfinder *pathfinder() { return m_pathfinder; }
};
extern AI *TheAI;

struct TCreateUnitsInfo
{
	Int minUnits;			// +0x00
	Int maxUnits;			// +0x04
	Int m_08;			// +0x08
	AsciiString m_bfmeString0C;	// +0x0C
	AsciiString unitThingName;	// +0x10
	Int m_14;			// +0x14
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class TeamTemplateInfo:public Snapshot {
public:
 TCreateUnitsInfo m_unitsInfo[7];Int m_numUnitsInfo;Coord3D m_homeLocation;Bool m_hasHomeLocation;
 char m_padBD[0xE7-0xBD];Bool m_automaticallyReinforce;char m_padE8[0xEC-0xE8];Int m_maxInstances;mutable Int m_productionPriority;
};
class TeamPrototype
{
public:
	const TeamTemplateInfo *getTemplateInfo()const{return (const TeamTemplateInfo *)((const char *)this+0x12c);}
	Bool evaluateProductionCondition();
	Int countTeamInstances();
	const AsciiString &getName() const { return m_name; }
	Bool getIsSingleton() const { return (m_flags & 1) != 0; }
	void rva0039D761();		// clears m_numUnitsInfo

	const AsciiString &getOwnerName() const { return m_owner; }
	const AsciiString &getProductionCondition() const { return m_productionCondition; }
	Bool getExecuteActions() const { return m_executeActions; }

	char m_pad000[0x10];
	AsciiString m_owner;			// +0x10
	AsciiString m_name;			// +0x14
	Int m_flags;				// +0x18
	char m_pad01C[0x130 - 0x1C];
	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
	Int m_numUnitsInfo;			// +0x1D8
	Coord3D m_homeLocation;			// +0x1DC
	Bool m_hasHomeLocation;			// +0x1E8
	char m_pad1E9[0x210 - 0x1E9];
	Bool m_bfme210;				// +0x210
	char m_pad211[2];
	Bool m_automaticallyReinforce; // +0x213
	char m_pad214[0x218 - 0x214];
	Int m_maxInstances;			// +0x218
	Int m_productionPriority;		// +0x21C
	char m_pad220[0x23C - 0x220];
	AsciiString m_productionCondition;	// +0x23C
	Bool m_executeActions;			// +0x240
	char m_pad241[0x31C - 0x241];
	Bool m_bfme31C;				// +0x31C
	Bool m_bfme31D;				// +0x31D
	char m_pad31E[0x334-0x31E];Team *m_teamInstances;
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
};

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance() { if (m_cur) m_cur = (m_cur->*m_getNextFunc)(); }
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

// BFME2's team-member iterator is a 24-byte object returned through a hidden
// pointer by Team::iterate_TeamMemberList (0x263864); advance is out of line
// at 0x263526.
template <> class DLINK_ITERATOR<Object>
{
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
private:
	Object *m_cur;
	unsigned char m_state[20];
};

class TeamPoolView {public:virtual ~TeamPoolView();};
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Rva0055B156:public Snapshot
{
public:
	void rva0055B156(int val);
};

class Team:public TeamPoolView,public Rva0055B156
{
public:
	virtual ~Team();
	Rva0055B156 *getSnapshotView(){return this;}
	char m_pad008[0x30 - 0x08];
	TeamPrototype *m_proto;			// +0x30
	unsigned int m_id;			// +0x34
	Object *m_firstMember;
	char m_pad03C[0x5D - 0x3C];
	Bool m_active;				// +0x5D
	Bool m_created;				// +0x5E
	char m_pad05F[0x110 - 0x5F];
	Bool m_bfme110;				// +0x110
	Bool m_bfme111;				// +0x111

	Team *dlink_next_TeamInstanceList() const;
	Bool rva0039DEC4();
	void countObjectsByThingTemplate(Int,const ThingTemplate *const *,Bool,Int *,Bool) const;
	Object *getFirstItemIn_TeamMemberList() const {return m_firstMember;}
	void rva0039D889(Bool flag);
	void disband();
	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *pos, Real maxDist, Int a, Int b, Int c);
	Bool rva0039DFF8();
	Bool hasAnyObjects(Bool ignoreBuilding);
	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	const AsciiString &getOwnerName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getOwnerName(); }
	const AsciiString &getName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getName(); }
	TeamPrototype *getPrototype() const { return m_proto; }
	void rva0039DA2A(Coord3D *center) const;
	__forceinline void deleteInstance() { ::delete this; }
};

#include "WorkOrder.h"
#include "TeamInQueue.h"

class GlobalData
{
public:
	char m_pad000[0x9B8];
	Int m_debugAI;				// +0x9B8
	char m_pad9BC[0xA5C-0x9BC];Int m_baseValuePerSupplyBox;
};
extern GlobalData *TheWritableGlobalData;

class Script
{
public:
	void *getAction() const { return m_action; }
private:
	char m_pad00[0x34];
	void *m_action;				// +0x34
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

enum { MAX_STRUCTURES_TO_REPAIR = 2 };

class AIPlayer
{
protected:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
public:
	virtual void update();						// +0x14
protected:
	virtual void slot06();
public:
	virtual void onUnitProduced(Object *factory, Object *unit);	// +0x1C
	virtual void onStructureProduced(Object *factory, Object *bldg);	// +0x20
	virtual void buildSpecificAITeam(TeamPrototype *teamProto, Bool priorityBuild);	// +0x24
	virtual void recruitSpecificAITeam(TeamPrototype *teamProto, Real recruitRadius, const Coord3D *pos);	// +0x28
	virtual Bool isSkirmishAI();					// +0x2C
protected:
	virtual void slot12();
	virtual void slot13();
public:
	virtual void repairStructure(ObjectID structure);		// +0x38
protected:
	virtual void slot15();
	virtual void checkReadyTeams();					// +0x40
	virtual void checkQueuedTeams();				// +0x44
	virtual void doTeamBuilding();					// +0x48
	virtual void doUpgradesAndSkills();				// +0x4C
	virtual Object *findDozer(const Coord3D *searchPosition);	// +0x50
	virtual void queueDozer();					// +0x54
	virtual Bool selectTeamToBuild();				// +0x58
	virtual Bool selectTeamToReinforce(Int minPriority);		// +0x5C
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);	// +0x60
	virtual Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);	// +0x64

	Object *findFactory(const ThingTemplate *thing, Bool busyOK, Int *buildIndex);
	Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory, Bool &notEnoughMoney);
	Bool rva004F13D8(TeamPrototype *proto);
	Bool dozerInQueue();
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
	void computeCenterAndRadiusOfBase(Coord3D *center, Real *radius);
	Bool getBaseCenter(Coord3D *pos) const { *pos = m_baseCenter; return m_baseCenterSet; }
	void queueSupplyTruck();
	void queueUnits();
	void updateBridgeRepair();
	DLINK_ITERATOR<TeamInQueue> iterate_TeamBuildQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamBuildQueue, &TeamInQueue::dlink_next_TeamBuildQueue);
	}
	DLINK_ITERATOR<TeamInQueue> iterate_TeamReadyQueue() const
	{
		return DLINK_ITERATOR<TeamInQueue>(m_teamReadyQueue, &TeamInQueue::dlink_next_TeamReadyQueue);
	}

public:
	void removeFrom_TeamBuildQueue(TeamInQueue *team);
	void prependTo_TeamReadyQueue(TeamInQueue *team);
	void removeFrom_TeamReadyQueue(TeamInQueue *team);
	void prependTo_TeamBuildQueue(TeamInQueue *team);
	void reverse_TeamBuildQueue();

private:
 // Fully inlined into queueSupplyTruck; no separate retail body.
 Int countSupplyHarvesters();
	TeamInQueue *m_teamBuildQueue;	// +0x04
	TeamInQueue *m_teamReadyQueue;	// +0x08
	Player *m_player;		// +0x0C
	Bool m_readyToBuildTeam;	// +0x10
	Int m_teamTimer;		// +0x14
	Int m_structureTimer;		// +0x18
	Int m_teamSeconds;		// +0x1C
	Int m_buildDelay;		// +0x20
	Int m_teamDelay;		// +0x24
	unsigned char m_pad28[0x30 - 0x28];
	Int m_skillsetSelector;		// +0x30
	Coord3D m_baseCenter;		// +0x34
	Bool m_baseCenterSet;		// +0x40
	unsigned char m_pad41[0x48 - 0x41];
	ObjectID m_structuresToRepair[MAX_STRUCTURES_TO_REPAIR];	// +0x48
	ObjectID m_repairDozer;		// +0x50
	Coord3D m_repairDozerOrigin;	// +0x54
	Int m_structuresInQueue;	// +0x60
	Bool m_dozerQueuedForRepair;	// +0x64
	Bool m_dozerIsRepairing;	// +0x65
	Int m_bridgeTimer;		// +0x68
};

enum { DOZER_TASK_BUILD = 0 };

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const {return DLINK_ITERATOR<Team>(m_teamInstances,&Team::dlink_next_TeamInstanceList);}


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


// vftable 0x00BFAD1C, allow 0x002611DD: no members (ZH's
// PartitionFilterOnMap).
namespace PartitionFilterTables {
extern "C" const void *const __identifier("??_7Rva002611DDFilter@@6B@")[];
}
class __declspec(novtable) Rva002611DDFilter : public Rva000421C8
{
public:
	Rva002611DDFilter() { *(const void **)this = PartitionFilterTables::__identifier("??_7Rva002611DDFilter@@6B@"); }
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
extern BitFlags<116> KINDOFMASK_NONE;

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

#include "../../Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;
#include "../../../Include/Common/Module.h"
class SupplyWarehouseDockUpdate:public Module{public:char m_pad08[0x88-8];int m_boxesStored;int getBoxesStored()const{return m_boxesStored;}};

/** Queue up a supply truck to be built. */
static __forceinline void restoreUnitBuild(Player *player,const Bool &saved) { _ReadWriteBarrier();player->setCanBuildUnits(saved); }
// ?countSupplyHarvesters@AIPlayer@@AAEHXZ absent-from-retail
__forceinline Int AIPlayer::countSupplyHarvesters() {
Int totalHarvesters;
	totalHarvesters = 0;

	// See how many harvesters we have servicing this supply src.
	// Scan my units.
	PlayerTeamList::const_iterator it;
	for (it = m_player->getPlayerTeams()->begin(); it != m_player->getPlayerTeams()->end(); ++it) {
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
			Team *team = iter.cur();
			if (!team) {
				continue;
			}
			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance()) {
				Object *obj = objIter.cur();
				if (!obj)  continue;
				if (!((obj->getTemplate()->m_kindOf10A&1)!=0)) continue;
				if (!obj->getAI()) continue;

				SupplyTruckAIInterface* supplyTruckAI = obj->getAI()->getSupplyTruckAIInterface();
				if( supplyTruckAI )	{
					totalHarvesters++;
				}
			}
		}
	}


return totalHarvesters;
}
void AIPlayer::queueSupplyTruck( void )
{
	Bool truckInQueue;
	truckInQueue = false;
	for ( DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
	{
		TeamInQueue *team = iter.cur();
		WorkOrder *order;
		for( order = team->m_workOrders; order; order = order->m_next )
		{
			// GLA dozers (workers) are also resource gatherers, so make sure it isn't a worker. jba.
			if (order->m_isResourceGatherer) {
				truckInQueue = true;
			}
		}
	}

	if (truckInQueue) {
		return; // already building a supply truck.
	}
	Int totalHarvesters=countSupplyHarvesters();

	/* Find the info building this. */
	for( BuildListInfo *info = m_player->getBuildList(); info; info = info->getNext() )
	{
		if (info->isSupplyBuilding() == false) continue;

		Int desiredGatherers = info->getDesiredGatherers();
		Int curGatherers = info->getCurrentGatherers();

		if (curGatherers>=desiredGatherers) {
			// Check & see if any have died.
			Object *supplyCenter = TheGameLogic->findObjectByID(info->getObjectID());
			// Check for supplies.
			if (!supplyCenter) continue;
			{
				if (((supplyCenter->getTemplate()->m_kindOf10C&0x40)!=0)) {
					continue; // don't consider rebuild holes.
				}
				// Make sure we have a supplies near it.
				Coord3D center;center.x=supplyCenter->m_pos.x;center.y=supplyCenter->m_pos.y;center.z=supplyCenter->m_pos.z;
				Real radius = 200.0f + supplyCenter->getGeometryRadius();

				// The filter chain is built from temporaries that die after the search.
				Object *supplySource = ThePartitionManager->getClosestObject(&center,radius,1,
					(&Rva0004584D(*(BfmeFixedStorage0004543D *)&Rva00045411BitSet(0,86), *(BfmeFixedStorage0004543D *)&KINDOFMASK_NONE))->link(Rva0026137EFilter(m_player,false).link(&Rva002611DDFilter())));	// Only find other.
                if (!supplySource) {
					// No supplies.
					continue;
				}
				static const NameKeyType key_warehouseUpdate = TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
				SupplyWarehouseDockUpdate *warehouseModule = (SupplyWarehouseDockUpdate*)supplySource->queryModule( key_warehouseUpdate );
				if( warehouseModule )	{
					Int availableCash = warehouseModule->getBoxesStored()*TheWritableGlobalData->m_baseValuePerSupplyBox;
					if (availableCash<=0) continue;
					if( m_player->getRelationship(supplySource->m_team) == 0 ) {
						continue;
					}
				}
				// Ok, it has supplies available near it.
				checkForSupplyCenter(info, supplyCenter);
				Int curGatherers = 0;
				// See how many harvesters we have servicing this supply src.
				// Scan my units.
				PlayerTeamList::const_iterator it;
				_STL::_List_node_base *initialEnd=*(_STL::_List_node_base **)((char *)m_player+0x32c); it._M_node=initialEnd->_M_next; if(it._M_node != initialEnd) do {
					for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
						Team *team = iter.cur();
						if (!team) {
							continue;
						}
						DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); for (Object *obj=(objIter.cur() ? objIter.cur() : objIter.cur()); obj; objIter.advance(),obj=(objIter.cur() ? objIter.cur() : objIter.cur())) {
							if (!obj)  continue;
							if (!((obj->getTemplate()->m_kindOf10A&1)!=0)) continue;
							// Keep the native object/AI register assignment across this load.
							_ReadWriteBarrier(); if (!obj->getAI()) continue;

							SupplyTruckAIInterface* supplyTruckAI = obj->getAI()->getSupplyTruckAIInterface();
							if( supplyTruckAI )	{
								ObjectID dock = supplyTruckAI->getPreferredDockID();
								if (dock == supplyCenter->getID()) {
									curGatherers++;
									if (!supplyTruckAI->isCurrentlyFerryingSupplies()) {
										// Note - although this is the ai, we are sending in CMD_FROM_PLAYER.
										// This causes the dock object to stick in the docking interface.
										// The supply truck ai issues dock commands, and they become confused.
										// Thus, player.  jba.  ;(
										obj->getAI()->getCommandInterface()->aiDock(supplyCenter,CMD_FROM_PLAYER);
									}
								}
							}
						}
					}

++it;
} while(it != m_player->getPlayerTeams()->end());
				//DEBUG_LOG(("Expected %d harvesters, found %d, need %d\n", info->getDesiredGatherers(),
				//	curGatherers, info->getDesiredGatherers()-curGatherers) );
				info->setCurrentGatherers(curGatherers);
			}
		} else {
			/* See if we have any "loose" harvesters (cause my supply center got nuked.) */
			PlayerTeamList::const_iterator it;
			for (it = m_player->getPlayerTeams()->begin(); it != m_player->getPlayerTeams()->end(); ++it) {
				for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
					Team *team = iter.cur();
					if (!team) continue;
					DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); for (Object *obj=objIter.cur(); obj; objIter.advance(),obj=objIter.cur()) {
						if (obj) _ReadWriteBarrier(); if (!obj)  continue;
						if (!((obj->getTemplate()->m_kindOf10A&1)!=0)) continue;
						if (!obj->getAI()) continue;

						SupplyTruckAIInterface* supplyTruckAI = obj->getAI()->getSupplyTruckAIInterface();
						if( supplyTruckAI )	{
							ObjectID dock = supplyTruckAI->getPreferredDockID();
							if (TheGameLogic->findObjectByID(dock)!=NULL) continue;
							if (supplyTruckAI->isCurrentlyFerryingSupplies() || supplyTruckAI->isForcedIntoWantingState())
							{
								// This thinks he is a gatherer, but doesn't have a preferred dock id.
								Object *center = TheGameLogic->findObjectByID(info->getObjectID());
								if (center) {
									info->setCurrentGatherers(info->getCurrentGatherers()+1);
									// Note - although this is the ai, we are sending in CMD_FROM_PLAYER.
									// This causes the dock object to stick in the docking interface.
									// The supply truck ai issues dock commands, and they become confused.
									// Thus, player.  jba.  ;(
									obj->getAI()->getCommandInterface()->aiDock(center,CMD_FROM_PLAYER);

									return;
								}
							}
						}
					}
				}
			}
			if (totalHarvesters >= desiredGatherers*3) {
				continue; // we got lotsa gatherers.
			}
			Bool canBuildUnits = m_player->getCanBuildUnits();
			// If we need a supply truck thingy, turn on unit building for a moment.
			m_player->setCanBuildUnits(true);
			const ThingTemplate *tTemplate = TheThingFactory->firstTemplate();
			while (tTemplate || (restoreUnitBuild(m_player,canBuildUnits), false)) {
				Bool isSupplyTruck = ((tTemplate->m_kindOf10A&1)!=0);;
				if (isSupplyTruck) {
					Object *factory = findFactory(tTemplate, false, NULL);
					if (factory) {
						// we can build one.
						WorkOrder *order = new WorkOrder;
						order->m_thing = tTemplate;
						order->m_factoryID = (ObjectID)0;
						order->m_numRequired = 1;
						order->m_required = true;
						order->m_isResourceGatherer =true;
						// prepend to head of list
						order->m_next = NULL;
						TeamInQueue *team = new TeamInQueue;
						// Put in front of queue.
						prependTo_TeamBuildQueue(team);
						team->m_priorityBuild = true;
						team->m_workOrders = order; _ReadWriteBarrier();
						team->m_frameStarted = TheGameLogic->getFrame();
						// Stick it on the default team
						team->m_team = m_player->getDefaultTeam();
						AsciiString teamName = "Supply truck - building one at the ";
						teamName.concat(factory->getTemplate()->getName());
						TheScriptEngine->AppendDebugMessage(teamName, false);
						m_teamDelay = 0;
						if (info->getCurrentGatherers()==-1) {
							// First one is automatic. jba.
							order->m_factoryID = factory->getID();
							info->setCurrentGatherers(0);
						}	else {
							startTraining( order, team->m_priorityBuild, team->m_team->getName());
						}
						goto factory_done;
					}
				}
				tTemplate = tTemplate->friend_getNextTemplate();
			}
			goto templates_done;
			factory_done:
			restoreUnitBuild(m_player,canBuildUnits);
			templates_done:;
		}
	}
}

