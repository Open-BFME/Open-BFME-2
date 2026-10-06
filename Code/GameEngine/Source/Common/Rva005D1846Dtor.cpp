// cl: /EHsc /MD
// ??1Rva005D1846@@QAE@XZ @0x005D1846 75B
// Non-virtual dtor with two EH-tracked members plus user forwarder call: user calls m_04->rva0057C2CC then implicit destroys m_10 via free then m_0C via clear.
// Evidence: deleting dtor callers 0x005D1891 and 0x005D18C8; callees rowed 0x0057C2CC 0x000AD6F4 and free 0x00030830; states 1 0 -1 match two members; no vtable so QAE.
class Rva0057C2CC
{
public:
    void rva0057C2CC();
};
class Rva000AD6F4
{
public:
    void clear();
private:
    char m_pad[4];
};
void __cdecl free(void *); // C++ decl keeps EH state around free (task 5)
struct W0C
{
    Rva000AD6F4 m;
    ~W0C() { m.clear(); }
};
struct W10
{
    void *p;
    ~W10() { if (p) free(p); }
};
class Rva005D1846
{
public:
    ~Rva005D1846();
private:
    char m_00[4];
    Rva0057C2CC *m_04;
    char m_08[4];
    W0C m_0C;
    W10 m_10;
};
Rva005D1846::~Rva005D1846()
{
    m_04->rva0057C2CC();
}
