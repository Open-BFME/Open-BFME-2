// cl: /MD
//
// ??4Rva005F8536@@QAEAAU0@ABU0@@Z @0x005F8536 33B.
// Evidence: unlock lane; two TreeHintRef00217D4C copies via rowed 0x002174A4;
// caller 0x005F8573 stride-8 copy loop; returns this with ret 4.

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	void *m_ptr;
};

struct Rva005F8536
{
	TreeHintRef00217D4C m_00;
	TreeHintRef00217D4C m_04;
	Rva005F8536 &operator=(const Rva005F8536 &other);
};

Rva005F8536 &Rva005F8536::operator=(const Rva005F8536 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	return *this;
}
