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
#include "../../../../GameEngine/Include/GameClient/TreeHintOpaque0043671B.h"

// Retail assignment 0x00401F76 copies the owning members, then the two words.
TreeHintOpaque0043671B &TreeHintOpaque0043671B::operator=(const TreeHintOpaque0043671B &other)
{
    m_text = other.m_text;
    m_subobject = other.m_subobject;
    m_wordDEC = other.m_wordDEC;
    m_wordDF0 = other.m_wordDF0;
    return *this;
}

inline bool operator==(const TreeHintOpaque0043671B &x, const TreeHintOpaque0043671B &y) { return x.m_wordDEC == y.m_wordDEC; }
inline bool operator<(const TreeHintOpaque0043671B &x, const TreeHintOpaque0043671B &y) { return x.m_wordDEC < y.m_wordDEC; }
// The exact 0x0043620F insert provider is StlportListInsertFootprints.cpp.
// Its node-creation call stays out of line; do not emit this TU's inlined copy.
template <> _STL::list<TreeHintOpaque0043671B>::iterator
_STL::list<TreeHintOpaque0043671B>::insert(
    _STL::list<TreeHintOpaque0043671B>::iterator, const TreeHintOpaque0043671B &);
template class _STL::list<TreeHintOpaque0043671B, _STL::allocator<TreeHintOpaque0043671B> >;
