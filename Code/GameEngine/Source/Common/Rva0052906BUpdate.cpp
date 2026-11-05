// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0052906BUpdate@@YAXH@Z @0x0052906B 197B
// Free Apt HeroRank updater: static "APT:RankLabel"/"APT:HeroRank" with guards,
// rank via TheGameText slot +0x40 into UnicodeString::format, then
// BfmeAptWindowManager::bfmeSetText through TheRva00222A8BTarget.
// Evidence: guard bits 1/2 with atexit, literals at 0x838988/0x86825C,
// rowed StringBase ctor 0x37BA0, rowed Unicode format 0x6CB660,
// pinned bfmeSetText 0x225301, rowed wide releaseBuffer 0x36E70,
// caller 0x00529130 passes one int and stores it at +0x10.
#include "ascii_string.h"

#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

void __cdecl Rva0052906BUpdate(int rank)
{
	static AsciiString s_rankLabel("APT:RankLabel");
	static AsciiString s_heroRank("APT:HeroRank");
	UnicodeString tmp;
	tmp.format(TheGameText->fetchPtr(s_rankLabel, 0), rank);
	g_bfmeAptWindowManager->bfmeSetText(s_heroRank, tmp, false);
}
