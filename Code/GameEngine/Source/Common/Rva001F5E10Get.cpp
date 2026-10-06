// cl: /MD
// ?get@Rva001F5E10Slot@@QAEPAXPAX@Z @0x001F5E10 20B
// Null-checked holder at +0xBC via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F6516 and 0x001FA841. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5E10Helper {
public:
    virtual ~Rva001F5E10Helper();
    virtual void u1();
    virtual void *fetch(void *arg);
};
class Rva001F5E10Slot {
public:
    void *get(void *arg);
    char m_pad[0xBC];
    Rva001F5E10Helper *m_ptr;
};
void *Rva001F5E10Slot::get(void *arg)
{
    Rva001F5E10Helper *p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
