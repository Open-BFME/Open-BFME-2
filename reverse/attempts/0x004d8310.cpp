// ?friend_isAnyWeaponInRangeOf@TurretAI@@QBE_NPBVObject@@@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?friend_isAnyWeaponInRangeOf@TurretAI@@QBE_NPBVObject@@@Z,
// retail 0x004D8310, 85B.
// TurretAI out-of-range check: for each of the 6 native weapon slots,
// skip empty or off-turret slots, return true on first weapon whose
// attack range covers (owner, o); false otherwise.
//
// Identity/layout/provenance (target evidence, not bytes alone):
// - Boundary [0x4D8310,0x4D8365) 85B: pred 0x4D82F6+26 ends exactly at
//   0x4D8310 (push ebx), succ 0x4D8365 is rowed friend_isSweepEnabled 24B.
//   Single ret-4 (1 Object* arg, thiscall const returning bool); loop
//   cmp ebx,6 / jl proves native 6-wide iteration (WEAPONSLOT_COUNT 6,
//   same 6 as ctor sweep/speed arrays [6] at +0x10/+0x28).
// - Layout: TurretAI m_owner at +0x10 (member, NOT inherited AudioEvent
//   base -- AudioEventRTS is a member elsewhere, base would shift owner).
//   Object embeds WeaponSet at +0x330 (retail lea ecx,[eax+0x330]).
//   isWeaponSlotOnTurret reads m_data+0x4C mask (rowed 0x4D81D7).
// - Providers: getWeaponInWeaponSlot 0x002C7469 (pinned ICF twin of
//   Peek_Texture 11B, address from retail REL32 at 0x290C74);
//   isWeaponSlotOnTurret 0x004D81D7 rowed 26B; isWithinAttackRange
//   0x002CB933 52B pinned candidate (retail REL32 at 0x4D834A, ZH/BFME1
//   donor widened to 4-arg per retail fldz/push1 pushes).
// - Reference-first: ZH GeneralsMD TurretAI.cpp friend_isAnyWeaponInRangeOf
//   (WEAPONSLOT_COUNT loop, getWeaponInWeaponSlot + isWeaponSlotOnTurret
//   skip, isWithinAttackRange(owner,o) true/false) + BFME1 game
//   TurretAI.cpp same (present-unmatched marker). Same-name hit never
//   used as proof; loop-6 + owner/member + 3-call shape + ret-4 do.
//   Donor rev 6583b3c1 reused read-only, no fetch. Flags from TurretAI
//   parse siblings (/O1 /DNDEBUG /MD).

typedef int Int;
typedef bool Bool;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_SECONDARY,
	WEAPONSLOT_TERTIARY,
	WEAPONSLOT_QUATERNARY,
	WEAPONSLOT_QUINARY,
	WEAPONSLOT_SIXTH,
	WEAPONSLOT_COUNT = 6
};

class Object;
class Weapon;

class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};

class Object
{
public:
	char m_pad[0x330];
	WeaponSet m_weaponSet;
};

class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, float f, int i) const;
};

class TurretAI
{
public:
	char m_pad[0x10];
	Object *m_owner;

	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
	Bool friend_isAnyWeaponInRangeOf(const Object *o) const;
};

// ?friend_isAnyWeaponInRangeOf@TurretAI@@QBE_NPBVObject@@@Z @0x004D8310
Bool TurretAI::friend_isAnyWeaponInRangeOf(const Object *o) const
{
	for (Int i = 0; i < WEAPONSLOT_COUNT; ++i)
	{
		WeaponSlotType slot = (WeaponSlotType)i;
		const Weapon *w = m_owner->m_weaponSet.getWeaponInWeaponSlot(slot);
		if (w == 0 || !isWeaponSlotOnTurret(slot))
			continue;
		if (w->isWithinAttackRange(m_owner, o, 0.0f, 1))
			return true;
	}
	return false;
}
