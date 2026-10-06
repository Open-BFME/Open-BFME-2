// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva005B6324Insert@@YAXPAPAXPAXVRva005B61B3@@@Z @0x005B6324 47B.
// Honest-address free function: __unguarded_linear_insert for void* elements
// with the stateful comparator rowed at 0x5B61B3. Shifts while comp(val next)
// then stores val. Callers at 0x5B63D8 and 0x5B63F6; prev is the comparator
// TU with the same /O1 flags.

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a, void *b);
private:
	int m_key0;
	int m_key1;
};

void Rva005B6324Insert(void **last, void *val, Rva005B61B3 comp);

void Rva005B6324Insert(void **last, void *val, Rva005B61B3 comp)
{
	void **next = last - 1;
	while (comp.rva005B61B3(val, *next)) {
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}
