// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B6353Adjust@@YAXPAPAXHHPAXVRva005B61B3@@@Z @0x005B6353 76B.
// Honest-address adjust heap over void* elements with the rowed comparator
// at 0x5B61B3. Percolates value from holeIndex toward topIndex via parent
// (hole-1)/2 while comp(parent value). Caller at 0x5B645D; prev is insert.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B6353Adjust(void **first, int holeIndex, int topIndex, void *val, Rva005B61B3 comp);

void Rva005B6353Adjust(void **first, int holeIndex, int topIndex, void *val, Rva005B61B3 comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex) {
		if (!comp.rva005B61B3(*(first + parent), val))
			break;
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (parent - 1) / 2;
	}
	*(first + holeIndex) = val;
}
