// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005BE264@Rva005BE264Owner@@QAEXXZ @0x005BE264 110B
// Evidence: AptTimeLine InitGadgets close plus SetPlayerFocus via TheRva00222A8BTarget rowed RemoveCommandMap; strings AptTimeLine::InitGadgets AptTimeLine::SetPlayerFocus write literals; callees rowed StringBase ctor 0x00037BA0 releaseBuffer 0x00036410 pinned _bfme_closeAptScreen; caller 0x0051E500 unblocks 0x0051E4B0; precedent BfmeAptScreenScoreDestructor plus Rva00224455 shared AsciiString.
// The only caller (0x0051E500) loads the owner into ecx (mov ecx,[esi+0x280];
// test ecx,ecx; je; call), so the body is a member that ignores this, spelled
// as the caller's pin names it.
#include "ascii_string.h"

class Rva00222A8BTarget;
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/Common/Rva00224455.h"

void _bfme_closeAptScreen(const AsciiString &name);

class Rva005BE264Owner
{
public:
	void rva005BE264();
};

void Rva005BE264Owner::rva005BE264()
{
	{
		AsciiString s1("AptTimeLine::InitGadgets");
		_bfme_closeAptScreen(s1);
	}
	{
		AsciiString s2("AptTimeLine::SetPlayerFocus");
		reinterpret_cast<Rva00224455 *>(g_bfmeAptWindowManager)->RemoveCommandMap(&s2);
	}
}
