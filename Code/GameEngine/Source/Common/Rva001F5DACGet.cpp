// cl: /MD
// ?get@Rva001F5DACSlot@@QAEPAXPAX@Z @0x001F5DAC 20B.
// Null-checked holder at +0xA8 via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F643B and 0x001FC362. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5DACHelper {
public:
    virtual ~Rva001F5DACHelper();
    virtual void u1();
    virtual void* fetch(void* arg);
};
class Rva001F5DACSlot {
public:
    void* get(void* arg);
    char m_pad[0xA8];
    Rva001F5DACHelper* m_ptr;
};
void* Rva001F5DACSlot::get(void* arg)
{
    Rva001F5DACHelper* p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
