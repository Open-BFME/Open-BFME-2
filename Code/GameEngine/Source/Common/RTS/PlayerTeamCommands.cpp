// stlport
// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/moduledata
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
#include "Lib/Coord3D.h"
#include "Common/Snapshot.h"
#include "../PartitionRangeQueryCallView.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
enum CommandSourceType {CMD_FROM_PLAYER,CMD_FROM_SCRIPT,CMD_FROM_AI};
enum CanEnterType {CHECK_CAPACITY,DONT_CHECK_CAPACITY,COMBATDROP_INTO};
typedef bool Bool;
template<int N>class BitFlags {public:unsigned bits[7];BitFlags(){std::memset(bits,0,sizeof(bits));}};
typedef int Int;
class Player;
// Partition filter views (matched Rva004AC7C9FindModuleObject.cpp spelling).
template <int NUMBITS> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;

#include "../../../Include/Common/BfmeFixedStorage0004543D.h"

#include "../../../Include/GameLogic/Module/Rva00045411BitSet.h"

#include "../../../Include/GameLogic/PartitionFilter.h"

class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual Bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

struct BfmeResultA
{
public:
	BfmeResultA();
	BfmeResultA(const BfmeResultA&);
	~BfmeResultA();
	void *m_value; // +0x00
};

class BfmeResultForwardB
{
public:
	BfmeResultA bfmeForwardResultB(int value);
};

extern PartitionManager *ThePartitionManager;

// Query payload: 8-byte hit entries [m_start, m_end), cursor at +0x0C.
struct BfmeWidePayloadCompat
{
	void *m_start;
	void *m_end;
	void *m_capacity;
	void *m_cursor;
};

#include "../../../Include/GameLogic/Module/ContainModule.h"


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
	FlagObj *m_template;
	char m_08[0x30];
	Coord3D m_cachedPos;
	char m_44[0x258 - 0x44];
	AIClass *m_aiUpdateInterface;
};


#include "../Thing/thing.h"
class AICommandInterface {public:void rva0026C347(Object *target, CommandSourceType cmdSource);void aiMoveToPosition(const Coord3D*,CommandSourceType);void aiHunt(CommandSourceType);void aiIdle(CommandSourceType);void aiEvacuate(bool,CommandSourceType);};
struct Rva2AE9B8AI
{
public:
	char m_pad00[0x20];
	AICommandInterface commands; // +0x20
};
struct Rva2AE9B8Template
{
public:
	char m_pad00[0x108];
	unsigned kinds; // +0x108
};
struct Rva2AE9B8Object
{
public:
	void *vt; // +0x00
	Rva2AE9B8Template *type; // +0x04
	char m_pad08[0x250];
	Rva2AE9B8AI *ai; // +0x258
};
class AIUpdateInterface
{
public:
	unsigned char m_pad[0x20];
	AICommandInterface m_command;
};

// BFME2 Object skeleton (reference/open-bfme-1/inputs/reference/shims/objectdlink/ObjectDlinkPmf.h).
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	ContainModuleInterface *getContain() const { return m_contain; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	Player *getControllingPlayer() const;
private:
	unsigned char m_tail[0x250 - 0x70];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[4];
	AIUpdateInterface *m_ai; // +0x258
};

// Zero Hour GameCommon.h DLINK_ITERATOR.
template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

#include "../../../Include/Common/MemoryPoolObject.h"

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_dlinkhead_TeamMemberList, &Object::dlink_next_TeamMemberList);
	}
private:
	unsigned char m_teamPad[0x38 - 8];
	Object *m_dlinkhead_TeamMemberList; // +0x38
};
struct Rva2AE9B8Prototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList);}
	char m_pad00[0x334];
	Team *head; // +0x334
};
class ActionManager;
extern ActionManager *TheActionManager;

class BFMEActionManager
{
public:
	Bool canEnterObject(const Object *obj, const Object *objectToEnter,
		CommandSourceType commandSource, CanEnterType mode, Bool passThrough, Bool *outFlag);
};


class Player {public:void garrisonAllUnits(CommandSourceType source);void ungarrisonAllUnits(CommandSourceType);void setUnitsShouldIdleOrResume(bool);Int getPlayerMask() const { return 1 << m_playerIndex; }private:char pad[0x54];Int m_playerIndex;char pad58[0x32c-0x58];_STL::list<Rva2AE9B8Prototype*>prototypes;char gap[0x33d-0x330];bool hunt;};
void Player::garrisonAllUnits(CommandSourceType source)
{
	BfmeResultA hold = ((BfmeResultForwardB *)ThePartitionManager)->bfmeForwardResultB(
		(int)&Rva0004584D(*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 7),
			*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE));
	BfmeWideResult &iterBuilding = *(BfmeWideResult *)&hold;

	for (_STL::list<Rva2AE9B8Prototype*>::iterator it = prototypes.begin(); it != prototypes.end(); ++it)
	{
		for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;

			for (DLINK_ITERATOR<Object> iterObj = team->iterate_TeamMemberList(); !iterObj.done(); iterObj.advance())
			{
				Object *obj = iterObj.cur();
				if (!obj)
					continue;

				AIUpdateInterface *ai = obj->getAIUpdateInterface();
				if (!ai)
					continue;

				BfmeWidePayloadCompat *hits = (BfmeWidePayloadCompat *)iterBuilding.m_value;
				hits->m_cursor = hits->m_start;
				Object *theBuilding = iterBuilding.next();
				while (theBuilding)
				{
					if (ContainModuleInterface *contain = theBuilding->getContain())
					{
						Int player = contain->getPlayerWhoEntered();
						if (!((player == 0) || (player == obj->getControllingPlayer()->getPlayerMask())))
						{
							theBuilding = iterBuilding.next();
							continue;
						}
					}
					Bool noEntry;
					if (((BFMEActionManager *)TheActionManager)->canEnterObject(obj, theBuilding, source, CHECK_CAPACITY, false, &noEntry) && !noEntry)
						ai->m_command.rva0026C347(theBuilding, source);
					theBuilding = iterBuilding.next();
				}
			}
		}
	}
}

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
    if(view->m_template->m_flag&0x80)continue;
    AIClass*ai=view->m_aiUpdateInterface;if(!ai)continue;
    if(idle) reinterpret_cast<AICommandInterface*>(reinterpret_cast<char*>(ai)+0x20)->aiMoveToPosition(&view->m_cachedPos,CMD_FROM_SCRIPT);
    else if(ai->v110()){AISecond*supply=ai->v95();if(supply)supply->s11(1);}
   }
  }
 }
}
