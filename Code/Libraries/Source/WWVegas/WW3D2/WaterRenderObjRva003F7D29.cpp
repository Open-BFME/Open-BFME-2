// cl: /MD
// ?rva003F7D29@Rva003F7D29@@QAEEXZ, retail 0x003F7D29 (24B).
// Evidence: unlock lane; caller 0x003F8052; offset 0x1c grid matches WaterRenderObjClass neighbour; plus8 equals 0xd early-out.
struct Rva003F7D29Grid
{
	virtual void rva0();
	virtual unsigned char rva4();
	virtual void rva8();
};

class Rva003F7D29
{
public:
	unsigned char rva003F7D29();
private:
	char m_00[8];
	int m_08;
	char m_0C[0x10];
	Rva003F7D29Grid *m_grid;
};

unsigned char Rva003F7D29::rva003F7D29()
{
	if (m_08 == 0xd)
		return 1;
	Rva003F7D29Grid *grid = m_grid;
	if (grid)
		return grid->rva4();
	return 0;
}
