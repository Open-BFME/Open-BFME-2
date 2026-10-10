// ??1Rva002CC20E@@UAE@XZ
// partial score=0.8397814207650274 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/GameEngine/Include /Ireference/open-bfme-1/game/GameEngine/Include/Precompiled
// New complete teardown lead for native2CCD56..2CCE37 (225B).
// Keep existing ctor's neutral Rva002CC20E owner/vtable spelling. Native and
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
namespace _STL{void __cdecl free(void*);}
#define free _STL::free
#include <vector>
#undef free
typedef bool Bool;
#include "subsystem_interface.h"
class RvaVector{public:void**erase(void**,void**);};
class Rva002CCD56Element{public:virtual ~Rva002CCD56Element();};
class Rva002CC20E:public SubsystemInterface{public:virtual ~Rva002CC20E();_STL::vector<void*> vec0C,vec18;};
Rva002CC20E::~Rva002CC20E(){
 for(unsigned i=0;i<vec0C.size();++i){Rva002CCD56Element*e=(Rva002CCD56Element*)vec0C[i];if(e)::delete e;}
 ((RvaVector*)&vec0C)->erase(vec0C.begin(),vec0C.end());
 for(unsigned i=0;i<vec18.size();++i){Rva002CCD56Element*e=(Rva002CCD56Element*)vec18[i];if(e)::delete e;}
 ((RvaVector*)&vec18)->erase(vec18.begin(),vec18.end());
}
