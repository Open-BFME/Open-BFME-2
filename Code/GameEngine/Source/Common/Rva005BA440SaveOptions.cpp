// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005BA440@Rva005BA440@@QAEXXZ retail 0x005BA440..0x005BA587 327B.
// The quick-match screen's save-options body: its only reference is the
// tail jump in the rowed slot 0x005BA621. It saves the five gadget
// selections into a temporary QuickMatchPreferences (ctor 0x005DF1A3 dtor
// 0x005DF17C): ladder (+0x90) through TheLadderList (0x00A05FB0) lookup
// 0x0054D6C8 then setLastLadder 0x005DF7A7 and write 0x003B1BF3; else an
// empty ladder and the number-of-players pick clamped at zero. Then
// numPlayers (+0x84) maxPing (+0x8C) side (+0x88 item data clamped at zero)
// and the colour picker at +0x80 (getter 0x00323674 clamped at zero).
// Donor: BFME 1 game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchSaveOptions.cpp
// (retail 0x005585B0 372B) with the gadget block moved from +0x5C to +0x80.
#include "ascii_string.h"

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool write();

private:
	unsigned char m_unmodelled[0x10];
};

class QuickMatchPreferences : public UserPreferences
{
public:
	QuickMatchPreferences();
	virtual ~QuickMatchPreferences();
	void setLastLadder(const AsciiString &address, unsigned short port);
	void setNumPlayers(int value);
	void setMaxPing(int value);
	void setSide(int value);
	void setColor(int value);
};

class Rva0054D8D8
{
private:
	unsigned char m_unmodelled[0x28];

public:
	AsciiString address; // +0x28
	unsigned short port; // +0x2C
};

class Rva0054D974
{
public:
	Rva0054D8D8 *rva0054D6C8(int index);
};

extern Rva0054D974 *TheLadderList;

class Rva00323674
{
public:
	int rva00323674() const;
};

class GameWindow;
void GadgetComboBoxGetSelectedPos(GameWindow *combo, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *combo, int selected);

template <typename T> inline const T &rva005BA440Max(const T &a, const T &b)
{
	if (a > b)
		return a;
	return b;
}

class Rva005BA440
{
public:
	void rva005BA440();

private:
	unsigned char m_unmodelled[0x80];
	Rva00323674 m_color; // +0x80
	GameWindow *m_numPlayers; // +0x84
	GameWindow *m_side; // +0x88
	GameWindow *m_connectionSpeed; // +0x8C
	GameWindow *m_ladder; // +0x90
};

void Rva005BA440::rva005BA440()
{
	QuickMatchPreferences pref;
	int selected;

	GadgetComboBoxGetSelectedPos(m_ladder, &selected);
	int ladderID = (int)GadgetComboBoxGetItemData(m_ladder, selected);
	const Rva0054D8D8 *li = TheLadderList->rva0054D6C8(ladderID);
	if (li != 0)
	{
		pref.setLastLadder(li->address, li->port);
		pref.write();
	}
	else
	{
		pref.setLastLadder(AsciiString::TheEmptyString, 0);
		GadgetComboBoxGetSelectedPos(m_numPlayers, &selected);
		if (selected < 0)
			selected = 0;
	}

	GadgetComboBoxGetSelectedPos(m_numPlayers, &selected);
	pref.setNumPlayers(selected);

	GadgetComboBoxGetSelectedPos(m_connectionSpeed, &selected);
	pref.setMaxPing(selected);

	int item;
	GadgetComboBoxGetSelectedPos(m_side, &selected);
	item = (int)GadgetComboBoxGetItemData(m_side, selected);
	pref.setSide(rva005BA440Max(0, item));

	selected = m_color.rva00323674();
	pref.setColor(rva005BA440Max(0, selected));
	pref.write();
}
