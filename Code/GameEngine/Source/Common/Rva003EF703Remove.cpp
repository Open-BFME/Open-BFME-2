// cl: /DNDEBUG /MD /EHsc /O1 /G7 /arch:SSE
// ?remove@Rva003EF8E1@@QAEXPAURva003C4CF0Span@@H@Z retail 0x003EF703, 37 bytes.
// Native caller 003EF8E1 supplies its ECX receiver; member remove-by-value: indexOf over two-pointer int span then
// vector<void*> erase at found slot; no-op when indexOf returns -1.
// Callees rowed 0x003EF676 indexOf and 0x001FF51F vector erase.
// Callers 0x003EF980 0x003EF98C in 0x003EF8E1. Neighbours 0x003EF6D6 and 0x003EF728 give flags.
struct Rva003C4CF0Span
{
    int *begin;
    int *end;
};
int __stdcall indexOf(Rva003C4CF0Span *span, int value);

namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
    T *_M_start;
    T *_M_finish;
    T *_M_end_of_storage;
    T *erase(T *);
};
}

class Rva003EF8E1 { public: void remove(Rva003C4CF0Span *span, int value); };

void Rva003EF8E1::remove(Rva003C4CF0Span *span, int value)
{
    int idx = indexOf(span, value);
    if (idx != -1) {
        _STL::vector<void *, _STL::allocator<void *> > *vec =
            (_STL::vector<void *, _STL::allocator<void *> > *)span;
        vec->erase(vec->_M_start + idx);
    }
}

// Native 003EF8E1 reloads ECX from EDI before this two-argument RET8 call.
// The address-derived owner records that unused-receiver ABI without an alias.
