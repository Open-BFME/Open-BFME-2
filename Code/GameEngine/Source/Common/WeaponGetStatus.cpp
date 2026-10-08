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

class ObjectFilter
{
public:
    bool isValid() const;
};

class WeaponTemplate
{
public:
    char m_pad00[0x0C];
    int m_key0C;
    char m_pad10[0x78 - 0x10];
    int m_flag78;
    char m_pad7C[0xE4 - 0x7C];
    int m_valueE4; // target ammo-scaling operand
    char m_padE8[0x120 - 0xE8];
    ObjectFilter m_ammo;
    char m_pad121[0x16E - 0x121]; // ObjectFilter is one byte here
    bool m_flag16E;
};

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

class Weapon
{
public:
    WeaponStatus getStatus() const;
    WeaponStatus computeStatus(bool *cacheable) const;
    __declspec(noinline) void cacheStatus(WeaponStatus status) const;
    unsigned int getRemainingAmmo(bool countReloadingAsEmpty) const;
    bool isAmmoReady() const;
    void loadAmmoNow(const Object *sourceObj);
    void reloadAmmo(const Object *sourceObj);
    void rva002CE226(const Object *sourceObj, const SavedWeaponState *saved);
    void rva002CE280(float rate, bool flag);
protected:
    void rebuildScatterTargets();
private:
    char m_pad00[4];
    WeaponTemplate *m_template;
    char m_pad08[8];
    mutable WeaponStatus m_status;
    int m_pad14;
    unsigned int m_frame18;
    unsigned int m_frame1C;
    unsigned int m_frame20;
    int m_pad24;
    int m_28;
};

void Weapon::cacheStatus(WeaponStatus status) const
{
    if (m_status != status)
        m_status = status;
}

// Ammo scaling is kept beside cacheStatus: both callers require the
// same visible noinline worker for VC7.1 register-preservation analysis.
// Upstream basetype.h x87 conversion, mirroring rowed sibling 0x002C937C:
// (int) on the float must stay inline fld/fistp, never __ftol2.
__forceinline long rva002CE280_float2long(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

// ?rva002CE280@Weapon@@QAEXM_N@Z
void Weapon::rva002CE280(float rate, bool flag)
{
	if (m_template->m_valueE4 == 0)
		return;
	int n = m_template->m_valueE4;
	float f = (float)floor((double)n * rate);
	int want = rva002CE280_float2long(f);
	if (want > getRemainingAmmo(false) || (flag && want < getRemainingAmmo(false))) {
		m_pad14 = want;
		cacheStatus((WeaponStatus)(getRemainingAmmo(false) != 0));
		m_frame18 = m_28 = TheGameLogic->m_frame;
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
    if (frame < m_frame1C)
    {
        if (cacheable)
            *cacheable = false;
        return PRE_ATTACK;
    }
    else
    {
        if (frame < m_frame20)
        {
            if (cacheable)
                *cacheable = false;
            return WEAPON_STATUS_5;
        }
        if (m_template->m_flag78 >= 0)
        {
            if (frame < m_frame18 && !m_template->m_ammo.isValid())
                goto return_cached_status;
            if (getRemainingAmmo(false) > 0)
                return READY_TO_FIRE;
            if (frame >= m_frame18)
            {
                WeaponTemplate *weaponTemplate = m_template;
                if (weaponTemplate->m_ammo.isValid())
                {
                    if (isAmmoReady())
                        return READY_TO_FIRE;
                }
            }
            return OUT_OF_AMMO;
        }
        if (frame < m_frame18 && !m_template->m_ammo.isValid())
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
            if (saved->m_key == m_template->m_key0C)
            {
                m_pad14 = saved->m_14;
                cacheStatus(saved->m_status);
                m_28 = saved->m_28;
                m_frame18 = saved->m_18;
                return;
            }
        }
    }
    if (m_template->m_flag16E)
        loadAmmoNow(sourceObj);
    else
        reloadAmmo(sourceObj);
}
