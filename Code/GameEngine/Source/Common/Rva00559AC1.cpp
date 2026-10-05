// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
// ?rva00559AC1@Rva00559AC1@@QAEHH@Z @0x00559AC1 27B: index search returning prior slot with 10 fallback.
// Evidence: unlock lane making 2 callers ready; callers pass same this and int arg with ret 4; no callees.
// ?rva00559C25@Rva00559AC1@@QAEPBVImage@@HH@Z @0x00559C25 24B: side+value to rank icon via search then GetImage.
// Evidence: chain via just-landed 0x00559AC1 search; calls rowed 0x00559AC1 thiscall and rowed 0x00559B64 cdecl GetImage; 4 callers; ret 8.
class Image;
const Image *__cdecl Rva00559B64GetImage(int side, int rank);
class Rva00559AC1
{
public:
	int rva00559AC1(int v);
	const Image *rva00559C25(int side, int v);
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

const Image *Rva00559AC1::rva00559C25(int side, int v)
{
	int idx = rva00559AC1(v);
	return Rva00559B64GetImage(side, idx);
}
