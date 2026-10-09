// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>
// Native004236F5..00423890 RET0 and WB01144650 establish STLport carry64 sort.
// Donor575ba2b04743f190f069805fbdc59936123c45da _list.c is the semantic guide.
// Target Object* list identity: owned closure2A1575 and InGameUI array constructor.
// Comparator three-word float copy/merge421E1C and four-byte circular heads measured.
// Original application name remains unproven; address-derived owner retained.
// Carry uses the directly measured base initialization40 and cleanup29; counters
// retain measured outer constructor18/default-argument closure13/destructor5.
// These are compatible storage views, not evidence for distinct target classes.
// Visible noinline initializer exposes its proven unused allocator argument;
// S1 supplied this compiler escape-analysis lead, permitting native carry EBP+8.
// Helpers40/18/13 independently full-byte-and-relocation verified; no new pins.
// Reuse the existing stlport_list_int_o1.cpp iterator comparison contract.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,const _List_iterator<T, Traits>& b){return a._M_node!=b._M_node;}
}

class FreelistProxyHead
{
public:
	void setup(const void *alloc, void *head);
};

class FreelistPool
{
public:
	void *pop();
};

class Rva001EB984Member
{
public:
	void *m_head;
	void *init(void *context);
};

// Distinct from the behavior pool at VA 0x00DA60E8.
extern FreelistPool g_freelistPool00DB8FEC;

// ?init@Rva001EB984Member@@QAEPAXPAX@Z @0x001EB984
__declspec(noinline) inline void *Rva001EB984Member::init(void *context)
{
	(void)context;
	char dummyAlloc;
	((FreelistProxyHead *)this)->setup(&dummyAlloc, 0);
	void *node = g_freelistPool00DB8FEC.pop();
	((void **)node)[0] = node;
	((void **)node)[1] = node;
	m_head = node;
	return this;
}

class Rva001EB769{public:void rva001EB769() throw();};
class Object;
template<class T>class Rva001EB984PoolAllocator {};
class Rva001EB940{public:
 _STL::_List_node_base *head;
 __declspec(noinline) Rva001EB940(const Rva001EB984PoolAllocator<Object*>&allocator=Rva001EB984PoolAllocator<Object*>()){((Rva001EB984Member*)this)->init((void*)&allocator);}
 __forceinline ~Rva001EB940() throw(){((Rva001EB769*)this)->rva001EB769();}
};
// Carry is the measured base-header lifetime; counters retain outer list construction.
class Rva001EB984Carry : public Rva001EB984Member {public:
 __forceinline Rva001EB984Carry(){char allocator;init(&allocator);}
 __forceinline ~Rva001EB984Carry() throw(){((Rva001EB769*)this)->rva001EB769();}
};
class Rva00421A16{public:__forceinline ~Rva00421A16(){} __forceinline Rva00421A16(const Rva00421A16&r):x(r.x),y(r.y),z(r.z){}bool rva00421A16(void*,void*);float x,y,z;};
struct MiniList00421E1C{void *head;};
void Rva00421E1CMerge(MiniList00421E1C&,MiniList00421E1C&,Rva00421A16);
void Rva004236F5(MiniList00421E1C&storage,Rva00421A16 comp){
 _STL::list<int>&list=(_STL::list<int>&)storage;
 _STL::_List_node_base *node=list._M_node._M_data;
 if(node->_M_next!=node && node->_M_next->_M_next!=node){
  Rva001EB984Carry carryStorage;Rva001EB940 counterStorage[64];_STL::list<int>&carry=(_STL::list<int>&)carryStorage;_STL::list<int>*counter=(_STL::list<int>*)counterStorage;int fill=0;
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

