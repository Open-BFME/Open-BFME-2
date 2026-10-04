// cl: /O1
// ?rva00180AF9@Rva00180AF9@@QAEPAV1@ABV?$RefCountPtr@VTextureClass@@@@@Z @0x00180AF9 50B
// Evidence: unlock lane; TextureClass slot 0x34 identity via 0x41474752 compare;
// callees rowed clear 0x0004D75B and RefCountPtr assign 0x000424D0; caller 0x00180BE0.
class TextureClass
{
public:
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
};

template <class T>
class RefCountPtr
{
public:
    T *Referent;
    const RefCountPtr &operator=(const RefCountPtr &other);
};

struct BfmeResetTextureRef
{
    void *pointer;
    void clear();
};

class Rva00180AF9
{
public:
    Rva00180AF9 *rva00180AF9(const RefCountPtr<TextureClass> &other);
};

Rva00180AF9 *Rva00180AF9::rva00180AF9(const RefCountPtr<TextureClass> &other)
{
    TextureClass *p = other.Referent;
    if (p != 0 && p->v13() != 0x41474752)
        ((BfmeResetTextureRef *)this)->clear();
    else
        ((RefCountPtr<TextureClass> *)this)->operator=(other);
    return this;
}
