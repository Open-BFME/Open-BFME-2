// cl: /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
#include <string.h>
#include "ascii_string.h"
extern "C" void __cdecl free(void *);
// Native vector teardown calls the game-memory wrapper at 0x30830, through
// its existing throwing C++ view. C-linkage CRT free would select the import
// thunk and elide the final unwind-state reset in the registration routine.
void Rva00030830FreeAllocation(void *);
namespace _STL {
template<> inline void allocator<int>::deallocate(int *p,size_t) const {
 if(p) Rva00030830FreeAllocation(p);
}
}
// AptTimeLineStats::SetPlayerFocus is named by WB 0x155C540, AptTimeLineStats.cpp
// asserts 537/543/547. Retail 0x5BE2D2..0x5BE344 proves offsets and RET 4.
// The callback receiver remains address-named: WB 0x15D6B30 is unnamed;
// its retail 0x5DE433..0x5DE47B body refills a listbox and restores scrolling.
// No applicable clean BFME1 timeline source is present at donor 9cbfb551fe20.

class GameWindow;
int GadgetListBoxGetTopVisibleEntry(GameWindow *);
void GadgetListBoxReset(GameWindow *);
void GadgetListBoxSetTopVisibleEntry(GameWindow *,int);
class Rva005DDBAB;
struct Rva005DE059Out {int first,second;};
// WB's inline loop retains a (listbox, focus-array address) context. Retail
// pushes its two words by value before end, begin and the result address.
// The existing C provider models these same eight argument bytes as int a,b;
// its first argument receives the two-word returned context, unused here.
struct TimelineFocusArgs
{
    GameWindow *window;
    int **focus;
    TimelineFocusArgs(GameWindow *w, int **f) : window(w), focus(f) {}
};
typedef char TimelineFocusArgsIsEightBytes[sizeof(TimelineFocusArgs)==8 ? 1 : -1];
extern "C" void __cdecl rva005DE059(Rva005DE059Out *,Rva005DDBAB *,Rva005DDBAB *,TimelineFocusArgs);
class Rva005DE433 {
public:
 void rva005DE433(int **);
 void *pad0;
 Rva005DDBAB *begin,*end;
 void *wordC;
 GameWindow *window;
};
// ?rva005DE433@Rva005DE433@@QAEXPAPAH@Z
void Rva005DE433::rva005DE433(int **focus) {
 if(window) {
  int top=GadgetListBoxGetTopVisibleEntry(window);
  GadgetListBoxReset(window);
  Rva005DE059Out result;
  rva005DE059(&result,begin,end,TimelineFocusArgs(window,focus));
  GadgetListBoxSetTopVisibleEntry(window,top);
 }
}
struct Widths {int *begin,*end;};
class Rva005DD7C3 {public:void rva005DD7C3(GameWindow*,const Widths*);};
class LivingWorldPlayer;
class Player;
class AptTimeLineStats {
public:
 Rva005DE433 *receiver;
 int *focusSlots;
 char pad8[8];
 int numPlayers;
 bool flag14;
 void SetPlayerFocus(const char *);
 void InitGadgets(const char*,int,GameWindow*);
 void rva005BF177();
 void CollectPlayerData(int,LivingWorldPlayer*);
 void CollectPlayerData(int,Player*);
};
void AptTimeLineStats::SetPlayerFocus(const char *text) {
 if(numPlayers<1)return;
 int focus=atoi(text);
 int minFocus=!flag14;
 if(focus<minFocus)focus=minFocus;
 if(focus>numPlayers)focus=numPlayers-2;
 if(!flag14)focusSlots[0]=0;
 for(int i=minFocus;i<3;++i) {
  if(focus<numPlayers)focusSlots[i]=focus++;
  else focusSlots[i]=-1;
 }
 Rva005DE433 *notify=receiver;
 if(notify)notify->rva005DE433(&focusSlots);
}

// WB 0x155C390 names AptTimeLineStats::InitGadgets (assert line 509).
// Retail initializes two 50% columns for one player, otherwise four 25% columns.
// The listbox provider's Widths view is the vector's verified first two words.
void AptTimeLineStats::InitGadgets(const char *name,int unused,GameWindow *window) {
 if(strcmp(name,"AptTimeLine::StatsList")==0 && receiver) {
  if(numPlayers==1) {
   _STL::vector<int> widths(2,50);
   reinterpret_cast<Rva005DD7C3*>(receiver)->rva005DD7C3(window,reinterpret_cast<const Widths*>(&widths));
  } else {
   _STL::vector<int> widths(4,25);
   reinterpret_cast<Rva005DD7C3*>(receiver)->rva005DD7C3(window,reinterpret_cast<const Widths*>(&widths));
  }
  receiver->rva005DE433(&focusSlots);
 }
}

// These non-virtual, single-inheritance member pointers occupy one word in
// VC7.1. The typed callback is erased only when packed for the existing wrapper.
typedef void (AptTimeLineStats::*TimelineHandler)();
typedef char TimelineHandlerIsOneWord[sizeof(TimelineHandler)==4 ? 1 : -1];
struct DelegateDesc {
 AptTimeLineStats *object;
 TimelineHandler method;
 DelegateDesc(AptTimeLineStats *o,TimelineHandler m):object(o),method(m){}
};
struct TargetRef00217D4C {void *vtable;int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva00579E47 {
public:
 Rva00579E47(const DelegateDesc &);
 TargetRef00217D4C *ptr;
};
template<class T>class AptRef:public Rva00579E47 {
public:
 AptRef(DelegateDesc d):Rva00579E47(d){}
 AptRef(const AptRef &other):Rva00579E47(other){if(ptr)++ptr->references;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
class AptScreenInitGadgets;
class AptCommandMap;
void _bfme_setAptScreenRef(const AsciiString &,AptRef<AptScreenInitGadgets>);
class AptPlayer {public:void AddCommandMap(const AsciiString &,AptRef<AptCommandMap>);};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
// Native 0x5BF177..0x5BF257 binds this sub-screen's two verified callbacks.
// WB 0x155A5F0 has the same bindings and empty-width setup but its name says
// AptTimeLine::InitGadgets; preserve the uncertain member name as an RVA.
// The eight-byte delegate is (object, four-byte erased member pointer);
// the rowed wrapper constructor and receiving registration helpers own it.
void AptTimeLineStats::rva005BF177() {
 {
  AsciiString name("AptTimeLine::InitGadgets");
  _bfme_setAptScreenRef(name,AptRef<AptScreenInitGadgets>(DelegateDesc(this,reinterpret_cast<TimelineHandler>(&AptTimeLineStats::InitGadgets))));
 }
 {
  AsciiString name("AptTimeLine::SetPlayerFocus");
  reinterpret_cast<AptPlayer*>(g_bfmeAptWindowManager)->AddCommandMap(name,AptRef<AptCommandMap>(DelegateDesc(this,reinterpret_cast<TimelineHandler>(&AptTimeLineStats::SetPlayerFocus))));
 }
 if(receiver) {
  _STL::vector<int> widths;
  reinterpret_cast<Rva005DD7C3*>(receiver)->rva005DD7C3(0,reinterpret_cast<const Widths*>(&widths));
 }
}

#include "unicode_string.h"
struct BfmeStringRecord005DDD40 {UnicodeString text; float word;};
// Consuming views of the existing eight-byte display constructors. Their
// first word is the owned UnicodeString; all table calls read the same bits.
class Rva005DD822:public BfmeStringRecord005DDD40 {public:Rva005DD822(unsigned);};
class Rva005DDED5:public BfmeStringRecord005DDD40 {public:Rva005DDED5(unsigned);};
class Rva005DD8E0:public BfmeStringRecord005DDD40 {public:Rva005DD8E0(float,float);};
class Rva005DDE01 {public:void rva005DDE01(unsigned,unsigned,const BfmeStringRecord005DDD40&,bool);};
class GameStats {public:class Row;class StrategicEndGame;class RealTimeEndGame;};
class Rva005DE9E3 {
public:Rva005DE9E3(unsigned);virtual~Rva005DE9E3();
protected:GameStats::Row *rows,*finish,*capacity;int extra;
};
class GameStats::StrategicEndGame:public Rva005DE9E3 {public:StrategicEndGame(int);};
class LivingWorldScoreKeeper {
public:
 unsigned rva004EE037();int rva004EE016();int rva004EE043();
 int GetBuildingsOfTypeBuilt(int);int rva004EE33B();
 int valueA8()const{return words[0xA8/4];}
 int valueAC()const{return words[0xAC/4];}
 int valueD8()const{return words[0xD8/4];}
 int valueDC()const{return words[0xDC/4];}
 int words[0xF4/4];
};
class LivingWorldPlayer {public:char beforeScore[0x2C8];LivingWorldScoreKeeper score;};
template<int N>class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
// The full44B constructor only clears 28 bytes and sets one bit. Native
// static initialization has no unwind state at this call: it cannot throw.
struct Rva00045411BitSet {unsigned words[7];Rva00045411BitSet(int,int) throw();};
class Rva004EE35D {public:int rva004EE35D(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3AB {public:int rva004EE3AB(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE3F9 {public:int rva004EE3F9(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva004EE447 {public:int rva004EE447();};
class Rva004EE485 {public:int rva005BE20B();};
class Rva004EE4C3 {public:int rva004EE4C3();};
// WB155C340 is an unnamed31B count helper whose body is expanded in retail
// before the deaths call. Keep its integer result until the float arguments
// are prepared; a compound caller expression chooses different evaluation.
__forceinline int countStrategicKills(LivingWorldScoreKeeper *score) {
 int directKills=score->words[0xB0/4];
 return reinterpret_cast<Rva004EE4C3*>(score)->rva004EE4C3()+directKills;
}
// WB155B550 names CollectPlayerData (Stats.cpp326..480). Native body1564
// is followed by its own27-entry switch table108; the complete1672B extent
// ends at the independently verified vector helper5BE9D1. Each stat uses
// its own verified scalar/display constructor and the full AddStat provider.
void AptTimeLineStats::CollectPlayerData(int playerIndex,LivingWorldPlayer *player) {
 if(!player)return;
 if(!receiver)receiver=reinterpret_cast<Rva005DE433*>(new GameStats::StrategicEndGame(8));
 LivingWorldScoreKeeper *score=&player->score;
 ++numPlayers;
 static const Rva00045411BitSet structures(0,7);
 const Rva00045411BitSet&structureKinds=structures;
 for(int stat=0;stat<27;++stat) {
  switch(stat) {
  case 0: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(0,playerIndex,Rva005DDED5(score->rva004EE037()),true);break;
  case 1: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(1,playerIndex,Rva005DDED5(score->rva004EE016()),true);break;
  case 2: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(2,playerIndex,Rva005DD822(score->rva004EE043()+1),true);break;
  case 3: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(3,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE35D*>(score)->rva004EE35D(structureKinds,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE))),true);break;
  case 4: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(4,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE3AB*>(score)->rva004EE3AB(structureKinds,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE))),true);break;
  case 5: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(5,playerIndex,Rva005DD822(score->words[0x94/4]),true);break;
  case 6: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(6,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE3F9*>(score)->rva004EE3F9(structureKinds,reinterpret_cast<const Rva00045411BitSet&>(KINDOFMASK_NONE))),true);break;
  case 7: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(7,playerIndex,Rva005DD822(score->words[0x98/4]),true);break;
  case 8: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(8,playerIndex,Rva005DD822(score->GetBuildingsOfTypeBuilt(1)),true);break;
  case 9: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(9,playerIndex,Rva005DD822(score->GetBuildingsOfTypeBuilt(3)),true);break;
  case 10: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(10,playerIndex,Rva005DD822(score->GetBuildingsOfTypeBuilt(2)),true);break;
  case 11: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(11,playerIndex,Rva005DD822(score->GetBuildingsOfTypeBuilt(4)),true);break;
  case 12: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(12,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE447*>(score)->rva004EE447()+score->rva004EE33B()),true);break;
  case 13: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(13,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE485*>(score)->rva005BE20B()),true);break;
  case 14: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(14,playerIndex,Rva005DD8E0(float(countStrategicKills(score)),float(reinterpret_cast<Rva004EE485*>(score)->rva005BE20B())),true);break;
  case 15: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(15,playerIndex,Rva005DD822(score->valueA8()+score->valueAC()),true);break;
  case 16: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(16,playerIndex,Rva005DD822(reinterpret_cast<Rva004EE4C3*>(score)->rva004EE4C3()),true);break;
  case 17: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(17,playerIndex,Rva005DD822(score->words[0xB0/4]),true);break;
  case 18: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(18,playerIndex,Rva005DD822(score->words[0xD8/4]),true);break;
  case 19: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(19,playerIndex,Rva005DD822(score->words[0xDC/4]),true);break;
  case 20: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(20,playerIndex,Rva005DD8E0(float(score->valueD8()),float(score->valueDC())),true);break;
  case 21: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(21,playerIndex,Rva005DD822(score->words[0xE0/4]),true);break;
  case 22: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(22,playerIndex,Rva005DD822(score->words[0xE4/4]),true);break;
  case 23: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(23,playerIndex,Rva005DD822(score->words[0xE8/4]),true);break;
  case 24: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(24,playerIndex,Rva005DD822(score->words[0xEC/4]),true);break;
  case 25: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(25,playerIndex,Rva005DD822((reinterpret_cast<int*>(score->words[0x38/4])-reinterpret_cast<int*>(score->words[0x34/4]))),true);break;
  case 26: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(26,playerIndex,Rva005DD822(score->words[0xF0/4]),true);break;
  }
 }
}

class GameStats::RealTimeEndGame:public Rva005DE9E3 {public:RealTimeEndGame(int);};
// Native accesses establish this consuming ScoreKeeper view: integer fields
// through0x1C, units70/74, buildingsC8/CC, and a pointer vector at328.
// WB155A800 confirms their statistics; its Player score offset3C8 differs
// from retail3BC. The inline integer accessors preserve the getter lifetime
// before conversion without asserting original names for those getters.
class ScoreKeeper {
public:
 int getTotalUnitsDestroyed();int getTotalBuildingsDestroyed();
 int value4()const{return words[4/4];}
 int value8()const{return words[8/4];}
 int value14()const{return words[20/4];}
 int value18()const{return words[24/4];}
 int value1C()const{return words[28/4];}
 int value70()const{return words[112/4];}
 int value74()const{return words[116/4];}
 int words[0x328/4];_STL::vector<int> fortresses;
};
class Player {public:char beforeScore[0x3BC];ScoreKeeper score;};
class Rva0039B709 {public:unsigned rva0039B6EE();unsigned rva0039B709();int rva0039B9D1();};
// Existing seven-word kind-mask initializer2618FA supplies the favorite-unit
// filter. The full39BDB8 selection worker and23B39BE95 wrapper are verified.
class Rva002618A2 {public:unsigned words[7];Rva002618A2*rva002618FA(int,int,int,int,int,int);};
class Rva0039BDB8 {public:void rva0039BE95(const BitFlags<69>*,UnicodeString*);};
class Rva0039BF0B {public:int rva0039BF0B(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva0039BF39 {public:int rva0039BF39(const Rva00045411BitSet&,const Rva00045411BitSet&);};
class Rva005DD772:public BfmeStringRecord005DDD40 {public:Rva005DD772(const UnicodeString&,float);};
// VC7.1 reverses the two overload slots: AsciiString fetch is38, char fetch3C.
// Retail calls3C with GUI:None and a hidden four-byte UnicodeString result.
class GameTextInterface {
public:
 virtual ~GameTextInterface(){}
 virtual void slot00()=0;virtual void slot01()=0;virtual void slot02()=0;virtual void slot03()=0;
 virtual void slot04()=0;virtual void slot05()=0;virtual void slot06()=0;virtual void slot07()=0;
 virtual void slot08()=0;virtual void slot09()=0;virtual void slot10()=0;virtual void slot11()=0;
 virtual void slot12()=0;virtual UnicodeString fetch(const char*,bool * =0)=0;
 virtual UnicodeString fetch(const AsciiString&,bool * =0)=0;
};
extern GameTextInterface*TheGameText;
// WB155A800 names this RTS CollectPlayerData overload (asserts106..292).
// Native5BEA70..5BF02C is1468 code bytes; its24-entry96B switch table follows
// and ends at the independently rowed vector constructor5BF08C. Verify the
// whole1564B extent, every case target, display temporary and unwind state.
// Cases17/21 have no implementation in either native body.
void AptTimeLineStats::CollectPlayerData(int playerIndex,Player*player) {
 if(!player)return;
 if(!receiver)receiver=reinterpret_cast<Rva005DE433*>(new GameStats::RealTimeEndGame(8));
 ScoreKeeper *score=&player->score;
 if(!score)return;
 ++numPlayers;
 for(int stat=0;stat<24;++stat) switch(stat) {
  case 0: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(0,playerIndex,Rva005DDED5(reinterpret_cast<Rva0039B709*>(score)->rva0039B6EE()),true);break;
  case 1: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(1,playerIndex,Rva005DD822(score->words[0xC8/4]),true);break;
  case 2: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(2,playerIndex,Rva005DD822(score->words[0xCC/4]),true);break;
  case 3: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(3,playerIndex,Rva005DD822(score->getTotalBuildingsDestroyed()),true);break;
  case 4: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(4,playerIndex,Rva005DD822(score->fortresses.size()),true);break;
  case 5: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(5,playerIndex,Rva005DD822(score->words[0x70/4]),true);break;
  case 6: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(6,playerIndex,Rva005DD822(score->words[0x74/4]),true);break;
  case 7: {
   float killed=float(score->getTotalUnitsDestroyed());float lost=float(score->value74());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(7,playerIndex,Rva005DD8E0(killed,lost),true);break;
  }
  case 8: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(8,playerIndex,Rva005DD822(score->getTotalUnitsDestroyed()),true);break;
  case 9: {
   UnicodeString favorite=TheGameText->fetch("GUI:None");
   Rva002618A2 kinds;
   reinterpret_cast<Rva0039BDB8*>(score)->rva0039BE95(reinterpret_cast<const BitFlags<69>*>(kinds.rva002618FA(0,109,90,10,11,191)),&favorite);
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(9,playerIndex,Rva005DD772(favorite,0.0f),true);break;
  }
  case 10: {
   float gathered=float(score->value4());float minutes=float(reinterpret_cast<Rva0039B709*>(score)->rva0039B9D1());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(10,playerIndex,Rva005DD8E0(gathered,minutes),true);break;
  }
  case 11: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(11,playerIndex,Rva005DD822(score->words[4/4]),true);break;
  case 12: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(12,playerIndex,Rva005DD822(score->words[16/4]),true);break;
  case 13: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(13,playerIndex,Rva005DD822(score->words[12/4]),true);break;
  case 14: {
   float spent=float(score->value18());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(14,playerIndex,Rva005DD822(unsigned(spent)),true);break;
  }
  case 15: {
   float spent=float(score->value14());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(15,playerIndex,Rva005DD822(unsigned(spent)),true);break;
  }
  case 16: {
   float spent=float(score->value1C());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(16,playerIndex,Rva005DD822(unsigned(spent)),true);break;
  }
  case 18: {
   float spent=float(score->value8());float kills=float(score->getTotalUnitsDestroyed());
   kills+=float(score->getTotalBuildingsDestroyed());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(18,playerIndex,Rva005DD8E0(kills*100.0f,spent),true);break;
  }
  case 19: {
   float lost=float(score->value74());float created=float(score->value70());
   reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(19,playerIndex,Rva005DD8E0(created,lost),true);break;
  }
  case 20: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(20,playerIndex,Rva005DDED5(reinterpret_cast<Rva0039B709*>(score)->rva0039B709()),true);break;
  case 22: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(22,playerIndex,Rva005DD822(reinterpret_cast<Rva0039BF0B*>(score)->rva0039BF0B(reinterpret_cast<const Rva00045411BitSet&>(Rva00045411BitSet(0,90)),reinterpret_cast<const Rva00045411BitSet&>(Rva00045411BitSet(0,179)))),true);break;
  case 23: reinterpret_cast<Rva005DDE01*>(receiver)->rva005DDE01(23,playerIndex,Rva005DD822(reinterpret_cast<Rva0039BF39*>(score)->rva0039BF39(reinterpret_cast<const Rva00045411BitSet&>(Rva00045411BitSet(0,90)),reinterpret_cast<const Rva00045411BitSet&>(Rva00045411BitSet(0,179)))),true);break;
 }
}
