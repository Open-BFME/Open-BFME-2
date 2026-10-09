// ??0NameKeyGenerator@@QAE@XZ
// partial score=1.0 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /I.
// stlport
#include <hash_map>
typedef int Bool;
#include "subsystem_interface.h"
#include "Code/GameEngine/Include/Common/Rva00041004Lock.h"
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION*) throw();
struct Rva0014918DElement {char bytes[8];};
typedef _STL::hash_map<int,Rva0014918DElement> ReverseIndex;
namespace _STL {template<> ReverseIndex::hash_map();}
struct UnlockGuard {
 Rva00041004 *ptr;
 __forceinline ~UnlockGuard() throw(){if(!ptr->m_flag)LeaveCriticalSection(&ptr->m_cs);}
};
class NameKeyGenerator : public SubsystemInterface {
public: NameKeyGenerator(); virtual ~NameKeyGenerator(); virtual void init(); virtual void reset(); virtual void update(){}
private: void freeSockets(); void *sockets[45007]; unsigned nextId;ReverseIndex reverse;Rva00041004 mutex;
};
NameKeyGenerator::NameKeyGenerator() : mutex(0){
 UnlockGuard guard={&mutex};
 nextId=0;
 for(int i=0;i<45007;++i)sockets[i]=0;

}

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
NameKeyGenerator::~NameKeyGenerator(){NameKeyGuard guard(&mutex);freeSockets();}
void NameKeyGenerator::init(){NameKeyGuard guard(&mutex);freeSockets();nextId=1;}
