// ?InitializeFactionVariables@AptStats@@QAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" unsigned char*__cdecl _mbscpy(unsigned char*,const unsigned char*);
class Rva00559AC1;
class AptStats {
public:
 virtual ~AptStats();
 virtual Rva00559AC1*rankValues();virtual int rankPoints(int);
 void ColorExtern(int,char*,bool);
 void NextRankExtern(int,char*,bool);
 void InitializeFactionVariables();
 char beforeOwner[0x14];void*owner;
};
void AptStats::ColorExtern(int faction,char*out,bool lvalue) {
 if(lvalue)return;
 const char*color="0xFFFFFFFF";
 switch(faction) {
 case 0:color="0x0E75D6";break;
 case 1:color="0x12AC7F";break;
 case 2:color="0xC0B60A";break;
 case 3:color="0x646464";break;
 case 4:color="0xD00303";break;
 case 5:color="0xF5772A";break;
 }
 _mbscpy(reinterpret_cast<unsigned char*>(out),reinterpret_cast<const unsigned char*>(color));
}

class Rva00559AC1 {public:float rva00559AF9(int);};
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
void AptStats::NextRankExtern(int faction,char*out,bool lvalue) {
 if(lvalue)return;
 int points=rankPoints(faction);
 float progress=rankValues()->rva00559AF9(points)*100.0f;
 sprintf(out,"%d",int(progress));
}
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
typedef void(AptStats::*StatsHandler)();
struct DelegateDesc {AptStats*object;StatsHandler method;DelegateDesc(AptStats*o,StatsHandler m):object(o),method(m){}};
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);TargetRef00217D4C*ptr;};
template<class T>class AptRef:public Rva00579E47 {
public:AptRef(const DelegateDesc&d):Rva00579E47(d){}
 AptRef(const AptRef&o):Rva00579E47(o){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class AptExternHandler;
class AptExternHandlerAdder {public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);};
class Rva00524306 {public:void rva00524767(const AsciiString&,const AsciiString&);};
class BfmeAptWindowManager {public:void bfmeSetText(const AsciiString&,const UnicodeString&,bool);};
extern BfmeAptWindowManager*g_bfmeAptWindowManager;
extern class PlayerTemplateStore*ThePlayerTemplateStore;
extern const char*g_rva0033A3F4Table[7];
class GameTextInterface {
public:virtual~GameTextInterface(){}
 virtual void slot00()=0;virtual void slot01()=0;virtual void slot02()=0;virtual void slot03()=0;
 virtual void slot04()=0;virtual void slot05()=0;virtual void slot06()=0;virtual void slot07()=0;
 virtual void slot08()=0;virtual void slot09()=0;virtual void slot10()=0;virtual void slot11()=0;
 virtual void slot12()=0;virtual UnicodeString fetch(const AsciiString&,bool * =0)=0;
};
extern GameTextInterface*TheGameText;
void AptStats::InitializeFactionVariables() {
 if(!ThePlayerTemplateStore)return;
 const DelegateDesc color(this,reinterpret_cast<StatsHandler>(&AptStats::ColorExtern));
 const DelegateDesc level(this,reinterpret_cast<StatsHandler>(&AptStats::NextRankExtern));
 for(int faction=0;faction<6;++faction) {
  const char*side=g_rva0033A3F4Table[faction];
  AsciiString name;
  name.format("FactionColor%d",faction);
  reinterpret_cast<AptExternHandlerAdder*>(static_cast<char*>(owner)+0x10)->AddExternHandler(name,faction,AptRef<AptExternHandler>(color));
  name.format("FactionLevel%d",faction);
  reinterpret_cast<AptExternHandlerAdder*>(static_cast<char*>(owner)+0x10)->AddExternHandler(name,faction,AptRef<AptExternHandler>(level));
  AsciiString label;label.format("SIDE:%s",side);
  UnicodeString display=TheGameText->fetch(label);
  name.format("Stats:FactionName_%d",faction);
  g_bfmeAptWindowManager->bfmeSetText(name,display,false);
  AsciiString image("AptIcon");image.concat(side);
  name.format("Stats:FactionIcon_%d",faction);
  reinterpret_cast<Rva00524306*>(static_cast<char*>(owner)+0x40)->rva00524767(name,image);
  image.format("Apt%sImage",side);
  name.format("Stats:FactionImage_%d",faction);
  reinterpret_cast<Rva00524306*>(static_cast<char*>(owner)+0x40)->rva00524767(name,image);
 }
}
