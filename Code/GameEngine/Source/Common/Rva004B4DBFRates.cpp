// cl: /MD /DNDEBUG
// ?rva004B4DBF@Rva004B4DBF@@QAEXPAM0@Z @0x004B4DBF 151B: thiscall with two float outs.
// Evidence: adjacent to 0x004B4DA3/0x004B4E56; call sites 0x004B506A and
// 0x004B515A; TheGameLogic+0x40 frame check, the 1.0f literal at 0x00BBB8D8
// and the g_00DBA4E8 int divisor.
// Structural inference: plain 1.0f divisions let the compiler keep the
// constant in xmm1 across both reciprocal stores, as retail does.

class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern int g_009BA4E8;

struct SubA004B4DBF
{
	char m_pad[0x148];
	float m_148;
	float m_14C;
	char m_gap150;
	unsigned char m_151;
};

struct SubB004B4DBF
{
	char m_pad[0x78];
	int m_78;
};

class Rva004B4DBF
{
public:
	void rva004B4DBF(float *p1, float *p2);
private:
	char m_pad0[4];
	SubA004B4DBF *m_a;
	SubB004B4DBF *m_b;
	char m_padC[0x1C - 0x0C];
	unsigned int m_1C;
};

void Rva004B4DBF::rva004B4DBF(float *p1, float *p2)
{
	SubA004B4DBF *a = m_a;
	if (a->m_151 != 0)
		return;
	SubB004B4DBF *b = m_b;
	if (b->m_78 == 0) {
		unsigned int v = m_1C + 3;
		if (TheGameLogic->m_frame < v)
			return;
	}
	if (a->m_148 != 0.0f)
		*p1 = 1.0f / a->m_148 / (float)g_009BA4E8;
	else
		*p1 = 0.0f;
	if (a->m_14C != 0.0f)
		*p2 = 1.0f / a->m_14C / (float)g_009BA4E8;
}
