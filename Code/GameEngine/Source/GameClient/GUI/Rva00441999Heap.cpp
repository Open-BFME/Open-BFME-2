// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00441999Heap@@YAXPAPAXHHPAXVRva0043FE9A@@@Z @0x00441999 97B.
// Adjust heap with Rva0043FE9A comp then delegate to push adjust.
// Evidence: callers 0x00441DE1 0x00441E1A; callees rowed 0x0043FE9A
// 0x00440B93; mirrors Rva005B6409Heap 97B.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00440B93Adjust(void **first, int holeIndex, int topIndex, void *val, Rva0043FE9A comp);

void Rva00441999Heap(void **first, int hole, int len, void *val, Rva0043FE9A comp)
{
	int top = hole;
	int child = hole * 2 + 2;
	while (child < len) {
		if (comp.rva0043FE9A((MapMetaData *)*(first + child), (MapMetaData *)*(first + child - 1)))
			--child;
		*(first + hole) = *(first + child);
		hole = child;
		child = child * 2 + 2;
	}
	if (child == len) {
		*(first + hole) = *(first + child - 1);
		hole = child - 1;
	}
	Rva00440B93Adjust(first, hole, top, val, comp);
}
