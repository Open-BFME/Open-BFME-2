// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E08A9@Rva004E08A9@@QAE_N_N@Z 0x004E08A9 77: flag-gated player check.
// Evidence: rowed Rva004E0705::rva004E0705 plus rowed Rva002B2B66::rva002B2B66
// plus pin 0x002E0BC0 Rva002E071E::rva002E0BC0; callers 0x004E0A58
// 0x004E0CCB; global g_009FEF10 mangled ?g_009FEF10@@3PAVRva002BA8F1Logic@@A;
// this+0x1C int vs +0xFC and +0x98 Player* match Rva002B2B66 layout.
class Rva002E2903Player;

// The native provider normalizes its bool result with movzx eax,al at
// 0x002E0BE0. Keep each caller's byte-sized test while naming its int ABI.
class Rva002E071E
{
public:
	int rva002E0BC0(int val);
};

class Rva002BA8F1Logic
{
public:
	char m_pad98[0x98];
	Rva002E2903Player *m_98;
	char m_pad9C[0xFC - 0x9C];
	int m_FC;
};

extern Rva002BA8F1Logic *g_009FEF10;

class Rva004E0705
{
public:
	Rva002E2903Player *rva004E0705();
};

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class Rva004E08A9
{
private:
	char m_pad[0x1C];
	int m_1C;
public:
	bool rva004E08A9(bool flag);
};

bool Rva004E08A9::rva004E08A9(bool flag)
{
	if (!flag || m_1C < g_009FEF10->m_FC)
	{
		Rva002E2903Player *p = ((Rva004E0705 *)this)->rva004E0705();
		if (p != 0 && p != g_009FEF10->m_98)
		{
			if (!(unsigned char)((Rva002E071E *)p)->rva002E0BC0(((Rva002B2B66 *)g_009FEF10)->rva002B2B66()))
				return true;
		}
	}
	return false;
}
