// cl: /MD
// ?onEnter@Rva00544884@@UAE?AW4StateReturnType@@XZ, retail 0x0054467A, 141 bytes.
// Virtual slot 4 (offset 0x10, onEnter) of vtable 0x00869C30, class of ??0Rva00544884@@QAE@PAVStateMachine@@@Z.
// Gets TurretStateMachine goal via rowed getGoalObject 0x004D7726, finds BEC via rowed bfmeFindBEC 0x0028BCB4, calls slot 0x1C with owner and goalPosition, loads AI at owner+0x258, checks slot 0x48, regets goal and calls rowed ignoreObstacle 0x00268D88, CritterDesync log via theLogicRandomLogFile and _fprintf when g_00E03745 set, clears adjustsDestination at +0x48, tail-chains to pinned base onEnter 0x0034C146. Evidence: vslot slot 4; ctor TU Rva00544884Ctor; sibling Rva005447EDOnEnter same tri pattern; AIStatesSmallUpdates CritterDesync precedent.
// ?update@Rva00544884@@UAE?AW4StateReturnType@@XZ, retail 0x00544707, 56 bytes.
// Virtual slot 6 (offset 0x18, update) of vtable 0x00869C30, same class.
// Gets goal via rowed getGoalObject, finds BEC via rowed bfmeFindBEC, calls slot 0x1C with owner and +0x20, tail-chains to pinned base update 0x00347460. Evidence: vslot slot 6; prev onEnter same TU.
// ?onExit@Rva00544884@@UAEXW4StateExitType@@@Z, retail 0x0054473F, 61 bytes.
// Virtual slot 5 (offset 0x14, onExit) of vtable 0x00869C30, same class.
// Gets goal via rowed getGoalObject, finds BEC via rowed bfmeFindBEC, notifies slot 0x2C with owner, clears machine+0x38 to 0, chains to rowed base onExit 0x003473A4. Evidence: vslot slot 5; prev update same TU.
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
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07(Object *owner, Coord3D *goal);
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11(Object *owner);
	virtual void v12();
	virtual void v13();
	virtual void v14();
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
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition; // +0x20
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination; // +0x48
};

class Rva00544884 : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType exitType);
	virtual StateReturnType update();
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

StateReturnType Rva00544884::onEnter()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	BfmeGotBEC *bec = 0;
	if (goal != 0)
		bec = ((BfmeSubBEC *)goal)->bfmeFindBEC();
	if (bec == 0)
		return STATE_FAILURE;
	bec->v07(m_machine->getOwner(), &m_goalPosition);
	AIUpdateInterface *ai = m_machine->getOwner()->m_ai;
	if (ai != 0) {
		if (bec->v18()) {
			Object *goal2 = ((TurretStateMachine *)m_machine)->getGoalObject();
			ai->ignoreObstacle(goal2);
			if (g_00E03745) {
				void *log = theLogicRandomLogFile;
				if (log != 0)
					fprintf(log, "CritterDesync: setAdjustDestination(FALSE) 2");
			}
			m_adjustsDestination = false;
		}
	}
	return AIInternalMoveToState::onEnter();
}

StateReturnType Rva00544884::update()
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	BfmeGotBEC *bec = 0;
	if (goal != 0)
		bec = ((BfmeSubBEC *)goal)->bfmeFindBEC();
	if (bec == 0)
		return STATE_FAILURE;
	bec->v07(m_machine->getOwner(), &m_goalPosition);
	return AIInternalMoveToState::update();
}

void Rva00544884::onExit(StateExitType exitType)
{
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	if (goal != 0) {
		BfmeGotBEC *bec = ((BfmeSubBEC *)goal)->bfmeFindBEC();
		if (bec != 0)
			bec->v11(m_machine->getOwner());
	}
	m_machine->m_38 = false;
	AIInternalMoveToState::onExit(exitType);
}
#pragma comment(linker, "/alternatename:_theLogicRandomLogFile=?g_00DFEFF0@@3PAXA")
