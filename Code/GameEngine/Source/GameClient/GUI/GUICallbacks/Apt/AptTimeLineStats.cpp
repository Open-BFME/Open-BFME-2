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
