// cl: /MD
// ?rva0025EB36@Rva0025EB36@@QAEXXZ at 0x0025EB36 (13B).
// Thiscall copying +0x48 to +0x28 and +0x4C to +0x2C. Evidence: retail moves,
// caller 0x0008D256, no vtable.

class Rva0025EB36
{
public:
	void rva0025EB36();
private:
	char m_pad00[0x28];
	int m_28;
	int m_2C;
	char m_pad30[0x18];
	int m_48;
	int m_4C;
};

void Rva0025EB36::rva0025EB36()
{
	m_28 = m_48;
	m_2C = m_4C;
}
