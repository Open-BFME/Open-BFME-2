// ?rva005E56FC@Rva005E56FC@@QAEPAXXZ
// partial score=0.92 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva005E56FC@Rva005E56FC@@QAEPAXXZ @0x005E56FC 78B.
// View then player then stdcall chain with redundant mov ecx before stdcall.
// Evidence: thiscall ret 0 no args returning void pointer; global g_009FEF10
// view at +0xB0 rowed 0x0020EAF6 with this+8; id chain this+4 then +0x18 +0x54;
// find rowed 0x002B51F8; stdcall rowed 0x002B4948; shared xor eax null path.
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);
};
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
public:
	char m_pad[0xB0];
	Rva0020EAF6View *m_B0;
};
extern Rva002BA8F1Logic *g_009FEF10;
void *__stdcall Rva002B4948Find(void *a1, void *a2, void *a3);
struct Rva005E56FCIdInner
{
	char m_pad[0x54];
	int m_id54;
};
struct Rva005E56FCOuter
{
	char m_pad[0x18];
	Rva005E56FCIdInner *m_ptr18;
};
class Rva005E56FC
{
public:
	void *rva005E56FC();
private:
	int m_00;
	Rva005E56FCOuter *m_04;
	int m_08;
};
// ?rva005E56FC@Rva005E56FC@@QAEPAXXZ present-unmatched
void *Rva005E56FC::rva005E56FC()
{
	Rva0020E89C *view = g_009FEF10->m_B0->rva0020EAF6(m_08);
	if (view != 0)
	{
		int id = m_04->m_ptr18->m_id54;
		Rva002E2903Player *player = g_009FEF10->find(id, 0);
		if (player != 0)
			return Rva002B4948Find(player, view, 0);
	}
	return 0;
}
