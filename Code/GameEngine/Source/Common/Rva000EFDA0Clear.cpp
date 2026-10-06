// cl: /MD
// ?rva000F11C0@Rva000EFDA0@@QAEXXZ 0x000F11C0 82B clear via rva000EFDA0 plus array deletes +0x20 +0x10 gated +0x30 plus ref releases +0 +4; chain from 0x000EFDA0
void operator delete[](void *block);
struct RvaRef {
    virtual void release();
    int m_refs;
};
class Rva000EFDA0 {
public:
    void rva000EFDA0();
    void rva000F11C0();
private:
    RvaRef *m_0;
    RvaRef *m_4;
    char _p8[8];
    char *m_10;
    char _p14[12];
    char *m_20;
    char *m_24;
    int m_28;
    char _p2c[4];
    bool m_30;
};
void Rva000EFDA0::rva000F11C0()
{
    rva000EFDA0();
    if (m_20 != 0)
        ::operator delete[](m_20);
    if (m_10 != 0) {
        if (!m_30)
            ::operator delete[](m_10);
    }
    RvaRef *p0 = m_0;
    if (p0 != 0) {
        if (--p0->m_refs == 0)
            p0->release();
        m_0 = 0;
    }
    RvaRef *p1 = m_4;
    if (p1 != 0) {
        if (--p1->m_refs == 0)
            p1->release();
        m_4 = 0;
    }
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1W3DShadowGeometryMesh@@QAE@XZ=?rva000F11C0@Rva000EFDA0@@QAEXXZ")
