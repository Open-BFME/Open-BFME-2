// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B6409Heap@@YAXPAPAXHHPAXVRva005B61B3@@@Z @0x005B6409 97B.
// Honest-address adjust heap over void* elements with the rowed comparator.
// Downward child selection then delegates to the rowed push at 0x5B6353.
// Callers at 0x5B64D7 and 0x5B6510; prev is aux TU with /O1 flags.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B6353Adjust(void **first, int holeIndex, int topIndex, void *val, Rva005B61B3 comp);
void Rva005B6409Heap(void **first, int hole, int len, void *val, Rva005B61B3 comp);

void Rva005B6409Heap(void **first, int hole, int len, void *val, Rva005B61B3 comp)
{
	int top = hole;
	int child = hole * 2 + 2;
	while (child < len) {
		if (comp.rva005B61B3(*(first + child), *(first + child - 1)))
			--child;
		*(first + hole) = *(first + child);
		hole = child;
		child = child * 2 + 2;
	}
	if (child == len) {
		*(first + hole) = *(first + child - 1);
		hole = child - 1;
	}
	Rva005B6353Adjust(first, hole, top, val, comp);
}
