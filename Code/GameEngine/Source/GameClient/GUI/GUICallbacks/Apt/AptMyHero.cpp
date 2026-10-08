// cl: /O1 /G7 /MD /EHsc /arch:SSE2 /Ireference/shims/bfme2_ascii
// Identity: WB AptMyHero.cpp names SwitchToPendingHero (assert line816),
// calls the same assignment/view/bling chain, and uses this+144/+148.
// Native005B1E71..005B1EE2 is the full113-byte standard-thiscall body.
// CreateAHeroData assignment and the 8-byte GetObjectInfo record are existing
// providers. The native self guard, flag handling and virtual slot14 are
// target facts. Unknown helper semantics and virtual names stay address views;
// their call declarations model witnessed noarg/one-dword ABIs only.
// No constructor, destructor or vtable layout beyond the used slots is claimed.
#include "ascii_string.h"
class Image;
class ImageCollection {public: const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00223AC4 {public: Image *rva00223AC4(const char *,const char *);};
class Rva002239B2 {public: void rva002239E2(const AsciiString &,const Image *);};
class CreateAHeroData {public: CreateAHeroData &operator=(const CreateAHeroData &);};
struct BfmePod8 {int a;float b;};
class Rva005B0E9F {public: BfmePod8 *rva005B0E9F(int);};
class Rva00406E47 {public: bool rva00406E47(int);};
struct Rva005B0473View {char opaque[0x60];float field60;int field64,field68;};
class CreateAHeroManager {public: Rva005B0473View *rva00219F36(int,int);char pad000[0x1E8];AsciiString field1E8;};
class Display {public: char pad000[0x141];bool field141;};
extern Display *TheDisplay;
class GameWindowTransitionsHandler {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();
 void setGroup(AsciiString groupName,bool immediate);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;
class Rva001DBB82OneSetter {public: void enable();};
class GameWindowManager {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();
};
extern GameWindowManager *TheWindowManager;
extern CreateAHeroManager *TheCreateAHeroManager;
struct MyHeroBlingRecord {int field00,field04,minimum,maximum,field10;};
struct MyHeroBlingBlock {MyHeroBlingRecord *first,*last,*capacity;};
int GetGameClientRandomValue(int,int,char *,int);
class CommandButton;
class Rva00406ED7 {public: const CommandButton *rva00406ED7(int);};
void __cdecl Rva005B24CDHeroPowerText(void *,const char *,int);
void rva005B2295(int button,int name,int index,int page);
class AptMyHero {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 void SwitchToPendingHero();
 void rva005B21DA(CreateAHeroData *hero,bool flag,int mode);
 void rva005B0416(int);void rva005B0446();
 bool rva005B0725();
 void rva005B0923(int);void SetBling(int,int,int);
 Rva005B0473View *rva005B0473();
 void BuildBlingData();
 void rva005B0487();void rva005B1019();void rva005B1288();void rva005B097F(int);void rva005B0FCD(int);
private:
 char pad04[0x0C-4];
 int field0C,field10;
 char pad14[0x138-0x14];
 const Image *image138;
 char pad13C[4];
 void *holder140;
 CreateAHeroData *pending144;
 bool flag148;
 char pad149[3];
 int field14C;
 char pad150[0x168-0x150];
 float field168,field16C;
 char pad170[4];
 MyHeroBlingBlock blocks174[2];
 int field18C;
};
void AptMyHero::SwitchToPendingHero(){
 if(pending144 != reinterpret_cast<CreateAHeroData *>(this) && pending144)
  *reinterpret_cast<CreateAHeroData *>(this) = *pending144;
 ((Rva00406E47 *)this)->rva00406E47(((Rva005B0E9F *)this)->rva005B0E9F(rva005B0473()->field68)->a);
 BuildBlingData();
 slot14();
 rva005B0487();
 rva005B1019();
 if(flag148){rva005B097F(0);rva005B0FCD(1);flag148=false;}
}

// Native005B0473..005B0487 forwards fields10 then0C through the existing
// typed manager global. Named locals preserve the independently observed
// read order; the getter and returned view retain address-derived names.
Rva005B0473View *AptMyHero::rva005B0473(){int b=field10;int a=field0C;return TheCreateAHeroManager->rva00219F36(a,b);}

// WB AptMyHero.cpp line1170 and native005B0923..005B097F prove this
// unnamed record loop. Retail retains the exact diagnostic path and line1203.
// The category stays constant while the independent index increments.
void AptMyHero::rva005B0923(int group){
 MyHeroBlingBlock &block=blocks174[group];
 int index=0;
 for(MyHeroBlingRecord *record=block.first;record!=block.last;++record){
  int value=GetGameClientRandomValue(record->minimum,record->maximum,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Gui\\GUICallbacks\\Apt\\AptMyHero.cpp",0x4B3);
  SetBling(group,index++,value);
 }
 slot14();
}
// Native005B0487..005B04B6 and WB corresponding view access prove the
// +60 float bound and +168/+16C range. Retail emits SSE2 stores.
void AptMyHero::rva005B0487(){int b=field10;int a=field0C;float upper=TheCreateAHeroManager->rva00219F36(a,b)->field60;float *range=&field168;range[0]=0.0f;range[1]=upper;}

// WB record-minimum loop and native005B097F..005B09BB; independent index.
void AptMyHero::rva005B097F(int group){MyHeroBlingBlock &block=blocks174[group];int index=0;for(MyHeroBlingRecord *record=block.first;record!=block.last;++record)SetBling(group,index++,record->minimum);slot14();}

// Native005B0FCD..005B1019 adds a group-zero minimum reset before the
// WB record-default loop. Preserve that target-specific branch.
void AptMyHero::rva005B0FCD(int group){MyHeroBlingBlock &block=blocks174[group];int index=0;if(group==0)rva005B097F(group);for(MyHeroBlingRecord *record=block.first;record!=block.last;++record)SetBling(group,index++,record->field10);slot14();}

// Native005B0725..005B07C1 and WB portrait lookup agree on +138,
// HPGandalf fallback and Cah::Portrait. Existing canonical image global
// and retained image-store owner are used without a new alias or pin.
bool AptMyHero::rva005B0725(){
 const Image *image=image138;
 if(!image){AsciiString name("HPGandalf");image=TheMappedImageCollection->findImageByName(name);}
 const char *key="Cah::Portrait";
 if(reinterpret_cast<Rva00223AC4 *>(g_bfmeAptWindowManager)->rva00223AC4(key,0)==image)return false;
 AsciiString name(key);
 reinterpret_cast<Rva002239B2 *>(g_bfmeAptWindowManager)->rva002239E2(name,image);
 return true;
}

// WB twin 0x0156ED30 (unnamed, AptMyHero.cpp) and native 0x005B1288..
// 0x005B129F: the view-range reset, slot14 and 0x005B1019 -- the tail of
// SwitchToPendingHero -- with the last call a tail jump. AptCreateAHero
// calls it on its embedded hero at +0x27C (OnShowScreen 0x00513A2D).
void AptMyHero::rva005B1288(){rva005B0487();slot14();rva005B1019();}

// WB twin 0x0156F380 (unnamed, AptMyHero.cpp) and native 0x005B0416..
// 0x005B0446, RET 4: a thiscall whose receiver passes straight through to
// the hero's level button lookup 0x00406ED7; that button then labels the
// "MyPowerLevel" text and the "MyPowerIcon" icon for the level.
void AptMyHero::rva005B0416(int level){
 const CommandButton *button=reinterpret_cast<Rva00406ED7 *>(this)->rva00406ED7(level);
 Rva005B24CDHeroPowerText((void *)button,"MyPowerLevel",level);
 rva005B2295((int)button,(int)"MyPowerIcon",level,-1);
}

// WB twin 0x0156F3D0 (unnamed, AptMyHero.cpp; called from FrameUpdate) and
// native 0x005B0446..0x005B045D: labels the ten power levels in turn.
void AptMyHero::rva005B0446(){for(unsigned int level=0;level<10;++level)rva005B0416(level);}

// WB twin 0x01571180 (unnamed, AptMyHero.cpp) and native 0x005B21DA..
// 0x005B2295, RET 12: a new pending hero records the +0x148 flag and clears
// +0x18C; without a manager transition group (+0x1E8 empty) mode 1 falls
// back to 0, which switches heroes at once, while mode 1 runs the group's
// transition. Retail dispatches through a switch (sub/dec), not if/else.
void AptMyHero::rva005B21DA(CreateAHeroData *hero,bool flag,int mode){
 if(pending144==hero)return;
 pending144=hero;
 flag148=flag;
 field18C=0;
 if(TheCreateAHeroManager->field1E8.isEmpty())mode=0;
 switch(mode){
  case 0:
   SwitchToPendingHero();
   field14C=0;
   break;
  case 1:
   TheDisplay->field141=true;
   TheTransitionHandler->slot24();
   TheTransitionHandler->setGroup(TheCreateAHeroManager->field1E8,false);
   reinterpret_cast<Rva001DBB82OneSetter *>(TheTransitionHandler)->enable();
   TheWindowManager->slot28();
   field14C=1;
   break;
 }
}
