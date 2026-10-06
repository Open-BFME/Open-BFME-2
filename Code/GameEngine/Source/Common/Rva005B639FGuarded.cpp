// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B639FGuarded@@YAXPAPAX0PAXVRva005B61B3@@@Z @0x005B639F 69B.
// Honest-address guarded linear insert over void* elements. If comp(val first)
// shifts via rowed __copy_trivial_backward at 0x620840 and stores val at
// first, else delegates to the rowed unguarded insert at 0x5B6324. Caller at
// 0x5B6486; prev is the insert TU with the same /O1 flags.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

namespace _STL
{
void * __copy_trivial_backward(const void *first, const void *last, void *result);
}

void Rva005B6324Insert(void **last, void *val, Rva005B61B3 comp);
void Rva005B639FGuarded(void **first, void **last, void *val, Rva005B61B3 comp);

void Rva005B639FGuarded(void **first, void **last, void *val, Rva005B61B3 comp)
{
	if (comp.rva005B61B3(val, *first)) {
		_STL::__copy_trivial_backward(first, last, last + 1);
		*first = val;
	}
	else {
		Rva005B6324Insert(last, val, comp);
	}
}
