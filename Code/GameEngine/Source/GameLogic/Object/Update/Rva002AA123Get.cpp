// cl: /DNDEBUG /MD
// ?rva002AA123@Rva002AA123@@QAEHH@Z 0x002AA123 42B
// Maps 1->+0xAC 2->+0xB0 3->+0xB4 else 0.
// Evidence: callers 0x273A30 0x273ADB 0x273B8C.
class Rva002AA123
{
	char m_pad[0xAC];
	int m_ac;
	int m_b0;
	int m_b4;
public:
	int rva002AA123(int which);
};

int Rva002AA123::rva002AA123(int which)
{
	switch (which) {
	case 1:
		return m_ac;
	case 2:
		return m_b0;
	case 3:
		return m_b4;
	default:
		return 0;
	}
}
