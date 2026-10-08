// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// AptTimeLineStats::SetPlayerFocus is named by WB 0x155C540, AptTimeLineStats.cpp
// asserts 537/543/547. Retail 0x5BE2D2..0x5BE344 proves offsets and RET 4.
// The callback receiver remains address-named: WB 0x15D6B30 is unnamed;
// its retail 0x5DE433..0x5DE47B body refills a listbox and restores scrolling.
// No applicable clean BFME1 timeline source is present at donor 9cbfb551fe20.
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
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
class AptTimeLineStats {
public:
 Rva005DE433 *receiver;
 int *focusSlots;
 char pad8[8];
 int numPlayers;
 bool flag14;
 void SetPlayerFocus(const char *);
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
