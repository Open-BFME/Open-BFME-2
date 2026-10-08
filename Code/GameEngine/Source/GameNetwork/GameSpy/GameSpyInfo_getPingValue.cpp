// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameNetwork/GameSpy/GameSpyInfo_getPingValue.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: GameSpyInfo::getPingValue 0x0038277F (194B), grabHexInt 0x005B9024
// (49B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.

#include <stdlib.h>

typedef int Int;

struct BfmePingStringData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

#include "ascii_string.h"

struct BfmePingString
{
	BfmePingStringData *m_data;

	Int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/GSConfig.h
class GameSpyConfigInterface
{
public:
	virtual ~GameSpyConfigInterface() {}
	virtual void slot_004() = 0;
	virtual void slot_008() = 0;
	virtual Int getPingTimeoutInMs() = 0;
};

// TheGameSpyConfig: matched references place it at VA 0x00E05FB4 (zero-filled
// .bss, 4 bytes; data_xrefs: read/write by 35 functions, this unit among them).
GameSpyConfigInterface *TheGameSpyConfig = 0;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefsImplementation.h
class GameSpyInfo
{
public:
	virtual Int getPingValue(const AsciiString& otherPing);

private:
	char m_pad[0x10];
	AsciiString m_pingString;
};

static Int grabHexInt(const char *s)
{
	char tmp[5] = "0xff";
	tmp[2] = s[0];
	tmp[3] = s[1];
	Int b = strtol(tmp, NULL, 16);
	return b;
}

Int GameSpyInfo::getPingValue(const AsciiString& otherPing)
{
	if (reinterpret_cast<const BfmePingString *>(&m_pingString)->getLength()
		!= reinterpret_cast<const BfmePingString *>(&otherPing)->getLength())
	{
		return TheGameSpyConfig->getPingTimeoutInMs();
	}

	if (reinterpret_cast<const BfmePingString *>(&m_pingString)->getLength() % 2 != 0)
	{
		return TheGameSpyConfig->getPingTimeoutInMs();
	}

	Int best = 255+255;
	const char *myStr = reinterpret_cast<const BfmePingString *>(&m_pingString)->str();
	const char *otherStr = reinterpret_cast<const BfmePingString *>(&otherPing)->str();

	while (*myStr)
	{
		Int myVal = grabHexInt(myStr);
		Int otherVal = grabHexInt(otherStr);
		Int val = myVal + otherVal;
		best = (val < best) ? val : best;
		myStr += 2;
		otherStr += 2;
	}

	return best * TheGameSpyConfig->getPingTimeoutInMs() / (255+255);
}
