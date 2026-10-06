// cl: /EHs /MD

// ??1Rva005A71B1@@UAE@XZ @0x005A71B1 79B: dtor stores vtable 0x00871BF8,
// destroys 0x40-element array at +0x218 via ehvec dtor, frees ptr at +4 via
// _free 0x00030830. Element dtor pointer is 0x005A66B8. Unblocks ??_G at
// 0x005A7200 and 0x005A734B.

extern "C" void __cdecl free(void *block);

class Rva005A66B8Elem
{
public:
    virtual ~Rva005A66B8Elem() {}
private:
    int m_pad[4];
};

class Rva005A71B1Base
{
public:
    ~Rva005A71B1Base() { if (m_ptr) free(m_ptr); }
protected:
    char *m_ptr;
};

class Rva005A71B1 : public Rva005A71B1Base
{
public:
    virtual ~Rva005A71B1();
private:
    unsigned char m_pad[0x210];
    Rva005A66B8Elem m_arr[0x40];
};

Rva005A71B1::~Rva005A71B1()
{
}

// 0x005A734B 119B: dtor stores vtable 0x00871BFC, frees 8 pointers at +0x90C
// via operator delete 0x0002FD60, destroys global at 0x00A063B0 via slot0
// with 0 then deletes and nulls it, then destroys Rva005A71B1 at +0x28 via
// rowed 0x005A71B1. Unblocks ??_G at 0x005A73C2.
void __cdecl operator delete(void *block);

struct Rva00A063B0Obj
{
    virtual void *Unknown00(int x);
};

extern Rva00A063B0Obj *g_a063b0;
// g_a063b0: matched references place it at VA 0xe063b0 (zero-filled .bss).
Rva00A063B0Obj * g_a063b0;

class Rva005A734B
{
public:
    virtual ~Rva005A734B();
private:
    unsigned char m_pre[0x24];
    Rva005A71B1 m_mid;
    unsigned char m_mid2[0x90C - 0x740];
    void *m_ptrs[8];
};

Rva005A734B::~Rva005A734B()
{
    for (int i = 0; i < 8; i++) {
        if (m_ptrs[i])
            operator delete(m_ptrs[i]);
    }
    if (g_a063b0) {
        void *q = g_a063b0->Unknown00(0);
        operator delete(q);
        g_a063b0 = 0;
    }
}
