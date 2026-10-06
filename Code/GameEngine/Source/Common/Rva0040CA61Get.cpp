// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?ComputePlayerEarnedSpellPoints@ArmySummarySystem@@QAEHPAU_Rva0040CA61Arg@@@Z, retail 0x0040CA61, 55 bytes.
// Free __stdcall sum of RankInfo m_34 over 1..m_1C via TheRankInfoStore get.
// Evidence: null-check via eax reuse, inc/xor /O1 idioms, TheRankInfoStore
// global VA 0xDFE0EC, pinned get 0x002000D7, callers 0x0040F19D 0x0040F87E.

struct Rva002000D7Config
{
	int m_pad[0x34 / 4];
	int m_34;
};

class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int v);
};

class RankInfoStore;
extern RankInfoStore *TheRankInfoStore;

struct _Rva0040CA61Arg
{
	int m_pad[7];
	int m_1C;
};

class ArmySummarySystem
{
public:
	int ComputePlayerEarnedSpellPoints(_Rva0040CA61Arg *a);
};

int ArmySummarySystem::ComputePlayerEarnedSpellPoints(_Rva0040CA61Arg *a)
{
	if (!a)
		return 0;
	int n = a->m_1C;
	int total = 0;
	for (int i = 1; i <= n; ++i) {
		Rva002000D7Config *cfg = ((Rva002000D7Store *)TheRankInfoStore)->get(i);
		if (cfg)
			total += cfg->m_34;
	}
	return total;
}
