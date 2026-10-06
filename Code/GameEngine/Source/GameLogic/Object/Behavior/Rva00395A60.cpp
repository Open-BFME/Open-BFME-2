// cl: /MD

// ?rva00395A60@Rva00395A60@@QAEMXZ @0x00395A60 34B
// Unlock: ptr at +4 with float at +0x2C or 0.0. Uses SSE movss.
// Prev/next are CastleMemberBehavior TUs. No EH.

struct RvaInner2C
{
	char _pad[0x2c];
	float m_2c;
};

class Rva00395A60
{
	char _pad0[4];
	RvaInner2C *m_04;
public:
	float rva00395A60();
};

float Rva00395A60::rva00395A60()
{
	float t = 0.0f;
	if (m_04)
		t = m_04->m_2c;
	return t;
}
