// cl: /MD
// ?xfer@Rva0047F94C@@QAEXPAVXfer@@@Z @ 0x0047F94C 50B
// Slot 3 (xfer) shared by vtables 0x00848418 (class of ??1Rva0047F92D) and
// 0x0084F838 (class of ??1Rva004969FF), both in Rva0024A797Derived.cpp.
// Version-gated base xfer: single-arg virtual slot 0x28 on the Xfer with a
// 2-byte version struct {1,2}, then UpdateModule::xfer only when the second
// byte reads back >= 2. Evidence: slot-3 xfer recipe; base call resolves to
// rowed ?xfer@UpdateModule@@UAEXPAVXfer@@@Z 0x0044DF9F; slot-0x28 callee
// identity unproven (indirect call, no relocation); owner class placeholder.
// Retail tables 0x00C48418 (CivilianSpawnUpdate) and 0x00C4F838
// (BannerCarrierUpdate) both hold this body at slot 3, so its owner is not
// proven and the placeholder class stands for no class of either table: it
// keeps its non-virtual row spelling and reaches the now-virtual base xfer
// through a qualified call on an UpdateModule view (same this, direct call).

struct XferVersion47
{
	unsigned char m_version;
	unsigned char m_flags;
};

#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"

#include "../../Include/GameLogic/Module/UpdateModule.h"

class Rva0047F94C
{
public:
	void xfer(Xfer *xfer);
};

void Rva0047F94C::xfer(Xfer *xfer)
{
	XferVersion47 version;
	version.m_version = 1;
	version.m_flags = 2;
	*xfer == reinterpret_cast<Xfer::Version &>(version);
	if (version.m_flags >= 2)
		((UpdateModule *)this)->UpdateModule::xfer(xfer);
}
