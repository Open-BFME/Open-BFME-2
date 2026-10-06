// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??A?$map@VAsciiString@@UTreeHintPayload002A1D9D@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@4@@_STL@@QAEAAUTreeHintPayload002A1D9D@@ABVAsciiString@@@Z @0x002A57BD 124B
// map operator[]; direct default-construction twin of 0x00218AA4 (124B exact same shape: lowerbound221B8D keyless5598C StringBase-copy365F0 insert2A47C4 release36410); caller 0x002A5B1D in UNCLAIMED 0x002A5A50; tree/insert owned by stlport_rb_tree_hint_002a40c6.cpp; lower_bound is ICF twin of Ref version at 0x00221B8D (key-only traversal, same comparator)
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#include <map>
#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload002A1D9D { int m_val; TreeHintPayload002A1D9D() : m_val(0) {} TreeHintPayload002A1D9D(const TreeHintPayload002A1D9D &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload002A1D9D> TreeHintPair002A1D9D;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair002A1D9D, _STL::_Select1st<TreeHintPair002A1D9D>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair002A1D9D> > TreeHint002A1D9D;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
typedef _STL::map<AsciiString,TreeHintPayload002A1D9D,_STL::less<AsciiString >,_STL::allocator<TreeHintPair002A1D9D> > MapInsert002A57BD;
template TreeHintPayload002A1D9D &MapInsert002A57BD::operator[](const AsciiString &);
