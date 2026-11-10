// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva003FEECBSetPalantirCommandPoints@@YA_NHH@Z @0x003FEECB 181B: Apt Palantir command points display via static AsciiString key plus int-gated Unicode format/set plus bfmeSetText. Evidence: calls StringBase ctor 0x00037BA0 plus atexit plus UnicodeString format 0x006CB5D0 twice plus StringBase set 0x0000565D plus bfmeSetText pin 0x00225301 plus release 0x00036E70; same shape as rowed Rva003FF02EPowerCap 0x003FF02E plus sibling Rva003FEE43.
#include "ascii_string.h"
#include "unicode_string.h"

extern const unsigned short g_Va007C9260[];

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

bool __cdecl Rva003FEECBSetPalantirCommandPoints(int cur, int max)
{
	static AsciiString s_key("APT:PalantirCommandPoints");
	UnicodeString str;
	if (cur >= 0)
	{
		if (max >= 0)
		{
			str.format(L"%d/%d", max, cur);
		}
		else
		{
			str.format(g_Va007C9260, cur);
		}
	}
	else
	{
		str.set(L" ");
	}
	g_bfmeAptWindowManager->bfmeSetText(s_key, str, false);
	return true;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
