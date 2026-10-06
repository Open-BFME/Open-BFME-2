// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B6543Final@@YAXPAPAX0VRva005B61B3@@@Z @0x005B6543 77B.
// Honest-address final insertion sort over void* elements. If byte size
// (last-first aligned) exceeds 0x40 sorts first 16 via rowed insertion sort
// at 0x5B646A then the tail via rowed unguarded sort at 0x5B649A, else sorts
// the whole range via insertion sort. Caller at 0x5B6749; prev is aux TU.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B646ASort(void **first, void **last, Rva005B61B3 comp);
void Rva005B649ASort(void **first, void **last, Rva005B61B3 comp);
void Rva005B6543Final(void **first, void **last, Rva005B61B3 comp);

void Rva005B6543Final(void **first, void **last, Rva005B61B3 comp)
{
	int bytes = (char *)last - (char *)first;
	bytes &= -4;
	if (bytes > 0x40) {
		void **mid = first + 16;
		Rva005B646ASort(first, mid, comp);
		Rva005B649ASort(mid, last, comp);
	}
	else {
		Rva005B646ASort(first, last, comp);
	}
}
