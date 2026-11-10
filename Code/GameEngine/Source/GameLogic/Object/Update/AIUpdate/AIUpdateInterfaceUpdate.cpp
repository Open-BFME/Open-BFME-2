// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /ICode/Libraries/Include/Lib /DNDEBUG /MD /GX
//
// ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0026E267, 850 bytes.
// AIUpdateInterface::update, slot 0 of the UpdateModuleInterface table (this
// is the +0x10 subobject); WanderAIUpdate::update 0x004A9424 and the other
// derived updates call it directly with that this. Target evidence:
// - the object's status 0x48 brackets the whole body (set after the
//   TheAiOrdersManager refresh, cleared on every exit through an EH-tracked
//   local);
// - a stored command at +0x2EC (Rva00351570, empty when its type is -1) is
//   rebuilt into a fresh AICommandParms(AICMD_NO_COMMAND, CMD_FROM_AI) through
//   0x0035164E and handed to aiDoCommand (slot 0 of the +0x20
//   AICommandInterface table) unless +0x140's 0x001E3591 check (with +0x1FC
//   set), the object's +0x1C9 bit 0 or status 0x4A holds it back;
// - the state machine's slot 12, the +0x1FC mode (2/3/4), KindOf 0x25/0x3D/
//   0x1BA and status 0x26 pick between the WorldBuilder-named
//   quickHordeUpdate 0x0026C4EB and the rowed main update body 0x0026A05D;
// - KindOf 0x1BA keeps +0x3CE, module data +0x54 runs 0x00265173, the rowed
//   handleEngagedFlag clamps the sleep;
// - for an object (or its +0x274 owner) with template KindOf 110 whose AI
//   module data +0x50 is set: no victim -> inside twice the geometry's
//   bounding radius by 0x00265514's planar estimate; victim -> 0x0029493F
//   or distance 0x00263763 beyond module data +0x4C squared; model
//   condition 310 then follows and vslot 142 gets +0x50 or 0;
// - ScriptTracker update at +0x3D0, then the team ID at +0x240 is joined
//   (0x00298C76) and cleared.
// Names past the rowed callees are structural, not recovered.
#define COORD3D_INLINE_NOTHROW_ESTIMATE
// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "Coord3DInline.h"
#include "GameLogic/BfmeStoredAICommandView.h"

enum AICommandType { AICMD_NO_COMMAND = -1 };
enum CommandSourceType { CMD_FROM_AI = 2 };
struct AICommandParms : public Rva00351570Src
{
	AICommandParms(AICommandType, CommandSourceType);
	~AICommandParms() { if (m_20.m_start) free(m_20.m_start); }
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum KindOfType
{
	KINDOF_INVALID = -1
};

class BitWords
{
public:
	bool test(unsigned int bit) const
	{
		return (m_words[bit >> 5] >> (bit & 0x1f)) & 1;
	}
	unsigned int testRaw(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
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
	__forceinline unsigned int isKindOf(unsigned int bit) const { return ((const unsigned char *)&m_kindOf)[bit >> 3] & (1 << (bit & 7)); }
};

#include "../../../../../Include/GameLogic/Module/UpdateModule.h"
#include "../../../../../Include/Common/Geometry.h"

class Team;
class AIUpdateInterface;

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, bool set);
	bool isKindOf(KindOfType t) const;
	bool rva0029493F(Object *victim, int how);
	float rva00263763(const void *other) const;
	// Retail's EH table registers no unwind state for the geometry copy live
	// across this call and the planar estimate: both are known not to throw.
	Coord3D rva00265514(const Object *other) const throw();
	void rva0028AE6D();
	void defect(Team *team, unsigned int flags);

	const AIUpdateThingTemplateView *getTemplate() const { return m_template; }
	int getID() const { return m_id; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AIUpdateInterface *getAI() const { return m_ai; }
	bool testModelConditionState(unsigned int mc) const { return m_modelConditionFlags.test(mc); }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.testRaw(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.testRaw(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	char m_pad00[4];
	const AIUpdateThingTemplateView *m_template;
	char m_pad08[0x74 - 0x08];
	int m_id;
	char m_pad78[0xA8 - 0x78];
	GeometryInfo m_geometryInfo;
	char m_pad104[0x10C - 0x104];
	BitWords m_modelConditionFlags;
	char m_pad158[0x1C9 - 0x158];
	unsigned char m_1C9;
	char m_pad1CA[0x258 - 0x1CA];
	AIUpdateInterface *m_ai;
	char m_pad25C[0x274 - 0x25C];
	Object *m_274;
};

// Sets the object's status on entry and clears it on every exit.
class ObjectStatusScope
{
public:
	__forceinline ObjectStatusScope(Object *obj, ObjectStatusTypes status) : m_obj(obj), m_status(status)
	{
		m_obj->setStatus(m_status, true);
	}
	__forceinline ~ObjectStatusScope()
	{
		m_obj->setStatus(m_status, false);
	}
private:
	Object *m_obj;
	ObjectStatusTypes m_status;
};

#include "../../../../../Include/GameLogic/AiOrdersManager.h"
extern AiOrdersManager *TheAiOrdersManager;

#include "../../../../../Include/Common/TeamFactory.h"
extern TeamFactory *TheTeamFactory;

#include "../../../../../Include/Common/Rva001E3591.h"
class Rva00265173
{
public:
	void rva00265173();
};

class ScriptTracker
{
public:
	void update();
private:
	char m_pad[0x10];
};

class AIStateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual bool slot12();
};

struct AIUpdateModuleData
{
	char m_pad00[0x4C];
	float m_4C;
	int m_50;
	bool m_54;
};

template <int N> class AIUpdateVSlots : public AIUpdateVSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateVSlots<0>
{
};

class AIUpdatePrimary : public AIUpdateVSlots<142>
{
public:
	virtual void slot142(int value);
protected:
	const AIUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	char m_pad0C[0x10 - 0x0C];
};


class UpdateModuleView : public AIUpdatePrimary, public UpdateModuleInterface
{
protected:
	char m_pad14[0x20 - 0x14];
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
};

class AIUpdateInterface : public UpdateModuleView, public AICommandInterface
{
public:
	virtual UpdateSleepTime update();

	UpdateSleepTime rva0026A05D();
	UpdateSleepTime quickHordeUpdate();
	int handleEngagedFlag();
	Object *getCurrentVictim() const;

	__forceinline void setSlot142(int value) { slot142(value); }

	Object *getObject() const { return m_object; }
	const AIUpdateModuleData *getAIUpdateModuleData() const { return m_moduleData; }
	AIStateMachine *getStateMachine() const { return m_stateMachine; }

private:
	char m_pad24[0x30 - 0x24];
	AIStateMachine *m_stateMachine;
	char m_pad34[0x140 - 0x34];
	Rva001E3591 *m_140;
	char m_pad144[0x1FC - 0x144];
	int m_1FC;
	char m_pad200[0x240 - 0x200];
	unsigned int m_teamID;
	char m_pad244[0x2EC - 0x244];
	Rva00351570 m_pendingCommand;
	char m_pad3B0[0x3CE - 0x3B0];
	bool m_3CE;
	char m_pad3CF[0x3D0 - 0x3CF];
	ScriptTracker m_scriptTracker;
};

UpdateSleepTime AIUpdateInterface::update()
{
	Object *obj = getObject();
	TheAiOrdersManager->rva003551D3(obj->getID());
	ObjectStatusScope inUpdate(obj, (ObjectStatusTypes)0x48);

	if (m_pendingCommand.m_00 != -1)
	{
		if (!(m_140 && m_1FC != 0 && m_140->rva001E3591()) &&
			!(obj->m_1C9 & 1) &&
			!obj->testStatus((ObjectStatusTypes)0x4A))
		{
			AICommandParms parms(AICMD_NO_COMMAND, CMD_FROM_AI);
			m_pendingCommand.reconstitute(parms);
			m_pendingCommand.m_00 = -1;
			aiDoCommand(&parms);
		}
	}

	TheAiOrdersManager->rva003551D3(obj->getID());

	bool quick = getStateMachine()->slot12();
	if (!quick)
	{
		if (m_1FC == 2 || m_1FC == 3 || m_1FC == 4)
			quick = true;
	}
	bool lone = obj->isKindOf((KindOfType)0x25) && !obj->isKindOf((KindOfType)0x3D);
	if (obj->isKindOf((KindOfType)0x1BA) && !lone)
	{
		m_3CE = true;
		quick = false;
	}

	UpdateSleepTime sleep;
	if (obj->testStatus((ObjectStatusTypes)0x26) && quick && !m_3CE &&
		!(obj->getTemplate()->isKindOf(14) && m_1FC == 3))
		sleep = quickHordeUpdate();
	else
		sleep = rva0026A05D();

	if (!obj->isKindOf((KindOfType)0x1BA))
		m_3CE = false;
	if (getAIUpdateModuleData()->m_54)
		((Rva00265173 *)this)->rva00265173();
	UpdateSleepTime engaged = (UpdateSleepTime)handleEngagedFlag();
	if (engaged < sleep)
		sleep = engaged;

	Object *source = obj->getTemplate()->isKindOf(110) ? getObject() : obj->m_274;
	if (source && source->getTemplate()->isKindOf(110))
	{
		AIUpdateInterface *ai = source->getAI();
		if (ai->getAIUpdateModuleData()->m_50 != 0)
		{
			Object *victim = ai->getCurrentVictim();
			bool inRange;
			if (victim == 0)
			{
				GeometryInfo geom(source->getGeometryInfo());
				Coord3D offset = source->rva00265514(getObject());
				float dist = offset.GetLengthEstimate2D();
				inRange = geom.getBoundingCircleRadius() * 2.0f > dist;
			}
			else if (source->rva0029493F(victim, 2))
			{
				float distSqr = source->rva00263763(victim);
				float range = getAIUpdateModuleData()->m_4C;
				range *= range;
				inRange = distSqr > range;
			}
			else
				inRange = true;
			if (inRange)
			{
				getObject()->setModelConditionState(310);
				setSlot142(ai->getAIUpdateModuleData()->m_50);
			}
			else
			{
				getObject()->clearModelConditionState(310);
				setSlot142(0);
			}
		}
	}
	else if (getObject()->testModelConditionState(310))
	{
		getObject()->clearModelConditionState(310);
		setSlot142(0);
	}

	m_scriptTracker.update();
	if (m_teamID != 0)
	{
		Team *team = TheTeamFactory->findTeamByID(m_teamID);
		if (team)
			getObject()->defect(team, 0);
		m_teamID = 0;
	}
	return sleep;
}
