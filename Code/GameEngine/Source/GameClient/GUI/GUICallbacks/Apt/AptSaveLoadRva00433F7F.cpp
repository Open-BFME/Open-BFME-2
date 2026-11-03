// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00433F7F (94 bytes), AptSaveLoad: the item data of the selected
// entry of the first list box (+0x288), falling back to the second list box
// (+0x28C) when nothing is selected there. WorldBuilder's debug body
// (0x012AEB20, unnamed) returns zero without the first list box and the last
// GadgetListBoxGetItemData result otherwise; the callers (Delete, Load,
// SetDefaultFileName, 0x004340AC) test that result as a pointer.

class GameWindow;
void GadgetListBoxGetSelected(GameWindow *listbox, int *selectList);
void *GadgetListBoxGetItemData(GameWindow *window, int a, int b);

#include "../../../../../Include/GameClient/AptSaveLoad.h"

int AptSaveLoad::rva00433F7F()
{
	int selected;
	void *data;
	if (field288 == 0)
		return 0;
	GadgetListBoxGetSelected(field288, &selected);
	data = GadgetListBoxGetItemData(field288, selected, 0);
	if (selected < 0 && field28C != 0)
	{
		GadgetListBoxGetSelected(field28C, &selected);
		data = GadgetListBoxGetItemData(field28C, selected, 0);
	}
	return (int)data;
}
