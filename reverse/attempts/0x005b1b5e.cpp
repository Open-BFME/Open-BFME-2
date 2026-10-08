// ?BuildBlingData@AptMyHero@@QAEXXZ
// partial score=0.95 date=2026-10-08
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
#include "unicode_string.h"
class Image;
class ImageCollection {public: const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
class BfmeAptWindowManager {public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool);};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();
 virtual UnicodeString fetch(const AsciiString &label,bool *exists=0);
};
extern GameTextInterface *TheGameText;
// CreateAHeroData's bling value get/set pair, rowed under this owner.
class Rva00407E28 {public: int rva00407E28(int id);bool rva00407E53(int id);bool rva00407DE0(int id,int value);};
class CreateAHeroHero {public: void ConstructHeroBlingList();};
// A bling binder (20 bytes): its name key, the game-text label, and the
// slot and category it fills.
struct BlingBinder {int key;AsciiString label;int pad08;unsigned int slot;int category;};
struct BlingBinderList {unsigned int size() const {return last-first;}BlingBinder *first,*last,*capacity;};
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
void __cdecl Rva0043DB23(Rva00222A8BTarget *,void *,const char *);
class Rva00223AC4 {public: Image *rva00223AC4(const char *,const char *);};
class Rva002239B2 {public: void rva002239E2(const AsciiString &,const Image *);};
// AptMyHero's base: vtable 0x00C38D88's five slots, the rowed assignment
// and destructor, and the fields the screen reads.
class CreateAHeroData {
public:
 virtual ~CreateAHeroData();
 virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 CreateAHeroData &operator=(const CreateAHeroData &);
protected:
 char pad04[0x0C-4];
 int field0C,field10;
 char pad14[0x138-0x14];
 const Image *image138;
 char pad13C[4];
};
void free(void *);
struct BfmePod8 {int a;float b;};
// The rowed by-value resize 0x005FF96A is spelled on this vector view.
class BfmePod8Vector {public: ~BfmePod8Vector(){if(first)free(first);}void resize(unsigned int,BfmePod8);unsigned int size() const {return last-first;}BfmePod8 *first,*last,*capacity;};
class Rva005B0E9F {public: BfmePod8 *rva005B0E9F(int);};
class Rva00406E47 {public: bool rva00406E47(int);};
struct Rva005B0473View {char opaque[0x60];float field60;int field64,field68;};
struct CreateAHeroClassRecord {char opaque[0x20];};
struct CreateAHeroClassList {unsigned int size() const {return last-first;}CreateAHeroClassRecord *first,*last,*capacity;};
class CreateAHeroManager {public: Rva005B0473View *rva00219F36(int,int);const AsciiString &GetBlingNameTag(int,const CreateAHeroHero *,unsigned int);int GetSubClassSpendableAttributePoints(unsigned int,unsigned int);void *GetBlingBinder(unsigned int);int GetBlingCount(int,const CreateAHeroHero *) const;int GetSubClassDefaultBlingId(int,unsigned int,unsigned int) const;int GetSubClassAttributeMinValue(unsigned int,unsigned int,unsigned int);int GetSubClassAttributeMaxValue(unsigned int,unsigned int,unsigned int);int GetSubClassAttributeDefaultValue(unsigned int,unsigned int,unsigned int);unsigned int GetClassCount() const {return classes14C.size();}char pad000[0x14C];CreateAHeroClassList classes14C;char pad158[0x168-0x158];BlingBinderList binders168;char pad174[0x1E8-0x174];AsciiString field1E8;};
class Object;
class Drawable {public: char pad000[0xFC];Object *object;char pad100[4];Drawable *next;};
class GameClient {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 virtual void slot18();virtual void slot1C();virtual void slot20();virtual void slot24();virtual void slot28();virtual void slot2C();
 virtual void slot30();virtual void slot34();virtual void slot38();virtual void slot3C();virtual void slot40();
 virtual Drawable *firstDrawable();
};
extern GameClient *TheGameClient;
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
struct MyHeroBlingBlock {~MyHeroBlingBlock();unsigned int size() const {return last-first;}MyHeroBlingRecord &operator[](unsigned int n){return first[n];}MyHeroBlingRecord *first,*last,*capacity;};
int GetGameClientRandomValue(int,int,char *,int);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *,const char *);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
// The Object fields the location map reads; offsets are retail's.
class Object {public: char pad00[0x44];float field44;char pad48[0x74-0x48];int field74;char pad78[0x88-0x78];AsciiString name88;};
class CommandButton;
class Rva00406ED7 {public: const CommandButton *rva00406ED7(int);};
void __cdecl Rva005B24CDHeroPowerText(void *,const char *,int);
bool __cdecl rva005B2295(const CommandButton *button,const char *prefix,int index,int page);
class Rva00223A94 {public: int rva00223A94(const AsciiString *);};
class Rva005241DF {public: void rva005241DF(const StringBase<char> &);};
class Rva005B1830 {public: void rva005B1830();};
class Rva005B1A07 {public: void rva005B1B26(unsigned int);};
const AsciiString &rva005B0A53(const char *kind,int index);
class AptMyHero : public CreateAHeroData {
public:
 virtual ~AptMyHero();
 virtual void slot14();
 void SwitchToPendingHero();
 void rva005B21DA(CreateAHeroData *hero,bool flag,int mode);
 void rva005B0416(int);int rva005B0E60(const Object *);void rva005B1A6C();void rva005B0446();
 bool rva005B0725();
 void rva005B0923(int);void SetBling(int,int,int);void AdjustBling(int,int,int);
 Rva005B0473View *rva005B0473();
 void BuildBlingData();
 void rva005B0487();void rva005B1019();void rva005B1288();void rva005B097F(int);void rva005B0FCD(int);
private:
 void *holder140;
 CreateAHeroData *pending144;
 bool flag148;
 char pad149[3];
 int field14C;
 int field150;
 int availAttribPoints154;	// WorldBuilder: m_availAttribPoints
 int maxAttribPoints158;
 BfmePod8Vector mapObjectInfo15C;
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
 rva005B2295(button,"MyPowerIcon",level,-1);
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

// WB twin 0x01571460 (unnamed, AptMyHero.cpp, __thiscall) and native
// 0x005B0E60..0x005B0E9F, RET 4: the map location an object's name encodes
// after its first '_', or -1. Its only caller 0x005B1A6C sets ECX to the
// AptMyHero receiver; the body never reads it.
int AptMyHero::rva005B0E60(const Object *object){
 if(!object)return -1;
 const char *suffix=strstr(object->name88.str(),"_");
 if(!suffix)return -1;
 return atoi(suffix+1);
}

// WB twin 0x0156F220 (unnamed, AptMyHero.cpp) and native 0x005B1A6C..
// 0x005B1B26: rebuilds the +0x15C location map, one empty record per
// CreateAHeroManager class, then for every drawable's object whose name
// encodes a location stores the object's +0x74 and +0x44 there, growing
// the map when the location is past its end.
void AptMyHero::rva005B1A6C(){
 BfmePod8 empty={0,0.0f};
 mapObjectInfo15C.resize(TheCreateAHeroManager->GetClassCount(),empty);
 for(Drawable *drawable=TheGameClient->firstDrawable();drawable;drawable=drawable->next){
  Object *object=drawable->object;
  if(!object)continue;
  int location=rva005B0E60(object);
  if(location<0)continue;
  if(location>=(int)mapObjectInfo15C.size()){BfmePod8 grown={0,0.0f};mapObjectInfo15C.resize(location+1,grown);}
  mapObjectInfo15C.first[location].a=object->field74;
  mapObjectInfo15C.first[location].b=object->field44;
 }
}

// AptMyHero::SetBling, retail 0x005B07C1..0x005B0923 (354 bytes, RET 12).
// WorldBuilder names it and asserts the slot, m_firstBling/m_lastBling and
// m_availAttribPoints bounds that retail keeps as early returns. Category 1
// shows the bling's game-text name under APT:MyHeroAppearanceVal_<group>;
// category 0 spends attribute points and shows the rest. The new value is
// stored through the hero data's bling setter either way.
void AptMyHero::SetBling(int category,int group,int to){
 MyHeroBlingBlock &block=blocks174[category];
 if((unsigned int)group>=(unsigned int)(block.last-block.first))return;
 MyHeroBlingRecord &record=block.first[group];
 int current=reinterpret_cast<Rva00407E28 *>(this)->rva00407E28(record.field00);
 if(to<record.minimum||to>record.maximum)return;
 switch(category){
 case 1:{
  AsciiString key;
  key.format("APT:MyHeroAppearanceVal_%d",group);
  const AsciiString &name=TheCreateAHeroManager->GetBlingNameTag(record.field00,reinterpret_cast<const CreateAHeroHero *>(this),to);
  g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(name),false);
 }break;
 case 0:{
  int diff=current-to;
  int &points=availAttribPoints154;
  if(points+diff<0||points+diff>maxAttribPoints158)return;
  points+=diff;
  UnicodeString text;
  text.format((const unsigned short *)L"%d",points);
  g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:MyHeroAttribPoints"),text,false);
 }break;
 }
 reinterpret_cast<Rva00407E28 *>(this)->rva00407DE0(record.field00,to);
}

// AptMyHero::AdjustBling, retail 0x005B0EE6..0x005B0FCB (231 bytes, RET 12).
// WorldBuilder names it and asserts the slot bound kept here as an early
// return. A record with a zero +0x04 step is fixed. Category 1 wraps the
// stepped value into [first, last]; category 0 first trims the delta to
// what m_availAttribPoints (+0x154, cap +0x158) allows, then clamps the
// result into [first, last]. SetBling stores it and slot 5 refreshes.
void AptMyHero::AdjustBling(int category,int group,int delta){
 MyHeroBlingBlock &block=blocks174[category];
 if((unsigned int)group>=(unsigned int)(block.last-block.first))return;
 MyHeroBlingRecord &record=block.first[group];
 if(record.field04==0)return;
 int current=reinterpret_cast<Rva00407E28 *>(this)->rva00407E28(record.field00);
 switch(category){
 case 1:
  for(current+=delta;current>record.maximum;current-=record.field04){}
  for(;current<record.minimum;current+=record.field04){}
  break;
 case 0:
  for(;delta!=0&&availAttribPoints154-delta>maxAttribPoints158;++delta){}
  for(;delta!=0&&availAttribPoints154-delta<0;--delta){}
  if(current+delta>record.maximum)delta=record.maximum-current;
  else if(current+delta<record.minimum)delta=record.minimum-current;
  current+=delta;
  break;
 default:
  return;
 }
 SetBling(category,group,current);
 slot14();
}

// WB-unnamed helper, retail 0x005B0A53..0x005B0A95 (cdecl): the shared
// "MyHero::<kind>Attrib_<index>" key, built in a function-local static
// AsciiString (guard 0x00E0645C, object 0x00E06458, atexit cleanup
// 0x007B969E). The destructor walks it with the kinds Base, Cur and Max.
const AsciiString &rva005B0A53(const char *kind,int index){
 static AsciiString key;
 key.format("MyHero::%sAttrib_%d",kind,index);
 return key;
}

// AptMyHero::~AptMyHero, retail 0x005B190D..0x005B1A07 (250 bytes): drops
// the Base/Cur/Max attribute keys of five slots from the +0x140 holder's
// +0x228 registry, clears the Cah::Portrait image key, runs 0x005B1830,
// then the members (two bling vectors at +0x174, the location map at
// +0x15C) and the CreateAHeroData base are destroyed.
AptMyHero::~AptMyHero(){
 for(int i=0;i<5;++i){
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Base",i));
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Cur",i));
  reinterpret_cast<Rva005241DF *>((char *)holder140+0x228)->rva005241DF(*(const StringBase<char> *)&rva005B0A53("Max",i));
 }
 {
  AsciiString key("Cah::Portrait");
  reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&key);
 }
 reinterpret_cast<Rva005B1830 *>(this)->rva005B1830();
}

// AptMyHero::BuildBlingData, retail 0x005B1B5E..0x005B1E71 (787 bytes, EH).
// WorldBuilder names it; its asserts (!binder, a slot already used,
// m_firstBling > m_lastBling) are the early outs and fixups retail keeps.
// It resets the attributes (0x005B1830), takes the subclass's spendable
// points as both the available and the maximum, rebuilds the hero's bling
// list, then fills one record per manager binder: appearance records
// (category 1) span the bling count with the subclass default, attribute
// records (category 0) take the subclass min/max/default or, without
// blings, a value derived from the class, subclass and binder index. Each
// gets its Apt label and a value clamped into range through SetBling.
void AptMyHero::BuildBlingData(){
 reinterpret_cast<Rva005B1830 *>(this)->rva005B1830();
 int sub=field10;int cls=field0C;
 maxAttribPoints158=availAttribPoints154=TheCreateAHeroManager->GetSubClassSpendableAttributePoints(cls,sub);
 reinterpret_cast<CreateAHeroHero *>(this)->ConstructHeroBlingList();
 unsigned int count=TheCreateAHeroManager->binders168.size();
 for(unsigned int i=0;i<count;++i){
  BlingBinder *binder=(BlingBinder *)TheCreateAHeroManager->GetBlingBinder(i);
  if(!binder)continue;
  int category=binder->category;
  unsigned int slot=binder->slot;
  MyHeroBlingBlock &block=blocks174[category];
  if(slot>=(unsigned int)(block.last-block.first))reinterpret_cast<Rva005B1A07 *>(&block)->rva005B1B26(slot+1);
  MyHeroBlingRecord &record=block.first[slot];
  if(record.field00!=0)continue;
  record.field00=binder->key;
  record.field10=0;
  bool hasValue=reinterpret_cast<Rva00407E28 *>(this)->rva00407E53(record.field00);
  unsigned int value=reinterpret_cast<Rva00407E28 *>(this)->rva00407E28(record.field00);
  AsciiString key;
  switch(category){
  case 1:
   record.minimum=0;
   record.maximum=TheCreateAHeroManager->GetBlingCount(record.field00,reinterpret_cast<const CreateAHeroHero *>(this))-1;
   {int s2=field10;int c2=field0C;record.field10=TheCreateAHeroManager->GetSubClassDefaultBlingId(record.field00,c2,s2);}
   key.format("APT:MyHeroAppearance_%d",slot);
   g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(binder->label),false);
   if(hasValue)value=record.field10;
   break;
  case 0:
   if(TheCreateAHeroManager->GetBlingCount(record.field00,reinterpret_cast<const CreateAHeroHero *>(this))){
    {int s2=field10;int c2=field0C;record.minimum=TheCreateAHeroManager->GetSubClassAttributeMinValue(record.field00,c2,s2);}
    {int s2=field10;int c2=field0C;record.maximum=TheCreateAHeroManager->GetSubClassAttributeMaxValue(record.field00,c2,s2);}
    {int s2=field10;int c2=field0C;record.field10=TheCreateAHeroManager->GetSubClassAttributeDefaultValue(record.field00,c2,s2);}
   }else{
    record.minimum=((field0C+1)*(field10+1)*(i+1))%10+5;
    record.maximum=record.minimum+3+(int)(i*3)%10-field0C;
   }
   if(hasValue)value=record.minimum;
   reinterpret_cast<Rva00407E28 *>(this)->rva00407DE0(record.field00,record.minimum);
   key.format("APT:MyHeroAttribute_%d",slot);
   g_bfmeAptWindowManager->bfmeSetText(key,TheGameText->fetch(binder->label),false);
   break;
  default:
   continue;
  }
  if(record.minimum>record.maximum)record.minimum=record.maximum;
  record.field04=record.maximum-record.minimum+1;
  if(value<(unsigned int)record.minimum||value>(unsigned int)record.maximum)value=record.minimum;
  if(record.field10<record.minimum||record.field10>record.maximum)record.field10=record.minimum;
  SetBling(category,slot,value);
 }
 slot14();
 Rva0043DB23(TheRva00222A8BTarget,*(void **)((char *)holder140+0x274),"UpdateHeroBaseAttributes");
}
