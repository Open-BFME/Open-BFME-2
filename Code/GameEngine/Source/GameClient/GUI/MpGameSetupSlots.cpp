// cl: /O1 /DNDEBUG /MD
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

class GameWindow;

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
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, int index, bool silent);

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

// The owning screen's interface at +0x58, by vslot.
class MpGameSetupOwner
{
public:
	virtual void v00();
	virtual bool v01();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual bool applySlotHero(GameSlot *slot);
	virtual void v07(); virtual void v08(); virtual void v09();
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

	// Unrowed 0x0043E30F (211 bytes), pinned by address.
	void rva0043E30F(int slot, int value);

private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner; // +0x58
	Rva0043DA65 *m_game; // +0x5C
	unsigned char m_pad060[0x7C - 0x60];
	int m_mode; // +0x7C (MpGameSetupOnInitGadget.cpp's m_hideFlag)
	unsigned char m_pad080[0xD0 - 0x80];
	Rva0057EE5C m_d0; // +0xD0
	unsigned char m_pad0d1[0x2C3 - 0xD1];
	bool m_pending; // +0x2C3
	bool m_2c4; // +0x2C4
	unsigned char m_pad2c5[0x314 - 0x2C5];
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
