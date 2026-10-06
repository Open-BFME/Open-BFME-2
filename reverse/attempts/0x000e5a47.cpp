// ??0Rva000E59D3@@QAE@XZ
// partial score=0.97 date=2026-10-06
// cl: /Ireference/shims/bfmelist /Os /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000E59D3@@QAE@XZ @0x000E5A47 102B
// Ctor of Rva000E59D3. Stores vtable 0x007CE9E0, clears +0x14, constructs
// int list at +0x18 via rowed List_base ctor, clears +0x20/+0x04/+0x08/+0x0C
// +0x10/+0x1C, inits via rowed Rva000E473F::rva000E479C, sets +0x20/+0x22.
// Evidence: vtable store, rowed callees, pin naming, caller 0x0006CC5D.
#include <list>

class Rva000E473F
{
public:
    void rva000E479C();
};

class Rva000E59D3Base
{
public:
    Rva000E59D3Base() {}
    ~Rva000E59D3Base();
};

class Rva000E59D3Holder14
{
public:
    Rva000E59D3Holder14(int v) : m_ptr((void *)v) {}
    ~Rva000E59D3Holder14();
private:
    void *m_ptr;
};

class Rva000E59D3 : public Rva000E59D3Base
{
public:
    Rva000E59D3();
    virtual ~Rva000E59D3();
private:
    int m04;
    int m08;
    int m0c;
    int m10;
    Rva000E59D3Holder14 m14;
    _STL::_List_base<int, _STL::allocator<int> > m18;
    int m1c;
    unsigned char m20;
    char m_pad21;
    unsigned char m22;
};

Rva000E59D3::Rva000E59D3() : Rva000E59D3Base(), m14(0), m18(_STL::allocator<int>())
{
    m20 = 0;
    m04 = 0;
    m08 = 0;
    m0c = 0;
    m10 = 0;
    m1c = 0;
    ((Rva000E473F *)this)->rva000E479C();
    m20 = 1;
    m22 = 1;
}
