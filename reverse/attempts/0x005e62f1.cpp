// ??0Rva005E62F1@@QAE@PAXHH0PAVRva005CB84A@@0PAVDetailsPanelFactoryFactory@PlanningPhaseArmySelection@StrategicInGameUI@@@Z
// partial score=0.90576 date=2026-10-10
// cl: /O1 /Oy- /G7 /MD /EHsc /arch:SSE
// Native5E62F1..5E652E. Address-derived five-slot interface, nonvirtual
// base cleanup, six stored inputs and seventh factory receiver. Native
// ownership states0..3 are base,record1C,ref38,owned40. No application
// identity inferred from the related PlanningPhaseArmySelection factory.
class Rva0005E57C9DwordImmSetter {public:void apply();};
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
class Rva00319B0AOwner {public:void rva00319B0A();};
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret*rva00318C32();};
class Rva00318FBE {public:int rva00318FBE();};
class Rva005CB84A {public:void rva005CB84A(int);};
struct TargetRef00217D4C {void*vt;int refs;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Ref {TargetRef00217D4C*pointer;Ref():pointer(0){} ~Ref(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}};
class Rva005773DB {public:Rva005773DB(const int*);__forceinline ~Rva005773DB(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}private:TargetRef00217D4C*pointer;};
class Rva005F2381 {public:Rva005F2381();~Rva005F2381();private:char storage[28];};
class Rva005E6253 {public:void clear();};
struct Owned {void*p;Owned():p(0){}~Owned(){reinterpret_cast<Rva005E6253*>(this)->clear();}};
class __declspec(novtable) Base {public:__forceinline Base(){} __forceinline ~Base(){reinterpret_cast<Rva0005E57C9DwordImmSetter*>(this)->apply();}virtual void first(int)=0;virtual void second(void*,unsigned)=0;virtual void third()=0;virtual void fourth()=0;virtual void fifth()=0;};
class Widget {public:virtual void s0();virtual void image(const void*);virtual void s2();virtual void range(int,int);virtual void s4();virtual void s5();virtual void ref(const Rva005773DB&);virtual void s7();virtual void refresh();};
class PanelWidget {public:virtual void s0();virtual void entry(int,const void*);virtual void s2();virtual void factory(const void*);};
class Rva0042D703PtrChaseField {public:int get()const;};
class Rva0042D6B4PtrChaseField {public:int get()const;};
class Rva0042D6FDPtrChaseField {public:int get()const;};
class Rva0042D69DPtrChaseField {public:int get()const;};
struct Rva005D2355In;class Image;
namespace StrategicInGameUI {class PlanningPhaseArmySelection {public:class DetailsPanelFactoryFactory;}; const Image*GetSelectionPortrait(Rva005D2355In*);}
class PanelFactoryResultView {public:~PanelFactoryResultView(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}private:TargetRef00217D4C*pointer;};
class StrategicInGameUI::PlanningPhaseArmySelection::DetailsPanelFactoryFactory {public:PanelFactoryResultView CreatePanelFactory(void*);};
namespace StrategicInGameUIFns {}
// Full existing free-function identity below is introduced by its established class.
class StrategicInGameUI2 {};
namespace StrategicInGameUIAlias {const Image*GetSelectionPortrait(Rva005D2355In*);}
int GetMaxCommandPoints(void*);
template<class T>class RvaCloneResult {public:~RvaCloneResult(){if(pointer)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(pointer));}private:T*pointer;};
class Rva005E59A5 {public:struct Payload{int v[3];};};
class Rva005E59C2 {public:struct Payload{int v[3];};};
class Rva005E59DF {public:struct Payload{int v[3];};};
RvaCloneResult<Rva005E59A5>Rva005E5C63Create(const Rva005E59A5::Payload*);
RvaCloneResult<Rva005E59C2>Rva005E5C95Create(const Rva005E59C2::Payload*);
RvaCloneResult<Rva005E59DF>Rva005E5CC7Create(const Rva005E59DF::Payload*);
struct Context{int info,owner;void*record;bool enabled;};
class Rva005E62F1:public Base {
public:Rva005E62F1(void*,int,int,void*,Rva005CB84A*,void*,StrategicInGameUI::PlanningPhaseArmySelection::DetailsPanelFactoryFactory*);~Rva005E62F1();
virtual void first(int);virtual void second(void*,unsigned);virtual void third()=0;virtual void fourth()=0;virtual void fifth()=0;
private:void*a4;int a8,aC;void*a10;Rva005CB84A*a14;void*a18;Rva005F2381 record;Ref ref38;bool flag;Owned owned;
};
Rva005E62F1::Rva005E62F1(void*p4,int p8,int pC,void*p10,Rva005CB84A*p14,void*p18,StrategicInGameUI::PlanningPhaseArmySelection::DetailsPanelFactoryFactory*factory):a4(p4),a8(p8),aC(pC),a10(p10),a14(p14),a18(p18),flag(false) {
 reinterpret_cast<Rva005A0B4CList*>(static_cast<char*>(a18)+8)->append(reinterpret_cast<Rva002BA8F1Listener*>(this));
 reinterpret_cast<Rva00319B0AOwner*>(a18)->rva00319B0A();
 Widget*w=reinterpret_cast<Widget*>(reinterpret_cast<Rva0042D703PtrChaseField*>(a10)->get());
 if(w) {
  w->image(StrategicInGameUI::GetSelectionPortrait(reinterpret_cast<Rva005D2355In*>(a18)));
  {int owner=reinterpret_cast<int>(a18);Rva005773DB temp(&owner);w->ref(temp);}
  w->range(reinterpret_cast<Rva00318FBE*>(a18)->rva00318FBE(),GetMaxCommandPoints(a18));w->refresh();
 }
 a14->rva005CB84A(reinterpret_cast<int>(reinterpret_cast<Rva00318C79Owner*>(a18)->rva00318C32()));
 int info=reinterpret_cast<Rva0042D6B4PtrChaseField*>(a10)->get();
 if(info) {
  PanelWidget*detail=reinterpret_cast<PanelWidget*>(reinterpret_cast<Rva0042D6FDPtrChaseField*>(a10)->get());
  if(detail) {Context c={info,reinterpret_cast<int>(p18),&record,true};detail->factory(&factory->CreatePanelFactory(&c));}
  PanelWidget*entries=reinterpret_cast<PanelWidget*>(reinterpret_cast<Rva0042D69DPtrChaseField*>(a10)->get());
  if(entries) {
   Rva005E59A5::Payload p1;p1.v[1]=reinterpret_cast<int>(a18);p1.v[0]=info;p1.v[2]=reinterpret_cast<int>(&record);entries->entry(1,&Rva005E5C63Create(&p1));
   Rva005E59C2::Payload p2;p2.v[1]=reinterpret_cast<int>(a18);p2.v[0]=info;p2.v[2]=reinterpret_cast<int>(&record);entries->entry(2,&Rva005E5C95Create(&p2));
   Rva005E59DF::Payload p5;p5.v[1]=reinterpret_cast<int>(a18);p5.v[0]=info;p5.v[2]=reinterpret_cast<int>(&record);entries->entry(5,&Rva005E5CC7Create(&p5));
  }
 }
}
