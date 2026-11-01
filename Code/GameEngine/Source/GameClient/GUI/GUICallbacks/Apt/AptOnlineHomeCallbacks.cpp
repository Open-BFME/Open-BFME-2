// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// platformsdk
//
// BFME2's online home screen Apt callbacks, bound as member pointers by
// the screen's registration under three spellings of its name
// ("AptOnline::OnlineHome::OnOpened", "AptOnlineHome::InitGadgets",
// "OnlineHome::NumTickerFields"); that binding is their only reference.
// They act on one object, viewed here as the first spelling's class.

#include "unicode_string.h"
#include <string.h>
#include <windows.h>
#include <stdio.h>

class GameWindow;

#include "../../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

void bfmeMinimizeCurrentThreadWindow();
class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *listBox);
void bfmeGo924A(BfmeKeyLC *listBox, char flag);

// The online home screen instance (Rva005B922FDtor.cpp's g_Va00E06480).
extern int g_Va00E06480;

namespace AptOnline
{
class OnlineHome
{
public:
	void OnOpened(const char *unused);
	void OfficialSite(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void NumTickerFields(int query, char *result, bool skip);

	// Unrowed 0x005B977B (366 bytes) and 0x005B98E9 (refills the message of
	// the day), pinned by address.
	void rva005B977B();
	void rva005B98E9();

private:
	unsigned char m_pad00[0x60];
	GameWindow *m_messageOfTheDay; // +0x60
};
}

// Retail 0x005B9B6B, 8 bytes: "AptOnline::OnlineHome::OnOpened".
void AptOnline::OnlineHome::OnOpened(const char *unused)
{
	rva005B977B();
}

// Retail 0x005B930C, 108 bytes: "AptOnline::OnlineHome::OfficialSite" opens
// the localized URL:LotrLadder in Internet Explorer and minimizes the game
// window (AptMpClans::WebSite's pattern).
void AptOnline::OnlineHome::OfficialSite(const char *unused)
{
	UnicodeString url = TheGameText->fetch("URL:LotrLadder");
	ShellExecuteW(0, L"open", L"IEXPLORE.EXE", url.str(), 0, 5);
	bfmeMinimizeCurrentThreadWindow();
}


// Retail 0x005B906C, 51 bytes: "OnlineHome::NumTickerFields", an Apt query
// answering 12.
void AptOnline::OnlineHome::NumTickerFields(int query, char *result, bool skip)
{
	if (!skip)
		*result = 0;
	if (query == 0 && !skip)
		_snprintf(result, 0xFF, "%d", 12);
}
