// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/moduledata /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// Native DC52B104 and DC4B8115 manipulate separate four-byte list headers
// at receiver+E0C and+E10. Nodes have next0/prev4 and payload8. The first
// payload is a Snapshot pointer; the second adds an unsigned sequence word.
// Old refusal logs assumed12-byte list headers and called them overlapping.
// Current BFME list shim's4-byte allocator proxy matches both actual headers.
// ZH GameState::addPostProcessSnapshot supplies post-load purpose; BFME2's
// sequence pruning and paired records are target-derived. No complete
// GameState layout or original sequence-field spelling is asserted.
// Canonical Snapshot slot1 and typed list clear/erase implementations are
// retained. Clear folds are independently proven by the existing tool;
// complete32-byte erase specializations match list-int including free30830.
// The prune body retains the native reference lifetime across marked erase.
// CallbackDC66F is a complete18-byte cdecl adapter; target construction in
// dispatcher2DD91A supplies its captured GameState as the second argument.
#include <list>
#include <string.h>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva0004224C { public:Rva0004224C *rva0004224C(); };
class GameStateFPScope {
public:
 GameStateFPScope() {((Rva0004224C*)this)->rva0004224C();}
 ~GameStateFPScope() {if(TheGameLogic)--((LogicFPView*)TheGameLogic)->depth;}
private:struct LogicFPView {char opaque[0x1B4];int depth;};
};
struct GameStatePostRecord {Snapshot *snapshot;unsigned sequence;};
class GameState {
 char opaque[0xE0C];
 _STL::list<Snapshot*> m_post;
 _STL::list<GameStatePostRecord> m_marks;
public:
 void rva002DC52B();
 void rva002DC4B8(void*,unsigned);
 void rva002DCF6C(Snapshot*,unsigned);
};
typedef char HeaderExtent[(sizeof(_STL::list<Snapshot*>)==4)?1:-1];
void GameState::rva002DC52B()
{
 GameStateFPScope guard;
 _STL::list<Snapshot*>::iterator it=m_post.begin();
 while(it._M_node!=m_post.end()._M_node) {
  Snapshot *snapshot=*it;
  ++it;
  snapshot->loadPostProcess();
 }
 m_post.clear();m_marks.clear();
}
void GameState::rva002DC4B8(void*,unsigned sequence)
{
 _STL::list<GameStatePostRecord>::iterator it=m_marks.begin();
 while(it._M_node!=m_marks.end()._M_node) {
  GameStatePostRecord &record=*it;
  if(record.sequence>=sequence) {
   it=m_marks.erase(it);
   for(_STL::list<Snapshot*>::iterator p=m_post.begin();p._M_node!=m_post.end()._M_node;++p) {
    if(*p==record.snapshot) {m_post.erase(p);break;}
   }
  } else ++it;
 }
}
void Rva002DC66F(void *unused,GameState *state,unsigned sequence)
{state->rva002DC4B8(unused,sequence);}
