// cl: /O1 /MD
// ?rva003EE7CA@Rva003EE7CA@@QAEHHH@Z @0x003EE7CA 23B virtual forward via this+0x48 slot1 then return first arg
// Evidence: retail pushes [esp+8]/[esp+8] with ecx=[ecx+0x48] and call [eax+4]; callers at 0x003EE8E8/0x003EE92D pass (local,arg); prev 0x003EE7C2 next 0x003EE7E1 same /O1 family
class Rva003EE7CAVirt
{
public:
    virtual void v0();
    virtual void virt(int a, int b);
};

class Rva003EE7CA
{
public:
    int rva003EE7CA(int a, int b);
private:
    char m_pad[0x48];
    Rva003EE7CAVirt *m_48;
};

int Rva003EE7CA::rva003EE7CA(int a, int b)
{
    m_48->virt(a, b);
    return a;
}
