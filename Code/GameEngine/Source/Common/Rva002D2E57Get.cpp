// cl: /O1
//
// ?Rva002D2E57Get@@YAHXZ @0x002D2E57 101B
// Evidence: globals g_009FEF10 TheGameLogic ThePlayerList g_00E02D6C plus rowed isSelectionLocked rva0042219 bfmePickRV; caller 0x002D666B; neighbours Rva002D2D13Calls/Rva002D317CCalls.
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

struct Rva00E02D6C
{
	char m_pad[0x2C];
	unsigned char m_2C;
};
extern Rva00E02D6C *g_00E02D6C;

class GameLogic
{
public:
	bool rva0042219();
};
extern GameLogic *TheGameLogic;

class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};
class PlayerList;
extern PlayerList *ThePlayerList;

struct Inner1BC
{
	char m_pad[0x1BC];
	unsigned char m_1BC;
};

class BfmeMemberRV
{
public:
	char m_pad[0x34];
	Inner1BC *m_34;
};

int __cdecl Rva002D2E57Get()
{
	if (g_009FEF10 && ((const BfmeSelectionState *)g_009FEF10)->isSelectionLocked())
	{
		return g_00E02D6C->m_2C ? 4 : 2;
	}
	if (TheGameLogic && TheGameLogic->rva0042219())
	{
		BfmeMemberRV *m = ((BfmeThingRV *)ThePlayerList)->bfmePickRV();
		if (m)
		{
			Inner1BC *p = m->m_34;
			if (p)
			{
				return p->m_1BC ? 3 : 1;
			}
		}
	}
	return 1;
}
