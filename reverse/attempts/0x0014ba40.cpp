// ?Rva0014BA40Get@@YA?AV?$RefCountPtr@VRefCountClass@@@@PAVRefCountClass@@@Z
// partial score=0.7439 date=2026-10-06
// ?Rva0014BA40Get@@YA?AV?$RefCountPtr@VRefCountClass@@@@PAVRefCountClass@@@Z
// partial score=0.99 date=2026-10-03
// cl: /O2 /DNDEBUG /MD /EHa /G7
// ?Rva0014BA40Get@@YA?AV?$RefCountPtr@VRefCountClass@@@@PAVRefCountClass@@@Z 0x0014BAB0 104B free RefCountPtr return via tmp copy; after Replace_Texture 0x0014B800; caller 0x0014BDDF
class RefCountClass {
public:
    virtual void Delete_This();
    int RefCount;
    void Add_Ref() { ++RefCount; }
    void Release_Ref() { if (--RefCount == 0) Delete_This(); }
};
template<class T> class RefCountPtr {
public:
    T *p;
    RefCountPtr(T *q) : p(q) { if (p) p->Add_Ref(); }
    RefCountPtr(const RefCountPtr &other) : p(other.p) { if (p) p->Add_Ref(); }
    ~RefCountPtr() { if (p) p->Release_Ref(); }
    RefCountPtr &operator=(const RefCountPtr &other) {
        if (other.p) other.p->Add_Ref();
        if (p) p->Release_Ref();
        p = other.p;
        return *this;
    }
};
RefCountPtr<RefCountClass> Rva0014BA40Get(RefCountClass *src)
{
    RefCountPtr<RefCountClass> tmp(src);
    return tmp;
}
