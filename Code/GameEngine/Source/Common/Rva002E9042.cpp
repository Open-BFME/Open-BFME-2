// cl: /MD
// ?rva002E9042@Rva002E9042@@QAEXPAX@Z retail 0x002E9042 93 bytes.
// Converts arg+0xC via WorldToCell 0x002E7875, gets Pathfinder cell 0x002E6D62 layer 1,
// clears via 0x0052DA63 and updates grid 0x0053155E when cell+4 matches arg, then clears byte at +0x48.
// Evidence: 6 unclaimed callers; callees all rowed; LINK BONUS 2 files 103B via 0x0046094C; layout from neighbours 0x002E8BCF and 0x002E9B31.
struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

ICoord2D *__cdecl Rva002E7875WorldToCell(ICoord2D *out, bool center, const Coord3D *pos);

enum PathfindLayerEnum
{
	PF_LAYER_0 = 0
};

class PathfindCell
{
public:
	char _00[4];
	void *m_04;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

class Rva0052DA63
{
public:
	void rva0052DA63(void *arg);
	char _00[4];
	void *m_04;
};

class Rva005312BE
{
public:
	void rva0053155E(int a, int b, bool add, int value);
};

struct Rva002E9042Arg
{
	char _00[0x0C];
	Coord3D m_0C;
	char _18[0x48 - 0x18];
	unsigned char m_48;
};

class Rva002E9042
{
public:
	void rva002E9042(void *p);
	void rva002E8FE5(void *p);
private:
	char m_pf[0x460];
	Rva005312BE m_grid;
};

void Rva002E9042::rva002E9042(void *p)
{
	Rva002E9042Arg *arg = (Rva002E9042Arg *)p;
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, true, &arg->m_0C);
	PathfindCell *c = ((Pathfinder *)this)->getCell((PathfindLayerEnum)1, cell.x, cell.y);
	if (c != 0 && ((Rva0052DA63 *)c)->m_04 == p)
	{
		((Rva0052DA63 *)c)->rva0052DA63(0);
		m_grid.rva0053155E(cell.x, cell.y, false, (int)p);
	}
	arg->m_48 = 0;
}

// ?rva002E8FE5@Rva002E9042@@QAEXPAX@Z @0x002E8FE5 93B: set twin of 0x002E9042; WorldToCell then getCell layer 1, fills via 0x0052DA63 and grid 0x0053155E when cell slot empty, sets byte at +0x48
void Rva002E9042::rva002E8FE5(void *p)
{
	Rva002E9042Arg *arg = (Rva002E9042Arg *)p;
	ICoord2D cell;
	Rva002E7875WorldToCell(&cell, true, &arg->m_0C);
	PathfindCell *c = ((Pathfinder *)this)->getCell((PathfindLayerEnum)1, cell.x, cell.y);
	if (c != 0 && ((Rva0052DA63 *)c)->m_04 == 0)
	{
		((Rva0052DA63 *)c)->rva0052DA63(p);
		m_grid.rva0053155E(cell.x, cell.y, true, (int)p);
	}
	arg->m_48 = 1;
}
