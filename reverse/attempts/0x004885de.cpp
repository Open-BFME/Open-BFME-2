// ??0Rva004885DE@@QAE@PAVObject@@H@Z
// partial score=0.98 date=2026-10-05
// cl: /O1 /MD /EHsc
// ??0Rva004885DE@@QAE@PAVObject@@H@Z retail 0x004885DE (227B).
// class-gate: allow AsciiString retail 0x004885DE pushes hash 0x253E8923 as POD with no ctor/dtor calls, shared header adds releaseBuffer ctor/dtor.
// StateMachine-family ctor: base Rva004D759C 0x004D79E1 with hash 0x253E8923,
// vtable 0x0084B510, second arg at +0x3C, then three State children
// Rva004884ED/Rva0048851B/Rva00488545 via new plus defineState 0x004D7B0F.
// Evidence: caller 0x00488883 passes owner from +0x18/+0x14 and int, new 0x40,
// ret 8 with mov eax esi proving ctor, callers/prev/next in packet.

class Object;
class StateMachine;

class AsciiString
{
public:
	void *m_data;
};

static const AsciiString kHash = { (void *)0x253E8923 };

struct StateConditionInfo
{
	void *test;
	unsigned int toStateID;
	void *userData;
};

class StateMachine
{
public:
	void defineState(unsigned int id, struct State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions);
};

struct State
{
public:
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
};

class Rva004D759C
{
public:
	Rva004D759C(Object *owner, AsciiString name, bool flag);
	virtual ~Rva004D759C();
private:
	char m_pad04[0x3C - 4];
};

class Rva004884ED : public State
{
public:
	Rva004884ED(StateMachine *machine, int arg0);
	int m_20;
	int m_24;
};

class Rva0048851B : public State
{
public:
	Rva0048851B(StateMachine *machine, int arg0);
	int m_20;
};

class Rva00488545 : public State
{
public:
	Rva00488545(StateMachine *machine, int arg0);
	int m_20;
	int m_24;
};

class Rva004885DE : public Rva004D759C
{
public:
	Rva004885DE(Object *owner, int val);
private:
	int m_3C;
};

// ??0Rva004885DE@@QAE@PAVObject@@H@Z present-unmatched
Rva004885DE::Rva004885DE(Object *owner, int val)
	: Rva004D759C(owner, kHash, false)
	, m_3C(val)
{
	StateMachine *machine = (StateMachine *)this;
	State *s0 = new Rva004884ED(machine, val);
	((StateMachine *)this)->defineState(0, s0, 1, 0x270Fu, 0);
	State *s1 = new Rva0048851B(machine, val);
	((StateMachine *)this)->defineState(1, s1, 2, 0, 0);
	State *s2 = new Rva00488545(machine, val);
	((StateMachine *)this)->defineState(2, s2, 0x270Eu, 0x270Fu, 0);
}
