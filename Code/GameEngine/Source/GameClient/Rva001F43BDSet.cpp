// cl: /O1 /GX- /arch:SSE2
// ?rva001F43BD@Rva001F43BD@@QAEXPAX@Z @0x001F43BD 33B
// Owned-pointer setter: releases the old object through its virtual slot 0
// with a 0 argument, frees the returned pointer with operator delete, then
// stores the new pointer. Evidence: retail pushes 0 (reused xor-ed eax) for
// the slot call, deletes unconditionally (je lands on push+delete), stores
// [esp+0xC] after; sole direct callee is rowed ??3@YAXPAX@Z 0x0002FD60;
// virtual slot call needs no row; 8 INI Parse bodies (0x001F83C9 et al)
// call it, landing this unblocks 6 of them.
class Rva001F43BD
{
    struct Ifc
    {
        virtual void *slot0(int flags);
    };
    Ifc *m_ptr;
public:
    void rva001F43BD(void *p);
};

void Rva001F43BD::rva001F43BD(void *p)
{
    Ifc *old = m_ptr;
    void *doomed = 0;
    if (old != 0)
        doomed = old->slot0(0);
    ::operator delete(doomed);
    m_ptr = (Ifc *)p;
}
