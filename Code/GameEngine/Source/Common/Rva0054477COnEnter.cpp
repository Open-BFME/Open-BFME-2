// cl: /MD
// ?onEnter@Rva00544867@@UAE?AW4StateReturnType@@XZ, retail 0x0054477C, 113 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00C69BE8, class of ??0Rva00544867@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, checks slot 0x4C, regets ExitInterface via rowed getObjectExitInterface 0x0028B445, checks slot 0x20, copies 12B goal position to +0x20, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva00544867Ctor; sibling Rva00544884 onEnter tri pattern.
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
class ExitInterface;
class StateMachine;

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
	ExitInterface *getObjectExitInterface() const;
};

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
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
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual bool v19();
};

class ExitInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual Coord3D *v08();
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void slot05();
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
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};

class Rva00544867 : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva00544867::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec = 0;
	if (goal != 0)
		bec = goal->getDockUpdateInterface();
	if (bec == 0)
		return STATE_FAILURE;
	if (bec->v19()) {
		if (goal->getObjectExitInterface() != 0) {
			if (goal->getObjectExitInterface()->v08() != 0) {
				Coord3D *pos = goal->getObjectExitInterface()->v08();
				m_goalPosition = *pos;
				return AIInternalMoveToState::onEnter();
			}
		}
	}
	return STATE_SUCCESS;
}
