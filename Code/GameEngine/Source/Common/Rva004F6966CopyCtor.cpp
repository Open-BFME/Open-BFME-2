// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva004F6966@@QAE@ABU0@@Z @0x004F6966 (32B): copy ctor for 12-byte holder.
// Copies pointer at +0 with inline AddRef at +4 plus ints at +4/+8. Same
// shape as Rva004F692B copy ctor at 0x004F692B (8B with +4 zeroed) but with
// +4/+8 copied. Callers at 0x004F6B75 0x004F6DFA 0x004F7171 0x004F72B2
// 0x004F7798 0x004F98A9. Prev Rva004F692B /O1 /Ob0 next Rva004F69C3 /O1.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F6966
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
};

Rva004F6966::Rva004F6966(const Rva004F6966 &other)
{
	m_00 = other.m_00;
	if (m_00 != 0)
		++m_00->references;
	m_04 = other.m_04;
	m_08 = other.m_08;
}
