// stlport
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/open-bfme-1/inputs/reference/shims/objectdlink
// ZH Player.cpp ungarrisonAllUnits semantics. Native [2AF037,2AF0C5)
// fixes Player prototype-list32C, prototype Team head334, Object AI258,
// ThingTemplate structure bit108:80, and AI commands base20.
// Team member-pointer dispatch has a function and zero this-adjustment;
// the neutral empty bases express that observed eight-byte ABI only.
// Idle/resume is ZH Player::setUnitsShouldIdleOrResume, confirmed by WB C1A140
// and target214B. Structure test108:80; position38; AI virtual110/95 and
// supply-truck virtual11. The referenced Coord3D uses the canonical header.
// Object iterator ABI is inherited from the verified263864/263526 providers.
// Donor revision 575ba2b04; target direct calls independently verify semantics.
#include <list>
#include <cstring>
#include "ObjectDlinkPmf.h"
#include "Lib/Coord3D.h"
enum CommandSourceType {CMD_FROM_PLAYER,CMD_FROM_SCRIPT,CMD_FROM_AI};
template<int N>class BitFlags {public:unsigned bits[7];BitFlags(){std::memset(bits,0,sizeof(bits));}};
typedef int Int;
class AISecond
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void s8();
	virtual void s9();
	virtual void s10();
	virtual void s11(Int v);
};

class AIClass
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual AISecond *v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual bool v110();
};

class FlagObj
{
public:
	char m_pad[0x108];
	unsigned char m_flag;
};

class PlayerIdleObject
{
public:
	void *m_vptr;
	FlagObj *m_04;
	char m_08[0x30];
	Coord3D m_38;
	char m_44[0x258 - 0x44];
	AIClass *m_258;
};


class Thing {public:bool isAnyKindOf(const BitFlags<69>&) const;};
class AICommandInterface {public:void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiHunt(CommandSourceType);void aiIdle(CommandSourceType);void aiEvacuate(bool,CommandSourceType);};
struct Rva2AE9B8AI {char pad[32];AICommandInterface commands;};
struct Rva2AE9B8Template {char pad[0x108];unsigned kinds;};
struct Rva2AE9B8Object {void*vt;Rva2AE9B8Template*type;char pad[0x258-8];Rva2AE9B8AI*ai;};
template<class T>class DLINK_ITERATOR {public:typedef T*(T::*GetNextFunc)()const;DLINK_ITERATOR(T*cur,GetNextFunc next):m_cur(cur),m_getNext(next){};T*cur()const{return m_cur;}bool done()const{return m_cur==0;}void advance();private:T*m_cur;GetNextFunc m_getNext;};
class Rva2AE9B8TeamBase1 {}; class Rva2AE9B8TeamBase2 {};
class Team : public Rva2AE9B8TeamBase1,public Rva2AE9B8TeamBase2 {public:Team*dlink_next_TeamInstanceList()const;DLINK_ITERATOR<Object> iterate_TeamMemberList()const;};
template<>__forceinline void DLINK_ITERATOR<Team>::advance(){if(m_cur)m_cur=(m_cur->*m_getNext)();}
struct Rva2AE9B8Prototype {char pad[0x334];Team*head;};
class Player {public:void ungarrisonAllUnits(CommandSourceType);void setUnitsShouldIdleOrResume(bool);private:char pad[0x32c];_STL::list<Rva2AE9B8Prototype*>prototypes;char gap[0x33d-0x330];bool hunt;};
void Player::ungarrisonAllUnits(CommandSourceType source){
 for(_STL::list<Rva2AE9B8Prototype*>::iterator it=prototypes.begin();it!=prototypes.end();++it){
  for(DLINK_ITERATOR<Team> iter=DLINK_ITERATOR<Team>((*it)->head,&Team::dlink_next_TeamInstanceList);!iter.done();iter.advance()){
   Team*team=iter.cur();if(!team)continue;
   for(DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();!objects.done();objects.advance()){
    Object*obj=objects.cur();if(!obj)continue;
    Rva2AE9B8Object*view=reinterpret_cast<Rva2AE9B8Object*>(obj);Rva2AE9B8AI*ai=view->ai;
    if(!ai)continue;if(view->type->kinds&0x80)ai->commands.aiEvacuate(false,source);
   }
  }
 }
}

void Player::setUnitsShouldIdleOrResume(bool idle) {
 for(_STL::list<Rva2AE9B8Prototype*>::iterator it=prototypes.begin();it!=prototypes.end();++it){
  for(DLINK_ITERATOR<Team> iter=DLINK_ITERATOR<Team>((*it)->head,&Team::dlink_next_TeamInstanceList);!iter.done();iter.advance()){
   Team*team=iter.cur();if(!team)continue;
   for(DLINK_ITERATOR<Object> objects=team->iterate_TeamMemberList();!objects.done();objects.advance()){
    Object*obj=objects.cur();if(!obj)continue;
    PlayerIdleObject*view=reinterpret_cast<PlayerIdleObject*>(obj);
    if(view->m_04->m_flag&0x80)continue;
    AIClass*ai=view->m_258;if(!ai)continue;
    if(idle) reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(ai)+0x20)->aiMoveToPosition(&view->m_38,CMD_FROM_SCRIPT);
    else if(ai->v110()){AISecond*supply=ai->v95();if(supply)supply->s11(1);}
   }
  }
 }
}
