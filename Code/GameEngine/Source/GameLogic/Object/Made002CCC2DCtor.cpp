// cl: /DNDEBUG /MD /EHsc
// ??0Made002CCC2D@@QAE@XZ, retail 0x0050BB0E 88B.
// Base Rva00507823 plus member at +0x128 via pinned 0x003623E5,
// int at +0x12c=0, three floats at +0x130 zeroed (SSE). Caller
// parseSpawnAndFadeNugget 0x002CCC52. Made002CCBCA precedent.
class Rva00507823
{
public:
    virtual ~Rva00507823();
    Rva00507823();
private:
    char m_pad04[0x128 - 4];
};
class Rva003623E5Member
{
public:
    Rva003623E5Member();
};
class Made002CCC2D : public Rva00507823
{
public:
    Made002CCC2D();
    virtual ~Made002CCC2D();
private:
    Rva003623E5Member m_128;
    int m_12c;
    float m_130;
    float m_134;
    float m_138;
};
Made002CCC2D::Made002CCC2D()
    : m_12c(0)
{
    float *p = &m_130;
    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;
}
