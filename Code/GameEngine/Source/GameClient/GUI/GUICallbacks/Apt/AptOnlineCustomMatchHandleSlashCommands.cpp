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

#include "../../../../../Include/GameNetwork/GameSpyInfoInterface.h"
extern GameSpyInfoInterface *TheGameSpyInfo;

enum GameSpyColors { GSCOLOR_DEFAULT = 0 };
extern Color GameSpyColor[];
extern int isThreadHosting;

#include "../../../../../Include/GameClient/AptOnlineCustomMatch.h"

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
