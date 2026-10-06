// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva004F6943@@QAE@ABUTreeHintRef00217D4C@@ABUInts004F6943@@@Z, retail 0x004F6943, 35 bytes.
// Ctor for 12-byte holder: pointer at +0 with inline AddRef at +4 plus ints
// at +4/+8 copied from 8-byte pair. Same layout as Rva004F6966 copy ctor at
// 0x004F6966 (ptr+0 AddRef plus ints +4/+8); prev copy ctor 0x004F692B ends
// exactly here, next copy ctor 0x004F6966 starts exactly at end.
// Evidence: mov eax ecx save plus ref deref test store je inc plus pair copy
// ret 8; callers at 0x004F97E6 0x004F9943 in FUN_008f971e.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};

struct Ints004F6943
{
	int m_00;
	int m_04;
};

struct Rva004F6943
{
	TargetRef00217D4C *m_00;
	int m_04;
	int m_08;
	Rva004F6943(const TreeHintRef00217D4C &ref, const Ints004F6943 &v);
};

Rva004F6943::Rva004F6943(const TreeHintRef00217D4C &ref, const Ints004F6943 &v)
{
	m_00 = ref.m_ptr;
	if (m_00 != 0)
		++m_00->references;
	m_04 = v.m_00;
	m_08 = v.m_04;
}
