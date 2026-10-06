// cl: /MD
// ??4Rva001F41CD@@QAEAAV0@ABV0@@Z @0x001F41CD 57B.
// Assignment clones other holder at +0 via slot plus 4 then deletes old holder at +0 via slot 0 plus 0.
// Then stores clone and returns self via rowed operator delete 0x0002FD60.
// Callers at 0x001F9CD3 and 0x001FA67F pass own this plus stack arg proving thiscall ret 4.
// Prev 0x001F41AF same clone shape and next 0x001F4206 same delete shape same flags. Honest Rva class.
// /O1 for test push-edi je plus jmp-over-xor shared stores.
void __cdecl operator delete(void *p);
struct Rva001F41CDHelper {
    virtual void *func0(int x);
    virtual void *clone();
};
class Rva001F41CD {
public:
    Rva001F41CDHelper *m_ptr;
    Rva001F41CD &operator=(const Rva001F41CD &other);
};
Rva001F41CD &Rva001F41CD::operator=(const Rva001F41CD &other)
{
    Rva001F41CDHelper *p = other.m_ptr;
    void *nq;
    if (p)
        nq = p->clone();
    else
        nq = 0;
    Rva001F41CDHelper *o = m_ptr;
    void *oq;
    if (o)
        oq = o->func0(0);
    else
        oq = 0;
    ::operator delete(oq);
    m_ptr = (Rva001F41CDHelper *)nq;
    return *this;
}
