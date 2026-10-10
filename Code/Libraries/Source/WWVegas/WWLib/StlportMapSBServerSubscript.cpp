// Native staging-server map uses signed int keys and the owned4B SBServer handle.
// STLport4.5.3 supplies the algorithms; target copies/releases5E3B2D/5E3B83
// and pair construction5E3BB8 establish value semantics. Visible never-inlined
// copy plus inline teardown lets the compiler prove the default-null temporary
// stays null, dropping its cleanup while retaining the real pair cleanup.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
struct SBServer {
 void *m_handle;
 SBServer():m_handle(0) {}
 __declspec(noinline) SBServer(const SBServer&);
 ~SBServer();
};
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
typedef _STL::map<int,SBServer> ServerMap;


inline __declspec(noinline) SBServer::SBServer(const SBServer &src) {
 void *handle = src.m_handle; m_handle = handle;
 if (handle) { void *slot=*(void**)handle;char *obj=(char*)((void**)slot)[1]+(unsigned int)handle;++*(int*)(obj+4); }
}

struct TargetRef00217D4C {virtual void *destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
inline SBServer::~SBServer(){void*handle=m_handle;if(handle){void*slot=*(void**)handle;char*obj=(char*)((void**)slot)[1]+(unsigned int)handle;ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)obj);}}

typedef _STL::pair<const int,SBServer> ServerPair;
typedef _STL::_Rb_tree<int,ServerPair,_STL::_Select1st<ServerPair>,_STL::less<int>,_STL::allocator<ServerPair> > ServerTree;
template ServerTree::iterator ServerTree::_M_insert(_STL::_Rb_tree_node_base*,_STL::_Rb_tree_node_base*,const ServerPair&,_STL::_Rb_tree_node_base*);
template _STL::pair<ServerTree::iterator,bool> ServerTree::insert_unique(const ServerPair&);
template ServerTree::iterator ServerTree::insert_unique(ServerTree::iterator,const ServerPair&);
template ServerMap::iterator ServerMap::insert(ServerMap::iterator,const ServerPair&);

// Native5E4BB7..5E4C2F RET4. The default mapped value is a known null
// SBServer; only the constructed pair receives a native cleanup state.
template SBServer& ServerMap::operator[](const int&);
