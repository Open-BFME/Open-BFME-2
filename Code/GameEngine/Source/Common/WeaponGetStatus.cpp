// cl: /DNDEBUG /MD
// BFME1's cached status query, adapted to BFME2's out-of-line cache setter.
//
// ?rva002CE226@Weapon@@QAEXPBVObject@@PBUSavedWeaponState@@@Z @0x002CE226
// 90B, caller 0x002C8DC3: looks the weapon template key (+0x0C) up in a
// six-entry table of 0x14-byte saved states; on a hit restores +0x14, the
// cached status (through cacheStatus), +0x28 and +0x18 from it, otherwise
// loadAmmoNow (rowed 0x002CE1AC) when the template byte at +0x16E is set,
// else reloadAmmo (rowed 0x002CE1E9). BFME2-only; the table entry fields are
// named by the Weapon fields they restore. Retail keeps the entry pointer in
// edx across the cacheStatus call, which cl only does because cacheStatus is
// compiled earlier in this TU.
#include <math.h>

extern class GameLogic *TheGameLogic;

enum WeaponStatus
{
    READY_TO_FIRE,
    OUT_OF_AMMO,
    BETWEEN_FIRING_SHOTS,
    RELOADING_CLIP,
    PRE_ATTACK,
    WEAPON_STATUS_5
};

#include "../../Include/GameLogic/ObjectFilter.h"

#include "../../Include/GameLogic/WeaponTemplate.h"

// The header keeps the +0x120 pooled ammo descriptor as opaque storage.
static __forceinline const ObjectFilter &weaponTemplateAmmo(const WeaponTemplate *wt)
{
    return *(const ObjectFilter *)&wt->m_field120;
}

class Object;

struct SavedWeaponState
{
    int m_key;
    int m_14;
    WeaponStatus m_status;
    int m_28;
    unsigned int m_18;
};

struct GameLogicFrame
{
    char m_pad00[0x40];
    unsigned int m_frame;
};

#define TheGameLogic (*(GameLogicFrame **)&TheGameLogic)

#include "../../Include/GameLogic/Weapon.h"

__declspec(noinline) void Weapon::cacheStatus(WeaponStatus status) const
{
    if (m_status != status)
        m_status = status;
}

// Ammo scaling is kept beside cacheStatus: both callers require the
// same visible noinline worker for VC7.1 register-preservation analysis.
// Upstream basetype.h x87 conversion, mirroring rowed sibling 0x002C937C:
// (int) on the float must stay inline fld/fistp, never __ftol2.
__forceinline long rva002CE280_float2long(float floatValue)
{
	long i;
	__asm {
		fld [floatValue]
		fistp [i]
	}
	return i;
}

// ?setClipPercentFull@Weapon@@QAEXM_N@Z
void Weapon::setClipPercentFull(float rate, bool flag)
{
	if (m_template->m_clipSize == 0)
		return;
	int m_clipSize = m_template->m_clipSize;
	float f = (float)floor((double)m_clipSize * rate);
	int want = rva002CE280_float2long(f);
	if (want > getRemainingAmmo(false) || (flag && want < getRemainingAmmo(false))) {
		m_ammoInClip = want;
		cacheStatus((WeaponStatus)(getRemainingAmmo(false) != 0));
		m_whenWeCanFireAgain = m_projectileStreamID = TheGameLogic->m_frame;
		rebuildScatterTargets();
	}
}

WeaponStatus Weapon::getStatus() const
{
    bool cacheable = true;
    WeaponStatus status = computeStatus(&cacheable);
    if (cacheable)
        cacheStatus(status);
    return status;
}

WeaponStatus Weapon::computeStatus(bool *cacheable) const
{
    unsigned int frame = TheGameLogic->m_frame;
    if (frame < m_whenPreAttackFinished)
    {
        if (cacheable)
            *cacheable = false;
        return PRE_ATTACK;
    }
    else
    {
        if (frame < m_whenLastReloadStarted)
        {
            if (cacheable)
                *cacheable = false;
            return WEAPON_STATUS_5;
        }
        if (m_template->m_idleAfterFiringDelay >= 0)
        {
            if (frame < m_whenWeCanFireAgain && !weaponTemplateAmmo(m_template).isValid())
                goto return_cached_status;
            if (getRemainingAmmo(false) > 0)
                return READY_TO_FIRE;
            if (frame >= m_whenWeCanFireAgain)
            {
                const WeaponTemplate *weaponTemplate = m_template;
                if (weaponTemplateAmmo(weaponTemplate).isValid())
                {
                    if (isAmmoReady())
                        return READY_TO_FIRE;
                }
            }
            return OUT_OF_AMMO;
        }
        if (frame < m_whenWeCanFireAgain && !weaponTemplateAmmo(m_template).isValid())
        return_cached_status:
            return m_status;
        return (WeaponStatus)(getRemainingAmmo(false) <= 0);
    }
}

void Weapon::rva002CE226(const Object *sourceObj, const SavedWeaponState *saved)
{
    if (saved)
    {
        for (int i = 0; i < 6; ++i, ++saved)
        {
            if (saved->m_key == m_template->m_nameKey)
            {
                m_ammoInClip = saved->m_14;
                cacheStatus(saved->m_status);
                m_projectileStreamID = saved->m_28;
                m_whenWeCanFireAgain = saved->m_18;
                return;
            }
        }
    }
    if (m_template->m_field16E)
        loadAmmoNow(sourceObj);
    else
        reloadAmmo(sourceObj);
}
