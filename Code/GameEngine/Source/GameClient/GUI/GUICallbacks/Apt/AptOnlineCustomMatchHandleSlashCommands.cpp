// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD
// ?handleSlashCommands@AptOnlineCustomMatch@@QAE_NVUnicodeString@@@Z
// Retail 0x0059FE2B..0x0059FF9D (370 bytes).
// AptOnlineCustomMatch::handleSlashCommands: the chat-entry slash commands of
// the custom match screen, /host (prints "Hosting qr2:%d thread:%d" with the
// qr2 status compiled to 0 and PeerThread's isThreadHosting through
// TheGameSpyInfo slot 61 in the default GameSpy colour) and /me (sends the
// remainder after "/me " as an emote through TheGameSpyInfo slot 64).
// Returns whether the text was a handled command.
// Evidence (target): thiscall ending in `ret 4` (by-value UnicodeString
// destroyed by the callee) with `this` unused; the "host" / "me" / "Hosting
// qr2:%d thread:%d" literals; rowed callees AsciiString::translate
// StringBase<char> ctor nextToken toLower compare UnicodeString::format
// StringBase<unsigned short> copy and text ctors and both releaseBuffer
// bodies; it sits between AptOnlineCustomMatch's rowed PopulateLobbyComboBox
// (0x0059FD3A) and the AptOnlineCustomMatch callbacks. No retail caller
// remains. Donor (shape and name): Open-BFME-1
// OnlineCustomMatchHandleSlashCommands.cpp
// (BfmeAptScreenOnlineCustomMatch::handleSlashCommands, from Zero Hour's
// handleGameSetupSlashCommands); BFME 2 differs in format taking the literal
// directly and in addText taking only the text and colour.
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Color;

class GameSpyInfoInterface
{
public:
#define GSI_SLOT(n) virtual void slot##n();
	GSI_SLOT(00) GSI_SLOT(01) GSI_SLOT(02) GSI_SLOT(03) GSI_SLOT(04) GSI_SLOT(05) GSI_SLOT(06) GSI_SLOT(07) GSI_SLOT(08) GSI_SLOT(09)
	GSI_SLOT(10) GSI_SLOT(11) GSI_SLOT(12) GSI_SLOT(13) GSI_SLOT(14) GSI_SLOT(15) GSI_SLOT(16) GSI_SLOT(17) GSI_SLOT(18) GSI_SLOT(19)
	GSI_SLOT(20) GSI_SLOT(21) GSI_SLOT(22) GSI_SLOT(23) GSI_SLOT(24) GSI_SLOT(25) GSI_SLOT(26) GSI_SLOT(27) GSI_SLOT(28) GSI_SLOT(29)
	GSI_SLOT(30) GSI_SLOT(31) GSI_SLOT(32) GSI_SLOT(33) GSI_SLOT(34) GSI_SLOT(35) GSI_SLOT(36) GSI_SLOT(37) GSI_SLOT(38) GSI_SLOT(39)
	GSI_SLOT(40) GSI_SLOT(41) GSI_SLOT(42) GSI_SLOT(43) GSI_SLOT(44) GSI_SLOT(45) GSI_SLOT(46) GSI_SLOT(47) GSI_SLOT(48) GSI_SLOT(49)
	GSI_SLOT(50) GSI_SLOT(51) GSI_SLOT(52) GSI_SLOT(53) GSI_SLOT(54) GSI_SLOT(55) GSI_SLOT(56) GSI_SLOT(57) GSI_SLOT(58) GSI_SLOT(59)
	GSI_SLOT(60)
	virtual void addText(UnicodeString message, Color color);                 // slot 61 (+0xF4)
	GSI_SLOT(62) GSI_SLOT(63)
	virtual void sendChat(UnicodeString message, bool isAction, void *window); // slot 64 (+0x100)
#undef GSI_SLOT
};
extern GameSpyInfoInterface *TheGameSpyInfo;

enum GameSpyColors { GSCOLOR_DEFAULT = 0 };
extern Color GameSpyColor[];
extern int isThreadHosting;

class AptOnlineCustomMatch
{
public:
	bool handleSlashCommands(UnicodeString uText);
};

// Retail inlines AsciiString::getCharAt(0) here (the shared header calls it
// out of line); it reads the string data header
// {int refCount; unsigned short length; unsigned short capacity;} (the
// AptInGameChat precedent).
static inline char firstChar(const AsciiString &text)
{
	const char *data = *(const char *const *)&text;
	return data ? data[8] : 0;
}

bool AptOnlineCustomMatch::handleSlashCommands(UnicodeString uText)
{
	AsciiString message;
	message.translate(uText);
	if (firstChar(message) != '/')
		return false;

	AsciiString remainder = message.str() + 1;
	AsciiString token;
	remainder.nextToken(&token);
	((StringBase<char> &)token).toLower();

	if (token.compare("host") == 0)
	{
		UnicodeString s;
		s.format(L"Hosting qr2:%d thread:%d", 0, isThreadHosting);
		TheGameSpyInfo->addText(s, GameSpyColor[GSCOLOR_DEFAULT]);
		return true;
	}
	else if (token.compare("me") == 0 && uText.getLength() > 4)
	{
		TheGameSpyInfo->sendChat(UnicodeString(uText.str() + 4), true, 0);
		return true;
	}

	return false;
}
