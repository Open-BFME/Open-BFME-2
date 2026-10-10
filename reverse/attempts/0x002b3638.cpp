// ?rva002B3638@Rva002B3638@@QAE?AV?$RefCountPtr@URva002B3638Node@@@@XZ
// partial score=0.98 date=2026-10-10
// ?rva002B3638@Rva002B3638@@QAE?AV?$RefCountPtr@URva002B3638Node@@@@XZ
// partial score=0.98 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /EHsc /MD
#include <vector>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// stlport
// Hidden value-return flags explain the prior banks' missing push ecx and
// AND [EBP-4],0. Each native ABI and payload is separately supported below.
template <class T> class RefCountPtr {
public:
    RefCountPtr() : ptr(0) {}
    RefCountPtr(const RefCountPtr &other) throw() : ptr(other.ptr) { if (ptr) ++ptr->refs; }
    ~RefCountPtr();
    T *ptr;
};
struct Rva002B3638Node { int pad00; int refs; };
class Rva002B3638 {
public:
    RefCountPtr<Rva002B3638Node> rva002B3638();
    char pad[0x154];
    _STL::vector<RefCountPtr<Rva002B3638Node> > entries;
};
// Native2B3638..2B3669 RET4: vector154/158 contains4B owning references;
// copy adds1 at referenced node+4 and default clears the hidden result word.
// Node and owner identity remain neutral; destructor ABI inferred from sret.
RefCountPtr<Rva002B3638Node> Rva002B3638::rva002B3638()
{
    _STL::vector<RefCountPtr<Rva002B3638Node> > *v = &entries;
    if (!v->empty()) {
        _ReadWriteBarrier();
        return (*v)[0];
    }
    return RefCountPtr<Rva002B3638Node>();
}
