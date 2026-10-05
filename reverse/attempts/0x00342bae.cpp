// ??0Rva00342BAE@@QAE@PAVStateMachine@@_N@Z
// partial score=0.85 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
//
// AIInternalMoveToState-derived state ctors, retail 0x00342BAE (70B),
// 0x00342C47 (28B), 0x00342D19 (34B).
//
// Same chained-ctor shape as AIStateMoveTightenCtors.cpp (verified first
// try there): the mid forwards (machine, flag) to the AIInternalMoveToState
// pin 0x0033F279, then installs its vtable and zeroes float/int/bool
// members in source order; the leaves forward to the mid pin. The mid's
// true extent runs to the ret-8 at 0x00342BF3 (Ghidra's 33B extent stops
// at the first movss run and is short). 0x00342C47 forwards both args;
// 0x00342D19 passes a 0 flag. Hierarchy views mirror the family-1 TU.

class StateMachine;
struct Coord3D
{
	float x, y, z;
};
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
class Rva00342BAE : public AIInternalMoveToState
{
public:
	Rva00342BAE(StateMachine *machine, bool flag);
private:
	float m_4c;
	float m_50;
	float m_54;
	int m_58;
	int m_5c;
	int m_60;
	bool m_64;
	bool m_65;
	bool m_66;
};
class Rva00342C47 : public Rva00342BAE
{
public:
	Rva00342C47(StateMachine *machine, bool flag);
};
class Rva00342D19 : public Rva00342BAE
{
public:
	Rva00342D19(StateMachine *machine);
private:
	int m_68;
	int m_6c;
};

Rva00342BAE::Rva00342BAE(StateMachine *machine, bool flag)
	: AIInternalMoveToState(machine, 0x6CE5EF54u),
		m_4c(0.0f), m_50(0.0f), m_58(0), m_5c(0), m_60(0), m_64(false),
		m_65(flag)
{
	m_54 = 0.0f;
	m_66 = true;
}

Rva00342C47::Rva00342C47(StateMachine *machine, bool flag)
	: Rva00342BAE(machine, flag)
{
}

Rva00342D19::Rva00342D19(StateMachine *machine)
	: Rva00342BAE(machine, false)
{
	m_68 = 0;
	m_6c = 0;
}
