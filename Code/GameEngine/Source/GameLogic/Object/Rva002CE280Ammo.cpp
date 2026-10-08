// ?rva002CE280@Weapon@@QAEXM_N@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva002CE280@Weapon@@QAEXM_N@Z @0x002CE280 138B: floor-scaled ammo setter
// (thiscall, float rate + bool flag, void). Retail reads an int timeout at
// this+0x04/+0xE4 (bails when zero), scales (double)timeout * rate through
// the floor import back to float, truncates to want, and reloads when
// want > getRemainingAmmo(false), or when flag is set and want differs below:
// sets +0x14 to want, caches (!!getRemainingAmmo(false)) as WeaponStatus,
// copies [g_00DFE78C+0x40] into +0x28/+0x18, and rebuilds scatter targets.
// All callees are the landed Weapon rows, declared minimally; the global is
// the known TheGameLogic slot viewed opaquely. Honest address-derived name.
#include <math.h>

enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO
};

struct Rva002CE280Template
{
	char m_pad00[0xE4]; // +0x00..+0xE4 unclaimed
	int m_iE4; // +0xE4
};

struct Rva002CE280Globals
{
	char m_pad00[0x40]; // +0x00..+0x40 unclaimed
	void *m_p40; // +0x40
};

struct Rva002CE280Globals; extern class GameLogic *TheGameLogic;

class Weapon
{
public:
	unsigned int getRemainingAmmo(bool x) const;
	__declspec(noinline) void cacheStatus(WeaponStatus s) const;
	void rva002CE280(float rate, bool flag);
protected:
	void rebuildScatterTargets();
private:
	char m_pad00[0x04]; // +0x00..+0x04 unclaimed
	Rva002CE280Template *m_p04; // +0x04
	char m_pad08[0x10 - 0x08]; // +0x08..+0x10 unclaimed
	mutable WeaponStatus m_status; // +0x10
	unsigned int m_u14; // +0x14
	void *m_p18; // +0x18
	char m_pad1C[0x28 - 0x1C]; // +0x1C..+0x28 unclaimed
	void *m_p28; // +0x28
};

// Same-TU visible definition (mirrors WeaponGetStatus.cpp): cl sees it
// preserves ecx, so no reload is emitted before rebuildScatterTargets.
// The row lives in WeaponGetStatus.cpp; this copy must stay identical.
void Weapon::cacheStatus(WeaponStatus status) const
{
	if (m_status != status)
		m_status = status;
}

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
	if (m_p04->m_iE4 == 0)
		return;
	int n = m_p04->m_iE4;
	float f = (float)floor((double)n * rate);
	int want = rva002CE280_float2long(f);
	if (want > getRemainingAmmo(false) || (flag && want < getRemainingAmmo(false))) {
		m_u14 = want;
		cacheStatus((WeaponStatus)(getRemainingAmmo(false) != 0));
		m_p18 = m_p28 = ((Rva002CE280Globals *)TheGameLogic)->m_p40;
		rebuildScatterTargets();
	}
}
