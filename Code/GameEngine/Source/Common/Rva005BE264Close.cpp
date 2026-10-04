// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva005BE264Close@@YAXXZ @0x005BE264 110B
// Evidence: free AptTimeLine InitGadgets close plus SetPlayerFocus via TheRva00222A8BTarget rowed rva00224455; strings AptTimeLine::InitGadgets AptTimeLine::SetPlayerFocus write literals; callees rowed StringBase ctor 0x00037BA0 releaseBuffer 0x00036410 pinned _bfme_closeAptScreen; caller 0x0051E500 unblocks 0x0051E4B0; precedent BfmeAptScreenScoreDestructor plus Rva00224455 shared AsciiString.
#include "ascii_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva00224455
{
public:
	int rva00224455(const AsciiString *key);
};

void _bfme_closeAptScreen(const AsciiString &name);

void __cdecl Rva005BE264Close(void)
{
	{
		AsciiString s1("AptTimeLine::InitGadgets");
		_bfme_closeAptScreen(s1);
	}
	{
		AsciiString s2("AptTimeLine::SetPlayerFocus");
		reinterpret_cast<Rva00224455 *>(TheRva00222A8BTarget)->rva00224455(&s2);
	}
}
