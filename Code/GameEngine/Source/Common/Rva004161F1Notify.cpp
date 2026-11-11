// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// platformsdk
// ?Rva004161F1Notify@@YAXVAsciiString@@VUnicodeString@@@Z @0x004161F1 198B
// Buddy multiple-online notification: TheGameText fetch Buddy string plus set
// via 0x00037150; releaseBuffer 0x00036E70; UnicodeString format via 0x006CB660;
// timeGetTime IAT; globals 0x00A04904 0x00A0308C 0x00A03090 0x00A03098
// 0x00A03094; chat login via rowed 0x00517048; caller 0x004163E1.
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"
typedef unsigned short wchar_t;

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

#include "../../Include/Common/Rva00517048.h"

extern Rva00517048 *g_Va00A04904;
extern unsigned char g_Va00A0308C;
// g_Va00A0308C: matched references place it at VA 0xe0308c (zero-filled .bss).
unsigned char g_Va00A0308C;
extern int g_Va00A03090;
// g_Va00A03090: matched references place it at VA 0xe03090 (zero-filled .bss).
int g_Va00A03090;
extern int g_Va00A03098;
// g_Va00A03098: matched references place it at VA 0xe03098 (zero-filled .bss).
int g_Va00A03098;
extern unsigned char g_Va00A03094;
// g_Va00A03094: matched references place it at VA 0xe03094 (zero-filled .bss).
unsigned char g_Va00A03094;
#define TheBuddy00517048Owner g_Va00A04904
#define G_BuddyFlag8C g_Va00A0308C
#define G_BuddyCount90 g_Va00A03090
#define G_BuddyTime98 g_Va00A03098
#define G_BuddyFlag94 g_Va00A03094

void __cdecl Rva004161F1Notify(AsciiString playerName, UnicodeString message)
{
	if (TheBuddy00517048Owner != 0)
	{
		if (G_BuddyFlag8C != 0 && G_BuddyCount90 > 1)
		{
			message = TheGameText->fetch("Buddy:MultipleOnlineNotification", 0);
		}
		if (!playerName.isEmpty())
		{
			message.format(&message, playerName.str());
		}
		unsigned long t = timeGetTime();
		G_BuddyTime98 = (int)(t + 0xBB8);
		G_BuddyFlag94 = 1;
		TheBuddy00517048Owner->rva00517048(message);
	}
}

#include "../../Include/Common/BfmeMemberRV.h"

#include "../../Include/Common/Player.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "../../Include/Common/PlayerList.h"

#include "../../Include/Common/NameKeyGenerator.h"

#include "../../Include/GameNetwork/GameInfo.h"


#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../Include/GameClient/InGameUI.h"

extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern InGameUI *TheInGameUI;

void __cdecl Rva004162B7Notify(AsciiString a, UnicodeString message)
{
	int localSlot = TheGameInfo->getLocalSlotNum();
	GameSlot *slot = TheGameInfo->getSlot(localSlot);
	AsciiString tmp(slot->m_field34);
	NameKeyType key = TheNameKeyGenerator->nameToKey(tmp);
	Player *player = ThePlayerList->findPlayerWithNameKey(key);
	if (player == 0)
	{
		TheInGameUI->message(UnicodeString(L"%s"), message.str());
	}
	else
	{
		bool skip = !((BfmeMemberRV *)player)->bfmeAskRV();
		if (skip)
			goto done;
		GameSlot *lslot = TheGameInfo->getSlot(localSlot);
		if (*(const unsigned char *)((const char *)lslot + 0xa) != 0)
			goto done;
		RGBColor color;
		color.setFromInt(player->m_color);
		TheInGameUI->messageColor(&color, UnicodeString(L"%s"), message.str());
	done:;
	}
}

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

void __cdecl Rva004163E1Notify(AsciiString playerName, UnicodeString message)
{
	if (TheGameLogic->m_110 != 5)
		Rva004161F1Notify(playerName, message);
	else
		Rva004162B7Notify(playerName, message);
}

// ?g_Va00A04904@@3PAURva00517048@@A: matched references place it at VA 0xe04904; also referenced as ?g_Va00E04904@@3HA.
Rva00517048 * g_Va00A04904 = 0;
#pragma comment(linker, "/alternatename:?g_Va00E04904@@3HA=?g_Va00A04904@@3PAURva00517048@@A")
