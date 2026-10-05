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

private:
	unsigned char m_pad000[0x58];
	MpGameSetupOwner *m_owner; // +0x58
	unsigned char m_pad05c[0x2C4 - 0x5C];
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
