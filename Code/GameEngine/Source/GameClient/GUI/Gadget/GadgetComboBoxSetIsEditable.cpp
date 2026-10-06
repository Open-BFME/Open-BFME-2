// cl: /DNDEBUG /MD
// ?GadgetComboBoxSetIsEditable@@YAXPAVGameWindow@@_N@Z, retail 0x00322660 (57B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBox.cpp
// GadgetComboBoxSetIsEditable. BFME2 repairs: null listBox guard, isEditable at
// ComboBoxData +0x0, then listBox (via rowed GadgetComboBoxGetListBox)
// winClearStatus/winSetStatus 0x600 (WIN_STATUS_NO_INPUT|NO_FOCUS) for true/false.
// Callers at 0x002C2DFD 0x00570A0B 0x00570A23 0x0057F7FB.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameWindow
{
public:
	void *winGetUserData();
	UnsignedInt winClearStatus(UnsignedInt status);
	UnsignedInt winSetStatus(UnsignedInt status);
};

GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);

struct ComboBoxData
{
	Bool isEditable;
};

void GadgetComboBoxSetIsEditable(GameWindow *comboBox, Bool isEditable)
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	GameWindow *listBox = GadgetComboBoxGetListBox(comboBox);
	if (!listBox)
		return;
	comboData->isEditable = isEditable;
	if (isEditable)
		listBox->winClearStatus(0x600);
	else
		listBox->winSetStatus(0x600);
}
