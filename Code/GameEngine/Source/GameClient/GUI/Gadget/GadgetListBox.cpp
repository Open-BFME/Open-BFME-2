// cl: /DNDEBUG /MD
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
	Int winHide(Bool hide);
	Bool winIsHidden(void);
};

GameWindow *GadgetComboBoxGetEditBox(GameWindow *comboBox);
GameWindow *GadgetListBoxGetDownButton(GameWindow *listbox);
GameWindow *GadgetListBoxGetSlider(GameWindow *listbox);

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

extern GameWindowManager *TheWindowManager;  // defined in GameWindowManager.cpp

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

// ?GadgetListBoxGetSelected@@YAXPAVGameWindow@@PAH@Z, retail 0x00324773, 37 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// GadgetListBoxGetSelected (BFME1 0x004B7xxx): null-guards the listbox then
// winSendSystemMsg 0x4018 with mData1 0 and the select list pointer through
// vtable slot +0xE8. Callers at 0x00323694 and 0x005B5C11 pass a stack Int slot.
void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList)
{
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4018, 0, (int)selectList);
}

// ?GadgetListBoxSetSelected@@YAXPAVGameWindow@@H@Z, retail 0x00324798, 38 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// GadgetListBoxSetSelected single-index overload: null-guards the listbox then
// winSendSystemMsg 0x4017 with the index address and count 1 through slot +0xE8.
void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex)
{
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4017, (int)&selectIndex, 1);
}

// ?GadgetListBoxSetSelected@@YAXPAVGameWindow@@PBHH@Z, retail 0x003247BE, 39 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// GadgetListBoxSetSelected list overload: null-guards the listbox then
// winSendSystemMsg 0x4017 with the list pointer and count through slot +0xE8.
// Caller at 0x00326FAD pushes count then list then window.
void GadgetListBoxSetSelected(GameWindow *listbox, const Int *selectList, Int selectCount)
{
	if (listbox == 0)
		return;
	TheWindowManager->winSendSystemMsg(listbox, 0x4017, (int)selectList, selectCount);
}

// Candidate 0x0032434A 54B: null-guarded listbox cell store through winGetUserData.
// listLength bound at +0x00, rows at +0x18 (16B stride, cell at +8), cells 28B
// stride with the stored value at +4. Callers pass row then column then value.
struct Rva2434ACell
{
	Int cellType;
	Int color;
	Int data;
	Int userData;
	Int width;
	Int height;
	Int pad18;
};

struct Rva2434ARow
{
	Int listHeight;
	Int height;
	Rva2434ACell *cell;
	Int padC;
};

struct Rva2434AData
{
	Short listLength;
	char pad2[0x16];
	Rva2434ARow *listData;
};

void Rva0032434ASet(GameWindow *listbox, Int row, Int column, Int value)
{
	if (listbox == 0)
		return;
	Rva2434AData *data = (Rva2434AData *)listbox->winGetUserData();
	if (data == 0)
		return;
	if ((unsigned)row >= (unsigned)data->listLength)
		return;
	data->listData[row].cell[column].color = value;
}

// ?GadgetListBoxAddEntryImage@@YAHPAVGameWindow@@PBVImage@@HHHH_NH@Z, retail 0x00324380, 80 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// GadgetListBoxAddEntryImage 8-arg overload: builds the 28B AddMessageStruct
// with type LISTBOX_IMAGE (2) and sends GLM_ADD_ENTRY 0x4011 through slot +0xE8.
class Image;

struct AddMessageStruct
{
	Int row;
	Int column;
	const void *data;
	Int type;
	Bool overwrite;
	Int width;
	Int height;
};

Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, Int row, Int column, Int hight, Int width, Bool overwrite, Int color)
{
	AddMessageStruct addInfo;
	addInfo.row = row;
	addInfo.column = column;
	addInfo.type = 2;
	addInfo.data = image;
	addInfo.overwrite = overwrite;
	addInfo.height = hight;
	addInfo.width = width;
	return TheWindowManager->winSendSystemMsg(listbox, 0x4011, (int)&addInfo, color);
}

// ?GadgetListBoxAddEntryImage@@YAHPAVGameWindow@@PBVImage@@HH_NH@Z, retail 0x003243D0, 35 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp
// GadgetListBoxAddEntryImage 6-arg overload: forwards to the 8-arg body with
// hight -1 and width -1.
Int GadgetListBoxAddEntryImage(GameWindow *listbox, const Image *image, Int row, Int column, Bool overwrite, Int color)
{
	return GadgetListBoxAddEntryImage(listbox, image, row, column, -1, -1, overwrite, color);
}

// ?GadgetComboBoxGetSelectedPos@@YAXPAVGameWindow@@PAH@Z, retail 0x003228EB (37B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBox.cpp
// GadgetComboBoxGetSelectedPos (BFME1 same name). Null-checks the combobox then
// GCM_GET_SELECTION (0x402c in BFME2, +3 from ZH 0x4029) through TheWindowManager
// at 0x9FEF1C slot 58 0xE8 with mData1=0 and mData2=selectedIndex. Caller
// 0x00322910 passes a stack slot address and returns it, proving Int* out-param.
void GadgetComboBoxGetSelectedPos(GameWindow *comboBox, Int *selectedIndex)
{
	if (comboBox == 0)
		return;
	TheWindowManager->winSendSystemMsg(comboBox, 0x402c, 0, (int)selectedIndex);
}

// ?Rva0032277F@@YAXPAVGameWindow@@_N@Z, retail 0x0032277F (33B).
// Null-checks the combobox, gets its edit box via rowed GadgetComboBoxGetEditBox,
// null-checks that, then hides it with the Bool arg via rowed GameWindow::winHide.
// Callers at 0x0057E17D/0x0057E643. True name unknown, honest address name.
void Rva0032277F(GameWindow *comboBox, Bool hide)
{
	if (comboBox == 0)
		return;
	GameWindow *editBox = GadgetComboBoxGetEditBox(comboBox);
	if (editBox == 0)
		return;
	editBox->winHide(hide);
}

// ?GadgetComboBoxHideList@@YAXPAVGameWindow@@@Z, retail 0x0032275D (34B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetComboBox.cpp
// GadgetComboBoxHideList: null-checks the combobox then GGM_CLOSE (0x4005)
// through TheWindowManager at 0x9FEF1C slot 58 0xE8. Same xor-shape as the
// landed GadgetComboBoxReset 0x0032273B (34B). Callers at 0x00440617 etc.
void GadgetComboBoxHideList(GameWindow *comboBox)
{
	if (comboBox == 0)
		return;
	TheWindowManager->winSendSystemMsg(comboBox, 0x4005, 0, 0);
}

// ?GadgetComboBoxSetItemData@@YAXPAVGameWindow@@HPAX@Z, retail 0x0032295A (39B).
// Ported from Open-BFME-1 GadgetComboBox.cpp GadgetComboBoxSetItemData.
// Null-checks the combobox then GCM_SET_ITEM_DATA (0x402b in BFME2, +3 from
// ZH 0x4028) through TheWindowManager at 0x9FEF1C slot 58 0xE8 with
// mData1=index and mData2=data. 37 callers.
void GadgetComboBoxSetItemData(GameWindow *comboBox, Int index, void *data)
{
	if (comboBox == 0)
		return;
	TheWindowManager->winSendSystemMsg(comboBox, 0x402b, index, (int)data);
}

// ?GadgetComboBoxSetSelectedPos@@YAXPAVGameWindow@@H_N@Z, retail 0x00322931 (41B).
// Ported from Open-BFME-1 GadgetComboBox.cpp GadgetComboBoxSetSelectedPos.
// Null-checks the combobox then GCM_SET_SELECTION (0x402d in BFME2, +3 from
// ZH 0x402a) through TheWindowManager at 0x9FEF1C slot 58 0xE8 with
// mData1=selectedIndex and mData2=dontHide (movzx bool). 37 callers.
void GadgetComboBoxSetSelectedPos(GameWindow *comboBox, Int selectedIndex, Bool dontHide)
{
	if (comboBox == 0)
		return;
	TheWindowManager->winSendSystemMsg(comboBox, 0x402d, selectedIndex, (int)dontHide);
}

// ?GadgetComboBoxGetItemData@@YAPAXPAVGameWindow@@H@Z, retail 0x00322981 (48B).
// Ported from Open-BFME-1 GadgetComboBox.cpp GadgetComboBoxGetItemData.
// Null data local, then GCM_GET_ITEM_DATA (0x402a in BFME2, +3 from ZH 0x4027)
// through TheWindowManager at 0x9FEF1C slot 58 0xE8 with mData1=index and
// mData2=&data; returns data. 26 callers.
void *GadgetComboBoxGetItemData(GameWindow *comboBox, Int index)
{
	void *data = 0;
	if (comboBox != 0)
		TheWindowManager->winSendSystemMsg(comboBox, 0x402a, index, (int)&data);
	return data;
}

// ?Rva003248F5Show@@YAXPAVGameWindow@@_N@Z @0x003248F5 115B
// Listbox children visibility sync: editbox via ComboBoxGetEditBox plus downbutton and slider, hide where isHidden != flag.
// Evidence: GadgetComboBoxGetEditBox 0x002C02FE GadgetListBoxGetDownButton 0x002C02D0 GadgetListBoxGetSlider 0x002C02E7
// winIsHidden 0x00313CD9 winHide 0x00313C64 unlock same TU.
void Rva003248F5Show(GameWindow *listbox, Bool hide)
{
	if (listbox == 0)
		return;
	GameWindow *editBox = GadgetComboBoxGetEditBox(listbox);
	if (editBox != 0 && editBox->winIsHidden() != hide)
		editBox->winHide(hide);
	GameWindow *downButton = GadgetListBoxGetDownButton(listbox);
	if (downButton != 0 && downButton->winIsHidden() != hide)
		downButton->winHide(hide);
	GameWindow *slider = GadgetListBoxGetSlider(listbox);
	if (slider != 0 && slider->winIsHidden() != hide)
		slider->winHide(hide);
}

// ?Rva0032431FSet@@YAXPAVGameWindow@@HE@Z, retail 0x0032431F, 43 bytes.
// Listbox row flag store: null-guards listbox and user data, bounds row
// against Short listLength at +0x00, stores byte value at rows[row]+0x0C.
// Rows hang at +0x18 with 16B stride like Rva0032434ASet. Caller at
// 0x00322732 cleans 0xC (3 __cdecl args). Evidence: rowed winGetUserData.
struct Rva2431FRow
{
	Int f00;
	Int f04;
	Int f08;
	unsigned char f0C;
	char pad0D[3];
};

struct Rva2431FData
{
	Short listLength;
	char pad02[0x16];
	Rva2431FRow *rows;
};

void Rva0032431FSet(GameWindow *listbox, Int row, unsigned char value)
{
	if (listbox == 0)
		return;
	Rva2431FData *data = (Rva2431FData *)listbox->winGetUserData();
	if (data == 0)
		return;
	if ((unsigned)row >= (unsigned)data->listLength)
		return;
	data->rows[row].f0C = value;
}

// BFME1 6d943426 donor; native multiselect byte+B and signed16 capacity+0.
Int GadgetListBoxGetListLength(GameWindow *listbox)
{
 void *listboxData=listbox->winGetUserData();
 if(*(Bool *)((char *)listboxData+0x0B))
  return *(Short *)listboxData;
 else return 1;
}
