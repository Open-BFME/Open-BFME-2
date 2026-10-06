// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?clear@?$_List_base@UTreeHintOpaque0043671B@@V?$allocator@UTreeHintOpaque0043671B@@@_STL@@@_STL@@QAEXXZ @0x00434EC9 49B: list clear of TreeHintOpaque0043671B via rowed dtor 0x00229840 and _free; empty-check plus sentinel reset match list<int> precedent.
// Layout from copy 0x0022D106 (UnicodeString +0, 0xDE8 subobject +4, words DEC/DF0); value at node+8 proves list node.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "unicode_string.h"
struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char m_opaque[0xDE4];
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC, m_wordDF0;
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();
};
inline bool operator==(const TreeHintOpaque0043671B &x, const TreeHintOpaque0043671B &y) { return x.m_wordDEC == y.m_wordDEC; }
inline bool operator<(const TreeHintOpaque0043671B &x, const TreeHintOpaque0043671B &y) { return x.m_wordDEC < y.m_wordDEC; }
template class _STL::list<TreeHintOpaque0043671B, _STL::allocator<TreeHintOpaque0043671B> >;
