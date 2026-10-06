// cl: /MD
// ?get@Rva001F5DD4Slot@@QAEPAXPAX@Z @0x001F5DD4 20B.
// Null-checked holder at +0xB0 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F6467 and 0x001FBC4E. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5DD4Helper {
public:
    virtual ~Rva001F5DD4Helper();
    virtual void u1();
    virtual void* fetch(void* arg);
};
class Rva001F5DD4Slot {
public:
    void* get(void* arg);
    char m_pad[0xB0];
    Rva001F5DD4Helper* m_ptr;
};
void* Rva001F5DD4Slot::get(void* arg)
{
    Rva001F5DD4Helper* p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
