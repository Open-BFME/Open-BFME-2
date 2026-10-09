// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /EHsc /MD
// Retail 0x00559C3D..0x00559CE5, 168 bytes. WB 0x013F9DD0 names
// RankPointValue::RankString and asserts (unsigned)rank < MAX_RANKS at
// RankPointValue.cpp:160. Its original namespace/class and argument type
// names are unknown; retain an address-derived free-function ABI.
// Native accesses prove eleven pointer entries at VA 0x00DD22C8 and
// 0x00DD22F4. The local array names describe their observed good/evil labels;
// every label and initializer relocation is checked against retail data.
#include "ascii_string.h"
#include "unicode_string.h"
class GameTextInterface
{
public:
#define T(n) virtual void t##n();
	T(0) T(1) T(2) T(3) T(4) T(5) T(6) T(7) T(8) T(9) T(10) T(11) T(12) T(13)
#undef T
	virtual UnicodeString fetch(const AsciiString &, bool *exists = 0);
};
extern GameTextInterface *TheGameText;
static const char *goodRankLabels[] = {
 "NoRank", "Peasant", "Page", "Squire", "Knight", "RoyalGuard",
 "CaptainOfTheGuard", "HighLord", "Prince", "King", "Wizard"
};
static const char *evilRankLabels[] = {
 "NoRank", "Scum", "Vermin", "Beast", "Goblin", "Orc", "MountainTroll",
 "Berserker", "DarkWizard", "RingWraith", "DarkLord"
};
UnicodeString Rva00559C3D(unsigned char evil, int rank)
{
	if ((unsigned int)rank >= 11)
		return UnicodeString::TheEmptyString;
	AsciiString name(evil ? evilRankLabels[rank] : goodRankLabels[rank]);
	AsciiString key("TOOLTIP:");
	key.concat(name);
	return TheGameText->fetch(key);
}