// cl: /MD
// ?get@Rva001F5E24Slot@@QAEPAXPAX@Z @0x001F5E24 20B.
// Null-checked holder at +0xC0 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F652C and 0x001FA558. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5E24Helper {
public:
    virtual ~Rva001F5E24Helper();
    virtual void u1();
    virtual void* fetch(void* arg);
};
class Rva001F5E24Slot {
public:
    void* get(void* arg);
    char m_pad[0xC0];
    Rva001F5E24Helper* m_ptr;
};
void* Rva001F5E24Slot::get(void* arg)
{
    Rva001F5E24Helper* p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
