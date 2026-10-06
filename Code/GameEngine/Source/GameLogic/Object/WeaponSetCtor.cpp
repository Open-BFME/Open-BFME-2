// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??0WeaponSet@@QAE@XZ @0x002C72D5, 60B.
// WeaponSet::WeaponSet. Zero-initializing ctor: vtable 0x0080089C plus null
// template set at +0x4, six slots at +0x8, ints at +0x20..+0x30, flags at
// +0x34/+0x35, per-slot bytes at +0x36[6] and tail at +0x3C.
// Evidence: neighbour WeaponSetIsOutOfAmmo.cpp proves six slots at +0x8 and
// hasPitchLimit at +0x34; WeaponSetRva002C75D1.cpp proves template set at
// +0x4 and byte array at +0x36[6]; next row 0x002C7362 is WeaponSet method;
// ZH donor WeaponSet::WeaponSet zeroes the same fields.
// ?isAnyWithinTargetPitch@WeaponSet@@ABE_NPBVObject@@0@Z is rowed.

class WeaponSet
{
public:
	WeaponSet();

private:
	const void *m_vptr;
	const void *m_templateSet;
	void *m_weapons[6];
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36[6];
	int m_3C;
};

extern const void *const g_00C0089C[];

WeaponSet::WeaponSet()
{
	m_vptr = g_00C0089C;
	m_20 = 0;
	m_24 = 0;
	m_templateSet = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_35 = 0;
	for (int i = 0; i < 6; ++i) {
		m_weapons[i] = 0;
		m_36[i] = 0;
	}
	m_3C = 0;
}
