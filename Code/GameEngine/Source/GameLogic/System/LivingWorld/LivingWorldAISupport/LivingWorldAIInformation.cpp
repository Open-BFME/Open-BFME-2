// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
// Native 0050228B..00502363, ret16. WB 012FFE10 has the same traversal.
// Address-derived thiscall owner and pointer/reference spellings remain open.
// Its +4 tree holds the player records used by GatherWorldInformation. Player records embed the 20-byte
// army vector at node+28; each army's +10 points to a region whose first
// word is its region id. Names beyond the existing record owners are open.
// The two searches use the independently rowed int-key node-search ABI;
// no int payload is inferred for the global distance table.
namespace _STL {
template<class T> class allocator;
template<class T> struct less;
template<class T> struct _Select1st;
template<class T1,class T2> struct pair;
struct _Rb_tree_node_base {
 char color;
 _Rb_tree_node_base* parent;
 _Rb_tree_node_base* left;
 _Rb_tree_node_base* right;
};
template<class T> struct _Rb_tree_node;
template<class K,class V,class KeyOfValue,class C,class A> class _Rb_tree {
 template<class SearchKey> _Rb_tree_node<V>* _M_find(const SearchKey&) const;
public:
 ~_Rb_tree();
 template<class SearchKey> __forceinline _Rb_tree_node<V>* findNode(const SearchKey& k) const {return _M_find(k);}
};
template<class T,class A=allocator<T> > class vector {
public:
 T* erase(T*,T*);
 void push_back(const T&);
 __forceinline T* begin(){return start;}
 __forceinline T* stop(){return finish;}
 __forceinline void clear(){erase(begin(),stop());}
 T* start;
 T* finish;
 T* end;
};
template<class K,class V,class C=less<K>,class A=allocator<pair<const K,V> > > class map {
public:
 map();
 char header[12];
};
}
typedef _STL::pair<const int,int> IntIntPair;
typedef _STL::_Rb_tree<int,IntIntPair,_STL::_Select1st<IntIntPair>,_STL::less<int>,_STL::allocator<IntIntPair> > IntIntTree;
// The local unit tree is empty throughout this traversal. Use the actual
// rowed 12-byte tree initialization and scalar-count teardown providers;
// these are ABI views, not claims about its original template spelling.
typedef _STL::map<int,void*> EmptyTreeInit;
struct Rva00501875Count {int value;};
typedef _STL::pair<const int,Rva00501875Count> CountPair;
typedef _STL::_Rb_tree<int,CountPair,_STL::_Select1st<CountPair>,_STL::less<int>,_STL::allocator<CountPair> > CountTree;
struct ArmyUnitTree : private EmptyTreeInit {
 __forceinline ArmyUnitTree(){}
 __forceinline ~ArmyUnitTree(){((CountTree*)this)->~CountTree();}
};
struct Rva00501656 {int regionID;};
struct Rva00501E3FElement {
 int armyID;
 ArmyUnitTree units;
 Rva00501656* region;
 __forceinline Rva00501E3FElement(){}
 Rva00501E3FElement(const Rva00501E3FElement&);
};
struct PlayerNode : public _STL::_Rb_tree_node_base {
 int playerID;
 int playerRecordPrefix[5];
 _STL::vector<Rva00501E3FElement> armies;
};
namespace _STL {
template<class T> class _Rb_global {
public:static _Rb_tree_node_base* _M_increment(_Rb_tree_node_base*);
};
}
class LivingWorldLogic;
extern LivingWorldLogic* TheLivingWorldLogic;
class Rva002E2903Player;
#include "../../../../../Include/GameLogic/Rva002BA8F1Logic.h"
#include "../../../../../Include/GameLogic/Rva002E071E.h"
extern unsigned int g_Va00E04544;
class Rva0050228B {
public:
 void rva0050228B(int playerID,int maxDistance,int* regionID,_STL::vector<Rva00501E3FElement>& out);
 int zero;
 PlayerNode* playerHeader;
};
void Rva0050228B::rva0050228B(int playerID,int maxDistance,int* regionID,_STL::vector<Rva00501E3FElement>& out)
{
 void* distances=((const IntIntTree*)&g_Va00E04544)->findNode(*regionID);
 Rva002E2903Player* player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0);
 out.clear();
 for(PlayerNode* node=(PlayerNode*)playerHeader->left;node!=playerHeader;node=(PlayerNode*)_STL::_Rb_global<bool>::_M_increment(node)) {
  if((unsigned char)((Rva002E071E*)player)->rva002E0BC0(node->playerID)) {
   for(Rva00501E3FElement* a=node->armies.start;a!=node->armies.finish;++a) {
    int otherID=a->region->regionID;
    void* distance=((const IntIntTree*)((const char*)distances+0x20))->findNode(otherID);
    if(*(const int*)((const char*)distance+0x14)<=maxDistance) {
     Rva00501E3FElement info;
     info.armyID=a->armyID;
     out.push_back(info);
    }
   }
  }
 }
}
