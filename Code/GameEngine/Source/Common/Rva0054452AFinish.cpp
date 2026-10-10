// cl: /MD
// ?update@Rva0054484A@@UAE?AW4StateReturnType@@XZ, retail 0x0054452A, 72 bytes.
// Virtual slot 6 (offset 0x18, update) of vtable 0x00869BA0, class of ??0Rva0054484A@@QAE@PAVStateMachine@@@Z.
// Same BEC tricall prologue as the matched onEnter at 0x00544480: gets TurretStateMachine goal
// via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, checks slot
// 0x38 (v14), then calls slot 0x18 (v06) with owner and goalPosition, tail-chains to the base
// update. All three failure conditions share one exit returning STATE_FAILURE (-2). Evidence:
// vslot slot6; onEnter TU Rva0054484AOnEnter.cpp; ctor TU Rva0054484ACtor.cpp.
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

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
	unsigned char m_pad18[0x38 - 0x18];
	bool m_38; // +0x38
};

class TurretStateMachine : public StateMachine
{
public:
	Object *getGoalObject();
};

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
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
	virtual void v06(Object *owner, Coord3D *goal);
	virtual void v07();
	virtual void v08();
	virtual void v09();
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
	virtual StateReturnType update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};

class Rva0054484A : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
};

StateReturnType Rva0054484A::update()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec = 0;
	if (goal != 0)
		bec = goal->getDockUpdateInterface();
	if (bec == 0)
		goto fail;
	if (!bec->v14())
		goto fail;
	bec->v06(m_machine->getOwner(), &m_goalPosition);
	return AIInternalMoveToState::update();
fail:
	return STATE_FAILURE;
}