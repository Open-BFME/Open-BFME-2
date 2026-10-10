// cl: /MD
// ?onEnter@Rva0054482D@@UAE?AW4StateReturnType@@XZ, retail 0x00544364, 137 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00C69B58, class of ??0Rva0054482D@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, checks slot 0x38, calls slot 0x34 with owner, checks ai and slot 0x48, regets goal for rowed ignoreObstacle 0x00268D88, calls slot 0x14 with owner and +0x20, sets machine+0x3C to -1, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva0054482DCtor; siblings Rva005442CC and Rva00544867 tri pattern.
// ?update@Rva0054482D@@UAE?AW4StateReturnType@@XZ, retail 0x005443ED, 56 bytes.
// Virtual slot 6 (offset 0x18, update) of vtable 0x00C69B58, same class.
// Gets goal via rowed getGoalObject, finds BEC via rowed Object::getDockUpdateInterface, calls slot 0x14 with owner and +0x20, tail-chains to pinned base update 0x00347460. Evidence: vslot slot 6; prev onEnter same TU.
enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_RESET = 1
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class DockUpdateInterface;
class StateMachine;

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
};

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
	AIUpdateInterface *getAI() { return m_ai; }
private:
	unsigned char m_pad00[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x3C - 0x18];
public:
	int m_3c; // +0x3C
};

class TurretStateMachine : public StateMachine
{
public:
	Object *getGoalObject();
};


class DockUpdateInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual bool v05(Object *owner, void *pos);
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void onApproachReached(Object *owner);	// +0x24
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13(Object *owner);
	virtual bool v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual bool v18();
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
	virtual void slot07();
	virtual bool isIdle() const;
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
};

class Rva0054482D : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

StateReturnType Rva0054482D::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec = 0;
	if (goal != 0)
		bec = goal->getDockUpdateInterface();
	if (bec == 0)
		return STATE_FAILURE;
	if (!bec->v14()) {
		bec->v13(m_machine->getOwner());
		return STATE_FAILURE;
	}
	AIUpdateInterface *ai = m_machine->getOwner()->getAI();
	if (ai != 0) {
		if (bec->v18()) {
			Object *goal2 = ((TurretStateMachine *)m_machine)->getGoalObject();
			ai->ignoreObstacle(goal2);
		}
	}
	bec->v05(m_machine->getOwner(), &m_goalPosition);
	m_machine->m_3c = -1;
	return AIInternalMoveToState::onEnter();
}

StateReturnType Rva0054482D::update()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec = 0;
	if (goal != 0)
		bec = goal->getDockUpdateInterface();
	if (bec == 0)
		return STATE_FAILURE;
	bec->v05(m_machine->getOwner(), &m_goalPosition);
	return AIInternalMoveToState::update();
}

// ?onExit@Rva0054482D@@UAEXW4StateExitType@@@Z, retail 0x00544425, 91 bytes:
// slot 5 between the onEnter and update above. Zero Hour's
// AIDockApproachState::onExit: an interrupted approach or a closed dock
// (slot 0x38) cancels the docking (slot 0x34), otherwise the dock is told the
// approach was reached (slot 0x24); then the base move-to onExit (pinned
// 0x003473A4).
void Rva0054482D::onExit(StateExitType status)
{
	Object *goalObject = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goalObject)
	{
		DockUpdateInterface *dock = goalObject->getDockUpdateInterface();
		if (dock)
		{
			// if we were interrupted, let the dock know we're not coming
			if (dock->v14() == false || status == EXIT_RESET)
				dock->v13(m_machine->getOwner());
			else
				dock->onApproachReached(m_machine->getOwner());
		}
	}

	// this behavior is an extention of basic MoveTo
	AIInternalMoveToState::onExit(status);
}
