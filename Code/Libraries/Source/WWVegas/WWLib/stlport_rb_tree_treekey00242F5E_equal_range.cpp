// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// equal_range TreeKey00242F5E set, retail 0x000A7C26, 42 bytes.
// Set equal_range calls rowed _M_upper_bound 0x000A7909 then rowed
// _M_lower_bound 0x000A78D1 and stores the pair. Same 42B shape as 0x005C9F41.
// Evidence: chain from 0x000A7909; caller 0x000A7E41; neighbours 0x000A7BEE
// and 0x000A7C50 share the same tree flags.
#include <set>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "TreeKey00242F5E.h"
struct Rva000A7AA7Less {
    bool operator()(const TreeKey00242F5E &a, const TreeKey00242F5E &b) const;
};
typedef _STL::_Rb_tree<TreeKey00242F5E, TreeKey00242F5E, _STL::_Identity<TreeKey00242F5E>, Rva000A7AA7Less, _STL::allocator<TreeKey00242F5E> > TreeKey00242F5ESetTree;
template _STL::pair<TreeKey00242F5ESetTree::iterator, TreeKey00242F5ESetTree::iterator> TreeKey00242F5ESetTree::equal_range(const TreeKey00242F5ESetTree::key_type &);
