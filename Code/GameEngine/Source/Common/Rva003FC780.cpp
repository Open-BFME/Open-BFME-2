// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva003FC780@Rva003FB65C@@QAEPAVHTreeClass@@PBVAsciiString@@H@Z @0x003FC780 71B
// Chain after rva003FB65C: releases old HTree at +0x18 via ref at +4 slot00 clears
// then GetAnimTree via AsciiString first-dword t+8 or empty stores calls rva003FB65C returns tree.
// Evidence: rowed callees rva003FB65C 0x003FB65C GetAnimTree 0x0014CF5F and g_Rva0107301CEmptyString.
#include "ascii_string.h"

class HTreeClass
{
public:
    virtual void slot00();
    int m_ref;
};

HTreeClass *Rva0014CF5F_GetAnimTree(const char *name);


class Rva003FB65C
{
public:
    HTreeClass *rva003FC780(const AsciiString *name, int x);
    void rva003FB65C(int x);
private:
    char m_pad00[8];
    void *m_ptr08;
    char m_pad0C[12];
    HTreeClass *m_tree;
};
HTreeClass *Rva003FB65C::rva003FC780(const AsciiString *name, int x)
{
    HTreeClass *old = m_tree;
    if (old)
    {
        if (--old->m_ref == 0)
            old->slot00();
        m_tree = 0;
    }
    const char *t = *(const char * const *)name;
    const char *animName = t ? t + 8 : "";
    HTreeClass *newTree = Rva0014CF5F_GetAnimTree(animName);
    m_tree = newTree;
    rva003FB65C(x);
    return m_tree;
}
