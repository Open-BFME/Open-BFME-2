// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva001DCDAF@Rva001DCDAF@@QAE_NPBUArg001DCDAF@@PBUVec001DCDAF@@1@Z @0x001DCDAF 143B
// Unlock leaf: float max/update vs vector store. Evidence: caller 0x001DD468 (stride 0x30/0x34 arrays),
// BfmeZeroRange at VA 0x00BBAEAC, unsigned fild+fadd 2^32 pattern via g_00BC26EC.

struct Arg001DCDAF
{
    char pad[4];
    unsigned int u4;
    unsigned int u8;
};

struct Vec001DCDAF
{
    float x;
    float y;
    float z;
};

class Rva001DCDAF
{
public:
    bool rva001DCDAF(Arg001DCDAF const *a, Vec001DCDAF const *b, Vec001DCDAF const *c);
    float rva001DCE4C(Arg001DCDAF const *a);

private:
    float m_0;
    float m_4;
    Vec001DCDAF m_8;
    Vec001DCDAF m_14;
    bool m_20;
    bool m_21;
    char m_pad[0x34 - 0x22];
};

bool Rva001DCDAF::rva001DCDAF(Arg001DCDAF const *a, Vec001DCDAF const *b, Vec001DCDAF const *c)
{
    if (m_0 > 0.0f) {
        float f = (float)a->u8;
        if (f > m_0)
            m_0 = f;
        return false;
    } else {
        m_4 = (float)a->u4;
        if (b == 0)
            m_20 = false;
        else {
            m_20 = true;
            m_8 = *b;
        }
        if (c == 0)
            m_21 = false;
        else {
            m_21 = true;
            m_14 = *c;
        }
        return true;
    }
}

float Rva001DCDAF::rva001DCE4C(Arg001DCDAF const *a)
{
    return (float)a->u4 - m_4;
}
