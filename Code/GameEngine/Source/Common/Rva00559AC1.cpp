// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
// ?rva00559AC1@Rva00559AC1@@QAEHH@Z @0x00559AC1 27B: index search returning prior slot with 10 fallback.
// Evidence: unlock lane making 2 callers ready; callers pass same this and int arg with ret 4; no callees.
class Rva00559AC1
{
public:
	int rva00559AC1(int v);
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
