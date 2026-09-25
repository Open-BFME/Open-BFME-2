// cl: /O1 /DNDEBUG /MD
//
// GadgetListBoxReset, retail 0x003247E5, 34 bytes.
// Dedicated TU so GameWindowManager.cpp bodies cannot see this wrapper.
// Null-checks the listbox then GLM_DEL_ALL (0x4013) through vtable +0xE8.

typedef int Int;
typedef bool Bool;
typedef short Short;

class GameWindow
{
public:
	void *winGetUserData(void);
	GameWindow *winGetChild(void);
};

class GameWindowManager
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57)
#undef V
	virtual int winSendSystemMsg(GameWindow *window, unsigned msg, int mData1, int mData2) = 0;
};

GameWindowManager *TheWindowManager;

void GadgetListBoxReset(GameWindow *listbox)
{
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4013, 0, 0);
}

// BFME1's GadgetComboBoxReset sends GCM_DEL_ALL through TheWindowManager.
// Retail at 0x0032273B confirms the 34B body, vtable slot +0xE8, and message
// value 0x4025; the name is carried from the donor callback and call sites.
enum { GCM_DEL_ALL = 0x4025 };

void GadgetComboBoxReset(GameWindow *comboBox)
{
	if (comboBox == 0)
		return;
	TheWindowManager->winSendSystemMsg(comboBox, GCM_DEL_ALL, 0, 0);
}

// ?GadgetListBoxGetNumEntries@@YAHPAVGameWindow@@@Z, retail 0x0032475A (25B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B77C0). The entry count is the Short endPos at +0x2C; keep the
// donor's test-true shape (jz over the load) for the retail branch layout.
Int GadgetListBoxGetNumEntries(GameWindow *listbox)
{
	if (!listbox)
		return 0;

	void *listboxData = listbox->winGetUserData();
	if (listboxData)
		return *(Short *)((char *)listboxData + 0x2C);

	return 0;
}

// ?GadgetListBoxSetAudioFeedback@@YAXPAVGameWindow@@_N@Z, retail 0x0032487B (25B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B7960). The click-feedback flag is the Bool at +0x0E.
void GadgetListBoxSetAudioFeedback(GameWindow *listbox, Bool enable)
{
	if (!listbox)
		return;

	void *listboxData = listbox->winGetUserData();
	if (!listboxData)
		return;

	*(Bool *)((char *)listboxData + 0x0E) = enable;
}

// ?GadgetListBoxGetNumColumns@@YAHPAVGameWindow@@@Z, retail 0x003248B1 (25B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B79B0). The column count is the Short at +0x02; keep the
// donor's test-false shape (jnz past the zero return) for the retail layout.
Int GadgetListBoxGetNumColumns(GameWindow *listbox)
{
	if (!listbox)
		return 0;

	void *listboxData = listbox->winGetUserData();
	if (!listboxData)
		return 0;

	return *(Short *)((char *)listboxData + 0x02);
}

// ?GadgetListBoxGetColumnWidth@@YAHPAVGameWindow@@H@Z, retail 0x003248CA (43B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B79D0). The widths array hangs at +0x14; the donor's
// columns-then-negative bound order is the retail cmp/jle + test/jl shape.
Int GadgetListBoxGetColumnWidth(GameWindow *listbox, Int column)
{
	if (!listbox)
		return 0;

	void *listboxData = listbox->winGetUserData();
	if (!listboxData)
		return 0;

	if (*(Short *)((char *)listboxData + 0x02) <= column || column < 0)
		return 0;

	return (*(Int **)((char *)listboxData + 0x14))[column];
}

// ?GadgetSliderGetEnabledSelectedThumbBorderColor@@YAHPAVGameWindow@@@Z, retail 0x00323D86 (23B).
// Ported from ZH GadgetSlider.h inline (BFME1 0x004B6910): the thumb child via
// winGetChild, its enabled-selected border color at +0x58, else 0x00FFFFFF.
Int GadgetSliderGetEnabledSelectedThumbBorderColor(GameWindow *slider)
{
	GameWindow *thumb = slider->winGetChild();
	if (thumb)
		return *(Int *)((char *)thumb + 0x58);

	return 0x00FFFFFF;
}

// ?GadgetListBoxGetTopVisibleEntry@@YAHPAVGameWindow@@@Z, retail 0x00324860 (27B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// (BFME1 0x004B7930). Retail passes the entry worker its argument in ecx, so
// the donor's mov edx,eax tail is a mov ecx,eax here and the worker is
// declared fastcall; the worker at 0x00323F78 is BFME2's top-entry scan.
struct _ListboxData;
typedef struct _ListboxData ListboxData;
int __fastcall Rva0032378(ListboxData *listData);

Int GadgetListBoxGetTopVisibleEntry(GameWindow *window)
{
	if (!window)
		return 0;

	ListboxData *listData = (ListboxData *)window->winGetUserData();
	if (!listData)
		return 0;

	return Rva0032378(listData);
}

// BFME2 top-entry scan, retail 0x00323F78 (36B). Same algorithm as the BFME1
// static getListboxTopEntry, but retail passes the list in ecx, walks rows
// with a 0x10 stride, and keeps only one saved register.
struct RvaTopRow
{
	Int listHeight;
	char pad[0x0C];
};

struct RvaTopLayout
{
	char pad0[0x18];
	RvaTopRow *rows;
	char pad1[0x10];
	Short endPos;
	char pad2[0x16];
	Short displayPos;
};

int __fastcall Rva0032378(ListboxData *list)
{
	Int entry;
	const RvaTopLayout *layout = (const RvaTopLayout *)list;

	// determine which entry is at the top of the display area
	for (entry = 0; ; entry++)
	{
		if (layout->rows[entry].listHeight > layout->displayPos)
			return entry;

		if (entry >= layout->endPos)
			return 0;
	}

	return 0;
}
