// cl: /MD
// ?get@Rva001F5DFCSlot@@QAEPAXPAX@Z @0x001F5DFC 20B
// Null-checked holder at +0xB8 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F64C7 and 0x001FB8F7. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5DFCHelper {
public:
    virtual ~Rva001F5DFCHelper();
    virtual void u1();
    virtual void *fetch(void *arg);
};
class Rva001F5DFCSlot {
public:
    void *get(void *arg);
    char m_pad[0xB8];
    Rva001F5DFCHelper *m_ptr;
};
void *Rva001F5DFCSlot::get(void *arg)
{
    Rva001F5DFCHelper *p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
