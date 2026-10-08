// cl: /O1 /G7 /EHsc /MD
// ?Rva00580C0E@@YAXPAPAX00PAXVRva000795C1Record@@0@Z @0x00580C0E 97B: cdecl heap pop helper.
// Stores the front element into the result slot, then descends the heap through the
// rowed adjust worker 0x00580AAC with the comparator copied by value. The comparator
// copy is an EH-framed temporary with the record destructor (free of its first pointer).
// Identities are address-derived; the sort family's record layout is the one from
// Rva005810B6Sort.cpp.
void __cdecl Rva00580AAC(void **, int, int, void *, class Rva000795C1Record);

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

void __cdecl Rva00580C0E(void **first, void **last, void **result, void *value, Rva000795C1Record compare, void **)
{
	*result = *first;
	Rva00580AAC(first, 0, (int)(last - first), value, compare);
}
