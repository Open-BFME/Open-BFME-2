// cl: /O1 /G7 /EHsc /MD
//
// ?Rva00580776Insert@@YAXPAPAXPAXVRva000795C1Record@@@Z @0x00580776 88B
// Unguarded linear insert for the 0x00580xxx introsort family: shifts while
// rowed-pin compareRva005803C0(val,next) holds then stores val. By-value
// 16-byte Rva000795C1Record teardown (cmp frame+14 / free) and EH prolog
// match Rva005810B6Sort. Evidence: packet loop with lea esi [edi-4], two
// rowed callees plus pin, callers 0x00580A2B 0x00580A7C, prev/next rows.
void __cdecl free(void *);

namespace _STL
{
void *__copy_trivial_backward(const void *first, const void *last, void *result);
}

class Rva000795C1Record
{
public:
	unsigned int key;
	void *first;
	void *last;
	void *end;
public:
	Rva000795C1Record(const Rva000795C1Record &other);
	bool compareRva005803C0(void *a, void *b) const;
	~Rva000795C1Record() { if (first) free(first); }
};

void __cdecl Rva00580776Insert(void **last, void *val, Rva000795C1Record compare)
{
	void **cur = last;
	void **prev = last - 1;
	while (compare.compareRva005803C0(val, *prev))
	{
		*cur = *prev;
		cur = prev;
		--prev;
	}
	*cur = val;
}

void __cdecl Rva00580A54Sort(void **first, void **last, void **, Rva000795C1Record compare)
{
	for (void **i = first; i != last; ++i)
		Rva00580776Insert(i, *i, compare);
}

void __cdecl Rva00580BBFUnguardedSort(void **first, void **last, Rva000795C1Record compare)
{
	Rva00580A54Sort(first, last, (void **)0, compare);
}

void __cdecl Rva005809DBLinearInsert(void **first, void **last, void *val, Rva000795C1Record compare)
{
	if (compare.compareRva005803C0(val, *first))
	{
		_STL::__copy_trivial_backward(first, last, last + 1);
		*first = val;
	}
	else
	{
		Rva00580776Insert(last, val, compare);
	}
}
