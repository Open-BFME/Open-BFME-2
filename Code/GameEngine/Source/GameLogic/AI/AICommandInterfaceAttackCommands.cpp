// cl: /DNDEBUG /MD /GX
//
// ?aiForceAttackObject@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z,
// retail 0x0036F05A, 110 bytes, plus
// ?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z,
// retail 0x0029599A, 117 bytes. Dedicated TU for the two SpawnBehavior
// slave-loop callees.
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/
// AICommandInterfaceAttackCommands.cpp, AICommandInterface::aiForceAttackObject
// plus aiAttackPosition): build the parameter block on the stack, drop the
// victim or position plus the shot count into their slots, then aiDoCommand
// at vtable slot 0. BFME2 deltas: the command ids are 0x0C and 0x0E, the
// block constructor is the opaque 0x351BD0 pin (cmd plus source, builds the
// +0x20 coordinate vector among the zeroed slots), and block teardown is an
// inline coordinate-buffer free through the C++-linkage free pinned at
// 0x00030830 (pin note: that decoration is what carries the unwind state).

typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;
class Team;
class Waypoint;
class PolygonTrigger;

enum AICommandType
{
	AICMD_TIGHTEN_TO_POSITION = 0x02,
	AICMD_MOVE_TO_POSITION_AND_EVACUATE = 0x03,
	AICMD_MOVE_TO_POSITION_AND_EVACUATE_AND_EXIT = 0x04,
	AICMD_IDLE = 5,
	AICMD_FOLLOW_WAYPOINT_PATH = 0x06,
	AICMD_FOLLOW_WAYPOINT_PATH_AS_TEAM = 0x07,
	AICMD_FORCE_ATTACK_OBJECT = 0x0C,
	AICMD_ATTACK_TEAM = 0x0D,
	AICMD_ATTACK_POSITION = 0x0E,
	AICMD_HUNT = 0x12,
	AICMD_EXIT = 0x1A,
	AICMD_EVACUATE = 0x1B,
	AICMD_GUARD_POSITION = 0x1E,
	AICMD_ATTACK_AREA = 0x23,
	AICMD_FACE_OBJECT = 0x26,
	AICMD_FACE_POSITION = 0x27,
	AICMD_WANDER_IN_PLACE = 0x2C,
	AICMD_FOLLOW_WAYPOINT_PATH_EXACT = 0x32,
	AICMD_BFME_33 = 0x33,
	AICMD_BFME_35 = 0x35,
	AICMD_BFME_3D = 0x3D
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

extern "C" void free(void *block);

class Rva003427DD
{
public:
	Rva003427DD &operator=(const Rva003427DD &src);
private:
	char m_data[0x7C];
};

class Rva0035149F
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};

struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	Object *m_obj; // +0x14
	Object *m_otherObj; // +0x18
	const void *m_team; // +0x1C
	void *m_coordsStart; // +0x20, coordinate vector buffer
	void *m_coordsFinish; // +0x24
	void *m_coordsEnd; // +0x28
	const Waypoint *m_waypoint; // +0x2C
	const void *m_polygon; // +0x30
	Int m_intValue; // +0x34
	float m_float38; // +0x38, float store for AICMD 0x50 (retail movss at +0x38)
	Rva003427DD m_3C; // +0x3C, copied via rowed 0x003427DD (e.g. 0x0036F400)
	char m_tailPad[0xC0 - 0x3C - 0x7C]; // +0xB8..+0xBF, retail block size
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;

	void aiIdle(CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource);
	void aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	void rva0026C2D9(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiFacePosition(const Coord3D *pos, Int cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFaceObject(Object *target, CommandSourceType cmdSource);
	void rva0026C3AC(Object *target, CommandSourceType cmdSource);
	void rva0026C486(Object *target, CommandSourceType cmdSource);
	void rva0026C411(Object *victim, const Coord3D *pos, CommandSourceType cmdSource);
	void rva0026C347(Object *target, CommandSourceType cmdSource);
	void aiWanderInPlace(CommandSourceType cmdSource);
	void rva003C7653(Object *target, CommandSourceType cmdSource);
	void rva0036EBB8(Object *target, CommandSourceType cmdSource);
	void rva0036EC1D(Object *target, CommandSourceType cmdSource);
	void rva0036EFF5(Object *target, CommandSourceType cmdSource);
	void aiExit(Object *objectToExit, CommandSourceType cmdSource);
	void aiBfmeObjectCommand3D(Object *obj, CommandSourceType cmdSource);
	void aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType cmdSource);
	void aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource);
	void aiGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType cmdSource);
	void rva0045003E(Int value, CommandSourceType cmdSource);
	void aiTightenToPosition(const Coord3D *position, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *position, CommandSourceType cmdSource);
	void aiMoveToAndEvacuateAndExit(const Coord3D *position, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *position, CommandSourceType cmdSource);
	void rva0036F400(const Rva003427DD *info, CommandSourceType cmdSource);
	void rva0036F19B(Object *target, CommandSourceType cmdSource);
	void rva0036F200(Object *target, CommandSourceType cmdSource);
	void rva0036F265(Object *target, CommandSourceType cmdSource);
	void rva0036F2CA(Object *target, CommandSourceType cmdSource);
	void aiHarvest(const Coord3D *position, CommandSourceType cmdSource);
	void rva0036F4DF(Object *target, Int value, CommandSourceType cmdSource);
	void rva0036F54D(const Team *team, Int value, CommandSourceType cmdSource);
	void rva0036F5BB(const PolygonTrigger *area, Int value, CommandSourceType cmdSource);
	void aiGuardAreaFromPosition(const PolygonTrigger *area, Int value, CommandSourceType cmdSource, const Coord3D *pos);
	void rva0036F6A7(float value, CommandSourceType cmdSource);
	void aiMoveToPositionAndFaceDirection(const Coord3D *position, CommandSourceType cmdSource, float value);
	void aiAttackMoveToPositionAndFaceDirection(const Coord3D *position, Int value, CommandSourceType cmdSource, float floatValue);
	void rva003C77EE(const Waypoint *waypoint, CommandSourceType cmdSource);
	void rva003C76B8(Int value, CommandSourceType cmdSource);
	void rva003C78AF(const Waypoint *waypoint, CommandSourceType cmdSource);
	void aiAttackMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource);
	void aiMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource);
	void rva0037379B(Object *target, CommandSourceType cmdSource);
	void rva0044FFD9(Object *target, CommandSourceType cmdSource);
	void aiMoveToPositionSA(const Coord3D *pos, Int cmdSource);
	void rva0036EE16(const Rva0035149F *info, Object *target, CommandSourceType cmdSource);
	void rva0036EE89(const Rva0035149F *info, Object *target, float value, CommandSourceType cmdSource);
	void rva0036EF09(const Rva0035149F *info, Object *target, float value, CommandSourceType cmdSource);
};

// ?aiIdle@AICommandInterface@@QAEXW4CommandSourceType@@@Z @0x1E8A38
inline void AICommandInterface::aiIdle(CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_IDLE, cmdSource);
	aiDoCommand(&parms);
}

// ?aiHunt@AICommandInterface@@QAEXW4CommandSourceType@@@Z, retail 0x002AE657, 92 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceMovementOrders.cpp
// aiHunt at AICMD 0x12 with no field store plus slot-0 aiDoCommand.
// BFME2 same id 0x12 plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x002AEA5C 0x00353968 0x003700AF 0x003C8AB7 plus 4 more.
inline void AICommandInterface::aiHunt(CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_HUNT, cmdSource);
	aiDoCommand(&parms);
}

// ?aiForceAttackObject@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z @0x36F05A
inline void AICommandInterface::aiForceAttackObject(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FORCE_ATTACK_OBJECT, cmdSource);
	parms.m_obj = victim;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// ?rva0026C2D9@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z, retail 0x0026C2D9, 110 bytes.
// Same 110B shape as aiForceAttackObject in this TU: AICMD 0x0B plus m_obj at +0x14 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Gap between aiMoveToPosition and rva0026C347; donor BFME1 ATTACK_OBJECT 0x0B with same m_obj plus int slots.
// Pinned as ?Rva0026C2D9Command@Rva0026C2D9Commands@@QAEXPAXHH@Z (void plus int plus int) for 27 callers.
void AICommandInterface::rva0026C2D9(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x0B, cmdSource);
	parms.m_obj = victim;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// ?aiAttackPosition@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@@Z @0x29599A
inline void AICommandInterface::aiAttackPosition(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_ATTACK_POSITION, cmdSource);
	parms.m_pos = *pos;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// ?aiFacePosition@AICommandInterface@@QAEXPBUCoord3D@@H@Z, retail 0x003C7782, 108 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceFaceCommands.cpp
// aiFacePosition at AICMD 0x47 plus m_pos at +0x08 plus slot-0 aiDoCommand.
// BFME2 delta is AICMD 0x27 plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x003C9A75 and 0x003C9B92 pass Waypoint location plus source 1.
void AICommandInterface::aiFacePosition(const Coord3D *pos, Int cmdSource)
{
	AICommandParms parms(AICMD_FACE_POSITION, (CommandSourceType)cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

// ?aiMoveToPosition@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z, retail 0x0026C26D, 108 bytes.
// Zero Hour's signature: the command source is the CommandSourceType enum, as its
// callers in the ported AI and update code spell it (formerly rowed with an Int).
// Same 108B position shape as aiFacePosition in this TU: AICMD 0x00 plus m_pos at +0x08 plus slot-0 aiDoCommand.
// Class proven by caller at 0x002AF138 via lea ecx,[esi+0x20] (AICommandInterface subobject) with Coord3D plus source 1.
// Callers at 0x0026D1C0 0x0026D519 0x002AF138 plus 37 more; landing unblocks 37.
void AICommandInterface::aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0, cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

// ?aiFaceObject@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x003C771D, 101 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceFaceCommands.cpp
// aiFaceObject at AICMD 0x26 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// BFME2 same id 0x26 plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x003C9A18 and 0x003C9AFE pass named Object plus source 1.
void AICommandInterface::aiFaceObject(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FACE_OBJECT, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0026C3AC@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0026C3AC, 101 bytes.
// Same 101B object shape as aiFaceObject in this TU: AICMD 0x18 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x0037023C via lea ecx,[eax+0x20] (AICommandInterface subobject).
// Callers at 0x0026DDE4 0x0037023C 0x004A72E5 plus 3 more; landing unblocks 3.
void AICommandInterface::rva0026C3AC(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x18, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0026C486@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0026C486, 101 bytes.
// Same 101B object shape as aiFaceObject in this TU: AICMD 0x4F plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x0026D5F0 via add ecx,0x20 to AIUpdate+0x258 (AICommandInterface subobject).
// Caller at 0x0026D5F0; landing unblocks 1.
void AICommandInterface::rva0026C486(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x4F, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0026C411@AICommandInterface@@QAEXPAVObject@@PBUCoord3D@@W4CommandSourceType@@@Z, retail 0x0026C411, 117 bytes.
// Same TU object-plus-position shape: AICMD 0x34 plus m_obj at +0x14 plus m_pos at +0x08 plus slot-0 aiDoCommand.
// Class proven by caller at 0x0026D837 via add ecx,0x20 to AIUpdate+0x258 (AICommandInterface subobject).
// Callers at 0x0026D837 0x002F3F0F 0x002F40D9 0x00498E24; landing unblocks 4.
void AICommandInterface::rva0026C411(Object *victim, const Coord3D *pos, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x34, cmdSource);
	parms.m_obj = victim;
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

// ?rva0026C347@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0026C347, 101 bytes.
// Same 101B object shape as aiFaceObject in this TU: AICMD 0x17 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by same-page siblings plus caller at 0x003C8607 via AIUpdate+0x258 plus 0x20 (see pin 3884 for 14 sites).
// Pinned as ?Rva0026C347Command@Rva0026C347Commands@@QAEXPAXH@Z (void plus int) for 2 matched callers; this row records the proven AICommandInterface owner.
void AICommandInterface::rva0026C347(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x17, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?aiWanderInPlace@AICommandInterface@@QAEXW4CommandSourceType@@@Z, retail 0x003C7853, 92 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceStandingOrders.cpp
// aiWanderInPlace at AICMD 0x2C with no field store plus slot-0 aiDoCommand.
// BFME2 same id 0x2C plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Caller at 0x003C8BB3 passes source 1 through AIUpdateInterface+0x20.
void AICommandInterface::aiWanderInPlace(CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_WANDER_IN_PLACE, cmdSource);
	aiDoCommand(&parms);
}

// ?rva003C7653@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x003C7653, 101 bytes.
// Same 101B object shape as aiFaceObject in this TU: AICMD 0x49 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// BFME1 has no 0x49 command; class proven by callers through AIUpdateInterface+0x20 with source 1.
// Callers at 0x003C7982 0x003C9666 0x003C999C 0x004BB658 0x005AD79B plus 3 more.
void AICommandInterface::rva003C7653(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x49, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// retail 0x0036EBB8, 101 bytes.
// Same 101B object shape as rva003C7653 in this TU: AICMD 0x42 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// BFME1 has no 0x42 command; class proven by caller at 0x00372A05 via lea ecx,[esi+0x20] (AICommandInterface subobject).
// Callers at 0x00372A05 0x00480E21 0x004A0655 0x004CDCF9 0x00546E1C 0x00546EB8.
void AICommandInterface::rva0036EBB8(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x42, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// retail 0x0036EC1D, 101 bytes. Gap between rva0036EBB8 and aiFollowWaypointPath in this TU.
// Same 101B object shape: AICMD 0x45 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x003705B7 via lea ecx,[esi+0x20] (AICommandInterface subobject).
// Callers at 0x003705B7 and 0x004C89A9.
void AICommandInterface::rva0036EC1D(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x45, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// retail 0x0036EFF5, 101 bytes. Gap between aiBfmeCommand33 and aiForceAttackObject in this TU.
// Same 101B object shape: AICMD 0x39 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x003C8339 via lea ecx,[esi+0x20] (AICommandInterface subobject) with source 1.
// Callers at 0x0036FEEC and 0x003C8339.
void AICommandInterface::rva0036EFF5(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x39, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?aiExit@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0036F39B, 101 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceObjectCommands.cpp
// aiExit at AICMD 0x1A plus m_obj at +0x14 plus slot-0 aiDoCommand.
// BFME2 same id 0x1A plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Class proven by caller at 0x003702A8 via lea ecx,[eax+0x20] (AICommandInterface subobject).
// Callers at 0x003702A8 0x00373C54 0x003787A9 0x003C8E72 0x003C90D5 plus 9 more.
inline void AICommandInterface::aiExit(Object *objectToExit, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_EXIT, cmdSource);
	parms.m_obj = objectToExit;
	aiDoCommand(&parms);
}

// ?aiBfmeObjectCommand3D@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x00470447, 101 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceBfmeObjectCommands.cpp
// aiBfmeObjectCommand3D at 0x00240680 with AICMD 0x3D plus m_obj at +0x14 plus slot-0 aiDoCommand.
// BFME2 delta is the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Placement is the HordeContain page with caller at 0x00472BB3.
void AICommandInterface::aiBfmeObjectCommand3D(Object *obj, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_3D, cmdSource);
	parms.m_obj = obj;
	aiDoCommand(&parms);
}

// retail 0x0036EC82, 101 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceFollowPathCommands.cpp
// aiFollowWaypointPath at AICMD 0x06 plus m_waypoint at +0x2C plus slot-0 aiDoCommand.
// BFME2 delta is the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x0036FA44 and 0x003C8767 plus 0x003C928D.
void AICommandInterface::aiFollowWaypointPath(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// retail 0x0036ECE7, 101 bytes. Gap between aiFollowWaypointPath and aiForceAttackObject in this TU.
// BFME1 donor AICommandInterfaceFollowPathCommands.cpp aiFollowWaypointPathExact at AICMD 0x32
// plus m_waypoint at +0x2C plus slot-0 aiDoCommand. Class proven by caller at 0x003C885E
// via lea ecx,[edi+0x20] in doNamedFollowWaypointsExact at 0x003C87F1 with source 1.
// Callers at 0x0036FA7B and 0x003C885E.
void AICommandInterface::aiFollowWaypointPathExact(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH_EXACT, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// retail 0x0036ED4C, 101 bytes. Gap between aiFollowWaypointPathExact and aiForceAttackObject in this TU.
// BFME1 donor AICommandInterfaceFollowPathCommands.cpp aiFollowWaypointPathAsTeam at AICMD 0x07
// plus m_waypoint at +0x2C plus slot-0 aiDoCommand. Class proven by caller at 0x0036FB45
// via lea ecx,[eax+0x20] with waypoint plus source.
// Callers at 0x0036FB45 and 0x0036FBB3.
void AICommandInterface::aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_FOLLOW_WAYPOINT_PATH_AS_TEAM, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// retail 0x0036EDB1, 101 bytes. Gap between aiFollowWaypointPathAsTeam and aiForceAttackObject in this TU.
// BFME1 donor AICommandInterfaceFollowPathCommands.cpp aiBfmeCommand33 at AICMD 0x33
// plus m_waypoint at +0x2C plus slot-0 aiDoCommand. Class proven by caller at 0x0036FBF1
// via lea ecx,[eax+0x20] with waypoint plus source.
// Caller at 0x0036FBF1.
void AICommandInterface::aiBfmeCommand33(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_33, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// ?aiAttackArea@AICommandInterface@@QAEXPBVPolygonTrigger@@W4CommandSourceType@@@Z, retail 0x0036F136, 101 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceAttackCommands.cpp
// aiAttackArea at AICMD 0x23 plus m_polygon at +0x30 plus slot-0 aiDoCommand.
// BFME2 same id 0x23 plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x00370543 plus ScriptActions doNamedAttackArea at 0x003C83A1 and doNamedAttackAreaForSeconds at 0x003C83FD.
void AICommandInterface::aiAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_ATTACK_AREA, cmdSource);
	parms.m_polygon = areaToGuard;
	aiDoCommand(&parms);
}

// ?aiAttackTeam@AICommandInterface@@QAEXPBVTeam@@HW4CommandSourceType@@@Z, retail 0x0036F0C8, 110 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceAttackCommands.cpp
// aiAttackTeam at AICMD 0x0D plus m_team at +0x1C plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// BFME2 same id 0x0D plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x0036FF63 plus ScriptActions doNamedAttackTeam at 0x003C8476.
void AICommandInterface::aiAttackTeam(const Team *team, Int maxShotsToFire, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_ATTACK_TEAM, cmdSource);
	parms.m_team = team;
	parms.m_intValue = maxShotsToFire;
	aiDoCommand(&parms);
}

// ?aiEvacuate@AICommandInterface@@QAEX_NW4CommandSourceType@@@Z, retail 0x002AE6B3, 106 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceMovementOrders.cpp
// aiEvacuate at AICMD 0x1B plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// BFME2 same id 0x1B plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Caller at 0x003C86F1 in ScriptActions::doNamedExitAll plus 5 more.
inline void AICommandInterface::aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_EVACUATE, cmdSource);
	if (exposeStealthUnits)
		parms.m_intValue = 1;
	else
		parms.m_intValue = 0;
	aiDoCommand(&parms);
}

// ?aiGuardPosition@AICommandInterface@@QAEXPBUCoord3D@@W4GuardMode@@W4CommandSourceType@@@Z, retail 0x0036F46A, 117 bytes.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameLogic/AI/AICommandInterfaceGuardCommands.cpp
// aiGuardPosition at AICMD 0x1E plus m_pos at +0x08 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// BFME2 same id 0x1E plus the 0xC0 block via opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x003703FF 0x003C88C0 0x003C894B 0x003C89C7 0x003C92E6 0x003C93CB.
inline void AICommandInterface::aiGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_GUARD_POSITION, cmdSource);
	parms.m_pos = *position;
	parms.m_intValue = guardMode;
	aiDoCommand(&parms);
}

// ?rva0045003E@AICommandInterface@@QAEXHW4CommandSourceType@@@Z, retail 0x0045003E, 101 bytes.
// Same 101B single-store shape as aiFaceObject in this TU: AICMD 0x31 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Class proven by callers at 0x00450575 and 0x0045059F via lea ecx,[eax+0x20] from Object+0x258 (AICommandInterface subobject) with source 2.
// Callers pass ModuleData ints at +0x28 and +0x90/0x94; landing unblocks 14 functions (2 become ready).
void AICommandInterface::rva0045003E(Int value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x31, cmdSource);
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

void AICommandInterface::aiTightenToPosition(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_TIGHTEN_TO_POSITION, cmdSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiMoveToAndEvacuate(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_MOVE_TO_POSITION_AND_EVACUATE, cmdSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiMoveToAndEvacuateAndExit(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_MOVE_TO_POSITION_AND_EVACUATE_AND_EXIT, cmdSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

void AICommandInterface::aiFollowPathAppend(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms(AICMD_BFME_35, cmdSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

// ?rva0036F400@AICommandInterface@@QAEXPBVRva003427DD@@W4CommandSourceType@@@Z, retail 0x0036F400, 106 bytes.
// Gap between aiExit and aiGuardPosition in this TU: AICMD 0x1D plus m_3C at +0x3C via rowed 0x003427DD copy plus slot-0 aiDoCommand.
// Class proven by caller at 0x003703BE via lea ecx,[eax+0x20] (AICommandInterface subobject); callers forward (info, source).
void AICommandInterface::rva0036F400(const Rva003427DD *info, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x1D, cmdSource);
	parms.m_3C = *info;
	aiDoCommand(&parms);
}

// ?rva0036F19B@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0036F19B, 101 bytes.
// Same 101B object shape as rva0026C3AC in this TU: AICMD 0x13 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x003700E5 via mov eax [eax+0x258] plus lea ecx [eax+0x20] (AICommandInterface subobject).
void AICommandInterface::rva0036F19B(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x13, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0036F200@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0036F200, 101 bytes.
// Same 101B object shape: AICMD 0x14 plus m_obj at +0x14 plus slot-0 aiDoCommand.
// Class proven by caller at 0x0037011B via AIUpdate+0x258 plus 0x20 pattern.
void AICommandInterface::rva0036F200(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x14, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0036F265@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0036F265, 101 bytes.
// Same 101B object shape: AICMD 0x15 plus m_obj at +0x14 plus slot-0 aiDoCommand.
void AICommandInterface::rva0036F265(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x15, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0036F2CA@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z, retail 0x0036F2CA, 101 bytes.
// Same 101B object shape: AICMD 0x16 plus m_obj at +0x14 plus slot-0 aiDoCommand.
void AICommandInterface::rva0036F2CA(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x16, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?aiHarvest@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z, retail 0x0036F32F, 108 bytes.
// Same 108B position shape as aiTightenToPosition in this TU: AICMD 0x19 plus m_pos at +0x08 plus slot-0 aiDoCommand.
// Class proven by gap between rva0036F2CA and aiExit plus same TU flags; callers at 0x00370272 0x00494767 0x004A731D.
void AICommandInterface::aiHarvest(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x19, cmdSource);
	parms.m_pos = *position;
	aiDoCommand(&parms);
}

// ?rva0036F4DF@AICommandInterface@@QAEXPAVObject@@HW4CommandSourceType@@@Z, retail 0x0036F4DF, 110 bytes.
// Same 110B object-plus-int shape as aiForceAttackObject in this TU: AICMD 0x1F plus m_obj at +0x14 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Class proven by gap between aiGuardPosition and rva0036F6A7 plus same TU flags; callers at 0x00370440 0x003C8A0C 0x003C9D01.
void AICommandInterface::rva0036F4DF(Object *target, Int value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x1F, cmdSource);
	parms.m_obj = target;
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

// ?rva0036F54D@AICommandInterface@@QAEXPBVTeam@@HW4CommandSourceType@@@Z, retail 0x0036F54D, 110 bytes.
// Same 110B team-plus-int shape as aiAttackTeam in this TU: AICMD 0x20 plus m_team at +0x1C plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Class proven by gap between rva0036F4DF and rva0036F6A7 plus same TU flags; caller at 0x00370481.
void AICommandInterface::rva0036F54D(const Team *team, Int value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x20, cmdSource);
	parms.m_team = team;
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

// ?rva0036F5BB@AICommandInterface@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@@Z, retail 0x0036F5BB, 110 bytes.
// Same 110B polygon-plus-int shape: AICMD 0x21 plus m_polygon at +0x30 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Class proven by gap between rva0036F54D and rva0036F6A7 plus same TU flags; callers at 0x003704C2 0x003C8A8A.
void AICommandInterface::rva0036F5BB(const PolygonTrigger *area, Int value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x21, cmdSource);
	parms.m_polygon = area;
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

// ?aiGuardAreaFromPosition@AICommandInterface@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@PBUCoord3D@@@Z, retail 0x0036F629, 126 bytes.
// Same TU polygon-plus-int-plus-pos shape: AICMD 0x44 plus m_polygon at +0x30 plus m_intValue at +0x34 plus m_pos at +0x08 plus slot-0 aiDoCommand.
// Class proven by gap between rva0036F5BB and rva0036F6A7 plus same TU flags; callers at 0x00370505 0x003C8A7E forward 4 args.
void AICommandInterface::aiGuardAreaFromPosition(const PolygonTrigger *area, Int value, CommandSourceType cmdSource, const Coord3D *pos)
{
	AICommandParms parms((AICommandType)0x44, cmdSource);
	parms.m_polygon = area;
	parms.m_intValue = value;
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

// ?rva0036F6A7@AICommandInterface@@QAEXMW4CommandSourceType@@@Z, retail 0x0036F6A7, 105 bytes.
// Same TU single-store shape with float: AICMD 0x50 plus m_float38 at +0x38 plus slot-0 aiDoCommand.
// Class proven by caller at 0x0037077B via lea ecx [edi+0x20] from AIUpdate+0x258 with ACos float plus source.
void AICommandInterface::rva0036F6A7(float value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x50, cmdSource);
	parms.m_float38 = value;
	aiDoCommand(&parms);
}

// ?aiMoveToPositionAndFaceDirection@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@M@Z @0x0036E906 121B
// Evidence: AICMD 0x4E plus m_pos at +0x08 plus m_float38 at +0x38 plus slot-0 aiDoCommand.
// Same TU pos-plus-float shape (aiGuardPosition pos-first order); class proven by slot-0
// aiDoCommand virtual call plus opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x00372ABF 0x00379946 0x00547F2B.
void AICommandInterface::aiMoveToPositionAndFaceDirection(const Coord3D *position, CommandSourceType cmdSource, float value)
{
	AICommandParms parms((AICommandType)0x4E, cmdSource);
	parms.m_pos = *position;
	parms.m_float38 = value;
	aiDoCommand(&parms);
}

// ?aiAttackMoveToPositionAndFaceDirection@AICommandInterface@@QAEXPBUCoord3D@@HW4CommandSourceType@@M@Z @0x0036E97F 130B
// Evidence: AICMD 0x51 plus m_pos at +0x08 plus m_intValue at +0x34 plus m_float38 at +0x38
// plus slot-0 aiDoCommand. Same TU pos-first order; class proven by slot-0 aiDoCommand
// plus opaque 0x351BD0 ctor plus inline free at 0x30830.
// Callers at 0x00372AA5 0x00547F23.
void AICommandInterface::aiAttackMoveToPositionAndFaceDirection(const Coord3D *position, Int value, CommandSourceType cmdSource, float floatValue)
{
	AICommandParms parms((AICommandType)0x51, cmdSource);
	parms.m_pos = *position;
	parms.m_intValue = value;
	parms.m_float38 = floatValue;
	aiDoCommand(&parms);
}

// ?rva003C77EE@AICommandInterface@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z retail 0x003C77EE 101B
// Gap between aiFacePosition and aiWanderInPlace in this TU: AICMD 0x2B plus m_waypoint at +0x2C plus slot-0 aiDoCommand.
// Same 101B waypoint shape as aiFollowWaypointPath family in this TU.
void AICommandInterface::rva003C77EE(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x2B, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// ?rva003C76B8@AICommandInterface@@QAEXHW4CommandSourceType@@@Z retail 0x003C76B8 101B
// Gap between rva003C7653 and aiFaceObject in this TU: AICMD 0x37 plus m_intValue at +0x34 plus slot-0 aiDoCommand.
// Same 101B single-int shape as rva0045003E in this TU.
void AICommandInterface::rva003C76B8(Int value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x37, cmdSource);
	parms.m_intValue = value;
	aiDoCommand(&parms);
}

// ?rva003C78AF@AICommandInterface@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z @0x003C78AF 101B
// Evidence: gap 0x003C7853+92=0x003C78AF in this TU; AICMD 0x2D plus m_waypoint at +0x2C plus slot-0 aiDoCommand.
// Same 101B waypoint shape as rva003C77EE; caller at 0x003C8C54 via lea ecx [esi+0x20] with waypoint plus source 1.
void AICommandInterface::rva003C78AF(const Waypoint *waypoint, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x2D, cmdSource);
	parms.m_waypoint = waypoint;
	aiDoCommand(&parms);
}

// ?aiAttackMoveToPositionAmphibious@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x003C75DD 118B
// Evidence: AICMD 0x52 plus m_pos at +0x08 plus m_intValue 1 at +0x34 plus slot-0 aiDoCommand.
// Caller at 0x003C7BA0 via lea ecx [edi+0x20] with coord plus source 1; next row rva003C7653 in this TU.
void AICommandInterface::aiAttackMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x52, cmdSource);
	parms.m_pos = *position;
	parms.m_intValue = 1;
	aiDoCommand(&parms);
}

// ?aiMoveToPositionAmphibious@AICommandInterface@@QAEXPBUCoord3D@@W4CommandSourceType@@@Z @0x0036EA01 115B
// Evidence: AICMD 0x52 plus m_pos at +0x08 plus m_intValue 0 at +0x34 plus slot-0 aiDoCommand.
// Same shape as aiAttackMoveToPositionAmphibious in this TU (118B with mov [ebp-0x98],1); the 3B delta is the
// /O1 and [ebp-0x98],0 zero encoding. Caller at 0x003C7ADD via lea ecx [edi+0x20]
// (AICommandInterface subobject of AIUpdateInterface) with coord plus source 1.
void AICommandInterface::aiMoveToPositionAmphibious(const Coord3D *position, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x52, cmdSource);
	parms.m_pos = *position;
	parms.m_intValue = 0;
	aiDoCommand(&parms);
}

// ?rva0037379B@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z @0x0037379B 101B:
// Same 101B object shape as rva0026C3AC rva0026C486 rva0026C347 in this TU:
// AICMD 0x3E plus m_obj at +0x14 plus slot-0 aiDoCommand plus inline free 0x30830.
// Callers 6 unclaimed; landing unblocks 3.
void AICommandInterface::rva0037379B(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x3E, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0044FFD9@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z @0x0044FFD9 101B:
// Same 101B object shape as rva0037379B in this TU:
// AICMD 0x48 plus m_obj at +0x14 plus slot-0 aiDoCommand plus inline free 0x30830.
// Callers 0x00450D01 0x004519C0; landing unblocks 2.
void AICommandInterface::rva0044FFD9(Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x48, cmdSource);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?aiMoveToPositionSA@AICommandInterface@@QAEXPBUCoord3D@@H@Z @0x0044FF6D 108B:
// Same 108B position shape as aiFacePosition in this TU:
// AICMD 0x47 (BFME1 aiFacePosition id) plus m_pos at +0x08 plus slot-0 aiDoCommand.
// Callers 0x00450C92 0x00450D82.
void AICommandInterface::aiMoveToPositionSA(const Coord3D *pos, Int cmdSource)
{
	AICommandParms parms((AICommandType)0x47, (CommandSourceType)cmdSource);
	parms.m_pos = *pos;
	aiDoCommand(&parms);
}

// ?rva0036EE16@AICommandInterface@@QAEXPBVRva0035149F@@PAVObject@@W4CommandSourceType@@@Z @0x0036EE16 115B
// Gap between aiBfmeCommand33 0x0036EDB1 and aiFollowPathAppend 0x0036EF89 in this TU.
// AICMD 0x09 plus coord-vector at +0x20 via rowed 0x0035149F copy plus m_obj at +0x14
// plus slot-0 aiDoCommand plus inline free at 0x30830. Class proven by gap plus same TU flags.
// Callers 7 unclaimed; landing unblocks 5.
void AICommandInterface::rva0036EE16(const Rva0035149F *info, Object *target, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)9, cmdSource);
	((Rva0035149F *)&parms.m_coordsStart)->rva0035149F(*info);
	parms.m_obj = target;
	aiDoCommand(&parms);
}

// ?rva0036EE89@AICommandInterface@@QAEXPBVRva0035149F@@PAVObject@@MW4CommandSourceType@@@Z @0x0036EE89 128B
// Gap between rva0036EE16 0x0036EE16 and aiFollowPathAppend 0x0036EF89 in this TU.
// AICMD 0x24 plus coord-vector at +0x20 via rowed 0x0035149F copy plus m_obj at +0x14
// plus m_pos.x at +0x08 via movss plus slot-0 aiDoCommand plus inline free at 0x30830.
// Class proven by gap plus same TU flags. Caller at 0x00371AA6.
void AICommandInterface::rva0036EE89(const Rva0035149F *info, Object *target, float value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x24, cmdSource);
	((Rva0035149F *)&parms.m_coordsStart)->rva0035149F(*info);
	parms.m_obj = target;
	parms.m_pos.x = value;
	aiDoCommand(&parms);
}

// ?rva0036EF09@AICommandInterface@@QAEXPBVRva0035149F@@PAVObject@@MW4CommandSourceType@@@Z @0x0036EF09 128B
// Gap between rva0036EE89 0x0036EE89 and aiFollowPathAppend 0x0036EF89 in this TU.
// Same 128B shape as rva0036EE89: AICMD 0x25 plus coord-vector plus m_obj plus m_pos.x plus slot-0.
// Class proven by gap plus same TU flags. Callers at 0x00371A6E 0x00465685.
void AICommandInterface::rva0036EF09(const Rva0035149F *info, Object *target, float value, CommandSourceType cmdSource)
{
	AICommandParms parms((AICommandType)0x25, cmdSource);
	((Rva0035149F *)&parms.m_coordsStart)->rva0035149F(*info);
	parms.m_obj = target;
	parms.m_pos.x = value;
	aiDoCommand(&parms);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_0)(CommandSourceType cmdSource) = &AICommandInterface::aiIdle;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_1)(CommandSourceType cmdSource) = &AICommandInterface::aiHunt;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_2)(Object *victim, Int maxShotsToFire, CommandSourceType cmdSource) = &AICommandInterface::aiForceAttackObject;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_3)(const Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource) = &AICommandInterface::aiAttackPosition;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_4)(Object *objectToExit, CommandSourceType cmdSource) = &AICommandInterface::aiExit;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_5)(bool exposeStealthUnits, CommandSourceType cmdSource) = &AICommandInterface::aiEvacuate;
void (AICommandInterface::*_bfmeInlineAnchor_AICommandInterfaceAttackCommands_6)(const Coord3D *position, GuardMode guardMode, CommandSourceType cmdSource) = &AICommandInterface::aiGuardPosition;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?aiFaceObject@AICommandInterface@@QAEXPAVObject@@H@Z=?aiFaceObject@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z")
