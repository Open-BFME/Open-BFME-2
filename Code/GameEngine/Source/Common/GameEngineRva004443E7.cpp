// cl: /O1 /MD
//
// ?rva004443E7@GameEngine@@QAEXXZ, retail 0x004443E7 37B.
// Calls member at +0x288 slot 1 then global 0xDFE958 slot 0x48 then tail to GameEngine terminateChild.
// Evidence: add ecx 0x288 and call [eax+4]; mov ecx [0xDFE958] test and call [eax+0x48];
// mov ecx [0xDFE710 TheGameEngine] jmp to rowed _bfme_terminateChildProcesses 0x2260F7;
// callers at 0x44459D 0x444E7E 0x444EA4 0x444EE5 0x44666D.

extern struct Global009FE958 *g_Va009FE958;

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

extern class GameEngine *TheGameEngine;

class Member004443E7
{
public:
	virtual void s0();
	virtual void s1();
};

class Global004443E7958View
{
public:
	virtual void g0();
	virtual void g1();
	virtual void g2();
	virtual void g3();
	virtual void g4();
	virtual void g5();
	virtual void g6();
	virtual void g7();
	virtual void g8();
	virtual void g9();
	virtual void g10();
	virtual void g11();
	virtual void g12();
	virtual void g13();
	virtual void g14();
	virtual void g15();
	virtual void g16();
	virtual void g17();
	virtual void g18();
};

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

#define TheGlobal004443E7958 (*(Global004443E7958View **)&g_Va009FE958)
#define TheGameEngine004443E7 (*(class GameEngine **)&TheGameEngine)
#define TheInvoke00444E8ATarget (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)

// Free helpers the key handler below calls: 0x00444040 is rowed; 0x005116C2
// (110 bytes, no arguments, opens "Messenger.apt" when no messenger state
// exists) is unrowed and pinned by address; 0x00511730 is rowed.
void Rva00444040Enable();
void Rva005116C2();
void __cdecl Rva00511730(int unused);

struct Rva00511730State;
extern Rva00511730State *g_Va00E046B8;

class GameEngine
{
public:
	void rva004443E7();
	void rva00444E69(int unused);
	void rva00444E8A();
	int rva0044522D(int msg, unsigned char key, int flags);

private:
	void _bfme_terminateChildProcesses();
	char m_pad274[0x274];
	void *m_274Owner; // +0x274
	char m_pad278[0x288 - 0x278];
	Member004443E7 m_mem288; // +0x288
	char m_pad28C[0x54B - 0x28C];
	unsigned char m_54B; // +0x54B
	char m_pad54C[0x6A4 - 0x54C];
	int m_6A4; // +0x6A4
	char m_pad6A8[0x6C0 - 0x6A8];
	unsigned char m_6C0; // +0x6C0
};

void GameEngine::rva004443E7()
{
	m_mem288.s1();
	Global004443E7958View *g = TheGlobal004443E7958;
	if (g)
		g->g18();
	GameEngine *e = TheGameEngine004443E7;
	e->_bfme_terminateChildProcesses();
}

void GameEngine::rva00444E69(int unused)
{
	(void)unused;
	if (m_6A4 == 6)
		m_54B = 0;
	else {
		rva004443E7();
		m_6A4 = 0;
	}
}

void GameEngine::rva00444E8A()
{
	if (TheInvoke00444E8ATarget == 0)
		return;
	if (m_6A4 == 0)
		return;
	m_6A4 = 0;
	rva004443E7();
	Rva00222A8BTarget *t = TheInvoke00444E8ATarget;
	t->invoke(m_274Owner, "CancelGame", 0, 0, 0, 0, 0, 0);
}

// Retail 0x0044522D, 123 bytes: slot 1 of the LAN lobby screen's own vftable
// 0x00C3E0F8 (the object this view describes; the GameEngine label is the
// ledger's). Name unknown. Message 0x15 with +0x6C0 clear: key 0x1C/0x9C
// with flag 0x4 or 0x8 handles (and on flag 0x1 opens the messenger or saves
// its text); key 1 on flag 0x1 dispatches on +0x6A4 (1, or 4 and 9). Key 1
// is written first: retail shares the second case's return block.
int GameEngine::rva0044522D(int msg, unsigned char key, int flags)
{
	if (!m_6C0 && msg == 0x15)
	{
		switch (key)
		{
		case 1:
			if (flags & 1)
			{
				switch (m_6A4)
				{
				case 1:
					Rva00444040Enable();
					return 1;
				case 4:
				case 9:
					rva00444E69(0);
					return 1;
				}
			}
			break;
		case 0x1C:
		case 0x9C:
			if (flags & 0xC)
			{
				if (flags & 1)
				{
					if (!g_Va00E046B8)
						Rva005116C2();
					else
						Rva00511730(0);
				}
				return 1;
			}
			break;
		}
	}
	return 0;
}
