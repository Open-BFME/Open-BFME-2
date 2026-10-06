// cl: /MD
// ?rva004DC082@Rva004DC082@@QAEXXZ 0x004DC082 20B unlock lane thiscall copies [ecx+0x6c] to [ecx+0xac] and [ecx+0x70]-1 to [ecx+0xb0]; caller 0x0028470E unclaimed
class Rva004DC082
{
public:
	void rva004DC082();
private:
	char m_pad0[0x6c];
	int m_6c;
	int m_70;
	char m_pad1[0x38];
	int m_ac;
	int m_b0;
};
void Rva004DC082::rva004DC082()
{
	m_ac = m_6c;
	m_b0 = m_70 - 1;
}
