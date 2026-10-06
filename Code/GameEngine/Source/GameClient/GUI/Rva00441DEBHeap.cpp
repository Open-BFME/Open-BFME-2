// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00441DEBHeap@@YAXPAPAX0VRva0043FE9A@@@Z @0x00441DEB 64B.
// Honest-address make heap over void* elements. Builds len from last-first
// then adjusts each hole from (len-2)/2 down to 0 via the rowed adjust at
// 0x00441999. Evidence: callee rowed 0x00441999; caller 0x00442889;
// neighbours 0x00441DBF 0x00441E2B cl /O1.
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
void Rva00441DEBHeap(void **first, void **last, Rva0043FE9A comp)
{
	int len = (int)(last - first);
	if (len < 2)
		return;
	for (int hole = (len - 2) / 2; ; --hole) {
		Rva00441999Heap(first, hole, len, *(first + hole), comp);
		if (hole == 0)
			break;
	}
}

// ?Rva005B64E1Heap@@YAXPAPAX0VRva005B61B3@@@Z, retail 0x005B64E1, 64 bytes: the
// same make-heap loop over the rowed Rva005B6409Heap adjust of the Rva005B61B3
// family; only that call differs from Rva00441DEBHeap.
class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};
void Rva005B6409Heap(void **first, int hole, int len, void *val, Rva005B61B3 comp);
void Rva005B64E1Heap(void **first, void **last, Rva005B61B3 comp)
{
	int len = (int)(last - first);
	if (len < 2)
		return;
	for (int hole = (len - 2) / 2; ; --hole) {
		Rva005B6409Heap(first, hole, len, *(first + hole), comp);
		if (hole == 0)
			break;
	}
}
