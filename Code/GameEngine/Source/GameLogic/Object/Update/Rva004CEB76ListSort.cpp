// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Target evidence: 4CEB76..4CED15 is STLport4.5.3 _S_sort: empty/singleton guard, carry,64 counters, splice/merge/swap binary runs and final fold.
// Reference: read-only BFME1 revision 0bef414b5, inputs/vendor/stlport/stl/_list.c lines173..199.
// Target: 415B boundary, 64 four-byte list heads, splice4CEA94, merge4CEB14 and swap374B2D.
// The element type is unresolved. list<int> supplies the existing four-byte node storage contract;
// this routine never reads an element, and the comparator/merge operate on independently rowed opaque views.
// The external base destructor is already supplied by stlport_list_int_o1.cpp at4EC395;
// retaining that declaration preserves the native potentially-throwing cleanup and exact EH state.
// Comparator float-copy scheduling is target evidence; x/y/z names are carried from its sibling view.
#include <list>
namespace _STL { template<> _List_base<int,allocator<int> >::~_List_base(); }
class Rva004CEAB7{public:__forceinline Rva004CEAB7(const Rva004CEAB7&r):x(r.x),y(r.y),z(r.z){}bool rva004CEAB7(void*,void*);float x,y,z;};
struct Rva004CEB14List{void *head;};
void Rva004CEB14(Rva004CEB14List&,Rva004CEB14List&,Rva004CEAB7);
void Rva004CEB76(Rva004CEB14List&storage,Rva004CEAB7 comp){
 _STL::list<int>&list=(_STL::list<int>&)storage;
 _STL::_List_node_base *node=list._M_node._M_data;
 if(node->_M_next!=node && node->_M_next->_M_next!=node){
  _STL::list<int> carry;_STL::list<int> counter[64];int fill=0;
  while(!list.empty()){
   carry.splice(carry.begin(),list,list.begin());int i=0;
   while(i<fill&&!counter[i].empty()){
    Rva004CEB14((Rva004CEB14List&)counter[i],(Rva004CEB14List&)carry,comp);
    carry.swap(counter[i++]);
   }
   carry.swap(counter[i]);if(i==fill)++fill;
  }
  for(int i=1;i<fill;++i)Rva004CEB14((Rva004CEB14List&)counter[i],(Rva004CEB14List&)counter[i-1],comp);
  list.swap(counter[fill-1]);
 }
}
