// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B649ASort@@YAXPAPAX0VRva005B61B3@@@Z @0x005B649A 27B.
// Honest-address forwarder: unguarded insertion sort over void* elements.
// Forwards first last and a null Tp* dummy plus the 8-byte comparator to
// the rowed aux at 0x5B63E4. Caller at 0x5B6571; prev is the aux TU.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B63E4Sort(void **first, void **last, void **dummy, Rva005B61B3 comp);
void Rva005B649ASort(void **first, void **last, Rva005B61B3 comp);

void Rva005B649ASort(void **first, void **last, Rva005B61B3 comp)
{
	Rva005B63E4Sort(first, last, 0, comp);
}
