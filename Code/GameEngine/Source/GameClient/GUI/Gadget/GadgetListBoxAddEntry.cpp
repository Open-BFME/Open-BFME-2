// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?moveRowsDown@@YAHPAU_ListboxData@@H@Z  Native 0x00324001..0x003240A6 (165 bytes)
// ?addEntry@@YAHPAVUnicodeString@@HHHPAVGameWindow@@_N@Z  Native 0x00325472..0x00325635 (451 bytes)
// GadgetListBox statics from ZH/BFME1 GadgetListBox.cpp (BFME1 donor
// game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp addEntry and
// moveRowsDown) with the BFME2 layout: 16-byte rows {listHeight height cell
// pad} and 0x1C-byte cells {type pad color data userData width height}; the
// text cell clears the word at +4. ListboxData: listLength +0 columns +2
// multiSelect +0xB columnWidth +0x14 listData +0x18 totalHeight +0x28 endPos
// +0x2C insertPos +0x2E selectPos +0x34 selections +0x38.
// moveRowsDown takes the list in ESI and the row on the stack; its only caller
// is addEntry. addEntry takes the column in EAX; its only retail caller is the
// GLM_ADD_ENTRY case of GadgetListBoxSystem 0x00325FBF. Both are private
// conventions of these statics. The dummy caller below is marked
// absent-from-retail and only gives cl the addEntry call site.
// Folded callees: winGetStatus is the 4-byte getter rowed as
// CategoryModuleClass<0>::getName 0x0030F45F and winGetFont the 7-byte getter
// rowed as Rva00313D6CDwordField::get 0x00313D6C.
#include <string.h>
#include "unicode_string.h"

typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned int UnsignedInt;

void *operator new[](unsigned int size);
void operator delete[](void *block);

class GameFont;

class FXParticleSystem
{
public:
	template <int N> class CategoryModuleClass
	{
	public:
		const char *getName() const;
	};
};

class Rva00313D6CDwordField
{
public:
	Int get() const;
};

class GameWindow
{
public:
	void *winGetUserData();
	UnsignedInt winGetStatus() { return (UnsignedInt)((FXParticleSystem::CategoryModuleClass<0> *)this)->getName(); }
	GameFont *winGetFont() { return (GameFont *)((Rva00313D6CDwordField *)this)->get(); }
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void setFont(GameFont *font);
	virtual void slot07();
	virtual void setWordWrap(Int width);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void getSize(Int *width, Int *height);
};

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;

struct ListEntryCell
{
	Int cellType;
	Int unknown04;
	Int color;
	void *data;
	void *userData;
	Int width;
	Int height;
};

struct ListEntryRow
{
	Int listHeight;
	Int height;
	ListEntryCell *cell;
	Int unknown0C;
};

struct _ListboxData
{
	Short listLength;
	Short columns;
	char m_pad04[0x0B - 0x04];
	Bool multiSelect;
	char m_pad0C[0x14 - 0x0C];
	Int *columnWidth;
	ListEntryRow *listData;
	char m_pad1C[0x28 - 0x1C];
	Int totalHeight;
	Short endPos;
	Short insertPos;
	char m_pad30[0x34 - 0x30];
	Int selectPos;
	Int *selections;
};
typedef _ListboxData ListboxData;

enum { LISTBOX_TEXT = 1 };
enum { WIN_STATUS_ONE_LINE = 0x4000 };
enum { TEXT_WIDTH_OFFSET = 7 };

void Rva00324AE5Update(GameWindow *window, Int adjustment, Bool updateSlider);
void computeTotalHeight(GameWindow *window);

static Int moveRowsDown(ListboxData *list, Int startingRow)
{
	Int copyLen = (list->endPos - startingRow) * sizeof(ListEntryRow);
	char *buf = new char[copyLen];
	memcpy(buf, &list->listData[startingRow], copyLen);
	memcpy(&list->listData[startingRow + 1], buf, copyLen);
	delete [] buf;
	list->endPos++;
	list->insertPos = list->endPos;
	list->listData[startingRow].cell = 0;
	list->listData[startingRow].height = 0;
	list->listData[startingRow].listHeight = 0;
	if (list->multiSelect)
	{
		Int i = 0;
		while (list->selections[i] >= 0)
		{
			if (startingRow <= list->selections[i])
				list->selections[i]++;
			i++;
		}
	}
	else
	{
		if (list->selectPos >= startingRow)
			list->selectPos++;
	}
	return 1;
}

static Int addEntry(UnicodeString *string, Int color, Int row, Int column, GameWindow *window, Bool overwrite)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	Int width;
	DisplayString *displayString;

	if (column >= list->columns || row >= list->listLength)
		return -1;

	if (row == -1)
	{
		row = list->insertPos;
		list->insertPos++;
		list->endPos++;
	}
	if (column == -1)
		column = 0;

	width = list->columnWidth[column] - TEXT_WIDTH_OFFSET;

	Int rowsAdded = 0;
	ListEntryRow *listRow = &list->listData[row];
	if (!listRow->cell)
	{
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}
	else if (!overwrite)
	{
		moveRowsDown(list, row);
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
		rowsAdded = 1;
	}

	listRow->cell[column].cellType = LISTBOX_TEXT;
	listRow->cell[column].unknown04 = 0;
	listRow->cell[column].color = color;

	if (!listRow->cell[column].data)
		listRow->cell[column].data = TheDisplayStringManager->newDisplayString();
	displayString = (DisplayString *)listRow->cell[column].data;
	if ((window->winGetStatus() & WIN_STATUS_ONE_LINE) == 0)
		displayString->setWordWrap(width);
	displayString->setText(*string);
	displayString->setFont(window->winGetFont());

	if (overwrite)
	{
		Int oldRowHeight = listRow->height;
		Int oldTotalHeight = listRow->listHeight;
		Int rowHeight;
		Int totalHeight;

		if (!oldTotalHeight && row)
			oldTotalHeight = list->listData[row - 1].listHeight;

		displayString->getSize(0, &rowHeight);
		if (rowHeight > oldRowHeight)
		{
			totalHeight = oldTotalHeight + (rowHeight - oldRowHeight);
			listRow->height = rowHeight;
			listRow->listHeight = totalHeight + rowsAdded;
			list->totalHeight += (rowHeight - oldRowHeight) + rowsAdded;
			Rva00324AE5Update(window, 0, true);
		}
	}
	else
	{
		computeTotalHeight(window);
	}

	return row;
}

struct AddMessageStruct
{
	Int row;
	Int column;
	void *data;
	Int type;
	Bool overwrite;
};

// ?addEntryCaller absent-from-retail
Int addEntryCaller(GameWindow *window, AddMessageStruct *addInfo, Int color)
{
	if (addInfo->type == LISTBOX_TEXT)
		return addEntry((UnicodeString *)addInfo->data, color, addInfo->row, addInfo->column, window, addInfo->overwrite);
	return 0;
}
