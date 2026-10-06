// cl: /MD
// ??0Rva0073F96A@@QAE@HM@Z @0x0073F85D 56B.
// Ctor of MaterialPassClass-derived Rva0073F96A: base ctor row 0x0013EDD0
// then int +0x38, float +0x3C, zero +0x40/+0x44, inc g_bfmeCountAtE1F290.
// Evidence: unlock lane packet; vtable 0x008F1544; callers 0x00362C1E/0x00362C75.
class MaterialPassClass {
public:
    MaterialPassClass();
    virtual ~MaterialPassClass();
};
extern int g_bfmeCountAtE1F290;
class Rva0073F96A : public MaterialPassClass {
public:
    Rva0073F96A(int color, float f);
    virtual ~Rva0073F96A();
    char _pad34[0x34];
    int m_38;
    float m_3c;
    int m_40;
    float m_44;
};
Rva0073F96A::Rva0073F96A(int color, float f)
{
    m_38 = color;
    m_3c = f;
    m_40 = 0;
    m_44 = 0.0f;
    ++g_bfmeCountAtE1F290;
}
