// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva0020D451@Rva0020D451Engine@@QAEXABVAsciiString@@PAX11PAVTeam@@@Z @0x0020D451 140B.
// Thiscall run-with-guard: a stack Rva002048A2 guard swaps the engine's string
// slot at +0x1A10C with the argument (restored by its virtual dtor), stores the
// team at +0x1A110 and its controlling player at +0x1A130 (both restored after),
// then runs the unrowed thiscall 0x0020C5C7 with the three pointer arguments.
// Evidence: target only; names are address-derived.
#include "ascii_string.h"

struct Rva002048A2
{
	virtual ~Rva002048A2();
	AsciiString m_str;
	AsciiString *m_alias;
	Rva002048A2(AsciiString *a1, const AsciiString &a2);
};

class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Rva0020D451Engine
{
public:
	void rva0020D451(const AsciiString &name, void *a, void *b, void *c, Team *team);
	void rva0020C5C7(void *a, void *b, void *c);

private:
	char m_pad0000[0x1A10C];
	AsciiString m_1A10C;
	Team *m_1A110;
	char m_pad1114[0x1A130 - 0x1A114];
	Player *m_1A130;
};

void Rva0020D451Engine::rva0020D451(const AsciiString &name, void *a, void *b, void *c, Team *team)
{
	Team *savedTeam = m_1A110;
	Player *savedPlayer = m_1A130;
	Rva002048A2 guard(&m_1A10C, name);
	m_1A130 = 0;
	m_1A110 = team;
	if (team)
		m_1A130 = team->getControllingPlayer();
	rva0020C5C7(a, b, c);
	m_1A110 = savedTeam;
	m_1A130 = savedPlayer;
}
