// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD
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
class Image;
const Image *__cdecl Rva00559B64GetImage(int side, int rank);
class Rva00559AC1
{
public:
	__declspec(noinline) int rva00559AC1(int v);
	float PercentDoneUntilNextRank(int points);
	int rva00559ADC(int v);
	const Image *rva00559C25(int side, int v);
	Rva00559AC1 *rva00559A76(int dummy);
private:
	int m_vals[11];
};

int Rva00559AC1::rva00559AC1(int v)
{
	for (int i = 1; i < 11; ++i)
	{
		if (m_vals[i] > v)
			return i - 1;
	}
	return 10;
}

// ?rva00559ADC@Rva00559AC1@@QAEHH@Z @0x00559ADC 29B: distance to the next
// rank threshold, returning zero once the search reaches its terminal slot.
// Evidence: adjacent body calls this object's rowed search and reads the same
// threshold array at +4; callers use the same this pointer and int argument.
int Rva00559AC1::rva00559ADC(int v)
{
	int idx = rva00559AC1(v);
	if (idx >= 10)
		return 0;
	return m_vals[idx + 1] - v;
}

const Image *Rva00559AC1::rva00559C25(int side, int v)
{
	int idx = rva00559AC1(v);
	return Rva00559B64GetImage(side, idx);
}

// ?rva00559A76@Rva00559AC1@@QAEPAV1@H@Z @0x00559A76 75B: rank threshold table init.
// Evidence: leaf with 2 callers; writes m_vals 11 ints matching search class; ret 4 unused arg.
Rva00559AC1 *Rva00559AC1::rva00559A76(int dummy)
{
	m_vals[0] = -1;
	m_vals[1] = 0;
	m_vals[10] = 1500;
	m_vals[9] = 800;
	m_vals[8] = 500;
	m_vals[7] = 300;
	m_vals[6] = 150;
	m_vals[5] = 50;
	m_vals[4] = 30;
	m_vals[3] = 10;
	m_vals[2] = 5;
	return this;
}

// WB13FA240 PercentDoneUntilNextRank and assertions at RankPointValue.cpp
// 266/274 prove the method's purpose. Native559AF9..559B4B reads the same
// eleven-int threshold object as the existing559AC1 search. The original
// owner spelling is retained as the established address-derived class.
float Rva00559AC1::PercentDoneUntilNextRank(int points)
{
 int rank = rva00559AC1(points);
 if (rank == 0)
  return 0.0f;
 if (rank >= 10)
  return 0.0f;
 float current = (float)m_vals[rank];
 float next = (float)m_vals[rank + 1];
 float difference = next - current;
 if (difference < 0.0001f)
  return 0.0f;
 return ((float)points - current) / difference;
}
