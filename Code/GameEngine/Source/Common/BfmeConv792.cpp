// A flag-gated unlock that clears itself (trimmed from a five-body donor;
// the other four are declared-only here).
//
// The donor names the import bfmeDoDWH, but the retail body reaches the real
// mss32.dll!_AIL_unlock_mutex@0, so the declaration names the real import
// (MSVC adds the leading underscore for __stdcall).

extern "C" __declspec(dllimport) void __stdcall AIL_unlock_mutex();

struct BfmeThingDWH
{
	void bfmeGoDWH();
    void rva00050E62();
	char m_bfmeFlag;
};

// ?bfmeGoDWH@BfmeThingDWH@@QAEXXZ
void BfmeThingDWH::bfmeGoDWH()
{
	if (m_bfmeFlag)
	{
		AIL_unlock_mutex();
		m_bfmeFlag = 0;
	}
}

struct BfmeThingDWJ
{
	void bfmeGoDWJ();
	unsigned char m_bfmeHead[0x4e0c];
	char m_bfmeFlag;
};

void bfmeGoDWI();

char bfmeGoDWK(const char *s);

struct BfmeThingDWL
{
	void *bfmeGoDWL(void *a);
	void *m_bfmeVft;
};

// Whole BFME1 source lead: 5cc75ddda6455c338a5068307e587a793f96d6b3,
// game/GameEngine/Source/Common/BfmeConv829.cpp. Its freeStr/dllimport-member
// identities do not describe the target import. Retail50E62/12 tests the same
// first-byte guard as the existing50E6E unlock-and-clear sibling, and when set
// tail-calls mss32.dll!_AIL_unlock_mutex@0 through BBAAC0. The import descriptor
// and existing C-linkage __stdcall declaration establish the actual callee ABI.
// Ghidra independently bounds50E62/12 between the16-byte initializer50E52 and
// the19-byte sibling50E6E. Reuse this home's byte-guard view without claiming
// an original class, destructor, field type beyond its bits, or full lifetime.
void BfmeThingDWH::rva00050E62()
{
    if (m_bfmeFlag) AIL_unlock_mutex();
}
