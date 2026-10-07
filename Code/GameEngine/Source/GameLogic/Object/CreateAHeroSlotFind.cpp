// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE /G7
// ?Rva0021B37AFind@@YAPAVGameSlot@@PBVPlayer@@@Z @0x0021B37A 128B.
// Free GameSlot search over 8 slots via TheGameInfo and TheNameKeyGenerator.
// Evidence: unlock lane plus caller 0x0021B3FA pushes Player and checks +0x50;
// getSlot row plus StringBase copy row plus nameToKey row plus releaseBuffer;
// neighbours CreateAHeroManager accessors same ascii flags.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_ZERO = 0
};

class GameSlot
{
public:
	char m_pad00[0x34];
	AsciiString m_name34;
};

class GameInfo
{
public:
	GameSlot *getSlot(Int slotNum);
};

extern GameInfo *TheGameInfo;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Player
{
public:
	char m_pad00[0x50];
	Int m_key50;
};

// ?Rva0021B37AFind@@YAPAVGameSlot@@PBVPlayer@@@Z
GameSlot *Rva0021B37AFind(const Player *player)
{
	GameSlot *found = 0;
	if (TheGameInfo != 0)
	{
		for (UnsignedInt i = 0; found == 0 && i < 8; ++i)
		{
			{
				AsciiString s(TheGameInfo->getSlot(i)->m_name34);
				NameKeyType key = TheNameKeyGenerator->nameToKey(s);
				if (player->m_key50 == (Int)key)
					found = TheGameInfo->getSlot(i);
			}
		}
	}
	return found;
}
