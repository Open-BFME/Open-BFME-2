// cl: /O1
//
// ?rva004E08A9@Rva004E0705@@QAE_N_N@Z @0x004E08A9 77B.
// Gate on the 0x004E0705 player lookup: when check is set and m_1C has reached
// TheLivingWorldLogic m_FC bail out; find the player via rowed 0x004E0705
// (this+0x24 id); reject null and the m_98 current entry; otherwise run the
// rowed 0x002B2B66 probe on the world and the pinned 0x002E0BC0 test on the
// player, succeeding only when the test returns zero.
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

struct Rva004E08A9World
{
	char m_pad[0x98];
	void *m_98;
	char m_pad9C[0xFC - 0x9C];
	int m_FC;
};

class Rva002E2903Player;

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(int v);
};

struct Rva004E0705Inner
{
	char m_pad[0x13C];
	int m_id;
};

class Rva004E0705
{
public:
	Rva002E2903Player *rva004E0705();
	bool rva004E08A9(bool check);
	char m_pad1C[0x1C];
	int m_1C;
	char m_pad20[0x24 - 0x20];
	Rva004E0705Inner *m_ptr;
};

bool Rva004E0705::rva004E08A9(bool check)
{
	Rva002E2903Player *p;
	if ((check == 0 || m_1C < ((Rva004E08A9World *)g_009FEF10)->m_FC)
		&& (p = rva004E0705()) != 0
		&& p != ((Rva004E08A9World *)g_009FEF10)->m_98
		&& ((Rva002E0BC0Helper *)p)->rva002E0BC0(((Rva002B2B66 *)(Rva004E08A9World *)g_009FEF10)->rva002B2B66()) == 0)
		return true;
	return false;
}
