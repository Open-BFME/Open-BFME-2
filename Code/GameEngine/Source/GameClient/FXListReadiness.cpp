// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Semantic guide: BFME1 f98983a7d FXList_bfmeIsBlocked.cpp. The target
// retains its time-window eviction and probabilistic culling, with frame40,
// GameMemory free, the target source literal/line and native list append.
// Original method spelling is unproven; retain its existing linker name.
namespace _STL { void free(void *); template <class T> class allocator; template <class T, class A> class list; }
struct Rva002923DFElement;
// LINK: 0x002923DF is rowed as the STLport list size; the frame-history list is
// that list, so the count is read through the rowed name.
namespace _STL { template <class T, class A> class list { public: unsigned size() const; }; }
int GetGameClientRandomValue(int,int,char *,int);
class GameLogic;
extern GameLogic *TheGameLogic;
struct FxPlayTimeNode {FxPlayTimeNode *next,*previous;unsigned frame;};
class IntFrameList {public:FxPlayTimeNode *head;};
#include "../../Include/GameClient/Rva0005548FNativeList.h"
class FXList {
public:bool rva001E2EF1()const;
private:
 char unknown00[0x14];unsigned tracking14;
 mutable IntFrameList times18;
 unsigned startCull1C,allCull20;
};
bool FXList::rva001E2EF1()const {
 if(!tracking14)return false;
 unsigned frame=*(unsigned *)((char *)TheGameLogic+0x40);
 IntFrameList *times=&times18;
 FxPlayTimeNode *node=times->head->next;
 while(node!=times->head){
  if(node->frame>=frame-tracking14)break;
  FxPlayTimeNode *next=node->next,*previous=node->previous;
  previous->next=next;
  next->previous=previous;
  _STL::free(node);
  node=next;
 }
 unsigned count=((const _STL::list<Rva002923DFElement, _STL::allocator<Rva002923DFElement> > *)times)->size();
 unsigned start=startCull1C;
 if(count>start)return true;
 if(count>allCull20){
  unsigned chance=(count-allCull20)/(start-allCull20);
  if(!GetGameClientRandomValue(0,(int)chance,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\FXList.cpp",0x882))return true;
 }
 ((Rva0005548FNativeList *)times)->append(*(void *const *)&frame);
 return false;
}
