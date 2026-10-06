// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived recovery of 0x0015B110 (136B), a ref-counted object factory.
// Retail: operator new(0x34) 0x002FDA0, construct with this via the unrowed
// ctor 0x00152DE9 (vtable 0x00BD3B1C, refcount at +4), store into the hidden
// return pointer, then the smart pointer's copy AddRef ([p+4]+=1) and
// temporary Release ([p+4]-=1, deleting through vtable[0] on zero). The
// hidden-pointer ret 4 and AssetReference-style temp match the rowed
// sharebuf/RefCount family. Ctor and class names are address-derived.

class RefCountClass
{
public:
    virtual void Delete();
    int m_refCount;

    void AddRef() { ++m_refCount; }
    int Release() { return --m_refCount; }
};

class Rva0015B110Owner;

class Rva0015B110Target : public RefCountClass
{
public:
    Rva0015B110Target(Rva0015B110Owner *owner);

    char m_pad[0x2C];
};

class RefPtr
{
public:
    RefCountClass *m_ptr;

    RefPtr(RefCountClass *p) : m_ptr(p) {}
    RefPtr(const RefPtr &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            m_ptr->AddRef();
    }
    ~RefPtr()
    {
        if (m_ptr && m_ptr->Release() == 0)
            m_ptr->Delete();
    }
};

class Rva0015B110Owner
{
public:
    RefPtr rva0015b110();
};

RefPtr Rva0015B110Owner::rva0015b110()
{
    RefPtr temp(new Rva0015B110Target(this));
    return temp;
}
