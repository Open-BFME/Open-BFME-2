// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5E254C..5E25B1 complete101B: pending selection24, icon range14/18,
// refresh clip, optionally display building-type1 tooltip. Original method unclaimed.
#include "unicode_string.h"
struct RGBColor;
class Mouse {public:void rva001EEA6D(UnicodeString,int,const RGBColor *,float);};
extern Mouse *TheMouse;
namespace StrategicInGameUI {
 enum LivingWorldBuildingType {BuildingType1=1};
 UnicodeString GetTooltipText(LivingWorldBuildingType);
 class RegionDetailsStructuresPage {public:class Impl;};
}
class StrategicInGameUI::RegionDetailsStructuresPage::Impl {public:class Icon;void SetSelectedIconIndex(int);};
class StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon {public:void Update();};

class Rva005F09F7 {public:void rva005F09F7();};
class Rva005E254C {public:void rva005E254C();private:
 char unknown00[0x14];StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon **first,**last;
 char unknown1C[8];int pending;char unknown28[4];bool tooltip;
};
void Rva005E254C::rva005E254C(){
 if(pending>=0){((StrategicInGameUI::RegionDetailsStructuresPage::Impl*)this)->SetSelectedIconIndex(pending);pending=-1;}
 StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon **finish=last;
 for(StrategicInGameUI::RegionDetailsStructuresPage::Impl::Icon **i=first;i!=finish;++i)(*i)->Update();
 ((Rva005F09F7*)this)->rva005F09F7();
 if(tooltip)TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(StrategicInGameUI::BuildingType1),-1,0,1.0f);
}
