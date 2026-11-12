#define BFME_STRINGBASE_PUBLIC_DTOR
// Territory page Impl constructor, 0x005E3753 (408 B); WorldBuilder15F6340.
// Native ABI and layout are reconstructed from the complete retail body.
// Implicit concat-to-StringBase conversion controls temporary lifetimes.
// The real caller makes GetBonus use ESI through normal MSVC optimization.
// See reverse/attempt_evidence/0x005e3753_crack_i.txt.
// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Native5E38EB..5E3947 complete92B and WB15F6AA0. Owner from
// admitted dtor5E362F and vtableC77BD0; Impl allocation16B from direct native call5E3753.
#include "ascii_string.h"
#include "../../../../Include/Common/Rva0007DF07.h"
class Rva005EEE5A:public Rva0007DF07 {public:Rva005EEE5A();bool active;};
namespace StrategicInGameUI {class RegionDetailsTerritoryPage {public:class Impl;};}
namespace StrategicHUD {class RegionDetailsTerritoryMovieClip {public:class Impl;RegionDetailsTerritoryMovieClip(unsigned,const AsciiString&);virtual ~RegionDetailsTerritoryMovieClip();private:void *implementation;};}
class Image;
class StrategicInGameUI::RegionDetailsTerritoryPage::Impl {public:Impl(unsigned,const AsciiString&,void*);private:StrategicHUD::RegionDetailsTerritoryMovieClip m_clip;void *m_region;Image *m_image;};
class Rva005E362F:public Rva005EEE5A {public:Rva005E362F(void*,void*,void*);virtual ~Rva005E362F();private:StrategicInGameUI::RegionDetailsTerritoryPage::Impl *impl;};
Rva005E362F::Rva005E362F(void *level,void *name,void *region):impl(new StrategicInGameUI::RegionDetailsTerritoryPage::Impl((unsigned)level,*(const AsciiString*)name,region)){}

class BaseA { int a; };
class BaseB { int b; };
class LivingWorldRegion : public BaseA, public BaseB {
public:
    int GetCommandPointBonus() { return *(int*)((char*)this + 0x94); }
    int GetAttackBonus() { return *(int*)((char*)this + 0x9c); }
    int GetDefenseBonus() { return *(int*)((char*)this + 0xa0); }
    int GetExperienceBonus() { return *(int*)((char*)this + 0xa4); }
    int GetResourceBonus() { return *(int*)((char*)this + 0x90); }
    int GetPowerPointBonus() { return *(int*)((char*)this + 0x98); }
};

namespace StrategicInGameUI {
    struct BonusPropertyEntry {
        int bonusType;
        int (LivingWorldRegion::*getter)();
    };

    static __declspec(noinline) int GetBonus(LivingWorldRegion *region, int bonusType) {
        static BonusPropertyEntry bonusTypePropertyMap[] = {
            { 0, &LivingWorldRegion::GetCommandPointBonus },
            { 1, &LivingWorldRegion::GetAttackBonus },
            { 2, &LivingWorldRegion::GetDefenseBonus },
            { 3, &LivingWorldRegion::GetExperienceBonus },
            { 4, &LivingWorldRegion::GetResourceBonus },
            { 5, &LivingWorldRegion::GetPowerPointBonus },
        };
        int i = 0;
        while (bonusTypePropertyMap[i].bonusType != bonusType)
            ++i;
        int (LivingWorldRegion::*getter)() = bonusTypePropertyMap[i].getter;
        return (region->*getter)();
    }
}

#include "unicode_string.h"
class Image;
#include "../../../../Include/GameClient/MapMetaData.h"
#include "../../../../Include/GameClient/MapCache.h"
extern MapCache *TheMapCache;
Image *getMapPreviewImage(AsciiString);
#include "../../../../Include/GameClient/Image.h"
#include "../../../../Include/GameClient/Rva0020E89C.h"
class Rva005F1B41 { public: void rva005F1B41(const Image *); };
class Rva005F1CFEForwarder { public: void rva005F1CFE(const UnicodeString &); };
class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl {public:void SetTerritoryName(const UnicodeString &);void rva005F1999(int,int);};
class Rva005F1CF6Forwarder {public:__declspec(noinline) void rva005F1CF6(const UnicodeString &s){impl->SetTerritoryName(s);}private:char pad[4];StrategicHUD::RegionDetailsTerritoryMovieClip::Impl *impl;};
class Rva005F1B49Forwarder {public:__declspec(noinline) void rva005F1B49(int i,int value){impl->rva005F1999(i,value);}private:char pad[4];StrategicHUD::RegionDetailsTerritoryMovieClip::Impl *impl;};
struct Rva002226E5TextPlusString { const char *text; int length; const AsciiString *str; Rva002226E5TextPlusString(){} Rva002226E5TextPlusString(const Rva002226E5TextPlusString &r):text(r.text),length(r.length),str(r.str){} };
Rva002226E5TextPlusString operator+(const char *,const AsciiString &);
struct Rva0059AFC2In { int v[3]; };
struct Rva0059AFC2Out { int v[5]; };
Rva0059AFC2Out *Rva0059AFC2Copy(Rva0059AFC2Out *,Rva0059AFC2In *,const char *);
void *Rva0059B036Copy(void *,void *,int);
struct Rva005D2F96S24 { int v[6]; };
struct Rva005E35F4S32 { int v[8]; Rva005E35F4S32(){} Rva005E35F4S32(const Rva005E35F4S32 &r){for(int i=0;i<8;++i)v[i]=r.v[i];} };
Rva005E35F4S32 Rva005E35F4Build(const Rva005D2F96S24 &,const char *);
class Rva005E36C5 { public: operator StringBase<char>(); };

// Local adapter for the target's base-string converting constructor. The
// canonical BFME2 AsciiString intentionally flattens its StringBase layout.
// Keeping this conversion local preserves the shared header and the native
// full-expression lifetime of the materialized concatenation temporary.
class TerritoryMapPath: public AsciiString {public:TerritoryMapPath(const StringBase<char> &s):AsciiString((const AsciiString&)s){}};
StrategicInGameUI::RegionDetailsTerritoryPage::Impl::Impl(unsigned level,const AsciiString &name,void *region)
 : m_clip(level,name),m_region(region),m_image(0)
{
 Rva0059AFC2Out middle;
 Rva005D2F96S24 head;
 const AsciiString &map=*(const AsciiString *)((char *)m_region+0x18);
 TerritoryMapPath path(*(Rva005E36C5 *)&Rva005E35F4Build(
  *(const Rva005D2F96S24 *)Rva0059B036Copy(&head,Rva0059AFC2Copy(&middle,(Rva0059AFC2In *)&("maps\\"+map),"\\"),(int)&map),".map"));
 MapMetaData *meta=(MapMetaData *)TheMapCache->findMap(path);
 if(meta) {
  ((Rva005F1CF6Forwarder *)this)->rva005F1CF6(((Rva0020E89C *)m_region)->rva0020E89C());
  ((Rva005F1CFEForwarder *)this)->rva005F1CFE(meta->getDescription());
  m_image=getMapPreviewImage(path);
  if(m_image) ((Rva005F1B41 *)this)->rva005F1B41(m_image);
  else ((Rva005F1B41 *)this)->rva005F1B41(TheMappedImageCollection->findImageByName(AsciiString("MissingMap")));
  for(int i=0;i<6;++i) ((Rva005F1B49Forwarder *)this)->rva005F1B49(i,StrategicInGameUI::GetBonus((LivingWorldRegion *)m_region,i));
 }
}
