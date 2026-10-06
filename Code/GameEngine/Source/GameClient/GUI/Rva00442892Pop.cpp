// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00442892Pop@@YAXPAPAX0VRva0043FE9A@@@Z @0x00442892 27B.
// Honest-address pop heap forwarder over void* elements. Forwards first last
// and a null dummy plus comp to the rowed pop at 0x00441E2B. Mirrors
// Rva005B65ADPop 27B. Evidence: callee rowed 0x00441E2B; caller 0x00442BB1.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void Rva00441E2BPop(void **first, void **last, void **dummy, Rva0043FE9A comp);
void Rva00442892Pop(void **first, void **last, Rva0043FE9A comp)
{
	Rva00441E2BPop(first, last, 0, comp);
}
