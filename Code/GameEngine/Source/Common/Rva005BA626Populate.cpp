// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva005BA626@Rva005BA626@@QAE_NXZ, retail 0x005BA626, 200 bytes.
// Sibling donor Code/GameEngine/Source/Common/Rva005BA6EEPopulate.cpp
// (BFME1 game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchPopulateMaxPing.cpp).
// Retail resets combo at +0x84, loops i=1..2 formatting "GUI:PlayersVersusPlayers"
// with (i,i) via TheGameText slot 0x44, adds entries with color g_00DB9198,
// then selects max(0,getNumPlayers) from prefs at +0x64. Caller 0x005BB5CE chains
// into 0x005BA6EE and 0x005BB3A1 with flag at +0x78, same this.

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

extern int GameSpyColor[];

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();
	int getNumPlayers();
};

class Rva005BA626
{
public:
	bool rva005BA626();
};

bool Rva005BA626::rva005BA626()
{
	if (*(GameWindow **)((char *)this + 0x84) == 0)
		return false;
	int color = GameSpyColor[0];
	GadgetComboBoxReset(*(GameWindow **)((char *)this + 0x84));
	UnicodeString text;
	for (int i = 1; i <= 2; ++i)
	{
		text.format(TheGameText->slot44("GUI:PlayersVersusPlayers", 0), i, i);
		GadgetComboBoxAddEntry(*(GameWindow **)((char *)this + 0x84), text, color);
	}
	int num = ((QuickMatchPreferences *)((char *)this + 0x64))->getNumPlayers();
	int zero = 0;
	int *pSel = num < 0 ? &zero : &num;
	GadgetComboBoxSetSelectedPos(*(GameWindow **)((char *)this + 0x84), *pSel, false);
	return true;
}
