// cl: /MD
// ?rva004E93A8@Rva004E93A8@@QAEHXZ @0x004E93A8 64B count ptr array +0xc +0x10 where get()==0 and (elem+0x5c==1 or global flag) callees get 0x002AA22A callers 0x002C6C6D 0x004E974A
class Rva002AA22AByteField
{
public:
    unsigned char get() const;
};
struct Glob004E93A8 { char _pad[0x860]; unsigned char m_860; };
extern Glob004E93A8 *g_00DFEEF8;
class Rva004E93A8
{
public:
    char _pad0[0xc];
    Rva002AA22AByteField **m_begin;
    Rva002AA22AByteField **m_end;
    int rva004E93A8();
};

int Rva004E93A8::rva004E93A8()
{
    int count = 0;
    Rva002AA22AByteField **p = m_begin;
    Rva002AA22AByteField **e = m_end;
    for (;;) {
        if (p == e)
            break;
        Rva002AA22AByteField *cur = *p;
        if (cur->get() == 0) {
            if (*(int *)((char *)cur + 0x5c) == 1 || g_00DFEEF8->m_860 != 0)
                ++count;
        }
        ++p;
    }
    return count;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DFEEF8@@3PAUGlob004E93A8@@A=?g_00DFEEF8@@3PAVRva002A8F24@@A")
