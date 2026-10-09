// cl: /DNDEBUG /MD
//
// TurretAIAimTurretState::SetModelAngle, retail 0x004D8C23 (258 bytes, Object* and float,
// ret 8; single caller 0x004D907B in the TurretAI block). The caller,
// TurretAIAimTurretState::update 0x004D8EAC, loads its own this into ECX
// before the call (as the WorldBuilder twin does), so this is a thiscall
// member that does not read this; the body bytes are the same as stdcall.
// Donor: BFME1 game/GameEngine/Source/GameLogic/Object/
// Rva0018E210TurretAngleConditions.cpp (open-bfme-1 068db38bb4), same body:
// clear the four turret-angle model conditions, wrap a negative angle by 2*pi,
// then set the 90/180/270 condition for the (pi/4,3pi/4], (3pi/4,5pi/4] and
// (5pi/4,7pi/4] ranges, else the 0 condition. The owner class is unresolved in
// BFME1 too, so the placeholder is named by this address.
// BFME2 deltas (target evidence): the conditions are bits 9*32+18..21 of the
// Object+0x10C words (word +0x130 masks 0x40000..0x200000), the notifier is the
// pinned 0x0028AE6D, and the float literals are the same values (2*pi at
// 0x00BC746C, the quarter-pi bounds at 0x00BCE3A8/0x00BCE3BC/0x00C60DA8/
// 0x00C60DA4).
typedef int Int;
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void reset(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
#define RVA004D8C23_ZERO 0.0f
#define RVA004D8C23_TWO_PI 6.2831854820251465f
#define RVA004D8C23_PI_OVER_FOUR 0.7853981852531433f
#define RVA004D8C23_THREE_PI_OVER_FOUR 2.3561944961547852f
#define RVA004D8C23_FIVE_PI_OVER_FOUR 3.9269909858703613f
#define RVA004D8C23_SEVEN_PI_OVER_FOUR 5.4977874755859375f
class TurretAIAimTurretState
{
public:
	void SetModelAngle(Object *object, float angle);
};
static __forceinline void clearModelCondition(Object *object, Int bit)
{
	if (object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.reset(bit);
		object->rva0028AE6D();
	}
}
static __forceinline void setModelCondition(Object *object, Int bit)
{
	if (!object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.set(bit);
		object->rva0028AE6D();
	}
}
enum Rva004D8C23TurretAngleCondition
{
	BFME_TURRET_ANGLE_0 = 9 * 32 + 18,
	BFME_TURRET_ANGLE_90 = 9 * 32 + 19,
	BFME_TURRET_ANGLE_180 = 9 * 32 + 20,
	BFME_TURRET_ANGLE_270 = 9 * 32 + 21
};
void TurretAIAimTurretState::SetModelAngle(Object *object, float angle)
{
	clearModelCondition(object, BFME_TURRET_ANGLE_0);
	clearModelCondition(object, BFME_TURRET_ANGLE_90);
	clearModelCondition(object, BFME_TURRET_ANGLE_180);
	clearModelCondition(object, BFME_TURRET_ANGLE_270);
	if (angle < RVA004D8C23_ZERO)
	{
		angle += RVA004D8C23_TWO_PI;
	}
	if (angle > RVA004D8C23_PI_OVER_FOUR &&
		angle <= RVA004D8C23_THREE_PI_OVER_FOUR)
	{
		setModelCondition(object, BFME_TURRET_ANGLE_90);
		return;
	}
	if (angle > RVA004D8C23_THREE_PI_OVER_FOUR &&
		angle <= RVA004D8C23_FIVE_PI_OVER_FOUR)
	{
		setModelCondition(object, BFME_TURRET_ANGLE_180);
		return;
	}
	if (angle > RVA004D8C23_FIVE_PI_OVER_FOUR &&
		angle <= RVA004D8C23_SEVEN_PI_OVER_FOUR)
	{
		setModelCondition(object, BFME_TURRET_ANGLE_270);
		return;
	}
	setModelCondition(object, BFME_TURRET_ANGLE_0);
}
