// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00440AB0Median@@YAPAPAXPAPAX00VRva0043FE9A@@@Z @0x00440AB0 107B.
// Median-of-three with Rva0043FE9A comp (5 calls). Evidence: caller
// 0x004434A6; prev shares /O1; mirrors Rva0021B9A0Median branch shape.
class MapMetaData;

class Rva0043FE9A
{
public:
	bool rva0043FE9A(MapMetaData *a, MapMetaData *b);
private:
	int m_sort0;
	int m_sort1;
};

void **Rva00440AB0Median(void **a, void **b, void **c, Rva0043FE9A comp)
{
	if (comp.rva0043FE9A((MapMetaData *)*a, (MapMetaData *)*b)) {
		if (comp.rva0043FE9A((MapMetaData *)*b, (MapMetaData *)*c))
			return b;
		else if (comp.rva0043FE9A((MapMetaData *)*a, (MapMetaData *)*c))
			return c;
		else
			return a;
	} else {
		if (comp.rva0043FE9A((MapMetaData *)*a, (MapMetaData *)*c))
			return a;
		else if (comp.rva0043FE9A((MapMetaData *)*b, (MapMetaData *)*c))
			return c;
		else
			return b;
	}
}

// ?Rva005B6270Median@@YAPAPAXPAPAX00VRva005B61B3@@@Z, retail 0x005B6270, 107 bytes:
// the same median of three over the rowed Rva005B61B3 comparator (same 8-byte
// by-value layout); only the five compare calls differ from Rva00440AB0Median.
class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};
void **Rva005B6270Median(void **a, void **b, void **c, Rva005B61B3 comp)
{
	if (comp.rva005B61B3(*a, *b)) {
		if (comp.rva005B61B3(*b, *c))
			return b;
		else if (comp.rva005B61B3(*a, *c))
			return c;
		else
			return a;
	} else {
		if (comp.rva005B61B3(*a, *c))
			return a;
		else if (comp.rva005B61B3(*b, *c))
			return c;
		else
			return b;
	}
}
