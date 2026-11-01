// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?FormatRankString@StrategicHUD@@YA?AVUnicodeString@@H@Z retail 0x005F632A 194B
// Evidence: static APT:RankLabel via rowed StringBase ctor 0x37BA0 and atexit; TheGameText slot 0x38 fetch; Unicode format 0x6CB5D0; releaseBuffers 0x36E70; caller 0x005F6407; precedent Rva0052906BUpdate
#include "ascii_string.h"

#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

namespace StrategicHUD {

UnicodeString __cdecl FormatRankString(int rank)
{
	UnicodeString tmp;
	if (rank >= 0) {
		static AsciiString s_rankLabel("APT:RankLabel");
		UnicodeString fetched = TheGameText->fetch(s_rankLabel, 0);
		tmp.format(fetched.str(), rank);
	}
	return tmp;
}

} // namespace StrategicHUD
