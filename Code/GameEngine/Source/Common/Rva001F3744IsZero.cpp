// cl: /O1 /MD /arch:SSE /G6
// ?Rva001F3744IsZero@@YA_NPBUS001F3744@@@Z @0x001F3744 42B
// Evidence: __cdecl free predicate returning both-floats-zero via ucomiss
// lahf test jp; callers 40x incl 0x001F8FF4 test al al; prev/next SSE flags.
struct S001F3744
{
    char m_00[4];
    float m_04;
    float m_08;
};

bool __cdecl Rva001F3744IsZero(const S001F3744 *p)
{
    return p->m_04 == 0.0f && p->m_08 == 0.0f;
}
