// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /ICode/GameEngine/Include/GameLogic
// ?privateRepair@HordeWorkerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z
// stlport
//
// ?privateRepair@HordeWorkerAIUpdate@@MAEXPAVObject@@W4CommandSourceType@@@Z,
// retail 0x0049AFFC..0x0049B0BF (195 bytes, EH, RET 8): HordeWorkerAIUpdate's
// override of AIUpdateInterface::privateRepair -- the slot WorkerAIUpdate's
// tables fill with the rowed DozerAIUpdate::privateRepair (0x004A9BDE), as in
// Zero Hour's WorkerAIUpdate. Only when TheActionManager allows the repair
// (rowed canRepairObject) is the horde's contain (rowed Object 0x0028C197)
// asked for its member list (slot 0x108 view, rowed list-return helper
// 0x0036AE51); every member whose template carries the 0x40 flag at +0x109 is
// passed to the contain's slot 0xA8 and told to repair the target through its
// AI's command interface (rowed 0x0036F19B, command source 2), and the target's
// +0x74 ID is remembered at +0x3EC.

#include <list>
#include "ContainmentListView.h"

typedef ContainmentList IntList;

namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
}

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};

class Object;

class ActionManager
{
public:
	bool canRepairObject(const Object *obj, const Object *objectToRepair, CommandSourceType cmdSource);
};

extern ActionManager *TheActionManager;

class AICommandInterface
{
public:
	void rva0036F19B(Object *obj, CommandSourceType cmdSource);
};

class Rva0049AFFCUpdateModule
{
public:
	virtual ~Rva0049AFFCUpdateModule();
	char m_pad04[0x20 - 0x04];
};

class AIUpdateInterface : public Rva0049AFFCUpdateModule, public AICommandInterface
{
};

struct Rva0049AFFCTemplate
{
	unsigned char m_pad000[0x109];
	unsigned char m_flags109;
};

class Rva0049AFFCContain;

class Object
{
public:
	Rva0049AFFCContain *getContain() const { return (Rva0049AFFCContain *)rva0028C197(); }
	void *rva0028C197() const;

	char m_pad00[0x04];
	Rva0049AFFCTemplate *m_template04;		// +0x04
	char m_pad08[0x74 - 0x08];
	int m_id74;								// +0x74
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_ai258;				// +0x258
};

class Rva0049AFFCContain
{
public:
#define V(n) virtual void s##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41)
	virtual void slotA8(Object *member);	// slot 42
	V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65)
#undef V
	virtual Rva0036AE51ListView slot108();	// slot 66
};

class HordeWorkerAIUpdate
{
protected:
	virtual void privateRepair(Object *obj, CommandSourceType cmdSource);
	Object *getObject() const { return m_object; }

private:
	char m_pad04[0x08 - 0x04];
	Object *m_object;						// +0x08
	char m_pad0C[0x3EC - 0x0C];
	int m_repairTarget3EC;					// +0x3EC
};

void HordeWorkerAIUpdate::privateRepair(Object *obj, CommandSourceType cmdSource)
{
	Object *me = getObject();
	if (!TheActionManager->canRepairObject(me, obj, cmdSource))
		return;
	Rva0049AFFCContain *contain = me->getContain();
	if (!contain)
		return;
	IntList members = contain->slot108().rva0036AE51();
	for (IntList::iterator it = members.begin(); it != members.end(); ++it)
	{
		Object *member = (Object *)containmentFirstWord(*it);
		if ((member->m_template04->m_flags109?member->m_template04->m_flags109:member->m_template04->m_flags109) & 0x40)
		{
			contain->slotA8(member);
			(member->m_ai258?member->m_ai258:member->m_ai258)->rva0036F19B(obj, CMD_FROM_AI);
			m_repairTarget3EC = obj->m_id74;
		}
	}
}
