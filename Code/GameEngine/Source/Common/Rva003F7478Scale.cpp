// cl: /MD
// ?rva003F7478@Rva003F7478@@QAEXM@Z @0x003F7478 40B
// Conditional scale of the +0x24 float by g_Va00BBB8D8/arg when arg exceeds
// BfmeZeroRange. Evidence: rowed-adjacent SSE sibling Rva003F74A0Mul at
// 0x003F74A0; externs BfmeZeroRange and g_Va00BBB8D8 named by packet;
// callers at 0x002BCADF and 0x003F220D.
extern const float BfmeZeroRange;
extern float g_Va00BBB8D8;

class Rva003F7478
{
	char m_pad[0x24];
	float m_float24;
public:
	void rva003F7478(float f);
};

void Rva003F7478::rva003F7478(float f)
{
	if (f > BfmeZeroRange)
	{
		float t = g_Va00BBB8D8 / f;
		m_float24 *= t;
	}
}
