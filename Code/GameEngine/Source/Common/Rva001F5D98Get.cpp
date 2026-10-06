// cl: /MD
// ?get@Rva001F5D98Slot@@QAEPAXPAX@Z @0x001F5D98 20B.
// Null-checked holder at +0xA4 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F6400 and 0x001FC45C. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5D98Helper {
public:
    virtual ~Rva001F5D98Helper();
    virtual void u1();
    virtual void* fetch(void* arg);
};
class Rva001F5D98Slot {
public:
    void* get(void* arg);
    char m_pad[0xA4];
    Rva001F5D98Helper* m_ptr;
};
void* Rva001F5D98Slot::get(void* arg)
{
    Rva001F5D98Helper* p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
