// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00442828Final@@YAXPAPAX0VRva0043FE9A@@@Z @0x00442828 77B.
// Honest-address final insertion sort over void* elements. If byte size
// exceeds 0x40 sorts first 16 via rowed sort at 0x00441D74 then the tail via
// rowed sort at 0x00441DA4 else sorts whole range via 0x00441D74. Mirrors
// Rva005B6543Final 77B. Evidence: callees rowed 0x00441D74 0x00441DA4;
// caller 0x0044352C.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00441D74Sort(void **first, void **last, Rva0043FE9A comp);
void Rva00441DA4Sort(void **first, void **last, Rva0043FE9A comp);
void Rva00442828Final(void **first, void **last, Rva0043FE9A comp)
{
	int bytes = (char *)last - (char *)first;
	bytes &= -4;
	if (bytes > 0x40) {
		void **mid = first + 16;
		Rva00441D74Sort(first, mid, comp);
		Rva00441DA4Sort(mid, last, comp);
	}
	else {
		Rva00441D74Sort(first, last, comp);
	}
}
