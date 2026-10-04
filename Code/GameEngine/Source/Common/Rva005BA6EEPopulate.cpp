// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva005BA6EE@Rva005BA6EE@@QAE_NXZ, retail 0x005BA6EE, 277 bytes.
// BFME1 donor game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchPopulateMaxPing.cpp
// BfmeAptScreenOnlineQuickMatch::rva00558A30Ready: same reset/compute/loop/ANY/select
// shape. BFME2 deltas from retail: color from g_00DB9198, timeout via TheGameSpyConfig
// slot 0xc, entries stored to g_00E0654C, format string via TheGameText slot 0x44
// (pointer) with ping vararg, ANY via fetch slot 0x3c by value, prefs at +0x64 via
// getMaxPing row, combo at +0x8c, selected clamp then SetSelectedPos(combo, sel, false).

#include "unicode_string.h"

class GameWindow;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int selectedIndex, bool dontHide);

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};
extern GameTextInterface *TheGameText;

class GameSpyConfigInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int getPingTimeoutInMs();
};
extern GameSpyConfigInterface *TheGameSpyConfig;

extern int g_00DB9198;
extern int g_00E0654C;

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getMaxPing();
};

class Rva005BA6EE
{
public:
	bool rva005BA6EE();
};

bool Rva005BA6EE::rva005BA6EE()
{
	if (*(GameWindow **)((char *)this + 0x8c) == 0)
		return false;
	int color = g_00DB9198;
	UnicodeString text;
	GadgetComboBoxReset(*(GameWindow **)((char *)this + 0x8c));
	int maxPingEntries = (TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
	maxPingEntries++;
	g_00E0654C = maxPingEntries;
	if (maxPingEntries > 1)
	{
		int ping = 100;
		int remaining = maxPingEntries - 1;
		do
		{
			text.format(TheGameText->slot44("GUI:TimeInMilliseconds", 0), ping);
			GadgetComboBoxAddEntry(*(GameWindow **)((char *)this + 0x8c), text, color);
			ping += 100;
		} while (--remaining != 0);
	}
	GadgetComboBoxAddEntry(*(GameWindow **)((char *)this + 0x8c), TheGameText->fetch("GUI:ANY"), color);
	int selected = ((QuickMatchPreferences *)((char *)this + 0x64))->getMaxPing();
	if (selected < 0 || selected >= maxPingEntries)
		selected = maxPingEntries - 1;
	GadgetComboBoxSetSelectedPos(*(GameWindow **)((char *)this + 0x8c), selected, false);
	return true;
}
