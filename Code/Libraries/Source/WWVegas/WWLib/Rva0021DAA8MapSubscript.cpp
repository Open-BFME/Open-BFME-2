// cl: /O1 /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii
// stlport
// Native21DAA8..21DB35 is the signed-key twin of5E017A. Its default
// record has a scalar and three narrow strings; existing21A940 construction
// and21A75E teardown independently establish the16B mapped layout.
#include <map>
#include "ascii_string.h"
struct BfmeStringRecord00219B0B {
 unsigned int word0; AsciiString text0,text1,text2;
 BfmeStringRecord00219B0B():word0(0){}
 BfmeStringRecord00219B0B(const BfmeStringRecord00219B0B &);
 ~BfmeStringRecord00219B0B();
};
struct BfmeStringRecord0021A940 {
 unsigned int word0; BfmeStringRecord00219B0B rec;
 BfmeStringRecord0021A940(const unsigned int *,const BfmeStringRecord00219B0B &);
};
struct Rva0021D657Record { char bytes[1]; };
typedef _STL::map<int,Rva0021D657Record> InsertMap;
namespace _STL { template<> InsertMap::iterator InsertMap::insert(InsertMap::iterator,const InsertMap::value_type &); }
typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > LowerTree;
namespace _STL { template<> LowerTree::_Link_type LowerTree::_M_lower_bound(const int &) const; }
class Rva0021DAA8 {
public: BfmeStringRecord00219B0B &rva0021DAA8(const int &key);
private: _STL::_Rb_tree_node_base *m_head;
};
BfmeStringRecord00219B0B &Rva0021DAA8::rva0021DAA8(const int &key) {
 _STL::_Rb_tree_node_base *node=reinterpret_cast<LowerTree *>(this)->lower_bound(key)._M_node;
 if (node==m_head || key < *reinterpret_cast<const int *>((char *)node+0x10)) {
  BfmeStringRecord00219B0B empty;
  node=reinterpret_cast<InsertMap *>(this)->insert(InsertMap::iterator(static_cast<InsertMap::iterator::_Link_type>(node)),reinterpret_cast<const InsertMap::value_type &>(BfmeStringRecord0021A940(reinterpret_cast<const unsigned int *>(&key),empty)))._M_node;
 }
 return *reinterpret_cast<BfmeStringRecord00219B0B *>((char *)node+0x14);
}
