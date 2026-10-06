// cl: /MD /EHsc
// ?rva0010EC4D@Rva0010EC4D@@QAEXHPAHH_N@Z @0x0010EC4D 104B
// Guarded 9-dword copy with event signal: constructs MilesMutexGuard over
// +4 holder mutex at +0x50 stores args copies 9 dwords to +8 stores +0x30
// stores +0x40 byte calls set at +0x44. Evidence: chain calls 0x0004120E
// ctor and 0x0004122F dtor and 0x00040F9D set; sibling Rva0010ECB5 proves
// +0x44 event layout; caller at 0x000A83D9.
class MilesMutexGuard
{
public:
    MilesMutexGuard(void *m, int x);
    ~MilesMutexGuard();
private:
    void *m_mutex; // +0
    bool m_flag; // +4
};

class Rva0040F9D
{
public:
    virtual ~Rva0040F9D();
    bool set();
};

struct Rva0010EC4DHolder
{
    char m_pad[0x50];
    void *m_mutex; // +0x50
};

class Rva0010EC4D
{
public:
    void rva0010EC4D(int a1, int *a2, int a3, bool a4);
private:
    void *m_unk00; // +0
    Rva0010EC4DHolder *m_holder; // +4
    int m_data[9]; // +8..+0x2B
    int m_a; // +0x2C
    int m_b; // +0x30
    char m_gap[12]; // +0x34..+0x3F
    bool m_c; // +0x40
    char m_pad[3];
    Rva0040F9D m_evt; // +0x44
};

struct NineDwords
{
    int v[9];
};

void Rva0010EC4D::rva0010EC4D(int a1, int *a2, int a3, bool a4)
{
    void *mtx = m_holder->m_mutex;
    MilesMutexGuard guard(mtx, 0);
    m_a = a1;
    *(NineDwords *)m_data = *(NineDwords *)a2;
    m_b = a3;
    m_c = a4;
    m_evt.set();
}
