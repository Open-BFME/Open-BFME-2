// cl: /Ob0
// ??4Rva004F6352@@QAEAAU0@ABU0@@Z, retail 0x004F6352, 35 bytes.
// 12-byte struct copy-assign: two dwords at +0/+4 plus TreeHintRef at +8 via
// rowed operator= 0x002174A4 then return this. Evidence: stride 0xC in callers
// 0x004F6C32 (idiv 0xC loop) and 0x004F6876; EH callers 0x004F6EB1 0x004F7022
// 0x004F6E62 all call this then ReleaseTreeHint; prev 0x004F62FE set pattern
// in Rva00468520Set.cpp; callee rowed TreeHintRef00217D4C::operator=.

// ??0Rva004F6352@@QAE@ABU0@@Z, retail 0x004F62DE, 32 bytes.
// Copy ctor for same 12-byte struct: two dwords at +0/+4 plus TreeHintRef at +8
// via inline AddRef at +4. Evidence: callers 0x004F6A76 wrapper and 0x004F6E62
// local at ebp-0x18 with release at ebp-0x10 via rowed 0x0007DEEF; same layout
// as rowed assign 0x004F6352 and rowed TreeHintRef assign 0x002174A4.

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

struct Rva004F6352
{
	int m_00;
	int m_04;
	TreeHintRef00217D4C m_08;

	Rva004F6352(const Rva004F6352 &other);
	Rva004F6352 &operator=(const Rva004F6352 &other);
};

Rva004F6352::Rva004F6352(const Rva004F6352 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08.m_ptr = other.m_08.m_ptr;
	if (m_08.m_ptr)
		++m_08.m_ptr->references;
}

Rva004F6352 &Rva004F6352::operator=(const Rva004F6352 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}
