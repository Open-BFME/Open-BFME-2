// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00440B93Adjust@@YAXPAPAXHHPAXVRva0043FE9A@@@Z @0x00440B93 76B.
// Push-heap adjust with Rva0043FE9A comp: percolate val from hole toward top
// via parent (hole-1)/2 while comp(parent val). Evidence: caller 0x004419ED;
// prev shares /O1; mirrors Rva005B6353Adjust 76B.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00440B93Adjust(void **first, int holeIndex, int topIndex, void *val, Rva0043FE9A comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex) {
		if (!comp.rva0043FE9A((MapMetaData *)*(first + parent), (MapMetaData *)val))
			break;
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (parent - 1) / 2;
	}
	*(first + holeIndex) = val;
}
