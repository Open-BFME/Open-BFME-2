// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva005D59F0Get@@YA?AVUnicodeString@@H@Z retail 0x005D59F0 142B
// Rank tooltip: if rank<=0 fetch TOOLTIP:LadderRankUnavailable via TheGameText
// slot 0x3C, else format rank via 0x00BC9260; return as UnicodeString.
// Same recipe as ?Rva0043A568Get@@YA?AVUnicodeString@@H@Z 0x0043A568.
// Evidence: same callees format 0x006CB5D0 set 0x00037150 releaseBuffer
// 0x00036E70 copy ctor 0x00037050; callers 0x005D6123 0x005D6133.
typedef unsigned short WideChar;

#include "unicode_string.h"


class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

#define RankFmt ((const WideChar *)L"%d")

UnicodeString __cdecl Rva005D59F0Get(int rank)
{
	UnicodeString s;
	if (rank < 0)
		s.set(TheGameText->fetch("TOOLTIP:LadderRankUnavailable"));
	else
		s.format(RankFmt, rank);
	return s;
}
