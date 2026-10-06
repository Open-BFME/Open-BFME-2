// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva004F691E@@QAE@HHABUTreeHintRef00217D4C@@@Z, retail 0x004F68FC, 34 bytes.
// Ctor for 12-byte holder (int +0, int +4, TargetRef* +8 with inline AddRef).
// Evidence: next row dtor 0x004F691E releases +8 via rowed fastcall 0x0007DEEF;
// Destroy stride 12 at 0x004F838C; callers at 0x004F9FE2 in 0x004F9F39.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};

struct Rva004F691E
{
	int m_00;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva004F691E(int a, int b, const TreeHintRef00217D4C &ref);
};

Rva004F691E::Rva004F691E(int a, int b, const TreeHintRef00217D4C &ref)
{
	m_00 = a;
	m_04 = b;
	m_08 = ref.m_ptr;
	if (m_08)
		++m_08->references;
}
