// cl: /MD
// ?rva004E93E8@Rva004E93E8@@QAEPAXXZ @0x004E93E8 49B search ptr array +0xc +0x10 for [elem+0x5c]==1 or global flag caller 0x004E9710
struct Elem004E93E8 { char _pad[0x5c]; int m_5c; };
struct Glob004E93E8 { char _pad[0x860]; unsigned char m_860; };
extern Glob004E93E8 *g_00DFEEF8;
class Rva004E93E8
{
public:
    char _pad0[0xc];
    Elem004E93E8 **m_begin;
    Elem004E93E8 **m_end;
    void *rva004E93E8();
};

void *Rva004E93E8::rva004E93E8()
{
    void *found = 0;
    Elem004E93E8 **p = m_begin;
    Elem004E93E8 **e = m_end;
    for (;;) {
        if (p == e)
            break;
        Elem004E93E8 *cur = *p;
        if (cur->m_5c == 1 || g_00DFEEF8->m_860 != 0)
            found = cur;
        ++p;
        if (found == 0)
            continue;
        break;
    }
    return found;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DFEEF8@@3PAUGlob004E93E8@@A=?g_00DFEEF8@@3PAVRva002A8F24@@A")
