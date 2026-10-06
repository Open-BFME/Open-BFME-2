// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00441E2BPop@@YAXPAPAX00VRva0043FE9A@@@Z @0x00441E2B 34B.
// Honest-address pop heap over void* elements. Decrements last then forwards
// first newLast newLast star-newLast and comp plus dummy 0 to the pop helper
// at 0x00441DBF. Mirrors Rva005B6521Pop 34B. Evidence: callee rowed 0x00441DBF;
// caller 0x004428A4; prev Pop TU cl /O1.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00441DBFPop(void **first, void **last, void **result, void *val, Rva0043FE9A comp, int dummy);
void Rva00441E2BPop(void **first, void **last, void **dummy, Rva0043FE9A comp)
{
	void **newLast = last - 1;
	Rva00441DBFPop(first, newLast, newLast, *newLast, comp, 0);
}
