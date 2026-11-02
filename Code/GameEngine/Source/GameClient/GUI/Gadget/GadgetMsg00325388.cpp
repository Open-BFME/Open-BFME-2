// cl: /Ob0
//
// Zero Hour's GadgetListBox.cpp item-data pair (BFME 1 rows of the same
// names, 0x004B84A0 / 0x004B84F0):
//
// ?GadgetListBoxSetItemData@@YAXPAVGameWindow@@PAXHH@Z, retail 0x00325388,
// 54 bytes: builds the ICoord2D cell (x = column at -8, y = row at -4) and,
// when the list box is non-null, sends message 0x4021 (cell, data)
// through TheWindowManager (0x00DFEF1C) winSendSystemMsg, vtable slot 0xE8.
//
// ?GadgetListBoxGetItemData@@YAPAXPAVGameWindow@@HH@Z, retail 0x003253BE,
// 63 bytes: data = NULL, same cell, sends message 0x4020 (cell,
// &data) and returns data.
//
// Identity: the BFME 1 donor bodies (compiled /O1) place uniquely at both
// addresses (donor_sweep pins); message ids, argument order and the
// column-then-row cell match Zero Hour; WorldBuilder twins 0x011512D0 and
// 0x01151330 have the same shape; GadgetComboBoxSystem (Zero Hour source)
// calls both by these names.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class GameWindow;

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column)
{
	struct ICoord2DView
	{
		int x;
		int y;
	};
	ICoord2DView pos;
	pos.x = column;
	pos.y = row;
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4021, (WindowMsgData)&pos, (WindowMsgData)data);
}

void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column)
{
	struct ICoord2DView
	{
		int x;
		int y;
	};
	ICoord2DView pos;
	void *data = 0;
	pos.x = column;
	pos.y = row;
	if (listbox != 0)
		TheWindowManager->winSendSystemMsg(listbox, 0x4020, (WindowMsgData)&pos, (WindowMsgData)&data);
	return data;
}
