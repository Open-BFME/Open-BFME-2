// cl: /O1 /DNDEBUG /MD
//
// ?rva0026D3FB@AIUpdateInterface@@QAEXPAVObject@@@Z, retail 0x0026D3FB..
// 0x0026D478 (125 bytes, RET 4): the AI method HordeMeleeAmoeba::AttackUnit
// (0x00587282) and 0x00295C5B call with a victim. When the current state
// (rowed 0x00260DED) is 0x21 or 0x3D, or the +0x30 machine's current state is
// absent or ready (its slot 9), the victim goes to the rowed 0x00262B0F and
// the path is dropped (rowed destroyPath) unless the pinned 0x00344EB2 gate
// holds for the +0x08 owner; otherwise, without the +0x34 guard, the +0x20
// command interface attacks it (rowed 0x0026C2D9, all shots, from the AI).
// The machine's ready test is an inline helper, which keeps retail's
// materialised true for an absent state.
class Object;
class Thing;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class MiniState
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual bool isReady();
};

class MiniMachine
{
public:
	virtual void m00();
	bool isCurrentReady() const { return m_current ? m_current->isReady() : true; }
	MiniState *m_current;
};

class AICommandInterface
{
public:
	void rva0026C2D9(Object *victim, int maxShots, CommandSourceType src);
private:
	char m_data[0x10];
};

bool rva00344EB2Gate(Object *a, Thing *b);

class AIUpdateInterface
{
public:
	int rva00260DED() const;
	void rva00262B0F(int v);
	void destroyPath();
	void rva0026D3FB(Object *victim);
private:
	char m_pad00[0x8];
	Object *m_owner;
	char m_pad01[0x20 - 0x0C];
	AICommandInterface m_cmd;
	MiniMachine *m_machine;
	int m_34;
};

void AIUpdateInterface::rva0026D3FB(Object *victim)
{
	int cur = rva00260DED();
	bool flag = (cur == 0x21 || cur == 0x3D);
	if (m_machine->isCurrentReady() || flag)
	{
		rva00262B0F((int)victim);
		Object *owner = m_owner;
		if (!rva00344EB2Gate(owner, (Thing *)victim))
			destroyPath();
	}
	else if (m_34 == 0)
		m_cmd.rva0026C2D9(victim, 0x7fffffff, CMD_FROM_AI);
}
