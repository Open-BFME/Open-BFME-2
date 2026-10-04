// cl: /O1 /DNDEBUG /MD
//
// Bodies ported from Open-BFME-1's GameEngine/Source/GameLogic/Object/Update/A
// IUpdateInterfacePrivateCommands.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// AIUpdateInterface::bfmePrivateCommand39 0x0026BE86 (96B),
// AIUpdateInterface::privateMoveToObject 0x0026472F (70B),
// AIUpdateInterface::bfmePrivateCommand1B 0x00267DAD (68B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
//
// The AIUpdateInterface private command handlers that share one shape: guard
// the object, clear the state machine, record the command source, and set a
// state. These are the bodies AICommandInterface::aiDoCommand dispatches to.
//
//   privateExitInstantly         0x00271800  state 0x26
//   bfmePrivateCommand01         0x00273400  state 0x01
//   bfmePrivateCommand38         0x002734B0  state 0x38
//   privateMoveToPosition        0x00278280  state 0x01
//   bfmePrivateCommand3F         0x00278390  state 0x3F
//   bfmePrivateCommand25         0x00278430  state 0x25
//   bfmePrivateCommand1C         0x002784A0  state 0x1C
//   bfmePrivateCommand1D         0x00278540  state 0x1D
//   bfmePrivateCommand1E         0x002785E0  state 0x1E
//   bfmePrivateCommand37         0x00278680  state 0x37
//   bfmePrivateCommand1B         0x002787D0  state 0x1B
//   privateAttackMoveToPosition  0x00279050  state 0x21
//   privateHunt                  0x00279100  state 0x11
//   privateFaceObject            0x00279180  state 0x1F
//   privateGetRepaired           0x00279360  state 0x18
//   privateGuardObject           0x002793C0  state 0x10
//   privateGuardPosition         0x00279450  state 0x10
//   privateGuardAreaFromPosition 0x002794E0  state 0x10
//   privateGuardRetaliate        0x002795D0  state 0x3E
//
// plus one query that belongs with them because it reads the same object:
//
//   bfmeCurrentWeaponTemplateFlag4  0x00278790, 44 bytes
//
// They sat in nineteen files, each re-declaring AIUpdateInterface out to
// whatever field its own body reached, so the class existed in nineteen partial
// versions that had to agree and nothing checked that they did. Declared once
// here, the fields line up with upstream's own order at +0x48 onward
// (m_lastCommandSource, m_guardMode, m_guardTargetType[2], the guard location,
// m_objectToGuard) -- which is the confirmation no single file could give. The
// same was true of StateMachine: six of the files declared 9 virtual slots and
// the rest 15, so in those six the slot at vtable+0x38 did not exist at all.
//
// Two things only the whole set can say.
//
// The state machine slot at vtable+0x38 has one meaning. Three of the merged
// files reached it through a placeholder -- `slot38(void *)` in two of them and
// `slot38(int)` in the third -- while privateExitInstantly and
// privateGuardRetaliate, which never sat beside them, called it
// setGoalObject(const Object *). It is the goal object: bfmePrivateCommand01
// and 38 set it from their argument and then read the position out of that same
// object at +0x38 for the voice response, and bfmePrivateCommand1B clears it by
// passing null.
//
// bfmePrivateCommand01 and privateMoveToPosition enter the SAME state. Both
// call setState(1); privateMoveToPosition takes a position and prepares the
// state action with it, bfmePrivateCommand01 takes an object, makes it the goal
// and takes the position from it. They are the position and object forms of one
// order, and the two files named the constant differently -- BFME_AI_MOVE_TO
// against BFME_AI_STATE_01 -- so nothing connected them. The same happened to
// the byte at +0x32B, which bfmePrivateCommand01 called m_flag32b and
// privateAttackMoveToPosition called m_isAiDead; both bodies read it as the
// same early-out.
//
// privateMoveToPosition's BfmeVirtualSlots<96> base is what pins isIdle() to
// its retail vtable slot. The private commands are declared after it and none
// of them dispatches through this vtable, so their own slot numbers are not
// evidence of anything.
//
// That 96 is corroborated from the other side of the call, by a different route.
// This TU derives it from INSIDE the class: privateMoveToPosition calls its own
// isIdle() through this, so isIdle has to be the first own virtual behind a
// 96-slot base. AIGroupStatePredicates.cpp derives it from OUTSIDE:
// AIGroup::isIdle calls ai->isIdle() through an AIUpdateInterface pointer and
// reproduces retail's dispatch only with 96 declared slots ahead of the method,
// which it writes out as a padding run rather than a template base. Two bodies,
// two call directions, two constructions, one number.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"

enum CanEnterType
{
	CHECK_CAPACITY = 0,
	DONT_CHECK_CAPACITY = 1,
	COMBATDROP_INTO = 2
};

enum KindOfType
{
	KINDOF_PROJECTILE = 0x19
};

// Status bit 0x26 is tested by privateHunt and bfmePrivateCommand37; its
// name is not evidenced.
enum ObjectStatusTypes
{
	BFME_OBJECT_STATUS_26 = 0x26
};

enum GuardMode
{
	GUARDMODE_NORMAL = 0
};

enum GuardTargetType
{
	GUARDTARGET_OBJECT = 1,
	GUARDTARGET_LOCATION = 2,
	GUARDTARGET_AREA = 3,
	GUARDTARGET_NONE = 4
};

enum StateID
{
	BFME_AI_MOVE_TO = 0x01,
	BFME_AI_GUARD = 0x10,
	BFME_AI_HUNT = 0x11,
	BFME_AI_GET_REPAIRED = 0x18,
	BFME_AI_STATE_1B = 0x1B,
	BFME_AI_STATE_1C = 0x1C,
	BFME_AI_STATE_1D = 0x1D,
	BFME_AI_STATE_1E = 0x1E,
	BFME_AI_FACE_OBJECT = 0x1F,
	BFME_AI_ATTACK_MOVE_TO = 0x21,
	BFME_AI_STATE_25 = 0x25,
	BFME_AI_EXIT_INSTANTLY = 0x26,
	BFME_AI_STATE_37 = 0x37,
	BFME_AI_STATE_38 = 0x38,
	BFME_AI_GUARD_RETALIATE = 0x3E,
	BFME_AI_STATE_3F = 0x3F
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x, y, z;
};

class WeaponSetFlags
{
public:
	Bool test(Int type) const { return (m_words[0] & (1U << type)) != 0; }

	UnsignedInt m_words[1];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponTemplate
{
public:
	unsigned char m_unmodelled_00[0x4D4];
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
	unsigned char m_bit4 : 1;					// WeaponTemplate+0x4D4 bit 4
};

// The weapon handle bfmeCurrentWeaponTemplateFlag4 asks the object for. It is
// the same question privateAttackMoveToPosition and privateGuardRetaliate ask
// through Object::getCurrentWeapon -- both take a null slot argument and both
// come back with the object's current weapon -- but the two calls are pinned
// separately, ?bfmeAskCLE@BfmeSubCLE@@ through ILT 0x00009C41 and
// ?getCurrentWeapon@Object@@ through ILT 0x00031A7F to body 0x001BE230. Until
// one caller settles whether those two thunks reach the same body, both
// spellings stay, and this one is reached by a cast the way the other
// address-named helpers in this TU are.
class BfmeXCLE
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }

private:
	void *m_vtable;
	const WeaponTemplate *m_template;			// +0x04
};

class BfmeSubCLE
{
public:
	BfmeXCLE *bfmeAskCLE(int);					///< ILT 0x00009C41
};

class Weapon
{
public:
	unsigned char m_unmodelled_00[0x20];
	Int m_shotsFired;
	unsigned char m_unmodelled_24[0x34 - 0x24];
	Int m_maxShotCount;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	// BFME2 keeps the KindOf bitset at +0x108 (bit n in byte 0x108 + n/8):
	// privateHunt tests KINDOF_PROJECTILE (0x19) as bit 1 of byte +0x10B, the
	// same byte layout Rva00290EFEGetGhostObject.cpp and
	// Object_isAbleToAttack.cpp read. Retail folds the whole Thing -> template
	// -> bitset chain to that one byte test; at /O1 the stand-in needs
	// __forceinline to do the same.
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_unmodelled_08[0x108 - 8];
	unsigned char m_kindof[16];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }

	virtual void slot00();
	ThingTemplate *m_template;
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h
class HordeContainInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void exitObject(Object *, CommandSourceType) = 0;
};

class HordeContainEnterInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void enterObject(Object *, CommandSourceType) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

class BFMEActionManager
{
public:
	Bool canEnterObject(const Object *, const Object *, CommandSourceType,
		CanEnterType, Bool *);
	// Body 0x000C4080 (113 B, ret 0xC), reached through ILT 0x00012B57. A
	// three-argument object/object/source test distinct from the five-argument
	// canEnterObject above; its name is not evidenced, so it keeps the address.
	Bool rva000C4080(const Object *, const Object *, CommandSourceType);
	Bool canGetHealedAt(const Object *, const Object *, CommandSourceType);	///< 0x0041BE93
	Bool canGetRepairedAt(const Object *, const Object *, CommandSourceType);	///< 0x0041BBE4
};

extern BFMEActionManager *TheActionManager;

// ZH's AIUpdateInterface derives from AICommandInterface at +0x20. The two
// order issuers here are matched under address names: 0x0026C347 builds
// AICMD 0x17 (the enter order, aiEnter) and 0x0026C3AC AICMD 0x18 (the dock
// order, aiDock; command 0x18 dispatches to the matched privateDock).
class AICommandInterface
{
public:
	void rva0026C347(Object *obj, CommandSourceType commandSource);
	void rva0026C3AC(Object *obj, CommandSourceType commandSource);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Bool isMobile() const;
	Bool testStatus(ObjectStatusTypes bit) const;	///< 0x0004E536
	Coord3D getPosition() const;
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);
	Bool rva002907A1();

	unsigned char m_unmodelled_08[0x74 - 8];
	UnsignedInt m_id;							// +0x74
	unsigned char m_unmodelled_78[0x90 - 0x78];
	UnsignedInt m_status;						// +0x90
	unsigned char m_flags;						// +0x94
	unsigned char m_unmodelled_95[0x1FC - 0x95];
	ContainModuleInterface *m_contain;			// +0x1FC
	unsigned char m_unmodelled_200[0x214 - 0x200];
	Object *m_containedBy;						// +0x214
	unsigned char m_unmodelled_218[0x274 - 0x218];
	Object *m_bfmeObject274;					// +0x274, bfmePrivateCommand3E's fallback target
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void clear();
	virtual void slot18();
	virtual void slot1C();
	virtual void setState(StateID state);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
	void setGoalPosition(const Coord3D *pos);	///< pinned 0x00262224
};

// The StateMachine member vector of positions at +0x3C (Zero Hour's
// m_goalPath); its assignment forwarder 0x00351759 is address-named
// (Rva0035149F.cpp), so the path commands reach it by a cast.
class Rva0035149F
{
	Coord3D *m_start, *m_finish, *m_end;
};
class Rva00351759
{
public:
	Rva0035149F &rva00351759(const Rva0035149F &other);
};

class Rva001B5CC0
{
public:
	void set(const char *other);
};

class Rva002BC470StateAction
{
public:
	void prepare(void *first, void *second);
};

class Rva00263910
{
public:
	void rva00265667(const Coord3D *pos, int flag);
};

class Rva0016AD50
{
public:
	void bfmeSnapshot();
};

#pragma comment(linker, "/alternatename:?bfmeSnapshot@Rva0016AD50@@QAEXXZ=?j_0002d308@@YAXXZ")

class Rva0016AD90
{
public:
	void setTemporaryState(StateID state, int frameCount);
};

#pragma comment(linker, "/alternatename:?setTemporaryState@Rva0016AD90@@QAEXW4StateID@@H@Z=?j_00044319@@YAXXZ")

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeVirtualSlots<96>
{
public:
	virtual Bool isIdle() const = 0;
	virtual Bool bfmeCurrentWeaponTemplateFlag4() const;

	void setGoalPositionClipped(const Coord3D *position, CommandSourceType commandSource);
	void rva00267D65(const Coord3D *pos, CommandSourceType commandSource);

protected:
	virtual void privateExitInstantly(Object *objectToExit, CommandSourceType commandSource);
	virtual void privateEnter(Object *object, CommandSourceType commandSource);
	virtual void bfmePrivateCommand01(void *first, CommandSourceType commandSource);
	virtual void bfmePrivateCommand38(void *first, CommandSourceType commandSource);
	virtual void privateMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3F(void *first, CommandSourceType commandSource);
	virtual void bfmePrivateCommand25(void *first, CommandSourceType commandSource);
	virtual void bfmePrivateCommand1C(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand1D(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand1E(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand37(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand1B(void *first, CommandSourceType commandSource);
	void bfmePrivateCommand31(Object *object, CommandSourceType commandSource);
	virtual void bfmePrivateCommand39(Object *victim, CommandSourceType commandSource);
	virtual void privateAttackMoveToPosition(const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource);
	virtual void privateHunt(CommandSourceType commandSource);
	virtual void privateFaceObject(Object *target, CommandSourceType commandSource);
	virtual void privateGetRepaired(Object *repairDepot, CommandSourceType commandSource);
	virtual void privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType commandSource);
	virtual void privateGuardPosition(const Coord3D *position, GuardMode guardMode, CommandSourceType commandSource);
	virtual void privateGuardAreaFromPosition(const PolygonTrigger *area, GuardMode guardMode,
		CommandSourceType commandSource, const Coord3D *position);
	virtual void privateGuardRetaliate(Object *victim, const Coord3D *position, Int maxShotsToFire, CommandSourceType commandSource);
	// Declared last so no slot above moves; nothing in this TU dispatches it.
	virtual void privateMoveToObject(Object *obj, CommandSourceType commandSource);
	// BFME2 aiDoCommand handlers named by their command id (see the bodies).
	virtual void privateGetHealed(Object *healDepot, CommandSourceType commandSource);
	virtual void bfmePrivateCommand37(Int value, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3D(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3E(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4A(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4B(Object *obj, const Coord3D *pos, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4C(Object *obj, const Rva0035149F *path, CommandSourceType commandSource);
	virtual void bfmePrivateCommand4D(Object *obj, const Rva0035149F *path, CommandSourceType commandSource);
	virtual void bfmePrivateCommand53(CommandSourceType commandSource);
	virtual void bfmePrivateCommand54(Object *obj, const Coord3D *pos, CommandSourceType commandSource);

	// Zero Hour's ObjectModule accessor. privateMoveToObject reads the owner
	// through it, and that is not cosmetic: see the body.
	Object *getObject() const { return m_object; }

	void playMoveVoiceResponse(const Coord3D *position);
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);
	void setCurrentVictim(const Object *victim);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;

	// Upstream's guard fields, in upstream's order. The +0x4C word also
	// carries bfmePrivateCommand37's value, and command 0x20 (banked) keeps a
	// team word at +0x68.
	GuardMode m_guardMode;						// +0x4C
	GuardTargetType m_guardTargetType[2];		// +0x50, a two-deep stack
	Coord3D m_locationToGuard;					// +0x58, privateGuardPosition
	UnsignedInt m_objectToGuard;				// +0x64
	UnsignedInt m_guardExtra;					// +0x68
	const PolygonTrigger *m_areaToGuard;		// +0x6C, privateAttackArea
	unsigned char m_unmodelled_70[0x16C - 0x70];
	int m_blockedFrames;						// +0x16C
	unsigned char m_unmodelled_170[0x1CC - 0x170];
	Rva001B5CC0 *m_curLocomotor;				// +0x1CC
	unsigned char m_unmodelled_1D0[0x325 - 0x1D0];
	unsigned char m_isBlocked;					// +0x325
	unsigned char m_isBlockedAndStuck;			// +0x326
	unsigned char m_unmodelled_327[0x32B - 0x327];
	unsigned char m_isAiDead;					// +0x32B
	unsigned char m_unmodelled_32C[0x3B8 - 0x32C];
	unsigned char m_bfmeByte3B8;				// +0x3B8, cleared by privateFaceObject
};

// Retail 0x00271630. BFME gates Zero Hour's move-to-object order on a
// three-argument ActionManager test, then drives the state machine as
// upstream does. The owner is read through getObject(), as upstream writes it:
// reading m_object directly compiles to the same load but hands the three
// vtable temporaries EDX, EAX, EDX where retail has EAX, EDX, EAX (MSVC 7.1
// assigns scratch registers round-robin and the inlined accessor's return
// value is one more step; docs/shape_levers.md, "Scratch registers rotate").
void AIUpdateInterface::privateMoveToObject(Object *obj, CommandSourceType commandSource)
{
	if (!TheActionManager->rva000C4080(getObject(), obj, commandSource))
		return;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x3c);
}


// Retail 0x00267D65 72B slot 70. Guarded by Object::rva002907A1 then clear
// plus Rva00263910 goal helper with commandSource as flag plus blocked
// counters plus state 0x25. Layout matches Rva00263910 at +8/+0x30.
void AIUpdateInterface::rva00267D65(const Coord3D *pos, CommandSourceType commandSource)
{
	if (!m_object->rva002907A1())
		return;
	m_stateMachine->clear();
	reinterpret_cast<Rva00263910 *>(this)->rva00265667(pos, (int)commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_25);
}


// Retail 0x002787D0, the shortest of the family: it clears the goal object
// rather than setting one, and skips the locomotor, the blocked counters and
// the voice response.
void AIUpdateInterface::bfmePrivateCommand1B(void *first, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(0);
	reinterpret_cast<Rva002BC470StateAction *>(this)->prepare(first, (void *)commandSource);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1B);
}


// Retail 0x00273730. BFME command 0x39 orders a giant bird to force-attack
// one object with one shot, then answers player and script orders with attack voice.
void AIUpdateInterface::bfmePrivateCommand39(Object *victim, CommandSourceType commandSource)
{
	if (!victim)
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(victim);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x2e);

	Weapon *weapon = m_object->getCurrentWeapon(0);
	if (weapon)
	{
		weapon->m_maxShotCount = 1;
		weapon->m_shotsFired = 0;
	}

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playAttackVoiceResponse(victim);
}


// BFME2 aiDoCommand (0x002673F6) switches on AICommandParms::m_cmd through the
// jump table at VA 0x00667BA6 and calls one AIUpdateInterface vtable slot per
// command, passing m_obj (+0x14), &m_pos (+0x08) or &m_coords (+0x20) and the
// command source. The handlers below are named by that command id, the way
// bfmePrivateCommand39 (command 0x39, slot 35) is; slot numbers are of the
// AIUpdate vtable 0x00C47B98, whose other slots are this class's matched
// privateDock / privateMoveToObject. The state ids are the target's constants.

// Command 0x3D, slot 49, retail 0x002647EF.
void AIUpdateInterface::bfmePrivateCommand3D(Object *obj, CommandSourceType commandSource)
{
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x34);
}

// Command 0x3E, slot 56, retail 0x00264963: with no object given it falls back
// to the owner's object at +0x274, and does nothing when that is null too.
void AIUpdateInterface::bfmePrivateCommand3E(Object *obj, CommandSourceType commandSource)
{
	if (!obj)
	{
		obj = m_object->m_bfmeObject274;
		if (!obj)
			return;
	}
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x35);
}

// Command 0x4A, slot 57, retail 0x002649A3.
void AIUpdateInterface::bfmePrivateCommand4A(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x41);
}

// Command 0x4B, slot 54, retail 0x002648F1.
void AIUpdateInterface::bfmePrivateCommand4B(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x42);
}

// Command 0x4C, slot 58, retail 0x002649DC.
void AIUpdateInterface::bfmePrivateCommand4C(Object *obj, const Rva0035149F *path, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	reinterpret_cast<Rva00351759 *>(sm)->rva00351759(*path);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x45);
}

// Command 0x4D, slot 55, retail 0x0026492A.
void AIUpdateInterface::bfmePrivateCommand4D(Object *obj, const Rva0035149F *path, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	reinterpret_cast<Rva00351759 *>(sm)->rva00351759(*path);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x44);
}

// Command 0x53, slot 77, retail 0x00264AB2.
void AIUpdateInterface::bfmePrivateCommand53(CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x4a);
}

// Command 0x54, slot 59, retail 0x00264A15.
void AIUpdateInterface::bfmePrivateCommand54(Object *obj, const Coord3D *pos, CommandSourceType commandSource)
{
	StateMachine *sm = m_stateMachine;
	sm->clear();
	sm->setGoalObject(obj);
	sm->setGoalPosition(pos);
	m_lastCommandSource = commandSource;
	sm->setState((StateID)0x4b);
}

// Command 0x12, slot 43, retail 0x002646E9. aiHunt (0x002AE657) issues
// AICMD 0x12; BFME1's privateHunt (mobile, not a projectile, then AI_HUNT,
// state 0x11) plus a BFME2 status-bit guard.
void AIUpdateInterface::privateHunt(CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	if (getObject()->testStatus(BFME_OBJECT_STATUS_26))
		return;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_HUNT);
}

// Command 0x26, slot 69, retail 0x002645B9. aiFaceObject (0x003C771D)
// issues AICMD 0x26; BFME1's privateFaceObject shape, with BFME2's state 0x24
// and one blocked byte at +0x3B8 instead of the two at +0x325.
void AIUpdateInterface::privateFaceObject(Object *target, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(target);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x24);
}

// Command 0x37, slot 62, retail 0x00264CBB: AICommandParms::m_intValue (+0x34)
// is stored at +0x4C before the state machine enters state 0x18.
void AIUpdateInterface::bfmePrivateCommand37(Int value, CommandSourceType commandSource)
{
	Object *obj = getObject();
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;
	m_guardMode = (GuardMode)value;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x18);
}

// Command 0x15 (ZH AICMD_GET_HEALED, one below ZH's numbering as HUNT 0x12
// and DOCK 0x18 are), slot 46, retail 0x0026DD89: the donor body, ending in
// aiEnter.
void AIUpdateInterface::privateGetHealed(Object *healDepot, CommandSourceType commandSource)
{
	if (TheActionManager->canGetHealedAt(getObject(), healDepot, commandSource) == false)
		return;
	reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->rva0026C347(healDepot, commandSource);
}

// Command 0x16 (AICMD_GET_REPAIRED), slot 47, retail 0x0026DDBB: BFME1's
// privateGetRepaired, ending in aiDock.
void AIUpdateInterface::privateGetRepaired(Object *repairDepot, CommandSourceType commandSource)
{
	if (TheActionManager->canGetRepairedAt(getObject(), repairDepot, commandSource) == false)
		return;
	reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20)->rva0026C3AC(repairDepot, commandSource);
}
