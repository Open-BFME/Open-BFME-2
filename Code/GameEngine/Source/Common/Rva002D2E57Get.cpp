// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?ComputeFrameState@@YAHXZ @0x002D2E57 101B
// Evidence: globals g_009FEF10 TheGameLogic ThePlayerList g_00E02D6C plus rowed isSelectionLocked rva0042219 bfmePickRV; caller 0x002D666B; neighbours Rva002D2D13Calls/Rva002D317CCalls.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002BA8F1Logic;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

struct Rva00E02D6CFlags
{
	char m_pad[0x2C];
	unsigned char m_2C;
};
class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

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

int __cdecl ComputeFrameState()
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) && ((const BfmeSelectionState *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->isSelectionLocked())
	{
		return ((Rva00E02D6CFlags *)TheCampaignManager)->m_2C ? 4 : 2;
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
