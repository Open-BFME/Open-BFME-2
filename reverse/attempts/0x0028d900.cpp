// ?rva0028D900@Object@@QAE_NPAM0@Z
// partial score=0.96 date=2026-10-06
// ?rva0028D900@Object@@QAE_NPAM0@Z
// partial score=0.96 date=2026-10-03
// ?rva0028D900@Object@@QAE_NPAM0@Z
// partial score=0.95 date=2026-10-01
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva0028D900@Object@@QAE_NPAM0@Z, RVA 0x0028D900, 154B. Unlock lane:
// Object __thiscall bool(float*,float*) proven by ecx use ret 8; flag at
// [ecx+4]+0x10d bit 0x80 early-out zeros; float at +0x534 or default
// g_00BC8980 scaled by +0xb8 clamped low g_bfmeClearA high g_00BED19C
// then *g_Va00BC28F4 low-clamped; out1 const g_00BC7508. Neighbours
// Rva0028D8EB.cpp ObjectRva0028D9E5.cpp share /O1 /DNDEBUG /MD.
extern const float g_bfmeClearA;
extern float g_Va00BC28F4;
extern float g_00BC8980;
extern float g_00BED19C;
extern float g_00BC7508;

struct Sub028D900
{
    char m_pad[0x10D];
    unsigned char m_flag10D;
    char m_pad2[0x534 - 0x10D - 1];
    float m_val534;
};

class Object
{
public:
    bool rva0028D900(float *out1, float *out2);
private:
    char m_pad0[4];
    Sub028D900 *m_sub4;
    char m_pad8[0xB0];
    float m_multB8;
};

// ?rva0028D900@Object@@QAE_NPAM0@Z present-unmatched
bool Object::rva0028D900(float *out1, float *out2)
{
    if (m_sub4->m_flag10D & 0x80)
    {
        *out1 = 0.0f;
        *out2 = 0.0f;
        return false;
    }
    float v = g_00BC8980;
    if (m_sub4)
        v = m_sub4->m_val534;
    float mult = m_multB8;
    float low = g_bfmeClearA;
    float s = v * mult;
    float high = g_00BED19C;
    if (s <= high)
    {
        if (low > s)
            s = low;
        else if (high < s)
            s = high;
    }
    else if (high < s)
    {
        s = high;
    }
    float t = s * g_Va00BC28F4;
    *out1 = g_00BC7508;
    if (t < low)
        t = low;
    *out2 = t;
    return true;
}
