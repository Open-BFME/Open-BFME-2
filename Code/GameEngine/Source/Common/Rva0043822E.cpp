// cl: /MD
//
// ?rva0043822E@Rva00439E0C@@QAEXPAURva004393D6@@I@Z @0x0043822E 27B
// Leaf member of the invisibility manager view (ret 8, two stack args; `this`
// unread, so the former free __stdcall spelling had identical bytes): total =
// GameLogic+0x40 plus arg2, keeps the max into the record's +4 expiry
// (cmp/jbe). TheGameLogic extern used by 72 TUs. Callers 0x00439809/0x00439ED9
// and the ECX-preserving call in 0x0043979D. Honest address name.
class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};
extern GameLogic *TheGameLogic;

struct Rva004393D6
{
	void **node;
	unsigned int expiry;
	unsigned int refresh;
	unsigned int other;
};

class Rva00439E0C
{
public:
	void rva0043822E(Rva004393D6 *p, unsigned int v);
};

void Rva00439E0C::rva0043822E(Rva004393D6 *p, unsigned int v)
{
	unsigned int total = TheGameLogic->m_40 + v;
	if (total > p->expiry)
		p->expiry = total;
}
