// cl: /DNDEBUG /MD /EHsc
// ?rva0039B632@Rva0039B632@@QAEXH@Z @0x0039B632 27B
// Guarded accumulate: when TheGameLogic's byte flag at +0x98 is set, add the
// argument into this +0xD0. Evidence: global VA 0x00DFE78C already named
// TheGameLogic (?TheGameLogic@@3PAVGameLogic@@A, used by 72 TUs); ret 4 proves
// one int arg; ecx use proves __thiscall; caller class unproven so honest
// Rva0039B632 owner.

class GameLogic
{
public:
	unsigned char m_pad[0x98];
	bool m_flag98;
};

extern GameLogic *TheGameLogic;

class Rva0039B632
{
public:
	void rva0039B632(int amount);

private:
	char m_pad[0xD0];
	int m_valueD0;
};

void Rva0039B632::rva0039B632(int amount)
{
	if (TheGameLogic->m_flag98)
		m_valueD0 += amount;
}
