// ?rva0036A5BB@Rva00368004@@QAEHXZ
// partial score=0.91127 date=2026-10-09
// cl: /MD /O1 /Oy- /arch:SSE /G7 /EHs
// ?rva00368004@Rva00368004@@QAE_NXZ @0x00368004 17B
// Null-checked virtual forward: if +0x3C pointer is null return false else
// tail-jmp to its virtual slot 0x48 (19th virtual returning bool).
// Evidence: retail cmp [ecx+0x3C],0 plus xor al,al null path plus mov ecx,[ecx+0x3C]
// plus mov eax,[ecx] plus jmp [eax+0x48]; callers at 0x0036A5A7/0x36A7C7.
// Owner unproven so honest address class names used.
//
// ?rva0036A75C@Rva00368004@@QAEHXZ @0x0036A75C 127B
// Flag-guarded refresh: when +0x40 is set, clear it and tail-jmp virtual
// slot 0x10; with a null +0x3C inner return -1; otherwise resolve the
// +0x18 info record's object id (+0x3C) via TheGameLogic and team id (+0x40)
// via TheTeamFactory, copy the object's +0x38 Coord3D into +0x28 (or fill
// +0x28 from the team centre when the object is null), call the inner
// virtual slot 0x18, then return -1 when rva00368004 succeeds else the slot
// result. Same +0x28/+0x3C/+0x40 trio shape as the AIGuard states (which
// keep IDs there; here +0x3C is the inner pointer).

typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt TeamID;
#define NULL 0

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	Real x, y, z;
};

class Object;
class StateMachine;
class AttackExitConditionsInterface {public:virtual bool shouldExit(const StateMachine*)const=0;};

class StateMachine
{
public:
	Object *getGoalObject();
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Team
{
public:
	void rva0039E5B9(Coord3D *pos);
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;

struct Rva0036A75CInfo
{
	char m_pad[0x14];
 Object *owner;
 char pad18[0x3C-0x18];
	ObjectID m_objectID; // +0x3C
	TeamID m_teamID; // +0x40
 class PolygonTrigger *area;
 Coord3D position;
 Coord3D specialPosition;
 bool special;char padding[7];
 ObjectID nemesis;int mode;int getMode()const{return mode;}const Coord3D*getPosition()const{return &position;}
};

class Rva00368004Inner
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual int slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual bool slot48() = 0;
};
struct GuardExitConditions:AttackExitConditionsInterface {virtual bool shouldExit(const StateMachine*)const;int flags;Coord3D center;float radius;unsigned frame;};
class Rva00368004
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual int slot10() = 0;
	bool rva00368004();
	int rva0036A75C();
	int rva0036A524();
 int rva0036A5BB();
 StateMachine*getMachine()const{return (StateMachine*)m_info;}
 AttackExitConditionsInterface *getConditions(){return (AttackExitConditionsInterface*)((char*)this+0x20);}

private:
	char m_pad04[0x14]; // +0x04..0x18 (vptr at +0x00)
	Rva0036A75CInfo *m_info; // +0x18
	char m_pad1C[4];
 GuardExitConditions m_conditions;

public:
	Rva00368004Inner *m_ptr; // +0x3C
	bool m_flag40; // +0x40
};
bool Rva00368004::rva00368004()
{
	if (!m_ptr)
		return false;
	return m_ptr->slot48();
}
int Rva00368004::rva0036A75C()
{
	if (m_flag40) {
		m_flag40 = false;
		return slot10();
	}
	if (m_ptr == NULL)
		return -1;
	Rva0036A75CInfo *info = m_info;
	Object *obj = TheGameLogic->findObjectByID(info->m_objectID);
	Team *team = TheTeamFactory->findTeamByID(info->m_teamID);
	if (obj != NULL)
		m_conditions.center = *(Coord3D *)((char *)obj + 0x38);
	else if (team != NULL)
		team->rva0039E5B9(&m_conditions.center);
	int inner = m_ptr->slot18();
	if (rva00368004())
		return -1;
	return inner;
}
int Rva00368004::rva0036A524()
{
	if (m_flag40) {
		m_flag40 = false;
		return slot10();
	}
	if (m_ptr == NULL)
		return -1;
	Rva0036A75CInfo *info = m_info;
	Object *obj = TheGameLogic->findObjectByID(info->m_objectID);
	Team *team = TheTeamFactory->findTeamByID(info->m_teamID);
	if (obj != NULL)
		m_conditions.center = *(Coord3D *)((char *)obj + 0x38);
	else if (team != NULL)
		team->rva0039E5B9(&m_conditions.center);
	int inner = m_ptr->slot18();
	StateMachine *sm = *(StateMachine **)((char *)m_ptr + 0x18);
	Object *goal = sm->getGoalObject();
	if (goal != NULL) {
		if ((*(unsigned char *)((char *)goal + 0x438) & 1) == 0)
			return inner;
	}
	if (rva00368004())
		return -1;
	return inner;
}

class PolygonTrigger {public:void getCenterPoint(Coord3D*)const;};
class AttackExitConditionsInterface;
struct AIDataGuard {char pad[0x3c];unsigned chaseFrames;};
class AI {public:static float getAdjustedVisionRangeForObject(const Object*,int);char pad[0x18];AIDataGuard *data; const AIDataGuard *getAiData()const{return data;}};
extern AI *TheAI;
class AIAttackState {public:
 AIAttackState(StateMachine*,bool,bool,bool,AttackExitConditionsInterface*);
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0c();virtual int onEnter();
 char pad04[0x14];StateMachine *machine;char pad1c[0x50-0x1c];
};
class GoalMachineView {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void setGoalObject(const Object*);
};
// Native0036A5BB..0036A75C and ZH AIGuardOuterState::onEnter support purpose.
// Owner spelling retained neutral; offsets and virtual slots follow retail.
int Rva00368004::rva0036A5BB() {
 Rva0036A75CInfo *info=m_info;
 if(info->getMode()==1)return -1;
 Object *target=TheGameLogic->findObjectByID(info->m_objectID);
 Team *team=TheTeamFactory->findTeamByID(info->m_teamID);
 Coord3D pos;
 if(target)pos=*(Coord3D*)((char*)target+0x38);
 else if(team)team->rva0039E5B9(&pos);
 else {unsigned char*container2=*(unsigned char**)((char*)this+0x18);pos=*(Coord3D*)(container2+0x48);}
 info=m_info;
 Object *nemesis=TheGameLogic->findObjectByID(info->nemesis);
 if(!nemesis)return -1;
 Object *owner=info->owner;
 float range=AI::getAdjustedVisionRangeForObject(owner,3);
 info=m_info;
 if(info->area){if(info->special)pos=info->specialPosition;else info->area->getCenterPoint(&pos);}
 m_conditions.center=pos;
 *(float*)((char*)this+0x34)=range*range;
 float chase=8.0f>(float)TheAI->getAiData()->chaseFrames?8.0f:(float)TheAI->getAiData()->chaseFrames;
 *(unsigned*)((char*)this+0x38)= (unsigned)((float)*(unsigned*)((char*)TheGameLogic+0x40)+chase);
 *(unsigned*)((char*)this+0x24)=7;
  StateMachine *machine=getMachine();
 m_ptr=(Rva00368004Inner*)new AIAttackState(machine,false,true,false,&m_conditions);
 ((GoalMachineView*)((AIAttackState*)m_ptr)->machine)->setGoalObject(nemesis);
 int result=((AIAttackState*)m_ptr)->onEnter();
 return result==0?0:-1;
}
