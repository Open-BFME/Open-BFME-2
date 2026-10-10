// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native001688FF..00168952 and00168952..0016897B, both cdecl RET0.
// WB9ECB90 identifies RefCountPtr<FXShader::RenderingMethod> in the clear
// helper. The runtime element and slot7 spelling remain address-derived.
// Target: owning four-byte argument, reference count at4, virtual slot7.
// An explicit owning copy constructor permits direct argument construction;
// a trivial copy instead creates a separate caller-owned temporary.
template<class T> class RefCountPtr
{
public:
    RefCountPtr(T *p) : ptr(p) { if (ptr) ++ptr->refs; }
    RefCountPtr(const RefCountPtr &other) : ptr(other.ptr) { if (ptr) ++ptr->refs; }
    ~RefCountPtr();
    T *ptr;
};

class Rva001688FFElement
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7(RefCountPtr<Rva001688FFElement> next);
    int refs;
};

void Rva001688FFShift(Rva001688FFElement **items, int count)
{
    if (count > 0) {
        for (int i = 0; i < count - 1; ++i)
            items[i]->slot7(RefCountPtr<Rva001688FFElement>(items[i + 1]));
        items[count - 1]->slot7(RefCountPtr<Rva001688FFElement>(0));
    }
}

void Rva00168952Clear(Rva001688FFElement **items, int count)
{
    for (int i = 0; i < count; ++i)
        items[i]->slot7(RefCountPtr<Rva001688FFElement>(0));
}
