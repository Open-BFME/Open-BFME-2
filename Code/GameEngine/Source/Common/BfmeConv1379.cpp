// Open-BFME5 conversions.
//
// Trimmed port of Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1379.cpp
// (near-miss donor). The AVIW/DVIW/EVIW trio served for BFME2 is carried
// here; the donor's B/C siblings are unserved so they stay out (the gate
// refuses unrowed definitions in a staged TU).
//
// WHAT THE BODY IS. A stdcall Fesl transaction-message filler: it snapshots
// the per-kind global, stamps the message kind dword, then adds its string
// fields through the matched Rva007E8810Message methods.

class BfmeMsgVIW
{
public:
	void bfmeRunVIW();
	void bfmeSetVIW(const char *k, void *v);
	void bfmeSet2VIW(const char *k, void *a, void *b);
	void bfmeSet3VIW(const char *k, int v);
	void bfmeSet4VIW(const char *k, void *v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

#include "../../Include/GameNetwork/Rva007E8810Message.h"

extern void *g_bfmeAVIW;
// g_bfmeAVIW: matched references place it at VA 0xe0a004 (zero-filled .bss).
void * g_bfmeAVIW;
extern void *g_bfmeBVIW;
// g_bfmeBVIW: matched references place it at VA 0xe0a01c (zero-filled .bss).
void * g_bfmeBVIW;
extern void *g_bfmeCVIW;
// g_bfmeCVIW: matched references place it at VA 0xe0a040 (zero-filled .bss).
void * g_bfmeCVIW;
extern void *g_bfmeDVIW;
// g_bfmeDVIW: matched references place it at VA 0xe09fe0 (zero-filled .bss).
void * g_bfmeDVIW;
extern void *g_bfmeEVIW;
// g_bfmeEVIW: matched references place it at VA 0xe09f04 (zero-filled .bss).
void * g_bfmeEVIW;

void __stdcall bfmeGoAVIW(BfmeMsgVIW *message, void *blobIdLowWord, void *blobIdHighWord)
{
	void *transactionName = g_bfmeAVIW;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addInt64("blobId", *(__int64 *)&blobIdLowWord);
}

// bfmeGoDVIW is the donor's D sibling: same blob category as AVIW plus a
// trailing int. The eight lotrbfme.exe fold-twins collapse by call-shape:
// retail 0x65DBE0 ends `ret 0x10` (4 args) with a Run/Set/Set2/Set3 call run
// at 0x655B50/0x655AA0/0x655F00/0x655960, which fits only the DVIW source
// (A/B/C/E take 3 args; the Rva007F3Ax0 _J-family takes int64 pairs).
// BFME1 donor b1 0x007F1050, 3 DIR32 string literals agree.
void __stdcall bfmeGoDVIW(BfmeMsgVIW *message, void *blobIdLowWord, void *blobIdHighWord, int rating)
{
	void *transactionName = g_bfmeDVIW;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addInt64("blobId", *(__int64 *)&blobIdLowWord);
	((Rva007E8810Message *)message)->addInt("rating", rating);
}

// Retail 0x6569E0 stamps 0x61636374 and calls Run/Set/Set4/Set4 at
// 0x655B50/0x655AA0/0x655A10 with the donor's own eaMailFlag and
// thirdPartyMailFlag words: the donor compiles unchanged. The earlier
// EVIW@0x656800 claim is corrected by this repoint -- that body pushes
// TXN/password/newPassword and calls one setter thrice, which is the VIT
// donor's shape, not this one (see BfmeConv1378.cpp).
void __stdcall bfmeGoEVIW(BfmeMsgVIW *message, void *eaMailFlag, void *thirdPartyMailFlag)
{
	void *transactionName = g_bfmeEVIW;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addBool("eaMailFlag", *(bool *)&eaMailFlag);
	((Rva007E8810Message *)message)->addBool("thirdPartyMailFlag", *(bool *)&thirdPartyMailFlag);
}

void __stdcall bfmeGoBVIW(BfmeMsgVIW *message, void *blobIdLowWord, void *blobIdHighWord)
{
	void *transactionName = g_bfmeBVIW;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addInt64("blobId", *(__int64 *)&blobIdLowWord);
}

void __stdcall bfmeGoCVIW(BfmeMsgVIW *message, void *blobIdLowWord, void *blobIdHighWord)
{
	void *transactionName = g_bfmeCVIW;
	((Rva007E8810Message *)message)->reset();
	message->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)message)->addString("TXN", (const char *)transactionName);
	((Rva007E8810Message *)message)->addInt64("blobId", *(__int64 *)&blobIdLowWord);
}
