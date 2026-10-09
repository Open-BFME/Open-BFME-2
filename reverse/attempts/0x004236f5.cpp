// ?Rva004236F5Sort@@YAXAAUMiniList00421E1C@@VRva00421A16@@@Z
// partial score=0.9569199942750822 date=2026-10-10
// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
// Reference: STLport4.5.3 _list.c _S_sort carry/64counter binary merge algorithm,
// BFME1 committed575ba2b04743f190f069805fbdc59936123c45da.
// Target: native004236F5..00423890 RET0, WB01144650 unnamed975B same algorithm.
// Calls pushVA005EB940/005EB984/005EB769 resolve to already rowed RVAs
// 001EB940 destructor5B /001EB984 initializer40B /001EB769 disposal29B;
// older refusal used VA as RVA and incorrectly called these unowned.
// Closure002A1575 proves Object* list construction, four-byte heads and64count.
// list<int> here supplies only measured node operations, never reads element data.
// Comparator copies three words as floats; original target names remain unknown.
// Correct no-throw cleanup closes EH-state reset instruction; carry stack location
// remains different: target EBP+8 vs candidate EBP-18, all counter/temp homes -4.
// Reuse the existing stlport_list_int_o1.cpp iterator comparison contract.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,const _List_iterator<T, Traits>& b){return a._M_node!=b._M_node;}
}

class Rva001EB984Member{public:void*init(void*);};
class Rva001EB769{public:void rva001EB769() throw();};
class Rva001EB940{public:
 _STL::_List_node_base *head;
 __forceinline Rva001EB940(){char allocator;((Rva001EB984Member*)this)->init(&allocator);}
 __forceinline ~Rva001EB940() throw(){((Rva001EB769*)this)->rva001EB769();}
};
class Rva00421A16{public:__forceinline ~Rva00421A16(){} __forceinline Rva00421A16(const Rva00421A16&r):x(r.x),y(r.y),z(r.z){}bool rva00421A16(void*,void*);float x,y,z;};
struct MiniList00421E1C{void *head;};
void Rva00421E1CMerge(MiniList00421E1C&,MiniList00421E1C&,Rva00421A16);
void Rva004236F5Sort(MiniList00421E1C&storage,Rva00421A16 comp){
 _STL::list<int>&list=(_STL::list<int>&)storage;
 _STL::_List_node_base *node=list._M_node._M_data;
 if(node->_M_next!=node && node->_M_next->_M_next!=node){
  Rva001EB940 carryStorage;Rva001EB940 counterStorage[64];_STL::list<int>&carry=(_STL::list<int>&)carryStorage;_STL::list<int>*counter=(_STL::list<int>*)counterStorage;int fill=0;
  while(!list.empty()){
   carry.splice(carry.begin(),list,list.begin());int i=0;
   while(i<fill&&!counter[i].empty()){
    Rva00421E1CMerge((MiniList00421E1C&)counter[i],(MiniList00421E1C&)carry,comp);
    carry.swap(counter[i++]);
   }
   carry.swap(counter[i]);if(i==fill)++fill;
  }
  for(int i=1;i<fill;++i)Rva00421E1CMerge((MiniList00421E1C&)counter[i],(MiniList00421E1C&)counter[i-1],comp);
  list.swap(counter[fill-1]);
 }
}

