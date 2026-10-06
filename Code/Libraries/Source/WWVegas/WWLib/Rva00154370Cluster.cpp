// cl: /DNDEBUG /MD /EHsc
//
// Sibling of the rowed two-float set-if-changed body Rva00154320::rva00154320
// (Code/GameEngine/Source/Common/Rva00154320Cluster.cpp): the same
// "if (m_a != a || m_b != b) { store; return true; } return false;" shape at
// retail 0x00154370 (72 bytes) with its float pair at +0xBC/+0xC0 instead of
// the sibling's +0xB4/+0xB8. The movss/ucomiss/lahf shape is why /G7 and
// /arch:SSE are required. Address-derived class and method name; no original
// identity is claimed. It shares a cluster with 0x00154058 but not its flags.
//
//  0x00154370  ?rva00154370@Rva00154370@@QAE_NMM@Z   72B

class Rva00154370
{
public:
	bool rva00154370(float a, float b);

private:
	char _pad[0xbc];
	float m_a;
	float m_b;
};

bool Rva00154370::rva00154370(float a, float b)
{
	if (m_a != a || m_b != b)
	{
		m_a = a;
		m_b = b;
		return true;
	}
	return false;
}
