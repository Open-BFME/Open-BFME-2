// cl: /DNDEBUG /MD
//
// ??0Rva0034005D@@QAE@PAVStateMachine@@@Z @ 0x0034005D (33B): ctor of unknown
// AI state with vtable 0x00811EB8. Target evidence: stores vtable then byte 1
// at +0x4C and returns this with ret 4. Calls pinned base
// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@I@Z at 0x0033F279 with hash
// 0x6e6fe691. Base layout and flags copied from AIStatesSmallUpdates.cpp.
// Callers include 0x00346CDD which chains this as its base.
typedef bool Bool;
typedef float Real;
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
struct Coord3D
{
	Real x, y, z;
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};
class StateMachine;
class Xfer;
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer(Xfer *xfer);
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	Real m_2C;
	int m_30;
	Coord3D m_pathGoalPosition; // +0x34
	int m_goalLayer; // +0x40
	int m_44;
	Bool m_adjustsDestination; // +0x48
	Bool m_49;
	Bool m_4A;
	Bool m_4B;
};
class Rva0034005D : public AIInternalMoveToState
{
public:
	Rva0034005D(StateMachine *machine);
private:
	Bool m_unk4C; // +0x4C
};
Rva0034005D::Rva0034005D(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x6e6fe691u)
	, m_unk4C(true)
{
}

// ??0Rva003400CE@@QAE@PAVStateMachine@@@Z @ 0x003400CE (37B): another
// AIInternalMoveToState-derived state (pinned base 0x0033F279, hash
// 0xf0a7ff17), vtable 0x00811F00; zeroes a dword at +0x4C and a byte at
// +0x50, ret 4.
class Rva003400CE : public AIInternalMoveToState
{
public:
	Rva003400CE(StateMachine *machine);
private:
	int m_4C; // +0x4C
	Bool m_50; // +0x50
};
Rva003400CE::Rva003400CE(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xf0a7ff17u)
	, m_4C(0)
	, m_50(false)
{
}

// ??0AIInternalMoveToState@@QAE@PAVStateMachine@@I@Z @ 0x0033F279 (92B): the
// base every constructor below calls (pinned name), vtable 0x00C10DE8. It calls
// the State ctor 0x004D73FC with (machine, hash), then clears the goal and path
// positions and sets the layer at +0x40 and m_adjustsDestination to 1, the
// Zero Hour shape plus BFME2's extra fields.
AIInternalMoveToState::AIInternalMoveToState(StateMachine *machine, unsigned int hash)
	: State(machine, hash)
{
	m_goalPosition.zero();
	m_2C = 0.0f;
	m_30 = 0;
	m_pathGoalPosition.zero();
	m_44 = 0;
	m_49 = false;
	m_4A = false;
	m_4B = false;
	m_goalLayer = 1;
	m_adjustsDestination = true;
}

// AI state constructors, retail 0x00342978..0x00343077. Each calls the pinned
// AIInternalMoveToState ctor 0x0033F279 (or a rowed intermediate) with its own
// name hash, installs its own vtable and initialises its members. The class
// names are target evidence: slot 2 of each vtable is the name getter rowed in
// ConstIntGetters3.cpp, and slots 3-6 (xfer/onEnter/onExit/update) are rowed
// under the same class names. Parameter names follow the stored members only.
// Float triples are cleared with Coord3D::zero() as in Zero Hour; VC7.1 keeps
// those stores after the vtable store, where plain float assignments are
// scheduled ahead of it.
// Structural inference: the +0x4C int of AIAttackMeleeApproachState and
// AIAttackMeleeSquishState is stored after the vtable, which VC7.1 does only
// for a member subobject that its own constructor zeroes (a plain int
// assignment is scheduled ahead of the vtable store). The original type name
// is unknown.
struct ZeroedInt
{
	int value;
	ZeroedInt() : value(0) {}
};

class Rva00342843 : public AIInternalMoveToState
{
public:
	Rva00342843(StateMachine *machine, unsigned int hash);
private:
	int m_4C; // +0x4C
	Bool m_50; // +0x50
};

// ??0AIAttackApproachTargetState@@QAE@PAVStateMachine@@_N11@Z @ 0x0034290D
// (101B): vtable 0x00C12610 (name getter "AIAttackApproachTargetState"), hash
// 0xcc44c7b1; three Bool parameters stored at +0x6C, +0x6D and +0x70.
class AIAttackApproachTargetState : public AIInternalMoveToState
{
public:
	AIAttackApproachTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking);
private:
	Coord3D m_4C;
	Coord3D m_58;
	int m_64;
	int m_68;
	Bool m_follow; // +0x6C
	Bool m_isAttackingObject; // +0x6D
	Bool m_6E;
	Bool m_6F;
	Bool m_forceAttacking; // +0x70
	Bool m_71;
};
AIAttackApproachTargetState::AIAttackApproachTargetState(StateMachine *machine, Bool follow, Bool attackingObject, Bool forceAttacking)
	: AIInternalMoveToState(machine, 0xcc44c7b1u)
{
	m_4C.zero();
	m_58.zero();
	m_64 = 0;
	m_68 = 0;
	m_follow = follow;
	m_isAttackingObject = attackingObject;
	m_6E = false;
	m_6F = true;
	m_forceAttacking = forceAttacking;
	m_71 = false;
}

// ??0AIAttackApproachTargetState00C12678@@QAE@PAVStateMachine@@@Z @ 0x00342978
// (65B): vtable 0x00C12678 (name getter "AIAttackApproachTargetState"), hash
// 0x2c0e0e68.
class AIAttackApproachTargetState00C12678 : public AIInternalMoveToState
{
public:
	AIAttackApproachTargetState00C12678(StateMachine *machine);
private:
	Coord3D m_4C;
	int m_58;
	int m_5C;
	Bool m_60;
	Bool m_61;
	Bool m_62;
};
AIAttackApproachTargetState00C12678::AIAttackApproachTargetState00C12678(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x2c0e0e68u)
{
	m_4C.zero();
	m_58 = 0;
	m_5C = 0;
	m_60 = false;
	m_62 = false;
	m_61 = true;
}

// ??0AIAttackPursueTargetState@@QAE@PAVStateMachine@@_N11@Z @ 0x003429FA
// (80B): vtable 0x00C12730 (name getter "AIAttackPursueTargetState"), hash
// 0xd69031bf; three Bool parameters stored at +0x5C, +0x5D and +0x60.
class AIAttackPursueTargetState : public AIInternalMoveToState
{
public:
	AIAttackPursueTargetState(StateMachine *machine, Bool follow, Bool attackBuildings, Bool forceAttacking);
private:
	Coord3D m_4C;
	int m_58;
	Bool m_follow; // +0x5C
	Bool m_attackBuildings; // +0x5D
	Bool m_5E;
	Bool m_5F;
	Bool m_forceAttacking; // +0x60
};
AIAttackPursueTargetState::AIAttackPursueTargetState(StateMachine *machine, Bool follow, Bool attackBuildings, Bool forceAttacking)
	: AIInternalMoveToState(machine, 0xd69031bfu)
{
	m_4C.zero();
	m_58 = 0;
	m_follow = follow;
	m_attackBuildings = attackBuildings;
	m_forceAttacking = forceAttacking;
	m_5E = false;
	m_5F = true;
}

// ??0Rva00342A50@@QAE@PAVStateMachine@@@Z @ 0x00342A50 (64B): vtable
// 0x00C12798 (name getter "AIAttackFireDuringApproachState"), hash
// 0xbcb86c63. Keeps the pinned opaque name its caller 0x003435FB links to.
class Rva00342A50 : public AIInternalMoveToState
{
public:
	Rva00342A50(StateMachine *machine);
private:
	int m_4C;
	Coord3D m_50;
	int m_5C;
	int m_60;
	int m_64;
	Bool m_68;
};
Rva00342A50::Rva00342A50(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xbcb86c63u)
{
	m_4C = 0;
	m_50.zero();
	m_5C = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = false;
}

// ??0AIAttackMeleeApproachState@@QAE@PAVStateMachine@@@Z @ 0x00342A96 (58B):
// vtable 0x00C12800 (name getter "AIAttackMeleeApproachState"), hash
// 0x11c8c40d.
class AIAttackMeleeApproachState : public AIInternalMoveToState
{
public:
	AIAttackMeleeApproachState(StateMachine *machine);
private:
	ZeroedInt m_4C;
	Coord3D m_50;
	int m_5C;
	int m_60;
};
AIAttackMeleeApproachState::AIAttackMeleeApproachState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x11c8c40du)
{
	m_50.zero();
	m_5C = 0;
	m_60 = 0;
}

// ??0AIAttackMeleeSquishState@@QAE@PAVStateMachine@@@Z @ 0x00342AD6 (62B):
// vtable 0x00C12868 (name getter "AIAttackMeleeSquishState"), hash 0xc891265a.
class AIAttackMeleeSquishState : public AIInternalMoveToState
{
public:
	AIAttackMeleeSquishState(StateMachine *machine);
private:
	ZeroedInt m_4C;
	Coord3D m_50;
	int m_5C;
	int m_60;
	Bool m_64;
};
AIAttackMeleeSquishState::AIAttackMeleeSquishState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xc891265au)
{
	m_50.zero();
	m_5C = 0;
	m_60 = 0;
	m_64 = true;
}

// ??0Rva00340BDC@@QAE@PAVStateMachine@@H@Z @ 0x00342B1A (81B): vtable
// 0x00C12150, whose slots 0 and 3 are rowed as Rva00340BDC (??_G and xfer);
// hash 0x26ab28f6; stores its int parameter at +0x74.
class Rva00340BDC : public AIInternalMoveToState
{
public:
	Rva00340BDC(StateMachine *machine, int value);
private:
	int m_4C;
	int m_50;
	int m_54;
	Coord3D m_58;
	int m_64;
	int m_68;
	int m_6C;
	Bool m_70;
	Bool m_71;
	int m_74;
};
Rva00340BDC::Rva00340BDC(StateMachine *machine, int value)
	: AIInternalMoveToState(machine, 0x26ab28f6u)
{
	m_50 = -1;
	m_4C = 0;
	m_54 = 0;
	m_58.zero();
	m_64 = 0;
	m_68 = 0;
	m_6C = 0;
	m_70 = false;
	m_71 = false;
	m_74 = value;
}

// ??0AIWanderInPlaceState@@QAE@PAVStateMachine@@@Z @ 0x00342CBF (55B):
// vtable 0x00C12AC8 (name getter "AIWanderInPlaceState"), hash 0xb8681eaf.
class AIWanderInPlaceState : public AIInternalMoveToState
{
public:
	AIWanderInPlaceState(StateMachine *machine);
private:
	Coord3D m_origin; // +0x4C
	int m_58;
	int m_5C;
};
AIWanderInPlaceState::AIWanderInPlaceState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xb8681eafu)
{
	m_origin.zero();
	m_58 = 0;
	m_5C = 0;
}

// ??0Rva00342CFC@@QAE@PAVStateMachine@@@Z @ 0x00342CFC (29B): vtable
// 0x00C12B28, hash 0x334bbbd8, no members of its own. Its name getter also
// returns "AIWanderInPlaceState", so the class stays opaque.
class Rva00342CFC : public AIInternalMoveToState
{
public:
	Rva00342CFC(StateMachine *machine);
};
Rva00342CFC::Rva00342CFC(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x334bbbd8u)
{
}

// ??0AIFollowPathState@@QAE@PAVStateMachine@@I@Z @ 0x00342D41 (47B): vtable
// 0x00C12BC8 (name getter "AIFollowPathState"); forwards the caller's hash.
class AIFollowPathState : public AIInternalMoveToState
{
public:
	AIFollowPathState(StateMachine *machine, unsigned int hash);
private:
	int m_4C;
	Bool m_50;
	Bool m_51;
	int m_54;
};
AIFollowPathState::AIFollowPathState(StateMachine *machine, unsigned int hash)
	: AIInternalMoveToState(machine, hash)
{
	m_4C = 0;
	m_50 = true;
	m_51 = false;
	m_54 = 10;
}

// ??0AIMoveAndEvacuateState@@QAE@PAVStateMachine@@@Z @ 0x00342D76 (47B):
// vtable 0x00C12C28 (name getter "AIMoveAndEvacuateState"), hash 0xe80d849c.
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
public:
	AIMoveAndEvacuateState(StateMachine *machine);
private:
	Coord3D m_origin; // +0x4C
};
AIMoveAndEvacuateState::AIMoveAndEvacuateState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xe80d849cu)
{
	m_origin.zero();
}

// ??0AIMoveAndDeleteState@@QAE@PAVStateMachine@@@Z @ 0x00342DAB (33B):
// vtable 0x00C12C88 (name getter "AIMoveAndDeleteState"), hash 0x599405f6.
class AIMoveAndDeleteState : public AIInternalMoveToState
{
public:
	AIMoveAndDeleteState(StateMachine *machine);
private:
	Bool m_appendGoalPosition; // +0x4C
};
AIMoveAndDeleteState::AIMoveAndDeleteState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x599405f6u)
{
	m_appendGoalPosition = false;
}

// ??0AIMoveToPositionAndDieState@@QAE@PAVStateMachine@@@Z @ 0x00342DD2 (33B):
// vtable 0x00C12CE8 (name getter "AIMoveToPositionAndDieState"), hash
// 0x026a0e93.
class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
public:
	AIMoveToPositionAndDieState(StateMachine *machine);
private:
	Bool m_4C;
};
AIMoveToPositionAndDieState::AIMoveToPositionAndDieState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x026a0e93u)
{
	m_4C = false;
}

// ??0AIMoveToAndEvacuateState@@QAE@PAVStateMachine@@@Z @ 0x00342DF9 (24B):
// vtable 0x00C12D50 (name getter "AIMoveToAndEvacuateState"), over the
// Rva0034005D ctor above.
class AIMoveToAndEvacuateState : public Rva0034005D
{
public:
	AIMoveToAndEvacuateState(StateMachine *machine);
};
AIMoveToAndEvacuateState::AIMoveToAndEvacuateState(StateMachine *machine)
	: Rva0034005D(machine)
{
}

// ??0AIAttackMoveToAndEvacuateState@@QAE@PAVStateMachine@@@Z @ 0x00342E17
// (24B): vtable 0x00C12DB8 (name getter "AIAttackMoveToAndEvacuateState"),
// over AIMoveToAndEvacuateState.
class AIAttackMoveToAndEvacuateState : public AIMoveToAndEvacuateState
{
public:
	AIAttackMoveToAndEvacuateState(StateMachine *machine);
};
AIAttackMoveToAndEvacuateState::AIAttackMoveToAndEvacuateState(StateMachine *machine)
	: AIMoveToAndEvacuateState(machine)
{
}

// ??0AIFollowPathAndEvacuateState@@QAE@PAVStateMachine@@@Z @ 0x00342E35 (29B):
// vtable 0x00C12E28 (name getter "AIFollowPathAndEvacuateState"), over
// AIFollowPathState with hash 0x4dea69c5.
class AIFollowPathAndEvacuateState : public AIFollowPathState
{
public:
	AIFollowPathAndEvacuateState(StateMachine *machine);
};
AIFollowPathAndEvacuateState::AIFollowPathAndEvacuateState(StateMachine *machine)
	: AIFollowPathState(machine, 0x4dea69c5u)
{
}

// ??0AICombineState@@QAE@PAVStateMachine@@@Z @ 0x00342ED7 (29B): vtable
// 0x00C12EE8 (name getter "AICombineState"), hash 0x0d2ccd3c.
class AICombineState : public AIInternalMoveToState
{
public:
	AICombineState(StateMachine *machine);
};
AICombineState::AICombineState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x0d2ccd3cu)
{
}

// ??0AIEnterAndAttackState@@QAE@PAVStateMachine@@@Z @ 0x00342EFA (37B):
// vtable 0x00C12F40 (name getter "AIEnterAndAttackState"), hash 0xb6e1ca71.
class AIEnterAndAttackState : public AIInternalMoveToState
{
public:
	AIEnterAndAttackState(StateMachine *machine);
private:
	int m_4C;
	int m_50;
};
AIEnterAndAttackState::AIEnterAndAttackState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0xb6e1ca71u)
{
	m_4C = 0;
	m_50 = 0;
}

// ??0AIMoveAwayAndCowerState@@QAE@PAVStateMachine@@@Z @ 0x00342FF8 (29B):
// vtable 0x00C12FF0 (name getter "AIMoveAwayAndCowerState"), over the rowed
// Rva00342843(machine, hash) ctor 0x0034286E with hash 0x0c947cc9.
class AIMoveAwayAndCowerState : public Rva00342843
{
public:
	AIMoveAwayAndCowerState(StateMachine *machine);
};
AIMoveAwayAndCowerState::AIMoveAwayAndCowerState(StateMachine *machine)
	: Rva00342843(machine, 0x0c947cc9u)
{
}

// ??0AIBackAwayState@@QAE@PAVStateMachine@@@Z @ 0x0034301B (33B): vtable
// 0x00C13050 (name getter "AIBackAwayState"), over Rva00342843(machine, hash)
// with hash 0x0fcb3e8d; clears a Bool at +0x54.
class AIBackAwayState : public Rva00342843
{
public:
	AIBackAwayState(StateMachine *machine);
private:
	Bool m_54;
};
AIBackAwayState::AIBackAwayState(StateMachine *machine)
	: Rva00342843(machine, 0x0fcb3e8du)
{
	m_54 = false;
}

// ??0AIChargeTargetState@@QAE@PAVStateMachine@@@Z @ 0x00343042 (47B): vtable
// 0x00C130A8 (name getter "AIChargeTargetState"), hash 0x6a236ab9.
class AIChargeTargetState : public AIInternalMoveToState
{
public:
	AIChargeTargetState(StateMachine *machine);
private:
	Bool m_4C;
	int m_50;
	Bool m_54;
	Bool m_55;
};
AIChargeTargetState::AIChargeTargetState(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x6a236ab9u)
{
	m_4C = false;
	m_50 = 1;
	m_54 = false;
	m_55 = false;
}

// ??0AIMoveForBoarding@@QAE@PAVStateMachine@@@Z @ 0x00343077 (24B): vtable
// 0x00C13108 (name getter "AIMoveForBoarding"), over the Rva0034005D ctor.
class AIMoveForBoarding : public Rva0034005D
{
public:
	AIMoveForBoarding(StateMachine *machine);
};
AIMoveForBoarding::AIMoveForBoarding(StateMachine *machine)
	: Rva0034005D(machine)
{
}
