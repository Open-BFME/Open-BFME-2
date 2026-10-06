// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B63E4Sort@@YAXPAPAX00VRva005B61B3@@@Z @0x005B63E4 37B.
// Honest-address free function: unguarded insertion sort aux over void*
// elements using the rowed comparator cluster. Loops i=first..last calling
// the rowed unguarded insert at 0x5B6324. Caller at 0x5B64AC; prev is the
// insert TU with the same /O1 flags.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B6324Insert(void **last, void *val, Rva005B61B3 comp);
void Rva005B63E4Sort(void **first, void **last, void **dummy, Rva005B61B3 comp);

void Rva005B63E4Sort(void **first, void **last, void **dummy, Rva005B61B3 comp)
{
	for (void **i = first; i != last; ++i)
		Rva005B6324Insert(i, *i, comp);
}
