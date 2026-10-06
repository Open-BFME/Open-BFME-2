// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00207BC3Pop@@YAXPAH0VRva00204BB8@@@Z @0x00207BC3 23B
// pop_heap forwarding wrapper over the rowed pop wrapper 0x00207539:
// forwards (first,last) plus trailing zero and comp; same pattern as
// Rva0021BAFCPopHeap. Evidence: chain via landed pop wrapper; caller
// 0x002082D6 in 0x002082B7.

class Rva00204BB8
{
public:
    bool operator()(int a, int b) const;
};

void __cdecl Rva00207539Pop(int *first, int *last, int, Rva00204BB8 comp);

void __cdecl Rva00207BC3Pop(int *first, int *last, Rva00204BB8 comp)
{
	Rva00207539Pop(first, last, 0, comp);
}
