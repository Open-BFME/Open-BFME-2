// cl: /Ireference/shims/bfme2_ascii /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// Native region-bonus label and formatting family. Static helpers are kept
// with their consumer to preserve the compiler's private register ABI.
#include "ascii_string.h"
#include "unicode_string.h"
struct RegionBonusPair { const char *format;const char *tooltip; };
struct RegionBonusRecord { int kind;RegionBonusPair labels; };
extern const char RegionBonusFormat0[]="STRATEGICHUD:RegionAbsoluteBonus";
extern const char RegionBonusTooltip0[]="STRATEGICHUD:RegionCommandPointBonusTooltip";
extern const char RegionBonusFormat1[]="STRATEGICHUD:RegionPercentageBonus";
extern const char RegionBonusTooltip1[]="STRATEGICHUD:RegionAttackBonusTooltip";
extern const char RegionBonusTooltip2[]="STRATEGICHUD:RegionDefenseBonusTooltip";
extern const char RegionBonusTooltip3[]="STRATEGICHUD:RegionExperienceBonusTooltip";
extern const char RegionBonusTooltip4[]="STRATEGICHUD:RegionResourceBonusTooltip";
extern const char RegionBonusTooltip5[]="STRATEGICHUD:RegionPowerPointBonusTooltip";
extern const RegionBonusRecord RegionBonusRecords[]={
 {0, {RegionBonusFormat0, RegionBonusTooltip0}},
 {1, {RegionBonusFormat1, RegionBonusTooltip1}},
 {2, {RegionBonusFormat1, RegionBonusTooltip2}},
 {3, {RegionBonusFormat1, RegionBonusTooltip3}},
 {4, {RegionBonusFormat1, RegionBonusTooltip4}},
 {5, {RegionBonusFormat0, RegionBonusTooltip5}}
};

class GameTextInterface {public:
 virtual ~GameTextInterface();
 virtual void s01();virtual void s02();virtual void s03();virtual void s04();
 virtual void s05();virtual void s06();virtual void s07();virtual void s08();
 virtual void s09();virtual void s10();virtual void s11();virtual void s12();
 virtual void s13();virtual void s14();
 virtual UnicodeString fetch(const char *label,bool *exists=0)=0;
};
extern GameTextInterface *TheGameText;
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
static __declspec(noinline) const RegionBonusPair *LookupRegionBonus(int kind) {
 int i=0;
 if(kind) { do {++i;} while(RegionBonusRecords[i].kind!=kind); }
 return &RegionBonusRecords[i].labels;
}
static __declspec(noinline) UnicodeString FormatRegionBonus(int kind,int count) {
 if(count>0) {
  UnicodeString text;
  bool exists;
  UnicodeString format=TheGameText->fetch(LookupRegionBonus(kind)->format,&exists);
  if(exists)text.format(format.str(),count);
  return text;
 }
 return TheGameText->fetch("STRATEGICHUD:RegionBonusNone",0);
}
class Image;
class Rva00524306 {public:
 void rva00524306(const StringBase<char>& key);
 void rva00524725(const AsciiString& key,const Image *image);
};
class AptCommandMapAdder {public:AptCommandMapAdder();~AptCommandMapAdder();private:char bytes[12];};
class Rva005242D7 {public:Rva005242D7();~Rva005242D7();private:char bytes[12];};
namespace StrategicHUD {class RegionDetailsTerritoryMovieClip {public:class Impl;};}
class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl {
public:void rva005F1999(int index,int value);
 void rva005F191E(const Image *image);
 void rva005F1A2D();
private:unsigned int level;AsciiString name;
 AptCommandMapAdder commands;Rva005242D7 images;
 UnicodeString title,description;const Image *preview;int bonuses[6];int selectedBonus;
};
void StrategicHUD::RegionDetailsTerritoryMovieClip::Impl::rva005F1999(int index,int value) {
 if(value!=bonuses[index]) {
  AsciiString key;key.format("APT:_level%u.%s_Bonus%d",level,name.str(),index);
  ((BfmeAptWindowManager*)TheRva00222A8BTarget)->bfmeSetText(key,FormatRegionBonus(index,value),false);
  bonuses[index]=value;
 }
}

static __declspec(noinline) UnicodeString RegionBonusTooltip(int kind) {
 return TheGameText->fetch(LookupRegionBonus(kind)->tooltip,0);
}
struct RGBColor;
class Mouse {public:void rva001EEA6D(UnicodeString text,int delay,const RGBColor *color,float scale);};
extern Mouse *TheMouse;
void StrategicHUD::RegionDetailsTerritoryMovieClip::Impl::rva005F1A2D() {
 if(selectedBonus>=0 && selectedBonus<6)TheMouse->rva001EEA6D(RegionBonusTooltip(selectedBonus),-1,0,1.0f);
}
