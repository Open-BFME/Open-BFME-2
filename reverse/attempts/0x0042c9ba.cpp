// ?Rva0042C9BAFactory@StrategicInGameUI@@YA?AU?$auto_ptr@VRva0042C993Pointee@@@_STL@@HH@Z
// partial score=0.94 date=2026-10-09
// cl: /O1 /D_STLP_NO_TEMPLATE_CONVERSIONS /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <memory>
class Rva0042C993Pointee {public:virtual ~Rva0042C993Pointee();};
class Rva00577838 : public Rva0042C993Pointee {public:Rva00577838(int);char data[4];};
class Object;
class Rva00575674 {public:void rva00575674(Object *);};
class Rva000AD6F4 {public:void clear();};
class Rva0042C993Holder {public:
 Rva0042C993Pointee *ptr;
 Rva0042C993Holder():ptr(0){}
 ~Rva0042C993Holder(){((Rva000AD6F4*)this)->clear();}
 void reset(Rva0042C993Pointee *p){((Rva00575674*)this)->rva00575674((Object*)p);}
 __declspec(noinline) _STL::auto_ptr<Rva0042C993Pointee> release();
};
_STL::auto_ptr<Rva0042C993Pointee> Rva0042C993Holder::release(){
 _STL::auto_ptr<Rva0042C993Pointee> result(ptr);ptr=0;
 return result;
}
namespace StrategicInGameUI {
_STL::auto_ptr<Rva0042C993Pointee> Rva0042C9BAFactory(int kind,int argument){
 Rva0042C993Holder behavior;
 switch(kind){case 2:behavior.reset(new Rva00577838(argument));break;}
 return behavior.release();
}
}
