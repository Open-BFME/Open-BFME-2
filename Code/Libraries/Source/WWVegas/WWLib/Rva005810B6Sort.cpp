// cl: /EHsc /MD
// Native Ghidra5810B6..58113D RET0: two four-byte iterator endpoints and a
// sixteen-byte by-value record. The original element/comparator names and
// key meaning are unknown. A dword followed by a twelve-byte owned vector
// is established by the full copy helper795C1/29 and its vector copy2CFAB9/67;
// free(frame+14) establishes the by-value record teardown.
// Algorithm follows STLport4.5.3 sort in inputs/vendor/stlport/stl/_algo.c
// at BFME1 revision6583b3c1ff21db4a561285717028fdafc780b7db: depth-limit
// introsort followed by final insertion sort. Retail callee5810FD1 is an
// EH-framed sixteen-element threshold loop;580D38 splits insertion at16.
// Boundary and ABI are target facts; the algorithm relationship is inferred
// from both callees and the characteristic lg(distance)*2 wrapper.
// ?Rva005810B6Sort@@YAXPAPAX0VRva000795C1Record@@@Z
void __cdecl free(void *);
class Rva000795C1Record {
    unsigned int key;
    void *first, *last, *end;
public:
    Rva000795C1Record(const Rva000795C1Record &);
    bool compareRva005803C0(void *, void *) const;
    ~Rva000795C1Record() { if (first) free(first); }
};
void __cdecl Rva00580FD1IntroSort(void **, void **, void **, int, Rva000795C1Record);
void __cdecl Rva00580D38FinishSort(void **, void **, Rva000795C1Record);
static int sort_depth(int count) {
    int depth;
    for (depth=0;count!=1;count >>= 1) ++depth;
    return depth;
}
void __cdecl Rva005810B6Sort(void **first, void **last, Rva000795C1Record compare) {
    if (first != last) {
        Rva00580FD1IntroSort(first,last,(void **)0,sort_depth(last-first)*2,compare);
        Rva00580D38FinishSort(first,last,compare);
    }
}

void __cdecl Rva00580B5CInsertionSort(void **, void **, Rva000795C1Record);
void __cdecl Rva00580BBFUnguardedSort(void **, void **, Rva000795C1Record);
void __cdecl Rva00580ED0PartialSortImpl(void **, void **, void **, void **, Rva000795C1Record);
void __cdecl Rva00580C0E(void **, void **, void **, void *, Rva000795C1Record, void **);
void __cdecl Rva00580C6F(void **, void **, Rva000795C1Record, void **, void **);
void __cdecl Rva00580AAC(void **, int, int, void *, Rva000795C1Record);
void __cdecl Rva005807CE(void **, int, int, void *, Rva000795C1Record);
// Native580D38..580DBF/135B; STLport final insertion pass at threshold16.
// /G7 reproduces the byte-sized alignment mask and schedules the record copy.
// ?Rva00580D38FinishSort@@YAXPAPAX0VRva000795C1Record@@@Z
void __cdecl Rva00580D38FinishSort(void **first, void **last, Rva000795C1Record compare) {
    if (last-first > 16) {
        Rva00580B5CInsertionSort(first,first+16,compare);
        Rva00580BBFUnguardedSort(first+16,last,compare);
    } else {
        Rva00580B5CInsertionSort(first,last,compare);
    }
}

void ** __cdecl Rva00580646Median(void * const &, void * const &, void * const &, Rva000795C1Record);
void ** __cdecl Rva00580705Partition(void **, void **, void *, Rva000795C1Record);
void __cdecl Rva00580F7FPartialSort(void **, void **, void **, Rva000795C1Record);
// Native580FD1..5810B6/229B; STLport introsort depth fallback and median partition.
// ?Rva00580FD1IntroSort@@YAXPAPAX00HVRva000795C1Record@@@Z
void __cdecl Rva00580FD1IntroSort(void **first, void **last, void **, int depth, Rva000795C1Record compare) {
    while (last-first > 16) {
        if (depth == 0) {
            Rva00580F7FPartialSort(first,last,last,compare);
            return;
        }
        --depth;
        void **cut = Rva00580705Partition(first,last,*Rva00580646Median(*first,*(first+(last-first)/2),*(last-1),compare),compare);
        Rva00580FD1IntroSort(cut,last,(void **)0,depth,compare);
        last=cut;
    }
}

// Native580646..580705/191B: STLport median decision tree with same record.
// Five member calls use ecx=by-value record and two dereferenced pointer values;
// target comparator5803C0/619 ends RET8. Its application meaning is unknown.
// ?Rva00580646Median@@YAPAPAXABQAX00VRva000795C1Record@@@Z
void ** __cdecl Rva00580646Median(void * const &a, void * const &b, void * const &c, Rva000795C1Record compare) {
    if (compare.compareRva005803C0(a,b)) {
        if (compare.compareRva005803C0(b,c)) return const_cast<void **>(&b);
        else if (compare.compareRva005803C0(a,c)) return const_cast<void **>(&c);
        else return const_cast<void **>(&a);
    } else if (compare.compareRva005803C0(a,c)) return const_cast<void **>(&a);
    else if (compare.compareRva005803C0(b,c)) return const_cast<void **>(&c);
    else return const_cast<void **>(&b);
}

// Native580705..580776/113B: STLport __unguarded_partition with same record.
// While compare(*first,pivot) ++first; --last; while compare(pivot,*last) --last;
// return first when first>=last else swap and ++first. Callers 0x00580FD1IntroSort,
// prev/next rows share // cl /O1 /G7 /EHsc /MD. Evidence packet leaf 0x00580705.
// ?Rva00580705Partition@@YAPAPAXPAPAX0PAXVRva000795C1Record@@@Z
void ** __cdecl Rva00580705Partition(void **first, void **last, void *pivot, Rva000795C1Record compare) {
    while (true) {
        while (compare.compareRva005803C0(*first, pivot))
            ++first;
        --last;
        while (compare.compareRva005803C0(pivot, *last))
            --last;
        if (!(first < last))
            return first;
        void *tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// Called only when the rowed introsort loop exhausts its depth budget. The
// three iterator arguments and comparator copy are target-supported by that
// call site; the helper's address-derived identity remains provisional.
// ?Rva00580F7FPartialSort@@YAXPAPAX00VRva000795C1Record@@@Z
void __cdecl Rva00580F7FPartialSort(void **first, void **middle, void **last, Rva000795C1Record compare) {
    Rva00580ED0PartialSortImpl(first, middle, last, (void **)0, compare);
}

// Target evidence: the helper reduces the end pointer by one element and
// forwards that element plus its comparator to the address-derived 0x580C0E.
// ?Rva00580CE2@@YAXPAPAX00VRva000795C1Record@@@Z
void __cdecl Rva00580CE2(void **first, void **last, void **, Rva000795C1Record compare) {
    Rva00580C0E(first, last - 1, last - 1, *(last - 1), compare, (void **)0);
}

// The adjacent heap routine uses this wrapper with its target-proven iterator
// pair and 16B comparator; the helper and template identity stay address-only.
// ?Rva00580DBF@@YAXPAPAX0VRva000795C1Record@@@Z
void __cdecl Rva00580DBF(void **first, void **last, Rva000795C1Record compare) {
    Rva00580C6F(first, last, compare, (void **)0, (void **)0);
}

// Target facts: heap length is iterator distance and parent indices descend
// from (length - 2) / 2 through zero. The STLport __make_heap relationship is
// inferred from the matched wrapper at 0x580DBF and donor _heap.c at 6583b3c1.
// ?Rva00580C6F@@YAXPAPAX0VRva000795C1Record@@00@Z
void __cdecl Rva00580C6F(void **first, void **last, Rva000795C1Record compare, void **, void **)
{
	int length = (int)(last - first);
	if (length < 2)
		return;

	int parent = (length - 2) / 2;
	while (true)
	{
		Rva00580AAC(first, parent, length, *(first + parent), compare);
		if (parent == 0)
			return;
		--parent;
	}
}

// Target moves the larger child into the hole then restores the saved value
// through 0x5807CE. This follows STLport _adjust_heap at donor 6583b3c1;
// comparator identity and element meaning remain unknown.
// ?Rva00580AAC@@YAXPAPAXHHPAXVRva000795C1Record@@@Z
void __cdecl Rva00580AAC(void **first, int holeIndex, int length, void *value, Rva000795C1Record compare)
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < length)
	{
		if (compare.compareRva005803C0(*(first + secondChild), *(first + (secondChild - 1))))
			--secondChild;
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == length)
	{
		*(first + holeIndex) = *(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	Rva005807CE(first, holeIndex, topIndex, value, compare);
}
