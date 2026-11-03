// Trimmed port of reference/open-bfme-1/Code/GameEngine/Source/Common/
// Bfme5SetupPairs.cpp: only the 007E9860 stub is carried; sibling stubs stay
// with the donor until rows land.

struct BfmeSetupRecord
{
	void bfmeBegin(void);					// retail 0x00655B50
	void bfmeWrite(const char *text, int value);		// retail 0x00655AA0
	void bfmeWriteAlt(const char *text, int value);		// retail 0x00655960

	char m_bfmeHead[0x1C];
	unsigned int m_bfmeTag;					// +0x1C
};

extern int TheBfmeSetupGlobal007E9860;
// TheBfmeSetupGlobal007E9860: matched references place it at VA 0xe09ebc (zero-filled .bss).
int TheBfmeSetupGlobal007E9860;
extern int TheBfmeSetupGlobal007F26A0;
// TheBfmeSetupGlobal007F26A0: matched references place it at VA 0xe0a0d0 (zero-filled .bss).
int TheBfmeSetupGlobal007F26A0;

// ?bfmeSetupPair_007E9860@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007E9860(BfmeSetupRecord *record, int accountNameValue)
{
	int transactionValue = TheBfmeSetupGlobal007E9860;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("name", accountNameValue);
}

// ?bfmeSetupPair_007F26A0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_007F26A0(BfmeSetupRecord *record, int reporterCount)
{
	int transactionValue = TheBfmeSetupGlobal007F26A0;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWriteAlt("numberOfReporters", reporterCount);
}

// Three more 'acct' setup pairs, identical in code to bfmeSetupPair_007E9860
// above but each reading its own TXN global. bfme1_sweep places that donor body
// at all four addresses; the DIR32 operand separates them. The globals are
// zero-filled .bss that no other unit references. Names are this image's
// addresses.
// TheBfmeSetupGlobal00656490: VA 0x00e09ef8 (zero-filled .bss).
int TheBfmeSetupGlobal00656490;

// ?bfmeSetupPair_00656490@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_00656490(BfmeSetupRecord *record, int accountNameValue)
{
	int transactionValue = TheBfmeSetupGlobal00656490;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("name", accountNameValue);
}

// TheBfmeSetupGlobal006564D0: VA 0x00e09f34 (zero-filled .bss).
int TheBfmeSetupGlobal006564D0;

// ?bfmeSetupPair_006564D0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_006564D0(BfmeSetupRecord *record, int accountNameValue)
{
	int transactionValue = TheBfmeSetupGlobal006564D0;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("name", accountNameValue);
}

// TheBfmeSetupGlobal00656550: VA 0x00e09f1c (zero-filled .bss).
int TheBfmeSetupGlobal00656550;

// ?bfmeSetupPair_00656550@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_00656550(BfmeSetupRecord *record, int accountNameValue)
{
	int transactionValue = TheBfmeSetupGlobal00656550;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("name", accountNameValue);
}

// Three more builders of the same shape, each over its own TXN global (zero-filled
// .bss, unreferenced elsewhere); tag and second key read from retail.

// TheBfmeSetupGlobal00656510: VA 0x00e09f40 (zero-filled .bss).
int TheBfmeSetupGlobal00656510;

// ?bfmeSetupPair_00656510@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_00656510(BfmeSetupRecord *record, int emailValue)
{
	int transactionValue = TheBfmeSetupGlobal00656510;

	record->bfmeBegin();

	record->m_bfmeTag = 0x61636374;					// 'acct'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("email", emailValue);
}

// TheBfmeSetupGlobal0065F1D0: VA 0x00e0a064 (zero-filled .bss).
int TheBfmeSetupGlobal0065F1D0;

// ?bfmeSetupPair_0065F1D0@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_0065F1D0(BfmeSetupRecord *record, int sessionID)
{
	int transactionValue = TheBfmeSetupGlobal0065F1D0;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("sessionId", sessionID);
}

// TheBfmeSetupGlobal0065F210: VA 0x00e0a070 (zero-filled .bss).
int TheBfmeSetupGlobal0065F210;

// ?bfmeSetupPair_0065F210@@YGXPAUBfmeSetupRecord@@H@Z
void __stdcall bfmeSetupPair_0065F210(BfmeSetupRecord *record, int sessionID)
{
	int transactionValue = TheBfmeSetupGlobal0065F210;

	record->bfmeBegin();

	record->m_bfmeTag = 0x72616E6B;					// 'rank'

	record->bfmeWrite("TXN", transactionValue);
	record->bfmeWrite("sessionId", sessionID);
}
