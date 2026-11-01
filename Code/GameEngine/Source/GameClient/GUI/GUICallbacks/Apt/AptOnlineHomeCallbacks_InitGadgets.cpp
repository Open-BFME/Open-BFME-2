// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// platformsdk
// Split from AptOnlineHomeCallbacks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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



// Retail 0x005B9B73, 73 bytes: "AptOnlineHome::InitGadgets" keeps the
// "OnlineHome::MessageOfTheDay" list box and fills it.
void AptOnline::OnlineHome::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!g_Va00E06480)
		return;
	if (!window)
		return;
	GadgetListBoxReset(window);
	if (strcmp(name, "OnlineHome::MessageOfTheDay") == 0)
	{
		m_messageOfTheDay = window;
		bfmeGo924A((BfmeKeyLC *)window, 0);
		rva005B98E9();
	}
}

