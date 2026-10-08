// cl: /O1 /G7 /EHsc /MD
// Heap helpers of the introsort family in Rva005810B6Sort.cpp.
// ?Rva005807CE@@YAXPAPAXHHPAXVRva000795C1Record@@@Z @0x005807CE 116B: cdecl push-heap worker.
//   Moves the hole up through parents while the comparator orders the parent before the value,
//   then stores the value. Comparator is the address-named Rva000795C1Record::compareRva005803C0.
// ?Rva00580E10@@YAXPAPAX0VRva000795C1Record@@@Z @0x00580E10 79B: cdecl pop-heap step.
//   Passes the comparator by value into the rowed Rva00580CE2 with a null third argument;
//   the by-value temporary carries the EH frame.
void __cdecl free(void *);

class Rva000795C1Record
{
	unsigned int key;
	void *first, *last, *end;
public:
	Rva000795C1Record(const Rva000795C1Record &);
	bool compareRva005803C0(void *, void *) const;
	~Rva000795C1Record() { if (first) free(first); }
};

void __cdecl Rva00580CE2(void **first, void **last, void **, Rva000795C1Record compare);

void __cdecl Rva005807CE(void **first, int hole, int top, void *value, Rva000795C1Record compare)
{
	int parent = (hole - 1) / 2;
	while (hole > top && compare.compareRva005803C0(*(first + parent), value)) {
		*(first + hole) = *(first + parent);
		hole = parent;
		parent = (hole - 1) / 2;
	}
	*(first + hole) = value;
}

void __cdecl Rva00580E10(void **first, void **last, Rva000795C1Record compare)
{
	Rva00580CE2(first, last, (void **)0, compare);
}
