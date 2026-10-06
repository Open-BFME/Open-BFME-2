// cl: /DNDEBUG /MD
// ?rva00395A82@Rva00395A82@@QAEMXZ RVA 0x00395A82 size 29 leaf float 1-minus-divide else zero.
extern const float BfmeZeroRange;
extern float g_Va00BBB8D8;
struct Rva00395A82Inner
{
	char m_pad[32];
	float m_20;
};
class Rva00395A82
{
public:
	float rva00395A82();
	char m_pad0[4];
	Rva00395A82Inner *m_04;
	char m_pad1[44];
	int m_34;
	char m_pad2[8];
	float m_40;
};
float Rva00395A82::rva00395A82()
{
	if (m_34 == 0)
		return g_Va00BBB8D8 - (m_40 / m_04->m_20);
	return BfmeZeroRange;
}
