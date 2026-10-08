// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// Object::friend_bindToDrawable, retail 0x0029080C..0x0029091E (274 bytes,
// RET 4). Zero Hour's Object.cpp body, also BFME 1's
// ObjectFriendBindToDrawable.cpp: the drawable is stored, and when there is
// one, every weapon-set bit maps through TheWeaponSetTypeToModelConditionTypeMap
// into a "set" or "clear" model-condition mask, the global time of day and
// weather force NIGHT/SNOW, and both masks are applied; every behavior module
// is then told (slot 6). WorldBuilder's debug twin 0x00CD2580 has the same
// flow (its asserts come from BitFlags.h).
//
// BFME 2 deltas the bytes show: 104 weapon-set bits at Object +0x370 (Zero
// Hour: 29 in one word), a 76-byte model-condition mask cleared by memset,
// the masks applied through the rowed Object::rva0028CFB2(clear, set) rather
// than on the drawable, and an extra notify through TheGameLogic +0x178
// (rowed 0x0043846D) before the behavior loop. The out-of-line
// set(bit, value) is the existing WeaponTemplateSetHead spelling of
// 0x000B3FA5; GlobalData offsets are retail's.

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);

#include "../../Common/GameLogicObjectLookupView.h"

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1,
	MODELCONDITION_NIGHT = 7,
	MODELCONDITION_SNOW = 8
};

// The 76-byte (BitFlags<591, ModelConditionFlagType>) model-condition mask.
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead() { memset(m_bits, 0, sizeof(m_bits)); }
	void set(ModelConditionFlagType bit) { m_bits[(unsigned int)bit >> 5] |= 1 << ((unsigned int)bit & 31); }
	void rva000B3FA5(int bit, int value);
	unsigned int m_bits[19];
};

enum { WEAPONSET_COUNT = 104 };
extern const ModelConditionFlagType TheWeaponSetTypeToModelConditionTypeMap[WEAPONSET_COUNT];

class GlobalData
{
public:
	unsigned char m_pad000[0x134];
	int m_timeOfDay;						// +0x134
	int m_weather;							// +0x138
	unsigned char m_pad13C[2];
	bool m_forceModelsToFollowTimeOfDay;	// +0x13E
	bool m_forceModelsToFollowWeather;		// +0x13F
};
extern GlobalData *TheWritableGlobalData;

// The manager at TheGameLogic +0x178; its 0x0043846D is rowed under this owner.
class Rva0043846D
{
public:
	void rva0043846D(Object *obj);
};
extern GameLogic *TheGameLogic;

class BehaviorModule
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14();
	virtual void onDrawableBoundToObject();	// slot 6
};

class Object
{
public:
	void friend_bindToDrawable(Drawable *draw);
	void rva0028CFB2(const int *clear, const int *set);

private:
	unsigned char m_pad000[0x84];
	Drawable *m_drawable;					// +0x84
	unsigned char m_pad088[0x244 - 0x88];
	BehaviorModule **m_behaviors;			// +0x244
	unsigned char m_pad248[0x370 - 0x248];
	unsigned int m_curWeaponSetFlags[4];	// +0x370
};

void Object::friend_bindToDrawable(Drawable *draw)
{
	m_drawable = draw;
	if (m_drawable)
	{
		WeaponTemplateSetHead set;
		WeaponTemplateSetHead clr;
		for (int i = 0; i < WEAPONSET_COUNT; ++i)
		{
			ModelConditionFlagType mcs = TheWeaponSetTypeToModelConditionTypeMap[i];
			if (mcs != MODELCONDITION_INVALID)
			{
				if (m_curWeaponSetFlags[(unsigned int)i >> 5] & (1 << (i & 31)))
					set.set(mcs);
				else
					clr.set(mcs);
			}
		}
		GlobalData *global = TheWritableGlobalData;
		if (global)
		{
			if (global->m_forceModelsToFollowTimeOfDay)
				set.rva000B3FA5(MODELCONDITION_NIGHT, global->m_timeOfDay == 4);
			if (global->m_forceModelsToFollowWeather)
				set.rva000B3FA5(MODELCONDITION_SNOW, global->m_weather == 1);
		}
		rva0028CFB2((const int *)clr.m_bits, (const int *)set.m_bits);
		reinterpret_cast<Rva0043846D *>(TheGameLogic->getManager178())->rva0043846D(this);
	}

	for (BehaviorModule **b = m_behaviors; *b; ++b)
	{
		(*b)->onDrawableBoundToObject();
	}
}
