// cl: /DNDEBUG /MD
//
// ?rva00323700@Rva00323700@@QAEHI@Z, retail 0x00323700, 54 bytes.
// __thiscall int method on the one-pointer combo window view (this+0 is the
// GameWindow*, as in the rowed siblings 0x003236C4 and 0x003236E8): through
// the combo user data's list box (+8) and that list box's own user data,
// return entry `index` of the dword array at +0x14 when index is below the
// short at +2 (unsigned compare), else 0.
// Evidence: both calls are the rowed winGetUserData 0x005C4ACD; the list box
// at combo user data +8 is shared with GadgetImageComboBox.cpp. Field
// meanings are not established; names are address-derived.

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

struct Rva00323700ComboData
{
	char m_pad[8];
	GameWindow *m_listBox;
};

struct Rva00323700ListData
{
	short m_00;
	short m_count;		// +0x02
	char m_pad04[0x14 - 0x04];
	int *m_entries;		// +0x14
};

class Rva00323700
{
public:
	int rva00323700(unsigned int index);
private:
	GameWindow *m_win;
};

static inline GameWindow *rva00323700ListBox(GameWindow *win)
{
	Rva00323700ComboData *combo = (Rva00323700ComboData *)win->winGetUserData();
	if (combo == 0)
		return 0;
	return combo->m_listBox;
}

static inline Rva00323700ListData *rva00323700List(GameWindow *win)
{
	GameWindow *listBox = rva00323700ListBox(win);
	if (listBox == 0)
		return 0;
	return (Rva00323700ListData *)listBox->winGetUserData();
}

int Rva00323700::rva00323700(unsigned int index)
{
	Rva00323700ListData *list = rva00323700List(m_win);
	if (list == 0)
		return 0;
	if (index >= (unsigned int)list->m_count)
		return 0;
	return list->m_entries[index];
}
