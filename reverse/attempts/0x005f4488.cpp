// ?DoUpdate@ArmyUnitIcon@StrategicInGameUI@@UAEXXZ
// partial score=0.9 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
#include "ascii_string.h"
#include "unicode_string.h"
class Rva005FC70A {public:void rva005FC70A(unsigned char);};
class Rva005FC71E {public:void rva005FC71E(unsigned char);};
class Rva005FC73BPtrChaseField {public:bool get()const;};
class Rva005FD034 {public:void rva005FD034(int);};
class Rva005FD04B {public:void rva005FD04B(unsigned char);};
class Rva002A98A7DwordField {public:int get()const;};
struct UnitView {
 int unknown; AsciiString name; int unknown08; int rank;
 char pad10[0xb8-0x10]; int flagB8; int flagBC; int unknownC0; unsigned char valueC4;
};
struct TemplateView { char pad[0x5c4]; int tooltip; };
class Rva002D06CA {public:void *rva002D06CA(const AsciiString *);};
class ThingFactory; extern ThingFactory *TheThingFactory;
struct RGBColor;
class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor *,float);};
extern Mouse *TheMouse;
class UpgradeTemplate;
class UpgradeCenter {public:const UpgradeTemplate *rva0026EEA0(int)const;};
extern UpgradeCenter *TheUpgradeCenter;
class GameTextInterface {public:
 virtual ~GameTextInterface();
 virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual void slot05();virtual void slot06();virtual void slot07();virtual void slot08();
 virtual void slot09();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();
 virtual UnicodeString fetch(const char *,bool *)=0;
 virtual UnicodeString fetch(const AsciiString &,bool *)=0;
};
extern GameTextInterface *TheGameText;
class Rva005F41AF {public:virtual void DoUpdate();void rva005F41AF();};
struct UnitClipHolder { void *p; __forceinline void *get()const{return p;} __forceinline bool IsBound()const{return p!=0;} };
struct UnitUpgradeList {
 int *begin,*end,*capacity;
 __forceinline unsigned size()const {return end-begin;}
 __forceinline const int &operator[](unsigned n)const{return begin[n];}
};
namespace StrategicInGameUI {
 UnicodeString GetTooltipText(int);
 class ArmyUnitIcon : public virtual Rva005F41AF {
 public: virtual void DoUpdate();
 private:
 int owner; UnitView *unit; UnitClipHolder clip;
 UnitUpgradeList upgrades; int unknown1c;
 };
}
void StrategicInGameUI::ArmyUnitIcon::DoUpdate() {
 Rva005F41AF::rva005F41AF();
 if(!clip.IsBound()) return;
 ((Rva005FD034 *)clip.get())->rva005FD034(unit->rank);
 ((Rva005FC70A *)clip.get())->rva005FC70A(unit->flagB8!=0);
 unsigned char value=unit->valueC4;
 ((Rva005FC71E *)clip.get())->rva005FC71E(value);
 ((Rva005FD04B *)clip.get())->rva005FD04B(unit->flagBC!=0);
 if(((Rva005FC73BPtrChaseField *)clip.get())->get()) {
  const AsciiString *name=&unit->name;
  if(!((const StringBase<char> *)name)->isEmpty()) {
   TemplateView *t=(TemplateView *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(name);
   if(t) { int tooltip=t->tooltip; TheMouse->rva001EEA6D(GetTooltipText(tooltip),-1,0,1.0f); }
  }
 }
 int index=((Rva002A98A7DwordField *)clip.get())->get();
 if(index<0) return;
 if((unsigned)index>=upgrades.size()) return;
 {
  const UpgradeTemplate *u=TheUpgradeCenter->rva0026EEA0(upgrades[index]);
  if(!u) return;
  TheMouse->rva001EEA6D(TheGameText->fetch(*(const AsciiString *)((const char *)u+0x28),0),-1,0,1.0f);
 }
}
