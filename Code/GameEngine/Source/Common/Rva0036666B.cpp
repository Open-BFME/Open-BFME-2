// cl: /MD
// ?rva0036666B@Rva0036666B@@QAE_NXZ 0x0036666B 16B via two-dword non-zero check at +0x34/+0x38
// Evidence: retail xor/cmp/jne/cmp/je/xor/inc shape; callers test al (e.g. 0x002E71D4 test al al); neighbours in Code/GameEngine/Source/Common.

class Rva0036666B
{
public:
	char m_pad[0x34];
	int m_a;
	int m_b;
	bool rva0036666B();
};

bool Rva0036666B::rva0036666B()
{
	return m_a != 0 || m_b != 0;
}
