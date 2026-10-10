// cl: /MD
// ?onExit@Rva0054484A@@UAEXW4StateExitType@@@Z, retail 0x00544572, 98 bytes.
// Virtual slot 5 (offset 0x14, onExit) of vtable 0x00869BA0, class of ??0Rva0054484A@@QAE@PAVStateMachine@@@Z.
// Same BEC tricall prologue as sibling update 0x0054452A and onEnter 0x00544480: gets
// TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed
// Object::getDockUpdateInterface 0x0028BCB4, then notifies slot 0x28 (v10) with owner when exitType != 1
// and slot 0x38 (v14) is true, else slot 0x34 (v13) with owner. Always clears
// machine+0x38 to 0 and chains to rowed AIInternalMoveToState::onExit 0x003473A4.
// Evidence: vslot slot5; ctor TU Rva0054484ACtor.cpp; prev Rva0054452AFinish.cpp.
enum StateExitType
{
	EXIT_NORMAL = 0,
	EXIT_OTHER = 1
};

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(Object *owner);
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
	virtual void onExit(StateExitType exitType);
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
	virtual void onExit(StateExitType exitType);
	virtual StateReturnType update();
};

class Rva0054484A : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();
	virtual void onExit(StateExitType exitType);
};

void Rva0054484A::onExit(StateExitType exitType)
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goal != 0) {
		DockUpdateInterface *bec = goal->getDockUpdateInterface();
		if (bec != 0) {
			if (exitType != EXIT_OTHER) {
				_ReadWriteBarrier();
				if (bec->v14()) {
					_ReadWriteBarrier();
					bec->v10(m_machine->getOwner());
				}
				else
					bec->v13(m_machine->getOwner());
			}
			else {
				bec->v13(m_machine->getOwner());
			}
		}
	}
	m_machine->m_38 = false;
	AIInternalMoveToState::onExit(exitType);
}
