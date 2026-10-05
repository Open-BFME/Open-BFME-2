// stlport
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// BFME1 RvaTreeInsertUniqueHint.cpp and STLport pair/tree are the semantic donor.
// BFME2 comparator0x206BCF orders two AsciiStrings lexicographically.
// Key copy0x20492B calls AsciiString copy0x365F0 twice.
// Node0x32B62F allocates28bytes; paircopy0x32ACB4 copies mapped dword+8.
// The original mapped type and its destruction remain unknown.
#include <map>
template <class T> class StringBase
{
    void *m_data;
    StringBase(const StringBase<T> &);
    void releaseBuffer();
    friend class AsciiString;
};
class AsciiString
{
public:
    __forceinline AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
    }
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
private:
    void *m_data;
};
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::pair<AsciiString,AsciiString> TreeKey00206BCF;
bool operator<(const TreeKey00206BCF &, const TreeKey00206BCF &);
struct TreeOpaqueMapped0032CB55 { unsigned int m_bits; ~TreeOpaqueMapped0032CB55(); };
typedef _STL::pair<const TreeKey00206BCF,TreeOpaqueMapped0032CB55> TreePair0032CB55;
typedef _STL::_Rb_tree<TreeKey00206BCF,TreePair0032CB55,_STL::_Select1st<TreePair0032CB55>,_STL::less<TreeKey00206BCF>,_STL::allocator<TreePair0032CB55> > Tree0032CB55;
namespace _STL { template <> class allocator<char> { public: static char *allocate(unsigned int bytes,const void *hint); }; }
// ?_M_create_node@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UTreeOpaqueMapped0032CB55@@@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UTreeOpaqueMapped0032CB55@@@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UTreeOpaqueMapped0032CB55@@@_STL@@@2@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UTreeOpaqueMapped0032CB55@@@_STL@@@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@UTreeOpaqueMapped0032CB55@@@2@@Z
template <> Tree0032CB55::_Link_type Tree0032CB55::_M_create_node(const TreePair0032CB55 &value) { _Link_type node=(_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<TreePair0032CB55>),0); _STL::_Construct(&node->_M_value_field,value); return node; }
template Tree0032CB55::iterator Tree0032CB55::insert_unique(Tree0032CB55::iterator,const TreePair0032CB55 &);

// The map wrapper directly calls this tree's verified hinted insertion.
typedef _STL::map<TreeKey00206BCF,TreeOpaqueMapped0032CB55,_STL::less<TreeKey00206BCF>,_STL::allocator<TreePair0032CB55> > Map0032CB55;
template Map0032CB55::iterator Map0032CB55::insert(Map0032CB55::iterator, const TreePair0032CB55 &);

// Retail0x32C4A4 uses the proven two-AsciiString comparator206BCF.
template Tree0032CB55::_Link_type Tree0032CB55::_M_lower_bound(const TreeKey00206BCF &) const;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva0033CopyBase@@QAE@ABV0@@Z=??0?$pair@VAsciiString@@V1@@_STL@@QAE@ABU01@@Z")
