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
    Rva00041344Holder() : m_p(0) {}
    void *m_p;
    ~Rva00041344Holder() { ::operator delete[](m_p); }
};
class Rva00041118Obj;
struct Rva00041389Objects
{
    Rva00041118Obj **first;
    Rva00041118Obj **last;
};
class Rva00041078
{
public:
    Rva00041078(const Rva00041389Objects &objects, int nonBlocking);
    bool rva00041078(unsigned long timeout, int single, int *out);
    bool rva00041118();
    void rva0004123B(int count);
    void rva0004128E();
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

// Native 0x00041389..0x00041403: construct from a pointer-range view,
// initialize three array owners, then use the rowed storage helpers and wait.
// The leading first/last words are proven; the original container is unknown.
// The second argument is tested as a dword and skips the blocking wait if set.
Rva00041078::Rva00041078(const Rva00041389Objects &objects, int nonBlocking)
{
    rva0004123B(objects.last - objects.first);
    for (int i = 0; i < m_count; ++i)
        ((Rva00041118Obj **)m_objs)[i] = objects.first[i];
    rva0004128E();
    if (nonBlocking == 0)
        rva00041078((unsigned long)-1, 0, 0);
}
