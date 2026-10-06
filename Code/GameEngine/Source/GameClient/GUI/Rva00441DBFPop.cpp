// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00441DBFPop@@YAXPAPAX00PAXVRva0043FE9A@@@Z @0x00441DBF 44B.
// Pop heap with Rva0043FE9A comp: move *first to *result then adjust
// [first last) with hole 0. Evidence: callers 0x00441E44 0x00443018;
// callee rowed 0x00441999; mirrors Rva005B64B5Pop 44B.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00441999Heap(void **first, int hole, int len, void *val, Rva0043FE9A comp);

void Rva00441DBFPop(void **first, void **last, void **result, void *val, Rva0043FE9A comp)
{
	*result = *first;
	int len = (int)(last - first);
	Rva00441999Heap(first, 0, len, val, comp);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva00441DBFPop@@YAXPAPAX00PAXVRva0043FE9A@@H@Z=?Rva00441DBFPop@@YAXPAPAX00PAXVRva0043FE9A@@@Z")
