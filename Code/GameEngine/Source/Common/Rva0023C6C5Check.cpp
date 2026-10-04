// cl: /O1 /DNDEBUG /MD
//
// ?rva0023C6C5@BfmeGlob939D@@QAEDXZ @0x0023C6C5, 56B.
// Multiplayer-plus-helper predicate: true when in a multiplayer game, else
// needs helper behind 0x00E02290 with getData()==1 and helper state at
// +0xE74 of 1 or 5. Same GameLogic base call, global and +0xE74 as neighbour
// BfmeGlob939D::bfmeCall939D at 0x0023C6FD without its mode==2 check.
// Evidence: thiscall via isInMultiplayerGame row, getData row 0x0030F2C7,
// g_bfme939Helper VA 0x00E02290, state 1/5 tail.

class GameLogic
{
	char m_pad[0x110];
public:
	int m_gameMode;
	bool isInMultiplayerGame();
};

class BfmeGlob939D : public GameLogic
{
public:
	char rva0023C6C5();
};

struct Bfme939Helper
{
	char m_pad[0xE74];
	int m_state; // +0xE74
};

extern Bfme939Helper *g_bfme939Helper;

class NetWrapperCommandMsg
{
public:
	unsigned char *getData();
};

char BfmeGlob939D::rva0023C6C5()
{
	if (isInMultiplayerGame())
		return 1;
	if (g_bfme939Helper != 0 && ((NetWrapperCommandMsg *)g_bfme939Helper)->getData() == (unsigned char *)1)
	{
		int state = g_bfme939Helper->m_state;
		if (state == 1 || state == 5)
			return 1;
		return 0;
	}
	return 0;
}
