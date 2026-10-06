// cl: /MD
// ?get@Rva001F5DC0Slot@@QAEPAXPAX@Z @0x001F5DC0 20B.
// Null-checked holder at +0xAC via virtual slot +0x8 with tail jmp forwarding one arg.
// Callers at 0x001F6451 and 0x001FBFF5. Honest Rva names; /O1 for je plus tail-jmp shape.
class Rva001F5DC0Helper {
public:
    virtual ~Rva001F5DC0Helper();
    virtual void u1();
    virtual void* fetch(void* arg);
};
class Rva001F5DC0Slot {
public:
    void* get(void* arg);
    char m_pad[0xAC];
    Rva001F5DC0Helper* m_ptr;
};
void* Rva001F5DC0Slot::get(void* arg)
{
    Rva001F5DC0Helper* p = m_ptr;
    if (p)
        return p->fetch(arg);
    return 0;
}
