// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
// ?rva0026A05D@AIUpdateInterface@@QAE?AW4UpdateSleepTime@@XZ retail
// 0x0026A05D..0x0026A3A0 (835B).
// The pinned AIUpdateInterface::update 0x0026E267 calls this body (at
// 0x0026E3E4) or the WorldBuilder-named quickHordeUpdate 0x0026C4EB with the
// same receiver; WorldBuilder 0x00E3EF80 is this body's twin (callgraph and
// the "AIUpdateInterface::update" lock name). The update name itself belongs
// to 0x0026E267 so this keeps an address name. The body follows the Zero Hour
// AIUpdateInterface::update (AIUpdate.cpp): state machine update and sleep
// clamp then the movement-complete goal pop (100.0f is the squared pathfind
// cell size) then the queue-for-path frame then the turret sleep helper then
// the dead-state machine lock then doLocomotor.
// BFME2 deltas (target evidence): a dead object with status 0x47 lets its
// rider (findObjectByID of 0x0028B85B; KindOf 165) go down on the corpse
// first; observer refresh 0x00264069; the Object+0x25C/+0x5C gate (dead ->
// setState 13 unless already 13 or 0x004D7383; alive -> destroyPath and
// vslot 136 when a state is current plus 0x0028AD32) clears model conditions
// 61 and 156 (Object+0x10C words; notifier 0x0028AE6D) and sleeps NONE; the
// +0x3E0 flag brackets the machine update; vslot 113 short-circuits; KindOf
// 109 skips 0x0028ACEE. Dead bit Object+0x438 bit 0 as in Rva00265AAB.
// Spelling levers (structural inference, not target evidence): the machine update is called through an
// explicit slot table loaded before the sleep init (donor Zero Hour/BFME 1 AIChooseTable style), which puts the
// virtual-slot load ahead of the address-taken sleep store as retail does; the redundant re-read of the +0x3E0
// flag folds away but gives its address web the register weight retail has; the flag store precedes the sleep
// init. No fence or volatile is needed.
#include "Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};


class BitWords
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

struct AIUpdateThingTemplateView
{
	char m_pad00[0x108];
	BitWords m_kindOf;
	__forceinline unsigned int isKindOf(unsigned int bit) const { return m_kindOf.test(bit); }
};

struct AIUpdateObjectGate
{
	char m_pad00[0x5C];
	bool m_5C;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	ObjectID rva0028B85B() const;
	void goDownOnCorpse(Object *corpse);
	void rva0028AD32();
	void rva0028AE6D();
	bool GetGoalPosition(Coord3D *pos) const;
	int rva0028B511() const;
	void rva0028ACEE(int pos, int layer);

	const AIUpdateThingTemplateView *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	ObjectID getID() const { return m_id; }
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	char m_pad00[4];
	const AIUpdateThingTemplateView *m_template;
	char m_pad08[0x38 - 0x08];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x10C - 0x78];
	BitWords m_modelConditionFlags;
	char m_pad158[0x25C - 0x158];
	AIUpdateObjectGate *m_25C;
	char m_pad260[0x438 - 0x260];
	unsigned char m_438;
};


extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/AIPathfind.h"
#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;

int Rva002EDE5B(void *object, Coord3D *pos);

class BfmeSub932C
{
public:
	unsigned char bfmeQuery932C();
};

struct AIStateView
{
	char m_pad00[4];
	int m_id;
};
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

struct AIStateMachineTable { void *m_slots[4]; int (AIStateMachine::*updateStateMachine)(); };
class Rva00264069ObserverPrefix
{
public:
	void refresh();
};
struct Object00265AAB;
class Rva00265AAB
{
public:
	void rva00265AAB(Object00265AAB *object, int *sleep);
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

UpdateSleepTime AIUpdateInterface::rva0026A05D()
{
	Object *obj = getObject();
	if (obj->isEffectivelyDead() && obj->testStatus((ObjectStatusTypes)0x47)) {
		Object *rider = TheGameLogic->findObjectByID(obj->rva0028B85B());
		if (rider && rider->getTemplate()->isKindOf(165)) {
			rider->goDownOnCorpse(obj);
			obj->setStatus((ObjectStatusTypes)0x47, false);
		}
	}
	((Rva00264069ObserverPrefix *)this)->refresh();
	if (obj->m_25C && obj->m_25C->m_5C) {
		if (obj->isEffectivelyDead()) {
			if (m_stateMachine->getCurrentStateID() == 13 || ((BfmeSub932C *)m_stateMachine)->bfmeQuery932C())
				return UPDATE_SLEEP_NONE;
			m_stateMachine->setState(13);
			getObject()->clearModelConditionState(61);
			getObject()->clearModelConditionState(156);
			return UPDATE_SLEEP_NONE;
		} else {
			if (m_stateMachine->getCurrentStateID() != 0) {
				destroyPath();
				setLocomotorGoalNone();
			}
			obj->rva0028AD32();
			getObject()->clearModelConditionState(61);
			getObject()->clearModelConditionState(156);
			return UPDATE_SLEEP_NONE;
		}
	}

	if (!isIdle())
		m_field3C8 = true;
	m_field3C2 = true;
	m_completedWaypoint = 0;
	bool f34 = m_nextEnemyScanTime != 0;
	m_field3E0 = f34;
	if (m_field3E0 != f34) m_field3E0 = f34;
	AIStateMachine *sm = m_stateMachine;
	AIStateMachineTable *tab = *(AIStateMachineTable **)sm;
	int subMachineSleep = UPDATE_SLEEP_FOREVER;
	int stRet = (sm->*tab->updateStateMachine)();
	m_field3E0 = false;
	if (stRet > 0) {
		if (stRet < UPDATE_SLEEP_FOREVER)
			subMachineSleep = stRet;
	} else {
		subMachineSleep = UPDATE_SLEEP_NONE;
	}
	if (rva00262DA3())
		return (UpdateSleepTime)subMachineSleep;

	if (m_field3B6) {
		m_field17C = 0;
		destroyPath();
		if (m_field1FC != 3)
			setLocomotorGoalNone();
		getObject()->clearModelConditionState(61);
		getObject()->clearModelConditionState(156);
		Coord3D goalPos;
		if (getObject()->GetGoalPosition(&goalPos)) {
			float dx = goalPos.x - getObject()->getPosition()->x;
			float dy = goalPos.y - getObject()->getPosition()->y;
			if (dx * dx + dy * dy >= 100.0f) {
				goalPos = *getObject()->getPosition();
				Rva002EDE5B(getObject(), &goalPos);
			}
			m_field180 = goalPos;
			m_field3B0 = false;
			if (!obj->getTemplate()->isKindOf(109))
				obj->rva0028ACEE((int)&goalPos, getObject()->rva0028B511());
		}
		m_field3B6 = false;
		ignoreObstacle(0);
	}

	unsigned int now = TheGameLogic->getFrame();
	if (m_field17C != 0) {
		if (now >= m_field17C) {
			TheAI->pathfinder()->queueForPath(getObject()->getID());
			m_field17C = 0;
		} else {
			unsigned int sleepForPathDelta = m_field17C - now;
			if (sleepForPathDelta < (unsigned int)subMachineSleep)
				subMachineSleep = sleepForPathDelta;
		}
	}

	((Rva00265AAB *)this)->rva00265AAB((Object00265AAB *)obj, &subMachineSleep);

	int sleep;
	if (m_field3BD && m_stateMachine->getCurrentStateID() != 13) {
		m_stateMachine->rva0035033F();
		m_stateMachine->clear();
		m_stateMachine->setState(13);
		m_stateMachine->m_locked = true;
		sleep = UPDATE_SLEEP_NONE;
	} else {
		sleep = subMachineSleep;
	}

	int locomotorSleep = doLocomotor();
	if (locomotorSleep < sleep)
		sleep = locomotorSleep;

	m_field3C2 = false;
	if (!(m_completedWaypoint == 0)) {
		return UPDATE_SLEEP_NONE;
	} else {
		return (UpdateSleepTime)sleep;
	}
}
