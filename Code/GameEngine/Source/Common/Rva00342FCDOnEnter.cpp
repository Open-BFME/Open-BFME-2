// cl: /MD
//
// ?onEnter@Rva00342FCD@@UAE?AW4StateReturnType@@XZ @0x0034BCBD 94B
// Override of Rva0033FE65::onEnter via vtable slot 4 of 0x00812FA0
// (class of ??0Rva00342FCD). Evidence: tail-jmp to 0x00346FD0
// (Rva0033FE65::onEnter) when m_28==2; float ==0.0f via Rva001E3F08
// returning 0/1 into m_2C; getGoalObject null plus m_28 checks
// returning -2/0; 0 callers (state virtual).
enum StateReturnType
{
	STATE_CONTINUE = 0
};

class StateMachine;
class Object;

struct Rva001E3F08MidB;
struct Rva001E3F08Arg
{
	char m_pad00[0x258];
	Rva001E3F08MidB *m_p258;
};

class Rva001E3F08
{
public:
	float rva001E3F08(Rva001E3F08Arg *p);
};

struct Rva001E3F08Holder
{
	char m_pad00[0x1F0];
	Rva001E3F08 *m_holder1F0;
};

struct AIUpdateLike
{
	char m_pad00[0x1F0];
	Rva001E3F08 *m_iface1F0;
};

struct OwnerLike
{
	char m_pad00[0x258];
	AIUpdateLike *m_ai258;
};

struct StateMachineLike
{
	char m_pad00[0x14];
	OwnerLike *m_owner14;
};

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachineLike *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};

class TurretStateMachine;
class Object;

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

class Rva0033FE65 : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned short m_20;
	unsigned short m_22;
	bool m_24;
	bool m_25;
	char m_pad26[0x28 - 0x26];
};

class Rva00342FCD : public Rva0033FE65
{
public:
	virtual StateReturnType onEnter();
private:
	int m_28;
	unsigned char m_2C;
};

StateReturnType Rva00342FCD::onEnter()
{
	OwnerLike *owner = m_machine->m_owner14;
	Rva001E3F08 *holder = owner->m_ai258->m_iface1F0;
	int flag;
	if (holder == 0)
		flag = 0;
	else if (holder->rva001E3F08((Rva001E3F08Arg *)owner) == 0.0f)
		flag = 1;
	else
		flag = 0;
	m_2C = flag;
	Object *goal = ((TurretStateMachine *)m_machine)->getGoalObject();
	int v = m_28;
	if (v != 0 && goal == 0)
		return (StateReturnType)-2;
	if (v == 2)
		return Rva0033FE65::onEnter();
	return STATE_CONTINUE;
}
