// cl: /MD /EHsc
// ??1Rva00041078@@QAE@XZ @0x00041344 69B
// Non-virtual dtor of the wait-set class: body re-queries via rva00041118
// then three trailing ArrayHolders at +0x58/+0x5C/+0x60 inline to delete[].
// Evidence: chain lane (calls 0x00041118 rowed in Rva00041078Wait.cpp at
// 0x4135C); callees 0x0002FD80 operator delete[] rowed in mem_ops.cpp;
// unwind callers jmp here from Unwind@00bab2f8/00bab366; state 2 reflects
// three members; throw() on delete[] removes inter-delete state stores.
void __cdecl operator delete[](void *block) throw();
struct Rva00041344Holder
{
    void *m_p;
    ~Rva00041344Holder() { ::operator delete[](m_p); }
};
class Rva00041078
{
public:
    bool rva00041118();
    ~Rva00041078();
private:
    void *m_handles;
    void *m_objs;
    void *m_done;
    int m_count;
    unsigned char m_pad[0x58 - 0x10];
    Rva00041344Holder m_58;
    Rva00041344Holder m_5c;
    Rva00041344Holder m_60;
};
Rva00041078::~Rva00041078()
{
    rva00041118();
}
