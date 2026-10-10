// stlport
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// BFME1 RvaTreeInsertUniqueHint.cpp and STLport tree/pair semantic donor.
// Comparator0x240CE0 orders signed dword then AsciiString at key+4.
// Keycopy0xCF475 calls AsciiString copy0x365F0; paircopy0x23E90D adds mapped dword+8.
// Node0x240DF1 allocates28bytes. Original application names remain unknown.
// Subscript0x246FF6 proves zero-initialized mapped storage and trivial cleanup:
// the temporary destroys only its key's AsciiString through releaseBuffer36410.
#include <map>
template<class T> class StringBase { void *m_data; void releaseBuffer(); StringBase(const StringBase<T> &); friend class AsciiString; protected: __forceinline ~StringBase() { releaseBuffer(); } };
class AsciiString : private StringBase<char> { public: __forceinline AsciiString(const AsciiString &that) : StringBase<char>(*(const StringBase<char> *)&that) {} __forceinline ~AsciiString() {} };
bool operator<(const AsciiString &, const AsciiString &);
struct TreeKey00242F5E { int m_id; AsciiString m_name; };
inline bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b) { return a.m_id < b.m_id || (!(b.m_id < a.m_id) && a.m_name < b.m_name); }
struct TreeOpaqueMapped242F5E { unsigned int m_bits; __forceinline TreeOpaqueMapped242F5E() : m_bits(0) {} };
typedef _STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> IntAsciiPair;
typedef _STL::_Rb_tree<TreeKey00242F5E, IntAsciiPair, _STL::_Select1st<IntAsciiPair>, _STL::less<TreeKey00242F5E>, _STL::allocator<IntAsciiPair> > Tree242F5E;
namespace _STL { template <> class allocator<char> { public: static char *allocate(unsigned int bytes,const void *hint); }; }
// ?_M_create_node@?$_Rb_tree@UTreeKey00242F5E@@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapped242F5E@@@_STL@@U?$_Select1st@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapped242F5E@@@_STL@@@3@U?$less@UTreeKey00242F5E@@@3@V?$allocator@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapped242F5E@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapped242F5E@@@_STL@@@2@ABU?$pair@$$CBUTreeKey00242F5E@@UTreeOpaqueMapped242F5E@@@2@@Z
template <> Tree242F5E::_Link_type Tree242F5E::_M_create_node(const IntAsciiPair &value) { _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<IntAsciiPair>),0); _STL::_Construct(&node->_M_value_field,value); return node; }
template Tree242F5E::iterator Tree242F5E::insert_unique(Tree242F5E::iterator, const IntAsciiPair &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<TreeKey00242F5E,TreeOpaqueMapped242F5E,_STL::less<TreeKey00242F5E >,_STL::allocator<IntAsciiPair> > MapInsert00242f5e;
template MapInsert00242f5e::iterator MapInsert00242f5e::insert(MapInsert00242f5e::iterator, const IntAsciiPair &);

// Lookup 0x24197A calls the proven key comparator 0x240CE0.
// The retail subscript at 0x246FF6 uses it on the same tree as insert0x242F5E.
template Tree242F5E::_Link_type Tree242F5E::_M_lower_bound(const TreeKey00242F5E &) const;
// _M_find at 0x241BD2 compares the same typed key twice; caller0x246FB0
// retrieves the mapped dword at node+0x18, matching this proven 28-byte node.
template Tree242F5E::iterator Tree242F5E::find(const TreeKey00242F5E &);

template TreeOpaqueMapped242F5E &MapInsert00242f5e::operator[](const TreeKey00242F5E &);

// Retail0x23FBC0 constructs the proven key then copies the separate mapped
// argument to value+8; its ret8 distinguishes this from the pair copy ctor.
template IntAsciiPair::pair(const TreeKey00242F5E &, const TreeOpaqueMapped242F5E &);
