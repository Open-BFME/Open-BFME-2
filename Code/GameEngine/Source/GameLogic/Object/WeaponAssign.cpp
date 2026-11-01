// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ??4Weapon@@QAEAAV0@ABV0@@Z retail 0x002C9462 (147B): Zero Hour's
// Weapon::operator= (Weapon.cpp: "Weapons lose all ammo when copied"), with
// BFME 2's extra state. Target facts: the template (+0x04), slot (+0x08) and
// the +0x0C word are copied; status (+0x10) becomes 1 (OUT_OF_AMMO); the ammo,
// timers and the BFME 2 words at +0x18 and +0x50/+0x54/+0x58/+0x5C clear;
// +0x4C is ZH's pitch-limited test against -PI/PI on the template's
// +0x88/+0x8C pitch limits; +0x34 is NO_MAX_SHOTS_LIMIT (0x7FFFFFFF); the
// +0x30 suspend frame is copied and +0x3C takes the template's +0x108 shots
// per barrel. Field names follow ZH where its order matches (structural
// inference); the others keep offset names.

#define PI 3.14159265359f
#define NO_MAX_SHOTS_LIMIT 0x7fffffff

#include "../../../Include/GameLogic/WeaponTemplate.h"

class Weapon
{
public:
	Weapon &operator=(const Weapon &that);
	__declspec(dllimport) __forceinline unsigned int getSuspendFXFrame() const { return m_suspendFXFrame; }
private:
	char m_pad00[4];
	const WeaponTemplate *m_template; // +0x04
	int m_wslot; // +0x08
	int m_0C; // +0x0C
	int m_status; // +0x10
	int m_ammoInClip; // +0x14
	int m_18; // +0x18
	unsigned int m_whenPreAttackFinished; // +0x1C
	unsigned int m_whenLastReloadStarted; // +0x20
	unsigned int m_whenWeCanFireAgain; // +0x24
	unsigned int m_28; // +0x28
	int m_curBarrel; // +0x2C
	unsigned int m_suspendFXFrame; // +0x30
	int m_maxShotCount; // +0x34
	unsigned int m_lastFireFrame; // +0x38
	int m_numShotsForCurBarrel; // +0x3C
	char m_pad40[0x4C - 0x40];
	bool m_pitchLimited; // +0x4C
	int m_50; // +0x50
	int m_54; // +0x54
	int m_58; // +0x58
	int m_5C; // +0x5C
};

Weapon &Weapon::operator=(const Weapon &that)
{
	if (this != &that)
	{
		m_template = that.m_template;
		m_wslot = that.m_wslot;
		m_0C = that.m_0C;
		m_status = 1;
		m_ammoInClip = 0;
		m_whenPreAttackFinished = 0;
		m_whenLastReloadStarted = 0;
		m_whenWeCanFireAgain = 0;
		m_28 = 0;
		m_18 = 0;
		m_50 = 0;
		m_54 = 0;
		m_pitchLimited = (m_template->getMinTargetPitch() > -PI || m_template->getMaxTargetPitch() < PI);
		m_lastFireFrame = 0;
		m_curBarrel = 0;
		m_maxShotCount = NO_MAX_SHOTS_LIMIT;
		m_suspendFXFrame = that.getSuspendFXFrame();
		m_numShotsForCurBarrel = m_template->getShotsPerBarrel();
		m_58 = 0;
		m_5C = 0;
	}
	return *this;
}
