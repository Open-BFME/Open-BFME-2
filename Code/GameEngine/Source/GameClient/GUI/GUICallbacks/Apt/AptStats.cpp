// cl: /O1 /G7 /EHsc /MD /DNDEBUG /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
#include <string.h>
void Rva00030830FreeAllocation(void*);
namespace _STL {template<> inline void allocator<unsigned int>::deallocate(unsigned int*p,size_t)const {if(p)Rva00030830FreeAllocation(p);}}
#include "ascii_string.h"
#include "unicode_string.h"
extern "C" unsigned char*__cdecl _mbscpy(unsigned char*,const unsigned char*);
// WB15D9470 names AptStats::ColorExtern (AptStats.cpp251). The native
// faction initializer5DD2D3 takes this callback address and the same
// six color strings; stack arguments are faction, output and bool, RET12.
// Ghidra omitted the entry: the preceding verified5B destructor ends at
//5DCFCE and this callback ends at5DD029 after its own RET12, whole91B.
// Retail calls the actual _mbscpy import thunk629176, not a guessed strcpy
// pin sharing its address. All selected literals are checked at their refs.
// Persistent's native20B table base and trailing word14 are established
// by complete retail and the verified781B Persistent constructor. The derived native ctor proves
// owner18, word1C and a12B index-vector20; individual template flags stay neutral.
class Rva005DE9E3 {public: virtual ~Rva005DE9E3(); protected: unsigned words[4];};
class GameStats {public: class Persistent:public Rva005DE9E3 {public: Persistent(int); private:int m_14;};};
class GameWindow;
class PlayerTemplate {public: unsigned char prefix[0x150]; bool flag150,flag151; unsigned char suffixA[0x1bc-0x152];bool flag1bc;unsigned char suffixB[0x1dc-0x1bd];};
class PlayerTemplateStore {public:
 const PlayerTemplate*getNthPlayerTemplate(int)const;
 unsigned char prefix[12];PlayerTemplate*first;PlayerTemplate*finish;PlayerTemplate*limit;
};
extern PlayerTemplateStore*ThePlayerTemplateStore;
// ScienceType is the existing 49B four-byte append-provider ABI spelling.
// Native template indices do not establish science semantics or an int-template fold.
enum ScienceType { SCIENCE_STORAGE_ZERO=0 };
// Native table-owner dtor keeps vector teardown in its EH state. Use the
// rowed throwing game-memory provider rather than the nonthrowing CRT view.
namespace _STL {template<> inline void allocator<ScienceType>::deallocate(ScienceType*p,size_t)const {if(p)Rva00030830FreeAllocation(p);}}
class AptStats : public GameStats::Persistent {
public:
 AptStats(void*host);
 virtual ~AptStats();
 virtual void*rankValues();virtual int rankPoints(int);
 void ColorExtern(int,char*,bool);
 void NextRankExtern(int,char*,bool);
 void InitializeFactionVariables();
 void rva005DD48C();void rva005DD22B();void rva005DD0EB(int);
 void rva005DD14D(const char*,int,GameWindow*);void rva005DD1D0(const char*);
 void*owner;
 int m_word1c;
 std::vector<ScienceType> m_factionToTemplate;
};
typedef char Persistent24[(sizeof(GameStats::Persistent)==24)?1:-1];
typedef char AptStats44[(sizeof(AptStats)==44)?1:-1];
typedef char PlayerTemplate476[(sizeof(PlayerTemplate)==476)?1:-1];
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

// Named WB15D8A50 and complete native5DD609..5DD6B6 RET4. Native
// and WB agree on the7-column Persistent base, template selection and
// the parameterless faction initializer; WB assert62 names the index-vector.
AptStats::AptStats(void*host):GameStats::Persistent(7),owner(host),m_word1c(0)
{
 int count=ThePlayerTemplateStore->finish-ThePlayerTemplateStore->first;
 for(ScienceType index=static_cast<ScienceType>(0);index<count;index=static_cast<ScienceType>(index+1)) {
  const PlayerTemplate*pt=ThePlayerTemplateStore->getNthPlayerTemplate(index);
  if(pt->flag151 && !pt->flag150)
   m_factionToTemplate.push_back(index);
 }
 InitializeFactionVariables();
}

// WB015D9570 AptStats.cpp295 names this callback; native full68B
// [005DD029,005DD06D),RET12. Its address is taken by the faction-level
// registration at005DD2D3. Target virtual slots1/2 supply thresholds/points.
// The rank-progress dependency has independently proven entry and thiscall ABI.
class Rva00559AC1 {public:float rva00559AF9(int);int rva00559AC1(int);int rva00559ADC(int);};
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
void AptStats::NextRankExtern(int faction,char*out,bool lvalue)
{
 if(lvalue)return;
 int points=rankPoints(faction);
 float progress=((Rva00559AC1*)rankValues())->rva00559AF9(points)*100.0f;
 sprintf(out,"%d",int(progress));
}

// Registration guide: matched AptTimeLineStats and donor f98983a7d3bb
// AptStrategicPlayerStatus use the same eight-byte (owner, member pointer)
// descriptor and owning four-byte AptRef. Native 5DD2D3 binds both rowed
// callbacks and labels six factions; WB 15D8E40 names InitializeFactionVariables.
// Returning the inline descriptor closes native callback-address scheduling.
struct TargetRef00217D4C {void*vt;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
typedef void(AptStats::*StatsHandler)();
struct DelegateDesc {AptStats*object;StatsHandler method;DelegateDesc(){}DelegateDesc(AptStats*o,StatsHandler m):object(o),method(m){}};
// ?MakeStatsDelegate absent-from-retail
__forceinline DelegateDesc MakeStatsDelegate(AptStats *owner,StatsHandler method) {DelegateDesc d(owner,method);return d;}
class Rva00579E47 {public:Rva00579E47(const DelegateDesc&);TargetRef00217D4C*ptr;};
template<class T>class AptRef:public Rva00579E47 {
public:AptRef(const DelegateDesc&d):Rva00579E47(d){}
 AptRef(const AptRef&o):Rva00579E47(o){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class AptExternHandler;
class AptExternHandlerAdder {public:void AddExternHandler(const AsciiString&,int,AptRef<AptExternHandler>);};
class Image;
class Rva00524306 {public:void rva00524767(const AsciiString&,const AsciiString&);void rva00524725(const AsciiString&,const Image*);};
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
 const DelegateDesc color=MakeStatsDelegate(this,reinterpret_cast<StatsHandler>(&AptStats::ColorExtern));
 const DelegateDesc level=MakeStatsDelegate(this,reinterpret_cast<StatsHandler>(&AptStats::NextRankExtern));
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

UnicodeString Rva00559C3D(unsigned char,int);
const Image*Rva00559B64GetImage(int,int);
// Native [5DD48C,5DD5ED) owns both rank string temporaries separately.
// Receiver slots 1/2 and template flag1BC are target facts; method name unknown.
// The rowed rank/string/image providers establish each consumed ABI.
void AptStats::rva005DD48C() {
 Rva00559AC1*values=(Rva00559AC1*)rankValues();
 if(ThePlayerTemplateStore) {
  for(int faction=0;faction<6;++faction) {
   AsciiString name;
   int points=rankPoints(faction);
   int rank=values->rva00559AC1(points);
   const PlayerTemplate*pt=ThePlayerTemplateStore->getNthPlayerTemplate(m_factionToTemplate[faction]);
   name.format("Stats:LevelName_%d",faction);
   g_bfmeAptWindowManager->bfmeSetText(name,Rva00559C3D(pt&&pt->flag1bc,rank),false);
   name.format("Stats:RankImage_%d",faction);
   const Image*image=Rva00559B64GetImage(faction,rank);
   reinterpret_cast<Rva00524306*>(static_cast<char*>(owner)+0x40)->rva00524725(name,image);
   name.format("Stats:PointsNextLevel_%d",faction);
   UnicodeString progress;
   int remain=values->rva00559ADC(points);
   progress.format((const unsigned short*)L"%d",remain);
   g_bfmeAptWindowManager->bfmeSetText(name,progress,false);
  }
 }
 rva005DD0EB(m_word1c);
}
class AptScreenInitGadgets;class AptCommandMap;
void _bfme_setAptScreenRef(const AsciiString&,AptRef<AptScreenInitGadgets>);
class AptCommandMapAdder {public:void AddCommandMap(const AsciiString&,AptRef<AptCommandMap>);};
// Native [5DD22B,5DD2D3) registers two callbacks and reuses one descriptor.
// Screen/member strings establish the AptStats receiver; keep unknown names.
void AptStats::rva005DD22B() {
 DelegateDesc desc;
 {
 AsciiString name("AptStats::InitGadgets");
 desc=MakeStatsDelegate(this,reinterpret_cast<StatsHandler>(&AptStats::rva005DD14D));
 _bfme_setAptScreenRef(name,AptRef<AptScreenInitGadgets>(desc));
 }
 {
 AsciiString name("Stats::OnSelectFaction");
 desc=MakeStatsDelegate(this,reinterpret_cast<StatsHandler>(&AptStats::rva005DD1D0));
 reinterpret_cast<AptCommandMapAdder*>(static_cast<char*>(owner)+4)->AddCommandMap(name,AptRef<AptCommandMap>(desc));
 }
}

class Rva005DE433 {public:void rva005DE433(int**);};
struct Widths {int*begin,*end;};
class GameWindow;
class Rva005DD7C3 {public:void rva005DD7C3(GameWindow*,const Widths*);};
// Native [5DD0EB,5DD14D), complete EH entry and RET4, proves a two-int
// focus vector and refresh of the inherited table. Earlier false-boundary
// verdict used the wrong image address; retail RVA includes the 400000 image base.
void AptStats::rva005DD0EB(int faction) {
 m_word1c=faction;
 // Signed/unsigned corresponding types share the proven32-bit storage;
 // the table reader interprets the same bits as signed faction indices.
 std::vector<unsigned int> focus(2);
 focus[0]=faction;focus[1]=6;
 reinterpret_cast<Rva005DE433*>(this)->rva005DE433(reinterpret_cast<int**>(&focus));
}
// Native [5DD14D,5DD1D0), complete EH entry and RET12, receives the
// StatsList screen callback, sets 50/25/25 widths and restores the focus.
// WB StatsList string lead does not establish a source method name.
void AptStats::rva005DD14D(const char*name,int unused,GameWindow*window) {
 if(strcmp(name,"AptStats::StatsList")==0) {
  std::vector<unsigned int> widths(3);
  widths[0]=50;widths[1]=25;widths[2]=25;
  reinterpret_cast<Rva005DD7C3*>(this)->rva005DD7C3(window,reinterpret_cast<const Widths*>(&widths));
  rva005DD0EB(m_word1c);
 }
}
// Native [5DD1D0,5DD1EA), RET4, is the registered faction-command callback.
void AptStats::rva005DD1D0(const char*text) {rva005DD0EB(atoi(text));}

// Native65B dtor and28B deleting dtor formerly lived under Rva005DD1EA.
// The verified44B constructor and registrations establish AptStats identity.
AptStats::~AptStats() {}
