// platformsdk
// BfmeThingDXB::bfmeGoDXB, retail 0x00628D20 (22B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv793.cpp
// (BFME1 0x009F69D3). Only the placed go is defined here; the donor's
// DXC/DXD/DXE/DXF helpers stay out, so the unmatched-definition gate passes.
// Retail inits the CS struct through the dllimport slot, then tail-jumps to
// the pinned sub call.

#include <windows.h>

#include "../../Include/Common/Rva009F68C6PointerArray.h"

struct BfmeThingDXB
{
	void bfmeGoDXB();
	unsigned char m_bfmeHead[0x18];
	CRITICAL_SECTION m_bfmeCs;
	Rva009F68C6PointerArray m_bfmeSub;
};

// ?bfmeGoDXB@BfmeThingDXB@@QAEXXZ, retail 0x00628D20 (22B).
void BfmeThingDXB::bfmeGoDXB()
{
	DeleteCriticalSection(&m_bfmeCs);
	m_bfmeSub.RemoveAll();
}

// The 16-byte x86 VARIANTARG passed to VariantClear: VT_ERROR (0x000A) with
// error value 0x80020004, matching retail .data at VA 0x00DD7F18.
unsigned char vtMissing[16] = {
	0x0A, 0, 0, 0, 0, 0, 0, 0,
	0x04, 0, 0x02, 0x80, 0, 0, 0, 0,
};
void __stdcall bfmeFailDXE(int code);

// ?clearMissingVariant@@YAXXZ, retail 0x007B9B40 (22B).
void clearMissingVariant()
{
	HRESULT hr = VariantClear((VARIANTARG *)vtMissing);
	if (hr < 0)
		bfmeFailDXE(hr);
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeFailDXE@@YGXH@Z=?_com_issue_error@@YGXJ@Z")
