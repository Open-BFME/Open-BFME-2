// cl: /MD
// ??4BfmeAssignRecord32@@QAEAAU0@ABU0@@Z at 0x00173499 (56B). Copy-assign 32B record.
// Evidence: pinned name; Rva00072A94 assign 0x72A94 for +0 plus loop 6 at +8;
// dword at +4; callers include copy_backward plus fill plus linear_insert.
class Rva00072A94 {
	unsigned char m_data[4];
public:
	Rva00072A94 &operator=(const Rva00072A94 &o);
};

struct BfmeAssignRecord32 {
	class Rva00072A94 m_00;
	unsigned int m_04;
	class Rva00072A94 m_08[6];
	BfmeAssignRecord32 &operator=(const BfmeAssignRecord32 &o);
};

struct BfmeAssignRecord32 &BfmeAssignRecord32::operator=(const struct BfmeAssignRecord32 &o)
{
	m_00 = o.m_00;
	m_04 = o.m_04;
	for (int i = 0; i < 6; ++i)
		m_08[i] = o.m_08[i];
	return *this;
}
