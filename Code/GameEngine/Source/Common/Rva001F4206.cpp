// cl: /MD
// ?rva001F4206@Rva001F4206@@QAEXXZ @0x001F4206 21B.
// Null-checked holder at +0 via virtual slot 0 taking 0 returning void* then rowed operator delete 0x0002FD60.
// Callers at 0x001F58E8 with this plus 8 and at 0x001F904E with own this prove __thiscall void void.
// Prev 0x001F3FD0 Rva001F3FD0Set same flags and next 0x001F421B FXParticleSystem. Honest Rva names.
// /O1 for xor-first compare plus push-eax delete epilogue.
void __cdecl operator delete(void *p);
struct Rva001F4206Helper {
    virtual void *func(int x);
};
class Rva001F4206 {
public:
    Rva001F4206Helper *m_ptr;
    void rva001F4206();
};
void Rva001F4206::rva001F4206()
{
    void *q = 0;
    Rva001F4206Helper *p = m_ptr;
    if (p)
        q = p->func(0);
    ::operator delete(q);
}
