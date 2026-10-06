// cl: /MD
// ?rva0037E421@Rva0037E421@@QAEPAXH@Z @0x0037E421 48B
// Bounds-checked accessor for the 216-byte (0xD8) element vector at +0x04/+0x08.
// Returns null when index < 0 or index >= (finish-start)/216 via signed idiv (cdq),
// else start+index*216. Proven by 14 direct callers needing this exact shape.
// Unlock lane; landing unblocks 11 functions. No donor; recipe follows
// Rva00219B9EAccessor signed-idiv precedent with /O1 keeping idiv.
// Honest-address name: owner unknown so Rva0037E421 class, void* return, int index.
struct Elem216 { char m_pad00[0x98]; int m_98; char m_pad9C[0xA4 - 0x9C]; int m_a4; char m_padA8[0xCC - 0xA8]; float m_cc; char m_padD0[0xD8 - 0xD0]; };
struct Vec216 { Elem216 *m_start; Elem216 *m_finish; Elem216 *m_end; };
static __forceinline unsigned VecSize(Vec216 *v) { return v->m_finish - v->m_start; }
static __forceinline Elem216 &VecAt(Vec216 *v, int i) { return v->m_start[i]; }
class Rva0037E270 { public: void *rva0037E270(); };
class Rva0037E421 {
    int m_00;
    Vec216 m_vec;
public:
    void *rva0037E421(int index);
    unsigned char rva0037E7BC(int index);
    void *rva0037E451(int key);
    unsigned char rva0037E7DA(int key);
    void *rva0037E7A5(int index);
};
void *Rva0037E421::rva0037E421(int index)
{
    if (index < 0)
        return 0;
    unsigned int count = VecSize(&m_vec);
    if ((unsigned int)index < count)
        return &VecAt(&m_vec, index);
    return 0;
}
// ?rva0037E7BC@Rva0037E421@@QAEEH@Z @0x0037E7BC 30B
// Chain of rva0037E421; returns element+0x98 == -1 as unsigned char, else 0.
// Proven by caller at 0x00392C96 and the rowed callee; same class and flags.
unsigned char Rva0037E421::rva0037E7BC(int index)
{
    void *p = rva0037E421(index);
    if (!p)
        return 0;
    return ((Elem216 *)p)->m_98 == -1;
}
// ?rva0037E451@Rva0037E421@@QAEPAXH@Z @0x0037E451 34B
// Linear search of the same 216-byte vector for element with m_a4 == key.
// Proven by 4 callers and the +4/+8 vector with 0xD8 stride; same class and flags.
void *Rva0037E421::rva0037E451(int key)
{
    Elem216 *p = m_vec.m_start;
    Elem216 *end = m_vec.m_finish;
    for (; p != end; ++p) {
        if (p->m_a4 == key)
            return p;
    }
    return 0;
}
// ?rva0037E7DA@Rva0037E421@@QAEEH@Z @0x0037E7DA 59B
// Chain of rva0037E451; if element missing or m_98 == -1 return 0 else set
// m_98/m_a4 to -1 via or -1, m_cc to 1.0f via movss, return 1. Proven by caller
// at 0x0049DCE7 and the shared 1.0f literal at 0x00BBB8D8; same class, /arch:SSE for movss.
unsigned char Rva0037E421::rva0037E7DA(int key)
{
    Elem216 *e = (Elem216 *)rva0037E451(key);
    if (!e)
        return 0;
    if (e->m_98 != -1) {
        e->m_98 = -1;
        e->m_a4 = -1;
        e->m_cc = 1.0f;
        return 1;
    }
    return 0;
}
// ?rva0037E7A5@Rva0037E421@@QAEPAXH@Z @0x0037E7A5 23B
// Chain of rva0037E421 then rowed Rva0037E270::rva0037E270; null if element missing.
// Proven by 5 callers and rowed callees 0x0037E421 and 0x0037E270; same class and flags.
void *Rva0037E421::rva0037E7A5(int index)
{
    void *p = rva0037E421(index);
    if (!p)
        return 0;
    return ((Rva0037E270 *)p)->rva0037E270();
}
