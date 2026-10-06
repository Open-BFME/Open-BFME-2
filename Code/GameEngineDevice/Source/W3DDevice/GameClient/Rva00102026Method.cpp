// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// ?rva00102026@Rva00102026@@QAEXXZ @0x00102026 97B: unlock method on holder at +0.
// Fills AsciiString temp via virtual slot0 on m_ptr, compares to global
// g_00DEC3B8 via rowed compare 0x000069D6; on equality gets block via virtual
// slot1(0) and operator-delete 0x0002FD60, then nulls m_ptr in both paths.
// Evidence: packet disassembly; sibling factory Rva00101FD8Create same global
// and compare; callers 0x0010223B.

#include "ascii_string.h"

extern const StringBase<char> g_00DEC3B8;

class Inner
{
public:
    virtual AsciiString GetName();
    virtual void *GetBlock(int v);
};

class Rva00102026
{
public:
    void rva00102026();
    Inner *m_ptr;
};

void Rva00102026::rva00102026()
{
    AsciiString tmp = m_ptr->GetName();
    if (((StringBase<char> &)tmp).compare(g_00DEC3B8) == 0) {
        void *p = m_ptr ? m_ptr->GetBlock(0) : (void *)0;
        ::operator delete(p);
    }
    m_ptr = 0;
}
