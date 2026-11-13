// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 pending-tree insertion used by refresh at 0x006227E0.
// Target evidence: CMP/JAE at 0x00622A32/37 establishes unsigned keys;
// stores at 0x00622A28/2C construct the key / element-pointer pair, and
// the call at 0x00622A57 reaches this 180-byte worker at 0x00759BC0.
// The worker calls the 23-byte pair copy at 0x006204B0 twice. Both bodies
// fold with the existing owners, including every relocation. The original
// record and element names remain unknown; these neutral names preserve
// the view of the rowed pending-tree destructor in StlSweepR3Rva00620A00.cpp.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

class Rva009EF0D0Element;
#include "Rva00620A00Record.h"
typedef _STL::pair<const unsigned int, Rva00620A00Record> RefreshPair;
typedef _STL::_Rb_tree<unsigned int, RefreshPair,
    _STL::_Select1st<RefreshPair>, _STL::less<unsigned int>,
    _STL::allocator<RefreshPair> > RefreshTree;

template RefreshTree::iterator RefreshTree::_M_insert(
    _STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *,
    const RefreshPair &, _STL::_Rb_tree_node_base *);
