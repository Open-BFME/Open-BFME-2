// ??1Rva005CC254@@QAE@XZ
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD
// Native constructor 5CC254/26B and teardown 5CC287/62B share dispatch table
// C74E04 and fields04/08/0C. The teardown has no constructor receiver return;
// its final table C6E330 is the parent observer table (eight RET4 entries).
// Explicit dispatch field retains this TU's established opaque representation.
extern const void *const g_00C74E04[];
extern const void *const g_00C6E330[];
class CreateAHeroData;
class Rva002B7250 { public: void rva002B7250(CreateAHeroData *v); };
struct Rva005CC254Holder { char pad[4]; Rva002B7250 list; };
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva005CC254Base {
public:
    ~Rva005CC254Base() { m_00 = (void *)g_00C6E330; }
    void *m_00;
    void *m_04;
    Rva005CC254Holder *m_08;
    unsigned char m_0c;
};
class Rva005CC254 : public Rva005CC254Base {
public:
    Rva005CC254(void *p);
    ~Rva005CC254();
};
Rva005CC254::Rva005CC254(void *p)
{
    m_08 = 0;
    m_00 = (void *)g_00C74E04;
    m_04 = p;
    m_0c = 1;
}
Rva005CC254::~Rva005CC254()
{
    m_00 = (void *)g_00C74E04;
    _ReadWriteBarrier();
    if (m_08) m_08->list.rva002B7250((CreateAHeroData *)this);
}
