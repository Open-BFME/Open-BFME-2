// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073C820Raster@@YADHHHVRva0073BBE0@@@Z 155B @0x0073C820: shroud circle raster via rowed 0x0073BBE0 updater twin of 0x0073BF40/0x0073C3B0 but BBE0 adjust. Midpoint-circle with per-row gate rowed rva0073BBE0 checked test al fail 1 full sweep 0 early out ret 0 is centerXY radius updater. Evidence: twin shape plus rowed 0x0073BBE0 plus caller at 0x0073CED8.
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
};

class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Element;

class Rva0073BBE0
{
public:
	char rva0073BBE0(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
	int m_counterIndex;
	int m_amount;
};

char __cdecl Rva0073C820Raster(int centerX, int centerY, const int radius, Rva0073BBE0 updater)
{
	int x = 0;
	int y = radius;
	int d = (1 - radius) << 1;
	int firstX = centerX;
	int lastX = centerX;

	for (;;)
	{
		if (d + y > 0)
		{
			if (y == 0 && radius == 1)
			{
				++x;
				++lastX;
				--firstX;
			}

			if (!updater.rva0073BBE0(firstX, lastX, centerY + y))
				return 0;
			if (y == 0)
				return 1;

			if (!updater.rva0073BBE0(firstX, lastX, centerY - y))
				return 0;
			--y;
			d -= ((y << 1) - 1);
		}

		if (x > d)
		{
			++x;
			++lastX;
			--firstX;
			d += ((x << 1) + 1);
		}
	}
}
