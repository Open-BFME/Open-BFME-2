// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?GadgetComboBoxSetText@@YAXPAVGameWindow@@VUnicodeString@@@Z @0x00322D63 98B.
// BFME1 donor GadgetComboBoxAccessors.cpp GadgetComboBoxSetText: null guard then
// ListBoxSetSelected(listBox -1) then TextEntrySetText(entry text).
// Retail calls 0x002C0315 listBox accessor at +0x2c rowed as bfmeGo925A then
// 0x00324798 SetSelected then 0x002C032C entry accessor at +0x28 rowed as
// GetListBox then 0x002C17EB TextEntrySetText; 8 callers include 0x0043F88F.
typedef unsigned short wchar_t;
typedef int Int;

#ifndef NULL
#define NULL 0
#endif

#include "unicode_string.h"


class GameWindow;
class BfmeKeyLC;

void *bfmeGo925A(BfmeKeyLC *k);
GameWindow *GadgetComboBoxGetListBox(GameWindow *comboBox);
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);
void GadgetTextEntrySetText(GameWindow *g, UnicodeString text);

void GadgetComboBoxSetText(GameWindow *comboBox, UnicodeString text)
{
	if (comboBox == NULL)
		return;
	GadgetListBoxSetSelected((GameWindow *)bfmeGo925A((BfmeKeyLC *)comboBox), -1);
	GadgetTextEntrySetText(GadgetComboBoxGetListBox(comboBox), text);
}
