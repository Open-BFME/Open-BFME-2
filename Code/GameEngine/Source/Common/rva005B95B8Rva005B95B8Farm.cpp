// ?rva005B95B8@OnlineHome@AptOnline@@QAEXXZ
// ?rva005B95B8@OnlineHome@AptOnline@@QAEXXZ
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
// ?rva005B947D@AptOnlineHome@@QAEXHHH@Z @0x005B947D 104B
// Ticker formatted row: formats m_64's text plus two ints through rowed
// UnicodeString::format with fmt at VA 0x00C73BD0, then sets it under the
// index through rowed rva005B9378. Evidence: member +0x64 (UnicodeString
// m_64 in AptOnlineHome dtor TU), TheNullChr fallback at VA 0x00BBB5C4,
// callees rowed format/rva005B9378/releaseBuffer, 6 callers in 0x005B95B8.
extern const unsigned short g_00C73BD0[];

class AptOnlineHome
{
public:
	void rva005B947D(int index, int a, int b);
private:
	char m_pad[0x64];
	UnicodeString m_64;	// +0x64
};

// AptOnlineHome::rva005B947D is rowed in its home unit; this copy was a duplicate definition.

struct FactionStatBlock
{
	int wins[4];
	int losses[4];
};

extern FactionStatBlock g_Va00E06484;
extern FactionStatBlock g_Va00E064A4;
extern FactionStatBlock g_Va00E064C4;
extern FactionStatBlock g_Va00E064E4;
extern FactionStatBlock g_Va00E06504;
extern FactionStatBlock g_Va00E06524;

template<class T> inline const T &onlineHomeMax(const T &left, const T &right)
{
	return left < right ? right : left;
}

float getWinShare(int *selected, int category)
{
	int totalGames = g_Va00E06484.losses[category] + g_Va00E06484.wins[category];
	float winPercent = float(g_Va00E06484.wins[category] * 100) / float(onlineHomeMax(totalGames, 1));

	int secondFactionTotalGames = g_Va00E064A4.losses[category] + g_Va00E064A4.wins[category];
	float secondFactionWinPercent = float(g_Va00E064A4.wins[category] * 100) / float(onlineHomeMax(secondFactionTotalGames, 1));

	int thirdFactionTotalGames = g_Va00E064C4.losses[category] + g_Va00E064C4.wins[category];
	float thirdFactionWinPercent = float(g_Va00E064C4.wins[category] * 100) / float(onlineHomeMax(thirdFactionTotalGames, 1));

	int fourthFactionTotalGames = g_Va00E064E4.losses[category] + g_Va00E064E4.wins[category];
	float fourthFactionWinPercent = float(g_Va00E064E4.wins[category] * 100) / float(onlineHomeMax(fourthFactionTotalGames, 1));

	int fifthFactionTotalGames = g_Va00E06504.losses[category] + g_Va00E06504.wins[category];
	float fifthFactionWinPercent = float(g_Va00E06504.wins[category] * 100) / float(onlineHomeMax(fifthFactionTotalGames, 1));

	int sixthFactionTotalGames = g_Va00E06524.losses[category] + g_Va00E06524.wins[category];
	float sixthFactionWinPercent = float(g_Va00E06524.wins[category] * 100) / float(onlineHomeMax(sixthFactionTotalGames, 1));

	FactionStatBlock *selectedFaction = reinterpret_cast<FactionStatBlock *>(selected);
	int selectedTotalGames = selectedFaction->losses[category] + selectedFaction->wins[category];
	float selectedWinPercent = float(selectedFaction->wins[category] * 100) / float(onlineHomeMax(selectedTotalGames, 1));

	float sum = sixthFactionWinPercent + fifthFactionWinPercent + fourthFactionWinPercent + thirdFactionWinPercent + secondFactionWinPercent + winPercent;
	return selectedWinPercent / onlineHomeMax(sum, 1.0f) * 100.0f;
}

namespace AptOnline
{
class OnlineHome
{
public:
	void rva005B95B8();
};
}

void AptOnline::OnlineHome::rva005B95B8()
{
	float callResult = getWinShare(reinterpret_cast<int *>(&g_Va00E06484), 3);
	int winShareScaled = int(callResult * 100.0f);
	callResult = getWinShare(reinterpret_cast<int *>(&g_Va00E064A4), 3);
	int secondFactionShareScaled = int(callResult * 100.0f);
	callResult = getWinShare(reinterpret_cast<int *>(&g_Va00E064C4), 3);
	int thirdFactionShareScaled = int(callResult * 100.0f);
	callResult = getWinShare(reinterpret_cast<int *>(&g_Va00E064E4), 3);
	int fourthFactionShareScaled = int(callResult * 100.0f);
	callResult = getWinShare(reinterpret_cast<int *>(&g_Va00E06504), 3);
	int fifthFactionShareScaled = int(callResult * 100.0f);
	int remainder = 10000 - fifthFactionShareScaled - fourthFactionShareScaled - thirdFactionShareScaled - secondFactionShareScaled - winShareScaled;
	AptOnlineHome *home = reinterpret_cast<AptOnlineHome *>(this);
	home->rva005B947D(6, winShareScaled / 100, (winShareScaled % 100) / 10);
	home->rva005B947D(7, secondFactionShareScaled / 100, (secondFactionShareScaled % 100) / 10);
	home->rva005B947D(8, thirdFactionShareScaled / 100, (thirdFactionShareScaled % 100) / 10);
	home->rva005B947D(9, fourthFactionShareScaled / 100, (fourthFactionShareScaled % 100) / 10);
	home->rva005B947D(10, fifthFactionShareScaled / 100, (fifthFactionShareScaled % 100) / 10);
	home->rva005B947D(11, remainder / 100, (remainder % 100) / 10);
}
