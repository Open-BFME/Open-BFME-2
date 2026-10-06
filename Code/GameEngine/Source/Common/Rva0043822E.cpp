// cl: /MD
//
// ?Rva0043822ESet@@YGXPAURva0043822EParam@@I@Z @0x0043822E 27B
// Leaf free __stdcall (ret 8, two stack args): total = GameLogic+0x40 plus
// arg2, keeps max into arg1+4 (cmp/jbe). TheGameLogic extern used by 72 TUs.
// Callers 0x00439809/0x00439ED9. Honest address name.
class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};
extern GameLogic *TheGameLogic;

struct Rva0043822EParam
{
	int m_00;
	unsigned int m_04;
};

void __stdcall Rva0043822ESet(Rva0043822EParam *p, unsigned int v)
{
	unsigned int total = TheGameLogic->m_40 + v;
	if (total > p->m_04)
		p->m_04 = total;
}
