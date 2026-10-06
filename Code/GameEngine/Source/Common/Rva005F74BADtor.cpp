// cl: /MD
// ??1Rva005F74BA@@QAE@XZ retail 0x005F74BA 26B
// Evidence: same 26B owning-pointer shape as rowed clear 0x005F74A0 via rowed virtual dtor 0x005F6AB0 plus operator delete 0x0002FD60; needed as array element dtor for outer 0x005F75C9 via EH vector dtor.
void __cdecl operator delete(void *p);

class Rva005F6AB0
{
public:
    virtual ~Rva005F6AB0();
};

struct Rva005F74BA
{
    Rva005F6AB0 *m_ptr;
    ~Rva005F74BA();
};

Rva005F74BA::~Rva005F74BA()
{
    Rva005F6AB0 *p = m_ptr;
    m_ptr = 0;
    if (p)
    {
        p->Rva005F6AB0::~Rva005F6AB0();
        ::operator delete(p);
    }
}
