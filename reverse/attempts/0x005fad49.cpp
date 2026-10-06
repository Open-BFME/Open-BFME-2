// ?rva005FAD49@Rva005FAD49@@QAEPAPAXPAPAX@Z
// partial score=0.8 date=2026-10-06
// cl: /MD /Oy-
// ?rva005FAD49@Rva005FAD49@@QAEPAPAXPAPAX@Z, RVA 0x005FAD49, 68 bytes.
// Clone: new 0x18 vtable 0x00879EC4 zero +4 copy 16B from this+8 store AddRef return out.
// Evidence: sibling ctor Rva005FAB9E same vtable/size/copy; slot1 of that table; callers none.
struct Payload005FAD49 { int v[4]; };
struct Rva005FAD49 {
    virtual void _vf();
    int m_ref;
    Payload005FAD49 m_data;
    Rva005FAD49(const Payload005FAD49 &o) : m_ref(0), m_data(o) {}
    void **rva005FAD49(void **out);
};
void **Rva005FAD49::rva005FAD49(void **out)
{
    volatile int _s = 0;
    Rva005FAD49 *p = new Rva005FAD49(m_data);
    *out = (void *)p;
    if (p)
        ++p->m_ref;
    return out;
}
