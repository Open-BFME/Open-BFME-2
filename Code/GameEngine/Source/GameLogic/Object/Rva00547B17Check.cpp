// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva00547B17Check@@YA_NPAX0@Z retail 0x00547B17 77 bytes.
// Free-function range check: null and flag byte 0x438 early-true plus
// 2D distance-squared against the 400.0f threshold (retail pool 0x00BC5D00;
// float literal links, an extern never does).
// Evidence: single caller 0x00547C58 plus SSE movss comiss shape plus
// prev ArmorStoreCtor O1 flags.
struct Rva00547B17A {
    char _00[0x38];
    float m_x;
    float m_y;
    char _40[0x438 - 0x40];
    unsigned char m_flag438;
};
struct Rva00547B17B {
    float m_x;
    float m_y;
};
bool __cdecl Rva00547B17Check(void *a, void *b)
{
    Rva00547B17A *pa = (Rva00547B17A *)a;
    Rva00547B17B *pb = (Rva00547B17B *)b;
    if (!pa || (pa->m_flag438 & 1))
        return true;
    float dx = pb->m_x - pa->m_x;
    float dy = pb->m_y - pa->m_y;
    float d2 = dx * dx + dy * dy;
    if (400.0f > d2)
        return true;
    return false;
}
