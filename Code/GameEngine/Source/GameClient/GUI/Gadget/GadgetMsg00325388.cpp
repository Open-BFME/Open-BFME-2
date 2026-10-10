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

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	virtual void windowHiding(GameWindow *window) = 0;
	V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	virtual GameWindow *winGetFocus() = 0;
	virtual int winSetFocus(GameWindow *window) = 0;
	V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, UnsignedInt msg, WindowMsgData mData1, WindowMsgData mData2) = 0;
};

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
