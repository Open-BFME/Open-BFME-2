// ?rva00051525@Rva00051525@@QAE_NXZ
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00051525@Rva00051525@@QAE_NXZ @ 0x00051525 57B
// Evidence: __thiscall via ecx plus ret no stack args; +0xBF0 range 1-5 check;
// TheGameLODManager null check plus +0x1770 index plus +0x21C byte table with
// stride 8; callers 0x000605A9 plus 0x00060828; neighbour Rva000514EBDec TU
// flags /O1. The null-check guard must carry an explicit else block: without
// it MSVC merges the three `return true` sites into one tail placed after the
// body (je-to-tail); with it the shared true block stays between the guard and
// the body (jne-to-body), which is retail.
class GameLODManager
{
public:
	char m_pad21C[0x21C];
	struct LODFlag
	{
		unsigned char flag;
		char m_pad[7];
	};
	LODFlag m_flags[2];
	char m_padAfter[0x1770 - (0x21C + 16)];
	int m_idx1770;
};

extern GameLODManager *TheGameLODManager;

class Rva00051525
{
public:
	bool rva00051525();

private:
	char m_pad[0xBF0];
	int m_valBF0;
};

bool Rva00051525::rva00051525()
{
	int v = m_valBF0;
	if (v <= 0 || v > 5)
		return false;
	GameLODManager *mgr = TheGameLODManager;
	if (mgr == 0)
		return true;
	else {
		int idx = mgr->m_idx1770;
		if (idx < 0 || idx >= 2)
			return true;
		return mgr->m_flags[idx].flag;
	}
}
