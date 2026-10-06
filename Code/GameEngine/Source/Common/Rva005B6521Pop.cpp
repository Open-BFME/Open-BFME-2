// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B6521Pop@@YAXPAPAX00VRva005B61B3@@@Z @0x005B6521 34B.
// Honest-address pop heap over void* elements. Decrements last then forwards
// first newLast newLast star-newLast and comp plus dummy 0 to the rowed pop
// helper at 0x5B64B5. Caller at 0x5B65BF; prev is pop helper TU.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B64B5Pop(void **first, void **last, void **result, void *val, Rva005B61B3 comp, int dummy);
void Rva005B6521Pop(void **first, void **last, void **dummy, Rva005B61B3 comp);

void Rva005B6521Pop(void **first, void **last, void **dummy, Rva005B61B3 comp)
{
	void **newLast = last - 1;
	Rva005B64B5Pop(first, newLast, newLast, *newLast, comp, 0);
}
