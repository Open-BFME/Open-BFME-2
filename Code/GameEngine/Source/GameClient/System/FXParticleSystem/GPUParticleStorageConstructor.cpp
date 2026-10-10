// cl: /Oy /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport
// Native3B0454..3B055C full264 RET4 and WB FA98A0 constructor of vtable
// C1D9B0, selected by native ParticleSystem ctor type7. WB FA9D70 independently
// names its slot5 GPUParticleSystemStorageModule::AddParticle. The existing
// Rva003B0344 owner spelling is retained for established ctor/dtor consumers;
// the original base/handle and queue wrapper names remain provisional.
// The +1C32-byte native VB / +20vertex count / +2412B expiry queue / +34int
// min-heap layouts follow ctor and independently owned3B0344 destructor.
// Expiry elements use the measured time/index/node record. BfmeE12 reserve
// and ModuleData-pointer vectors are existing allocator/call ABI views:
// their payloads here are expiry(time,index,node) and integer slot bits, not
// ModuleData pointees. The input references and vector growth helpers preserve
// that measured 12B/4B storage. No target claim about original C++ type names.
// Both wrapper default constructors are complete19B byte-and-relocation twins
// of the ObjectCreationList owner1F81BF: zero-init the vector allocation header.
// Showing the owned33B push body (including its real stored comparator) gives
// the parent native14B frame and EBX receiver; hiding push_back costs4B. /Oy
// preserves the owned push's frameless33B shape. No new callee pin is used.
#include <stl/_algobase.h>
namespace _STL {static inline const unsigned&max(const unsigned&a,const unsigned&b){return a<b?b:a;}}
#include <vector>
#include <algorithm>
#include <functional>
namespace _STL {template<> void push_heap<int*,greater<int> >(int*,int*,greater<int>);}
#include <string.h>
void* __cdecl operator new(unsigned);
void __cdecl operator delete(void*)throw();
void BFME_DX8_Thread_Lock();bool BFME_DX8_Thread_Assert();
class DX8ThreadLock{public:DX8ThreadLock(){BFME_DX8_Thread_Lock();}~DX8ThreadLock(){BFME_DX8_Thread_Assert();}};
class ParticleSystem{public:unsigned rva001F3C6B();};ParticleSystem*Make001FCBD7();
class RvaSmartPtr12{public:ParticleSystem*target;unsigned b,c;ParticleSystem*operator->()const{return target?target:Make001FCBD7();}};
class Rva003B00D6{public:Rva003B00D6(const RvaSmartPtr12&);virtual ~Rva003B00D6();char data[24];};
struct BfmeE12{int a[3];};struct Rva003B02F4Entry{float time;int slot;void*node;};
// Typed empty allocation header29 and proxy11 are independent native twins.
// This removes the old BfmeE12 base pin that chooses a different kept copy.
class ModuleData;
class Rva003B0412{public:__declspec(noinline)Rva003B0412();_STL::vector<Rva003B02F4Entry>c;char comp;};Rva003B0412::Rva003B0412(){}
class Rva003B0433{public:__declspec(noinline)Rva003B0433();_STL::vector<const ModuleData*>c;_STL::greater<int>comp;__declspec(noinline) void rva003B0433(const ModuleData*&);};Rva003B0433::Rva003B0433(){}
class BfmeDynamicNativeVB{public:BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);char data[32];};
class VertexBufferClass{public:class WriteLockClass{public:WriteLockClass(VertexBufferClass*,int);~WriteLockClass();void*VertexBuffer;void*Vertices;int extra;void*Get_Vertex_Array(){return Vertices;}};};
class Rva003B0344:public Rva003B00D6{public:Rva003B0344(const RvaSmartPtr12&);virtual ~Rva003B0344();BfmeDynamicNativeVB*vb;unsigned vertices;Rva003B0412 expiry;Rva003B0433 slots;};
Rva003B0344::Rva003B0344(const RvaSmartPtr12 &src) : Rva003B00D6(src)
{
    DX8ThreadLock thread;
    unsigned n = src->rva001F3C6B();
    vertices = 4 * n;
    vb = new BfmeDynamicNativeVB(0, (unsigned short)vertices, 0, 40);
    VertexBufferClass::WriteLockClass lock((VertexBufferClass *)vb, 0);
    memset(lock.Get_Vertex_Array(), 0, vertices * 40);
    reinterpret_cast<_STL::vector<BfmeE12> *>(&expiry.c)->reserve(n);
    slots.c.reserve(n);
    for (unsigned i = 0; i < n; i++)
    {
        // Established four-byte ABI carrier for the integer slot; no dereference.
        slots.rva003B0433(reinterpret_cast<const ModuleData *&>(i));
    }
}

void Rva003B0433::rva003B0433(const ModuleData *&m)
{
    c.push_back(m);
    _STL::push_heap((int *)c.begin(), (int *)c.end(), comp);
}
