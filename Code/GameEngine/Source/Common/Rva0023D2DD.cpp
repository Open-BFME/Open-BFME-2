// cl: /MD
// ?rva0023D2DD@Rva0023D2DD@@QAEXXZ, retail 0x0023D2DD, 50 bytes.
// Switch on dword at +0x114 storing to +0x110 (0->8, 1->1, 2->5).
// Evidence: leaf lane; caller 0x002BE697; sub/dec/dec chain is /O1 switch lowering.
class Rva0023D2DD
{
public:
	void rva0023D2DD();
private:
	char m_pad[0x110];
	int m_110;
	int m_114;
};
void Rva0023D2DD::rva0023D2DD()
{
	switch (m_114) {
	case 0:
		m_110 = 8;
		break;
	case 1:
		m_110 = 1;
		break;
	case 2:
		m_110 = 5;
		break;
	}
}
