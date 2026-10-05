// cl: /O1 /EHsc /MD
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
