// cl: /Ob0
// ??0Rva004F692B@@QAE@ABU0@@Z, retail 0x004F692B, 24 bytes.
// Copy ctor for 8-byte holder: pointer at +0 with inline AddRef at +4 plus
// int at +4 zeroed (not copied). Evidence: mov eax ecx then copy ptr test
// inc and [eax+4] 0 ret 4; single caller at 0x004F9819 in FUN_008f971e.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004F692B
{
	TargetRef00217D4C *m_00;
	int m_04;
	Rva004F692B(const Rva004F692B &other);
};

Rva004F692B::Rva004F692B(const Rva004F692B &other)
{
	m_00 = other.m_00;
	if (m_00)
		++m_00->references;
	m_04 = 0;
}
