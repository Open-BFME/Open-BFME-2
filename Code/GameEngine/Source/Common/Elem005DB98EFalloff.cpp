// cl: /MD
// ?rva005DB928@Elem005DB98E@@QAEMXZ @0x005DB928 51B, caller 0x005DB96B (same
// this as 0x005DB95B). Falloff: 0 when m_08 <= 1, else
// max(m_08 - m_0C - 1, 0) / m_08.
// Target evidence: SSE comiss of the pooled 1.0 at 0x00BBB8D8 against +0x08,
// pooled 0.0 at 0x00BBAEAC on the low path, x87 subtract chain with the
// float memory operand 1.0 (fsub dword, so the 1.0 is the established
// g_Va00BBB8D8 global rather than a literal folded to double), fldz/fcomip
// clamp, then fdiv by +0x08.
// Structural inference: the clamp runs in double and the quotient divides
// the float-converted value, which keeps the fdiv memory form as retail.
//
// ?rva005DB95B@Elem005DB98E@@QAEMXZ @0x005DB95B 51B, callers 0x005A03B4,
// 0x005A7067 and 0x005A70E8: -1 when m_08 <= 0 (SSE comiss against zero,
// pooled -1.0 at 0x00BBB9AC), else with f = rva005DB928() the quadratic
// ((m_04 + 4000) * f + (m_04 + 2000)) * f + m_04 in x87 (pooled 4000.0 at
// 0x00C767D8 and 2000.0 at 0x00BC897C). Retail keeps this in ecx across the
// rva005DB928 call, which cl only does when that callee was compiled earlier
// in the same TU.
extern float g_Va00BBB8D8;

struct Elem005DB98E
{
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	unsigned long m_10;
	char m_14[4];
public:
	float rva005DB928();
	float rva005DB95B();
	float rva005A66BF();
};

float Elem005DB98E::rva005DB928()
{
	if (m_08 <= g_Va00BBB8D8)
		return 0.0f;
	double t = (double)m_08 - (double)m_0C - (double)g_Va00BBB8D8;
	if (t < 0.0)
		t = 0.0;
	return (float)t / m_08;
}

float Elem005DB98E::rva005DB95B()
{
	if (m_08 <= 0.0f)
		return -1.0f;
	float f = rva005DB928();
	return ((m_04 + 4000.0f) * f + (m_04 + 2000.0f)) * f + m_04;
}
float Elem005DB98E::rva005A66BF()
{
	int v;
	if (m_08 > 0.0f && m_04 > 0.0f)
		v = 1;
	else
		v = 0;
	return (float)v;
}
