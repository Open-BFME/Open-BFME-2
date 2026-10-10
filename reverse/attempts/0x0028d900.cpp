// ?rva0028D900@Object@@QAE_NPAM0@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /arch:SSE
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
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
bool Object::rva0028D900(float *out1, float *out2)
{
    if (m_sub4->m_flag10D & 0x80)
    {
        *out1 = 0.0f;
        *out2 = 0.0f;
        return false;
    }
    float v = 1.5f;
    if (m_sub4)
        v = m_sub4->m_val534;
    float s = max(20.0f, min(150.0f, m_multB8 * v));
    *out1 = 3.0f;
    *out2 = max(20.0f, s * 2.0f);
    return true;
}
