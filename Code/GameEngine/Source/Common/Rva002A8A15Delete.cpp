// cl: /MD
// ?rva002A8A15@Rva002A8A15@@QAEPAXH@Z @0x002A8A15 28B clear via rowed 0x004E9337 then cond delete via rowed 0x0002FD60 return this
class Rva004E9337
{
public:
    void rva004E9337();
};
class Rva002A8A15 : public Rva004E9337
{
public:
    void *rva002A8A15(int flags);
};
void __cdecl operator delete(void *p);

void *Rva002A8A15::rva002A8A15(int flags)
{
    rva004E9337();
    if (flags & 1)
        operator delete(this);
    return this;
}
