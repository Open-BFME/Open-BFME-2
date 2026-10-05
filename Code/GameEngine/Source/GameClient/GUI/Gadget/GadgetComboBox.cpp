// cl: /O1 /DNDEBUG /MD

// Text-color family from clean Open-BFME-1 6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Retail independently proves four distinct color-pair stores and the
// ComboBox style-bit dispatch at GameWindow +0x3C. The paired helpers call
// the rowed winGetUserData provider and then the same setter on optional
// child pointers at data +0x2C and +0x28. Donor supplies semantic names;
// native boundaries, stores and reciprocal calls establish target ABI/offsets.
// Disabled helper intentionally gets user data before its null test, as retail does.

// GadgetComboBox small setters, retail 0x003226E7/0x00322703.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBox.cpp
// (BFME1 0x004B3980/0x004B39B0). ComboBoxData/EntryData keep their ZH order
// here; winGetUserData resolves through the ledger (no new pins).

typedef int Int;
typedef bool Bool;
typedef short Short;

class GameWindow;
class ListboxData;
class DisplayString;

struct EntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	Bool secretText;
	Bool numericalOnly;
	Bool alphaNumericalOnly;
	Bool aSCIIOnly;
	Short maxTextLen;
	Bool receivedUnichar;
	Bool drawTextFromStart;
	GameWindow *constructList;
	unsigned short charPos;
	unsigned short conCharPos;
};

struct ComboBoxData
{
	Bool isEditable;
	Int maxDisplay;
	Int maxChars;
	Bool asciiOnly;
	Bool lettersAndNumbersOnly;
	ListboxData *listboxData;
	EntryData *entryData;
	Bool dontHide;
	Int entryCount;
	GameWindow *dropDownButton;
	GameWindow *editBox;
	GameWindow *listBox;
};

class GameWindow
{
public:
	Int winSetEnabledColor(Int index, Int color);
	Int winSetEnabledBorderColor(Int index, Int color);
	Int winSetDisabledColor(Int index, Int color);
	Int winSetDisabledBorderColor(Int index, Int color);
	Int winSetHiliteColor(Int index, Int color);
	Int winSetHiliteBorderColor(Int index, Int color);
	void winSetEnabledTextColors(int, int);
	void winSetDisabledTextColors(int, int);
	void winSetHiliteTextColors(int, int);
	void winSetIMECompositeTextColors(int, int);
	void *winGetUserData(void);
};

#ifndef NULL
#define NULL 0
#endif

typedef Int Color;
class BfmeKeyLC;

// BFME moved the child windows to data +0x24/+0x28/+0x2C (drop-down button,
// edit box, list box: GadgetComboBoxGetText reads the edit box through
// 0x002C032C, GadgetComboBoxSetText selects in the list box through
// 0x002C0315). The three accessors keep the names their ledger rows carry,
// which follow Zero Hour's order: 0x002C032C GadgetComboBoxGetListBox (+0x28),
// 0x002C02FE GadgetComboBoxGetEditBox (+0x24), 0x002C0315 bfmeGo925A (+0x2C).
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);
GameWindow *GadgetComboBoxGetEditBox(GameWindow *comboBox);
void *bfmeGo925A(BfmeKeyLC *k);
void GadgetListBoxSetColors(GameWindow *listbox,
	Color enabledColor, Color enabledBorderColor,
	Color enabledSelectedItemColor, Color enabledSelectedItemBorderColor,
	Color disabledColor, Color disabledBorderColor,
	Color disabledSelectedItemColor, Color disabledSelectedItemBorderColor,
	Color hiliteColor, Color hiliteBorderColor,
	Color hiliteSelectedItemColor, Color hiliteSelectedItemBorderColor);

// ?GadgetComboBoxSetColors@@YAXPAVGameWindow@@HHHHHHHHHHHH@Z, retail 0x00322463
// (509B): the Zero Hour GadgetComboBox.cpp body with its GadgetComboBoxSet*/
// GadgetButtonSet* inline setters expanded; built /O1 it places uniquely.
void GadgetComboBoxSetColors( GameWindow *comboBox,
	Color enabledColor, Color enabledBorderColor,
	Color enabledSelectedItemColor, Color enabledSelectedItemBorderColor,
	Color disabledColor, Color disabledBorderColor,
	Color disabledSelectedItemColor, Color disabledSelectedItemBorderColor,
	Color hiliteColor, Color hiliteBorderColor,
	Color hiliteSelectedItemColor, Color hiliteSelectedItemBorderColor )
{
	// enabled
	comboBox->winSetEnabledColor( 0, enabledColor );
	comboBox->winSetEnabledBorderColor( 0, enabledBorderColor );
	comboBox->winSetEnabledColor( 1, enabledSelectedItemColor );
	comboBox->winSetEnabledBorderColor( 1, enabledSelectedItemBorderColor );
	// disabled
	comboBox->winSetDisabledColor( 0, disabledColor );
	comboBox->winSetDisabledBorderColor( 0, disabledBorderColor );
	comboBox->winSetDisabledColor( 1, disabledSelectedItemColor );
	comboBox->winSetDisabledBorderColor( 1, disabledSelectedItemBorderColor );
	// hilite
	comboBox->winSetHiliteColor( 0, hiliteColor );
	comboBox->winSetHiliteBorderColor( 0, hiliteBorderColor );
	comboBox->winSetHiliteColor( 1, hiliteSelectedItemColor );
	comboBox->winSetHiliteBorderColor( 1, hiliteSelectedItemBorderColor );

	GameWindow *editBox = GadgetComboBoxGetListBox( comboBox );	// data +0x28
	if (editBox)
	{
		editBox->winSetEnabledColor( 0, enabledColor );
		editBox->winSetEnabledBorderColor( 0, enabledBorderColor );
		editBox->winSetEnabledColor( 1, enabledSelectedItemColor );
		editBox->winSetEnabledBorderColor( 1, enabledSelectedItemBorderColor );
		editBox->winSetDisabledColor( 0, disabledColor );
		editBox->winSetDisabledBorderColor( 0, disabledBorderColor );
		editBox->winSetDisabledColor( 1, disabledSelectedItemColor );
		editBox->winSetDisabledBorderColor( 1, disabledSelectedItemBorderColor );
		editBox->winSetHiliteColor( 0, hiliteColor );
		editBox->winSetHiliteBorderColor( 0, hiliteBorderColor );
		editBox->winSetHiliteColor( 1, hiliteSelectedItemColor );
		editBox->winSetHiliteBorderColor( 1, hiliteSelectedItemBorderColor );
	}

	GameWindow *dropDownButton = GadgetComboBoxGetEditBox( comboBox );	// data +0x24
	if (dropDownButton)
	{
		dropDownButton->winSetEnabledColor( 0, enabledColor );
		dropDownButton->winSetEnabledBorderColor( 0, enabledBorderColor );
		dropDownButton->winSetEnabledColor( 1, enabledSelectedItemColor );
		dropDownButton->winSetEnabledBorderColor( 1, enabledSelectedItemBorderColor );
		dropDownButton->winSetDisabledColor( 0, disabledColor );
		dropDownButton->winSetDisabledBorderColor( 0, disabledBorderColor );
		dropDownButton->winSetDisabledColor( 1, disabledSelectedItemColor );
		dropDownButton->winSetDisabledBorderColor( 1, disabledSelectedItemBorderColor );
		dropDownButton->winSetHiliteColor( 0, hiliteColor );
		dropDownButton->winSetHiliteBorderColor( 0, hiliteBorderColor );
		dropDownButton->winSetHiliteColor( 1, hiliteSelectedItemColor );
		dropDownButton->winSetHiliteBorderColor( 1, hiliteSelectedItemBorderColor );
	}

	GameWindow *listBox = (GameWindow *)bfmeGo925A( (BfmeKeyLC *)comboBox );	// data +0x2C
	if ( listBox )
	{
		GadgetListBoxSetColors(listBox,
			enabledColor, enabledBorderColor,
			enabledSelectedItemColor, enabledSelectedItemBorderColor,
			disabledColor, disabledBorderColor,
			disabledSelectedItemColor, disabledSelectedItemBorderColor,
			hiliteColor, hiliteBorderColor,
			hiliteSelectedItemColor, hiliteSelectedItemBorderColor);
	}
}

// ?GadgetComboBoxSetMaxChars@@YAXPAVGameWindow@@H@Z, retail 0x003226E7 (28B).
void GadgetComboBoxSetMaxChars(GameWindow *comboBox, Int maxChars)
{
	if (comboBox == NULL)
		return;

	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	comboData->maxChars = maxChars;
	comboData->entryData->maxTextLen = maxChars;
}

// ?GadgetComboBoxSetMaxDisplay@@YAXPAVGameWindow@@H@Z, retail 0x00322703 (17B).
void GadgetComboBoxSetMaxDisplay(GameWindow *comboBox, Int maxDisplay)
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	comboData->maxDisplay = maxDisplay;
}

// ?GadgetComboBoxGetLength@@YAHPAVGameWindow@@@Z, retail 0x003229B1 (20B).
// Entry count lives at +0x20 (BFME ComboBoxData places the child windows at
// +0x24/+0x28/+0x2C); load by offset so the body matches retail.
Int GadgetComboBoxGetLength(GameWindow *comboBox)
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	if (comboData)
		return *(Int *)((char *)comboData + 0x20);

	return 0;
}

void GadgetComboBoxSetEnabledTextColors(GameWindow *comboBox, int color, int borderColor )
{
	// sanity
	if( comboBox == 0 )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2c);
	if(listBox)
		listBox->winSetEnabledTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetEnabledTextColors(color,borderColor);
}

void GadgetComboBoxSetDisabledTextColors(GameWindow *comboBox, int color, int borderColor )
{
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	// sanity
	if( comboBox == 0 )
		return;

	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetDisabledTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetDisabledTextColors(color,borderColor);
}

void GadgetComboBoxSetHiliteTextColors( GameWindow *comboBox,int color, int borderColor )
{
	// sanity
	if( comboBox == 0 )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	
	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetHiliteTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetHiliteTextColors(color,borderColor);
}

void GadgetComboBoxSetIMECompositeTextColors(GameWindow *comboBox, int color, int borderColor )
{
	// sanity
	if( comboBox == 0 )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();

	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetIMECompositeTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetIMECompositeTextColors(color,borderColor);
}
