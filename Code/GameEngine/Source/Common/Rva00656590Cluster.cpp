// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Single-key 'acct' setup writers. Same one-argument shape as the rowed
// bfmeSetupPair_00656490 family (Bfme5SetupPairs.cpp), minus the second key:
// begin, tag 'acct', write the pair's own TXN global under "TXN". Retail 44B
// each; the DIR32 operand is the only per-member difference.
// TheBfmeSetupGlobal<rva>: zero-filled .bss, referenced by no other unit.

struct BfmeSetupRecord
{
	void bfmeBegin(void);				// retail 0x00655B50
	void bfmeWrite(const char *text, int value);	// retail 0x00655AA0

	char m_bfmeHead[0x1C];
	unsigned int m_bfmeTag;				// +0x1C
};

extern int TheBfmeSetupGlobal00656590;
int TheBfmeSetupGlobal00656590;

void __stdcall Rva00656590(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal00656590;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}

extern int TheBfmeSetupGlobal006565C0;
int TheBfmeSetupGlobal006565C0;

void __stdcall Rva006565C0(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal006565C0;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}

extern int TheBfmeSetupGlobal00656890;
int TheBfmeSetupGlobal00656890;

void __stdcall Rva00656890(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal00656890;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}

extern int TheBfmeSetupGlobal006568C0;
int TheBfmeSetupGlobal006568C0;

void __stdcall Rva006568C0(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal006568C0;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}

extern int TheBfmeSetupGlobal00656980;
int TheBfmeSetupGlobal00656980;

void __stdcall Rva00656980(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal00656980;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}

extern int TheBfmeSetupGlobal006569B0;
int TheBfmeSetupGlobal006569B0;

void __stdcall Rva006569B0(BfmeSetupRecord *record)
{
	int value = TheBfmeSetupGlobal006569B0;

	record->bfmeBegin();
	record->m_bfmeTag = 0x61636374;			// 'acct'
	record->bfmeWrite("TXN", value);
}
