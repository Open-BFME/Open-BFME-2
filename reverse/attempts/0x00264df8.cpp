// ?privateGuardAreaFromPosition@AIUpdateInterface@@MAEXPBVPolygonTrigger@@W4GuardMode@@W4CommandSourceType@@PBUCoord3D@@@Z
// partial score=0.9507 date=2026-10-06
// ?privateGuardAreaFromPosition@AIUpdateInterface@@MAEXPBVPolygonTrigger@@W4GuardMode@@W4CommandSourceType@@PBUCoord3D@@@Z
// partial score=0.96 date=2026-10-05
// ?privateGuardAreaFromPosition@AIUpdateInterface@@MAEXPBVPolygonTrigger@@W4GuardMode@@W4CommandSourceType@@PBUCoord3D@@@Z
// cl: /O1 /DNDEBUG /MD /Ireference/open-bfme-1/game/GameEngine/Source/GameLogic
//
// AIUpdateInterface's private command handlers: the bodies BFME2's
// AICommandInterface::aiDoCommand (0x002673F6) reaches through its jump table
// at VA 0x00667BA6, one AIUpdate vtable slot per AICommandParms::m_cmd. They
// are named after real Zero Hour handlers where the body is one, and otherwise
// bfmePrivateCommandXX after the BFME2 command id XX that dispatches to them.
// BFME1-era names numbered by state id or by BFME1's command table are not
// used (BFME1's bfmePrivateCommand1B is command 0x02 here). Several bodies
// were first ported from Open-BFME-1's AIUpdateInterfacePrivateCommands.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1) and placed by masked whole-.text search; callee addresses are read off
// retail's call sites (reverse/symbols.csv).
//
// Declared once here, the fields line up with upstream's own order at +0x48
// onward (m_lastCommandSource, m_guardMode, m_guardTargetType[2], the guard
// location, m_objectToGuard). The same is true of StateMachine, whose slot at
// vtable+0x38 every handler uses.
//
// The state machine slot at vtable+0x38 is the goal object: the object-order
// handlers set it from their argument and bfmePrivateCommand02 clears it by
// passing null.
//
// The BfmeVirtualSlots<96> base places isIdle() at its retail slot, as
// AIGroupStatePredicates.cpp's AIGroup::isIdle dispatch confirms from outside.
// None of the handlers dispatches through this vtable, so their own
// declaration order is not evidence of their slots; the slots quoted beside
// each body are read from aiDoCommand and vtable 0x00C47B98.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "command_source_type.h"

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
// BFME2 slots, from privateExitInstantly (0x0026488B, +0x84) and the enter
// order handler (0x00264775, +0x80) reaching one interface.
class HordeContainInterface
{
public:
	virtual void slot00() = 0; 	virtual void slot01() = 0;
	virtual void slot02() = 0; 	virtual void slot03() = 0;
	virtual void slot04() = 0; 	virtual void slot05() = 0;
	virtual void slot06() = 0; 	virtual void slot07() = 0;
	virtual void slot08() = 0; 	virtual void slot09() = 0;
	virtual void slot10() = 0; 	virtual void slot11() = 0;
	virtual void slot12() = 0; 	virtual void slot13() = 0;
	virtual void slot14() = 0; 	virtual void slot15() = 0;
	virtual void slot16() = 0; 	virtual void slot17() = 0;
	virtual void slot18() = 0; 	virtual void slot19() = 0;
	virtual void slot20() = 0; 	virtual void slot21() = 0;
	virtual void slot22() = 0; 	virtual void slot23() = 0;
	virtual void slot24() = 0; 	virtual void slot25() = 0;
	virtual void slot26() = 0; 	virtual void slot27() = 0;
	virtual void slot28() = 0; 	virtual void slot29() = 0;
	virtual void slot30() = 0; 
	virtual void slot31() = 0;
	virtual void enterObject(Object *, CommandSourceType) = 0;
	virtual void exitObject(Object *, CommandSourceType) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
// BFME2 slot 31 (+0x7C) hands out the horde interface.
class ContainModuleInterface
{
public:
	virtual void slot00() = 0; 	virtual void slot01() = 0;
	virtual void slot02() = 0; 	virtual void slot03() = 0;
	virtual void slot04() = 0; 	virtual void slot05() = 0;
	virtual void slot06() = 0; 	virtual void slot07() = 0;
	virtual void slot08() = 0; 	virtual void slot09() = 0;
	virtual void slot10() = 0; 	virtual void slot11() = 0;
	virtual void slot12() = 0; 	virtual void slot13() = 0;
	virtual void slot14() = 0; 	virtual void slot15() = 0;
	virtual void slot16() = 0; 	virtual void slot17() = 0;
	virtual void slot18() = 0; 	virtual void slot19() = 0;
	virtual void slot20() = 0; 	virtual void slot21() = 0;
	virtual void slot22() = 0; 	virtual void slot23() = 0;
	virtual void slot24() = 0; 	virtual void slot25() = 0;
	virtual void slot26() = 0; 	virtual void slot27() = 0;
	virtual void slot28() = 0; 	virtual void slot29() = 0;
	virtual void slot30() = 0; 
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
	// Thing::getPosition: the cached position the object-order handlers hand
	// to the move voice (the +0x38 operand in their bodies).
	const Coord3D *getPosition() const { return &m_cachedPos; }
	const WeaponSetFlags &getWeaponSetFlags() const;
	Weapon *getCurrentWeapon(WeaponSlotType *wslot);

	unsigned char m_unmodelled_08[0x38 - 8];
	Coord3D m_cachedPos;						// +0x38
	unsigned char m_unmodelled_44[0x74 - 0x44];
	UnsignedInt m_id;							// +0x74
	unsigned char m_unmodelled_78[0x90 - 0x78];
	UnsignedInt m_status;						// +0x90
	unsigned char m_flags;						// +0x94
	unsigned char m_unmodelled_95[0x250 - 0x95];
	ContainModuleInterface *m_contain;			// +0x250 (BFME2; the enter and exit handlers)
	unsigned char m_unmodelled_254[0x274 - 0x254];
	Object *m_containedBy;						// +0x274 (BFME2; privateExitInstantly's getContainedBy fallback)
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

// Locomotor helper 0x001E4147 (matched, Rva001E4147Copy.cpp): copies the
// position at +0x38 of the object it is handed to +0x14 of the locomotor.
struct Rva001E4147Twelve;
// Object's flag word at +0x370, handed out by the matched lea getter
// 0x0028B7AE (DispDwordLeaFieldGetters.cpp); command 0x47 refuses an object
// with bit 8 set.
class Rva0028B7AELeaGetter
{
public:
	void *get() const;
	Bool testBit8() const { return (UnsignedInt)((*(const UnsignedInt *)get() >> 8) & 1); }
};

class Rva001E4147
{
public:
	void rva001E4147(Rva001E4147Twelve *src);
};

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
	virtual void clearGuardTargetType();

	void setGoalPositionClipped(const Coord3D *position, CommandSourceType commandSource);
	void setCurrentVictim(const Object *victim);	///< matched 0x00268D1F

protected:
	virtual void privateExitInstantly(Object *objectToExit, CommandSourceType commandSource);
	virtual void privateEnter(Object *object, CommandSourceType commandSource);
	virtual void privateMoveToPosition(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand01(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand02(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand03(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand04(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand38(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand41(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand3C(Object *obj, CommandSourceType commandSource);
	virtual void bfmePrivateCommand47(const Coord3D *position, CommandSourceType commandSource);
	virtual void bfmePrivateCommand48(Object *obj, CommandSourceType commandSource);
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
	virtual void privateAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType commandSource);
	virtual void privateFacePosition(const Coord3D *position, CommandSourceType commandSource);
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

	void playMoveVoiceResponse(const Coord3D *position);		///< 0x0026B403 (voice message 0x7E7)
	void playAttackVoiceResponse(Object *victim);
	void playAttackVoiceResponse(const Coord3D *position);

	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
	unsigned char m_unmodelled_34[0x48 - 0x34];
	CommandSourceType m_lastCommandSource;

	// Merging the seven files exposed a collision none of them could see:
	// privateGuardObject and privateGuardPosition write the guard mode to
	// +0x4C, and privateGetRepaired writes its repair-depot pointer to the
	// same word. Both stores are byte-verified against retail, so BFME really
	// does reuse this slot; nothing in these bodies says which name it wore,
	// and upstream's field order (m_guardMode here) covers only one of them.
	union
	{
		GuardMode m_guardMode;					// +0x4C, the guard commands
		Object *m_repairDepot;					// +0x4C, privateGetRepaired
	};
	GuardTargetType m_guardTargetType[2];		// +0x50

	// privateGuardAreaFromPosition writes three floats here, which is what
	// turns the guess that +0x58 is upstream's m_locationToGuard into
	// something byte-verified. Note that privateGuardPosition does NOT write
	// it: that body stores only the z word, and it stores it at +0x68, past
	// the end of this member.
	Coord3D m_locationToGuard;					// +0x58

	UnsignedInt m_objectToGuard;				// +0x64
	UnsignedInt m_guardExtra;					// +0x68

	// The second collision this TU exposes. privateFaceObject stores the
	// object it is turning towards at +0x6C; privateGuardAreaFromPosition
	// stores the polygon it is guarding at the same word. Both stores are
	// byte-verified, so BFME reuses this slot the way it reuses +0x4C.
	union
	{
		Object *m_faceObject;					// +0x6C, privateFaceObject
		const PolygonTrigger *m_areaToGuard;	// +0x6C, the area guard
	};
	unsigned char m_unmodelled_70[0x16C - 0x70];
	int m_blockedFrames;						// +0x16C
	unsigned char m_unmodelled_170[0x1F0 - 0x170];
	Rva001E4147 *m_curLocomotor;				// +0x1F0 (BFME2; BFME1 +0x1CC)
	unsigned char m_unmodelled_1F4[0x3B8 - 0x1F4];
	unsigned char m_bfmeByte3B8;				// +0x3B8, cleared with m_blockedFrames
	unsigned char m_unmodelled_3B9[0x3BD - 0x3B9];
	unsigned char m_isAiDead;					// +0x3BD (BFME2; BFME1 +0x32B)
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


// Command 0x02, slot 25, retail 0x00267DAD, the shortest of the position
// family: it clears the goal object rather than setting one, takes the
// clipped goal position, and skips the locomotor, the blocked counters and the
// voice response. BFME1 carried this body as bfmePrivateCommand1B, after its
// state id.
void AIUpdateInterface::bfmePrivateCommand02(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(0);
	setGoalPositionClipped(position, commandSource);
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
		obj = m_object->m_containedBy;
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

// Command 0x1F, slot 64, retail 0x00264D0E: BFME1's privateGuardObject
// (guard target type OBJECT in the free slot, mode at +0x4C, the guarded
// object's id at +0x64, AI_GUARD) behind BFME2's status-bit guard.
void AIUpdateInterface::privateGuardObject(Object *objectToGuard, GuardMode guardMode, CommandSourceType commandSource)
{
	Object *obj = getObject();
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_OBJECT;
	else
		m_guardTargetType[0] = GUARDTARGET_OBJECT;
	m_guardMode = guardMode;
	m_objectToGuard = objectToGuard->m_id;

	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}

// Command 0x27, slot 70, retail 0x00267D65. aiFacePosition (0x003C7782)
// issues AICMD 0x27; ZH's privateFacePosition with BFME2's state 0x25 and
// one blocked byte at +0x3B8.
void AIUpdateInterface::privateFacePosition(const Coord3D *position, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x25);
}

// Command 0x23, slot 68, retail 0x0026C1CE. aiAttackArea (0x0036F136)
// issues AICMD 0x23; BFME1's privateAttackArea (state 0x1F here) plus an
// attack voice at the area's centre for player and script orders.
void AIUpdateInterface::privateAttackArea(const PolygonTrigger *areaToGuard, CommandSourceType commandSource)
{
	if (!getObject()->isMobile())
		return;
	if (getObject()->isKindOf(KINDOF_PROJECTILE))
		return;

	m_areaToGuard = areaToGuard;
	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState((StateID)0x1f);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
	{
		Coord3D pos;
		areaToGuard->getCenterPoint(&pos);
		playAttackVoiceResponse(&pos);
	}
}

// Command 0x1A (ZH AICMD_EXIT_INSTANTLY, one below ZH's numbering), slot 53,
// retail 0x0026488B: BFME1's privateExitInstantly (default to the container
// we are in, state 0x26) without the subdued test, and handing the exit to a
// horde container's interface when there is one.
void AIUpdateInterface::privateExitInstantly(Object *objectToExit, CommandSourceType commandSource)
{
	Object *us = getObject();
	if (!objectToExit)
	{
		objectToExit = us->m_containedBy;
		if (!objectToExit)
			return;
	}

	ContainModuleInterface *contain = us->m_contain;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
		{
			horde->exitObject(objectToExit, commandSource);
			return;
		}
	}

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(objectToExit);
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_EXIT_INSTANTLY);
}

// Retail 0x0026E9AA, AIUpdate vtable 0x00C47B98 slot 124, right after the
// getGuardTargetType slot (123, the m_guardTargetType[1] getter at 0x0009AAA4):
// ZH AIUpdate.h's inline clearGuardTargetType, which shifts the guard target
// stack down and empties the top.
void AIUpdateInterface::clearGuardTargetType()
{
	m_guardTargetType[1] = m_guardTargetType[0];
	m_guardTargetType[0] = GUARDTARGET_NONE;
}

// The move-order family. Each prepares the locomotor with the owner's position
// (0x001E4147), resets the blocked counters, enters its state and answers
// player and script orders with a voice. Command 0x01 takes an object (and is
// gated on the AI-dead byte), the rest a position.

// Command 0x01, slot 15, retail 0x0026B637: move to an object.
void AIUpdateInterface::bfmePrivateCommand01(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_MOVE_TO);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(obj->getPosition());
}

// Command 0x03, slot 19, retail 0x0026B6B2: state 0x1C.
void AIUpdateInterface::bfmePrivateCommand03(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1C);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x04, slot 20, retail 0x0026B720: state 0x1D.
void AIUpdateInterface::bfmePrivateCommand04(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1D);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x38, slot 21, retail 0x0026B78E: state 0x1E.
void AIUpdateInterface::bfmePrivateCommand38(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_1E);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x41, slot 22, retail 0x0026B7FC: state 0x37.
void AIUpdateInterface::bfmePrivateCommand41(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_37);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(position);
}

// Command 0x3C, slot 82, retail 0x0026B86A: an object order a contained unit
// cannot take; the previous goal object becomes the current victim.
void AIUpdateInterface::bfmePrivateCommand3C(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_object->m_containedBy)
		return;

	Object *oldGoal = m_stateMachine->getGoalObject();
	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_lastCommandSource = commandSource;
	setCurrentVictim(oldGoal);
	m_stateMachine->setState((StateID)0x31);

	if (commandSource == CMD_FROM_PLAYER || commandSource == CMD_FROM_SCRIPT)
		playMoveVoiceResponse(obj->getPosition());
}

// Command 0x47, slot 16, retail 0x00267CFA: a position order into state 0x3F
// with no voice, refused while bit 8 of the owner's +0x370 flag word is set.
void AIUpdateInterface::bfmePrivateCommand47(const Coord3D *position, CommandSourceType commandSource)
{
	if (!m_object->isMobile())
		return;
	if (reinterpret_cast<const Rva0028B7AELeaGetter *>(m_object)->testBit8())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	setGoalPositionClipped(position, commandSource);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

// Command 0x48, slot 18, retail 0x00264558: the object form of command 0x47
// (state 0x3F, no voice), gated on the AI-dead byte as command 0x01 is.
void AIUpdateInterface::bfmePrivateCommand48(Object *obj, CommandSourceType commandSource)
{
	if (m_isAiDead)
		return;
	if (!m_object->isMobile())
		return;
	if (m_curLocomotor)
		m_curLocomotor->rva001E4147(reinterpret_cast<Rva001E4147Twelve *>(m_object));

	m_stateMachine->clear();
	m_stateMachine->setGoalObject(obj);
	m_blockedFrames = 0;
	m_bfmeByte3B8 = 0;
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_STATE_3F);
}

// Command 0x44, slot 67, retail 0x00264DF8: Zero Hour's
// privateGuardAreaFromPosition behind BFME2's status-bit, mobility and
// projectile guards. The guard target type AREA goes in the free slot of the
// two-deep stack, and with no position given the guard location is the
// area's centre.
void AIUpdateInterface::privateGuardAreaFromPosition(const PolygonTrigger *area, GuardMode guardMode,
	CommandSourceType commandSource, const Coord3D *position)
{
	Coord3D pos;
	Object *obj = getObject();
	if (obj->testStatus(BFME_OBJECT_STATUS_26))
		return;
	if (!obj->isMobile())
		return;
	if (m_object->isKindOf(KINDOF_PROJECTILE))
		return;

	if (m_guardTargetType[1] == GUARDTARGET_NONE)
		m_guardTargetType[1] = GUARDTARGET_AREA;
	else
		m_guardTargetType[0] = GUARDTARGET_AREA;
	m_areaToGuard = area;
	m_guardMode = guardMode;

	if (position == 0)
		area->getCenterPoint(&pos);
	else
		pos = *position;
	m_objectToGuard = 0;
	m_locationToGuard = pos;

	m_stateMachine->clear();
	m_lastCommandSource = commandSource;
	m_stateMachine->setState(BFME_AI_GUARD);
}
