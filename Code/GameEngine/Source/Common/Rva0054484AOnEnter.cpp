// cl: /MD
// ?onEnter@Rva0054484A@@UAE?AW4StateReturnType@@XZ, retail 0x00544480, 170 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00869BA0, class of ??0Rva0054484A@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed Object::getDockUpdateInterface 0x0028BCB4, checks slot 0x38, notifies slot 0x34 with owner, calls slot 0x18 with owner and goalPosition, loads AI at owner+0x258, checks slot 0x48, regets goal and calls rowed ignoreObstacle 0x00268D88, CritterDesync log via theLogicRandomLogFile and fprintf when g_00E03745 set, clears adjustsDestination at +0x48, sets machine+0x38 to 1, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva0054484ACtor; sibling Rva005447EDOnEnter tri pattern plus 0x0054467a stash adjustsDestination.
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
class AIUpdateInterface;

class Object
{
public:
	DockUpdateInterface *getDockUpdateInterface();
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
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};

class Rva0054484A : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

StateReturnType Rva0054484A::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	DockUpdateInterface *bec;
	if (goal == 0 || (bec = goal->getDockUpdateInterface()) == 0)
		return STATE_FAILURE;
	if (!bec->v14()) {
		bec->v13(m_machine->getOwner());
		return STATE_FAILURE;
	}
	bec->v06(m_machine->getOwner(), &m_goalPosition);
	AIUpdateInterface *ai = m_machine->getOwner()->m_ai;
	if (ai != 0) {
		if (bec->v18()) {
			Object *goal2 = ((TurretStateMachine *)m_machine)->getGoalObject();
			ai->ignoreObstacle(goal2);
			if (g_00E03745) {
				void *log = theLogicRandomLogFile;
				if (log != 0)
					fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 1");
			}
			m_adjustsDestination = false;
		}
	}
	m_machine->m_38 = true;
	return AIInternalMoveToState::onEnter();
}
