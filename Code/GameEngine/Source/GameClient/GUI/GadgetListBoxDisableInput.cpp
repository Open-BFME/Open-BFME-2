// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00326DE9, 56 bytes.
// Listbox input teardown: if data flag +0x0B is set, frees array at +0x38 via
// vector-delete, clears it and the flag, and restores GadgetListBoxInput
// (pin 0x00325635) through winSetInputFunc (0x00314147).
// Evidence: winGetUserData 0x005C4ACD, vector-delete 0x0002FD80,
// winSetInputFunc 0x00314147, caller at 0x00326F87.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

class GameWindow;
typedef WindowMsgHandledType (__cdecl *GameWinInputFunc)(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);

class GameWindow
{
public:
	void *winGetUserData();
	Int winSetInputFunc(GameWinInputFunc input);
};

WindowMsgHandledType __cdecl GadgetListBoxInput(GameWindow *win, UnsignedInt a, WindowMsgData b, WindowMsgData c);
void __cdecl operator delete[](void *p);

struct ListBoxTeardownData
{
	unsigned char pad0[0x0B];
	unsigned char flag;
	unsigned char pad1[0x38 - 0x0C];
	void *array;
};

void Rva00326DE9Disable(GameWindow *win)
{
	ListBoxTeardownData *data = (ListBoxTeardownData *)win->winGetUserData();
	if (!data->flag)
		return;
	if (data->array) {
		::operator delete[](data->array);
		data->array = 0;
	}
	data->flag = 0;
	win->winSetInputFunc(GadgetListBoxInput);
}
