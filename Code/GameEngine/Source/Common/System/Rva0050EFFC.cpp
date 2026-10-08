// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0050EFFC@Rva0050F041@@QAEXH@Z @0x0050EFFC 69B
// SetState setter on Rva0050F041 layout: m_5c level m_60 name holder +8 m_74 state.
// Evidence: chain via rowed 0x0050E9FE AptCall; caller 0x0050FF48; sibling Rva0050F041;
// prefix empty g_Rva0107301CEmptyString else +8; function "SetState"; table 0x00C6556C;
// target TheRva00222A8BTarget 0x009FE4CC.
class Rva00222A8BTarget
{
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C6556C[];
int Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva0050F041Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Player
{
public:
	bool isLocalPlayer() const;
};

// The rowed method name is donor-derived. This view exists only to make the
// thiscall at 0x002AA231; the target pointer's class and the method's meaning
// remain unproven here.
class BfmeMemberRV
{
public:
	bool bfmeAskRV();
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class Rva0050F041
{
public:
	void rva0050EFFC(int state);
	void rva0050F306();
	void rva0050FF1C();
private:
	char m_pad00[0x5c];
	int m_5c;
	Rva0050F041Inner *m_60;
	Player *m_64;
	char m_pad68[0x0c];
	int m_74;
};

void Rva0050F041::rva0050EFFC(int state)
{
	if (state == m_74)
		return;
	const char *prefix = m_60 ? m_60->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_5c, prefix, "SetState", &g_00C6556C[state]);
	m_74 = state;
}

// ?rva0050FF1C@Rva0050F041@@QAEXXZ 57B @0x0050FF1C.
// Target facts: Ghidra bounds are 0x0050FF1C-0x0050FF54; the body calls
// rowed Player::isLocalPlayer, then calls rowed 0x002AA231 on the PlayerList
// local pointer and tail-jumps to 0x0050F306 after SetState. The only current
// row for 0x002AA231 has a donor-derived name and an unproven target meaning.
// Structural inference: the +0x64 pointer is a Player, and 0x0050F306 is the
// shared update path also called by the constructor at 0x0050FC54. The class
// and purpose of that update path remain address-named.
void Rva0050F041::rva0050FF1C()
{
	if (m_64->isLocalPlayer())
	{
		rva0050EFFC(1);
	}
	else
	{
		Player *localPlayer = ThePlayerList->m_localPlayer;
		if (localPlayer == 0 || !((BfmeMemberRV *)localPlayer)->bfmeAskRV())
			rva0050EFFC(2);
	}
	rva0050F306();
}
