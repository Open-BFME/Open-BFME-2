// cl: /MD
//
// ?rva002BE7DB@Rva002BE7DB@@QBEAAURva002BE7DBValue@@AAU2@@Z, RVA 0x002BE7DB, 23 bytes.
// 12-byte copy: float at +0 via x87 then two dword moves at +4/+8, from this
// to out-param, returning out. Same fld+mov mix as Matrix4D::GetXVector.
// Evidence: caller 0x002BE8F9 fills local [ebp-0x20] from object then uses
// eax (out) as source; caller 0x003FD584 fills [ebp-0x0c] from [ebp-0x28]
// then reads [eax]/[eax+4]; frameless ret-4 with float needs /O1.

struct Rva002BE7DBValue
{
    float x;
    float y;
    float z;
};

class Rva002BE7DB
{
public:
    float m_x;
    float m_y;
    float m_z;
    Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &out) const;
};

Rva002BE7DBValue &Rva002BE7DB::rva002BE7DB(Rva002BE7DBValue &out) const
{
    out.x = m_x;
    out.y = m_y;
    out.z = m_z;
    return out;
}
