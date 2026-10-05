// WeaponTemplate bonus-argument Int getter at 0x002C93F7 (9 bytes):
//
//     8B 81 44 01 00 00  mov eax,[ecx+0x144]
//     C2 04 00           ret 4
//
// Target facts (game.dat, base 0x400000, .text vaddr 0x1000): disp32 0x144
// load with ret 4, i.e. one 4-byte stack argument -- the same const
// WeaponBonus& shape as the rowed clip/delay/preAttack siblings at
// 0x002C937C/0x002C9322/0x002C93DF. Starts exactly where the rowed 24B
// preAttack body ends (0x93DF+24 = 0x93F7); 0x9400 starts the rowed Disp32
// bool getters, so the boundary is proven on both sides. Leaf: no calls,
// no DIR32 slots, no string refs, no pins (a pin alone proves nothing).
//
// Donor lead (ZH GeneralsMD Weapon.h, immutable rev 6583b3c1, read-only):
// the class carries getPreAttackDelay-style bonus getters, but no donor
// field maps onto BFME 2 +0x144 (the BFME 2 layout diverges past
// m_preAttackDelay at +0x138), so the name is address-derived and the
// bonus argument stays opaque and unused until a rowed caller or table
// entry proves semantics. No // cl: line: build defaults (-O2 -GR- -EHsc-)
// match the frameless shape, same as Disp32DwordFieldGetters.
class WeaponBonus;
class WeaponTemplate
{
public:
	int rva002C93F7(const WeaponBonus &bonus) const;
private:
	char m_pad[0x144];
	int m_value144;
};
int WeaponTemplate::rva002C93F7(const WeaponBonus & /*bonus*/) const
{
	return m_value144;
}
