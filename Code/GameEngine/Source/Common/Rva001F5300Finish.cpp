// cl: /MD
// ?rva001F5300@Rva001F5300@@QAEXPAM@Z @ 0x001F5300 76B: thiscall writes 2 floats
// to out from extern float g_Va00BBB8D8 or from virtuals slot8/9 at +0x1C4
// returning int converted via cvtsi2ss; caller 0x001F71CF in 0x001F713E.
// The float pair is a 2-element array; that is what makes the compiler reserve
// two 4-byte slots (two push ecx) and spill the first result to [ebp-8] instead
// of reusing a single [ebp-4] temp.
extern float g_Va00BBB8D8;

struct Inner
{
    virtual int s0();
    virtual int s1();
    virtual int s2();
    virtual int s3();
    virtual int s4();
    virtual int s5();
    virtual int s6();
    virtual int s7();
    virtual int s8();
    virtual int s9();
};

class Rva001F5300
{
public:
    void rva001F5300(float *out);
private:
    char m_pad[0x1C4];
    Inner *m_1C4;
};

void Rva001F5300::rva001F5300(float *out)
{
    float f[2];
    f[0] = g_Va00BBB8D8;
    f[1] = g_Va00BBB8D8;
    Inner **pp = &m_1C4;
    Inner *p = *pp;
    if (p)
    {
        f[0] = (float)p->s8();
        f[1] = (float)(*pp)->s9();
    }
    out[0] = f[0];
    out[1] = f[1];
}
