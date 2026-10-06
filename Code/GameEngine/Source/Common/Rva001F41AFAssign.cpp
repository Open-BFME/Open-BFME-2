// cl: /MD
// ??4Rva001F41AF@@QAEAAV0@ABV0@@Z @0x001F41AF 30B.
// Assignment clones holder at +0 via second virtual slot returning void* with null else zero then returns self.
// Callers at 0x001F9C89 and 0x001FA647 pass own this plus stack arg and ignore return proving thiscall ret4.
// Prev 0x001F3FD0 Rva001F3FD0Set same flags and next 0x001F4206 same flags. Honest Rva class and operator.
// /O1 for test-je plus jmp-over-xor shared store epilogue.
struct Rva001F41AFHelper {
    virtual void f0();
    virtual void *clone();
};
class Rva001F41AF {
public:
    Rva001F41AFHelper *m_ptr;
    Rva001F41AF &operator=(const Rva001F41AF &other);
};
Rva001F41AF &Rva001F41AF::operator=(const Rva001F41AF &other)
{
    Rva001F41AFHelper *p = other.m_ptr;
    void *q;
    if (p)
        q = p->clone();
    else
        q = 0;
    m_ptr = (Rva001F41AFHelper *)q;
    return *this;
}
