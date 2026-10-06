// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B646ASort@@YAXPAPAX0VRva005B61B3@@@Z @0x005B646A 48B.
// Honest-address insertion sort over void* elements. If first==last returns,
// else loops i=first+1..last calling the rowed guarded insert at 0x5B639F.
// Callers at 0x5B6562 and 0x5B6586; prev is the aux TU with /O1 flags.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B639FGuarded(void **first, void **last, void *val, Rva005B61B3 comp);
void Rva005B646ASort(void **first, void **last, Rva005B61B3 comp);

void Rva005B646ASort(void **first, void **last, Rva005B61B3 comp)
{
	if (first == last)
		return;
	for (void **i = first + 1; i != last; ++i)
		Rva005B639FGuarded(first, i, *i, comp);
}
