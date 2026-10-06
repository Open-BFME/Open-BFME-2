// cl: /MD
//
// ?rva003426CE@Rva003426AB@@UAEHXZ, retail 0x003426CE, 62 bytes.
// Virtual slot 4 (offset 0x10) of vtable 0x00812438, the class whose ctor
// ??0Rva003426AB@@QAE@PAVStateMachine@@@Z was just landed in
// StateDerivedCtorRva003426AB.cpp (same // cl: line; chain lane). Body:
// chase State::m_machine(+0x18)->+0x14->+0x258; return -2 when null;
// otherwise call slot 0x238 with 15, then slot 0x21C with the float at
// m_machine+0x24 (x87 fld plus push-ecx slot plus fstp), and return 0.
// Chain-head types are TU-local pads; only slots and offsets are
// evidence-backed. State base layout copied from rowed StateCtor.cpp.

class StateMachine;

class CEMid
{
public:
	char m_pad00[0x44];
	unsigned int m_44;
	char m_pad48[0x1C0 - 0x48];
	unsigned int m_1C0;
	char m_pad1C4[0x258 - 0x1C4];
	class CEFinal *m_ptr258;
};

class StateMachine
{
public:
	char m_pad00[0x14];
	CEMid *m_ptr14;
	char m_pad18[0x24 - 0x18];
	float m_float24;
};

class CEFinal
{
public:
	virtual void _cp000();
	virtual void _cp001();
	virtual void _cp002();
	virtual void _cp003();
	virtual void _cp004();
	virtual void _cp005();
	virtual void _cp006();
	virtual void _cp007();
	virtual void _cp008();
	virtual void _cp009();
	virtual void _cp010();
	virtual void _cp011();
	virtual void _cp012();
	virtual void _cp013();
	virtual void _cp014();
	virtual void _cp015();
	virtual void _cp016();
	virtual void _cp017();
	virtual void _cp018();
	virtual void _cp019();
	virtual void _cp020();
	virtual void _cp021();
	virtual void _cp022();
	virtual void _cp023();
	virtual void _cp024();
	virtual void _cp025();
	virtual void _cp026();
	virtual void _cp027();
	virtual void _cp028();
	virtual void _cp029();
	virtual void _cp030();
	virtual void _cp031();
	virtual void _cp032();
	virtual void _cp033();
	virtual void _cp034();
	virtual void _cp035();
	virtual void _cp036();
	virtual void _cp037();
	virtual void _cp038();
	virtual void _cp039();
	virtual void _cp040();
	virtual void _cp041();
	virtual void _cp042();
	virtual void _cp043();
	virtual void _cp044();
	virtual void _cp045();
	virtual void _cp046();
	virtual void _cp047();
	virtual void _cp048();
	virtual void _cp049();
	virtual void _cp050();
	virtual void _cp051();
	virtual void _cp052();
	virtual void _cp053();
	virtual void _cp054();
	virtual void _cp055();
	virtual void _cp056();
	virtual void _cp057();
	virtual void _cp058();
	virtual void _cp059();
	virtual void _cp060();
	virtual void _cp061();
	virtual void _cp062();
	virtual void _cp063();
	virtual void _cp064();
	virtual void _cp065();
	virtual void _cp066();
	virtual void _cp067();
	virtual void _cp068();
	virtual void _cp069();
	virtual void _cp070();
	virtual void _cp071();
	virtual void _cp072();
	virtual void _cp073();
	virtual void _cp074();
	virtual void _cp075();
	virtual void _cp076();
	virtual void _cp077();
	virtual void _cp078();
	virtual void _cp079();
	virtual void _cp080();
	virtual void _cp081();
	virtual void _cp082();
	virtual void _cp083();
	virtual void _cp084();
	virtual void _cp085();
	virtual void _cp086();
	virtual void _cp087();
	virtual void _cp088();
	virtual void _cp089();
	virtual void _cp090();
	virtual void _cp091();
	virtual void _cp092();
	virtual void _cp093();
	virtual void _cp094();
	virtual void _cp095();
	virtual void _cp096();
	virtual void _cp097();
	virtual void _cp098();
	virtual void _cp099();
	virtual void _cp100();
	virtual void _cp101();
	virtual void _cp102();
	virtual void _cp103();
	virtual void _cp104();
	virtual void _cp105();
	virtual void _cp106();
	virtual void _cp107();
	virtual void _cp108();
	virtual void _cp109();
	virtual void _cp110();
	virtual void _cp111();
	virtual void _cp112();
	virtual void _cp113();
	virtual void _cp114();
	virtual void _cp115();
	virtual void _cp116();
	virtual void _cp117();
	virtual void _cp118();
	virtual void _cp119();
	virtual void _cp120();
	virtual void _cp121();
	virtual void _cp122();
	virtual void _cp123();
	virtual void _cp124();
	virtual void _cp125();
	virtual void _cp126();
	virtual void _cp127();
	virtual void _cp128();
	virtual void _cp129();
	virtual void _cp130();
	virtual void _cp131();
	virtual void _cp132();
	virtual void _cp133();
	virtual void _cp134();
	virtual void method21C(float value);
	virtual void method220();
	virtual void _cq137();
	virtual void _cq138();
	virtual void _cq139();
	virtual void _cq140();
	virtual void _cq141();
	virtual void method238(int value);
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
	StateMachine *m_machine;
	bool m_tail1C;
};

class Rva003426AB : public State
{
public:
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual int rva003426CE();
	virtual void rva0034270C(int);
};

int Rva003426AB::rva003426CE()
{
	CEFinal *target = m_machine->m_ptr14->m_ptr258;
	if (target == 0)
		return -2;
	target->method238(15);
	target->method21C(m_machine->m_float24);
	return 0;
}

// ?rva0034270C@Rva003426AB@@UAEXH@Z, retail 0x0034270C, 62 bytes.
// Virtual slot 5 (offset 0x14) of the same vtable 0x00812438: same machine
// chain, early-out on null, slot 0x238 with 0, slot 0x220, then copy
// mid+0x44 to mid+0x1C0. The 4-byte arg (ret 4) is never read; int/void are
// code-neutral guesses.

void Rva003426AB::rva0034270C(int)
{
	CEFinal *target = m_machine->m_ptr14->m_ptr258;
	if (target == 0)
		return;
	target->method238(0);
	target->method220();
	CEMid *mid = m_machine->m_ptr14;
	mid->m_1C0 = mid->m_44;
}
