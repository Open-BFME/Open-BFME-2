// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004E09FB@Rva004E0790Inner@@QAEAAU1@ABU1@@Z @0x004E09FB 93B
// Copy-assign of Rva004E0790Inner: assigns leading BfmeAssignRecord172 at +0x00
// via rowed 0x001EB20E, skips TargetRef at +0xAC (refcount preserved), then
// copies dwords at +0xB4/+0xB8/+0xBC/+0xC0 and bytes at +0xC4/+0xC5.
// Returns *this (ret 4). Evidence: caller at 0x004E0C29 passes Inner m_ptr in
// ecx with source in stack arg; same 0xAC record plus 0xB0 refcount layout as
// Rva004E0790Inner in Rva004E0790Release.cpp/Rva004E08F6Set.cpp.
struct BfmeAssignRecord172
{
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &other);
	char m_pad[0xAC];
};
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct Rva004E0790Inner
{
	BfmeAssignRecord172 m_00;
	TargetRef00217D4C m_ac;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_c5;
	Rva004E0790Inner &rva004E09FB(const Rva004E0790Inner &other);
};
Rva004E0790Inner &Rva004E0790Inner::rva004E09FB(const Rva004E0790Inner &other)
{
	m_00 = other.m_00;
	m_b4 = other.m_b4;
	m_b8 = other.m_b8;
	m_bc = other.m_bc;
	m_c0 = other.m_c0;
	m_c4 = other.m_c4;
	m_c5 = other.m_c5;
	return *this;
}
