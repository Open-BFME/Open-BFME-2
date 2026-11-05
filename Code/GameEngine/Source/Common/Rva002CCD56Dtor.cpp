// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled
// stlport
// ??1Rva002CCD56@@UAE@XZ @0x002CCD56 225B. Dedicated TU: the matched ctor
// Rva002CC20ECtor.cpp keeps its own BfmeE16 views/flags. Emitted under the
// ledger pin name the scalar deleting dtor 0x002CD5E0 calls. R1/S2 stacked
// equal-arm receiver on both vector end() calls closes the teardown order.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled
// New complete teardown lead for native2CCD56..2CCE37 (225B).
// Keep existing ctor's neutral Rva002CCD56 owner/vtable spelling. Native and
// WB BB2EC0 establish base SubsystemInterface plus two4-byte pointer vectors
// atC/18 and null-guarded virtual slot0/flag0 followed by global delete.
// Element class names/layouts remain unknown; the element view asserts only
// this destructor dispatch. ZH WeaponStore::~WeaponStore guides the cleanup
// loop; BFME2 has a second vector and ::delete behavior independently observed.
// Existing RvaVector erase view owns the34-byte/relocation twin31BD55; direct
// vector<void*> pin currently points27400. Use established game-STL C++ free
// route30830, not CRT free628F98; both calls alter EH/liveness, not just bytes.
// This is a BANK, not a matched claim: emits233B, retains extra4-byte home,
// EBX/ESI ownership/counter swap and second-loop spill. Base/header/table and
// the ctor's earlier BfmeE16 private views need reconciliation before landing.
// Existing vtable symbol resolution does not verify generated table entries.
// stlport
#include <stdlib.h>
namespace _STL

{
 void __cdecl free(void*);
 
}
// Bind before STLport imports ::free into the same namespace.
static __forceinline void releaseVectorStorage(void *storage)
{
	_STL::free(storage);
}
#include <vector>
namespace _STL {
template<> inline void allocator<void *>::deallocate(void **__p, size_type) const
{
	if (__p != 0) releaseVectorStorage((void *)__p);
}
}
typedef bool Bool;
#include "subsystem_interface.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::end() { return this->_M_finish; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * * vector<void *,allocator<void *> >::begin() { return this->_M_start; } }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
// bfme link decl-only end
class RvaVector

{
 public:void**erase(void**,void**);
 
}
;
class Rva002CCD56Element

{
 public:virtual ~Rva002CCD56Element();
 
}
;
class Rva002CCD56:public SubsystemInterface

{
 public:virtual ~Rva002CCD56();
 _STL::vector<void*> vec0C,vec18;
 
}
;
Rva002CCD56::~Rva002CCD56()

{
 for(unsigned i=0;i<vec0C.size();++i)
 
 {
  Rva002CCD56Element*e=(Rva002CCD56Element*)vec0C[i];
  if(e)::delete e;
  
 }
 ((RvaVector*)&vec0C)->erase(vec0C.begin(),((&(vec0C)) ? (vec0C) : (vec0C)).end());
 for(unsigned i=0;i<vec18.size();++i)
 
 {
  Rva002CCD56Element*e=(Rva002CCD56Element*)vec18[i];
  if(e)::delete e;
  
 }
 ((RvaVector*)&vec18)->erase(vec18.begin(),((this) ? (vec18) : (vec18)).end());
 
}
