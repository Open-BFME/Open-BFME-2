// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ??4Weapon@@QAEAAV0@ABV0@@Z retail 0x002C9462 (147B): Zero Hour's
// Weapon::operator= (Weapon.cpp: "Weapons lose all ammo when copied"), with
// BFME 2's extra state. Target facts: the template (+0x04), the +0x08 and
// +0x0C words are copied; status (+0x10) becomes 1 (OUT_OF_AMMO); the ammo,
// timers and the BFME 2 words at +0x18 and +0x50/+0x54/+0x58/+0x5C clear;
// +0x4C is ZH's pitch-limited test against -PI/PI on the template's
// +0x88/+0x8C pitch limits; +0x34 is NO_MAX_SHOTS_LIMIT (0x7FFFFFFF); the
// +0x30 suspend frame is copied and +0x3C takes the template's +0x108 shots
// per barrel. Field names are the canonical Weapon.h's for each offset.

#define PI 3.14159265359f
#define NO_MAX_SHOTS_LIMIT 0x7fffffff

#include "../../../Include/GameLogic/WeaponTemplate.h"

#include "../../../Include/GameLogic/Weapon.h"

Weapon &Weapon::operator=(const Weapon &that)
{
	if (this != &that)
	{
		m_template = that.m_template;
		m_ownerID = that.m_ownerID;
		m_wslot = that.m_wslot;
		m_status = (WeaponStatus)1;
		m_ammoInClip = 0;
		m_whenPreAttackFinished = 0;
		m_whenLastReloadStarted = 0;
		m_lastFireFrame = 0;
		m_projectileStreamID = 0;
		m_whenWeCanFireAgain = 0;
		m_leechWeaponRangeActive = 0;
		m_unknown54 = 0;
		m_pitchLimited = (m_template->getMinTargetPitch() > -PI || m_template->getMaxTargetPitch() < PI);
		m_curBarrel = 0;
		m_unknown2C = 0;
		m_maxShotCount = NO_MAX_SHOTS_LIMIT;
		m_suspendFXFrame = that.getSuspendFXFrame();
		m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
		m_tailState = 0;
		m_extra5C = 0;
	}
	return *this;
}
