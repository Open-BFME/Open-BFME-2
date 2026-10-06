// cl: /DNDEBUG /MD
//
// ?rva00263025@AIUpdateInterface@@QAEXXZ, retail 0x00263025, 40 bytes.
// Max-updater sibling of rva0026304D in the same AIUpdateInterface tail:
// computes TheGameLogic frame plus delay from 0x00DFF0F8 outer+0x18
// inner+0x14, keeps the max in +0x21C, then sets +0x3BC to 1.
// Callers at 0x346FEA 0x4D83E7. No direct callees.

extern class AI *TheAI;
extern class GameLogic *TheGameLogic;

struct Rva00DFF0F8Inner
{
	char m_pad00[0x14];
	unsigned int m_delay;
};

struct Rva00DFF0F8Outer
{
	char m_pad00[0x18];
	Rva00DFF0F8Inner *m_inner;
};

struct GameLogicFrame
{
	char m_pad00[0x40];
	unsigned int m_frame;
};

#define Rva00DFF0F8 (*(Rva00DFF0F8Outer **)&TheAI)
#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

class AIUpdateInterface
{
	char m_pad00[0x21C];
	unsigned int m_field21C;
	char m_pad220[0x3BC - 0x220];
	unsigned char m_flag3BC;
public:
	void rva00263025();
};

void AIUpdateInterface::rva00263025()
{
	Rva00DFF0F8Outer *outer = Rva00DFF0F8;
	Rva00DFF0F8Inner *inner = outer->m_inner;
	GameLogicFrame *logic = TheGameLogic;
	unsigned int val = inner->m_delay + logic->m_frame;
	if (val > m_field21C)
		m_field21C = val;
	m_flag3BC = 1;
}
