// ?Rva00380B0CInit@@YAXXZ
// partial score=0.97 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /G7 /arch:SSE
#include "ascii_string.h"
extern bool g_Va00E022E0;
extern unsigned g_Va00E022E8;
extern void *TheRva00222A8BOwner;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class AptGuiFX {public:static void OnInitialized(const char *);};
class Coord2D;
void rva00380869(Coord2D *,Coord2D *);
struct TargetRef00217D4C;
void ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva0023E8D8 {public:Rva0023E8D8(void *);void *ptr;};
class Rva00380AB1 {public:Rva00380AB1(void *);void *ptr;};
class AptCommandMap {public:void *vtable;int refs;};
class AptCustomRender {public:void *vtable;int refs;};
template<class T>class AptRef {public:
 AptRef(void *desc);
 AptRef(const AptRef &rhs):ptr(rhs.ptr){if(ptr)++ptr->refs;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)ptr);}
 private:T *ptr;
};
template<>__forceinline AptRef<AptCommandMap>::AptRef(void *desc){((Rva0023E8D8*)this)->Rva0023E8D8::Rva0023E8D8(desc);}
template<>__forceinline AptRef<AptCustomRender>::AptRef(void *desc){((Rva00380AB1*)this)->Rva00380AB1::Rva00380AB1(desc);}
class AptPlayer {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
#undef V
 virtual void *loadWindow(AsciiString,AsciiString,int,int);
 void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);
 void AddCustomRender(const AsciiString &,AptRef<AptCustomRender>);
};
struct Rva001408C0Target;
class Rva002239B2 {public:void rva002239B2(const void *,Rva001408C0Target *);};
void Rva003806D4CreateMessageBox();
class AptStrategicMessageBox {public:static void CreateSingleton();};
void Rva00380B0CInit(){
 if(g_bfmeAptWindowManager){
  g_Va00E022E0=false;
  ((Rva002239B2*)g_bfmeAptWindowManager)->rva002239B2(&g_Va00E022E8,(Rva001408C0Target*)13);
  TheRva00222A8BOwner=((AptPlayer*)g_bfmeAptWindowManager)->loadWindow(AsciiString("Apt\\"),*(AsciiString*)&g_Va00E022E8,1,0);
  if(g_bfmeAptWindowManager){
   AsciiString name("AptGuiFX::OnInitialized");
   void *callback=(void*)&AptGuiFX::OnInitialized;
   ((AptPlayer*)g_bfmeAptWindowManager)->AddCommandMap(name,AptRef<AptCommandMap>(&callback));
  }
  {
   AsciiString name("ToolTipText");
   void *callback=(void*)&rva00380869;
   ((AptPlayer*)g_bfmeAptWindowManager)->AddCustomRender(name,AptRef<AptCustomRender>(&callback));
  }
  Rva003806D4CreateMessageBox();
  AptStrategicMessageBox::CreateSingleton();
 }
}
