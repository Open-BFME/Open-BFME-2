// cl: /DNDEBUG /MD
// ?rva0039DA2A@Team@@QBEXPAUCoord3D@@@Z @ 0x0039DA2A 202B (ours 202B exact size/count, 0 structural, 0 register)
// Team centroid: averages live member positions. Walks via rowed iterate_TeamMemberList 0x263864 + DLINK advance pin 0x263526 (pin 5911),
// skips Object+0x438 bit0 dead + Object+0x94 bit0 status (TeamHasAnyObjects precedent), sums Object+0x38/0x3C/0x40 Coord3D,
// divides by count via the 1.0f literal at 0xBBB8D8. Neighbours rva0039D9E3/rva0039DC63 share /O1 flags + 24B iterator.
// Near miss: X accumulation operand order (retail movss sum/addss pos vs ours movss pos/addss sum, 2 insns) + global reloc;
// Y/Z, frame, dec-chain-free SSE arithmetic, empty/average shared write tail (ox=x oz=z oy=y order) all exact.

struct Coord3D
{
    float x;
    float y;
    float z;
};

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
    unsigned char m_pad0[4];
    void *m_template;
    unsigned char m_pad08[0x38 - 0x08];
    Coord3D m_position;
    unsigned char m_pad44[0x94 - 0x44];
    unsigned char m_status94;
    unsigned char m_pad95[0x258 - 0x95];
    void *m_ai;
    unsigned char m_pad25C[0x438 - 0x25C];
    unsigned char m_dead;
};

class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
    void rva0039DA2A(Coord3D *out) const;
};

void Team::rva0039DA2A(Coord3D *out) const
{
    Coord3D sum;
    sum.x = 0.0f;
    sum.y = 0.0f;
    sum.z = 0.0f;
    int count = 0;
    for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
        Object *cur = iter.cur();
        if ((cur->m_dead & 1) != 0)
            continue;
        if ((cur->m_status94 & 1) != 0)
            continue;
        sum.x = *(const volatile float *)&sum.x + cur->m_position.x;
        sum.y += cur->m_position.y;
        sum.z += cur->m_position.z;
        ++count;
    }
    float ox;
    float oy;
    float oz;
    if (count > 0) {
        float inv = 1.0f / (float)count;
        ox = sum.x * inv;
        oy = sum.y * inv;
        oz = sum.z * inv;
    }
    else {
        ox = sum.x;
        oz = sum.z;
        oy = sum.y;
    }
    out->x = ox;
    out->y = oy;
    out->z = oz;
}
