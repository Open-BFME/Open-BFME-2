// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AIFaceState::update, retail 0x0035487E (199 bytes): slot 6 of vtable
// 0x00C12FA0, whose slot-2 name getter returns AIFaceState (slot 3 is the
// rowed AIFaceState::xfer). Ported from Zero Hour's
// GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference): face the machine's goal object or
// position, succeed within REL_THRESH (0.035), else turn in place to the
// owner's orientation (+0x44) plus the relative angle (AI vslot 135) or steer
// to the position (AI vslot 132).
// BFME 2 differences (target evidence): m_obj is a mode (+0x28): mode 2 turns
// through the owner's rowed rva0029439D target (its vslot 132) and then
// returns the base AIIdleState::update (0x0035389E, slot 6 of the
// AIIdleState vtable 0x00C11E08, pinned); the relative angle is the owner's
// out-of-line helper at 0x000B4542 (pinned opaque) instead of
// ThePartitionManager's; fabs is the CRT import, declared here with a float
// result: retail compares its x87 result directly with the float threshold
// (fld dword), which the double declaration turns into a double constant.
// AIFaceState::onExit, retail 0x003423A6 (34 bytes): slot 5 of the same
// vtable. Zero Hour's is empty; BFME 2 stops the mode-2 turner (its vslot 133).
// Layout: machine goal position +0x24, m_canTurnInPlace +0x2C.
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
};
extern "C" float __cdecl fabs(double); // CRT fabs; x87 result compared as float
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class Rva0029439DTarget : public VSlots<132>
{
public:
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &newPos) = 0;
	virtual void bfmeStopTurn() = 0;
};
class AIUpdateInterface : public VSlots<132>
{
public:
	virtual void setLocomotorGoalPositionExplicit(const Coord3D &newPos) = 0;
	virtual void slot133() = 0;
	virtual void slot134() = 0;
	virtual void setLocomotorGoalOrientation(Real angle) = 0;
};
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	Real getOrientation() const { return m_orientation; }
	AIUpdateInterface *getAI() { return m_ai; }
	Real rva000B4542(const Coord3D *pos) const;
	void *rva0029439D();
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
	unsigned char m_pad48[0x258 - 0x48];
	AIUpdateInterface *m_ai; // +0x258
};
class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	Object *getGoalObject();
	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x24 - 0x18];
	Coord3D m_goalPosition; // +0x24
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	Object *getMachineGoalObject() const { return m_machine->getGoalObject(); }
	const Coord3D *getMachineGoalPosition() const { return m_machine->getGoalPosition(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIIdleState : public State
{
public:
	virtual StateReturnType update();
};
class AIFaceState : public AIIdleState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
private:
	unsigned char m_pad1C[0x28 - 0x1C];
	int m_obj; // +0x28
	Bool m_canTurnInPlace; // +0x2C
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIFaceState::update()
{

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	const Coord3D* pos = getMachineGoalPosition();
	if (m_obj)
	{
		Object *target = getMachineGoalObject();
		if (!target)
		{
			// Nothing to face.
			return STATE_FAILURE;	
		}
		pos = target->getPosition();
	}
	Real relAngle = obj->rva000B4542( pos );

	static const Real REL_THRESH = 0.035f;	// about 2 degrees. (getRelativeAngle2D is current only accurate to about 1.25 degrees)
	if( fabs( relAngle ) < REL_THRESH )
	{
		return STATE_SUCCESS;
	}

	if (m_canTurnInPlace)
	{
		Real desiredAngle = obj->getOrientation() + relAngle;
		Rva0029439DTarget *turner;
		if (m_obj == 2 && (turner = (Rva0029439DTarget *)obj->rva0029439D()) != 0)
			turner->setLocomotorGoalPositionExplicit(*pos);
		else
			ai->setLocomotorGoalOrientation( desiredAngle );
	}
	else
	{
		ai->setLocomotorGoalPositionExplicit(*pos);
	}

	if (m_obj == 2)
		return AIIdleState::update();
	return STATE_CONTINUE;
}

//----------------------------------------------------------------------------------------------------------
void AIFaceState::onExit( StateExitType status )
{
	if (m_obj == 2)
	{
		Rva0029439DTarget *turner = (Rva0029439DTarget *)getMachineOwner()->rva0029439D();
		if (turner)
			turner->bfmeStopTurn();
	}
}
