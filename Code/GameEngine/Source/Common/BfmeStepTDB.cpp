// cl: /O2 /G7 /DNDEBUG /MD
// Open-BFME5 conversions.
//
// ?bfmeStepTDB@@YAXXZ, retail 0x0011DC20 (58B). Called once by the rowed
// bfmeGoTDB in BfmeConv1309.cpp. The bfme1 sweep maps that call to BFME1
// 0x904720 where bfmeApplyBQ and bfmeStepTDB are ICF twins, so this
// transcribes reference/open-bfme-1/Code/GameEngine/Source/Common/
// BfmeConv1753.cpp bfmeApplyBQ with BQ names swapped for TDB ones.
//
// The dispatch table type mirrors BfmeConv1309.cpp BfmeCallsTDB: slot 89
// is the set operation (slot 92 is the run operation rowed through
// GoTDB). The /G7 P4 tuning is load-bearing: it emits the retail
// cmp-byte-imm and add-mem-imm forms where /O1-/O2/G6 use test and inc.

struct BfmeObjTDB;

struct BfmeCallsTDB
{
	void *m_bfmeSlot89[89];
	void (__stdcall *m_bfmeSetTDB)(BfmeObjTDB *owner, void *item);
};

struct BfmeObjTDB
{
	BfmeCallsTDB *m_bfmeCalls;
};

struct BfmeStateTDB
{
	unsigned char m_bfmeHeadTDB[0x14];
	void **m_bfmeSourceTDB;
	char m_bfmeBusyTDB;
};

extern BfmeStateTDB *g_bfmeStateTDB;
extern int g_bfmeModeTDB;
extern BfmeObjTDB *g_bfmeObjTDB;
extern int g_bfmeCountTDB;

// ?bfmeStepTDB@@YAXXZ
void bfmeStepTDB(void)
{
	if (g_bfmeStateTDB == 0)
		return;

	if (g_bfmeModeTDB != 0 && g_bfmeModeTDB != 2)
		return;

	if (g_bfmeStateTDB->m_bfmeBusyTDB)
		return;

	g_bfmeObjTDB->m_bfmeCalls->m_bfmeSetTDB(g_bfmeObjTDB,
		*g_bfmeStateTDB->m_bfmeSourceTDB);

	++g_bfmeCountTDB;
}
