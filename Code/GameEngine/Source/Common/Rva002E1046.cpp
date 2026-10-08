// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002E1046@Rva002E1046@@QAE_NXZ @0x002E1046 119B: thiscall bool scan over
// LivingWorld players via rowed rva002B52A8 plus pinned helper 0x002E0BC0.
// Evidence: packet disasm with rowed find 0x002B52A8 via g_009FEF10 plus
// pinned rva002E0BC0 plus byte flag at +0x3c4 on self and player, caller
// 0x00520A28, neighbours Rva002E1001 and Rva002E0CD4Get with /O1.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player
{
public:
	char m_pad00[0x14];
	int m_14;
	char m_pad18[0x3c4 - 0x18];
	unsigned char m_3c4;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
	struct PlayerList
	{
		Rva002E2903Player **m_begin;
		Rva002E2903Player **m_end;
		Rva002E2903Player **m_storage;
		int size() const { return m_end - m_begin; }
	};
	char m_gap00[0x8c];
	PlayerList m_players8c;
};

// The native provider normalizes its bool result with movzx eax,al at
// 0x002E0BE0. Keep each caller's byte-sized test while naming its int ABI.
class Rva002E071E
{
public:
	int rva002E0BC0(int v);
};

class Rva002E1046
{
public:
	bool rva002E1046();
private:
	char m_pad00[0x3c4];
	unsigned char m_3c4;
};

bool Rva002E1046::rva002E1046()
{
	if (m_3c4 != 0)
		return false;
	for (int i = 0; i < (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_players8c.size(); i++)
	{
		Rva002E2903Player *p1 = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
		if ((unsigned char)((Rva002E071E *)this)->rva002E0BC0(p1->m_14))
			continue;
		Rva002E2903Player *p2 = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B52A8(i);
		if (p2->m_3c4 == 0)
			return true;
	}
	return false;
}
