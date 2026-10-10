// ?rva002B88EC@LivingWorldLogic@@QAEXXZ
// partial score=1.0 date=2026-10-10
// ?rva002B88EC@LivingWorldLogic@@QAEXXZ
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Exact native97 evidence bank; these prototype-only class views are NOT an
// admitted canonical-class recovery. Landing needs the existing owned GameLogic
// declaration in its canonical header and repair of the resulting guard spill
// regression (old-header control exact1034; new-header two homes swap).
#include <vector>
typedef bool Bool;typedef int Int;
class LivingWorldLogic{public:void rva002B88EC();};
class GameLogic{public:void rva0023D0E3(bool);};extern GameLogic*TheGameLogic;
struct TreeHintRef00217D4C;
class Rva002B6151Listener{public:virtual void notify(void*);};
class Rva002B6151List{public:void forEach(void(Rva002B6151Listener::*)(void*),void*);};
void Rva00437E9C(int);
namespace _STL {template<> TreeHintRef00217D4C* vector<TreeHintRef00217D4C>::erase(TreeHintRef00217D4C*,TreeHintRef00217D4C*);}
class Rva002BED91 {public:void clear();};
void Rva002B29BDFire();
void LivingWorldLogic::rva002B88EC(){
 _STL::vector<TreeHintRef00217D4C>*pending=(_STL::vector<TreeHintRef00217D4C>*)((char*)this+0x154);
 pending->erase(pending->begin(),pending->end());
 ((Rva002BED91*)((char*)this+0x160))->clear();
 *((Bool*)this+0x175)=true;
 Rva00437E9C(1);
 *((Int*)((char*)this+0x164))=-1;
 // Retail explicitly sets ECX=this before the existing zero-stack-argument
 // fire helper; its 27-byte body ignores the receiver and has a plain RET.
 // A one-register fastcall view preserves that observed call without a new name.
 ((void (__fastcall*)(LivingWorldLogic*))Rva002B29BDFire)(this);
 if(!*((Bool*)this+0x168))((Rva002B6151List*)((char*)this+0x4c))->forEach(&Rva002B6151Listener::notify,this);
 TheGameLogic->rva0023D0E3(false);
}
