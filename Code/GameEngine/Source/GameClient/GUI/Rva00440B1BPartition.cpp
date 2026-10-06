// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00440B1BPartition@@YAPAPAXPAPAX0PAXVRva0043FE9A@@@Z @0x00440B1B 73B.
// Unguarded partition with Rva0043FE9A comp: while comp(first pivot) advance;
// pre-decrement last while comp(pivot last); return first if >= else swap.
// Evidence: caller 0x004434B5; prev shares /O1; mirrors Rva005B62DBPartition.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void **Rva00440B1BPartition(void **first, void **last, void *pivot, Rva0043FE9A comp)
{
	for (;;) {
		while (comp.rva0043FE9A((MapMetaData *)*first, (MapMetaData *)pivot))
			++first;
		--last;
		while (comp.rva0043FE9A((MapMetaData *)pivot, (MapMetaData *)*last))
			--last;
		if (first >= last)
			return first;
		void *tmp = *first;
		*first = *last;
		*last = tmp;
		++first;
	}
}
