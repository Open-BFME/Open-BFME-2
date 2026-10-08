// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// Zero Hour's DozerAIUpdate (GeneralsMD GameLogic/Object/Update/AIUpdate/
// DozerAIUpdate.cpp) as BFME 2 kept it.
//
// ?createMachines@DozerAIUpdate@@AAEXXZ, retail 0x00488EFC, 86 bytes. Called
// by the ctor 0x004894F5 and by construct 0x00488F52 (which first stores its
// isRebuild argument at +0x40C, ZH's m_isRebuild); +0x400 is the machine
// pointer both test. As in ZH: without a machine, make a
// DozerPrimaryStateMachine (0x3C bytes, plain operator new; ctor 0x00488DAB
// defines the dozer states) for the object and enter its default state
// (machine vslot 7, initDefaultState).
//
// ??0DozerPrimaryStateMachine@@QAE@PAVObject@@@Z, retail 0x00488DAB, 309
// bytes. As in ZH: the StateMachine base (rowed 0x004D79E1; name key
// 0x3EA7DE5F, flag false; vtable 0x0084B668) and the five dozer states in
// ZH's order: idle (rowed ctor 0x004886C7) with the idle conditions table
// (retail .rdata 0x0084B808: three tests, states 1-3, then a terminator;
// the tests 0x0048899D/0x004889E8/0x00488A34 are ZH's is*MostImportant),
// the build, repair and fortify action states (rowed ctor 0x00488883 with
// tasks 0-2) and going home (rowed ctor 0x0048896B), every success and
// failure id idle except the idle state's INVALID_STATE_ID.
//
// The idle conditions, retail 0x0048899D (75 bytes), 0x004889E8 (76) and
// 0x00488A34 (77), ZH's isBuildMostImportant, isRepairMostImportant and
// isFortifyMostImportant in table order: the machine owner's AI (Object
// +0x258), its dozer interface (AI vslot 93) and idleness (vslot 110),
// then whether the most recent command (dozer vslot 5) is the state's
// task. Their State parameter is spelled struct, as the rowed defineState.
//
// ??0DozerAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004894F5,
// 239 bytes. Target evidence: the body runs the pinned AIUpdateInterface
// ctor 0x0026E9BD and the implicit ctor of the all-_purecall interface at
// +0x3E4 (vtable 0x0084B788), stores the final vtables (0x0084B848 primary)
// and builds the 3x3 dock point array at +0x410 through __ehvec_ctor with an
// empty out-of-line element ctor/dtor (ICF-folded 0x0047A6A9/0x000B3FD0).
// As in ZH it clears the three tasks (+0x3E8, 8 bytes each) and every dock
// point (valid flag and zeroed location), sets the current task to
// DOZER_TASK_INVALID (+0x404), the build sub-task (+0x4A0) to
// DOZER_SELECT_BUILD_DOCK_LOCATION and the machine pointer to NULL, then
// creates the machines. New in BFME 2: +0x4A4 is zeroed in the init list,
// the +0x40C flag (construct 0x00488F52's isRebuild) is cleared and +0x408
// is set to 1.
//
// ?onDelete@DozerAIUpdate@@UAEXXZ, retail 0x00489CA1, 104 bytes (primary vslot 8; the
// dozer interface's slot 0 reaches it through its this-adjusting entry). As
// in ZH: cancel every pending task (dozer interface vslots 6 and 13), then
// clear MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED (Object +0x114 bit 5,
// notifying through the rowed 0x0028AE6D on change) on each task's target
// (+0x3E8 ids, the rowed GameLogic::findObjectByID). New in BFME 2: it ends
// with the dozer interface's finishBuildingSound (vslot 24, tail call).
//
// ?findGoodBuildOrRepairPositionAndTarget@DozerAIUpdate@@IAEPAVObject@@PAV2@0AAUCoord3D@@@Z,
// retail 0x00489913, 244 bytes. ZH's static
// DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget as a member, the
// Worker twin 0x004AABB4 without its docking-trace lines: for a bridge
// (kind-of bit 22 on the template, Thing +0x04 then +0x108) it picks the
// reachable tower (bridge interface vslot 1, four towers, the pinned
// isPathAvailable) whose position (the rowed findGoodBuildOrRepairPosition
// 0x00489039) is nearest, else it finds the target's position.
//
// ?findGoodBuildOrRepairPosition@DozerAIUpdate@@IAE_NPBVObject@@0AAUCoord3D@@@Z,
// retail 0x00489039, 421 bytes. Donor: BFME 1's
// DozerAIUpdateFindGoodBuildOrRepairPosition.cpp (a member there too) over
// ZH's static: bias the target's position towards us by half its major
// radius (GeometryInfo at Object +0xA8, radius +0x10), take the nearest
// labeled contact point (the pinned AIUpdateInterface helper 0x0026872B,
// named by its own trace line; BFME 2 passes skipCollideTest true), else
// findPositionAround (rowed 0x00285202) within 100 and a 10 z delta for
// ground units, ignoring the target for flyers. WWMath's Vector3 inlines
// (member-wise copy and assignment) give retail's offset arithmetic; the
// member-wise Coord3D copy is BFME 2's own (coord3d.cpp).
//
// ?newTask@DozerAIUpdate@@UAEXW4DozerTask@@PAVObject@@@Z, retail 0x00489A07,
// 666 bytes (dozer interface vslot 12, so its this is the +0x3E4
// interface). Donor: BFME 1's DozerAIUpdateNewTaskBfme.cpp over ZH's
// DozerAIUpdate::newTask: for a build or repair task it cancels a pending one
// (vslots 6 and 13), finds the position and target (rowed 0x00489913), sets
// the builder (rowed 0x0028AFE7) for builds and fills the three dock points,
// the end point pushed 50 units out from the target along the normalized 2D
// offset (rowed Coord3D::normalize 0x000035B6; the offset in its own block,
// as in the donor, keeps its scaled components in registers); then it
// records the target id and frame (TheGameLogic +0x40) and resets the dozer
// machine (vslot 6). The DockingDesync(DOZER) diagnostics are the Worker
// twin's (0x004AADB1), under the same two switches. Unlike the Worker, BFME 2
// adds nothing here.
//
// ?aiDoCommand@DozerAIUpdate@@UAEXPBUAICommandParms@@@Z, retail 0x0048AF0B,
// 307 bytes: slot 0 of the vtable the ctor stores at +0x20 (0x0084B838, the
// AICommandInterface subobject, so its this is +0x20). ZH's
// DozerAIUpdate::aiDoCommand unchanged: clear
// MODELCONDITION_ACTIVELY_CONSTRUCTING (Object +0x114 bit 9), ask
// isAllowedToRespondToAiCommands (primary vslot 148), create the machines,
// then by command: move-away-from-unit (0x34) is ignored while busy unless
// the other unit is a dozer (kind-of bit 14), repair (0x13) and resume
// construction (0x14) go idle (the rowed aiIdle 0x001E8A38) when taskless
// and run privateRepair / privateResumeConstruction (primary vslots 44 and
// 45), and anything else cancels the current task (dozer interface vslots
// 9 and 13) for player commands before AIUpdateInterface::aiDoCommand
// (pinned 0x002673F6) and resets the dozer machine.
//
// ?update@DozerActionMoveToActionPosState@@UAE?AW4StateReturnType@@XZ,
// retail 0x004892E1, 412 bytes: slot 6 of vtable 0x0084B448, which the rowed
// ctor 0x0048851B (ZH's second dozer action state, between the pick and do
// states 0x004884ED and 0x00488545) stores. ZH's update: the machine's goal
// object (pinned StateMachine::getGoalObject 0x004D7726) and owner, a
// repairer that is not us fails the task (getSoleHealingBenefactor, dozer
// interface vslot 14 internalTaskComplete, machine vslot 14 setGoalObject),
// success within max(MIN_ACTION_TOLERANCE, bounding sphere radius + 15)
// of the goal position (machine +0x24; the 70.0 at .rdata 0x0084B3DC is the
// TU's own static, addressed through the reference max), failure when the AI
// went idle. New in BFME 2: without a goal object it takes the dozer's own
// (dozer interface vslot 29, the object whose id is at +0x4A4), the repair
// check skips KINDOF_SWARM_DOZER units (kind-of bit 15 by the name table at
// .rdata 0x009BBE18), there is no builder-id check, and a finished move to a
// build site with that object deselects the dozer (the static
// Rva00489256Do), runs dozer vslot 26 and the rowed Object 0x0028AB4E, tells
// TheAiOrdersManager (pinned 0x00355183, order 3) and refreshes the site's
// drawable (rowed 0x00274176) after the model condition swap (rowed mask
// builders 0x0028F59A and 0x001E4912, Object 0x0028CFB2).
//
// ?Rva00489256Do@@YAXPAVObject@@@Z, retail 0x00489256, 95 bytes: a static
// helper called only from that update (0x00489400) with the object in ESI,
// MSVC's custom convention for a same-TU static.
//
// ??0Rva004885DE@@QAE@PAVObject@@H@Z, retail 0x004885DE, 227 bytes: ZH's
// DozerActionStateMachine (owner, task), built by the action state ctor
// 0x00488883 (new 0x40). Name key 0x253E8923 through the scalar-key base
// view, vtable 0x0084B510, the task at +0x3C, then ZH's three states (rowed
// pick/move/do ctors 0x004884ED, 0x0048851B, 0x00488545) with ZH's
// transitions: pick -> move or exit-with-failure, move -> do or back to pick,
// do -> exit with success or failure.
//
// ?update@DozerActionPickActionPosState@@UAE?AW4StateReturnType@@XZ,
// retail 0x0048A4DD, 449 bytes: slot 6 of vtable 0x0084B3E0, stored by the
// rowed ctor 0x004884ED. ZH's update: the task target (dozer interface vslot
// 7 through findObjectByID), the dock point (vslot 17) or a findPositionAround
// on the bounding sphere starting at the angle back to us (Coord2D::toAngle
// 0x00005923), then the machine goal object and position and a move order
// (ignoreObstacle 0x00268D88, aiMoveToPosition 0x0026C26D through the AI's
// +0x20 command interface). New in BFME 2: without a target it falls back to
// dozer vslot 29 before cancelling (vslot 13), setGoalPosition takes a range
// (FLT_MAX), and two logic-random-log lines gated by g_00E03745.
#include <list>
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line normalize (rowed 0x000035B6) that newTask calls; same three floats
struct Coord3D
{
	Coord3D() {}
	// member-wise, as BFME 2's own (coord3d.cpp)
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	void normalize();
	void sub(const Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
	// by value: retail reads all three of the addend before summing
	void add(Coord3D a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
	}
	void scale(float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	float x;
	float y;
	float z;
};

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#define FALSE false
#define TRUE true

struct _iobuf;
typedef struct _iobuf FILE;

extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

// BFME's logic random log file (data ledger 0x00DFEFF0).
extern "C" FILE *theLogicRandomLogFile;

// BFME 1's docking diagnostics switches (0x00DCBF44 and 0x00E03CA8).
extern bool g_bfmeDockingDesyncLog;
extern bool g_bfmeDockingTraceActive;

// Logic random log switch (data ledger 0x00A03745).
extern unsigned char g_00E03745;

// class-gate: allow Coord2D the canonical data-only header cannot declare BFME 2's out-of-line toAngle (rowed 0x00005923) that the pick state calls; same two floats
class Coord2D
{
public:
	Real toAngle() const;

	float x;
	float y;
};

enum ObjectID
{
	INVALID_ID = 0
};

extern "C" void *memset(void *dst, int val, unsigned size);

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	void _M_do_or(const _Base_bitset<4> &other);
	unsigned long _M_w[4];
};
}

class Thing;
class ModuleData;
class BodyModuleInterface;
class Object;
class Drawable;
class Player;
class ThingTemplate;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

typedef UnsignedInt StateID;
enum { INVALID_STATE_ID = 999999 };

class State;
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
	virtual void slot08(); virtual void slot09(); virtual void slot10();
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *obj); // vslot 14
	void defineState(StateID id, struct State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = 0);
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
	void setGoalPosition(const Coord3D *pos, Real range);
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
	unsigned char m_pad30[0x3C - 0x30]; // operator new size 0x3C
};

// BFME 2's StateMachine constructor (owner, name key, flag), rowed by
// address as ??0Rva004D759C@@QAE@PAVObject@@VAsciiString@@_N@Z. Every
// caller passes the name as one dword, and only a scalar parameter gives
// retail's push of the immediate key, so this view takes the key as one.
class Rva004D759C : public StateMachine
{
public:
	Rva004D759C(Object *owner, UnsignedInt nameKey, Bool flag);
	virtual ~Rva004D759C();
};

struct State
{
public:
	virtual ~State();
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
	unsigned char m_pad1C[0x20 - 0x1C];
};

// ZH's DozerPrimaryIdleState (rowed ctor 0x004886C7).
class Rva004886C7 : public State
{
public:
	Rva004886C7(StateMachine *machine);
private:
	unsigned char m_pad20[0x2C - 0x20];
};

// ZH's DozerActionState (machine, task) (rowed ctor 0x00488883).
class Rva00488D5C : public State
{
public:
	Rva00488D5C(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

// ZH's DozerPrimaryGoingHomeState (rowed ctor 0x0048896B).
class Rva0048896B : public State
{
public:
	Rva0048896B(StateMachine *machine);
};

enum DozerTask
{
	DOZER_TASK_INVALID = -1,
	DOZER_TASK_FIRST = 0,
	DOZER_TASK_BUILD = DOZER_TASK_FIRST,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY
};

enum DozerDockPoint
{
	DOZER_DOCK_POINT_START = 0,
	DOZER_DOCK_POINT_ACTION = 1,
	DOZER_DOCK_POINT_END = 2,
	DOZER_NUM_DOCK_POINTS
};

enum
{
	DOZER_PRIMARY_IDLE = 0,
	DOZER_PRIMARY_BUILD,
	DOZER_PRIMARY_REPAIR,
	DOZER_PRIMARY_FORTIFY,
	DOZER_PRIMARY_GO_HOME
};

class DozerPrimaryStateMachine : public Rva004D759C
{
public:
	DozerPrimaryStateMachine(Object *owner);
	virtual ~DozerPrimaryStateMachine();

	static Bool isBuildMostImportant(State *thisState, void *userData);
	static Bool isRepairMostImportant(State *thisState, void *userData);
	static Bool isFortifyMostImportant(State *thisState, void *userData);
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

// BFME 2's command ids (aiDoCommand 0x002673F6's jump table); ZH's order
// up to AICMD_RESUME_CONSTRUCTION, BFME 2 inserts four before
// AICMD_MOVE_AWAY_FROM_UNIT.
enum AICommandType
{
	AICMD_REPAIR = 0x13,
	AICMD_RESUME_CONSTRUCTION = 0x14,
	AICMD_MOVE_AWAY_FROM_UNIT = 0x34
};

struct AICommandParms
{
	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFaceObject(Object *obj, CommandSourceType cmdSource);
};

class AIUpdateInterface24
{
public:
	virtual void slot0();
};

// ZH's build sub-tasks; BFME 2 turns to face the site (2) before building.
enum DozerBuildSubTask
{
	DOZER_SELECT_BUILD_DOCK_LOCATION = 0,
	DOZER_MOVING_TO_BUILD_DOCK_LOCATION = 1,
	DOZER_FACING_BUILD_TARGET = 2,
	DOZER_DO_BUILD_AT_DOCK = 3
};

class Rva002390CB;

class DozerAIInterface
{
public:
	virtual void onDelete() = 0; // vslot 0
	virtual Real getRepairHealthPerSecond() const = 0; // vslot 1
	virtual Real getBoredTime() const = 0;
	virtual Real getBoredRange() const = 0;
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags) = 0; // vslot 4
	virtual DozerTask getMostRecentCommand() = 0; // vslot 5
	virtual Bool isTaskPending(DozerTask task) = 0; // vslot 6
	virtual ObjectID getTaskTarget(DozerTask task) = 0; // vslot 7
	virtual Bool isAnyTaskPending() = 0; // vslot 8
	virtual DozerTask getCurrentTask() const = 0; // vslot 9
	virtual void setCurrentTask(DozerTask task) = 0;
	virtual Bool getIsRebuild() = 0; // vslot 11
	virtual void newTask(DozerTask task, Object *target) = 0; // vslot 12
	virtual void cancelTask(DozerTask task) = 0; // vslot 13
	virtual void internalTaskComplete(DozerTask task) = 0; // vslot 14
	virtual void internalCancelTask(DozerTask task) = 0; // vslot 15
	virtual void internalTaskCompleteOrCancelled(DozerTask task) = 0; // vslot 16
	virtual const Coord3D *getDockPoint(DozerTask task, DozerDockPoint point) = 0; // vslot 17
	virtual void setBuildSubTask(DozerBuildSubTask subTask) = 0; // vslot 18
	virtual DozerBuildSubTask getBuildSubTask() = 0; // vslot 19
	virtual Bool canAcceptNewRepair(Object *obj) = 0;
	virtual void createBridgeScaffolding(Object *bridgeTower) = 0; // vslot 21
	virtual void removeBridgeScaffolding(Object *bridgeTower) = 0;
	// BFME 2 hands over the drawable's sound record (by reference).
	virtual void startBuildingSound(const Rva002390CB &sound, ObjectID constructionSiteID) = 0; // vslot 23
	virtual void finishBuildingSound() = 0; // vslot 24
	// BFME 2's own slots. 26 (0x0048A15A) and 29 (0x00489DD1, which slot 28
	// shares) both work on the object whose id is at DozerAIUpdate +0x4A4.
	// Slot names 25, 26 and 31 are WorldBuilder's (DozerAIUpdate.cpp asserts).
	virtual void createPhantomStructure(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle) = 0; // vslot 25
	virtual void makePhantomStructureReal() = 0; // vslot 26
	virtual void rva00489D09() = 0; // vslot 27
	virtual Object *slot28() = 0;
	virtual Object *rva00489DD1() = 0; // vslot 29
	virtual void slot30() = 0;
	virtual void notifyConstructionComplete() = 0; // vslot 31
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
	// Primary vtable slots 1-92 (slot 0 is the destructor).
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void onDelete(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
	virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
	virtual void v41(); virtual void v42(); virtual void v43();
	virtual void privateRepair(Object *obj, CommandSourceType cmdSource); // vslot 44 (+0xB0)
	virtual void privateResumeConstruction(Object *obj, CommandSourceType cmdSource); // vslot 45 (+0xB4)
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50();
	virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
	virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69(); virtual void v70();
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80();
	virtual void v81(); virtual void v82(); virtual void v83(); virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87(); virtual void v88(); virtual void v89(); virtual void v90();
	virtual void v91(); virtual void v92();
	virtual DozerAIInterface *getDozerAIInterface(); // vslot 93 (+0x174)
	virtual void v94(); virtual void v95(); virtual void v96(); virtual void v97(); virtual void v98(); virtual void v99(); virtual void v100();
	virtual void v101(); virtual void v102(); virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106(); virtual void v107(); virtual void v108(); virtual void v109();
	virtual Bool isIdle() const; // vslot 110 (+0x1B8)
	virtual void v111(); virtual void v112(); virtual void v113(); virtual void v114(); virtual void v115(); virtual void v116(); virtual void v117(); virtual void v118(); virtual void v119(); virtual void v120();
	virtual void v121(); virtual void v122(); virtual void v123(); virtual void v124(); virtual void v125();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags); // vslot 126 (+0x1F8)
	virtual void v127(); virtual void v128(); virtual void v129(); virtual void v130();
	virtual void v131(); virtual void v132(); virtual void v133(); virtual void v134(); virtual void v135(); virtual void v136(); virtual void v137(); virtual void v138(); virtual void v139(); virtual void v140();
	virtual void v141(); virtual void v142(); virtual void v143(); virtual void v144(); virtual void v145(); virtual void v146(); virtual void v147();
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const; // vslot 148 (+0x250)
	virtual void aiDoCommand(const AICommandParms *parms);
	Bool isPathAvailable(const Coord3D *destination) const;
	void ignoreObstacle(const Object *obj);
	Bool findNearestLabeledContactPointOnTarget(Object *target, Coord3D *result, const Coord3D *workingPosition, Bool skipCollideTest);
protected:
	virtual ~AIUpdateInterface();
private:
	unsigned char m_pad28[0x3E4 - 0x28];
};

enum ModelConditionFlagType
{
	MODELCONDITION_AWAITING_CONSTRUCTION = 67,
	MODELCONDITION_PARTIALLY_CONSTRUCTED = 68,
	MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED = 69, // +0x114 bit 5
	MODELCONDITION_ACTIVELY_CONSTRUCTING = 73, // +0x114 bit 9
	MODELCONDITION_PHANTOM_STRUCTURE = 109 // +0x118 bit 13
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
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

// The four-bit status mask Rva00489256Do sets.
class Rva00346BC0
{
public:
	Rva00346BC0(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5);
private:
	unsigned int m_bits[4];
};

class GeometryInfo
{
public:
	Real getMajorRadius() const { return m_majorRadius; }
	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
private:
	unsigned char m_pad00[0x10];
	Real m_majorRadius; // +0x10
	Real m_boundingSphereRadius; // +0x14 (calcBoundingStuff 0x006BE700)
	unsigned char m_pad18[0x5C - 0x18];
};

// BFME 2's kind-of bit names (the name table at .rdata 0x009BBE18).
enum KindOfType
{
	KINDOF_DOZER = 14,
	KINDOF_SWARM_DOZER = 15,
	KINDOF_BRIDGE = 22,
	KINDOF_BRIDGE_TOWER = 24,
	KINDOF_NO_COLLIDE = 30,
	KINDOF_DO_NOT_CLASSIFY = 149
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return m_kindOf[t >> 5] & (1U << (t & 31)); }
	Int rva0033A69A(const Player *player, Int builder, Int a3) const;
	Int rva0033AA1F(const Player *player, Int builder, Int a3) const;
private:
	unsigned char m_pad000[0x64];
	AsciiString m_name; // +0x64
	unsigned char m_pad068[0x108 - 0x68];
	UnsignedInt m_kindOf[7]; // +0x108 (218 kind-of bits)
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	Drawable *getDrawable() const;
	void setPosition(const Coord3D *pos);
	void setOrientation(Real angle);
private:
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
};

// BFME 2's object status bit names (the name table at .rdata 0x009A5F30).
enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_RECONSTRUCTING = 21,
	OBJECT_STATUS_PENDING_CONSTRUCTION = 87,
	OBJECT_STATUS_PHANTOM_STRUCTURE = 88
};

// ZH's disabled types, in its order.
enum DisabledType
{
	DISABLED_UNMANNED = 5
};

class Module;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
	void rva0028AFE7(Object *builder);
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	Bool isUsingAirborneLocomotor() const;
	__forceinline UnsignedInt isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getSoleHealingBenefactor() const;
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	void rva0028AB4E() const;
	void rva0028CFB2(const int *clear, const int *set);
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
	void rva0028CDEB(const _STL::_Base_bitset<4> *mask, Bool set);
	Bool get454() const { return m_454; }
	Player *getControllingPlayer() const;
	void rva0028DCC4();
	void rva0028AE6D();
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	void setProducer(Object *obj);
	ObjectID getProducerID() const { return m_producerID; }
	ObjectID getBuilderID() const { return m_builderID; }
	__forceinline UnsignedInt isDisabledByType(DisabledType type) const { return m_disabledMask & (1U << type); }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	Real getConstructionPercent() const { return m_constructionPercent; }
	void setConstructionPercent(Real percent) { m_constructionPercent = percent; }
	void setStatus(ObjectStatusTypes status, Bool set);
	Module *findModule(NameKeyType key) const;
	void rva001E42F2(const int *clear);
	void setSpecialModelConditionState(ModelConditionFlagType mc, UnsignedInt frames);
	Bool isLocallyControlled() const;
	void *getDisplayName();
	// ZH's attemptHealingFromSoleBenefactor (amount, source, duration).
	Bool rva0028FEA7(Real amount, const Object *source, UnsignedInt duration);
	Int get45C() const { return m_45C; }
private:
	unsigned char m_pad048[0x74 - 0x48];
	ObjectID m_id; // +0x74
	ObjectID m_producerID; // +0x78
	ObjectID m_builderID; // +0x7C
	unsigned char m_pad080[0xA8 - 0x80];
	GeometryInfo m_geometryInfo; // +0xA8
	unsigned char m_pad104[0x10C - 0x104];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x1C8 - 0x158];
	UnsignedInt m_disabledMask; // +0x1C8
	unsigned char m_pad1CC[0x254 - 0x1CC];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x280 - 0x25C];
	Real m_constructionPercent; // +0x280
	unsigned char m_pad284[0x324 - 0x284];
public:
	Real m_buildCost; // +0x324
private:
	unsigned char m_pad328[0x438 - 0x328];
	unsigned char m_privateStatus; // +0x438, bit 0 effectively dead
	unsigned char m_pad439[0x454 - 0x439];
	Bool m_454; // +0x454
	unsigned char m_pad455[0x45C - 0x455];
	Int m_45C; // +0x45C
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const { return m_frame; }
	void rva0023D0C2(Object *obj, Int handle);
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

// WWMath's Vector3 (its inline members, WWINLINE as __forceinline).
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	__forceinline Vector3(void) {}
	__forceinline Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	__forceinline float Length2(void) const { return X*X + Y*Y + Z*Z; }
	__forceinline void Normalize(void)
	{
		float len2 = Length2();
		if (len2 != 0.0f)
		{
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	__forceinline friend Vector3 operator*(const Vector3 &a, float k) { return Vector3((a.X * k), (a.Y * k), (a.Z * k)); }
};

struct FindPositionOptions
{
	FindPositionOptions() : flags(0), minRadius(0.0f), maxRadius(0.0f), startAngle(-99999.9f),
		maxZDelta(1e10f), ignoreObject(0), sourceToPathToDest(0), relationshipObject(0) {}
	UnsignedInt flags;
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
	virtual void createScaffolding();
	virtual void removeScaffolding();
	virtual Bool isScaffoldInMotion(); // vslot 4
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

inline void zeroCoord(Coord3D &c)
{
	c.x = 0.0f;
	c.y = 0.0f;
	c.z = 0.0f;
}

// The dock point element: an out-of-line empty ctor and dtor (retail's
// __ehvec_ctor arguments, the ICF-folded 0x0047A6A9 and 0x000B3FD0).
struct Rva004894F5DockPoint
{
	Rva004894F5DockPoint();
	~Rva004894F5DockPoint();
	Bool valid;
	Coord3D location;
};

class DozerAIUpdate : public AIUpdateInterface, public DozerAIInterface
{
public:
	DozerAIUpdate(Thing *thing, const ModuleData *moduleData);
	virtual void onDelete();
	virtual Object *construct(const ThingTemplate *what, const Coord3D *pos, Real angle, Player *owningPlayer, Bool isRebuild, Int flags);
	virtual void finishBuildingSound();
	virtual void createPhantomStructure(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle);
	virtual void makePhantomStructureReal();
	virtual void rva00489D09();
	virtual Object *rva00489DD1();
	virtual void notifyConstructionComplete();
	virtual void newTask(DozerTask task, Object *target);
	virtual void cancelTask(DozerTask task);
	virtual void internalTaskCompleteOrCancelled(DozerTask task);
	virtual const Coord3D *getDockPoint(DozerTask task, DozerDockPoint point);
	virtual void aiDoCommand(const AICommandParms *parms);
	void makePhantomStructureInert();
	void makePhantomStructureNotInert();
private:
	enum { DOZER_NUM_TASKS = 3 };

	struct DozerTaskInfo
	{
		ObjectID m_targetObjectID;
		UnsignedInt m_taskOrderFrame;
	};

	void createMachines();

protected:
	Bool findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut);
	Object *findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut);
	virtual ~DozerAIUpdate();

private:
	DozerTaskInfo m_task[DOZER_NUM_TASKS]; // +0x3E8
	DozerPrimaryStateMachine *m_dozerMachine; // +0x400
	Int m_currentTask; // +0x404
	Int m_408; // +0x408
	Bool m_isRebuild; // +0x40C
	Rva004894F5DockPoint m_dockPoint[DOZER_NUM_TASKS][DOZER_NUM_DOCK_POINTS]; // +0x410
	Int m_buildSubTask; // +0x4A0
	Int m_4A4; // +0x4A4
};

DozerAIUpdate::DozerAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData),
	  m_4A4(0)
{
	Int i, j;

	for (i = 0; i < DOZER_NUM_TASKS; i++)
	{
		m_task[i].m_targetObjectID = INVALID_ID;
		m_task[i].m_taskOrderFrame = 0;

		for (j = 0; j < DOZER_NUM_DOCK_POINTS; j++)
		{
			m_dockPoint[i][j].valid = FALSE;
			zeroCoord(m_dockPoint[i][j].location);
		}
	}
	m_currentTask = DOZER_TASK_INVALID;
	m_buildSubTask = DOZER_SELECT_BUILD_DOCK_LOCATION;
	m_dozerMachine = 0;
	m_isRebuild = FALSE;
	m_408 = 1;

	createMachines();
}

DozerPrimaryStateMachine::DozerPrimaryStateMachine(Object *owner) : Rva004D759C(owner, 0x3EA7DE5F, false)
{
	static const StateConditionInfo idleConditions[] =
	{
		{ isBuildMostImportant, DOZER_PRIMARY_BUILD, 0 },
		{ isRepairMostImportant, DOZER_PRIMARY_REPAIR, 0 },
		{ isFortifyMostImportant, DOZER_PRIMARY_FORTIFY, 0 },
		{ 0, 0, 0 } // keep last
	};

	// order matters: first state is the default state.
	defineState(DOZER_PRIMARY_IDLE, new Rva004886C7(this), INVALID_STATE_ID, INVALID_STATE_ID, idleConditions);
	defineState(DOZER_PRIMARY_BUILD, new Rva00488D5C(this, DOZER_TASK_BUILD), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_REPAIR, new Rva00488D5C(this, DOZER_TASK_REPAIR), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_FORTIFY, new Rva00488D5C(this, DOZER_TASK_FORTIFY), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
	defineState(DOZER_PRIMARY_GO_HOME, new Rva0048896B(this), DOZER_PRIMARY_IDLE, DOZER_PRIMARY_IDLE);
}

Bool DozerPrimaryStateMachine::isBuildMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_BUILD;
}

Bool DozerPrimaryStateMachine::isRepairMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_REPAIR;
}

Bool DozerPrimaryStateMachine::isFortifyMostImportant(State *thisState, void *userData)
{
	Object *dozer = thisState->getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
	{
		return FALSE;
	}
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
	{
		return FALSE;
	}

	if (!ai->isIdle())
		return FALSE; // busy doing something else

	// if the most important task is us then return true
	DozerTask task = dozerAI->getMostRecentCommand();
	return task == DOZER_TASK_FORTIFY;
}

void DozerAIUpdate::createMachines()
{
	if (m_dozerMachine == 0)
	{
		m_dozerMachine = new DozerPrimaryStateMachine(getObject());
		m_dozerMachine->initDefaultState();
	}
}

void DozerAIUpdate::onDelete(void)
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

Object *DozerAIUpdate::findGoodBuildOrRepairPositionAndTarget(Object *me, Object *target, Coord3D &positionOut)
{
	if (target->isKindOf(KINDOF_BRIDGE))
	{
		BridgeBehaviorInterface *bridgeInterface = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
		if (bridgeInterface)
		{
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

void DozerAIUpdate::newTask(DozerTask task, Object *target)
{
	// sanity
	if (target == 0)
		return;

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
				fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) BEGIN: Object %s(%d) with target %s(%d) at %g,%g,%g",
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
					fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) END: Object %s(%d) with no target found docking position %g,%g,%g",
						me->getTemplate()->getName().str(), me->getID(),
						position.x, position.y, position.z);
				g_bfmeDockingTraceActive = false;
			}
			return; // could happen for some bridges
		}

		if (g_bfmeDockingDesyncLog)
		{
			if (theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile, "DockingDesync(DOZER) END: Object %s(%d) with target %s(%d) found docking position %g,%g,%g",
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

		// the end point is pushed out from the target
		{
			Coord3D offset;
			offset.x = position.x - target->getPosition()->x;
			offset.y = position.y - target->getPosition()->y;
			offset.z = 0.0f;
			offset.normalize();
			offset.x *= 50.0f;
			offset.y *= 50.0f;
			offset.z *= 50.0f;
			position.x += offset.x;
			position.y += offset.y;
			position.z += offset.z;
		}

		m_dockPoint[task][DOZER_DOCK_POINT_END].valid = TRUE;
		m_dockPoint[task][DOZER_DOCK_POINT_END].location = position;
	}

	// set the new task target and the frame in which we got this order
	m_task[task].m_targetObjectID = target->getID();
	m_task[task].m_taskOrderFrame = TheGameLogic->getFrame();

	// reset the dozer behavior so that it can re-evluate which task to continue working on
	m_dozerMachine->resetToDefaultState();
}

Bool DozerAIUpdate::findGoodBuildOrRepairPosition(const Object *me, const Object *target, Coord3D &positionOut)
{
	// The place we go to build or repair is the closest spot from us to them
	Coord3D ourPosition = *me->getPosition();
	Coord3D theirPosition = *target->getPosition();

	Coord3D bestPosition = theirPosition; // This answer is the best, as it includes findPositionAround
	Coord3D workingPosition = theirPosition; // But if findPositionAround fails, we need to say something.

	Vector3 offset(ourPosition.x - theirPosition.x,
		ourPosition.y - theirPosition.y,
		ourPosition.z - theirPosition.z);
	offset.Normalize();
	// This scaler makes FindPositionAround bias towards our side
	offset = offset * (target->getGeometryInfo().getMajorRadius() / 2);

	workingPosition.x += offset.X;
	workingPosition.y += offset.Y;
	workingPosition.z += offset.Z;

	// this is a little cheesy... the idea is that we can only choose a location that is pretty close
	// in z to the desired one. this prevents us from choosing a space at the bottom of a cliff when
	// the space we want is at the top of the cliff. ideally we should do a funky terrain-zone compare
	// but that isn't well-exposed... (srj)
	const Real MAX_Z_DELTA = 10.0f;

	FindPositionOptions fpOptions;
	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 100.0f;
	fpOptions.sourceToPathToDest = me; // This makes it find a place forWhom can get to.
	if (!me->isUsingAirborneLocomotor())
		fpOptions.maxZDelta = MAX_Z_DELTA;
	if (me->isUsingAirborneLocomotor())
		fpOptions.ignoreObject = target; // Flyers can ignore stuff, so they can approach right over the target if they want.

	Bool spotFound = findNearestLabeledContactPointOnTarget((Object *)target, &bestPosition, &workingPosition, true);
	if (!spotFound)
		spotFound = PartitionManager::findPositionAround(&workingPosition, &fpOptions, &bestPosition);

	positionOut = spotFound ? bestPosition : workingPosition;

	return spotFound;
}

//-------------------------------------------------------------------------------------------------
void DozerAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	//
	// anytime we get a command, just remove any model condition that has us actively building
	// if we need to show that, that bit will be set anyway again during the build process
	//
	getObject()->clearModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);

	if (!isAllowedToRespondToAiCommands(parms))
		return;

	// if we haven't made the dozer machine yet, do so now
	createMachines();

	switch (parms->m_cmd)
	{
		case AICMD_MOVE_AWAY_FROM_UNIT:
		{
			Object *otherObj = parms->m_obj;
			Bool otherIsDozer = false;
			if (otherObj)
			{
				otherIsDozer = otherObj->isKindOf(KINDOF_DOZER);
			}
			// We only want to do this if we aren't busy doing dozer things. jba.
			// Or if the other guy is a dozer too.
			if (!otherIsDozer && getCurrentTask() != DOZER_TASK_INVALID)
			{
				return; // just ignore it.  jba.
			}
			// issue the command
			AIUpdateInterface::aiDoCommand(parms);
			break;
		}

		// --------------------------------------------------------------------------------------------
		case AICMD_REPAIR:
		{
			// if we have no task right now, go idle so we can immediately respond to this
			if (getCurrentTask() == DOZER_TASK_INVALID)
				aiIdle(CMD_FROM_AI);

			// do the repair
			privateRepair(parms->m_obj, parms->m_cmdSource);
			break;
		}

		// --------------------------------------------------------------------------------------------
		case AICMD_RESUME_CONSTRUCTION:
		{
			// if we have no task right now, go idle so we can immediately respond to this
			if (getCurrentTask() == DOZER_TASK_INVALID)
				aiIdle(CMD_FROM_AI);

			// do the command
			privateResumeConstruction(parms->m_obj, parms->m_cmdSource);
			break;
		}

		// --------------------------------------------------------------------------------------------
		default:
		{
			// if this is from the player, cancel our current task
			if (parms->m_cmdSource == CMD_FROM_PLAYER && getCurrentTask() != DOZER_TASK_INVALID)
				cancelTask(getCurrentTask());

			// issue the command
			AIUpdateInterface::aiDoCommand(parms);

			// when a player issues commands, this will cause the dozer to re-evaluate what it's doing
			if (parms->m_cmdSource == CMD_FROM_PLAYER)
				m_dozerMachine->resetToDefaultState();
			break;
		}
	}
}

class Drawable
{
public:
	void rva00274176(Bool flag);
	void fadeIn(UnsignedInt frames);
	void fadeOut(UnsignedInt frames);
	Rva002390CB rva00274CD8(const AsciiString &name);
	Bool rva002765D4(UnicodeString *name);
	void setDrawableHidden(Bool hide);
	void setDrawableOpacity(Real value) { m_explicitOpacity = value; }
private:
	unsigned char m_pad00[0xB0];
	Real m_explicitOpacity; // +0xB0
};

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	// cl 7.1 lays overloaded virtuals out in reverse declaration order:
	// message(AsciiString) is vslot 15 (+0x3C), message(UnicodeString) 16.
	virtual void message(UnicodeString format, ...);
	virtual void message(AsciiString stringManagerLabel, ...);
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66();
	virtual void deselectDrawable(Drawable *draw); // vslot 67 (+0x10C)
};

extern InGameUI *TheInGameUI;

class AiOrdersManager
{
public:
	void rva00355183(Int a, Int b);
};

extern AiOrdersManager *TheAiOrdersManager;

bool __cdecl rva004884B7(Object *obj);

class Rva0028BAC0
{
public:
	void rva0028BAC0();
};

// ZH's DozerActionMoveToActionPosState (rowed ctor 0x0048851B, vtable
// 0x0084B448).
class DozerActionMoveToActionPosState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

template <class T>
inline const T &bfmeMax(const T &a, const T &b)
{
	return (a > b) ? a : b;
}

static const Real MIN_ACTION_TOLERANCE = 70.0f;

static __declspec(noinline) void Rva00489256Do(Object *obj)
{
	TheInGameUI->deselectDrawable(obj->getDrawable());
	if (rva004884B7(obj))
		return;
	Rva00346BC0 mask(0, 0x3c, 3, 0x4f, 0x63);
	obj->rva0028CDEB(mask, true);
	if (obj->get454())
		reinterpret_cast<Rva0028BAC0 *>(obj)->rva0028BAC0();
}

StateReturnType DozerActionMoveToActionPosState::update()
{
	Object *goalObject = getMachineGoalObject();
	Object *dozer = getMachineOwner();

	// sanity
	if (dozer == 0)
		return STATE_FAILURE;
	if (goalObject == 0)
	{
		DozerAIInterface *dozerAI = dozer->getAIUpdateInterface()->getDozerAIInterface();
		if (dozerAI == 0 || (goalObject = dozerAI->rva00489DD1()) == 0)
			return STATE_FAILURE;
	}

	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (m_task == DOZER_TASK_REPAIR && !dozer->isKindOf(KINDOF_SWARM_DOZER))
	{
		ObjectID currentRepairer = goalObject->getSoleHealingBenefactor();
		if (currentRepairer != INVALID_ID && currentRepairer != dozer->getID()) // oops I guess someone beat me to it!
		{
			if (ai)
			{
				DozerAIInterface *dozerAI = ai->getDozerAIInterface();
				if (dozerAI)
					dozerAI->internalTaskComplete(m_task);
			}
			getMachine()->setGoalObject(0);
			return STATE_FAILURE;
		}
	}

	// if distance between us and our goal position is close enough
	const Coord3D *goalPos = getMachine()->getGoalPosition();
	Real distSqr = dozer->rva002C97E8(dozer->getPosition(), goalPos);
	const Real SLOP = 15.0f;
	Real allowableDistanceSqr = sqr(bfmeMax(MIN_ACTION_TOLERANCE, dozer->getGeometryInfo().getBoundingSphereRadius() + SLOP));

	if (distSqr <= allowableDistanceSqr)
	{
		if (m_task == DOZER_TASK_BUILD)
		{
			DozerAIInterface *dozerAI = ai->getDozerAIInterface();
			if (dozerAI)
			{
				Object *other = dozerAI->rva00489DD1();
				if (other)
				{
					Rva00489256Do(dozer);
					dozerAI->makePhantomStructureReal();
					other->rva0028AB4E();
					TheAiOrdersManager->rva00355183(3, dozer->getID());
				}
			}

			// the object is now no longer awaiting construction, it is being constructed
			Rva001E4912 setBits;
			goalObject->rva0028CFB2((const int *)&Rva0028F59A(0, MODELCONDITION_AWAITING_CONSTRUCTION),
				(const int *)setBits.rva001E4912(0, MODELCONDITION_PARTIALLY_CONSTRUCTED, MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED));
			goalObject->getDrawable()->rva00274176(true);
		}

		return STATE_SUCCESS;
	}

	// if we're in the idle state fail our move
	if (ai && ai->isIdle())
		return STATE_FAILURE;

	return STATE_CONTINUE;
}

class DozerActionPickActionPosState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

StateReturnType DozerActionPickActionPosState::update()
{
	StateMachine *machine = getMachine();
	Object *dozer = machine->getOwner();

	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;
	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
		return STATE_FAILURE;

	Object *goalObject = TheGameLogic->findObjectByID(dozerAI->getTaskTarget(m_task));
	if (goalObject == 0)
	{
		goalObject = dozerAI->rva00489DD1();
		if (goalObject == 0)
		{
			getMachine()->setGoalObject(goalObject);
			dozerAI->cancelTask(m_task);
			return STATE_FAILURE;
		}
	}

	Coord3D goalPos;
	const Coord3D *pos = dozerAI->getDockPoint(m_task, DOZER_DOCK_POINT_START);
	if (pos)
		goalPos = *pos;
	else
	{
		Coord2D v;
		v.x = dozer->getPosition()->x - goalObject->getPosition()->x;
		v.y = dozer->getPosition()->y - goalObject->getPosition()->y;

		Real radius = goalObject->getGeometryInfo().getBoundingSphereRadius();
		FindPositionOptions fpOptions;
		fpOptions.minRadius = radius;
		fpOptions.maxRadius = radius;
		fpOptions.startAngle = v.toAngle();
		if (PartitionManager::findPositionAround(goalObject->getPosition(), &fpOptions, &goalPos) == FALSE)
			goalPos = *goalObject->getPosition();
		else if (g_00E03745 && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile, "\t\t  DozerActionPickActionPosState::update() goalPos is uninitialized");

		ai->ignoreObstacle(goalObject);
	}

	if (g_00E03745 && theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile, "\t\t  DozerActionPickActionPosState::update(), moving to goalPos %.03f, %.03f", goalPos.x, goalPos.y);

	machine->setGoalObject(goalObject);
	machine->setGoalPosition(&goalPos, 3.402823466e+38f);
	ai->ignoreObstacle(goalObject);
	ai->aiMoveToPosition(&goalPos, CMD_FROM_AI);

	return STATE_SUCCESS;
}

// ZH's dozer action states (rowed ctors 0x004884ED, 0x0048851B, 0x00488545).
class Rva004884ED : public State
{
public:
	Rva004884ED(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

class Rva0048851B : public State
{
public:
	Rva0048851B(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x24 - 0x20];
};

class Rva00488545 : public State
{
public:
	Rva00488545(StateMachine *machine, Int task);
private:
	unsigned char m_pad20[0x28 - 0x20];
};

enum
{
	DOZER_ACTION_PICK_ACTION_POS = 0,
	DOZER_ACTION_MOVE_TO_ACTION_POS,
	DOZER_ACTION_DO_ACTION
};

enum
{
	EXIT_MACHINE_WITH_SUCCESS = 9998,
	EXIT_MACHINE_WITH_FAILURE = 9999
};

// ZH's DozerActionStateMachine.
class Rva004885DE : public Rva004D759C
{
public:
	Rva004885DE(Object *owner, Int task);
protected:
	Int m_task; // +0x3C
};

Rva004885DE::Rva004885DE(Object *owner, Int task) : Rva004D759C(owner, 0x253E8923, false)
{
	m_task = task;

	// order matters: first state is the default state.
	defineState(DOZER_ACTION_PICK_ACTION_POS, new Rva004884ED(this, task), DOZER_ACTION_MOVE_TO_ACTION_POS, EXIT_MACHINE_WITH_FAILURE);
	defineState(DOZER_ACTION_MOVE_TO_ACTION_POS, new Rva0048851B(this, task), DOZER_ACTION_DO_ACTION, DOZER_ACTION_PICK_ACTION_POS);
	defineState(DOZER_ACTION_DO_ACTION, new Rva00488545(this, task), EXIT_MACHINE_WITH_SUCCESS, EXIT_MACHINE_WITH_FAILURE);
}

typedef UnsignedInt AudioHandle;

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
	virtual void removeAudioEvent(AudioHandle handle); // vslot 27 (+0x6C)
};

extern AudioManager *TheAudio;

// Folded into FoundationAIUpdate's identical body at 0x004550DE.
void DozerAIUpdate::finishBuildingSound()
{
	TheAudio->removeAudioEvent(m_408);
	m_408 = 1;
}

DozerAIUpdate::~DozerAIUpdate()
{
	finishBuildingSound();

	::delete m_dozerMachine;
	m_dozerMachine = 0;

	for (Int i = 0; i < DOZER_NUM_TASKS; i++)
	{
		m_task[i].m_targetObjectID = INVALID_ID;
		m_task[i].m_taskOrderFrame = 0;
	}

	if (m_4A4 != 0)
		rva00489D09();
}

void DozerAIUpdate::internalTaskCompleteOrCancelled(DozerTask task)
{
	switch (task)
	{
		case DOZER_TASK_INVALID:
			break; // do nothing, this is really no task

		case DOZER_TASK_BUILD:
			// the builder is no longer actively building something
			getObject()->clearModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);
			break;

		case DOZER_TASK_REPAIR:
			// the builder is no longer actively repairing something
			getObject()->clearModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);
			break;

		case DOZER_TASK_FORTIFY:
			break;

		default:
			break;
	}
}

const Coord3D *DozerAIUpdate::getDockPoint(DozerTask task, DozerDockPoint point)
{
	if (task < 0 || task >= DOZER_NUM_TASKS)
		return 0;
	if (point < 0 || point >= DOZER_NUM_DOCK_POINTS)
		return 0;

	if (m_dockPoint[task][point].valid)
		return &m_dockPoint[task][point].location;

	return 0;
}

Object *DozerAIUpdate::rva00489DD1()
{
	return TheGameLogic->findObjectByID((ObjectID)m_4A4);
}

// TheSkirmishAIManager's per-player record (0x002A8AB1), and the AI builder
// call (0x004EC2D4) that takes this dozer's id.
struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};

extern Rva002A8F24 *g_00DFEEF8;

class AIBuilder
{
public:
	void rva004EC2D4(int value);
};

void DozerAIUpdate::notifyConstructionComplete()
{
	Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(getObject()->getControllingPlayer());
	if (record)
		reinterpret_cast<AIBuilder *>(record)->rva004EC2D4(getObject()->getID());
}

class GlobalData
{
public:
	unsigned char m_pad0000[0x11DC];
	UnsignedInt m_11DC; // +0x11DC, the frames a dozer takes to fade out into a site
	UnsignedInt m_11E0; // +0x11E0, the frames a dozer takes to fade back in
	Real m_11E4; // +0x11E4, how far it steps away from the structure it leaves
};

extern GlobalData *TheWritableGlobalData;

// The dozer comes back out of a structure it was working in: it steps away
// from the target (when asked and one is given), fades back in and drops the
// model conditions Rva00489256Do set. Callers: DozerActionDoActionState::update
// (target, TRUE) and cancelTask (none, FALSE).
static __declspec(noinline) void Rva0048A3B9Do(Object *obj, Object *target, Bool moveAway)
{
	if (rva004884B7(obj))
		return;

	if (moveAway && target && TheWritableGlobalData->m_11E4 > 0.0f)
	{
		Coord3D dir = *obj->getPosition();
		dir.sub(target->getPosition());
		dir.normalize();
		dir.scale(TheWritableGlobalData->m_11E4);
		dir.add(*obj->getPosition());
		obj->getAIUpdateInterface()->aiMoveToPosition(&dir, CMD_FROM_PLAYER);
	}

	if (!obj->get454())
		obj->rva0028DCC4();
	obj->getDrawable()->fadeIn(TheWritableGlobalData->m_11E0);

	Rva00346BC0 mask(0, 0x3c, 3, 0x4f, 0x63);
	obj->rva0028CDEB(mask, false);
}

void DozerAIUpdate::cancelTask(DozerTask task)
{
	// clear the order
	internalCancelTask(task);

	// reset the machine to we can re-evaluate what we want to do
	m_dozerMachine->resetToDefaultState();

	if (rva00489DD1())
		rva00489D09();

	Rva0048A3B9Do(getObject(), 0, FALSE);
}

// The rowed two-bit status mask builder.
struct Rva00391F4E : public _STL::_Base_bitset<4>
{
	Rva00391F4E(int unused, int b1, int b2);
};

// What ThingFactory::newObject takes: the initial status bits.
struct CreateMask : public _STL::_Base_bitset<4>
{
	CreateMask() { memset(_M_w, 0, sizeof(_M_w)); }
};

class Team;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *statusBits, Bool flag);
};

extern ThingFactory *TheThingFactory;

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
	Bool isLocalPlayer() const;
	// The flag after ZH's m_canBuildUnits/m_canBuildBase (+0x338/+0x339),
	// where ZH keeps m_observer.
	Bool rva002AA223() const;
	void onStructureCreated(Object *builder, Object *structure);
	void onStructureConstructionComplete(Object *builder, Object *structure, Bool isRebuild);
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

// The rowed add-if-missing object id lists: TheInGameUI's at +0x9C4 and the
// player's at +0x754.
class Rva002A1111
{
public:
	void rva002A1111(ObjectID id);
};

class Rva002AE3F4
{
public:
	void rva002AE3F4(ObjectID id);
};

// Dozer interface vslot 25: BFME 2 places a phantom of the structure first.
// ZH construct's creation steps (newObject, producer and builder, the cost,
// position, orientation, onStructureCreated, zero percent) with the status
// bits PENDING_CONSTRUCTION and PHANTOM_STRUCTURE and model condition
// PHANTOM_STRUCTURE (retail's name tables). Its id goes to +0x4A4, which
// vslots 27 and 29 work on, and the phantom is made inert at once.
void DozerAIUpdate::createPhantomStructure(const ThingTemplate *what, Player *owningPlayer, const Coord3D *pos, Real angle)
{
	if (m_4A4 != 0)
		rva00489D09();

	CreateMask statusBits;
	statusBits._M_do_or(Rva00391F4E(0, OBJECT_STATUS_PENDING_CONSTRUCTION, OBJECT_STATUS_PHANTOM_STRUCTURE));

	Object *obj = TheThingFactory->newObject(what, owningPlayer->getDefaultTeam(), &statusBits, false);
	if (obj == 0)
		return;

	obj->setModelConditionState(MODELCONDITION_PHANTOM_STRUCTURE);

	obj->setProducer(getObject());
	obj->rva0028AFE7(getObject());

	if (m_isRebuild == FALSE)
	{
		UnsignedInt cost = what->rva0033A69A(owningPlayer, (Int)getObject(), -1);
		owningPlayer->getMoney()->rva003B0CB3(cost, owningPlayer->getStats(), true);
		owningPlayer->getStats()->rva0039BAD2((Rva0039BAD2Input *)what, cost);
		obj->m_buildCost = (Real)cost;
	}

	obj->setPosition(pos);
	obj->setOrientation(angle);

	owningPlayer->onStructureCreated(getObject(), obj);

	obj->setConstructionPercent(0.0f);

	// only the builder's own side (or, where ZH keeps it, an observer) sees
	// the phantom; everyone else gets it hidden
	Object *me = getObject();
	if (!me->getControllingPlayer()->isLocalPlayer() && !me->getControllingPlayer()->rva002AA223())
		obj->getDrawable()->setDrawableHidden(true);
	else
		((Rva002A1111 *)TheInGameUI)->rva002A1111(obj->getID());

	obj->getDrawable()->setDrawableOpacity(0.4f);

	me = getObject();
	m_4A4 = obj->getID();
	if (me && me->get45C())
		TheGameLogic->rva0023D0C2(obj, me->get45C());

	makePhantomStructureInert();

	if (me)
	{
		Player *player = me->getControllingPlayer();
		if (player)
			((Rva002AE3F4 *)player)->rva002AE3F4((ObjectID)m_4A4);
	}
}

// The status mask builder's pinned spelling (memset, then one bit).
struct ObjectStatusMask : public _STL::_Base_bitset<4>
{
	ObjectStatusMask *Rva0023DA79(int reserved, ObjectStatusTypes bit);
	void set(ObjectStatusTypes bit) { _M_w[bit >> 5] |= 1U << (bit & 31); }
};

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE
};

class BodyModuleInterface
{
public:
	virtual void i00(); virtual void i01(); virtual void i02(); virtual void i03();
	virtual Real getHealth() const; // +0x10
	virtual void i05();
	virtual Real getMaxHealth() const; // +0x18
	virtual void i07();
	virtual BodyDamageType getDamageState() const; // +0x20
	virtual void i09(); virtual void i10(); virtual void i11();
	virtual void i12(); virtual void i13(); virtual void i14(); virtual void i15();
	virtual void i16(); virtual void i17(); virtual void i18(); virtual void i19();
	virtual void i20(); virtual void i21(); virtual void i22(); virtual void i23();
	virtual void i24(); virtual void i25(); virtual void i26(); virtual void i27();
	virtual void i28(); virtual void i29(); virtual void i30(); virtual void i31();
	virtual void internalChangeHealth(Real delta, Int flag); // +0x80
	virtual void i33(); virtual void i34(); virtual void i35();
	virtual void evaluateVisualCondition(); // +0x90
};

enum { LBC_OK = 0 };

class BuildAssistant
{
public:
	enum
	{
		TERRAIN_RESTRICTIONS = 0x01,
		NO_OBJECT_OVERLAP = 0x04,
		SHROUD_REVEALED = 0x10
	};
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual Int isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, Real angle,
		UnsignedInt options, Object *builderObject, Player *player); // +0x40
	void clearRemovableForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle);
	Bool moveObjectsForConstruction(const ThingTemplate *whatToBuild, const Coord3D *pos, Real angle, Player *playerToBuild);
};

extern BuildAssistant *TheBuildAssistant;

class GeometryInfo;

class TerrainLogic
{
public:
	virtual void t00(); virtual void t01(); virtual void t02(); virtual void t03();
	virtual void t04(); virtual void t05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const; // +0x18
	// BFME 2's: it destroys what intersects the footprint, then has the
	// terrain visual (vslot 18) remove trees and props for construction.
	void rva0028449F(const Coord3D *pos, const GeometryInfo &geom, Real angle);
	void flattenTerrain(Object *obj);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
	void RemoveObjectFromPathfindMap(Object *object);
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

// The rowed guarded remove from TheInGameUI's id list at +0x9C4.
class Rva0029F93A
{
public:
	void rva0029F93A(Int id);
};

// Dozer interface vslot 26: the phantom becomes the real structure under
// construction. Unless rebuilding, a human player's (or a skirmish AI's)
// site must still be legal to build, else the phantom is dropped (vslot 27).
// Then the rest of ZH construct: clear and move what is in the way, flatten
// the terrain and settle on it, one hit point, the under-construction status
// bits, the pathfind map; the phantom bits, hiding and opacity come off.
void DozerAIUpdate::makePhantomStructureReal()
{
	if (m_4A4 == 0)
		return;

	Object *obj = TheGameLogic->findObjectByID((ObjectID)m_4A4);
	if (obj == 0)
	{
		m_4A4 = 0;
		return;
	}

	if (m_isRebuild == FALSE)
	{
		if (getObject()->getControllingPlayer()->getPlayerType() != PLAYER_COMPUTER ||
			g_00DFEEF8->rva002A8AB1(getObject()->getControllingPlayer()) != 0)
		{
			if (TheBuildAssistant->isLocationLegalToBuild(obj->getPosition(), obj->getTemplate(), obj->getOrientation(),
					BuildAssistant::TERRAIN_RESTRICTIONS |
					BuildAssistant::NO_OBJECT_OVERLAP |
					BuildAssistant::SHROUD_REVEALED,
					getObject(), 0) != LBC_OK)
			{
				rva00489D09();
				return;
			}
		}
	}

	makePhantomStructureNotInert();

	if (!obj->isKindOf(KINDOF_NO_COLLIDE) && !obj->isKindOf(KINDOF_DO_NOT_CLASSIFY))
	{
		TheBuildAssistant->clearRemovableForConstruction(obj->getTemplate(), obj->getPosition(), obj->getOrientation());
		TheBuildAssistant->moveObjectsForConstruction(obj->getTemplate(), obj->getPosition(), obj->getOrientation(), obj->getControllingPlayer());
		TheTerrainLogic->rva0028449F(obj->getPosition(), obj->getGeometryInfo(), obj->getOrientation());
	}

	obj->clearModelConditionState(MODELCONDITION_PHANTOM_STRUCTURE);

	// newly constructed objects start at one hit point
	BodyModuleInterface *body = obj->getBodyModule();
	body->internalChangeHealth(-body->getHealth() + 1.0f, 0);

	// Flatten the terrain underneath the object, then adjust to the flattened height. jba.
	TheTerrainLogic->flattenTerrain(obj);
	Coord3D adjustedPos = *obj->getPosition();
	adjustedPos.z = TheTerrainLogic->getGroundHeight(obj->getPosition()->x, obj->getPosition()->y);
	obj->setPosition(&adjustedPos);

	ObjectStatusMask statusBits;
	statusBits.Rva0023DA79(0, OBJECT_STATUS_UNDER_CONSTRUCTION);
	if (m_isRebuild)
		statusBits.set(OBJECT_STATUS_RECONSTRUCTING);
	obj->rva0028CDEB(&statusBits, true);

	static_cast<_STL::_Base_bitset<4> &>(statusBits) = Rva00391F4E(0, OBJECT_STATUS_PENDING_CONSTRUCTION, OBJECT_STATUS_PHANTOM_STRUCTURE);
	obj->rva0028CDEB(&statusBits, false);

	// Note - very important that we add to map AFTER we flatten terrain. jba.
	TheAI->pathfinder()->AddObjectToPathfindMap(obj);

	obj->getDrawable()->setDrawableHidden(false);
	obj->getDrawable()->setDrawableOpacity(1.0f);

	((Rva0029F93A *)TheInGameUI)->rva0029F93A(m_4A4);
	m_4A4 = 0;
}

// The drawable's sound record (8 bytes, a reference at +4), as
// DrawableKeyedLookup.cpp spells it.
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
public:
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva002390CB
{
public:
	int m_0;
	Rva0036CA00Str m_4;
};

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0; virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0; virtual void slot06() = 0;
	virtual void slot07() = 0; virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0; virtual void slot12() = 0;
	virtual void slot13() = 0;
	// cl 7.1 lays overloaded virtuals out in reverse declaration order:
	// fetch(const char *) is slot 15 (+0x3C), fetch(const AsciiString &) 14.
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

enum RadarEventType
{
	RADAR_EVENT_INVALID = 0,
	RADAR_EVENT_CONSTRUCTION
};

class Radar
{
public:
	void createEvent(const Coord3D *world, RadarEventType type, Real secondsToLive = 4.0f);
};

extern Radar *TheRadar;

// Retail calls the list destructor out of line (the shared pointer-list
// destructor 0x00239AF4).
class DrawableList : public _STL::list<Drawable *>
{
public:
	~DrawableList() throw();
};

class PickAndPlayInfo;

class GameMessage
{
public:
	enum Type
	{
		MSG_BFME2_0x7DE = 0x7DE
	};
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type messageType,
	PickAndPlayInfo *info);

class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge);
	virtual ObjectID getBridgeID(); // vslot 1
};

class BridgeTowerBehavior
{
public:
	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *obj);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

// The three-bit model condition mask builder (19 dwords).
class Rva00265254
{
public:
	Rva00265254(UnsignedInt unused, UnsignedInt bit1, UnsignedInt bit2, UnsignedInt bit3);
private:
	unsigned int m_words[19];
};

class Rva0028CBFD
{
public:
	void rva0028CBFD();
};

// LOGICFRAMES_PER_SECOND.
extern const int g_009BA4E4;

static const Real CONSTRUCTION_COMPLETE = -1.0f;

// ZH's DozerActionDoActionState (rowed ctor 0x00488545, vtable slot 6).
//
// ?update@DozerActionDoActionState@@UAE?AW4StateReturnType@@XZ, retail
// 0x0048A69E, 2028 bytes: vtable slot 6 of the state the ctor 0x00488545
// builds. ZH DozerActionDoActionState::update's shape (task switch over
// REPAIR and BUILD, construction percent stepping, completion through the
// dozer's internalTaskComplete); BFME 2 adds the castle check, the rubble/
// damage/under-construction drawable lookups (0x00274CD8) and the voice
// response through a stack DrawableList. The BUILD branch tests the
// complete case first, and the list is STLport's own (its by-value iterator
// and temps fix the frame at 0xE0).
class DozerActionDoActionState : public State
{
public:
	virtual StateReturnType update();
private:
	DozerTask m_task; // +0x20
};

StateReturnType DozerActionDoActionState::update()
{
	Object *goalObject = getMachineGoalObject();
	Object *dozer = getMachineOwner();
	AIUpdateInterface *ai = dozer->getAIUpdateInterface();
	if (!ai)
		return STATE_FAILURE;

	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (!dozerAI)
		return STATE_FAILURE;

	// check for object gone
	if (goalObject == 0)
		return STATE_FAILURE;

	Drawable *draw = goalObject->getDrawable();

	if (dozer->isDisabledByType(DISABLED_UNMANNED)) // Yipes, I've been sniped!
		return STATE_FAILURE;

	// do the task
	Bool complete = FALSE;
	switch (m_task)
	{
		case DOZER_TASK_BUILD:
		{
			if (dozer->getControllingPlayer() != goalObject->getControllingPlayer()) // Yipes, SOmehow I have changed sides in mid build!
				return STATE_FAILURE;

			// if we need to select the dock location and move there do so
			if (dozerAI->getBuildSubTask() == DOZER_SELECT_BUILD_DOCK_LOCATION)
			{
				const Coord3D *dockLocation = dozerAI->getDockPoint(m_task, DOZER_DOCK_POINT_ACTION);
				if (dockLocation)
				{
					if (g_00E03745 && theLogicRandomLogFile)
						fprintf(theLogicRandomLogFile, "\t\t  DozerActionDoActionState::update() moving to dock location %.03f, %.03f", dockLocation->x, dockLocation->y);
					ai->aiMoveToPosition(dockLocation, CMD_FROM_AI);
				}

				// we're now moving to the dock location
				dozerAI->setBuildSubTask(DOZER_MOVING_TO_BUILD_DOCK_LOCATION);
			}

			// if we're moving to the build dock location, when we become idle we are there
			if (dozerAI->getBuildSubTask() == DOZER_MOVING_TO_BUILD_DOCK_LOCATION && ai->isIdle())
			{
				dozerAI->setBuildSubTask(DOZER_FACING_BUILD_TARGET);
				ai->aiFaceObject(goalObject, CMD_FROM_AI);
			}

			if (dozerAI->getBuildSubTask() == DOZER_FACING_BUILD_TARGET && ai->isIdle())
			{
				dozerAI->setBuildSubTask(DOZER_DO_BUILD_AT_DOCK);

				// start playing the construction sound (from the building itself)
				if (draw)
					dozerAI->startBuildingSound(draw->rva00274CD8("UnderConstruction"), goalObject->getID());

				if (!rva004884B7(dozer))
					dozer->getDrawable()->fadeOut(TheWritableGlobalData->m_11DC);
			}

			// only do the build if we've moved into the dock position
			if (dozerAI->getBuildSubTask() == DOZER_DO_BUILD_AT_DOCK)
			{
				// the builder is now actively constructing something
				dozer->setModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);

				if (goalObject->isEffectivelyDead())
				{
					dozerAI->cancelTask(DOZER_TASK_BUILD);
					ai->aiIdle(CMD_FROM_AI);
					return STATE_CONTINUE;
				}

				if (goalObject->getConstructionPercent() == CONSTRUCTION_COMPLETE)
				{
					Rva0048A3B9Do(dozer, goalObject, TRUE);
					complete = TRUE;
				}
				else
				{
					// increase the construction percent of the goal object
					Int framesToBuild = goalObject->getTemplate()->rva0033AA1F(dozer->getControllingPlayer(), (Int)dozer, -1);
					Real percentProgressThisFrame = 100.0f / framesToBuild;
					goalObject->setConstructionPercent(goalObject->getConstructionPercent() + percentProgressThisFrame);

					// every time we construct a piece of the goal object, the goal object gets a little bit o health
					BodyModuleInterface *body = goalObject->getBodyModule();
					body->internalChangeHealth(body->getMaxHealth() / (Real)framesToBuild, 0);

					if (goalObject->getProducerID() == INVALID_ID)
						goalObject->setProducer(dozer);

					// check for construction complete
					if (goalObject->getConstructionPercent() >= 100.0f)
					{
						// clear the under construction status
						goalObject->setStatus(OBJECT_STATUS_UNDER_CONSTRUCTION, false);
						goalObject->setStatus(OBJECT_STATUS_RECONSTRUCTING, false);

						// stop playing the construction sound!
						dozerAI->finishBuildingSound();

						// object will now be idle instead of in one of the construction actions
						Module *castle = goalObject->findModule(CastleBehavior::rva0003955DA());
						if (castle)
						{
							goalObject->rva001E42F2((const int *)&Rva0028F59A(0, MODELCONDITION_AWAITING_CONSTRUCTION));
							goalObject->setSpecialModelConditionState(MODELCONDITION_PARTIALLY_CONSTRUCTED, 5);
							goalObject->setSpecialModelConditionState(MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED, 5);
						}
						else
						{
							goalObject->rva001E42F2((const int *)&Rva00265254(0, MODELCONDITION_AWAITING_CONSTRUCTION,
								MODELCONDITION_PARTIALLY_CONSTRUCTED, MODELCONDITION_ACTIVELY_BEING_CONSTRUCTED));
						}

						// set the construction at the 100% enum value
						goalObject->setConstructionPercent(CONSTRUCTION_COMPLETE);

						body->evaluateVisualCondition();

						// this object now has energy influence in the player
						Player *player = goalObject->getControllingPlayer();
						if (player)
						{
							// notification for build completeion
							player->onStructureConstructionComplete(dozer, goalObject, dozerAI->getIsRebuild());
							reinterpret_cast<Rva0028CBFD *>(goalObject)->rva0028CBFD();
						}

						goalObject->getDrawable()->rva00274176(true);

						TheAI->pathfinder()->RemoveObjectFromPathfindMap(goalObject);
						TheAI->pathfinder()->AddObjectToPathfindMap(goalObject);

						// do some UI stuff for the constrolling player
						if (dozer->isLocallyControlled())
						{
							// message the the building player
							UnicodeString format = TheGameText->fetch("DOZER:ConstructionComplete");
							UnicodeString objectName;
							Drawable *goalDraw = goalObject->getDrawable();
							objectName = (goalDraw && goalDraw->rva002765D4(&objectName)) ? objectName
								: *(const UnicodeString *)goalObject->getDisplayName();
							if (objectName.isEmpty())
							{
								UnicodeString format = TheGameText->fetch("INI:MissingDisplayName");
								objectName.format(&format, goalObject->getTemplate()->getName().str());
							}

							UnicodeString msg;
							msg.format(format.str(), objectName.str());
							TheInGameUI->message(msg);

							DrawableList list;
							list.push_back(dozer->getDrawable());
							pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_BFME2_0x7DE, 0);

							/// make radar neat-o attention grabber event at build location
							TheRadar->createEvent(goalObject->getPosition(), RADAR_EVENT_CONSTRUCTION);
						}

						Rva0048A3B9Do(dozer, goalObject, TRUE);
						complete = TRUE;
					}
					else
					{
						if (goalObject->getBuilderID() == INVALID_ID)
							goalObject->rva0028AFE7(dozer);
					}
				}
			}

			break;
		}

		case DOZER_TASK_REPAIR:
		{
			BodyModuleInterface *body = goalObject->getBodyModule();

			if (dozerAI->getBuildSubTask() == DOZER_SELECT_BUILD_DOCK_LOCATION)
			{
				const Coord3D *dockLocation = dozerAI->getDockPoint(m_task, DOZER_DOCK_POINT_ACTION);
				if (dockLocation)
					ai->aiMoveToPosition(dockLocation, CMD_FROM_AI);

				dozerAI->setBuildSubTask(DOZER_MOVING_TO_BUILD_DOCK_LOCATION);
			}

			if (dozerAI->getBuildSubTask() == DOZER_MOVING_TO_BUILD_DOCK_LOCATION && ai->isIdle())
			{
				dozerAI->setBuildSubTask(DOZER_FACING_BUILD_TARGET);
				ai->aiFaceObject(goalObject, CMD_FROM_AI);
			}

			if (dozerAI->getBuildSubTask() == DOZER_FACING_BUILD_TARGET && ai->isIdle())
			{
				dozerAI->setBuildSubTask(DOZER_DO_BUILD_AT_DOCK);

				if (draw)
				{
					if (body->getDamageState() == BODY_RUBBLE)
						dozerAI->startBuildingSound(draw->rva00274CD8("UnderRepairFromRubble"), goalObject->getID());
					else
						dozerAI->startBuildingSound(draw->rva00274CD8("UnderRepairFromDamage"), goalObject->getID());
				}
			}

			if (dozerAI->getBuildSubTask() == DOZER_DO_BUILD_AT_DOCK)
			{
				// check for fully "repaired"
				if (body->getHealth() == body->getMaxHealth())
				{
					// issue repair complete message
					TheInGameUI->message("DOZER:RepairComplete");

					dozerAI->finishBuildingSound();

					// we're now complete
					complete = TRUE;
				}
				else
				{
					Bool canHeal = TRUE;

					// if we are repairing a bridge, create scaffolding over the bridge if we need to
					if (goalObject->isKindOf(KINDOF_BRIDGE_TOWER))
						dozerAI->createBridgeScaffolding(goalObject);

					// the builder is now actively repairing something, we'll borrow the constructing animation
					dozer->setModelConditionState(MODELCONDITION_ACTIVELY_CONSTRUCTING);

					// when repairing bridges, we cannot actually do any repairing until the
					// scaffolding is extended and all the way complete
					if (goalObject->isKindOf(KINDOF_BRIDGE_TOWER))
					{
						BridgeTowerBehaviorInterface *btbi = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(goalObject);
						Object *bridgeObject = TheGameLogic->findObjectByID(btbi->getBridgeID());
						BridgeBehaviorInterface *bbi = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridgeObject);

						if (bbi->isScaffoldInMotion() == TRUE)
							canHeal = FALSE;
					}

					// do healing
					if (canHeal)
					{
						// figure out how much health we will restore this frame
						Real health = body->getMaxHealth() * dozerAI->getRepairHealthPerSecond() / g_009BA4E4;

						// try to give it a little bit-o-health
						if (!goalObject->rva0028FEA7(health, dozer, 2)) // this frame and the next
						{
							dozerAI->internalTaskComplete(m_task);
							getMachine()->setGoalObject(0);
							return STATE_FAILURE;
						}
					}
				}
			}

			break;
		}

		case DOZER_TASK_FORTIFY:
		{
			break;
		}

		default:
		{
			return STATE_FAILURE;
		}
	}

	// if we're complete with the task we exit success
	if (complete == TRUE)
	{
		// this task is now complete, remove it from dozer consideration
		dozerAI->internalTaskComplete(m_task);

		// to be clean get rid of the goal object we set
		getMachine()->setGoalObject(0);

		dozerAI->notifyConstructionComplete();

		// we're done
		return STATE_SUCCESS;
	}

	return STATE_CONTINUE;
}
