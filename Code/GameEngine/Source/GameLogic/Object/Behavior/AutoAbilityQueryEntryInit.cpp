// cl: /O1 /MD /DNDEBUG
//
// ?init@AutoAbilityQueryEntry@@QAEPAV1@XZ,
// retail 0x0045A1D9, 18 bytes. Frameless Query-entry init over the Query
// table at +0x2C (key Query, array of 6 8-byte entries). Identity is the
// ehvec construction in AutoAbility ctor 0x45A2E7 (element size 8 count 6
// with this as ctor arg) plus the Query parse proc 0x45A22E in the same
// cluster plus the AutoAbilityBehavior poolkey 0x45A3CE. Shape is or-minus1
// plus member construct through pinned 0x3623E5 plus return-this tail
// (DieMuxData init precedent: frameless member-init ending mov eax esi
// returns this, not void).

class Rva003623E5Member
{
public:
	void construct();
};

class AutoAbilityQueryEntry
{
public:
	AutoAbilityQueryEntry *init();

private:
	int m_state; // +0, or-minus1
	Rva003623E5Member m_filter; // +4, via pinned 0x3623E5
};

// ?init@AutoAbilityQueryEntry@@QAEPAV1@XZ @0x45A1D9
AutoAbilityQueryEntry *AutoAbilityQueryEntry::init()
{
	m_state |= -1;
	m_filter.construct();
	return this;
}
