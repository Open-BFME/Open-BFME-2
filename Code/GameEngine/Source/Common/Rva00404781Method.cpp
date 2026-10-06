// cl: /MD
// ?rva00404781@Rva00404781@@QAEXMHH@Z retail 0x00404781 77B
// Evidence: __thiscall float int int ret 0xC; touches +0x50[i] +0xA4 then +0[i] +0xA0; stride 0xA8 from caller 0x0056C4D3 imul; callers 0x00405180 0x0056C505
// ?rva0040475C@Rva00404781@@QAEXXZ retail 0x0040475C 37B
// Evidence: __thiscall zeroing m_a[20] m_b[20] m_flags0 m_flags1; same layout as 0x00404781; callers 0x00404AA8 0x00404B5B 0x0040553D 0x0056C1EB
class Rva00404781
{
public:
	void rva00404781(float v, int i, int j);
	void rva0040475C();
private:
	float m_a[20]; // +0x00
	float m_b[20]; // +0x50
	unsigned int m_flags0; // +0xA0
	unsigned int m_flags1; // +0xA4
};

void Rva00404781::rva00404781(float v, int i, int j)
{
	m_b[i] += v;
	m_flags1 |= (1u << i);
	if (i == j)
		return;
	m_a[j] += v;
	m_flags0 |= (1u << j);
}

void Rva00404781::rva0040475C()
{
	for (unsigned int i = 0; i < 20; ++i) {
		m_b[i] = 0.0f;
		m_a[i] = 0.0f;
	}
	m_flags1 = 0;
	m_flags0 = 0;
}
