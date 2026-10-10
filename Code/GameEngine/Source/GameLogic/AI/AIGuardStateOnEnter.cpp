// cl: /DNDEBUG /MD
//
// AIGuardState::onEnter, retail 0x003511E3 (378 bytes): slot 4 of vtable
// 0x00C11740, whose slot-2 name getter returns "AIGuardState". Ported from
// Zero Hour's GameEngine/Source/GameLogic/AI/AIStates.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference): hand the AI's
// guard target to the guard sub-machine by target type, set the guard mode,
// initDefaultState and enter the machine's default state.
// BFME 2 differences (target evidence): the sub-machine comes from the
// owning state machine's vslot 10 instead of a new one; target type 4 hands
// over to the rowed opaque AIUpdateInterface::rva00262D40(0) and fails; a
// location target also takes the owner's +0x44 radius (machine +0x64) and
// flags AI +0x3CD when TheTerrainLogic's getLayerForDestination is not the
// ground layer; an object target is also passed to the owner's +0x23C helper
// (Object::rva0028BBE1, pinned opaque); type 2 guards a team (machine
// setTeamToGuard 0x0033F852 through TeamFactory::findTeamByID); an area
// target caches a non-zero guard location as the area centre (machine
// +0x54/+0x60); the state entered is the machine's default id (+0x1C).
// AI vslots: getGuardLocation 118, getGuardObject 119, BFME getGuardTeam 120,
// getAreaToGuard 121, getGuardTargetType 123, getGuardMode 125.
// AIGuardMachine::setTargetToGuard (0x0033F83D) and setTeamToGuard
// (0x0033F852) are the rowed opaque setters, pinned by these names.
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt TeamID;
enum ObjectID
{
	INVALID_ID = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};
enum GuardTargetType
{
	GUARDTARGET_LOCATION = 0,
	GUARDTARGET_OBJECT,
	GUARDTARGET_BFME_TEAM,
	GUARDTARGET_AREA,
	GUARDTARGET_BFME_4
};
enum GuardMode
{
	GUARDMODE_NORMAL = 0
};
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};
struct Coord3D
{
	Real x, y, z;
	Real GetLengthEstimate() const;
};
class Object;
class Team;
class PolygonTrigger;
class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};
extern TeamFactory *TheTeamFactory;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
class AIUpdateInterface : public VSlots<118>
{
public:
	virtual const Coord3D *getGuardLocation(void) const = 0;
	virtual ObjectID getGuardObject(void) const = 0;
	virtual TeamID getGuardTeam(void) const = 0;
	virtual PolygonTrigger *getAreaToGuard(void) const = 0;
	virtual void slot122() = 0;
	virtual GuardTargetType getGuardTargetType(void) const = 0;
	virtual void slot124() = 0;
	virtual GuardMode getGuardMode(void) const = 0;
	void rva00262D40(int value);
	void setBfme3CD() { m_bfme3CD = true; }
private:
	unsigned char m_pad004[0x3CD - 0x04];
	Bool m_bfme3CD; // +0x3CD
};
class Object
{
public:
	AIUpdateInterface *getAI() { return m_ai; }
	Real getBfme44() const { return m_bfme44; }
private:
	unsigned char m_pad00[0x44];
	Real m_bfme44; // +0x44
	unsigned char m_pad48[0x258 - 0x48];
	AIUpdateInterface *m_ai; // +0x258
};
// The guard-target setters and the object notification are rowed under
// their address classes (Rva0033F83DSetter.cpp, Rva0033F852Setter.cpp,
// Rva0028BBE1.cpp).
struct Source0033F83D;
struct Source0033F852;
class Rva0033F83D { public: void rva0033F83D(const Source0033F83D *src); };
class Rva0033F852 { public: void rva0033F852(const Source0033F852 *src); };
class Rva0028BBE1 { public: void rva0028BBE1(void *target); };
class AIGuardMachine;
class StateMachine
{
public:
	virtual ~StateMachine();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual StateReturnType initDefaultState();
	virtual StateReturnType setState(StateID newStateID);
	virtual void slot09();
	virtual AIGuardMachine *getBfmeGuardMachine();
	Object *getOwner() const { return m_owner; }
protected:
	unsigned char m_pad04[0x14 - 0x04];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x1C - 0x18];
	StateID m_defaultStateID; // +0x1C
};
class AIGuardMachine : public StateMachine
{
public:
	StateID getDefaultStateID() const { return m_defaultStateID; }
	void setAreaToGuard(PolygonTrigger *area) { m_areaToGuard = area; }
	void setTargetPositionToGuard(const Coord3D *pos, Real radius) { m_positionToGuard = *pos; m_bfmeGuardRadius = radius; }
	void setBfmeAreaCenter(const Coord3D *pos) { m_bfmeAreaCenter = *pos; m_bfmeAreaCenterValid = true; }
	void setGuardMode(GuardMode guardMode) { m_guardMode = guardMode; }
private:
	unsigned char m_pad20[0x44 - 0x20];
	PolygonTrigger *m_areaToGuard; // +0x44
	Coord3D m_positionToGuard; // +0x48
	Coord3D m_bfmeAreaCenter; // +0x54
	Bool m_bfmeAreaCenterValid; // +0x60
	Real m_bfmeGuardRadius; // +0x64
	ObjectID m_nemesisToAttack; // +0x68
	GuardMode m_guardMode; // +0x6C
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};
class AIGuardState : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned char m_pad1C[0x20 - 0x1C];
	AIGuardMachine *m_guardMachine; // +0x20
};

//----------------------------------------------------------------------------------------------------------
StateReturnType AIGuardState::onEnter()
{

	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();

	m_guardMachine = getMachine()->getBfmeGuardMachine();

	GuardTargetType targetType = ai->getGuardTargetType();
	if (targetType == GUARDTARGET_BFME_4)
	{
		ai->rva00262D40(0);
		return STATE_FAILURE;
	}

	// tell the guarding machine what it is guarding with
	switch(targetType)
	{
		case GUARDTARGET_LOCATION:
		{
			Real radius = obj->getBfme44();
			m_guardMachine->setTargetPositionToGuard( ai->getGuardLocation(), radius );
			if (TheTerrainLogic->getLayerForDestination(obj, ai->getGuardLocation()) != LAYER_GROUND)
				ai->setBfme3CD();
			break;
		}
		case GUARDTARGET_OBJECT:
		{
			Object *target = TheGameLogic->findObjectByID(ai->getGuardObject());
			((Rva0033F83D *)m_guardMachine)->rva0033F83D( (const Source0033F83D *)target );
			((Rva0028BBE1 *)obj)->rva0028BBE1(target);
			break;
		}
		case GUARDTARGET_BFME_TEAM:
			((Rva0033F852 *)m_guardMachine)->rva0033F852( (const Source0033F852 *)TheTeamFactory->findTeamByID(ai->getGuardTeam()) );
			break;
		case GUARDTARGET_AREA:
			m_guardMachine->setAreaToGuard( ai->getAreaToGuard() );
			if (ai->getGuardLocation()->GetLengthEstimate() != 0.0f)
				m_guardMachine->setBfmeAreaCenter(ai->getGuardLocation());
			break;
	}
	m_guardMachine->setGuardMode(ai->getGuardMode());

	// now that essential parameters are set, set the machine's initial state
	if (m_guardMachine->initDefaultState() == STATE_FAILURE) 
		return STATE_FAILURE;
	return m_guardMachine->setState(m_guardMachine->getDefaultStateID());
}
