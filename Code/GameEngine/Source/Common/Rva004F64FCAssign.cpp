// cl: /Ob0
// ??4Rva004F64FC@@QAEAAU0@ABU0@@Z, retail 0x004F64FC, 33 bytes.
// 12-byte struct copy-assign: TreeHintRef at +0 via rowed operator= 0x002174A4 then ints at +4/+8 then return this.
// Evidence: callers at 0x004F6C9B 0x004F6CBA 0x004F6DC0 0x004F6DE3 0x004F729E; prev assign 0x004F6352 /O1 /Ob0 next dtor 0x004F691E /O1.

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

struct Rva004F64FC
{
	TreeHintRef00217D4C m_00;
	int m_04;
	int m_08;

	Rva004F64FC &operator=(const Rva004F64FC &other);
};

Rva004F64FC &Rva004F64FC::operator=(const Rva004F64FC &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}
