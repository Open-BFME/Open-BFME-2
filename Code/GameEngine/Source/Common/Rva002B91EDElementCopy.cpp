// cl: /O1 /EHs /MD
//
// ??0Rva002B91EDElement@@QAE@ABU0@@Z @0x002B90D6 103B: existing pin (copy
// constructor called by the rowed EH _Construct 0x002B91ED). 0x34-byte element:
// the unrowed copy constructor 0x002B72EC at +0, the
// rowed vector copy Rva002B55AE at +0xC (0x002B55AE) under EH state 0, then
// seven plain words +0x18..+0x30. Same layout as BfmeAssignRecord52 (rowed
// dtor 0x002B707E destroys Rva002B5558 at +0, op= 0x002B828A assigns it), so
// 0x002B72EC is pinned as the Rva002B5558 copy constructor and the unwind
// uses the rowed ~Rva002B5558.

class Rva002B5558
{
public:
	Rva002B5558(const Rva002B5558 &other);
	~Rva002B5558();

private:
	char m_pad[0xC];
};

class Rva002B55AE
{
public:
	Rva002B55AE(const Rva002B55AE &other);

private:
	char m_pad[0xC];
};

struct Rva002B91EDElement
{
	Rva002B91EDElement(const Rva002B91EDElement &other);

	Rva002B5558 m_00;
	Rva002B55AE m_0C;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
};

Rva002B91EDElement::Rva002B91EDElement(const Rva002B91EDElement &other) :
	m_00(other.m_00),
	m_0C(other.m_0C),
	m_18(other.m_18),
	m_1C(other.m_1C),
	m_20(other.m_20),
	m_24(other.m_24),
	m_28(other.m_28),
	m_2C(other.m_2C),
	m_30(other.m_30)
{
}
