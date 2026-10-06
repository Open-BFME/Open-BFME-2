// cl: /MD
// ?rva003F7478@Rva003F7478@@QAEXM@Z @0x003F7478 40B
// Conditional scale of the +0x24 float by g_Va00BBB8D8/arg when arg exceeds
// BfmeZeroRange. Evidence: rowed-adjacent SSE sibling Rva003F74A0Mul at
// 0x003F74A0; externs BfmeZeroRange and g_Va00BBB8D8 named by packet;
// callers at 0x002BCADF and 0x003F220D.
// The data ledger identifies the shared read-only operand as float +0.0.
extern float g_Va00BBB8D8;

class Rva003F7478
{
	char m_pad[0x20];
	float m_float20;
	float m_float24;
public:
	void rva003F7465(float f);
	void rva003F7478(float f);
};

// ?rva003F7465@Rva003F7478@@QAEXM@Z @0x003F7465 19B.
// Unconditional scale of the +0x20 float. Same class as rowed 0x003F7478.
// Evidence: retail movss mulss movss ret4 plus callers 0x002BCAB9 0x003F21FF.
void Rva003F7478::rva003F7465(float f)
{
	m_float20 *= f;
}

void Rva003F7478::rva003F7478(float f)
{
	if (f > 0.0f)
	{
		float t = g_Va00BBB8D8 / f;
		m_float24 *= t;
	}
}
