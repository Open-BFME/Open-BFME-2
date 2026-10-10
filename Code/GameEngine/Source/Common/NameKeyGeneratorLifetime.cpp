// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /I.
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
#include <hash_map>
typedef int Bool;
#include "subsystem_interface.h"
#include "Code/GameEngine/Include/Common/Rva00041004Lock.h"
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION*) throw();
struct Rva0014918DElement {char bytes[8];};
typedef _STL::hash_map<int,Rva0014918DElement> ReverseIndex;
namespace _STL {template<> ReverseIndex::hash_map();}
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
