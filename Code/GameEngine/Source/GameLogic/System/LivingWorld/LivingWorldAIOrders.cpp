// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Native4FB924..4FBB25 and WB131A480 prove LivingWorldAI::SubmitOrders,
// the three8/16/20-byte order queues68/74/80 and the temporary88B spawn copy.
// Existing sibling4FB7B2 retains its distinct skip predicate and clears80.
// Receiver extent134 is inherited from the independently checked home view
// and constructor4FB3F2. Field roles come from native/WB reads, not this padding.
// The existing certified raw-pointer dispatch overload at2B4076 bridges the
// established structArmy consumer without changing CanMoveArmyMember104's ABI.
// No new pin/alias: only that declaration repairs the previously unresolved
// relocation in the bank, whose complete513B body otherwise already matched.
#include <vector>
#include "ascii_string.h"
struct BfmePod8 {int a[2];}; struct BfmePod16 {int a[4];};
struct Rva005B09D8Record {int words[5];};
namespace _STL {
template<> BfmePod8 *vector<BfmePod8>::erase(BfmePod8*,BfmePod8*);
template<> BfmePod16 *vector<BfmePod16>::erase(BfmePod16*,BfmePod16*);
}
class Rva005B129FVector {public: Rva005B09D8Record *erase(Rva005B09D8Record*,Rva005B09D8Record*); __forceinline void clear() {erase(first,finish);} Rva005B09D8Record *first,*finish,*limit;};
class Rva004E3184 {public: Rva004E3184(const Rva004E3184&);virtual ~Rva004E3184();char bytes[0x58-4];};
class Rva004E0625 {public:int rva004E0625() const;};
class ArmySpawnerOrderView {public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();virtual void slot10();virtual void slot14();virtual void spawn(const Rva004E3184*);
};
class Rva0020EEF4Outer {public:int rva0020EEF4(int);};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C *rva0020EAF6(int);};
class Rva003F1C56Plot;struct Rva003F1BD3TemplateView;
class LivingWorldRegion {public:void *rva003F0588();void BuildBuilding(Rva003F1C56Plot*,const Rva003F1BD3TemplateView*);};
class Rva003F1093 {public:void rva003F1CFE(void*,int);};
struct LivingWorldArmy;
class LivingWorldLogic {public:
 bool CanMoveArmyMember(LivingWorldArmy*,int,int);
 __forceinline Rva0020EAF6View *getRegions() const {return (Rva0020EAF6View*)regions;}
 __forceinline Rva0020EEF4Outer *getSpawnerRegions() const {return (Rva0020EEF4Outer*)regions;}
 char unknown[0xB0];void *regions;
};
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0022C0CDSubsystem;extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
enum NameKeyType{NAMEKEY_INVALID=0};class ArmorTemplate;
class Rva002B6498 {public:ArmorTemplate *rva002B6498(NameKeyType);};
class Rva002E0A9FElem {public:int rva002E0A9F(void*);};
class Rva00318F42 {public:bool rva00318F42();};
class Rva002B4076 {public:void rva002B4076(void*,int,void*);};
class Rva002B2702 {public:void rva002B2702(void*,void*,int);};
class LivingWorldAI {public:
 void SubmitOrders();void rva004FB7B2();
private:
 Rva002E0A9FElem *owner;char unknown4[0x68-4];
 _STL::vector<BfmePod8> orders68;
 _STL::vector<BfmePod16> orders74;
 _STL::vector<Rva005B09D8Record> orders80;
 char unknown8C[0x134-0x8C];
};
template<class T> __forceinline void clearOrderVector(_STL::vector<T>&v) {v.erase(v.begin(),v.end());}
void LivingWorldAI::SubmitOrders() {
 if(!owner)return;
 unsigned n=orders68.size();
 for(unsigned i=0;i<n;++i) {
  Rva004E0625 *region=(Rva004E0625*)TheLivingWorldLogic->getSpawnerRegions()->rva0020EEF4(orders68[i].a[0]);
  if(region) {
   ArmySpawnerOrderView *spawner=(ArmySpawnerOrderView*)region->rva004E0625();
   Rva004E3184 spawn(*(Rva004E3184*)orders68[i].a[1]);spawner->spawn(&spawn);
  }
 }
 clearOrderVector(orders68);
 n=orders74.size();
 for(unsigned i=0;i<n;++i) {
  LivingWorldRegion *region=(LivingWorldRegion*)TheLivingWorldLogic->getRegions()->rva0020EAF6(orders74[i].a[1]);
  if(region) {
   if(*(bool*)&orders74[i])((Rva003F1093*)region)->rva003F1CFE((void*)orders74[i].a[3],1);
   else {
    Rva003F1C56Plot *plot=(Rva003F1C56Plot*)region->rva003F0588();
    region->BuildBuilding(plot,(const Rva003F1BD3TemplateView*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)orders74[i].a[2]));
   }
  }
 }
 clearOrderVector(orders74);
 n=orders80.size();
 for(unsigned i=0;i<n;++i) {
  LivingWorldArmy *army=(LivingWorldArmy*)owner->rva002E0A9F((void*)orders80[i].words[0]);
  if(army && (((Rva00318F42*)army)->rva00318F42() || ((AsciiString*)((char*)army+0x18))->isEmpty()))continue;
  if(orders80[i].words[2]) {
   if(TheLivingWorldLogic->CanMoveArmyMember(army,orders80[i].words[3],owner->rva002E0A9F((void*)orders80[i].words[2])))
    ((Rva002B4076*)TheLivingWorldLogic)->rva002B4076(army,orders80[i].words[3],(LivingWorldArmy*)owner->rva002E0A9F((void*)orders80[i].words[2]));
  } else ((Rva002B2702*)TheLivingWorldLogic)->rva002B2702(army,TheLivingWorldLogic->getRegions()->rva0020EAF6(orders80[i].words[4]),1);
 }
}
void LivingWorldAI::rva004FB7B2() {
 unsigned n=orders80.size();
 for(unsigned i=0;i<n;++i) {
  LivingWorldArmy *army=(LivingWorldArmy*)owner->rva002E0A9F((void*)orders80[i].words[0]);
  if(army && (((Rva00318F42*)army)->rva00318F42() || !((AsciiString*)((char*)army+0x18))->isEmpty()))continue;
  if(orders80[i].words[2]) {
   if(TheLivingWorldLogic->CanMoveArmyMember(army,orders80[i].words[3],owner->rva002E0A9F((void*)orders80[i].words[2])))
    ((Rva002B4076*)TheLivingWorldLogic)->rva002B4076(army,orders80[i].words[3],(LivingWorldArmy*)owner->rva002E0A9F((void*)orders80[i].words[2]));
  } else ((Rva002B2702*)TheLivingWorldLogic)->rva002B2702(army,TheLivingWorldLogic->getRegions()->rva0020EAF6(orders80[i].words[4]),1);
 }
 ((Rva005B129FVector*)&orders80)->clear();
}

// Native4FBB25..4FBC02 complete198B RET4 and independently mapped unnamed
// WB1319C70/390 establish the owner0/state4 phase dispatcher and its calls.
// Original dispatcher name remains unknown; retain its existing neutral pin.
// WB131A0F0 names the retreat role at native4FB600..4FB7B2 complete434B.
// Reuse the independently landed neutral Rva004FB600 provider; no alias pin.
// Canonical channel global g_Va00E04508 already owns the byte cleared here.
class Rva004FB600 {public:void rva004FB600();};
class Rva004FB382 {public:bool rva004FB382();};
class Rva004FB582Owner {public:void rva004FB582();};
class Rva004FB27E {public:void rva004FB27E();};
class Rva004FB2C1 {public:void rva004FB2C1();};
class Rva004FB303Owner {public:void rva004FB303();void rva004FB328();};
extern unsigned int g_Va00E04508;
struct AIPhaseOwnerPrefix {char unknown00[0x2c4];int submitted2C4;};
class Rva004FBB25Sub {public:void rva004FBB25(int);
private:AIPhaseOwnerPrefix *m_owner;int m_state;
};
void Rva004FBB25Sub::rva004FBB25(int phase){
 if(!m_owner)return;
 if(((Rva004FB382 *)this)->rva004FB382()){m_owner->submitted2C4=1;return;}
 switch(phase){
  case 0:
   switch(m_state){
    case 0:((Rva004FB582Owner *)this)->rva004FB582();m_state=1;break;
    case 1:((Rva004FB27E *)this)->rva004FB27E();m_state=2;break;
    case 2:((Rva004FB2C1 *)this)->rva004FB2C1();m_state=3;break;
    case 3:((Rva004FB303Owner *)this)->rva004FB303();m_state=4;break;
    case 4:((Rva004FB303Owner *)this)->rva004FB328();((LivingWorldAI *)this)->SubmitOrders();m_state=5;m_owner->submitted2C4=1;break;
   }
   break;
  case 1:case 2:case 3:case 5:m_owner->submitted2C4=1;break;
  case 4:((Rva004FB600 *)this)->rva004FB600();*(unsigned char *)&g_Va00E04508=0;m_state=0;m_owner->submitted2C4=1;break;
 }
}
