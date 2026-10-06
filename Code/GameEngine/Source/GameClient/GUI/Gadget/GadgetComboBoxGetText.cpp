// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?GadgetComboBoxGetText@@YA?AVUnicodeString@@PAVGameWindow@@@Z @0x00322D21 66B.
// ZH donor GadgetComboBox.cpp GadgetComboBoxGetText: null -> empty,
// GWS_COMBO_BOX 0x8000 check via winGetStyle, else TextEntryGetText of child.
// Retail calls 0x002C032C +0x28 child and 0x00320AAB TextEntryGetText;
// 11 callers include 0x0043E3AA 0x0056EAC8 0x0057F3D8. Empty at 0xA0C898.
typedef unsigned short wchar_t;
typedef unsigned int UnsignedInt;
#define BitTest(x, i) (((x) & (i)) != 0)
#define GWS_COMBO_BOX 0x00008000
#ifndef NULL
#define NULL 0
#endif
#include "unicode_string.h"
class GameWindow
{
public:
	UnsignedInt winGetStyle();
};
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
UnicodeString GadgetComboBoxGetText(GameWindow *comboBox)
{
	if (comboBox == NULL)
		return UnicodeString::TheEmptyString;
	if (BitTest(comboBox->winGetStyle(), GWS_COMBO_BOX) == 0)
		return UnicodeString::TheEmptyString;
	return GadgetTextEntryGetText(GadgetComboBoxGetListBox(comboBox));
}
