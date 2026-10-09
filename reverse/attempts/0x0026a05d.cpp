// ?rva0026A05D@AIUpdateInterface@@QAE?AW4UpdateSleepTime@@XZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
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
#include "Coord3D.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum ObjectID
{
	INVALID_ID = 0
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

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned int getFrame() const { return m_frame; }
	char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	bool queueForPath(ObjectID id);
};
class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
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
class AIStateMachine
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual int updateStateMachine();
	virtual void clear();
	virtual void slot06();
	virtual void slot07();
	virtual int setState(int id);
	void rva0035033F();
	int getCurrentStateID() const
	{
		if (m_currentState)
			return m_currentState->m_id;
		return 999999;
	}
	AIStateView *m_currentState;
	char m_pad08[0x38 - 0x08];
	bool m_locked;
};

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

template <int N> class AIUpdateVSlots : public AIUpdateVSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateVSlots<0>
{
};

class AIUpdateInterface : public AIUpdateVSlots<110>
{
public:
	virtual bool slot110();
	virtual void slot111();
	virtual void slot112();
	virtual bool slot113();
	virtual void slot114(); virtual void slot115(); virtual void slot116();
	virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void slot120(); virtual void slot121(); virtual void slot122();
	virtual void slot123(); virtual void slot124(); virtual void slot125();
	virtual void slot126(); virtual void slot127(); virtual void slot128();
	virtual void slot129(); virtual void slot130(); virtual void slot131();
	virtual void slot132(); virtual void slot133(); virtual void slot134();
	virtual void slot135();
	virtual void setLocomotorGoalNone();
	virtual void slot137(); virtual void slot138(); virtual void slot139();
	virtual void slot140(); virtual void slot141(); virtual void slot142();
	virtual void slot143(); virtual void slot144(); virtual void slot145();
	virtual void slot146(); virtual void slot147(); virtual void slot148();
	virtual int doLocomotor();

	UpdateSleepTime rva0026A05D();
	void destroyPath();
	void ignoreObstacle(const Object *obj);

	Object *getObject() const { return m_object; }
	AIStateMachine *getStateMachine() const { return m_stateMachine; }

	char m_pad04[4];
	Object *m_object;
	char m_pad0C[0x30 - 0x0C];
	AIStateMachine *m_stateMachine;
	void *m_34;
	char m_pad38[0x13C - 0x38];
	void *m_completedWaypoint;
	char m_pad140[0x17C - 0x140];
	unsigned int m_queueForPathFrame;
	Coord3D m_finalPosition;
	char m_pad18C[0x1FC - 0x18C];
	int m_1FC;
	char m_pad200[0x3B0 - 0x200];
	bool m_3B0;
	char m_pad3B1[0x3B6 - 0x3B1];
	bool m_movementComplete;
	char m_pad3B7[0x3BD - 0x3B7];
	bool m_isAiDead;
	char m_pad3BE[0x3C2 - 0x3BE];
	bool m_isInUpdate;
	char m_pad3C3[0x3C8 - 0x3C3];
	bool m_3C8;
	char m_pad3C9[0x3E0 - 0x3C9];
	bool m_3E0;
};

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
			if (getStateMachine()->getCurrentStateID() != 13 &&
				!((BfmeSub932C *)getStateMachine())->bfmeQuery932C()) {
				getStateMachine()->setState(13);
				getObject()->clearModelConditionState(61);
				getObject()->clearModelConditionState(156);
			}
		} else {
			if (getStateMachine()->getCurrentStateID() != 0) {
				destroyPath();
				setLocomotorGoalNone();
			}
			obj->rva0028AD32();
			getObject()->clearModelConditionState(61);
			getObject()->clearModelConditionState(156);
		}
		return UPDATE_SLEEP_NONE;
	}

	if (!slot110())
		m_3C8 = true;
	m_isInUpdate = true;
	m_completedWaypoint = 0;
	int subMachineSleep = UPDATE_SLEEP_FOREVER;
	m_3E0 = m_34 != 0;
	int stRet = getStateMachine()->updateStateMachine();
	m_3E0 = false;
	if (stRet > 0) {
		if (stRet < UPDATE_SLEEP_FOREVER)
			subMachineSleep = stRet;
	} else {
		subMachineSleep = UPDATE_SLEEP_NONE;
	}
	if (slot113())
		return (UpdateSleepTime)subMachineSleep;

	if (m_movementComplete) {
		m_queueForPathFrame = 0;
		destroyPath();
		if (m_1FC != 3)
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
			m_finalPosition = goalPos;
			m_3B0 = false;
			if (!obj->getTemplate()->isKindOf(109))
				obj->rva0028ACEE((int)&goalPos, getObject()->rva0028B511());
		}
		m_movementComplete = false;
		ignoreObstacle(0);
	}

	unsigned int now = TheGameLogic->getFrame();
	if (m_queueForPathFrame != 0) {
		if (now >= m_queueForPathFrame) {
			TheAI->pathfinder()->queueForPath(getObject()->getID());
			m_queueForPathFrame = 0;
		} else {
			unsigned int sleepForPathDelta = m_queueForPathFrame - now;
			if (sleepForPathDelta < (unsigned int)subMachineSleep)
				subMachineSleep = sleepForPathDelta;
		}
	}

	((Rva00265AAB *)this)->rva00265AAB((Object00265AAB *)obj, &subMachineSleep);

	int sleep;
	if (m_isAiDead && getStateMachine()->getCurrentStateID() != 13) {
		getStateMachine()->rva0035033F();
		getStateMachine()->clear();
		getStateMachine()->setState(13);
		getStateMachine()->m_locked = true;
		sleep = UPDATE_SLEEP_NONE;
	} else {
		sleep = subMachineSleep;
	}

	int tmp = doLocomotor();
	if (tmp < sleep)
		sleep = tmp;

	m_isInUpdate = false;
	if (m_completedWaypoint != 0)
		return UPDATE_SLEEP_NONE;
	return (UpdateSleepTime)sleep;
}
