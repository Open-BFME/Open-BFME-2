// cl: /MD
// ?rva0052A36A@Rva0052A36A@@QAEXPAUOut0052A36A@@@Z @0x0052A36A 29B leaf: array element fetch (base+((idx+4)*20)), float@+8 int@+12 to out; caller 0x0052A628
struct Elem0052A36A {
    char m_pad0[8];
    float m_f;
    int m_i;
    char m_pad1[4];
};
struct Out0052A36A {
    float m_f;
    int m_i;
};
class Rva0052A36A {
public:
    void rva0052A36A(Out0052A36A *out);
private:
    void *m_base;
    int m_index;
};
void Rva0052A36A::rva0052A36A(Out0052A36A *out)
{
    char *base = (char *)m_base;
    int off = (m_index + 4) * 20;
    Elem0052A36A *e = (Elem0052A36A *)(base + off);
    int tmpi = e->m_i;
    float tmpf = e->m_f;
    out->m_f = tmpf;
    out->m_i = tmpi;
}
