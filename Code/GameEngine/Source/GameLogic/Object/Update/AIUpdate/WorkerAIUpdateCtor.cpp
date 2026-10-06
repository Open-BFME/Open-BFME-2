// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// Zero Hour's WorkerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// WorkerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@WorkerAIUpdate@@AAEXXZ, retail 0x004A9ED5, 218 bytes. As in
// ZH: without a worker machine, make one (0x3C bytes, plain operator new;
// pinned ctor 0x004A9D79) and, where missing, the dozer (pinned 0x00488DAB)
// and supply truck (pinned 0x004A7010) machines, entering each one's default
// state (machine vslot 7) and the worker machine's last. The three machine
// pointers are the rowed dtor 0x004A9A12's +0x4C0/+0x4C4/+0x4C8.
//
// ??0WorkerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004AA3AB,
// 339 bytes. Target evidence: the body runs the pinned AIUpdateInterface
// ctor 0x0026E9BD and the implicit ctors of the three all-_purecall
// interfaces at +0x3E4/+0x3E8/+0x3EC, stores the final vtables (0x00854190
// primary, slot 0 the rowed ??_GWorkerAIUpdate 0x004A9EB9) and builds the
// 3x3 dock point array at +0x40C through __ehvec_ctor with an empty
// out-of-line element ctor/dtor (ICF-folded 0x0047A6A9/0x000B3FD0; the
// dtor's BfmeWorkerDockPoint). As in ZH it clears the rebuild flag and the
// dozer machine, the tasks (+0x3F0) and dock points, sets the current task
// to DOZER_TASK_INVALID and the build sub-task to
// DOZER_SELECT_BUILD_DOCK_LOCATION, clears the supply truck machine, +0x4A4
// with the +0x4A8 point and the +0x4B4 flag (where ZH clears the box count;
// newTask clears the same three where ZH clears the preferred dock, so their
// role is open), both force flags and the worker machine, then creates the
// machines. Other member roles past the dock points follow ZH's order
// (sub-task, preferred dock, the three flags, the machines); new in BFME 2:
// +0x4A0 and +0x4CC (set to 1, where ZH copied its supplies-depleted voice).
// The preferred dock is zeroed first.
//
// ??0WorkerStateMachine@@QAE@PAVObject@@@Z, retail 0x004A9D79, 169 bytes. As
// in ZH: the StateMachine base (rowed 0x004D79E1; name key 0xF80D13C5, flag
// false; vtable 0x00854058, the rowed Rva004A9964 dtor's), then ActAsDozer
// (rowed ctor 0x004A992A) with asDozerConditions (retail .rdata 0x00854410)
// and ActAsSupplyTruck (rowed ctor 0x004A9947) with asTruckConditions
// (0x008543F8), plain operator new of 0x20 bytes each.
//
// The two condition tests, ZH's supplyTruckSubMachineWantsToEnter (retail
// 0x004A9975, 70 bytes) and supplyTruckSubMachineReadyToLeave (0x004A99BB,
// 59), and WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy (0x004A98D6, 62)
// that the second calls: the machine owner's AI (Object +0x258), its AI
// state (the rowed getCurrentStateID 0x00262FC3) and forced-wanting flag
// (the supply truck interface at +0x3E8, vslot 12, reading +0x4BC); BFME 2
// also accepts AI state 47 besides AI_DOCK. The brain test reads the worker
// and supply truck machines' current state ids (+0x04 state, its +0x04 id).
//
// ?onDelete@WorkerAIUpdate@@UAEXXZ, retail 0x004AAB0B, 104 bytes (primary vslot 8; the
// dozer interface's slot 0 reaches it through its this-adjusting entry). As
// in ZH: cancel every pending task (dozer interface vslots 6 and 13), then
// clear MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED (Object +0x114 bit 5,
// notifying through the rowed 0x0028AE6D on change) on each task's target
// (+0x3F0 ids, the rowed GameLogic::findObjectByID). New in BFME 2: it ends
// with the dozer interface's finishBuildingSound (vslot 24, tail call).
//
// ?construct@WorkerAIUpdate@@UAEPAVObject@@PBVThingTemplate@@PBUCoord3D@@MPAVPlayer@@_NH@Z,
// retail 0x004A9FAF, 556 bytes (primary vslot 126, the rowed
// AIUpdateInterface::construct's slot). ZH's WorkerAIUpdate::construct: the
// rebuild flag (+0x4BD) and createMachines first, then the build checks
// through TheBuildAssistant (vslot 16 isLocationLegalToBuild with ZH's AI
// and human option masks 6 and 0x17, vslot 24 canMakeUnit for humans; the
// player type at +0x5C), the under-construction status mask (pinned builder
// 0x0023DA79; reconstructing is bit 21), newObject on the player's +0x2EC
// team, producer and builder, leaving the supply truck state (the +0x3EC
// interface's vslot 0), the cost and withdrawal, position, the flattened
// ground height, the pathfind map, the structure-created callback, zero
// construction percent (+0x280), one hit point (body +0x254, vslots 4 and
// 32), ZH's model conditions (67 set; 68 and 69 cleared) and the build task
// (dozer interface vslot 12). New in BFME 2: the AI skips canMakeUnit; the
// cost helper (pinned 0x0033A69A) also takes the builder object and -1, the
// withdrawal (rowed 0x003B0CB3) passes the player's +0x3BC member and true,
// the same member records the template and cost (rowed 0x0039BAD2) and the
// new object keeps the cost at +0x324; the sixth argument is unused.
// Callee identities: flattenTerrain 0x0028458F (called with the new object
// where ZH flattens; it returns at once when the object's +0xAC flag is set,
// as ZH does for small geometry, before reading its position) and
// onStructureCreated 0x002AA559 (ZH's callback slot, builder then structure).
//
// ?findGoodBuildOrRepairPositionAndTarget@WorkerAIUpdate@@IAEPAVObject@@PAV2@0AAUCoord3D@@@Z,
// retail 0x004AABB4, 426 bytes. Donor: BFME 1's
// WorkerAIUpdateFindGoodBuildOrRepairPositionAndTarget.cpp (BFME 1 0x002C9C40,
// name and protected member spelling carried from its ledger). Target
// evidence: its BEGIN log line names the function; called from the dozer
// interface's newTask with the full object. ZH's static
// DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget as a member: for a
// bridge (kind-of bit 22 on the template, Thing +0x04 then +0x108) it picks
// the reachable tower (bridge interface vslot 1, four towers, the pinned
// isPathAvailable) whose position (the pinned findGoodBuildOrRepairPosition
// 0x004AA4FE, whose own BEGIN line names it) is nearest, else it finds the
// target's position. The diagnostics are BFME's: fprintf to the logic
// random log file while the docking trace switch (0x00E03CA8, BFME 1's
// g_bfmeDockingTraceActive) is set; template name +0x64, id +0x74.
//
// ?newTask@WorkerAIUpdate@@UAEXW4DozerTask@@PAVObject@@@Z, retail 0x004AADB1,
// 671 bytes (dozer interface vslot 12, so its this is the +0x3E4
// interface). Donor: BFME 1's WorkerAIUpdateNewTaskBfme.cpp (BFME 1
// 0x002CA130) over ZH's WorkerAIUpdate::newTask: for a build or repair task
// it cancels a pending one (vslots 6 and 13), finds the position and target
// (rowed 0x004AABB4), sets the builder (rowed 0x0028AFE7) for builds and
// fills the three dock points; then it records the target id and frame
// (TheGameLogic +0x40), resets the dozer machine (vslot 6) and, when the
// worker machine acts as a supply truck, idles the AI (rowed aiIdle,
// CMD_FROM_AI) and sets the dozer state (vslot 8). As in BFME 1 the docking
// diagnostics run while the switch at 0x00DCBF44 (BFME 1's
// g_bfmeDockingDesyncLog) is set and raise the trace switch around the
// search. New in BFME 2: the cleared preferred-dock trio is +0x4A4, the
// +0x4A8 point and the +0x4B4 flag, and a build or repair also sets object
// status 97 on the worker and the AIUpdateInterface byte at +0x3BA.
#include "ascii_string.h"
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define FALSE false
#define TRUE true

struct _iobuf;
typedef struct _iobuf FILE;

extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

// The logic random log file; BFME 2's docking diagnostics write to it.
extern "C" FILE *theLogicRandomLogFile;

// BFME 1's names for the docking diagnostics switches.
extern bool g_bfmeDockingDesyncLog;
extern bool g_bfmeDockingTraceActive;

enum ObjectID
{
	INVALID_ID = 0
};

class Thing;
class ModuleData;
class Object;
class Player;
class Team;
class ThingTemplate;

enum StateReturnType
{
	STATE_CONTINUE,
	STATE_SUCCESS,
	STATE_FAILURE
};

typedef UnsignedInt StateID;
enum { INVALID_STATE_ID = 999999 };

class StateMachine;

struct State
{
public:
	virtual ~State();
	StateID getID() const { return m_ID; }
	StateMachine *getMachine() const { return m_machine; }
protected:
	StateID m_ID; // +0x04
	unsigned char m_pad08[0x18 - 0x08];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

struct StateConditionInfo
{
	Bool (*test)(State *thisState, void *userData);
	StateID toStateID;
	void *userData;
};

class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05();
	virtual void resetToDefaultState(); // vslot 6
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(StateID newStateID); // vslot 8
	void defineState(StateID id, struct State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = 0);
	StateID getCurrentStateID() const { return m_currentState ? m_currentState->getID() : INVALID_STATE_ID; }
	Object *getOwner() const { return m_owner; }
protected:
	State *m_currentState; // +0x04
	unsigned char m_pad08[0x14 - 0x08];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18]; // operator new size 0x3C
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z; the key is
// taken as one dword, as in the dozer machine's TU.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};

// ZH's ActAsDozerState (rowed ctor 0x004A992A).
class Rva004A992A : public State
{
public:
	Rva004A992A(StateMachine *machine);
};

// ZH's ActAsSupplyTruckState (rowed ctor 0x004A9947).
class Rva004A9947 : public State
{
public:
	Rva004A9947(StateMachine *machine);
};

enum
{
	AS_DOZER = 0,
	AS_SUPPLY_TRUCK
};

class WorkerStateMachine : public Rva004D759C
{
public:
	WorkerStateMachine(Object *owner);
	virtual ~WorkerStateMachine();

	static Bool supplyTruckSubMachineWantsToEnter(State *thisState, void *userData);
	static Bool supplyTruckSubMachineReadyToLeave(State *thisState, void *userData);
};

class DozerPrimaryStateMachine : public StateMachine
{
public:
	DozerPrimaryStateMachine(Object *owner);
};

enum
{
	ST_IDLE = 0,
	ST_BUSY
};

class SupplyTruckStateMachine : public StateMachine
{
public:
	SupplyTruckStateMachine(Object *owner);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	Object *getObject() const { return m_object; }
private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

class AICommandInterface
{
public:
	virtual void aiDoCommand();
	void aiIdle(CommandSourceType cmdSource);
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	// Primary vtable slots 1-8 (slot 0 is the destructor).
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07();
	virtual void onDelete(); // vslot 8
	Int getCurrentStateID() const;
	Bool isPathAvailable(const Coord3D *destination) const;
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3BA - 0x28];
protected:
	Bool m_3BA; // +0x3BA
private:
	unsigned char m_pad3BB[0x3E4 - 0x3BB];
};

enum ModelConditionFlagType
{
	MODELCONDITION_AWAITING_CONSTRUCTION = 67,
	MODELCONDITION_PARTIALLY_CONSTRUCTED = 68,
	MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED = 69 // +0x114 bit 5
};

// The two model condition mask builders (19 dwords each).
class Rva001E4912
{
public:
	Rva001E4912 *rva001E4912(int unused, unsigned int bit1, unsigned int bit2);
private:
	unsigned int m_words[19];
};

class Rva0028F59A
{
public:
	Rva0028F59A(int unused, int bit);
private:
	unsigned int m_words[19];
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_RECONSTRUCTING = 21,
	OBJECT_STATUS_97 = 97 // BFME 2's; set on a worker given a build or repair task
};

struct ObjectStatusMask
{
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit);
	void set(ObjectStatusTypes bit) { m_bits[bit >> 5] |= 1U << (bit & 31); }
	UnsignedInt m_bits[4];
};

// What ThingFactory::newObject takes: the initial status bits.
struct CreateMask : public ObjectStatusMask
{
};

class BodyModuleInterface
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual Real getHealth() const; // +0x10
	virtual void i05(); virtual void i06(); virtual void i07();
	virtual void i08(); virtual void i09(); virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, Int flag); // +0x80
};

enum KindOfType
{
	KINDOF_BRIDGE = 22
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	Int rva0033A69A(const Player *player, Int builder, Int a3) const;
private:
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x108 - 0x68];
	UnsignedInt m_kindOf[4]; // +0x108
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	void setProducer(Object *obj);
	void rva0028AFE7(Object *builder);
	void setStatus(ObjectStatusTypes bit, Bool set);
	void rva0028CFB2(const int *clear, const int *set);
	void setConstructionPercent(Real percent) { m_constructionPercent = percent; }
	void rva0028AE6D();
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Real m_constructionPercent; // +0x280
	unsigned char m_pad284[0x324 - 0x284];
public:
	Real m_buildCost; // +0x324
};

class Rva0039B795;

struct Rva0039BAD2Input;

// The player's +0x3BC member, under its two rowed spellings.
class Rva0039BAD2
{
public:
	void rva0039BAD2(Rva0039BAD2Input *what, Int cost);
};

class Rva0039B795 : public Rva0039BAD2
{
};

// The player's money (+0x90).
class Rva003B0D7C
{
public:
	UnsignedInt rva003B0CB3(UnsignedInt amount, Rva0039B795 *stats, Bool flag);
};

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Player
{
public:
	PlayerType getPlayerType() const { return m_playerType; }
	Rva003B0D7C *getMoney() { return &m_money; }
	Team *getDefaultTeam() const { return m_defaultTeam; }
	Rva0039B795 *getStats() { return &m_stats; }
	void onStructureCreated(Object *builder, Object *structure);
private:
	unsigned char m_pad000[0x5C];
	PlayerType m_playerType; // +0x5C
	unsigned char m_pad060[0x90 - 0x60];
	Rva003B0D7C m_money; // +0x90
	unsigned char m_pad091[0x2EC - 0x91];
	Team *m_defaultTeam; // +0x2EC
	unsigned char m_pad2F0[0x3BC - 0x2F0];
	Rva0039B795 m_stats; // +0x3BC
};


class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, Bool flag);
};

extern ThingFactory *TheThingFactory;

enum { CANMAKE_OK = 0 };
enum { LBC_OK = 0 };

// TheBuildAssistant.
class Rva00A027B8
{
public:
	enum
	{
		TERRAIN_RESTRICTIONS = 0x01,
		CLEAR_PATH = 0x02,
		NO_OBJECT_OVERLAP = 0x04,
		SHROUD_REVEALED = 0x10
	};
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual Int isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, Real angle,
		UnsignedInt options, Object *builderObject, Player *player); // +0x40
	virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual Int canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int quantity); // +0x60
};

extern Rva00A027B8 *g_00A027B8;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const; // +0x18
	void flattenTerrain(Object *obj);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};

extern AI *TheAI;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_MAX_TOWERS = 4
};

class BridgeBehaviorInterface
{
public:
	virtual void slot0();
	virtual ObjectID getTowerID(BridgeTowerType type); // vslot 1
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

inline Real sqr(Real x)
{
	return x * x;
}

enum AIStateType
{
	AI_DOCK = 14, // ZH's numbering (AI_IDLE 0 .. AI_DEAD 13)
	AI_STATE_47 = 47 // BFME 2's second supply state
};

enum DozerTask
{
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR
};

class DozerAIInterface
{
public:
	virtual void onDelete() = 0; // vslot 0
	virtual void slot1() = 0; virtual void slot2() = 0; virtual void slot3() = 0;
	virtual void slot4() = 0; virtual void slot5() = 0;
	virtual Bool isTaskPending(DozerTask task) = 0; // vslot 6
	virtual void slot7() = 0; virtual void slot8() = 0; virtual void slot9() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void newTask(DozerTask task, Object *target) = 0; // vslot 12
	virtual void cancelTask(DozerTask task) = 0; // vslot 13
	virtual void slot14() = 0; virtual void slot15() = 0; virtual void slot16() = 0;
	virtual void slot17() = 0; virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0; virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void finishBuildingSound() = 0; // vslot 24
};

class SupplyTruckAIInterface
{
public:
	virtual void supplyTruckSlot0() = 0;
	virtual void st01() = 0; virtual void st02() = 0; virtual void st03() = 0; virtual void st04() = 0;
	virtual void st05() = 0; virtual void st06() = 0; virtual void st07() = 0; virtual void st08() = 0;
	virtual void st09() = 0; virtual void st10() = 0; virtual void st11() = 0;
	virtual Bool isForcedIntoWantingState() const = 0; // vslot 12 (+0x30)
};

class WorkerAIInterface3EC
{
public:
	virtual void exitingSupplyTruckState() = 0; // vslot 0
};

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The dock point element: an out-of-line empty ctor and dtor (retail's
// __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and 0x000B3FD0).
struct BfmeWorkerDockPoint
{
	BfmeWorkerDockPoint();
	~BfmeWorkerDockPoint();
	Bool valid;
	Coord3D location;
};

class WorkerAIUpdate : public AIUpdateInterface, public DozerAIInterface, public SupplyTruckAIInterface, public WorkerAIInterface3EC
{
public:
	WorkerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void onDelete();
	virtual void supplyTruckSlot0();
	virtual void exitingSupplyTruckState();
	virtual Bool isForcedIntoWantingState() const;
	virtual void newTask(DozerTask task, Object *target);
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int unused);
	Bool isSupplyTruckBrainActiveAndBusy();
protected:
	virtual ~WorkerAIUpdate();
	Bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
	Object *findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut);
private:
	enum { DOZER_NUM_TASKS = 3 };
	enum { DOZER_NUM_DOCK_POINTS = 3 };
	enum { DOZER_TASK_INVALID = -1 };
	enum { DOZER_SELECT_BUILD_DOCK_LOCATION = 0 };
	enum { DOZER_DOCK_POINT_START = 0, DOZER_DOCK_POINT_ACTION, DOZER_DOCK_POINT_END };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

	DozerTaskInfo m_task[DOZER_NUM_TASKS]; // +0x3F0
	Int m_currentTask; // +0x408
	BfmeWorkerDockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS]; // +0x40C
	Int m_buildSubTask; // +0x49C
	Int m_4A0; // +0x4A0
	Int m_4A4; // +0x4A4
	Coord3D m_4A8; // +0x4A8
	Bool m_4B4; // +0x4B4
	ObjectID m_preferredDock; // +0x4B8
	Bool m_forcePending; // +0x4BC
	Bool m_isRebuild; // +0x4BD
	Bool m_forcedBusyPending; // +0x4BE
	WorkerStateMachine *m_workerMachine; // +0x4C0
	DozerPrimaryStateMachine *m_dozerMachine; // +0x4C4
	SupplyTruckStateMachine *m_supplyTruckStateMachine; // +0x4C8
	Int m_4CC; // +0x4CC
};

WorkerAIUpdate::WorkerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
	m_preferredDock = INVALID_ID;
	m_isRebuild = FALSE;
	m_dozerMachine = 0;
	for (Int i = 0; i < DOZER_NUM_TASKS; i++)
	{
		m_task[i].m_targetObjectID = INVALID_ID;
		m_task[i].m_taskOrderFrame = 0;
		for (Int j = 0; j < DOZER_NUM_DOCK_POINTS; j++)
		{
			m_dockPoint[i][j].valid = FALSE;
			zeroCoord(m_dockPoint[i][j].location);
		}
	}
	m_currentTask = DOZER_TASK_INVALID;
	m_buildSubTask = DOZER_SELECT_BUILD_DOCK_LOCATION;

	m_supplyTruckStateMachine = 0;
	m_4A4 = 0;
	zeroCoord(m_4A8);
	m_4B4 = FALSE;
	m_4A0 = 0;
	m_forcePending = FALSE;
	m_forcedBusyPending = FALSE;

	m_workerMachine = 0;
	m_4CC = 1;

	createMachines();
}

void WorkerAIUpdate::createMachines()
{
	if (m_workerMachine == 0)
	{
		m_workerMachine = new WorkerStateMachine(getObject());

		if (m_dozerMachine == 0)
		{
			m_dozerMachine = new DozerPrimaryStateMachine(getObject());
			m_dozerMachine->initDefaultState();
		}

		if (m_supplyTruckStateMachine == 0)
		{
			m_supplyTruckStateMachine = new SupplyTruckStateMachine(getObject());
			m_supplyTruckStateMachine->initDefaultState();
		}

		m_workerMachine->initDefaultState();
	}
}

WorkerStateMachine::WorkerStateMachine(Object *owner) : Rva004D759C(owner, 0xF80D13C5, false)
{
	static const StateConditionInfo asDozerConditions[] =
	{
		{ supplyTruckSubMachineWantsToEnter, AS_SUPPLY_TRUCK, 0 },
		{ 0, 0, 0 } // keep last
	};

	static const StateConditionInfo asTruckConditions[] =
	{
		{ supplyTruckSubMachineReadyToLeave, AS_DOZER, 0 },
		{ 0, 0, 0 } // keep last
	};

	// order matters: first state is the default state.
	defineState(AS_DOZER, new Rva004A992A(this), INVALID_STATE_ID, INVALID_STATE_ID, asDozerConditions);
	defineState(AS_SUPPLY_TRUCK, new Rva004A9947(this), INVALID_STATE_ID, INVALID_STATE_ID, asTruckConditions);
}

Bool WorkerStateMachine::supplyTruckSubMachineWantsToEnter(State *thisState, void *userData)
{
	Object *owner = thisState->getMachine()->getOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate *)owner->getAIUpdateInterface();
	if (!update)
	{
		return false;
	}
	Int masterState = update->getCurrentStateID();

	// If I detect a Supply force message, or if I have been put straight in
	// dock, then the worker master part of me wants to switch to the Supply
	// sub-brain.
	return update->isForcedIntoWantingState() || (masterState == AI_DOCK) || (masterState == AI_STATE_47);
}

Bool WorkerStateMachine::supplyTruckSubMachineReadyToLeave(State *thisState, void *userData)
{
	Object *owner = thisState->getMachine()->getOwner();
	WorkerAIUpdate *update = (WorkerAIUpdate *)owner->getAIUpdateInterface();
	if (!update)
	{
		return false;
	}

	// It isn't ready to leave if it is on its way in. Active and Busy means
	// it isn't doing anything Supply related.
	return !supplyTruckSubMachineWantsToEnter(thisState, 0) && update->isSupplyTruckBrainActiveAndBusy();
}

Bool WorkerAIUpdate::isSupplyTruckBrainActiveAndBusy()
{
	return (m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK)
		&& (m_supplyTruckStateMachine->getCurrentStateID() == ST_BUSY);
}

void WorkerAIUpdate::onDelete(void)
{
	Int i;

	// cancel any of the tasks we had queued up
	for (i = DOZER_TASK_FIRST; i < DOZER_NUM_TASKS; ++i)
	{
		if (isTaskPending((DozerTask)i))
			cancelTask((DozerTask)i);
	}

	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		Object *goalObject = TheGameLogic->findObjectByID(m_task[i].m_targetObjectID);
		if (goalObject != 0)
		{
			goalObject->clearModelConditionState(MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED);
		}
	}

	finishBuildingSound();
}

Object *WorkerAIUpdate::construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int unused)
{
	m_isRebuild = isRebuild;

	createMachines();

	// sanity
	if (what == 0 || pos == 0 || owningPlayer == 0)
		return 0;

	// if we're not rebuilding, we have a few checks to pass first for sanity
	if (isRebuild == FALSE)
	{
		// AI has weaker restriction on building
		Bool dozerIsAI = owningPlayer->getPlayerType() == PLAYER_COMPUTER;
		if (dozerIsAI)
		{
			// validate the the position to build at is valid
			if (g_00A027B8->isLocationLegalToBuild(pos, what, angle,
					Rva00A027B8::CLEAR_PATH |
					Rva00A027B8::NO_OBJECT_OVERLAP,
					getObject(), 0) != LBC_OK)
				return 0;
		}
		else
		{
			// make sure the player is capable of building this
			if (g_00A027B8->canMakeUnit(getObject(), what, -1) != CANMAKE_OK)
				return 0;

			// validate the the position to build at is valid
			if (g_00A027B8->isLocationLegalToBuild(pos, what, angle,
					Rva00A027B8::TERRAIN_RESTRICTIONS |
					Rva00A027B8::CLEAR_PATH |
					Rva00A027B8::NO_OBJECT_OVERLAP |
					Rva00A027B8::SHROUD_REVEALED,
					getObject(), 0) != LBC_OK)
				return 0;
		}
	}

	// what will our initial status bits
	CreateMask statusBits;
	statusBits.Rva0023DA79(0, OBJECT_STATUS_UNDER_CONSTRUCTION);
	if (isRebuild)
		statusBits.set(OBJECT_STATUS_RECONSTRUCTING);

	// create an object at the destination location
	Object *obj = TheThingFactory->newObject(what, owningPlayer->getDefaultTeam(), &statusBits, false);

	// even though we haven't actually built anything yet, this keeps things tidy
	obj->setProducer(getObject());
	obj->rva0028AFE7(getObject());

	// leave the supply truck state and now behave like a dozer.
	exitingSupplyTruckState();

	// take the required money away from the player
	if (isRebuild == FALSE)
	{
		UnsignedInt cost = what->rva0033A69A(owningPlayer, (Int)getObject(), -1);
		owningPlayer->getMoney()->rva003B0CB3(cost, owningPlayer->getStats(), true);
		owningPlayer->getStats()->rva0039BAD2((Rva0039BAD2Input *)what, cost);
		obj->m_buildCost = (Real)cost;
	}

	obj->setStatus(OBJECT_STATUS_UNDER_CONSTRUCTION, true);

	// initialize object
	obj->setPosition(pos);
	obj->setOrientation(angle);

	// Flatten the terrain underneath the object, then adjust to the flattened height. jba.
	TheTerrainLogic->flattenTerrain(obj);
	Coord3D adjustedPos;
	adjustedPos.x = pos->x;
	adjustedPos.y = pos->y;
	adjustedPos.z = pos->z;
	adjustedPos.z = TheTerrainLogic->getGroundHeight(pos->x, pos->y);
	obj->setPosition(&adjustedPos);

	// Note - very important that we add to map AFTER we flatten terrain. jba.
	TheAI->pathfinder()->AddObjectToPathfindMap(obj);

	// "callback" event for structure created (note that it's not yet "complete")
	owningPlayer->onStructureCreated(getObject(), obj);

	// set a construction percent for the new object to zero and a status for under construction
	obj->setConstructionPercent(0.0f);

	// newly constructed objects start at one hit point
	BodyModuleInterface *body = obj->getBodyModule();
	body->internalChangeHealth(-body->getHealth() + 1.0f, 0);

	// set the model action state to awaiting construction
	Rva001E4912 clearBits;
	obj->rva0028CFB2((const int *)clearBits.rva001E4912(0, MODELCONDITION_PARTIALLY_CONSTRUCTED, MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED),
		(const int *)&Rva0028F59A(0, MODELCONDITION_AWAITING_CONSTRUCTION));

	// we have a construction pending
	newTask(DOZER_TASK_BUILD, obj);

	return obj;
}

Object *WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut)
{
	if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile, "  WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget() BEGIN: Object %s(%d) with target %s(%d)",
			me->getTemplate()->getName().str(), me->getID(),
			target ? target->getTemplate()->getName().str() : "NULL", target ? target->getID() : 0);

	if (target->isKindOf(KINDOF_BRIDGE))
	{
		if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile, "  target is a bridge case");

		BridgeBehaviorInterface *bridgeInterface = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
		if (bridgeInterface)
		{
			if (g_bfmeDockingTraceActive && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "  target has a bridge behavior");

			// pick the reachable tower position closest to us
			AIUpdateInterface *ai = me->getAIUpdateInterface();
			Real closestDistSq = 1e10f;
			Object *closestTower = 0;
			for (Int i = 0; i < BRIDGE_MAX_TOWERS; ++i)
			{
				Object *tower = TheGameLogic->findObjectByID(bridgeInterface->getTowerID((BridgeTowerType)i));
				if (tower)
				{
					Coord3D pos;
					if (findGoodBuildOrRepairPosition(me, tower, pos) && ai->isPathAvailable(&pos))
					{
						Real distSq = sqr(me->getPosition()->x - pos.x) + sqr(me->getPosition()->y - pos.y);
						if (distSq < closestDistSq)
						{
							positionOut = pos;
							closestDistSq = distSq;
							closestTower = tower;
						}
					}
				}
			}
			return closestTower;
		}
	}

	findGoodBuildOrRepairPosition(me, target, positionOut);
	return target;
}

void WorkerAIUpdate::newTask(DozerTask task, Object *target)
{
	// sanity
	if (target == 0)
		return;

	// where ZH forgets the preferred dock, BFME 2 clears these
	m_4A4 = 0;
	zeroCoord(m_4A8);
	m_4B4 = FALSE;

	//
	// special check for the build task, we should never be given more than one of them ...
	// for the other tasks we just forget what we were doing and the new target takes
	// precedence for the task
	//
	if (task == DOZER_TASK_BUILD || task == DOZER_TASK_REPAIR)
	{
		// handle getting two tasks
		if (isTaskPending(task) == TRUE)
			cancelTask(task);

		// get our object
		Object *me = getObject();

		Coord3D position;
		if (g_bfmeDockingDesyncLog)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "DockingDesync(WORKER) BEGIN: Object %s(%d) with target %s(%d) at %g,%g,%g",
					me->getTemplate()->getName().str(), me->getID(),
					target->getTemplate()->getName().str(), target->getID(),
					me->getPosition()->x, me->getPosition()->y, me->getPosition()->z);
			g_bfmeDockingTraceActive = true;
		}

		target = findGoodBuildOrRepairPositionAndTarget(me, target, position);
		if (target == 0)
		{
			if (g_bfmeDockingDesyncLog)
			{
				if (theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile, "DockingDesync(WORKER) END: Object %s(%d) with no target found docking position %g,%g,%g",
						me->getTemplate()->getName().str(), me->getID(),
						position.x, position.y, position.z);
				g_bfmeDockingTraceActive = false;
			}
			return; // could happen for some bridges
		}

		if (g_bfmeDockingDesyncLog)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "DockingDesync(WORKER) END: Object %s(%d) with target %s(%d) found docking position %g,%g,%g",
					me->getTemplate()->getName().str(), me->getID(),
					target->getTemplate()->getName().str(), target->getID(),
					position.x, position.y, position.z);
			g_bfmeDockingTraceActive = false;
		}

		//
		// for building, we say that even "thinking" about building or rebuilding an object
		// sets us as the current builder of that object
		//
		if (task == DOZER_TASK_BUILD)
			target->rva0028AFE7(me);

		m_dockPoint[task][DOZER_DOCK_POINT_START].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_START].location = position;
		m_dockPoint[task][DOZER_DOCK_POINT_ACTION].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_ACTION].location = position;
		m_dockPoint[task][DOZER_DOCK_POINT_END].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_END].location = position;

		me->setStatus(OBJECT_STATUS_97, true);
		m_3BA = TRUE;
	}

	// set the new task target and the frame in which we got this order
	m_task[task].m_targetObjectID = target->getID();
	m_task[task].m_taskOrderFrame = TheGameLogic->getFrame();

	// reset the dozer behavior so that it can re-evluate which task to continue working on
	m_dozerMachine->resetToDefaultState();

	// reset the workermachine, if we've been acting like a supply truck
	if (m_workerMachine->getCurrentStateID() == AS_SUPPLY_TRUCK)
	{
		if (getObject()->getAIUpdateInterface())
			getObject()->getAIUpdateInterface()->aiIdle(CMD_FROM_AI);
		m_workerMachine->setState(AS_DOZER);
	}
}
