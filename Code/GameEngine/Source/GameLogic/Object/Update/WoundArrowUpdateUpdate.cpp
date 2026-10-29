// cl: /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004C6A20,
// 347 bytes (WB 0x01266AA0 debug twin). The UpdateModuleInterface slot,
// compiled with the +0x10 subobject this. Before the wound is armed (+0x88)
// it runs slot 17 (triggerAbilityEffect) and sleeps one frame; it also waits
// while the owner's AI (Object+0x258) is not idle (AI slot 110). Then it
// disarms, looks the +0x40 target up through GameLogic::findObjectByID and,
// for a target with an AI, moves that AI (locomotor set 4, slot 142) to the
// point the module data's +0xC8 distance beyond the target along the
// owner->target direction (CMD_FROM_AI) and raises the target's model
// condition bit 77. The owner then releases its weapon lock 2, drops model
// condition bit 207 and the SpecialAbilityUpdate exit helper 0x004502CE runs.
//
// The length is written ((float)sqrt(...)), the shape a ((float)sqrt(x))
// macro expands to. Each parenthesized floating-point expression is a paren
// node in c2's IL; the two around the sqrt result are what let the scheduler
// issue the data and target x loads ahead of the fstp of the length, as
// retail does. Without them, "float length = sqrt(...)" stores the length
// first (traced in c2 3077 with SchSelectInstrs picks, 2026-10-20).
#include <math.h>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "Coord3D.h"

class WoundArrowConditionBits
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void set(int bit) { m_words[bit >> 5] |= 1U << (bit & 0x1f); }
	void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
private:
	unsigned int m_words[19];
};

enum CommandSourceType { CMD_FROM_AI = 2 };
enum WeaponLockType { LOCKED_TEMPORARILY = 2 };
enum LocomotorSetType { LOCOMOTORSET_WOUNDED = 4 };

class AIUpdateInterface;

class Object
{
public:
	void rva0028AE6D();
	void releaseWeaponLock(WeaponLockType type);

	unsigned char m_pad000[0x38];
	Coord3D m_pos;	// +0x38
	unsigned char m_pad044[0x10C - 0x44];
	WoundArrowConditionBits m_conditionBits;	// +0x10C
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai;	// +0x258
};

#define WAU_SLOTS10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterfaceHead
{
public:
	WAU_SLOTS10(s0) WAU_SLOTS10(s1) WAU_SLOTS10(s2) WAU_SLOTS10(s3) WAU_SLOTS10(s4)
	WAU_SLOTS10(s5) WAU_SLOTS10(s6) WAU_SLOTS10(s7) WAU_SLOTS10(s8) WAU_SLOTS10(s9)
	WAU_SLOTS10(s10)
	virtual bool isIdle() const;	// slot 110
	WAU_SLOTS10(s11) WAU_SLOTS10(s12) WAU_SLOTS10(s13)
	virtual void s141();
	virtual bool chooseLocomotorSet(LocomotorSetType set);	// slot 142
private:
	unsigned char m_pad04[0x20 - 4];
};

class AIUpdateInterface : public AIUpdateInterfaceHead, public AICommandInterface
{
};

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };

struct WoundArrowUpdateModuleData
{
	unsigned char m_pad000[0xC8];
	float m_distance;	// +0xC8
};

class SpecialAbilityUpdate
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12();
protected:
	virtual void onExit(bool a, bool b);	// slot 13 (+0x34), 0x004502CE
public:
	virtual void s14(); virtual void s15();
	virtual void s16();
	virtual void triggerAbilityEffect();	// slot 17
private:
	friend class WoundArrowUpdate;
protected:
	const WoundArrowUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
	int m_0C;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class WoundArrowUpdate : public SpecialAbilityUpdate, public UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned char m_pad14[0x40 - 0x14];
	ObjectID m_targetID;	// +0x40
	unsigned char m_pad44[0x88 - 0x44];
	bool m_woundArmed;	// +0x88
};

UpdateSleepTime WoundArrowUpdate::update()
{
	if (!m_woundArmed)
	{
		triggerAbilityEffect();
	}
	else
	{
		if (m_object->m_ai->isIdle())
		{
			Object *owner = m_object;
			m_woundArmed = false;
			Object *target = TheGameLogic->findObjectByID(m_targetID);
			if (target)
			{
				AIUpdateInterface *ai = target->m_ai;
				if (ai)
				{
				Coord3D dir;
				dir.x = target->m_pos.x - owner->m_pos.x;
				dir.y = target->m_pos.y - owner->m_pos.y;
				const WoundArrowUpdateModuleData *data = m_moduleData;
				float length = ((float)sqrt((double)(dir.y * dir.y + dir.x * dir.x)));
				float nx = dir.x / length;
				float ny = dir.y / length;
				float ox = nx * data->m_distance, oy = ny * data->m_distance;
				dir.y = oy;
				dir.x = ox;
				dir.x += target->m_pos.x;
				dir.y += target->m_pos.y;
				ai->chooseLocomotorSet(LOCOMOTORSET_WOUNDED);
				ai->aiMoveToPosition(&dir, CMD_FROM_AI);
				setModelConditionBit(target, 77);
				}
				else
					return UPDATE_SLEEP_FOREVER;
			}
			owner->releaseWeaponLock(LOCKED_TEMPORARILY);
			clearModelConditionBit(owner, 207);
			SpecialAbilityUpdate::onExit(false, false);
			return UPDATE_SLEEP_FOREVER;
		}
	}
	return UPDATE_SLEEP_NONE;
}
