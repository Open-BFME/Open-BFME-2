// ?rva0045F2F8@Rva0045F2F8@@QAEEM@Z
// cl: /O1 /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
//
// ?rva0045F2F8@Rva0045F2F8@@QAEEXM@Z @0x0045F2F8 107B: vslot 23 of SpawnBehavior
// vtable 0x00842550. Predicate taking float (Real maxSelfTaskersRatio) similar
// to donor maySpawnSelfTaskAI: if m_34==0 or arg<=0/NaN vs BfmeZeroRange or
// helper object missing/ret!=2 then false; else (float)m_38/(float)m_34 vs arg.
// Evidence: donor ZH SpawnBehavior.h maySpawnSelfTaskAI; ctor layout +0x34/+0x38;
// virtual call slot 0x23C; BfmeZeroRange extern; g_00BC26EC via unsigned casts.


class Helper0045F2F8
{
public:
    virtual int helper00();
};

class Rva0045F2F8
{
public:
    unsigned char rva0045F2F8(float v);
private:
    char m_00[0x34];
    int m_34;
    unsigned int m_38;
};

unsigned char Rva0045F2F8::rva0045F2F8(float v)
{
    if (m_34 == 0)
        return 0;
    if (v == 0.0f)
        return 0;
    char *base = (char *)this - 0x18;
    void *obj = *(void **)base;
    if (!obj)
        return 0;
    void *inner = *(void **)((char *)obj + 0x258);
    if (!inner)
        return 0;
    int ret = ((int (__fastcall *)(void *))((void ***)inner)[0][0x23C / 4])(inner);
    if (ret != 2)
        return 0;
    float f = (float)m_38 / (float)m_34;
    return v > f ? 1 : 0;
}
