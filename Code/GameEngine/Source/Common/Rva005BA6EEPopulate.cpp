// cl: /DBFME_ASCII_DTOR_DECL /vmg /vmm /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
// ?rva005BA6EE@Rva005BA6EE@@QAE_NXZ, retail 0x005BA6EE, 277 bytes.
// BFME1 donor game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchPopulateMaxPing.cpp
// BfmeAptScreenOnlineQuickMatch::rva00558A30Ready: same reset/compute/loop/ANY/select
// shape. BFME2 deltas from retail: color from GameSpyColor[0], timeout via TheGameSpyConfig
// slot 0xc, entries stored to OnlineQuickMatchMaxPingEntries, format string via TheGameText slot 0x44
// (pointer) with ping vararg, ANY via fetch slot 0x3c by value, prefs at +0x64 via
// getMaxPing row, combo at +0x8c, selected clamp then SetSelectedPos(combo, sel, false).

#include "unicode_string.h"
#include "ascii_string.h"
#include <list>

class GameWindow;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int selectedIndex, bool dontHide);

class GameTextInterface {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual UnicodeString fetch(const char *,bool *exists=0);virtual UnicodeString fetch(const AsciiString &,bool *exists=0);virtual void slot16();virtual const UnicodeString *fetchFormat(const char *,bool *exists=0);};
extern GameTextInterface *TheGameText;

class GameSpyConfigInterface {
public:
  virtual void s0();
  virtual void s1();
  virtual void s2();
  virtual int getPingTimeoutInMs();
  virtual void s4();
  virtual void s5();
  virtual _STL::list<AsciiString> getQMMaps();
  virtual int getQMBotID();
  virtual int getQMChannel();
};
extern GameSpyConfigInterface *TheGameSpyConfig;

// Chat.cpp owns the colour array at VA 0x00DB9198; index/addend unchanged.
extern int GameSpyColor[];
// Native one-word combo-entry count; descriptive original-name-unknown label.
int OnlineQuickMatchMaxPingEntries = 0;

#include "../../Include/Common/UserPreferences.h"

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
public:
	virtual ~QuickMatchPreferences();
public:
	void setLastLadder(const AsciiString &address, unsigned short port);
public:
	void setNumPlayers(int value);
public:
	void setMaxPing(int value);
public:
	void setSide(int value);
public:
	void setColor(int value);
public:
	int getNumPlayers();
	int getMaxPing();
	int getSide();
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
	int color = GameSpyColor[0];
	UnicodeString text;
	GadgetComboBoxReset(*(GameWindow **)((char *)this + 0x8c));
	int maxPingEntries = (TheGameSpyConfig->getPingTimeoutInMs() - 1) / 100;
	maxPingEntries++;
	OnlineQuickMatchMaxPingEntries = maxPingEntries;
	if (maxPingEntries > 1)
	{
		int ping = 100;
		int remaining = maxPingEntries - 1;
		do
		{
			text.format(TheGameText->fetchFormat("GUI:TimeInMilliseconds", 0), ping);
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
