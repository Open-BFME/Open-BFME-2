// cl: /Oy- /DNDEBUG /MD
// ?Rva00322910@@YAHPAVGameWindow@@@Z, retail 0x00322910 (33B).
// Chain of GadgetComboBoxGetSelectedPos 0x003228EB: null combobox yields -1,
// else reuse the parameter slot as the Int out-param (lea [ebp+8]) and return
// the overwritten slot. Callers compare the result to -1 (e.g. 0x0043F4BC at
// 0x0043F4BC, 0x004405AB, 0x0057C659). True name unknown, so the honest
// address-derived name stands. EBP frame needs /Oy- (neighbour is /O1).

typedef int Int;

class GameWindow
{
};

void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, Int *selectedIndex);

int Rva00322910(GameWindow *comboBox)
{
	if (comboBox == 0)
		return -1;
	GadgetComboBoxGetSelectedPos(comboBox, (Int *)&comboBox);
	return (int)comboBox;
}
