// cl: /MD
// ?rva005D3FE4@Rva005D3FE4@@QAEXM@Z @0x005D3FE4 28B
// Evidence: unlock; float setter at +0x38 with flag clear at +0x3C bit4;
// abuts prev 0x005D3FBD same flags byte; callers 0x0057B122 0x0057B2F6 0x0057B368 0x0057B443
class Rva005D3FE4
{
public:
	void rva005D3FE4(float v);
private:
	char m_pad[0x38];
	float m_val38;
	unsigned char m_flags3C;
};

void Rva005D3FE4::rva005D3FE4(float v)
{
	if (v != m_val38) {
		m_flags3C = (unsigned char)(m_flags3C & 0xEF);
		m_val38 = v;
	}
}
