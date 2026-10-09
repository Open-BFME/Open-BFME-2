// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@HitReactionBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004592A1,
// 681 bytes: slot 0 of the UpdateModuleInterface vftable 0x00840FF8 whose
// xfer and pool-key slots are the rowed HitReactionBehavior ones (0x00459173,
// 0x004591A5), so the body runs with `this` on the interface at +0x10
// (object at this-8, module data at this-0xC, m_20/m_24 at this+0x10/+0x14).
// WorldBuilder twin 0x01176E00 (callgraph; its inlined BitFlags asserts name
// Object::clearModelConditionState / setModelConditionState).
// While a reaction runs (+0x20 frames left) it is kept only as long as the
// AI's slot-110 query holds; otherwise the drawable's reaction conditions
// (model conditions 172..175) are cleared.  A health drop since the last
// update (+0x24) picks a level from the module data's three thresholds
// (+0x14..+0x1C), restarts the timer from its LifeTimer (+0x08..+0x10), sets
// condition 172 plus the level's, pokes the 0x0028BD3A interface and, with
// HitsParalyze (+0x21), disables the object (type 4) until the timer ends.
// Module data names follow HitReactionBehaviorModuleDataCtor.cpp.

#include "../../../Common/GameLogicObjectLookupView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum DisabledType
{
	DISABLED_PARALYZED = 4
};

enum
{
	MODELCONDITION_HIT_REACTION = 172,
	MODELCONDITION_HIT_LEVEL1 = 173,
	MODELCONDITION_HIT_LEVEL2 = 174,
	MODELCONDITION_HIT_LEVEL3 = 175
};

template <int N> class Rva004592A1Slots : public Rva004592A1Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004592A1Slots<0>
{
};

// AIUpdateInterface: slot 110 (+0x1B8) is a bool query.
class AIUpdateInterface : public Rva004592A1Slots<110>
{
public:
	virtual bool rva004592A1Slot110() = 0;
};

// Body module: slot 4 (+0x10) returns the current health.
class BodyModuleInterface : public Rva004592A1Slots<4>
{
public:
	virtual float getHealth() = 0;
};

// Interface returned by 0x0028BD3A: slot 2 takes one argument.
class Rva0028BD3AInterface : public Rva004592A1Slots<2>
{
public:
	virtual void rva004592A1Slot2(int value) = 0;
};

class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class Drawable
{
public:
	void rva00274176(bool immediate);	// 0x00274176
	__forceinline bool testModelCondition(unsigned int bit) const
	{
		return (m_conditionWords[bit >> 5] & (1U << (bit & 0x1f))) != 0;
	}
private:
	char m_pad000[0x258];
	unsigned int m_conditionWords[19];	// +0x258
};

class Object
{
public:
	Drawable *getDrawable() const;	// 0x005508E2
	void rva0028AE6D();	// model-condition change notifier
	void *rva0028BD3A() const;
	void setDisabledUntil(DisabledType type, unsigned int frame);	// 0x00290114

	BodyModuleInterface *getBodyModule() { return m_body; }
	AIUpdateInterface *getAI() { return m_ai; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags;	// +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body;	// +0x254
	AIUpdateInterface *m_ai;	// +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;	// +0x438
};

extern GameLogic *TheGameLogic;

class ModuleData;

class HitReactionBehaviorModuleData
{
public:
	const void *m_vtable;	// +0x00
	unsigned int m_unused04;	// +0x04
	int m_lifeTimer[3];	// +0x08
	float m_threshold[3];	// +0x14
	bool m_fastHitsReset;	// +0x20
	bool m_hitsParalyze;	// +0x21
};

class Rva004592A1Module
{
public:
	virtual void rva004592A1Module0();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
};

class Rva004592A1Interface0C
{
public:
	virtual void rva004592A1Interface0C0();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public Rva004592A1Module, public Rva004592A1Interface0C, public UpdateModuleInterface
{
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }
	unsigned char m_pad14[0x20 - 0x14];
};

class HitReactionBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	__forceinline void clearHitReaction(Object *obj, Drawable *draw)
	{
		if (draw->testModelCondition(MODELCONDITION_HIT_REACTION))
		{
			obj->clearModelConditionState(MODELCONDITION_HIT_REACTION);
			obj->clearModelConditionState(MODELCONDITION_HIT_LEVEL1);
			obj->clearModelConditionState(MODELCONDITION_HIT_LEVEL2);
			obj->clearModelConditionState(MODELCONDITION_HIT_LEVEL3);
			draw->rva00274176(false);
		}
	}

	int m_framesLeft;	// +0x20
	float m_lastHealth;	// +0x24
};

UpdateSleepTime HitReactionBehavior::update()
{
	Object *obj = getObject();
	AIUpdateInterface *ai = obj->getAI();
	BodyModuleInterface *body = obj->getBodyModule();
	Drawable *draw = obj->getDrawable();
	const HitReactionBehaviorModuleData *data = (const HitReactionBehaviorModuleData *)getModuleData();
	if (ai && draw && body)
	{
		float health = body->getHealth();
		bool reacting = m_framesLeft > 0;
		if (reacting)
		{
			--m_framesLeft;
			if (m_framesLeft <= 0 || obj->isEffectivelyDead() || !ai->rva004592A1Slot110())
			{
				clearHitReaction(obj, draw);
				m_framesLeft = 0;
			}
		}

		if ((!reacting || data->m_fastHitsReset) && (ai->rva004592A1Slot110() || data->m_hitsParalyze) && m_lastHealth > health)
		{
			clearHitReaction(obj, draw);
			float damage = m_lastHealth - health;
			int level = -1;
			if (damage >= data->m_threshold[2])
				level = 2;
			else if (damage >= data->m_threshold[1])
				level = 1;
			else if (damage >= data->m_threshold[0])
				level = 0;
			if (level != -1)
			{
				m_framesLeft = data->m_lifeTimer[level];
				if (m_framesLeft > 0 && !draw->testModelCondition(MODELCONDITION_HIT_REACTION))
				{
					obj->setModelConditionState(MODELCONDITION_HIT_REACTION);
					switch (level)
					{
					case 0:
						obj->setModelConditionState(MODELCONDITION_HIT_LEVEL1);
						break;
					case 1:
						obj->setModelConditionState(MODELCONDITION_HIT_LEVEL2);
						break;
					case 2:
						obj->setModelConditionState(MODELCONDITION_HIT_LEVEL3);
						break;
					}
					Rva0028BD3AInterface *iface = (Rva0028BD3AInterface *)obj->rva0028BD3A();
					if (iface)
						iface->rva004592A1Slot2(0);
					if (data->m_hitsParalyze)
						obj->setDisabledUntil(DISABLED_PARALYZED, TheGameLogic->getFrame() + m_framesLeft);
					draw->rva00274176(false);
				}
			}
		}

		m_lastHealth = health;
		if (!obj->isEffectivelyDead())
			return UPDATE_SLEEP_NONE;
	}
	return UPDATE_SLEEP_FOREVER;
}
