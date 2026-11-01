// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Oi /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva000591A3@Rva000591A3@@QAEXABVAsciiString@@@Z @ 0x000591A3 76B: thiscall
// inserts AsciiString into set at +0xA0 via row 0x0005897D then if inserted
// and float at +0x9C != 1.0f fills 48B at +0x188 with 0x02.
// Caller 0x00059A5C in 0x00059A25.
#include <set>
#include <cstring>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}


#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left < right;
    }
};
}

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

class Rva000591A3
{
public:
    void rva000591A3(const AsciiString &name);
    void rva000591EF();
private:
    char m_pad[0x9C];
    float m_9C;
    _STL::set<AsciiString> m_A0;
    char m_padAC[0x188 - 0xAC];
    unsigned char m_188[48];
};

void Rva000591A3::rva000591A3(const AsciiString &name)
{
    if (!m_A0.insert(name).second)
        return;
    if (m_9C != 1.0f)
    {
        for (int i = 0; i < 12; ++i)
            ((int *)m_188)[i] = 0x02020202;
    }
}

// ?rva000591EF@Rva000591A3@@QAEXXZ at 0x000591EF (62B).
// Sibling of 0x000591A3: if set empty return else if float != global fill 48B
// then tail-jmp tree clear. Evidence: cmp [edx+0xA4] via empty() plus movss/
// ucomiss vs 1.0f plus rep stosd 0xC then lea+jmp 0x57B4B. Caller 0x59AB0.
void Rva000591A3::rva000591EF()
{
    if (m_A0.empty())
        return;
    if (m_9C != 1.0f)
    {
        for (int i = 0; i < 12; ++i)
            ((int *)m_188)[i] = 0x02020202;
    }
    m_A0.clear();
}
