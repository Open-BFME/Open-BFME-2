// cl: /DNDEBUG /MD
// ?rva001D982B@Rva001D982B@@QAE_NXZ @0x001D982B 60B unlock.
// Evidence: leaf predicate; +0xB0 type check plus +0x34 zero check plus +0x4C flag
// plus three pair compares; callers 0x0006204A 0x00062182 in 0x00061E37;
// neighbour Rva001D98BD shares +0xB0 type field and /O1 flags.
class Rva001D982B
{
public:
	bool rva001D982B();
private:
	unsigned char m_pad00[0x34];
	int m_34;
	unsigned char m_pad38[0x4C - 0x38];
	unsigned char m_4C;
	unsigned char m_pad4D[0x50 - 0x4D];
	int m_50;
	int m_54;
	unsigned char m_pad58[0x60 - 0x58];
	int m_60;
	int m_64;
	unsigned char m_pad68[0x70 - 0x68];
	int m_70;
	int m_74;
	unsigned char m_pad78[0xB0 - 0x78];
	int m_B0;
};

bool Rva001D982B::rva001D982B()
{
	if (m_B0 != 2)
		goto Fail;
	int n = 0;
	if (m_34 != 0)
		goto Fail;
	if (m_4C & 1)
		goto Succeed;
	if (m_50 != m_54)
		++n;
	if (m_60 != m_64)
		++n;
	if (m_70 != m_74)
		++n;
	if (n >= 2)
		goto Succeed;
Fail:
	return false;
Succeed:
	return true;
}
