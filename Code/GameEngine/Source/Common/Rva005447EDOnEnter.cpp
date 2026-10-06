// cl: /MD
// ?onEnter@Rva005447ED@@UAE?AW4StateReturnType@@XZ, retail 0x00544133, 124 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00869AB0, class of ??0Rva005447ED@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal object via rowed getGoalObject 0x004D7726, finds BfmeGotBEC via rowed bfmeFindBEC 0x0028BCB4, checks slot 0x38, notifies slot 0x34 with owner, calls slot 0x04 with owner and goalPosition and machine+0x3C, clears obstacle via rowed ignoreObstacle 0x00268D88, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva005447EDCtor; prev Rva005440BCVSlot5440CD same call pair.
enum StateReturnType
{
	STATE_CONTINUE = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;
class BfmeGotBEC;
class AIUpdateInterface;

class Object
{
public:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *obj);
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
	unsigned char m_pad18[0x3C - 0x18];
	int m_3C; // +0x3C
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
	virtual bool v01(Object *owner, Coord3D *goal, void *arg3);
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

class Rva005447ED : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

StateReturnType Rva005447ED::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goal == 0)
		return (StateReturnType)-2;
	BfmeGotBEC *bec = ((BfmeSubBEC *)goal)->bfmeFindBEC();
	if (bec == 0)
		return (StateReturnType)-2;
	if (!bec->v14()) {
		bec->v13(m_machine->getOwner());
		return (StateReturnType)-2;
	}
	if (!bec->v01(m_machine->getOwner(), &m_goalPosition, &((TurretStateMachine *)m_machine)->m_3C))
		return (StateReturnType)-2;
	AIUpdateInterface *ai = m_machine->getOwner()->m_ai;
	if (ai != 0)
		ai->ignoreObstacle(0);
	return AIInternalMoveToState::onEnter();
}
