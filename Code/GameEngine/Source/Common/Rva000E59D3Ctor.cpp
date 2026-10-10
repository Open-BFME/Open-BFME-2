// cl: /Ireference/shims/bfmelist /Os /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000E59D3@@QAE@XZ @0x000E5A47 102B
// Ctor of Rva000E59D3 (pairs with the rowed dtor 0x000E59D3 in
// Rva000E59D3Dtor.cpp). Stores vtable 0x007CE9E0, clears the texture handle at
// +0x14, default-constructs the list<int> at +0x18 (rowed _List_base ctor
// 0x004EC36C), clears +0x20/+0x04/+0x08/+0x0C/+0x10/+0x1C, runs the rowed
// W3DFloorBuffer::allocateFloorBuffers 0x000E479C on this, sets +0x20/+0x22.
// The member is the full list<int>, not a bare _List_base: list's inline ctor
// evaluates the allocator temporary and this before the push (lea eax / lea
// ecx / push eax), which a direct _List_base member reorders to lea/push/lea.
// Unwind funclets: base dtor this+0 (the base owns the vptr, as the dtor TU
// models it), handle this+0x14, list this+0x18.
// Evidence: vtable store, rowed callees, caller 0x0006CC5D. Names address-derived.
#include <list>

class W3DFloorBuffer
{
public:
    void allocateFloorBuffers();
};

class Rva000E59D3Base
{
public:
    Rva000E59D3Base() {}
    virtual ~Rva000E59D3Base();
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
    _STL::list<int> m18;
    int m1c;
    unsigned char m20;
    char m_pad21;
    unsigned char m22;
};

Rva000E59D3::Rva000E59D3() : Rva000E59D3Base(), m14(0)
{
    m20 = 0;
    m04 = 0;
    m08 = 0;
    m0c = 0;
    m10 = 0;
    m1c = 0;
    ((W3DFloorBuffer *)this)->allocateFloorBuffers();
    m20 = 1;
    m22 = 1;
}
