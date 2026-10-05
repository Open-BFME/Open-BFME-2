// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// Small MpGameSetup members of BFME2's LAN lobby panel (the screen's +0x288
// object: its callback registration 0x0044303D binds the rowed
// MpGameSetup::_bfme_onInitGadget 0x0043EB1D, and ??1Rva004421E1 0x004421E1
// destroys it). Names are unknown, so each keeps its address.
//
// Target facts (all read from retail): the owning screen's interface is
// at +0x58 (BFME1's MpGameSetup kept its owner at +0x04 behind a smaller
// base); the per-slot player template combo boxes are at +0x334 (as in
// MpGameSetupOnInitGadget.cpp); +0x2C4 is a dirty flag.

#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow;
class BfmeKeyLC;

void *bfmeGo925A(BfmeKeyLC *comboBox);

extern "C" __declspec(dllimport) int __cdecl atoi(const char *text);

class GameSlot
{
public:
	bool isHuman() const;
	bool isObserver() const;

	unsigned char m_pad00[0x04];
	int m_state; // +0x04
	bool m_accepted; // +0x08
	unsigned char m_pad09[0x18 - 0x09];
	int m_playerTemplate; // +0x18
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual bool v12();

	GameSlot *getSlot(int index);
};

// The validated current game at +0x5C (rowed under its address name).
class Rva0043DA65
{
public:
	int rva0043DA65();
};

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *comboBox, int index);
int GadgetComboBoxGetLength(GameWindow *comboBox);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox);
int GadgetListBoxGetNumEntries(GameWindow *listBox);
int Rva003253BEGet(GameWindow *listBox, int row, int column);
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int index, bool silent);

class MultiplayerColorDefinition
{
public:
	unsigned char m_pad[0x10];
	int m_color; // +0x10
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor(int which);
};

extern MultiplayerSettings *TheMultiplayerSettings;
extern const unsigned short g_00C3D9D4[];
void GadgetComboBoxReset(GameWindow *comboBox);
int GadgetComboBoxAddEntry(GameWindow *comboBox, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *comboBox, int index, void *data);
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, int maxDisplay);
int Rva0043DDF8(int count);

extern "C" char *__cdecl _mbscpy(char *dest, const char *src);
extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
	// Unrowed 0x002239E2 (sets a named Apt image), pinned by address.
	void rva002239E2(const AsciiString &name, const Image *image);
};

// The owning screen's interface at +0x58, by vslot.
class MpGameSetupOwner
{
public:
	virtual void v00();
	virtual bool v01();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual bool applySlotHero(GameSlot *slot);
	virtual void v07(); virtual void v08();
	virtual bool setSlotState(GameSlot *slot, int state, const UnicodeString &name);
	virtual bool applySlotPlayerTemplate(GameSlot *slot, int playerTemplate);
	virtual void v11();
	virtual bool applySlotTeam(GameSlot *slot, int team);
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16(bool value);
	virtual void v17(int value, bool flag);
	virtual void v18(); virtual void v19(); virtual void v20();
	virtual void *v21();
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// TheCreateAHeroManager (0x00DFE344), spelled as Rva00406E65.cpp does.
class Rva00219B9E;
extern Rva00219B9E *g_00DFE344;

void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

// The member at +0xD0 (destroyed through ??1Rva0057EE5C); its 0x0057EA0F
// (158 bytes) is unrowed and pinned.
class Rva0057EE5C
{
public:
	void rva0057EA0F();
	// And its unrowed 0x0057E6D8 (5 bytes, a jump to 0x0057E6C1), pinned.
	void rva0057E6D8();
};

// The member at +0x244 (rowed under its address name).
class Rva0057FD6E
{
public:
	void rva0057FD94();
};

class MpGameSetup
{
public:
	int rva0043DD02(int slot);
	void rva0043DC0F();
	void rva0043E49C(int value);
	void rva0043E4B6(const char *slotText);
	void rva0043DB6E();
	bool handlePlayerTemplateSelection(int index);
	bool rva0043E04D(int index);
	void rva0043E3E2(int index, int team);

	// Unrowed 0x0043DD34 (138 bytes; stores a hero choice on the slot when
	// the hero manager accepts it), pinned.
	bool rva0043DD34(GameSlot *slot, int hero);

	// Unrowed 0x0044149C (313 bytes; refreshes a slot's widgets), pinned.
	void rva0044149C(GameSlot *slot, int index, bool flag);

	void rva0043E30F(int slot, int value);
	void rva0043E253(int slot);
	void rva00442F65(int query, char *result, bool skip);
	const Image *rva0043E512(int value);
	void rva0043E5C1(int slot, int kind, int value);
	void OnSortName(const char *unused);
	void OnSortPlayers(const char *unused);
	void OnSortIcons(const char *unused);
	void OnTabSelect(const char *tab);

	// Unrowed 0x0043DC40 (53 bytes; picks the games list sort column, the
	// same column again toggling to the next value), pinned by address.
	void rva0043DC40(int column);

	// Unrowed 0x00442C9C (23 bytes), pinned by address.
	bool rva00442C9C();

private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner; // +0x58
	Rva0043DA65 *m_game; // +0x5C
	unsigned char m_pad060[0x7C - 0x60];
	int m_mode; // +0x7C (MpGameSetupOnInitGadget.cpp's m_hideFlag)
	unsigned char m_pad080[0xD0 - 0x80];
	Rva0057EE5C m_d0; // +0xD0
	unsigned char m_pad0d1[0x160 - 0xD1];
	int m_160; // +0x160
	unsigned char m_pad164[0x244 - 0x164];
	Rva0057FD6E m_244; // +0x244
	unsigned char m_pad245[0x2C3 - 0x245];
	bool m_pending; // +0x2C3
	bool m_2c4; // +0x2C4
	unsigned char m_pad2c5[0x2D4 - 0x2C5];
	GameWindow *m_player[8]; // +0x2D4
	unsigned char m_pad2f4[0x314 - 0x2F4];
	GameWindow *m_team[8]; // +0x314
	GameWindow *m_playerTemplate[8]; // +0x334
	GameWindow *m_handicap[8]; // +0x354
	GameWindow *m_hero[8]; // +0x374
	unsigned char m_pad394[0x3A4 - 0x394];
	int m_flags; // +0x3A4
};

// Retail 0x0043DD02, 50 bytes: the item data of slot's selected player
// template, or -1 without a combo box.
int MpGameSetup::rva0043DD02(int slot)
{
	GameWindow *comboBox = m_playerTemplate[slot];
	if (!comboBox)
		return -1;
	int selected;
	GadgetComboBoxGetSelectedPos(comboBox, &selected);
	return (int)GadgetComboBoxGetItemData(comboBox, selected);
}

// Retail 0x0043DC0F, 49 bytes.
void MpGameSetup::rva0043DC0F()
{
	if (m_2c4)
	{
		m_2c4 = false;
		m_owner->v16(false);
		if (m_owner->v01())
			m_owner->v15();
	}
}

// Retail 0x0043E49C, 26 bytes.
void MpGameSetup::rva0043E49C(int value)
{
	rva0043DC0F();
	m_owner->v17(value, true);
}

// Retail 0x0043DDF8, 33 bytes: the larger of 8 - count and 4, through
// references like the STL max.
template <class T> static inline const T &rva0043DDF8Max(const T &a, const T &b)
{
	return a > b ? a : b;
}

int Rva0043DDF8(int count)
{
	return rva0043DDF8Max(8 - count, 4);
}

// Retail 0x0043DB23, 26 bytes: invoke an Apt callback with no arguments.
void Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name)
{
	target->invoke(owner, name, 0, 0, 0, 0, 0, 0);
}

// Retail 0x0043E4B6, 92 bytes: when game vslot 12 holds, a slot given by
// number (1..7) that is neither open nor closed goes to 0x0043E30F.
void MpGameSetup::rva0043E4B6(const char *slotText)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (game && game->v12())
	{
		int slot = atoi(slotText);
		if (slot > 0 && slot < 8)
		{
			GameSlot *gameSlot = game->getSlot(slot);
			if (gameSlot && gameSlot->m_state != 0 && gameSlot->m_state != 1)
				rva0043E30F(slot, 0);
		}
	}
}

// Retail 0x0043DB6E, 53 bytes: refreshes the +0xD0 member and, with flag
// 0x40 set, tells the owner's Apt movie "OnClansFlagChange".
void MpGameSetup::rva0043DB6E()
{
	m_d0.rva0057EA0F();
	if (m_flags & 0x40)
		Rva0043DB23(TheRva00222A8BTarget, m_owner->v21(), "OnClansFlagChange");
}

// Retail 0x00441AAA, 107 bytes. Donor Open-BFME-1 MpGameSetup.cpp
// (handlePlayerTemplateSelection, BFME1 0x00524C30). BFME2 reads the choice
// through 0x0043DD02, treats an unchanged template as handled, applies a new
// one through the owner's applySlotPlayerTemplate (vslot 10) and then
// refreshes the slot (0x0044149C).
bool MpGameSetup::handlePlayerTemplateSelection(int index)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;

	m_pending = false;
	int playerTemplate = rva0043DD02(index);
	if (playerTemplate < -2)
		return false;
	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	if (playerTemplate != slot->m_playerTemplate && !m_owner->applySlotPlayerTemplate(slot, playerTemplate))
		return false;
	rva0044149C(slot, index, true);
	return true;
}

// Retail 0x0043E04D, 120 bytes: the hero combo box counterpart of
// handlePlayerTemplateSelection (BFME1 has no hero choice; the name is
// unknown). Needs the hero manager; a hero accepted by 0x0043DD34 is applied
// through the owner's applySlotHero (vslot 6).
bool MpGameSetup::rva0043E04D(int index)
{
	if (!g_00DFE344)
		return false;
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return false;

	GameSlot *slot = game->getSlot(index);
	if (!slot)
		return false;
	m_pending = false;
	GameWindow *comboBox = m_hero[index];
	int selected;
	GadgetComboBoxGetSelectedPos(comboBox, &selected);
	if (!rva0043DD34(slot, (int)GadgetComboBoxGetItemData(comboBox, selected)))
		return false;
	return m_owner->applySlotHero(slot);
}

// Retail 0x0043E3E2, 186 bytes. Name unknown. Shows a slot's team in its
// team combo box (+0x314); in mode 1 an unset team (-1) on a slot that is not
// closed becomes 1 for slot 1 and 0 otherwise, and the host (game vslot 12)
// applies it through the owner's applySlotTeam (vslot 12).
void MpGameSetup::rva0043E3E2(int index, int team)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameWindow *comboBox = m_team[index];
	if (!comboBox)
		return;

	int mode = m_mode;
	GameSlot *slot = game->getSlot(index);
	if (mode == 1 && team == -1 && slot->m_state != 1)
	{
		team = index == 1;
		if (game->v12())
		{
			slot = game->getSlot(index);
			if (slot)
				m_owner->applySlotTeam(slot, team);
		}
	}

	int count = GadgetComboBoxGetLength(comboBox);
	for (int i = 0; i < count; ++i)
	{
		if (team == (int)GadgetComboBoxGetItemData(comboBox, i))
		{
			GadgetComboBoxSetSelectedPos(comboBox, i, true);
			return;
		}
	}
}

// Retail 0x0043E30F, 211 bytes. Name unknown. Selects the player combo box
// (+0x2D4) entry whose list item data equals the slot state and, on the host
// (game vslot 12), hands the slot, state and the combo text to the owner's
// slot-state setter (vslot 9, BfmeAptScreenLanLobby::rva00444B90 for LAN).
void MpGameSetup::rva0043E30F(int index, int state)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	GameWindow *comboBox = m_player[index];
	if (!comboBox)
		return;

	GameWindow *listBox = (GameWindow *)bfmeGo925A((BfmeKeyLC *)comboBox);
	int count = GadgetListBoxGetNumEntries(listBox);
	for (int i = 0; i < count; ++i)
	{
		if (Rva003253BEGet(listBox, i, 0) == state)
		{
			GadgetComboBoxSetSelectedPos(comboBox, i, false);
			if (game->v12())
			{
				GameSlot *slot = game->getSlot(index);
				if (slot)
				{
					UnicodeString name = GadgetComboBoxGetText(comboBox);
					m_owner->setSlotState(slot, state, name);
				}
			}
			return;
		}
	}
}

// Retail 0x0043E253, 188 bytes. Name unknown. Populates the handicap combo
// box (+0x354) with 0 down to -95 step -5, each entry formatted through
// g_00C3D9D4 with the default color's +0x10 value and item data equal to the
// handicap, then selects 0 and limits display through 0x0043DDF8.
// Evidence: callers 0x004427E8; callees all rowed; TheMultiplayerSettings
// getColor(-1) plus GadgetComboBoxReset/AddEntry/SetItemData/SetSelectedPos/
// SetMaxDisplay and UnicodeString::format; neighbours 0x0043E132/0x0043E30F.
void MpGameSetup::rva0043E253(int slot)
{
	if (!m_handicap[slot])
		return;
	MultiplayerColorDefinition *color = TheMultiplayerSettings->getColor(-1);
	GadgetComboBoxReset(m_handicap[slot]);
	for (int handicap = 0; handicap >= -0x5F; handicap -= 5)
	{
		UnicodeString text;
		text.format(g_00C3D9D4, handicap);
		int index = GadgetComboBoxAddEntry(m_handicap[slot], text, color->m_color);
		GadgetComboBoxSetItemData(m_handicap[slot], index, (void *)handicap);
	}
	GadgetComboBoxSetSelectedPos(m_handicap[slot], 0, false);
	GadgetComboBoxSetMaxDisplay(m_handicap[slot], Rva0043DDF8(slot));
}

// Retail 0x00442F65, 115 bytes: an Apt query callback bound four times by the
// panel's registration 0x0044303D. Unless told to skip, it writes "1" or "0"
// for query 0 (owner vslot 1), 1 (0x00442C9C), 2 (mode +0x160 is 1 with a
// current game) or 3 (flag 0x80 at +0x3A4). Name unknown.
void MpGameSetup::rva00442F65(int query, char *result, bool skip)
{
	switch (query)
	{
	case 0:
		if (!skip)
			_mbscpy(result, m_owner->v01() ? "1" : "0");
		break;
	case 1:
		if (!skip)
			_mbscpy(result, rva00442C9C() ? "1" : "0");
		break;
	case 2:
		if (!skip)
			_mbscpy(result, m_160 == 1 && m_game->rva0043DA65() ? "1" : "0");
		break;
	case 3:
		if (!skip)
			_mbscpy(result, m_flags & 0x80 ? "1" : "0");
		break;
	}
}

// Retail 0x0043E512, 175 bytes: the "AptPing03", "AptPing02" or "AptPing01"
// image for 1, 2 or 3, else none (it ignores the receiver; the online screen
// calls it on its own panel at +0x70 too). Name unknown.
const Image *MpGameSetup::rva0043E512(int value)
{
	switch (value)
	{
	case 1:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing03"));
	case 2:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing02"));
	case 3:
		return TheMappedImageCollection->findImageByName(AsciiString("AptPing01"));
	}
	return 0;
}

// Retail 0x0043E5C1, 264 bytes. Name unknown. Shows a slot's connection
// state as the Apt image "ConnectionIcon~<slot>": failed, waiting,
// connecting, or (kind 4) the ping image for the value.
void MpGameSetup::rva0043E5C1(int slot, int kind, int value)
{
	const Image *image = 0;
	switch (kind)
	{
	case 1:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptConnectionFailed"));
		break;
	case 2:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptWaitingToConnect"));
		break;
	case 3:
		image = TheMappedImageCollection->findImageByName(AsciiString("AptConnecting"));
		break;
	case 4:
		image = rva0043E512(value);
		break;
	}

	char name[128];
	sprintf(name, "ConnectionIcon~%d", slot);
	TheRva00222A8BTarget->rva002239E2(AsciiString(name), image);
}

// Retail 0x0043DC75, 0x0043DC7F and 0x0043DC89, 10 bytes each: the Apt
// callbacks the panel registration 0x0044303D binds as
// "MpGameSetup::OnSortName", "MpGameSetup::OnSortPlayers" and
// "MpGameSetup::OnSortIcons"; they pick sort column 0, 2 or 4.

void MpGameSetup::OnSortName(const char *)
{
	rva0043DC40(0);
}

void MpGameSetup::OnSortPlayers(const char *)
{
	rva0043DC40(2);
}

void MpGameSetup::OnSortIcons(const char *)
{
	rva0043DC40(4);
}
