// cl: /EHsc /DNDEBUG /MD
// ?rva004DD9E3@Rva004DD9E3@@QAEHHHH@Z, RVA 0x004DD9E3, size 183.
// Evidence: getCell 0x002E6D62 plus Rva0052DBCDInit plus Rva002E8B7AInit plus
// rva004DD73B pool plus globals g_Va009FF0F8 TheMixFileInfoPool g_00E049D8;
// callers 0x004DDC94 0x004DDDDE unclaimed.
typedef int Int;

enum PathfindLayerEnum
{
	LAYER_0 = 0
};

class PathfindCell
{
public:
	void *m_buffer;
};

class MixFileInfoBuffer
{
public:
	char m_pad[0x14];
	void *m_arr[16];
};

struct In002E6BA1
{
	int m_00;
	int m_04;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_pathfinder;
};
extern class AI *TheAI;

extern int TheMixFileInfoPool;
void Rva0052DBCDInit(void);
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);

class Rva004DD73B
{
public:
	void *rva004DD73B();
};
extern unsigned int g_Va00E049D8;

struct Outer00
{
	char m_pad[0x14];
	PathfindCell *m_14;
};

struct Node16
{
	void *m_00;
	void *m_04;
	int m_08;
	PathfindCell *m_0C;
};

class Rva004DD9E3
{
public:
	int rva004DD9E3(int a1, int x, int y);
private:
	Outer00 *m_00;
	int m_04;
	int m_08;
	int m_layers[2];
};

int Rva004DD9E3::rva004DD9E3(int a1, int x, int y)
{
	(void)a1;
	int *layer = m_layers;
	for (int i = 0; i < 2; ++i, ++layer) {
		PathfindLayerEnum l = (PathfindLayerEnum)*layer;
		if (l == 0) {
			break;
		}
		Pathfinder *pf = TheAI->m_pathfinder;
		PathfindCell *cell = pf->getCell(l, x, y);
		if (cell == 0) {
			continue;
		}
		if (cell->m_buffer == 0) {
			In002E6BA1 in;
			in.m_00 = x;
			in.m_04 = y;
			if (TheMixFileInfoPool == 0) {
				Rva0052DBCDInit();
			}
			cell->m_buffer = Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (int)cell, &in);
		}
		Node16 *node = (Node16 *)reinterpret_cast<Rva004DD73B &>(g_Va00E049D8).rva004DD73B();
		node->m_0C = cell;
		node->m_08 = m_08;
		node->m_04 = ((Outer00 *)m_00)->m_14;
		node->m_00 = ((MixFileInfoBuffer *)cell->m_buffer)->m_arr[m_04];
		((MixFileInfoBuffer *)cell->m_buffer)->m_arr[m_04] = node;
		((Outer00 *)m_00)->m_14 = cell;
	}
	return 0;
}
