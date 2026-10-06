// ?rva0026D3FB@AIUpdateInterface@@QAEXPAVObject@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva0026D3FB@AIUpdateInterface@@QAEXPAVObject@@@Z @0x0026D3FB 125B.
// AIUpdate state check then attack or reset path. Flag when current state 0x21 or 0x3D via rowed 0x00260DED; virtual slot 0x24 on machine+4 or true when null; if virtual true or flag then rowed 0x00262B0F plus gate 0x00344EB2 then destroyPath unless gate true; else when +0x34 zero call AICommandInterface +0x20 rowed 0x0026C2D9 with victim 0x7fffffff 2.
// Evidence: callees rowed 0x00260DED 0x00262B0F destroyPath 0x0026C2D9 pin gate 0x00344EB2; callers 0x00295C5B 0x00587282 push victim; +0x30 machine +0x20 cmd +0x08 owner +0x34 guard.
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
	MiniMachine *m = m_machine;
	unsigned char ok = 1;
	if (m->m_current != 0)
		ok = m->m_current->isReady();
	if (!ok && !flag)
	{
		if (m_34 != 0)
			return;
		m_cmd.rva0026C2D9(victim, 0x7fffffff, CMD_FROM_AI);
		return;
	}
	rva00262B0F((int)victim);
	Object *owner = m_owner;
	if (!rva00344EB2Gate(owner, (Thing *)victim))
		destroyPath();
}
