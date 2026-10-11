// cl: /MD
struct Rva0028ECDBAux
{
	unsigned char m_pad[0x11F];
	unsigned char m_11F;
	unsigned char m_pad2[0x123 - 0x120];
	unsigned char m_123;
};
struct Rva002E9897Host;
struct Rva002DFF0F8
{
	unsigned char m_pad[0x10];
	Rva002E9897Host *m_10;
};
class AI;
extern AI *TheAI;
class Rva002E9897Host
{
public:
	bool IsWaterCell(void *a, int b);
};
// 0x002E9897 is rowed as Pathfinder::IsWaterCell (47B,
// PathfinderCellQueryPredicates.cpp; WB Pathfinder::IsWaterCell); the host
// class above is that same class under an address-derived name. This call
// goes through a TU-local Pathfinder view so it resolves to the rowed body
// instead of the unrowed spelling (sole U on this unit).
class Pathfinder
{
public:
	bool IsWaterCell(int a, int b);
};
class Rva0028ECDBHost
{
public:
	bool rva0028ECDB(void *a);
private:
	unsigned char m_pad[4];
	Rva0028ECDBAux *m_04;
	unsigned char m_pad2[0x250 - 0x8];
	int m_250;
};
// ?rva0028ECDB@Rva0028ECDBHost@@QAE_NPAX@Z
bool Rva0028ECDBHost::rva0028ECDB(void *a)
{
	Rva0028ECDBAux *aux = m_04;
	if ((aux->m_11F & 0x80) != 0 && (aux->m_123 & 2) != 0 && m_250 != 0 && !((Pathfinder *)((Rva002DFF0F8 *)TheAI)->m_10)->IsWaterCell((int)a, 1))
		return true;
	return false;
}
