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
	virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16(bool value);
	virtual void v17(int value, bool flag);
};

class MpGameSetup
{
public:
	int rva0043DD02(int slot);
	void rva0043DC0F();
	void rva0043E49C(int value);
	void rva0043E4B6(const char *slotText);

	// Unrowed 0x0043E30F (211 bytes), pinned by address.
	void rva0043E30F(int slot, int value);

private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner; // +0x58
	Rva0043DA65 *m_game; // +0x5C
	unsigned char m_pad060[0x2C4 - 0x60];
	bool m_2c4; // +0x2C4
	unsigned char m_pad2c5[0x334 - 0x2C5];
	GameWindow *m_playerTemplate[8]; // +0x334
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
