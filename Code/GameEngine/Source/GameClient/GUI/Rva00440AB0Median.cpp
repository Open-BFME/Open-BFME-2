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

void **Rva00440AB0Median(void **first, void **second, void **third, Rva0043FE9A comp)
{
	if (comp.rva0043FE9A((MapMetaData *)*first, (MapMetaData *)*second)) {
		if (comp.rva0043FE9A((MapMetaData *)*second, (MapMetaData *)*third))
			return second;
		else if (comp.rva0043FE9A((MapMetaData *)*first, (MapMetaData *)*third))
			return third;
		else
			return first;
	} else {
		if (comp.rva0043FE9A((MapMetaData *)*first, (MapMetaData *)*third))
			return first;
		else if (comp.rva0043FE9A((MapMetaData *)*second, (MapMetaData *)*third))
			return third;
		else
			return second;
	}
}

// ?Rva005B6270Median@@YAPAPAXPAPAX00VRva005B61B3@@@Z, retail 0x005B6270, 107 bytes:
// the same median of three over the rowed Rva005B61B3 comparator (same 8-byte
// by-value layout); only the five compare calls differ from Rva00440AB0Median.
#include "../../../Include/Common/Rva005B61B3.h"
void **Rva005B6270Median(void **first, void **second, void **third, Rva005B61B3 comp)
{
	if (comp.rva005B61B3(*first, *second)) {
		if (comp.rva005B61B3(*second, *third))
			return second;
		else if (comp.rva005B61B3(*first, *third))
			return third;
		else
			return first;
	} else {
		if (comp.rva005B61B3(*first, *third))
			return first;
		else if (comp.rva005B61B3(*second, *third))
			return third;
		else
			return second;
	}
}
