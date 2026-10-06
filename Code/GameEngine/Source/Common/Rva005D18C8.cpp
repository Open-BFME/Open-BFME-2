// cl: /MD
// ?rva005D18C8@Rva005D18C8@@QAEXXZ @0x005D18C8 26B
// Owning-pointer clear: takes pointer at +0 nulls it then if non-null calls rowed dtor 0x005D1846 then rowed operator delete 0x0002FD60.
// Evidence: chain from just-landed 0x005D1846; caller 0x005D1A4B jmp; no vtable no EH so plain method.
class Rva005D1846
{
public:
    ~Rva005D1846();
};
void __cdecl operator delete(void *);
class Rva005D18C8
{
public:
    void rva005D18C8();
private:
    Rva005D1846 *m_ptr;
};
void Rva005D18C8::rva005D18C8()
{
    Rva005D1846 *p = m_ptr;
    m_ptr = 0;
    if (p)
        delete p;
}
