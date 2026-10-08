// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /Ireference/shims/bfme2_ascii
// ?MakeNormalBuff@BuffInstance@@QAE_NHHPAX0H@Z retail 0x00362518 171 bytes. Chain from 0x0030682A which this calls. Evidence: callers 0x0036284D, callees rowed rva00419BA5 and addBuff, float 1.0f, TheGameLogic, g_00DFF190.
class BuffLogic
{
public:
	void *addBuff(void *a, void *b);
};

extern class BuffLogic *g_00DFF190;

class Rva00419BA5
{
public:
	void rva00419BA5();
};

class GameLogic
{
public:
	char m_pad[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

struct DrawObj
{
	char m_pad[8];
	int m_08;
	float m_0C;
};

class BuffInstance
{
public:
	bool MakeNormalBuff(int a, int b, void *c, void *d, int e);
private:
	char m_pad0[4];
	bool m_04;
	char m_pad5[3];
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	DrawObj *m_18;
	void *m_1C;
};

bool BuffInstance::MakeNormalBuff(int a, int b, void *c, void *d, int e)
{
	if (a >= 9 || a < 1)
		return false;
	if (c == 0)
		return false;
	if (d == 0)
		return false;
	if (m_18 == 0)
	{
		m_08 = a;
		m_0C = b;
		m_1C = c;
		m_18 = (DrawObj *)((BuffLogic *)g_00DFF190)->addBuff(c, d);
	}
	else
	{
		if (c != m_1C)
		{
			((Rva00419BA5 *)m_18)->rva00419BA5();
			m_18 = 0;
			m_08 = a;
			m_0C = b;
			m_1C = c;
			m_18 = (DrawObj *)((BuffLogic *)g_00DFF190)->addBuff(c, d);
		}
		else if (m_18->m_08 == 2)
		{
			m_18->m_08 = 1;
			m_18->m_0C = 1.0f;
		}
	}
	if (m_18 != 0)
	{
		m_10 = e;
		m_04 = true;
		m_14 = TheGameLogic->m_40 + e;
		return true;
	}
	m_04 = false;
	return false;
}
