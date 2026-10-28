// ??0SpecialAbilityUpdateModuleData@@QAE@XZ
// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
// ??0SpecialAbilityUpdateModuleData@@QAE@XZ at 0x0044EB54 (378 bytes).
// Identity: ModuleFactory registers SpecialAbilityUpdate with the data factory
// at 0x0024A882, which calls this ctor and pushes buildFieldParse 0x0044ED95
// (tools/check_module_registry.py); it was rowed by address as Rva0044EB54.
// Address-derived opaque intermediate default ctor. Target evidence: vtable
// immediate 0x00C3F2A8, 26 this-only module-data ctor callers, a 0xC8 prefix
// shared by derived factories, and the rowed chained parser at 0x0044ED95.
// Ghidra boundary is 378 bytes. Association with the SpecialAbility family
// is structural inference; exact semantic identity is unproven.
#include <stddef.h>
#include "Common/Snapshot.h"


#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"


class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class OpaqueRefPtr
{
public:
	OpaqueRefPtr() : m_p(0) {}
	~OpaqueRefPtr() { if (m_p) m_p->Release_Ref(); }
private:
	OpaqueRefCounted *m_p;
};

// The four dwords form one layout-only group so the +1C/+20 zero stores precede
// the paired -1 stores, matching the target's schedule without asserting names.
class Rva0044EB54Fields18
{
public:
	__forceinline Rva0044EB54Fields18()
	{
		m_customAnimTime = 0;
		m_20 = 0;
		m_customAnimState = -1;
		m_grabPassengerAnimState = -1;
	}

private:
	int m_customAnimState;
	int m_customAnimTime;
	int m_20;
	int m_grabPassengerAnimState;
};

class SpecialAbilityUpdateModuleData : public Snapshot
{
public:
	SpecialAbilityUpdateModuleData();
private:
	int m_04;
	OpaqueRefPtr m_packSound;
	OpaqueRefPtr m_unpackSound;
	OpaqueRefPtr m_prepSoundLoop;
	OpaqueRefPtr m_triggerSound;
	Rva0044EB54Fields18 m_fields18;
	int m_28;
	int m_2C;
	float m_grabPassengerHealGainPercent;
	OpaqueRefPtr m_activeLoopSound;
	int m_specialPowerTemplate;
	int m_disableFXParticleSystem;
	AsciiString m_specialObject;
	AsciiString m_specialObjectAttachToBone;
	AsciiString m_triggerAttributeModifier;
	float m_startAbilityRange;
	float m_abilityAbortRange;
	float m_packUnpackVariationFactor;
	float m_fleeRangeAfterCompletion;
	int m_effectValue;
	float m_effectRange;
	int m_awardXPForTriggering;
	int m_skillPointsForTriggering;
	int m_unpackingVariation;
	int m_persistentCount;
	int m_preparationTime;
	int m_persistentPrepTime;
	int m_effectDuration;
	int m_maxSpecialObjects;
	int m_packTime;
	int m_unpackTime;
	int m_preTriggerUnstealthTime;
	int m_paralyzeDurationWhenCompleted;
	int m_paralyzeDurationWhenAborted;
	int m_attributeModifierDuration;
	int m_freezeAfterTriggerDuration;
	int m_requiredConditions;
	int m_rejectedConditions;
	unsigned char m_skipPackingWithNoTarget;
	unsigned char m_specialObjectsPersistent;
	unsigned char m_AA;
	unsigned char m_AB;
	unsigned char m_AC;
	unsigned char m_AD;
	unsigned char m_AE;
	unsigned char m_AF;
	unsigned char m_loseStealthOnTrigger;
	unsigned char m_approachRequiresLOS;
	unsigned char m_chargeAttackSpeedBoost;
	unsigned char m_killAttributeModifierOnExit;
	unsigned char m_killAttributeModifierOnRejected;
	unsigned char m_mustFinishAbility;
	unsigned char m_disableWhenWearingTheRing;
	unsigned char m_instant;
	unsigned char m_needCollisionBeforeTrigger;
	AsciiString m_BC;
	AsciiString m_chainedButton;
	unsigned char m_suppressForHordes;
	unsigned char m_approachUntilMembersInRange;
	unsigned char m_ignoreFacingCheck;
};

SpecialAbilityUpdateModuleData::SpecialAbilityUpdateModuleData()
	: m_packSound()
	, m_unpackSound()
	, m_prepSoundLoop()
	, m_triggerSound()
	, m_28(0)
	, m_2C(0)
	, m_grabPassengerHealGainPercent(100.0f)
	, m_activeLoopSound()
	, m_specialPowerTemplate(0)
	, m_disableFXParticleSystem(0)
	, m_specialObject()
	, m_specialObjectAttachToBone()
	, m_triggerAttributeModifier()
	, m_startAbilityRange(10000000.0f)
	, m_abilityAbortRange(10000000.0f)
	, m_packUnpackVariationFactor(0.0f)
	, m_fleeRangeAfterCompletion(0.0f)
	, m_effectValue(1)
	, m_effectRange(0.0f)
	, m_awardXPForTriggering(0)
	, m_skillPointsForTriggering(-1)
	, m_unpackingVariation(0)
	, m_persistentCount(-1)
	, m_preparationTime(0)
	, m_persistentPrepTime(0)
	, m_effectDuration(0)
	, m_maxSpecialObjects(1)
	, m_packTime(0)
	, m_unpackTime(0)
	, m_preTriggerUnstealthTime(0)
	, m_paralyzeDurationWhenCompleted(0)
	, m_paralyzeDurationWhenAborted(0)
	, m_attributeModifierDuration(0)
	, m_freezeAfterTriggerDuration(0)
	, m_requiredConditions(0)
	, m_rejectedConditions(0)
	, m_skipPackingWithNoTarget(0)
	, m_specialObjectsPersistent(0)
	, m_AA(0)
	, m_AB(0)
	, m_AC(0)
	, m_AD(0)
	, m_AE(0)
	, m_AF(0)
	, m_loseStealthOnTrigger(0)
	, m_approachRequiresLOS(1)
	, m_chargeAttackSpeedBoost(0)
	, m_killAttributeModifierOnExit(0)
	, m_killAttributeModifierOnRejected(0)
	, m_mustFinishAbility(0)
	, m_disableWhenWearingTheRing(0)
	, m_instant(0)
	, m_needCollisionBeforeTrigger(0)
	, m_BC()
	, m_chainedButton("")
	, m_suppressForHordes(0)
	, m_approachUntilMembersInRange(0)
	, m_ignoreFacingCheck(0)
{
}
