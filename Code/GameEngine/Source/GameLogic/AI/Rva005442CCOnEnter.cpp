// cl: /DNDEBUG /MD
// ?onEnter@Rva005442CC@@UAE?AW4StateReturnType@@XZ, retail 0x005442CC, 124 bytes.
// Gap between 0x0054428B and 0x00544348 of AIDockStates.cpp, same flags.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed bfmeFindBEC 0x0028BCB4, checks slot 0x38, calls slot 0x34 with owner, calls slot 8 with owner and +0x20 and machine+0x3C, clears obstacle via rowed ignoreObstacle 0x00268D88, tail-chains to pinned base onEnter 0x0034C146. Evidence: gap TU flags; tri-pattern sibling Rva00544867 onEnter; tail to base onEnter.
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
class BfmeGotBEC;
class StateMachine;

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
};

class Object
{
public:
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

class BfmeSubBEC
{
public:
	BfmeGotBEC *bfmeFindBEC();
};

class BfmeGotBEC
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool v02(Object *owner, void *a, void *b);
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
	virtual void v13(Object *owner);
	virtual bool v14();
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
};

class Rva005442CC : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva005442CC::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goal == 0)
		return STATE_FAILURE;
	BfmeGotBEC *bec = ((BfmeSubBEC *)goal)->bfmeFindBEC();
	if (bec == 0)
		return STATE_FAILURE;
	if (!bec->v14()) {
		bec->v13(m_machine->getOwner());
		return STATE_FAILURE;
	}
	if (!bec->v02(m_machine->getOwner(), &m_goalPosition, &m_machine->m_3c))
		return STATE_FAILURE;
	AIUpdateInterface *ai = m_machine->getOwner()->getAI();
	if (ai != 0)
		ai->ignoreObstacle(0);
	return AIInternalMoveToState::onEnter();
}
