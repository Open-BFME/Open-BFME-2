// cl: /DNDEBUG /MD
//
// ?rva004D839A@Rva004D839A@@QAEXXZ, retail 0x004d839a, 55 bytes. Banked partial (score 0.93) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Evidence: unlock lane; caller 0x004D83D1 calls it; chain esi+0x18 -> +0x3c -> +8 -> lo/hi at +0x58/+0x5c; TheGameLogic+0x40 frame added; rowed GetGameLogicRandomValue; store to +0x20.

class GameLogic
{
	char m_pad[0x40];
	unsigned m_frame;

public:
	unsigned getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;

int __cdecl GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva004D839AC
{
	char m_pad[0x58];
	int m_lo;
	int m_hi;
};

struct Rva004D839AB
{
	char m_pad[8];
	Rva004D839AC *m_c;
};

struct Rva004D839AA
{
	char m_pad[0x3c];
	Rva004D839AB *m_b;
};

class Rva004D839A
{
	char m_pad[0x18];
	Rva004D839AA *m_a;
	int m_1C;
	unsigned m_20;

public:
	void rva004D839A();
};

void Rva004D839A::rva004D839A()
{
	unsigned frame = TheGameLogic->getFrame();
	Rva004D839AC *c = m_a->m_b->m_c;
	int hi = c->m_hi;
	int lo = c->m_lo;
	int r = GetGameLogicRandomValue(lo, hi, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\AI\\TurretAI.cpp", 0x524);
	m_20 = r + frame;
}
