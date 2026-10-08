// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E0A58@Rva004E0705@@QAE_NXZ @0x004E0A58 62B.
// Refresh the Rva004E0705 gate state: snapshot the world m_FC id into m_1C
// with m_20 armed to -1, run the pinned 0x0052B10F sweep on the +0x2C
// target, then re-run the rowed 0x004E08A9 gate; on success dispatch slot
// 0x20 on the target with (1 0) and report true.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002BA8F1Logic;

struct Rva004E08A9World
{
	char m_pad[0x98];
	void *m_98;
	char m_pad9C[0xFC - 0x9C];
	int m_FC;
};

class Rva0052B10F
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7();
	virtual void vf8(int a, int b);
	void rva0052B10F();
};

struct Rva004E0705Inner
{
	char m_pad[0x13C];
	int m_id;
};

class Rva002E2903Player;

class Rva004E0705
{
public:
	bool rva004E08A9(bool check);
	bool rva004E0A58();
	char m_pad1C[0x1C];
	int m_1C;
	int m_20;
	Rva004E0705Inner *m_ptr;
	char m_pad28[0x2C - 0x28];
	Rva0052B10F *m_2C;
};

bool Rva004E0705::rva004E0A58()
{
	int id = ((Rva004E08A9World *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->m_FC;
	m_20 = -1;
	m_1C = id;
	m_2C->rva0052B10F();
	bool ok = rva004E08A9(false);
	if (ok)
		m_2C->vf8(1, 0);
	return ok;
}
