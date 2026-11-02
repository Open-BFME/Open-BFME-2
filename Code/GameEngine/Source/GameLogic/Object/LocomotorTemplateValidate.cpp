// cl: /O1 /arch:SSE
//
// LocomotorTemplate::validate, retail 0x001E38B9 (64 bytes); formerly the
// address-named Rva001E38B9::rva001E38B9 (Code/GameEngine/Source/Common/
// Rva001E38B9Fixup.cpp).
// Identity (target): WorldBuilder's debug Locomotor.cpp
// LocomotorTemplate::validate (asserts at lines 351..356, "WINGS should always
// have positive minSpeeds" / "... positive minTurnSpeed") has the same four
// steps on the same offsets: +0x30 defaults from +0x2C when zero, +0x4C from
// +0x48 when negative, and for appearance 3 (+0x74) non-positive +0x28 and
// +0x54 become 0.01f. Retail's single caller is 0x001E8C07 (wb-lead 1/callsite).
// Field names: minSpeed (+0x28) and minTurnSpeed (+0x54) come from the WB
// assert text; the +0x2C/+0x30 and +0x48/+0x4C fallback pairs are not named
// by target evidence and stay offset-named (Zero Hour's validate makes damaged
// values fall back to undamaged ones, an unverified donor reading).

typedef float Real;

enum LocomotorAppearance
{
	LOCO_WINGS = 3 // retail-measured value of +0x74 tested here
};

#include "../../../Include/GameLogic/LocomotorTemplate.h"

void LocomotorTemplate::validate()
{
	if (m_turnTimeDamaged == 0)
		m_turnTimeDamaged = m_turnTime;

	if (m_liftDamaged < 0.0f)
		m_liftDamaged = m_lift;

	if (m_appearance == LOCO_WINGS)
	{
		if (m_minSpeed <= 0.0f)
			m_minSpeed = 0.01f;
		if (m_minTurnSpeed <= 0.0f)
			m_minTurnSpeed = 0.01f;
	}
}
