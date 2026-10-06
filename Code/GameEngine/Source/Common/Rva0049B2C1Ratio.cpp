// cl: /MD
// ?rva0049B2C1@Rva0049B2C1@@QAEMXZ @0x0049B2C1 66B
// Float progress via TheGameLogic+0x40 and +0x20/+0x24 diffs as unsigned
// fild plus fadd 2^32 pattern via g_00BC26EC then fdivp then g_Va00BBB8D8
// minus ratio. Evidence: rowed TheGameLogic plus float globals plus caller
// 0x0053E321 plus vtable 0x008392E0 slot 1.
class GameLogic
{
public:
	char m_pad[0x40];
	unsigned m_40;
};

extern GameLogic *TheGameLogic;
extern float g_00BC26EC;

class Rva0049B2C1
{
public:
	float rva0049B2C1();
private:
	char m_pad[0x20];
	unsigned m_20;
	unsigned m_24;
};

float Rva0049B2C1::rva0049B2C1()
{
	unsigned a = m_20 - TheGameLogic->m_40;
	unsigned b = m_20 - m_24;
	return 1.0f - (float)a / (float)b;
}
