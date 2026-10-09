// ?Rva0042C261CreateTurnPhaseBehavior@StrategicInGameUI@@YA?AU?$auto_ptr@VRva0042C23APointee@@@_STL@@HPAXH@Z
// partial score=0.93 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <memory>
class Rva0042C23APointee {public:virtual ~Rva0042C23APointee();};
class Rva00575D45 : public Rva0042C23APointee {public:Rva00575D45(void *,int);char data[8];};
class Rva00576B5E : public Rva0042C23APointee {public:Rva00576B5E(void *,int);char data[8];};
class Rva005772BF : public Rva0042C23APointee {public:Rva005772BF(void *,int);char data[8];};
class Object;
class Rva00575674 {public:void rva00575674(Object *);};
class Rva000AD6F4 {public:void clear();};
class Rva0042C23AHolder {public:
 Rva0042C23APointee *ptr;
 Rva0042C23AHolder():ptr(0){}
 ~Rva0042C23AHolder(){((Rva000AD6F4*)this)->clear();}
 void reset(Rva0042C23APointee *p){((Rva00575674*)this)->rva00575674((Object*)p);}
 __declspec(noinline) _STL::auto_ptr<Rva0042C23APointee> release();
};
namespace StrategicInGameUI {
_STL::auto_ptr<Rva0042C23APointee> Rva0042C261CreateTurnPhaseBehavior(int phase,void *held,int argument){
 Rva0042C23AHolder behavior;
 switch(phase){
 case 0:behavior.reset(new Rva00575D45(held,argument));break;
 case 2:behavior.reset(new Rva00576B5E(held,argument));break;
 case 4:behavior.reset(new Rva005772BF(held,argument));break;
 }
 return behavior.release();
}
}
