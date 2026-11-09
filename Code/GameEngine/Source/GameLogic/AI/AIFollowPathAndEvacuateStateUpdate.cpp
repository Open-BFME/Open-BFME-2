// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?update@AIFollowPathAndEvacuateState@@UAE?AW4StateReturnType@@XZ @0x00354B44 295B.
// Slot 6 of the AIFollowPathAndEvacuateState vtable 0x00C12E28 (its slot-2 name
// getter 0x00342E52 returns the state's own literal; enter/exit 0x0035014D and
// 0x0034C0B4 are rowed in AIStatesEvacuate.cpp). Target evidence: once the
// pathfinder finds a point on land beside the owner it copies the owner AI's
// command path (rowed 71B copy), drops the points already walked (m_pathIndex,
// rowed erase), then for every contained unit ignores the transport as an
// obstacle, clears DISABLED_HELD and hands it the path through one of two
// command members chosen by template flag bit 0x20 of +0x115, and finally idles
// the owner's AI; otherwise it runs the base AIFollowPathState::update. The
// semantic spine (evacuate onto land) follows Zero Hour's evacuate states;
// the class views and offsets come from target accesses.
// Codegen: /EHs, not /EHsc - the inlined holder free must be able to throw so
// retail's state -1 store before it is kept; testing the flag bit inline
// (no named bool) keeps retail's test-byte form and its 0x20 frame.
#include "../../../Include/Common/StateMachine.h"
#include "../../../Include/Common/StateMachineClass.h"
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
#include "Coord3D.h"
#include <vector>
#include <list>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

struct BfmePod12 

{
 unsigned m_data[3];
 
}
;
// The single-point erase is called out of line; its body is rowed in
// stlport_pod_vector_malloc_bodies.cpp (0x0034C117).
namespace _STL { template <> BfmePod12 *vector<BfmePod12, allocator<BfmePod12> >::erase(BfmePod12 *); }
// Import-inline: every use of the range destroy is inlined here, and this
// unit's trivial copy is not the body retail keeps under that name.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy(BfmePod12 *first, BfmePod12 *last) { __destroy(first, last, (BfmePod12 *)0); } }
class Rva0034C0D0: public _STL::vector<BfmePod12> 

{
 public: Rva0034C0D0(const Rva0034C0D0 &);
 
}
;
class Rva0035149F;
enum CommandSourceType 

{
 CMD_FROM_AI=2
 
}
;
enum DisabledType 

{
 DISABLED_HELD=3
 
}
;
class Rva00352F9D 

{
 public: virtual void slot0();
 void rva00353168(const void *,const Rva0035149F &,CommandSourceType);
 void rva00353080(const void *,const Rva0035149F &,CommandSourceType);
 
}
;
class AICommandInterface 

{
 public:void aiIdle(CommandSourceType);
 
}
;
// What the path's 0x003642DF returns by value (16 bytes): a node and a
// position (as in AIUpdateInterfacePrivateCommands.cpp). Unnamed.
struct Rva003642DFNode;
#include "../../../Include/GameLogic/Rva003642DFResult.h"
#include "../../../Include/GameLogic/PathfindPath.h"
class Object;
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/AI.h"
extern AI *TheAI;
class ObjectRingNode 

{
 public:ObjectRingNode *next,*prev;
 Object *value;
 
}
;
struct ObjectRing 

{
 ObjectRingNode *head;
 
}
;
struct ContainedObjects 

{
 void *context;
 _STL::list<Object *> *list;
 
}
;
class ContainModuleInterface 

{
 public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual ContainedObjects getContainedObjects();
 
}
;
class AIUpdateInterface

{
 public:
 Path *getPath()const
 
 {
  return m_path;
  
 }
 void ignoreObstacle(const Object *);
 virtual void slot000();
 virtual void slot001();
 virtual void slot002();
 virtual void slot003();
 virtual void slot004();
 virtual void slot005();
 virtual void slot006();
 virtual void slot007();
 virtual void slot008();
 virtual void slot009();
 virtual void slot010();
 virtual void slot011();
 virtual void slot012();
 virtual void slot013();
 virtual void slot014();
 virtual void slot015();
 virtual void slot016();
 virtual void slot017();
 virtual void slot018();
 virtual void slot019();
 virtual void slot020();
 virtual void slot021();
 virtual void slot022();
 virtual void slot023();
 virtual void slot024();
 virtual void slot025();
 virtual void slot026();
 virtual void slot027();
 virtual void slot028();
 virtual void slot029();
 virtual void slot030();
 virtual void slot031();
 virtual void slot032();
 virtual void slot033();
 virtual void slot034();
 virtual void slot035();
 virtual void slot036();
 virtual void slot037();
 virtual void slot038();
 virtual void slot039();
 virtual void slot040();
 virtual void slot041();
 virtual void slot042();
 virtual void slot043();
 virtual void slot044();
 virtual void slot045();
 virtual void slot046();
 virtual void slot047();
 virtual void slot048();
 virtual void slot049();
 virtual void slot050();
 virtual void slot051();
 virtual void slot052();
 virtual void slot053();
 virtual void slot054();
 virtual void slot055();
 virtual void slot056();
 virtual void slot057();
 virtual void slot058();
 virtual void slot059();
 virtual void slot060();
 virtual void slot061();
 virtual void slot062();
 virtual void slot063();
 virtual void slot064();
 virtual void slot065();
 virtual void slot066();
 virtual void slot067();
 virtual void slot068();
 virtual void slot069();
 virtual void slot070();
 virtual void slot071();
 virtual void slot072();
 virtual void slot073();
 virtual void slot074();
 virtual void slot075();
 virtual void slot076();
 virtual void slot077();
 virtual void slot078();
 virtual void slot079();
 virtual void slot080();
 virtual void slot081();
 virtual void slot082();
 virtual void slot083();
 virtual void slot084();
 virtual void slot085();
 virtual void slot086();
 virtual void slot087();
 virtual void slot088();
 virtual void slot089();
 virtual void slot090();
 virtual void slot091();
 virtual void slot092();
 virtual void slot093();
 virtual void slot094();
 virtual void slot095();
 virtual void slot096();
 virtual void slot097();
 virtual void slot098();
 virtual void slot099();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void slot140();
 virtual void slot141();
 virtual void slot142();
 virtual CommandSourceType getSource();
 Rva0034C0D0 &getCommandPath()const
 
 {
  return *(Rva0034C0D0 *)((char *)m_moveMachine+0x3C);
  
 }
 char m_pad04[0x20-4];
 Rva00352F9D m_command;
 char m_pad24[0x30-0x24];
 void *m_moveMachine;
 char m_pad34[0x140-0x34];
 Path *m_path;
 
}
;
struct ObjectTemplateView 

{
 char pad00[0x115];
 unsigned char kind115;
 
}
;
class Object

{
 public:
 AIUpdateInterface *getAI()
 
 {
  return m_ai;
  
 }
 float getBfmeRealB8()const
 
 {
  return m_bfmeRealB8;
  
 }
 bool clearDisabled(DisabledType);
 char pad00[4];
 ObjectTemplateView *m_template;
 char pad08[0x38-8];
 Coord3D m_position;
 char pad44[0xB8-0x44];
 float m_bfmeRealB8;
 char padBC[0x250-0xBC];
 ContainModuleInterface *m_contain;
 char pad254[4];
 AIUpdateInterface *m_ai;
 
}
;
class StateMachine;
void rva003532BF(Object *owner, StateMachine *machine, bool flag);
class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);
class Object0033FA79;
void Rva0033FA79Do(const Object0033FA79 *obj);


class AIMoveToState : public AIInternalMoveToState

{
 public:
 virtual StateReturnType onEnter();
 virtual void onExit(StateExitType status);
 virtual StateReturnType update();
 
}
;
class AIMoveToAndEvacuateState : public AIMoveToState

{
 public:
 virtual void onExit(StateExitType status);
 virtual StateReturnType update();
 
}
;
// AIMoveToAndEvacuateState::onExit is rowed in its home unit; this copy was a duplicate definition.
// AIMoveToAndEvacuateState::update is rowed in its home unit; this copy was a duplicate definition.
class AIMoveForBoarding : public AIMoveToAndEvacuateState

{
 public:
 virtual StateReturnType onEnter();
 virtual StateReturnType update();
 
}
;
// AIMoveForBoarding::onEnter is rowed in its home unit; this copy was a duplicate definition.
// AIMoveForBoarding::update is rowed in its home unit; this copy was a duplicate definition.
class AIFollowPathState : public AIInternalMoveToState

{
 protected:
 int m_pathIndex;
 public:
 virtual StateReturnType update();
 virtual StateReturnType onEnter();
 virtual void onExit(StateExitType status);
 
}
;
class AIFollowPathAndEvacuateState : public AIFollowPathState

{
 public:
 virtual StateReturnType update();
 virtual StateReturnType onEnter();
 virtual void onExit(StateExitType status);
 
}
;
// AIFollowPathAndEvacuateState::onEnter is rowed in its home unit; this copy was a duplicate definition.
// AIFollowPathAndEvacuateState::onExit is rowed in its home unit; this copy was a duplicate definition.
StateReturnType AIFollowPathAndEvacuateState::update()

{
 Object *owner=getMachineOwner();
 Coord3D shore;
 const Coord3D *position=&owner->m_position;
 if(TheAI->pathfinder()->getClosestPointOnLand(position,owner,&shore)) 
 
 {
  Rva0034C0D0 path(owner->getAI()->getCommandPath());
  for(int i=0;i<m_pathIndex;++i)path.erase(path.begin());
  ContainedObjects objects=owner->m_contain->getContainedObjects();
  for(_STL::list<Object *>::const_iterator it=objects.list->begin();it!=objects.list->end();++it) 
  
  {
   Object *unit=*it;
   unit->getAI()->ignoreObstacle(owner);
   unit->clearDisabled(DISABLED_HELD);
   if((unit->m_template->kind115 & 0x20)!=0)
   unit->getAI()->m_command.rva00353168(owner,reinterpret_cast<const Rva0035149F &>(path),owner->getAI()->getSource());
   else
   unit->getAI()->m_command.rva00353080(owner,reinterpret_cast<const Rva0035149F &>(path),owner->getAI()->getSource());
   
  }
  reinterpret_cast<AICommandInterface *>(&owner->getAI()->m_command)->aiIdle(CMD_FROM_AI);
  return STATE_SUCCESS;
  
 }
 return AIFollowPathState::update();
 
}
