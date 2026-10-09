// ?update@AIFollowPathAndEvacuateState@@UAE?AW4StateReturnType@@XZ
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// The evacuate AI states' enter/exit overrides. Each class is identified by
// its vtable's slot-2 name getter (the state's own name literal):
//
//   0x00C12D50 "AIMoveToAndEvacuateState" (getter 0x00342E11): slot 4
//     onEnter 0x003500E6 (banked near miss, not here), slot 5 onExit
//     0x0034C098 (28 B), slot 6 update 0x00354AB6 (not here). The same
//     three slots fill 0x00C12DB8 "AIAttackMoveToAndEvacuateState" (getter 0x00342E2F), which therefore
//     overrides none of them.
//   0x00C13108 "AIMoveForBoarding" (getter 0x0034308F): slot 4 onEnter
//     0x00350164 (23 B); slot 5 is the same onExit 0x0034C098.
//   0x00C12E28 "AIFollowPathAndEvacuateState" (getter 0x00342E52): slot 4
//     onEnter 0x0035014D (23 B), slot 5 onExit 0x0034C0B4 (28 B).
//
// Target evidence: the enter overrides call Rva0033FA64Do (0x0033FA64) on the
// machine owner before the base onEnter (the pinned AIMoveToState::onEnter
// 0x0034C7BD, or the rowed AIFollowPathState::onEnter 0x0034DEF8, as a tail
// jump); the exit overrides call the base onExit (the rowed
// AIInternalMoveToState::onExit 0x003473A4 directly, or
// AIFollowPathState::onExit 0x00349D92) and then Rva0033FA79Do (0x0033FA79)
// on the owner, as the matched AIFollowWaypointPathStateAndEvacuate pair
// does. The class derivations are inferred from the shared slots and the
// base calls.
//
// The two update slots, AIMoveToAndEvacuateState 0x00354AB6 (142 B) and
// AIMoveForBoarding 0x00354CAD (96 B), run the pinned AIMoveToState::update
// (0x00353A65) and then succeed once the point of the AI's path (+0x140) at
// the owner's +0xB8 distance (times 0.9 for the evacuate state) fails the
// pathfinder's cell test 0x002E996E; on success the evacuate state also
// hands the owner and machine to the helper 0x003532BF with its slot-18
// Bool. Callees pinned by address.

enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

#include "Coord3D.h"
#include <vector>
#include <list>
struct BfmePod12 { unsigned m_data[3]; };
class Rva0034C0D0: public _STL::vector<BfmePod12> {public: Rva0034C0D0(const Rva0034C0D0 &);};
class Rva0035149F;
enum CommandSourceType {CMD_FROM_AI=2};
enum DisabledType {DISABLED_HELD=3};
class Rva00352F9D {public: virtual void slot0(); void rva00353168(const void *,const Rva0035149F &,CommandSourceType); void rva00353080(const void *,const Rva0035149F &,CommandSourceType);};
class AICommandInterface {public:void aiIdle(CommandSourceType);};

// What the path's 0x003642DF returns by value (16 bytes): a node and a
// position (as in AIUpdateInterfacePrivateCommands.cpp). Unnamed.
struct Rva003642DFNode;
struct Rva003642DFResult
{
	Rva003642DFResult();
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};

class Path
{
public:
	Rva003642DFResult rva003642DF(float dist);
};

class Object;
class Pathfinder
{
public:
 bool getClosestPointOnLand(const Coord3D *,Object *,Coord3D *);
	bool IsBuildRestrictedCell(const Coord3D *pos, bool flagA, bool flagB, int layer);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
};
extern AI *TheAI;

class ObjectRingNode {public:ObjectRingNode *next,*prev;Object *value;};
struct ObjectRing {ObjectRingNode *head;};
struct ContainedObjects {void *context;_STL::list<Object *> *list;};
class ContainModuleInterface {public:
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
};
class AIUpdateInterface
{
public:
 Path *getPath()const{return m_path;}
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
 Rva0034C0D0 &getCommandPath()const{return *(Rva0034C0D0 *)((char *)m_moveMachine+0x3C);}
 char m_pad04[0x20-4]; Rva00352F9D m_command;
 char m_pad24[0x30-0x24]; void *m_moveMachine;
 char m_pad34[0x140-0x34];Path *m_path;
};
struct ObjectTemplateView {char pad00[0x115]; unsigned char kind115;};
class Object
{
public:
 AIUpdateInterface *getAI(){return m_ai;}
 float getBfmeRealB8()const{return m_bfmeRealB8;}
 bool clearDisabled(DisabledType);
 char pad00[4];ObjectTemplateView *m_template;
 char pad08[0x38-8];Coord3D m_position;
 char pad44[0xB8-0x44];float m_bfmeRealB8;
 char padBC[0x250-0xBC];ContainModuleInterface *m_contain;
 char pad254[4];AIUpdateInterface *m_ai;
};

class StateMachine;
void rva003532BF(Object *owner, StateMachine *machine, bool flag);

class Object0033FA64;
void Rva0033FA64Do(const Object0033FA64 *obj);
class Object0033FA79;
void Rva0033FA79Do(const Object0033FA79 *obj);

class StateMachine
{
public:
	Object *getOwner() const { return m_owner; }
private:
	unsigned char m_pad00[0x14];
	Object *m_owner; // +0x14
};

class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17();
	virtual bool rva00354B2ESlot18();
protected:
	StateMachine *getMachine() const { return m_machine; }
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine; // +0x18
};

class AIInternalMoveToState : public State
{
public:
	virtual void onExit(StateExitType status);
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

class AIMoveToAndEvacuateState : public AIMoveToState
{
public:
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

void AIMoveToAndEvacuateState::onExit(StateExitType status)
{
	AIInternalMoveToState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}

StateReturnType AIMoveToAndEvacuateState::update()
{
	StateReturnType status = AIMoveToState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8() * 0.9f);
		if (!TheAI->pathfinder()->IsBuildRestrictedCell(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	if (status == STATE_SUCCESS)
		rva003532BF(owner, getMachine(), rva00354B2ESlot18());
	return status;
}

class AIMoveForBoarding : public AIMoveToAndEvacuateState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};

StateReturnType AIMoveForBoarding::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIMoveToState::onEnter();
}

StateReturnType AIMoveForBoarding::update()
{
	StateReturnType status = AIMoveToState::update();
	Object *owner = getMachineOwner();
	if (owner->getAI()->getPath() != 0)
	{
		Rva003642DFResult end = owner->getAI()->getPath()->rva003642DF(owner->getBfmeRealB8());
		if (!TheAI->pathfinder()->IsBuildRestrictedCell(&end.m_pos, false, false, 1))
			status = STATE_SUCCESS;
	}
	return status;
}

class AIFollowPathState : public AIInternalMoveToState
{
protected: char unknown1C[0x4C-0x1C]; int m_pathIndex;
public:
 virtual StateReturnType update();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

class AIFollowPathAndEvacuateState : public AIFollowPathState
{
public:
 virtual StateReturnType update();
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
};

StateReturnType AIFollowPathAndEvacuateState::onEnter()
{
	Rva0033FA64Do((const Object0033FA64 *)getMachineOwner());
	return AIFollowPathState::onEnter();
}

void AIFollowPathAndEvacuateState::onExit(StateExitType status)
{
	AIFollowPathState::onExit(status);
	Rva0033FA79Do((const Object0033FA79 *)getMachineOwner());
}

StateReturnType AIFollowPathAndEvacuateState::update()
{
 Object *owner=getMachineOwner();
 Coord3D shore;
 const Coord3D *position=&owner->m_position;
 if(TheAI->pathfinder()->getClosestPointOnLand(position,owner,&shore)) {
  Rva0034C0D0 path(owner->getAI()->getCommandPath());
  for(int i=0;i<m_pathIndex;++i)path.erase(path.begin());
  ContainedObjects objects=owner->m_contain->getContainedObjects();
  for(_STL::list<Object *>::const_iterator it=objects.list->begin();it!=objects.list->end();++it) {
   Object *unit=*it;
   unit->getAI()->ignoreObstacle(owner);
   unit->clearDisabled(DISABLED_HELD);
   bool special=(unit->m_template->kind115 & 0x20)!=0;
   AIUpdateInterface *ai=unit->getAI();
   if(special)
    ai->m_command.rva00353168(owner,reinterpret_cast<const Rva0035149F &>(path),owner->getAI()->getSource());
   else
    ai->m_command.rva00353080(owner,reinterpret_cast<const Rva0035149F &>(path),owner->getAI()->getSource());
  }
  AIUpdateInterface *ownerAI=owner->getAI();
  reinterpret_cast<AICommandInterface *>(&ownerAI->m_command)->aiIdle(CMD_FROM_AI);
  return STATE_SUCCESS;
 }
 return AIFollowPathState::update();
}
