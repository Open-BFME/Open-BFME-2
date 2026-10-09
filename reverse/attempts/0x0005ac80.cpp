// ?rva0005AC80@MilesAudioManager@@QAE?AVRva0036CA00Str@@ABVAsciiString@@H@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include "ascii_string.h"
#include <vector>
class OpaqueRefCounted { public: bool rva00050EFA(); void Release_Ref(); };
struct AudioEventInfo;
class AudioEventInfoRef {
 const AudioEventInfo *ptr;
public:
 __declspec(noinline) AudioEventInfoRef(const AudioEventInfo *);
 __forceinline ~AudioEventInfoRef() { if(ptr) ((OpaqueRefCounted*)ptr)->Release_Ref(); }
 __forceinline const AudioEventInfo *const &get() const { return ptr; }
};
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
AudioEventInfoRef::AudioEventInfoRef(const AudioEventInfo *p) : ptr(p) {
 if(ptr) InterlockedIncrement((long volatile*)((char*)ptr+4));
}
// Target5AC80..5ADA3 RET12, vtable slot73 and map+BC proven in earlier review.
// Rva0036CA00Str is the ledger's existing opaque owning-handle/vector name.
// Its single4B member wraps the separately verified raw AudioEventInfoRef ctor:
// this composition is an analysis view, not an assertion about donor hierarchy.
// The existing map owner uses struct AudioEventInfo, while raw ctor owner uses
// class AudioEventInfo; this TU emits the struct-tag constructor. Its29B body
// must be admitted as an exact ICF twin of the existing class-tag owner, not pinned.
// Metadata allocation invokes provisional Rva001DA19EBase at1DA19E; object
// semantics/layout beyond C4 allocation and atomic reference word+4 stay opaque.
// Four-byte counted-handle ABI view; composition bridges the existing opaque
// copy/vector owners and the separately rowed AudioEventInfoRef raw ctor.
// This does not assert that the original source had two distinct wrapper types.
class Rva0036CA00Str {
 AudioEventInfoRef value;
public:
 __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &);
 __forceinline Rva0036CA00Str(const AudioEventInfo *p) : value(p) {}
 __forceinline ~Rva0036CA00Str() {}
 __forceinline const AudioEventInfo *const &get() const { return value.get(); }
};
namespace _STL { template <> void vector<Rva0036CA00Str,allocator<Rva0036CA00Str> >::push_back(const Rva0036CA00Str&); }
class Rva001DA19EBase { char native[0xc4]; public: Rva001DA19EBase(); };
class MilesMutexGuard { void *mutex; bool flag; public: MilesMutexGuard(void*,int); ~MilesMutexGuard(); };
class Rva00056F61;
struct Rva0041534BIter { void *m_node; Rva00056F61 *m_table; Rva0041534BIter(void*n,Rva00056F61*t):m_node(n),m_table(t){} };
class Rva00056F61 { char native[0x14]; public: __declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString*); };
class Rva00059FBBMap { public: AudioEventInfo *&rva00059FBB(const AsciiString&); };
struct AudioInfoNode { void *next; AsciiString key; AudioEventInfo *info; };
class MilesAudioManager {
 char head[0xbc]; Rva00056F61 infos; char padD0[4]; _STL::vector<Rva0036CA00Str> owned;
 char padE0[0x6a4-0xe0]; bool dirty;
 char pad6A5[0x9d4-0x6a5]; char mutex[8];
public:
 Rva0036CA00Str rva0005AC80(const AsciiString &name,int context);
};
Rva0036CA00Str MilesAudioManager::rva0005AC80(const AsciiString &name,int)
{
 MilesMutexGuard guard(mutex,0);
 Rva0041534BIter found=infos.rva0041534B(&name);
 if(found.m_node && ((OpaqueRefCounted*)((AudioInfoNode*)found.m_node)->info)->rva00050EFA()) {
  Rva0036CA00Str result(((AudioInfoNode*)found.m_node)->info);
  ((OpaqueRefCounted*)result.get())->Release_Ref();
  return result;
 }
 dirty=false;
 Rva0036CA00Str result((AudioEventInfo*)new Rva001DA19EBase);
 owned.push_back(result);
 ((Rva00059FBBMap*)&infos)->rva00059FBB(name)=(AudioEventInfo*)result.get();
 return Rva0036CA00Str(((Rva00059FBBMap*)&infos)->rva00059FBB(name));
}
