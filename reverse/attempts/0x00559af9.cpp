// ?rva00559AF9@Rva00559AC1@@QAEMH@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD /arch:SSE
// ?rva00559AC1@Rva00559AC1@@QAEHH@Z @0x00559AC1 27B: index search returning prior slot with 10 fallback.
// Evidence: unlock lane making 2 callers ready; callers pass same this and int arg with ret 4; no callees.
extern const float BfmeZeroRange;
extern const float g_00BBB9B0;
class Rva00559AC1
{
public:
	int rva00559AC1(int v);
	float rva00559AF9(int v);
private:
	int m_vals[11];
};

int Rva00559AC1::rva00559AC1(int v)
{
	for (int i = 1; i < 11; ++i)
	{
		if (m_vals[i] > v)
			return i - 1;
	}
	return 10;
}

// ?rva00559AF9@Rva00559AC1@@QAEMH@Z @0x00559AF9 82B: fraction between table slots with zero-range fallback.
// Evidence: chain via just-landed 0x00559AC1 search; callers pass same this and int arg with ret 4; BfmeZeroRange and g_00BBB9B0 data refs.
#pragma optimize("y", off)
// ?rva00559AF9@Rva00559AC1@@QAEMH@Z present-unmatched
float Rva00559AC1::rva00559AF9(int v)
{
	int idx = rva00559AC1(v);
	if (idx == 0 || idx >= 10)
		return BfmeZeroRange;
	float a = (float)m_vals[idx];
	float diff = (float)m_vals[idx + 1] - a;
	if (g_00BBB9B0 > diff)
		return BfmeZeroRange;
	return ((float)v - a) / diff;
}
#pragma optimize("y", on)
