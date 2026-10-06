// cl: /DNDEBUG /MD /EHsc
// ?rva0039B64D@Rva0039B64D@@QAEXH@Z @0x0039B64D 27B
// Guarded accumulate: when TheGameLogic's byte flag at +0x98 is set, add the
// argument into this +0xD4. Evidence: global VA 0x00DFE78C already named
// TheGameLogic (?TheGameLogic@@3PAVGameLogic@@A, used by 72 TUs); ret 4 proves
// one int arg; ecx use proves __thiscall; caller class unproven so honest
// Rva0039B64D owner. Sibling pattern from 0x0039B632 (+0xD0) and 0x0039B683.

class GameLogic
{
public:
	unsigned char m_pad[0x98];
	bool m_flag98;
};

extern GameLogic *TheGameLogic;

class Rva0039B64D
{
public:
	void rva0039B64D(int amount);

private:
	char m_pad[0xD4];
	int m_valueD4;
};

void Rva0039B64D::rva0039B64D(int amount)
{
	if (TheGameLogic->m_flag98)
		m_valueD4 += amount;
}
