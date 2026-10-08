// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native D3945..D397D is 56B; the old 76B Ghidra span includes the
// already-rowed 20B iterator helper at D397D. The clear call at D395A
// identifies the existing Rva000D20A9 tree owner. Native EH state zero
// owns the header storage while clear runs, then state -1 precedes free.
// The owning-head view preserves the established 8B head/count layout.
// C++ free is the existing game-allocator spelling at30830; its global
// binding lives in GameMemoryFree.cpp and retains the native EH transition.
void __cdecl free(void *);
struct Rva000D3945Head
{
    void *pointer;
    // ?Rva000D3945Head::~Rva000D3945Head present-unmatched
    ~Rva000D3945Head() { if (pointer) free(pointer); }
};
class Rva000D20A9
{
public:
    ~Rva000D20A9();
    void rva000D2294();
private:
    Rva000D3945Head head;
    int count;
};
Rva000D20A9::~Rva000D20A9() { rva000D2294(); }
