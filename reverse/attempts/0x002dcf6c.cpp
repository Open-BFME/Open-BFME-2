// ?rva002DCF6C@GameState@@QAEXPAVSnapshot@@I@Z
// partial score=0.983367198838897 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/moduledata /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /G7  /arch:SSE /DNDEBUG /MD /EHsc
// stlport
#include <list>
#include <string.h>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
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
 while(it!=m_post.end()) {
  Snapshot *snapshot=*it;
  ++it;
  snapshot->loadPostProcess();
 }
 m_post.clear();m_marks.clear();
}
void GameState::rva002DC4B8(void*,unsigned sequence)
{
 _STL::list<GameStatePostRecord>::iterator it=m_marks.begin();
 while(it!=m_marks.end()) {
  GameStatePostRecord &record=*it;
  if(record.sequence>=sequence) {
   it=m_marks.erase(it);
   for(_STL::list<Snapshot*>::iterator p=m_post.begin();p!=m_post.end();++p) {
    if(*p==record.snapshot) {m_post.erase(p);break;}
   }
  } else ++it;
 }
}
void GameState::rva002DCF6C(Snapshot *snapshot,unsigned sequence)
{
 if(!snapshot)return;
 const char *name=snapshot->GetSnapshotName();
 Snapshot *postCopy=snapshot;
 if(name && !strcmp(name,"Object"))m_post.push_front(postCopy);
 else {
  if(name && !strcmp(name,"Weapon"))return;
  m_post.push_back(postCopy);
 }
 GameStatePostRecord record;
 record.snapshot=snapshot;record.sequence=sequence;
 m_marks.push_back(record);
}
void Rva002DD908(Snapshot *snapshot,GameState *state,unsigned sequence)
{state->rva002DCF6C(snapshot,sequence);}
void Rva002DC66F(void *unused,GameState *state,unsigned sequence)
{state->rva002DC4B8(unused,sequence);}
