class BfmeS1019
{
public:
	virtual void bfmeVS01019(void);
	virtual void bfmeVS11019(void);
	virtual void *bfmeDoB1019(int a, int b);
	virtual void bfmeDoC1019(int a, int b);
};

extern class GenAlloc *g_genAlloc;
void bfmeInit1019(char *name);

// ?bfmeGo1019C@@YAXH@Z
void bfmeGo1019C(int a)
{
	if ((*(BfmeS1019 **)&g_genAlloc) == 0)
		bfmeInit1019((char *)"no FESL allocator defined\n");

	(*(BfmeS1019 **)&g_genAlloc)->bfmeDoC1019(a, 0);
}

// Callers elsewhere reach bodies in this unit through spellings pinned to the same
// retail address (same cdecl/thiscall ABI); bind them here.
#pragma comment(linker, "/alternatename:_Rva007F0030=?bfmeGo1019C@@YAXH@Z")
#pragma comment(linker, "/alternatename:?Rva007F0030Free@@YAXPAX@Z=?bfmeGo1019C@@YAXH@Z")

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeInit1019@@YAXPAD@Z=?ji_00629b14@@YAXXZ")
