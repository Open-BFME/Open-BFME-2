// cl: /O1 /G7 /MD /EHsc /arch:SSE
// Native5E62F1..5E652E. Address-derived five-slot interface, nonvirtual
// base cleanup, six stored inputs and seventh factory receiver. Native
// ownership states0..3 are base,record1C,owned38,owned40. No application
// identity inferred from the related PlanningPhaseArmySelection factory.
// Native vtable C77DF0 is the callback11, empty RET8, then three pure slots.
// Its nine-state unwind map independently identifies base cleanup3F3F7C,
// record cleanup5F23B2, two owning clearAD6F4 calls and five reference
// temporary releases5F8F96. The member at3C is the flag between the owners.
// The visible existing53-byte Rva005773DB constructor is essential even
// though it stays out of line: without its definition MSVC reuses argument
// home8 for the image vtable; retail reserves that home for the reference
// temporary and spills the vtable at10. The inline value-payload constructors
// likewise evaluate info before the owner store. No original class name is
// inferred from byte equality. See reverse/attempt_evidence/0x005e62f1_crack_i.txt.
class Rva003F3F7CDwordImmSetter {public:void apply();};
class Rva000AD6F4 {public:void clear();};
struct Rva002BA8F1Listener;
class Rva005A0B4CList {public:void append(Rva002BA8F1Listener*);};
class Rva00319B0AOwner {public:void rva00319B0A();};
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret*rva00318C32();};
class Rva00318FBE {public:int rva00318FBE();};
class Rva005CB84A {public:void rva005CB84A(int);};
struct TargetRef00217D4C {void*vt;int refs;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Ref {void*pointer;Ref():pointer(0){} ~Ref(){reinterpret_cast<Rva000AD6F4*>(this)->clear();}};
class Rva005773DB {public:Rva005773DB(const int*);__forceinline ~Rva005773DB(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}private:TargetRef00217D4C*pointer;};
class Rva005F23B2 {public:~Rva005F23B2();};
class Rva005F2381 {public:Rva005F2381();~Rva005F2381(){reinterpret_cast<Rva005F23B2*>(this)->~Rva005F23B2();}private:char storage[28];};
struct Owned {void*p;Owned():p(0){}~Owned(){reinterpret_cast<Rva000AD6F4*>(this)->clear();}};
class __declspec(novtable) Rva005E62F1ListenerBase {public:__forceinline Rva005E62F1ListenerBase(){} __forceinline ~Rva005E62F1ListenerBase(){reinterpret_cast<Rva003F3F7CDwordImmSetter*>(this)->apply();}virtual int rva005E57A2(void*)=0;virtual void rva0050B238(void*,unsigned)=0;virtual void third()=0;virtual void fourth()=0;virtual void fifth()=0;};
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
int GetMaxCommandPoints(void*);
template<class T>class RvaCloneResult {public:~RvaCloneResult(){if(pointer)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C*>(pointer));}private:T*pointer;};
class Rva005E59A5 {public:struct Payload{int v[3];Payload(int i,int o,int r){v[0]=i;v[1]=o;v[2]=r;}};};
class Rva005E59C2 {public:struct Payload{int v[3];Payload(int i,int o,int r){v[0]=i;v[1]=o;v[2]=r;}};};
class Rva005E59DF {public:struct Payload{int v[3];Payload(int i,int o,int r){v[0]=i;v[1]=o;v[2]=r;}};};
RvaCloneResult<Rva005E59A5>Rva005E5C63Create(const Rva005E59A5::Payload*);
RvaCloneResult<Rva005E59C2>Rva005E5C95Create(const Rva005E59C2::Payload*);
RvaCloneResult<Rva005E59DF>Rva005E5CC7Create(const Rva005E59DF::Payload*);
struct Context{int info,owner;void*record;bool enabled;};
class Rva005E57A2Callback {public:int invoke();};
class Rva005E62F1:public Rva005E62F1ListenerBase {
public:Rva005E62F1(void*,int,int,void*,Rva005CB84A*,void*,StrategicInGameUI::PlanningPhaseArmySelection::DetailsPanelFactoryFactory*);~Rva005E62F1();
virtual int rva005E57A2(void*);virtual void rva0050B238(void*,unsigned);virtual void third()=0;virtual void fourth()=0;virtual void fifth()=0;
private:void*a4;int a8,aC;void*a10;Rva005CB84A*a14;void*a18;Rva005F2381 record;Ref ref38;bool flag;Owned owned;
};
Rva005E62F1::Rva005E62F1(void*p4,int p8,int pC,void*ui,Rva005CB84A*p14,void*army,StrategicInGameUI::PlanningPhaseArmySelection::DetailsPanelFactoryFactory*factory):a4(p4),a8(p8),aC(pC),a10(ui),a14(p14),a18(army),flag(false) {
 reinterpret_cast<Rva005A0B4CList*>(static_cast<char*>(a18)+8)->append(reinterpret_cast<Rva002BA8F1Listener*>(this));
 reinterpret_cast<Rva00319B0AOwner*>(a18)->rva00319B0A();
 Widget*widget=reinterpret_cast<Widget*>(reinterpret_cast<Rva0042D703PtrChaseField*>(a10)->get());
 if(widget) {
  widget->image(StrategicInGameUI::GetSelectionPortrait(reinterpret_cast<Rva005D2355In*>(a18)));
  {int owner=reinterpret_cast<int>(a18);Rva005773DB temp(&owner);widget->ref(temp);}
  widget->range(reinterpret_cast<Rva00318FBE*>(a18)->rva00318FBE(),GetMaxCommandPoints(a18));widget->refresh();
 }
 a14->rva005CB84A(reinterpret_cast<int>(reinterpret_cast<Rva00318C79Owner*>(a18)->rva00318C32()));
 int info=reinterpret_cast<Rva0042D6B4PtrChaseField*>(a10)->get();
 if(info) {
  PanelWidget*detail=reinterpret_cast<PanelWidget*>(reinterpret_cast<Rva0042D6FDPtrChaseField*>(a10)->get());
  if(detail) {Context c={info,reinterpret_cast<int>(army),&record,true};detail->factory(&factory->CreatePanelFactory(&c));}
  PanelWidget*entries=reinterpret_cast<PanelWidget*>(reinterpret_cast<Rva0042D69DPtrChaseField*>(a10)->get());
  if(entries) {
   {Rva005E59A5::Payload p1(info,reinterpret_cast<int>(a18),reinterpret_cast<int>(&record));entries->entry(1,&Rva005E5C63Create(&p1));}
   {Rva005E59C2::Payload p2(info,reinterpret_cast<int>(a18),reinterpret_cast<int>(&record));entries->entry(2,&Rva005E5C95Create(&p2));}
   {Rva005E59DF::Payload p5(info,reinterpret_cast<int>(a18),reinterpret_cast<int>(&record));entries->entry(5,&Rva005E5CC7Create(&p5));}
  }
 }
}


struct Rva00080221RefImpl {virtual ~Rva00080221RefImpl(){} int refs;Rva00080221RefImpl():refs(0){}};
struct Impl005773DB: Rva00080221RefImpl {int value;Impl005773DB(const int &v):value(v){}};
// ??0Rva005773DB@@QAE@PBH@Z: retail 0x005773DB (53B). Its home is this unit: a
// second, strong definition elsewhere was a duplicate symbol at link.
inline Rva005773DB::Rva005773DB(const int *valuePtr){Impl005773DB *impl=new Impl005773DB(*valuePtr);pointer=(TargetRef00217D4C*)impl;if(impl)++impl->refs;}

int Rva005E62F1::rva005E57A2(void*){return reinterpret_cast<Rva005E57A2Callback*>(a4)->invoke();}
void Rva005E62F1::rva0050B238(void*,unsigned){}
