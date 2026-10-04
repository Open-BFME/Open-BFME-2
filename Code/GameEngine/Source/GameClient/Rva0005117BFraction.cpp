// ?rva0005117B@Rva0005117B@@QAEMM@Z
// partial score=0.96 date=2026-09-30
// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG
// ?rva0005117B@Rva0005117B@@QAEMM@Z @0x0005117B 72B: clamp 1-v/denom to [0,1]
// Evidence: callers 0x0005AA24 0x0005F715 0x0005F766 0x0005F91E; global 1.0f g_Va00BBB8D8.
extern float g_Va00BBB8D8;

struct Rva0005117BRef
{
	char m_pad[0x78];
	int m_78;
};

class Rva0005117B
{
public:
	float rva0005117B(float v);
	char m_lead[0x10];
	Rva0005117BRef *m_10;
};

// Clamp 1 - v / count to [0, 1]. Retail stores 1 and keeps it when the
// value exceeds 1 (comiss value, 1; ja), which the three-way if/else
// reproduces; the banked `1 >= f` form swapped the comiss operands.
float Rva0005117B::rva0005117B(float v)
{
	float f = 1.0f - v / (float)m_10->m_78;
	if (f < 0.0f)
		v = 0.0f;
	else if (f > 1.0f)
		v = 1.0f;
	else
		v = f;
	return v;
}
