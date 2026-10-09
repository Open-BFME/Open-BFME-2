// ?rva00559AF9@Rva00559AC1@@QAEMH@Z
// partial score=0.792683 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /arch:SSE
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
	int rva00559ADC(int v);
	float rva00559AF9(int v);
	const Image *rva00559C25(int side, int v);
	Rva00559AC1 *rva00559A76(int dummy);
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

// ?rva00559ADC@Rva00559AC1@@QAEHH@Z @0x00559ADC 29B: distance to the next
// rank threshold, returning zero once the search reaches its terminal slot.
// Evidence: adjacent body calls this object's rowed search and reads the same
// threshold array at +4; callers use the same this pointer and int argument.
int Rva00559AC1::rva00559ADC(int v)
{
	int idx = rva00559AC1(v);
	if (idx >= 10)
		return 0;
	return m_vals[idx + 1] - v;
}

const Image *Rva00559AC1::rva00559C25(int side, int v)
{
	int idx = rva00559AC1(v);
	return Rva00559B64GetImage(side, idx);
}

// ?rva00559A76@Rva00559AC1@@QAEPAV1@H@Z @0x00559A76 75B: rank threshold table init.
// Evidence: leaf with 2 callers; writes m_vals 11 ints matching search class; ret 4 unused arg.
Rva00559AC1 *Rva00559AC1::rva00559A76(int dummy)
{
	m_vals[0] = -1;
	m_vals[1] = 0;
	m_vals[10] = 1500;
	m_vals[9] = 800;
	m_vals[8] = 500;
	m_vals[7] = 300;
	m_vals[6] = 150;
	m_vals[5] = 50;
	m_vals[4] = 30;
	m_vals[3] = 10;
	m_vals[2] = 5;
	return this;
}

// Full native [00559AF9,00559B4B),82B RET4 and WB013FA240
// RankPointValue::PercentDoneUntilNextRank establish this role. The existing
// eleven-threshold owner remains address-derived. Its search preserves ECX;
// defining the dependency here gives MSVC the witnessed call summary.
// Endpoint ranks and degenerate intervals return zero; interior progress uses
// the two neighboring integer thresholds with target float precision.
float Rva00559AC1::rva00559AF9(int v)
{
 int rank=rva00559AC1(v);
 if(rank==0 || rank>=10)return 0.0f;
 float low=(float)m_vals[rank];
 float span=(float)m_vals[rank+1]-low;
 if(span<0.0001f)return 0.0f;
 return ((float)v-low)/span;
}
