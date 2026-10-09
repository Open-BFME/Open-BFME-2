// cl: /MD
//
// ?rva0023CFE4@GameLogic@@QAEXPAVXfer@@@Z @0x0023CFE4, 24B.
// GameLogic forwarder: Version1 then tail to submodule at +0x184 slot 3 (xfer).
// Retail: push esi; Version1 on Xfer arg; lea ecx,[esi+0x184]; jmp [eax+0xC].
// Evidence: sole caller 0x002BC7A4 passes TheGameLogic (global 0xDFE78C) with
// Xfer in esi, so this is GameLogic; +0x184 member type unproven so it keeps
// opaque virtuals with xfer in slot 3. Callee ?Version1@Xfer@@QAEXXZ is rowed
// (Xfer.cpp). Flags from xfer precedent PoisonedBehaviorXfer.cpp (/O1 /MD).

// Canonical GameLogic view; the existing native +0x184 access is unchanged.
#include "../../Common/GameLogicObjectLookupView.h"

class Xfer
{
public:
	void Version1();
};

class Sub184
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void xfer(Xfer *xfer);
};

void GameLogic::rva0023CFE4(Xfer *xfer)
{
	xfer->Version1();
	((Sub184 *)((char *)this + 0x184))->xfer(xfer);
}
