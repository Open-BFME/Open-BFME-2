// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BB700@@YGX_N@Z @0x003BB700 19B: free stdcall setter of
// TheGameLogic's byte at +0x98 (the flag Rva0039B683 gates on).
// Target evidence: TheGameLogic is the global at 0x00DFE78C; with the real
// extern the compiler loads the argument first as retail does (the banked
// attempt read the global through a literal-address macro).
class GameLogic
{
public:
	char m_pad00[0x98];
	bool m_flag98; // +0x98
};

extern GameLogic *TheGameLogic;

void __stdcall Rva003BB700(bool v)
{
	TheGameLogic->m_flag98 = v;
}
