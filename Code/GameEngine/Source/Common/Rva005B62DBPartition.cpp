// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B62DBPartition@@YAPAPAXPAPAX0PAXVRva005B61B3@@@Z @0x005B62DB 73B.
// Honest-address unguarded partition over void* elements with the rowed
// comparator at 0x5B61B3. While comp(first pivot) advances first; then
// pre-decrements last while comp(pivot last); returns first when first>=last
// else swaps and advances. Caller at 0x5B66D2; prev is the comparator TU.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void **Rva005B62DBPartition(void **first, void **last, void *pivot, Rva005B61B3 comp);

void **Rva005B62DBPartition(void **first, void **last, void *pivot, Rva005B61B3 comp)
{
	for (;;) {
		while (comp.rva005B61B3(*first, pivot))
			++first;
		--last;
		while (comp.rva005B61B3(pivot, *last))
			--last;
		if (first >= last)
			return first;
		void *tmp = *first;
		*first = *last;
		*last = tmp;
		++first;
	}
}
