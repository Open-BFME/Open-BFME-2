// cl: /O1 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii
// stlport
// Twin lead: stlport_rb_tree_hint_asciistring_pair.cpp, subscript 2031FB.
// Target 4491CB..449258 builds two wide strings through 4480BE and releases
// them through 448089. The returned mapped string is at node+14. Original
// map type is unknown; retain the existing address-derived provider views.
#include <set>
#include "unicode_string.h"
struct BfmeStringRecord00448113 { unsigned char m_data[8]; };
bool operator<(const BfmeStringRecord00448113 &,const BfmeStringRecord00448113 &);
typedef _STL::_Rb_tree<BfmeStringRecord00448113,BfmeStringRecord00448113,_STL::_Identity<BfmeStringRecord00448113>,_STL::less<BfmeStringRecord00448113>,_STL::allocator<BfmeStringRecord00448113> > LowerTree;
struct Rva00448FF2Record {
 Rva00448FF2Record(); Rva00448FF2Record(const Rva00448FF2Record&);
 ~Rva00448FF2Record(); Rva00448FF2Record&operator=(const Rva00448FF2Record&);
 char bytes[8];
};
bool operator<(const Rva00448FF2Record &,const Rva00448FF2Record &);
typedef _STL::_Rb_tree<Rva00448FF2Record,Rva00448FF2Record,_STL::_Identity<Rva00448FF2Record>,_STL::less<Rva00448FF2Record>,_STL::allocator<Rva00448FF2Record> > InsertTree;
namespace _STL {
template<> LowerTree::_Link_type LowerTree::_M_lower_bound(const BfmeStringRecord00448113 &) const;
template<> InsertTree::iterator InsertTree::insert_unique(InsertTree::iterator,const Rva00448FF2Record &);
}
class Rva00448089 {
public:
 Rva00448089(const UnicodeString &,const UnicodeString &);
 ~Rva00448089();
private:
 UnicodeString m_00,m_04;
};
class Rva004491CB {
public:
 UnicodeString &rva004491CB(const UnicodeString &key);
 __declspec(noinline) InsertTree::iterator rva004491AE(InsertTree::iterator hint,const Rva00448089 &value);
private:
 _STL::_Rb_tree_node_base *m_header;
};
InsertTree::iterator Rva004491CB::rva004491AE(InsertTree::iterator hint,const Rva00448089 &value) {
 return reinterpret_cast<InsertTree *>(this)->insert_unique(hint,reinterpret_cast<const Rva00448FF2Record &>(value));
}
UnicodeString &Rva004491CB::rva004491CB(const UnicodeString &key) {
 _STL::_Rb_tree_node_base *node = reinterpret_cast<LowerTree *>(this)->lower_bound(reinterpret_cast<const BfmeStringRecord00448113 &>(key))._M_node;
 if (node == m_header || reinterpret_cast<const BfmeStringRecord00448113 &>(key) < *reinterpret_cast<const BfmeStringRecord00448113 *>((char *)node+0x10)) {
  UnicodeString empty;
  node=rva004491AE(InsertTree::iterator(static_cast<InsertTree::_Link_type>(node)),Rva00448089(key,empty))._M_node;
 }
 return *reinterpret_cast<UnicodeString *>((char *)node+0x14);
}
