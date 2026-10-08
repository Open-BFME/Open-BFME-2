// ?onEnter@Rva0033FE65@@UAE?AW4StateReturnType@@XZ
// partial score=0.95 date=2026-09-30
// cl: /MD
//
// ?onEnter@Rva0033FE65@@UAE?AW4StateReturnType@@XZ retail 0x00346FD0 170 bytes.
// AIIdleState::onEnter via vtable slot 4 of 0x00811E08 (class of
// ??0Rva0033FE65). BFME1 donor AIStates.cpp AIIdleState::onEnter plus BFME2
// debug logging. Callers 0x0034BD12. Callees rowed AIUpdateInterface
// rva00263025 plus fprintf plus GetGameLogicRandomValue. Externs
// theLogicRandomLogFile plus g_Rva0107301CEmptyString plus g_00E01E04.
// Layout from Rva0033FE65Ctor (State base plus m_20 m_22 m_24 m_25).
enum StateReturnType { STATE_CONTINUE = 0 };
class StateMachine;
class AIUpdateInterface
{
public:
	void rva00263025();
};
struct SubP00346FD0
{
	char m_pad00[0x64];
	const char *m_nameBase;
	char m_pad68[0x635 - 0x68];
	bool m_flag635;
};
struct SubQ00346FD0
{
	char m_pad00[0x20];
	int m_bits20;
};
struct Owner00346FD0
{
	char m_pad00[4];
	SubP00346FD0 *m_p04;
	char m_pad08[0x38 - 0x08];
	float m_x38;
	float m_y3c;
	float m_z40;
	char m_pad44[0x74 - 0x44];
	int m_id74;
	char m_pad78[0x240 - 0x78];
	SubQ00346FD0 *m_q240;
	char m_pad244[0x258 - 0x244];
	AIUpdateInterface *m_ai258;
};
class StateMachineDef
{
public:
	char m_pad00[0x14];
	Owner00346FD0 *m_owner14;
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
	StateMachineDef *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
extern "C" struct FILE_dummy00346FD0;
extern "C" void *theLogicRandomLogFile;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern int g_00E01E04;
// g_00E01E04: matched references place it at VA 0xe01e04 (zero-filled .bss).
int g_00E01E04;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);
int __cdecl GetGameLogicRandomValue(int a, int b, char *c, int d);
class __declspec(novtable) Rva0033FE65 : public State
{
public:
	virtual StateReturnType onEnter();
private:
	unsigned short m_20;
	unsigned short m_22;
	bool m_24;
	bool m_25;
};
StateReturnType Rva0033FE65::onEnter()
{
	Owner00346FD0 *obj = m_machine->m_owner14;
	AIUpdateInterface *ai = obj->m_ai258;
	m_22 = 5;
	if (ai)
		ai->rva00263025();
	m_25 = true;
	SubP00346FD0 *p = obj->m_p04;
	if (p->m_flag635) {
		SubQ00346FD0 *q = obj->m_q240;
		if (q)
			q->m_bits20 &= 0;
	}
	void *logFile = theLogicRandomLogFile;
	if (logFile) {
		unsigned int u = (unsigned int)obj->m_p04;
		int id = obj->m_id74;
		u += 0x64;
		_ReadWriteBarrier();
		const char *name = *(const char **)u;
		if (name)
			name = name + 8;
		else
			name = "";
		fprintf(logFile, "AIIdleState::onEnter() called for object %s(%d) at location %g,%g,%g.", name, id, obj->m_x38, obj->m_y3c, obj->m_z40);
	}
	m_20 = (unsigned short)GetGameLogicRandomValue(0, g_00E01E04, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\AIStates.cpp", 0x94A);
	return STATE_CONTINUE;
}
