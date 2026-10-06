// cl: /DNDEBUG /MD /EHsc
// ?rva002E7414@Rva002E7414@@QAEHHH@Z, retail 0x002E7414, 44 bytes.
// Layer-1 cell flag test via rowed Pathfinder::getCell 0x002E6D62, ret 8.
// Evidence: 5 callers in 0x002EAE5F, flags &0x3f0==0x10, layer 1.
enum PathfindLayerEnum
{
	PF_LAYER_0 = 0,
	PF_LAYER_1 = 1
};

class PathfindCell
{
public:
	char m_pad[12];
	int m_flags;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

class Rva002E7414
{
public:
	int rva002E7414(int x, int y);
private:
	class Pathfinder *m_pf;
};

int Rva002E7414::rva002E7414(int x, int y)
{
	PathfindCell *cell = m_pf->getCell(PF_LAYER_1, x, y);
	if (cell != 0) {
		if ((cell->m_flags & 0x3f0) == 0x10)
			return 1;
	}
	return 0;
}
