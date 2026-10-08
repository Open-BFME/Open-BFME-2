// cl: /O1 /G7 /MD /EHsc /arch:SSE2
// Identity: WB AptMyHero.cpp names SwitchToPendingHero (assert line816),
// calls the same assignment/view/bling chain, and uses this+144/+148.
// Native005B1E71..005B1EE2 is the full113-byte standard-thiscall body.
// CreateAHeroData assignment and the 8-byte GetObjectInfo record are existing
// providers. The native self guard, flag handling and virtual slot14 are
// target facts. Unknown helper semantics and virtual names stay address views;
// their call declarations model witnessed noarg/one-dword ABIs only.
// No constructor, destructor or vtable layout beyond the used slots is claimed.
class CreateAHeroData {public: CreateAHeroData &operator=(const CreateAHeroData &);};
struct BfmePod8 {int a;float b;};
class Rva005B0E9F {public: BfmePod8 *rva005B0E9F(int);};
class Rva00406E47 {public: bool rva00406E47(int);};
struct Rva005B0473View {char opaque[0x60];float field60;int field64,field68;};
class CreateAHeroManager {public: Rva005B0473View *rva00219F36(int,int);};
extern CreateAHeroManager *TheCreateAHeroManager;
struct MyHeroBlingRecord {int field00,field04,minimum,maximum,field10;};
struct MyHeroBlingBlock {MyHeroBlingRecord *first,*last,*capacity;};
int GetGameClientRandomValue(int,int,char *,int);
class AptMyHero {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();virtual void slot14();
 void SwitchToPendingHero();
 void rva005B0923(int);void SetBling(int,int,int);
 Rva005B0473View *rva005B0473();
 void BuildBlingData();
 void rva005B0487();void rva005B1019();void rva005B097F(int);void rva005B0FCD(int);
private:
 char pad04[0x0C-4];
 int field0C,field10;
 char pad14[0x140-0x14];
 void *holder140;
 CreateAHeroData *pending144;
 bool flag148;
 char pad149[0x168-0x149];
 float field168,field16C;
 char pad170[4];
 MyHeroBlingBlock blocks174[2];
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
