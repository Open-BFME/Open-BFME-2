// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
#include <string>



// BFME1 RvaTreeInsertUniqueHint.cpp and STLport tree/pair semantic donor.
// Comparator0x388F39 passes narrow-string begin/end pointers to compare0x24FC0.
// Paircopy0x389DD6 calls known basic_string<char> copy0x9170, then copies dword+12.
// Node0x38AAA8 allocates32bytes: links16 + narrow string12 + mapped4.
// Retail map subscript0x38E041 proves zero-initialized scalar storage and
// trivial mapped cleanup. The original application meaning remains unknown.
// Use a 32-bit scalar model in place of the earlier opaque class placeholder.
typedef unsigned int TreePayload0038D58C;
typedef _STL::pair<const _STL::basic_string<char>, TreePayload0038D58C> TreePair0038D58C;
typedef _STL::_Rb_tree<_STL::basic_string<char>, TreePair0038D58C, _STL::_Select1st<TreePair0038D58C>, _STL::less<_STL::basic_string<char> >, _STL::allocator<TreePair0038D58C> > Tree0038D58C;
template Tree0038D58C::iterator Tree0038D58C::insert_unique(Tree0038D58C::iterator, const TreePair0038D58C &);

namespace _STL { template <> class allocator<char> { public: static char *allocate(unsigned int bytes, const void *hint); __forceinline static void deallocate(char *p, unsigned int) { if (p) ::free(p); } }; }
template <> Tree0038D58C::_Link_type Tree0038D58C::_M_create_node(const TreePair0038D58C &value)
{
    _Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreePair0038D58C>), 0);
    _STL::_Construct(&node->_M_value_field, value);
    return node;
}

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<_STL::basic_string<char>,TreePayload0038D58C,_STL::less<_STL::basic_string<char> >,_STL::allocator<TreePair0038D58C> > MapInsert0038d58c;
template MapInsert0038d58c::iterator MapInsert0038d58c::insert(MapInsert0038d58c::iterator, const TreePair0038D58C &);

template Tree0038D58C::_Link_type Tree0038D58C::_M_lower_bound(const _STL::basic_string<char> &) const;


template TreePayload0038D58C &MapInsert0038d58c::operator[](const _STL::basic_string<char> &);

// Retail0x389291 uses the independently matched narrow-string comparator388F39 twice.
template Tree0038D58C::iterator Tree0038D58C::find(const _STL::basic_string<char> &);
