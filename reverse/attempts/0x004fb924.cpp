// ?SubmitOrders@LivingWorldAI@@QAEXXZ
// partial score=0.992202729 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
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
class Rva002B4076 {public:void rva002B4076(LivingWorldArmy*,int,LivingWorldArmy*);};
class Rva002B2702 {public:void rva002B2702(void*,void*,int);};
class LivingWorldAI {public:
 void SubmitOrders();void rva004FB7B2();
private:
 Rva002E0A9FElem *owner;char unknown4[0x68-4];
 _STL::vector<BfmePod8> orders68;
 _STL::vector<BfmePod16> orders74;
 _STL::vector<Rva005B09D8Record> orders80;
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
