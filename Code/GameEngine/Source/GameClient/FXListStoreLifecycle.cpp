// ??1Rva001E2AD9@@UAE@XZ
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_NO_CSTD_FUNCTION_IMPORTS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// Target facts: data ledger vtable BDD97C establishes FXListStore;
// body1E2AD9..1E2BB0 destroys pointer-map at0C and nugget vector20.
// Keep existing address-derived linker owner used by the deleting wrapper.
// Window-video begin/increment and Armor clear below are ABI provider views,
// not claims that the target map stores those donor payloads.
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}
class GameWindow;class WindowVideo;
class WindowVideoManager {public:struct hashConstGameWindowPtr;};
enum NameKeyType { NAMEKEY_INVALID=0 };
class ArmorTemplate;
namespace rts {template<class T>struct hash;}
namespace _STL {
template<class T>struct _Select1st;template<class T>struct equal_to;
template<class V,class K,class H,class E,class Eq,class A>class hashtable;
template<class V,class Traits,class K,class H,class E,class Eq,class A>struct _Ht_iterator {
 void *node;void *table;
 _Ht_iterator(const _Ht_iterator &x):node(x.node),table(x.table){}
 _Ht_iterator &operator++();
};
template<class V,class K,class H,class E,class Eq,class A>class hashtable {
public:
 typedef _Ht_iterator<V,_Nonconst_traits<V>,K,H,E,Eq,A> iterator;
 iterator begin();
 void clear();
 ~hashtable();
 char storage[0x14];
};
}
typedef _STL::pair<const GameWindow *const,WindowVideo *> WindowPair;
typedef _STL::hashtable<WindowPair,const GameWindow*,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<WindowPair>,_STL::equal_to<const GameWindow*>,_STL::allocator<WindowPair> > NativeBeginTable;
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > NativeClearTable;
struct FxHeapObject {virtual void *destroyDelete(unsigned);};
struct FxMapNode {FxMapNode *next;NameKeyType key;FxHeapObject *value;};
namespace _STL {void free(void *);}
namespace _STL {
template<> __forceinline void allocator<void *>::deallocate(pointer p,size_type n)const {if(p)_STL::free(p);}
template<> __forceinline void _STLP_alloc_proxy<void **,void *,allocator<void *> >::deallocate(void **p,size_t n){__stl_alloc_rebind(static_cast<_Base&>(*this),(void **)0).deallocate(p,n);}
}
struct FxOwnedVector {
 void **first,**last,**limit;
 ~FxOwnedVector(){if(first)_STL::free(first);}
 unsigned size()const{return last-first;}
 void *operator[](unsigned i)const{return first[i];}
 void clear(){reinterpret_cast<_STL::vector<void *> *>(this)->erase(first,last);}
};
struct Rva001E287F {
 unsigned unknown00;FxOwnedVector buckets04;unsigned count10;
 ~Rva001E287F();
 NativeBeginTable::iterator begin(){return reinterpret_cast<NativeBeginTable *>(this)->begin();}
 void clear(){reinterpret_cast<NativeClearTable *>(this)->clear();}
};
class SubsystemInterface {public:virtual ~SubsystemInterface();char opaque04[8];};
class Rva001E2AD9:public SubsystemInterface {public:virtual ~Rva001E2AD9();Rva001E287F map0C;_STL::vector<void *> nuggets20;};
Rva001E2AD9::~Rva001E2AD9(){
 for(NativeBeginTable::iterator it=map0C.begin();it.node;++it){
  FxHeapObject *p=((FxMapNode *)it.node)->value;
  ::operator delete(p?p->destroyDelete(0):0);
 }
 map0C.clear();
 for(unsigned i=0;i<nuggets20.size();++i){
  FxHeapObject *p=(FxHeapObject *)nuggets20[i];
  ::operator delete(p?p->destroyDelete(0):0);
 }
 nuggets20.clear();
}

typedef char FxStoreSizeCheck[sizeof(Rva001E2AD9)==0x2C ? 1 : -1];
