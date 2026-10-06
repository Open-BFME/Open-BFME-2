// cl: /DNDEBUG /MD /EHsc
// ?rva0039B683@Rva0039B683@@QAEXM@Z @0x0039B683 37B, call sites 0x002AA6BD
// (ecx = lea esi+0x3BC) and 0x002AA736. Adds the float argument to +0xF8
// while TheGameLogic's byte at +0x98 is set.
// Target evidence: TheGameLogic is the global at 0x00DFE78C whose
// findObjectByID calls other matched bodies make; retail loads the argument
// first and adds the member from memory (delta + m_valF8).
class GameLogic
{
public:
	char m_pad00[0x98];
	unsigned char m_flag98; // +0x98
};

extern GameLogic *TheGameLogic;

class Rva0039B683
{
public:
	void rva0039B683(float delta);
private:
	char m_pad00[0xF8];
	float m_valF8; // +0xF8
};

void Rva0039B683::rva0039B683(float delta)
{
	if (TheGameLogic->m_flag98 == 0)
		return;
	m_valF8 = delta + m_valF8;
}
