// ?getConstructButtonHelp@LivingWorldBuildingTemplate@@QBE?AVUnicodeString@@PAVRva003F1C22@@@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /Oy- /EHsc /MD /Ireference/shims/bfme2_ascii /D_CRTIMP=
#include "ascii_string.h"
#include "unicode_string.h"
class CreateAHeroData;
class Rva003F1C22 {
public:
 bool rva003F1C22(CreateAHeroData*,int*);
 char unknown00[0x11c];
 bool fortRestricted;
 bool isFortRestricted() const { return fortRestricted; }
};
class GameTextInterface {
public:
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
 SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
 virtual UnicodeString fetch(const char*,bool*);
 virtual UnicodeString fetch(const AsciiString&,bool*);
};
extern GameTextInterface *TheGameText;
class LivingWorldBuildingTemplate {
 char unknown00[0x1c];
 AsciiString label;
 char unknown20[8];
 int buildTime,kind;
 int getKind() const { return kind; }
public:
 void appendDisplayCommandPointBonus(UnicodeString&) const;
 UnicodeString getConstructButtonHelp(Rva003F1C22*) const;
};
UnicodeString LivingWorldBuildingTemplate::getConstructButtonHelp(Rva003F1C22 *region) const
{
 UnicodeString result=TheGameText->fetch(label,0);
 static AsciiString singular("CONTROLBAR:LW_Structure_BuildTimeSingular");
 static AsciiString plural("CONTROLBAR:LW_Structure_BuildTimePlural");
 bool exists=false;
 UnicodeString time;
 if(buildTime==1) time=TheGameText->fetch(singular,&exists);
 else time=TheGameText->fetch(plural,&exists);
 if(!exists) return result;
 time.format(&time,buildTime);
 result+=time;
 int count=0;
 if(region->rva003F1C22((CreateAHeroData*)kind,&count)) {
  UnicodeString restriction;
  if(count==0 && kind==1 && region->fortRestricted)
   restriction=TheGameText->fetch("CONTROLBAR:LW_FortRestricted",0);
  else {
   restriction=TheGameText->fetch("CONTROLBAR:LW_BuildNumberRestriction",0);
   restriction.format(&restriction,count);
  }
  result+=restriction;
 }
 appendDisplayCommandPointBonus(result);
 return result;
}
