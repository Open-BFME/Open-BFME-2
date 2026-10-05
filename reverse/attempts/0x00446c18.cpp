// ?PopulateTeamComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?PopulateTeamComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z draft: 322B, every instruction right except the comboArray[comboBox] address: retail loads comboArray into eax and the index into ecx (lea esi,[eax+ecx*4]) where cl loads them the other way round (lea esi,[ecx+eax*4]); pointer/reference locals, index[array], unsigned index, local copies, /G7 /Os /Oy- all keep the swap.
//
// BFME2's lobby slot helpers after the LAN lobby screen (0x00446A95 onward),
// Zero Hour's GameEngine/Source/GameNetwork/GUIUtil.cpp. Nothing in the
// image calls or points at them; they survive as plain functions.
//
// PopulateTeamComboBox, retail 0x00446C18, 322 bytes. Zero Hour's
// PopulateTeamComboBox with BFME's fixed four teams, as Open-BFME-1's
// GameNetwork/PopulateColorComboBox.cpp ports it (donor revision
// 6583b3c1ff21db4a561285717028fdafc780b7db): "Team:0" (item data -1), then
// for a non-observer "Team:1".."Team:4" (item data 0..3), all in the
// default color (TheMultiplayerSettings->getColor(-1)), the first entry
// selected. The name is the donor's; the target evidence is the shape, the
// two literals and the argument use (the observer flag is the fourth
// cdecl argument). BFME2 skips it while the LAN lobby panel instance
// (g_Va00E0333C, cleared by ??1Rva004421E1) exists, where BFME1 tested
// its skirmish screen state.

#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow;
class GameInfo;

class MultiplayerColorDefinition
{
public:
	int getColor() const { return m_color; }

	unsigned char m_pad[0x10];
	int m_color; // +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
};

extern MultiplayerSettings *TheMultiplayerSettings;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetchLabel(const AsciiString &label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int index, bool silent);

// The LAN lobby panel instance (MpGameSetupSlots.cpp's g_Va00E0333C).
extern int g_Va00E0333C;

void PopulateTeamComboBox(int comboBox, GameWindow *comboArray[], GameInfo *myGame, bool isObserver)
{
	if (g_Va00E0333C)
		return;

	MultiplayerColorDefinition *def;
	UnicodeString teamName;
	int newIndex;

	GadgetComboBoxReset(comboArray[comboBox]);

	def = TheMultiplayerSettings->getColor(-1);
	newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], TheGameText->fetch("Team:0"), def->getColor());
	GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)-1);

	if (isObserver)
	{
		GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
		return;
	}

	for (int c = 0; c < 4; ++c)
	{
		AsciiString teamStr;
		teamStr.format("Team:%d", c + 1);
		teamName = TheGameText->fetch(teamStr.str());
		newIndex = GadgetComboBoxAddEntry(comboArray[comboBox], teamName, def->getColor());
		GadgetComboBoxSetItemData(comboArray[comboBox], newIndex, (void *)c);
	}

	GadgetComboBoxSetSelectedPos(comboArray[comboBox], 0, false);
}
