// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS  /EHsc- /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// platformsdk
// stlport
// Target identity: constructor1491AC is called by GameEngine::init; native
// vtableBD3568 and scalar deleting wrapper148DC3 identify destructor148BC2.
// Target layout:12B base,45007 socket pointers,nextID2BF48,20B reverse index
// at2BF4C and mutex2BF60 are proven by ctor and existing nameToKey/freeSockets.
// Reverse payload/template spelling retains14918D donor inference; no claim
// about the original mapped type. Its concrete cleanup provider is148B84.
// Native vtable slots1/9 both use the same84B initialization/reset operation.
// Inline init emits that exact complete body; reset uses the existing provider.
// Donor semantics: ZH NameKeyGenerator.cpp; scope Lock/Unlock are existing
// native helpers and the target demonstrates that they do not throw.
#include <windows.h>
#include <hash_map>
typedef bool Bool;
#include "subsystem_interface.h"
#include "../../Include/Common/Rva00041004Lock.h"
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
struct Rva0014918DElement {char bytes[8];};
typedef _STL::hash_map<int,Rva0014918DElement> ReverseIndex;
namespace _STL {template<> ReverseIndex::hash_map();}
// Same-object reverse-table destructor copied from the verified native148B84
// provider, retaining its established ArmorTable clear-worker call. The
// existing opaque reverse value remains an inference; complete parent and
// provider bytes plus EH are independently verified before fold admission.
enum NameKeyType {NAMEKEY_INVALID=0,NAMEKEY_MAX=1<<23,FORCE_NAMEKEYTYPE_LONG=0x7fffffff};
namespace rts { template<class T>struct hash {unsigned operator()(const T&v)const{return (unsigned)v;} }; }
#include "../../Include/GameLogic/Armor.h"
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > ArmorTable;
namespace _STL {template<> void ArmorTable::clear();}
typedef _STL::pair<const int,Rva0014918DElement> ReversePair;
typedef _STL::hashtable<ReversePair,int,_STL::hash<int>,_STL::_Select1st<ReversePair>,_STL::equal_to<int>,_STL::allocator<ReversePair> > ReverseTable;
namespace _STL {template<> ReverseTable::~hashtable();}
struct UnlockGuard {
 Rva00041004 *ptr;
 __forceinline ~UnlockGuard() throw(){if(!ptr->m_flag)LeaveCriticalSection(&ptr->m_cs);}
};
class CriticalSection;
class ScopedCriticalSection {
friend class NameKeyGuard;
private: CriticalSection *cs;bool locked; void Lock() throw();void Unlock() throw();
};
class NameKeyGuard : public ScopedCriticalSection {
public:
 __forceinline NameKeyGuard(Rva00041004 *p){cs=reinterpret_cast<CriticalSection*>(p);locked=false;Lock();}
 __forceinline ~NameKeyGuard(){if(locked)Unlock();}
};
class NameKeyGenerator : public SubsystemInterface {
public: NameKeyGenerator(); virtual ~NameKeyGenerator(); virtual void init(){NameKeyGuard guard(&mutex);freeSockets();nextId=1;} virtual void reset(); virtual void update(){}
private: void freeSockets(); void *sockets[45007]; unsigned nextId;ReverseIndex reverse;Rva00041004 mutex;
};
NameKeyGenerator::NameKeyGenerator() : mutex(0){
 UnlockGuard guard={&mutex};
 nextId=0;
 for(int i=0;i<45007;++i)sockets[i]=0;

}

NameKeyGenerator::~NameKeyGenerator(){NameKeyGuard guard(&mutex);freeSockets();}
