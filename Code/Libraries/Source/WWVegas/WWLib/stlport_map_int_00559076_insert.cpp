// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert@?$map@HURva00559076Mapped@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva00559076Mapped@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00559076Mapped@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva00559076Mapped@@@2@@Z @0x005592FB 29B map hint-insert forwards to tree insert_unique 0x0055913B.
// Evidence: callee rowed in StlportIntMapInsertFamily.cpp; caller 0x00559376 in 150B unclaimed user; prev BFMENetwork queues cl /O1 /DNDEBUG /MD /GX.
#include <map>

struct Rva00559076Mapped { int a; };

typedef _STL::map<int, Rva00559076Mapped, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00559076Mapped> > > Map005592FB;

template Map005592FB::iterator Map005592FB::insert(Map005592FB::iterator, const Map005592FB::value_type &);

// Native 559318..5593AE is the stats map subscript: key+PSPlayerAllStats
// default temporary, pair construction, hinted insertion, then reverse teardown.
// WB13F4E50 and the independently rowed112B default/105B copy/75B teardown
// establish the mapped value and its0x548 footprint. The opaque mapped/key
// providers below share this native node/iterator ABI; their existing calls
// keep their current owner names rather than inventing folded aliases.
class PSPlayerAllStats {
public:
 PSPlayerAllStats(int id=0);
 ~PSPlayerAllStats();
 char bytes[0x548];
};
struct Rva005564EBSub;
struct Rva00556306 {
 const int first;
 PSPlayerAllStats second;
 Rva00556306(const int &, const Rva005564EBSub &);
};

typedef _STL::map<int,Rva00559076Mapped> InsertTree;
typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > KeyTree;
namespace _STL {
template<> PSPlayerAllStats &map<int,PSPlayerAllStats>::operator[](const int &key) {
 KeyTree::iterator i=((KeyTree*)this)->lower_bound(key);
 if(i._M_node==((KeyTree*)this)->end()._M_node || key<i->first) {
  i._M_node=((InsertTree*)this)->insert(InsertTree::iterator((_STL::_Rb_tree_node<InsertTree::value_type>*)i._M_node),*(const InsertTree::value_type*)&Rva00556306(key,*(const Rva005564EBSub*)&PSPlayerAllStats()))._M_node;
 }
 return *(PSPlayerAllStats*)((char*)i._M_node+20);
}
}
PSPlayerAllStats &(_STL::map<int,PSPlayerAllStats>::*StatsMapSubscriptBody)(const int&)=&_STL::map<int,PSPlayerAllStats>::operator[];
