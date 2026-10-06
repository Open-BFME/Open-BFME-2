// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva002C75D1@WeaponSet@@QBE_NHH@Z @0x002C75D1, 41B.
// WeaponSet slot auto-choose check. Returns true when the per-slot byte at
// +0x36 is set, otherwise tests the template auto-choose mask at +0x2C for
// bit (1 << cmdSource). Retail reads byte [this+0x36+slot] then
// [[this+4]+slot*4+0x2C] & (1 << cmdSource).
// Evidence: caller 0x002C7E25 passes slot in 0..5 and CommandSource;
// [this+4] is WeaponTemplateSet whose +0x2C array stride 4 matches
// m_autoChooseMask[6] (+0x2C..+0x43, next array at +0x44proven by 0x002C7501
// KindOf callers). Neighbour WeaponSetRvaSlotSearch.cpp proves six slots.

class WeaponTemplateSet
{
public:
	char m_pad[0x2C];
	int m_autoChooseMask[6];
};

class WeaponSet
{
public:
	bool rva002C75D1(int slot, int cmdSource) const;

private:
	char m_pad0[4];
	const WeaponTemplateSet *m_templateSet;
	char m_pad8[0x36 - 8];
	unsigned char m_byte36[6];
};

bool WeaponSet::rva002C75D1(int slot, int cmdSource) const
{
	if (m_byte36[slot])
		return true;
	if ((m_templateSet->m_autoChooseMask[slot] & (1 << cmdSource)) != 0)
		return true;
	return false;
}
