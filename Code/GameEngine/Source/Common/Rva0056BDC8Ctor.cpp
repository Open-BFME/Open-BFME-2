// cl: /O1 /MD
// ??0Rva0056BDC8@@QAE@PAX@Z @0x0056BDC8 52B. Ctor via pinned 0x0056B7E4 init plus vtable 0x00C37898 plus 1 at +0x58 plus 2 at +0x5C plus zeros at +0x60..0x63. Evidence: same vtable as Rva00402F28Item 0x0056BEFB sibling plus same base init plus caller 0x0056BE83 in 0x0056BDFC parse plus unlocks 0x0056BDFC.
class Rva0056B7E4
{
public:
	void rva0056B7E4(void *arg);
};

extern const void *const g_00C37898[];

class Rva0056BDC8
{
public:
	Rva0056BDC8(void *arg);

private:
	char m_pad[0x58];
	unsigned m_58;
	unsigned m_5C;
	unsigned char m_60;
	unsigned char m_61;
	unsigned char m_62;
	unsigned char m_63;
};

Rva0056BDC8::Rva0056BDC8(void *arg)
{
	((Rva0056B7E4 *)this)->rva0056B7E4(arg);
	m_60 = 0;
	m_61 = 0;
	m_62 = 0;
	m_63 = 0;
	*(unsigned int *)this = (unsigned int)g_00C37898;
	m_58 = 1;
	m_5C = 2;
}
