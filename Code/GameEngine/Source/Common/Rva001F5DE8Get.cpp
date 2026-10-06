// cl: /MD
// ?get@Rva001F5DE8Slot@@QAEPAXPAX@Z @0x001F5DE8 20B
// Null-checked holder at +0xB4 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F647D and 0x001FBA97. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5DE8Helper {
public:
    virtual ~Rva001F5DE8Helper();
    virtual void u1();
    virtual void *fetch(void *arg);
};
class Rva001F5DE8Slot {
public:
    void *get(void *arg);
    char m_pad[0xB4];
    Rva001F5DE8Helper *m_ptr;
};
void *Rva001F5DE8Slot::get(void *arg)
{
    Rva001F5DE8Helper *p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
