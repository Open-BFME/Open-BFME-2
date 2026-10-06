// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B64B5Pop@@YAXPAPAX00PAXVRva005B61B3@@H@Z @0x005B64B5 44B.
// Honest-address pop heap helper over void* elements with the rowed
// comparator. Moves *first to *result then adjusts [first last) of the
// computed length with hole 0 via the rowed adjust at 0x5B6409. Takes a
// trailing dummy to match the 7-push callers at 0x5B653A and 0x5B6645.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B6409Heap(void **first, int hole, int len, void *val, Rva005B61B3 comp);
void Rva005B64B5Pop(void **first, void **last, void **result, void *val, Rva005B61B3 comp, int dummy);

void Rva005B64B5Pop(void **first, void **last, void **result, void *val, Rva005B61B3 comp, int dummy)
{
	*result = *first;
	int len = (int)(last - first);
	Rva005B6409Heap(first, 0, len, val, comp);
}
