// cl: /O1 /DNDEBUG /MD
// ?rva0044EECA@Rva0044EECA@@QAE_NPAURva0044EECAParam@@@Z @0x0044EECA 98B
// Vtable slot 37 (offset 0x94) of 0x0084D5A0 (ArrowStormUpdateModuleData),
// 0x0084DF58 (HeroModeSpecialAbilityUpdateModuleData) and 0x0084E108
// (WeaponFireSpecialAbilityUpdateModuleData); base SpecialAbilityUpdateModuleData family.
// Retail is a bool predicate over this+0x10/+0x48/+0x60 and param+0x44
// (Overridable) plus param flag+0x1D bit 1, calling rowed
// Overridable::friend_getFinalOverride at 0x00288609 and testing
// final+0x1C == 0x16 then final+0x20 == 0. Flags from neighbours
// ModuleDataBuildFieldParseChained.cpp and Rva0044EF2CFinalOverride.cpp.
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	unsigned char m_pad00[0x1C];
	int m_val1C;
	int m_val20;
};

struct Rva0044EECAParam
{
	unsigned char m_pad00[0x1D];
	unsigned char m_flags1D;
	unsigned char m_pad1E[0x44 - 0x1E];
	Overridable *m_over44;
};

class Rva0044EECA
{
public:
	bool rva0044EECA(Rva0044EECAParam *p);
private:
	unsigned char m_pad00[0x10];
	int m_val10;
	unsigned char m_pad14[0x48 - 0x14];
	int m_val48;
	unsigned char m_pad4C[0x60 - 0x4C];
	unsigned char m_val60;
};

bool Rva0044EECA::rva0044EECA(Rva0044EECAParam *p)
{
	if (p != 0) {
		Overridable *o = p->m_over44;
		if (o != 0) {
			const Overridable *f = o->friend_getFinalOverride();
			if (f->m_val1C == 0x16 && (p->m_flags1D & 2) == 0)
				return m_val48 == 0;
		}
	}
	int v = m_val10;
	if (v != 0) {
		if (v == 1 || v == 3) {
			if (p != 0) {
				const Overridable *f2 = p->m_over44->friend_getFinalOverride();
				if (f2->m_val20 == 0)
					return false;
			}
		}
		if (m_val60 != 0)
			return true;
	}
	return false;
}
