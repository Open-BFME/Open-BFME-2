// bfmeGoUPB: look a value up in the UPB table and format it.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv1339.cpp); trimmed to the single T2
// body the sweep places. The donor's other body, GoUPC, is Lua's sized
// lua_newtable and lives in Code/Libraries/Source/Lua/lapi.c.


void *bfmeFindUPB(void *table, void *a);
void bfmeFormatUPB(void *r, char *out, void *c, const char *fmt);

class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *a, char *out, void *c);
	char m_bfmePad[0x10];
	void *m_bfmeTable;
};

char BfmeThingUPB::bfmeGoUPB(void *a, char *out, void *c)
{
	void *r = bfmeFindUPB(m_bfmeTable, a);
	if (!r) {
		*out = 0;
		return 0;
	}
	bfmeFormatUPB(r, out, c, (char *)"");
	return 1;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGetStrVJI@BfmeMsgVJI@@QAEDPBDPADH@Z=?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetStrVHC@BfmeMsgVHC@@QAEDPAXPADH@Z=?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeCallEMC@BfmeObjEMC@@QAEXPAX00@Z=?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeFillURC@BfmeSrcURC@@QAEDPAXPAD0@Z=?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetStrVJT@BfmeMsgVJT@@QAEDPBDPADH@Z=?bfmeGoUPB@BfmeThingUPB@@QAEDPAXPAD0@Z")
