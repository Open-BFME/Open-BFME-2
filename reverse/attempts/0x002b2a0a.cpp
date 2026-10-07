// ?rva002B2A0A@LivingWorldLogic@@QAEXXZ
// partial score=0.9 date=2026-10-07
// ?rva002B2A0A@LivingWorldLogic@@QAEXXZ
// partial score=0.9 date=2026-10-07
// ?rva002B2A0A@LivingWorldLogic@@QAEXXZ
// partial score=0.6 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// Native 0x002B2A0A..0x002B2A95 (RET 0). The transition caller at
// 0x0023D0CD identifies LivingWorldLogic; method purpose remains unresolved.
// Retail fills a zero-initialized XY pair through the +0xB0 host using
// the +0xB8 index, then forwards it to the 0x00DFEF18 singleton and
// copies the pair into singleton fields +0x1C/+0x20.

struct Rva002B2A0APair
{
    float x, y;
    Rva002B2A0APair() : x(0.0f), y(0.0f) {}
    Rva002B2A0APair(const Rva002B2A0APair &other) : x(other.x), y(other.y) {}
};

struct Rva002B2A0ATriple
{
    float x, y, z;
    Rva002B2A0ATriple(const Rva002B2A0APair &pair, float height)
        : x(pair.x), y(pair.y), z(height) {}
    Rva002B2A0ATriple(const Rva002B2A0ATriple &other)
        : x(other.x), y(other.y), z(other.z) {}
    ~Rva002B2A0ATriple() {}
};

class Rva0020F27EHost
{
public:
    bool rva0020F27E(int index, int output);
};

class Rva002BECCD
{
public:
    void rva002BECCD(Rva002B2A0ATriple position);
};

class Rva002D3627Host
{
public:
    unsigned char m_head[0x1C];
    unsigned int m_x, m_y;
    void setX(float x) { m_x = *(unsigned int *)&x; }
    void setY(float y) { m_y = *(unsigned int *)&y; }
};
extern Rva002D3627Host *g_00DFEF18;

class LivingWorldLogic
{
public:
    void rva002B2A0A();
private:
    unsigned char m_head[0xB0];
    Rva0020F27EHost *m_host;
    unsigned int m_unknownB4;
    int m_index;
};

void LivingWorldLogic::rva002B2A0A()
{
    Rva002B2A0APair pair;
    m_host->rva0020F27E(m_index, (int)&pair);
    if (g_00DFEF18)
    {
        ((Rva002BECCD *)g_00DFEF18)->rva002BECCD(Rva002B2A0ATriple(pair, 0.0f));
        Rva002B2A0APair values(pair);
        g_00DFEF18->m_x = *(unsigned int *)&values.x;
        g_00DFEF18->m_y = *(unsigned int *)&values.y;
    }
}
