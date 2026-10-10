// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WB15B80C0 names WaitForBattleStateHandler::Update, StrategicInGameUIBattleResolver.cpp656.
// Native5D08FD..5D0A67 supplies complete362B boundary. Native vtable
// C75538 slots0/1 hold rowed scalar-delete5D08E1 and this update. Matched
// ctor5D0AD5 establishes existing ownerRva005D0643, bases8/C and fields
// owner4/time10/selected14/shown18; owner14/1C separately read in native.
// Current providers include the ShowAllEnemiesRetreated state ctor187 and
// battle-selected Unicode fetch46. Private Apt singleton uses its real key.
// The12B wide compose node's43B builder is a complete byte-and-relocation
// twin of Rva0037BA97Init at37BA97: two copied words plus string pointer.
// Its16-bit char and string views follow the target Unicode materializer98.
#include "unicode_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Rva0056A989{public:bool rva0056A989();};
class Rva005CFA87{public:Rva005CFA87(void*,bool);char data[16];};
class Object;
class Rva00575674{public:void rva00575674(Object*);};
class Rva002BA8F1Logic{public:int rva002B5256(bool);};class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva0054D2DDTarget{public:void method(int,const UnicodeString&,const UnicodeString&);};
class AptStrategicMessageBox{static AptStrategicMessageBox*s_instance;friend class Rva005D0643;};
class GameTextInterface{public:
virtual~GameTextInterface();
#define V(n) virtual void v##n();
V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
virtual UnicodeString fetch(const char*,bool* =0);};extern GameTextInterface*TheGameText;
UnicodeString Rva005D0100Get(int);
struct WideStringRef{const UnicodeString*text;};struct WideStringChar:WideStringRef{unsigned short ch;};
class Rva005D087F:public WideStringChar{public:const UnicodeString*right;operator UnicodeString();};
static __forceinline WideStringChar operator+(const UnicodeString&a,unsigned short ch){WideStringChar out;out.text=&a;out.ch=ch;return out;}
__declspec(noinline) Rva005D087F operator+(const WideStringChar&left,const UnicodeString&right){Rva005D087F tmp;static_cast<WideStringChar&>(tmp)=left;tmp.right=&right;return tmp;}
class Rva005D0643B1{public:virtual~Rva005D0643B1();void*owner;};class Rva005D0643B2{public:virtual~Rva005D0643B2();};class Rva005D0643B3{public:virtual~Rva005D0643B3();};
struct WaitOwnerView{char pad[0x14];Rva0056A989*resolver;char gap[4];Rva00575674 nextState;};
class Rva005D0643:public Rva005D0643B1,public Rva005D0643B2,public Rva005D0643B3{public:virtual void rva005D08FD();unsigned startTime;int selected;bool shown;};
void Rva005D0643::rva005D08FD(){
if(((WaitOwnerView*)owner)->resolver->rva0056A989()){
 bool change=shown;shown=false;
 ((WaitOwnerView*)owner)->nextState.rva00575674((Object*)new Rva005CFA87(owner,change));
}else if(((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B5256(false)>1&&!shown){
 AptStrategicMessageBox*prompt=AptStrategicMessageBox::s_instance;
 if(prompt&&timeGetTime()-startTime>=200){
  UnicodeString wait=TheGameText->fetch("STRATEGICHUD:WaitMessage",0);
  ((Rva0054D2DDTarget*)prompt)->method(4,UnicodeString(L" "),(Rva005D0100Get(selected)+(unsigned short)'\n'+wait));
  shown=true;
 }
}
}
