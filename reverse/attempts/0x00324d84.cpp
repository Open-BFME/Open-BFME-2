// ?addImageEntry@@YAHPBVImage@@HHHPAVGameWindow@@HH@Z
// partial score=0.95 date=2026-10-08
// Caller map of GadgetListBoxSystem 0x325FBF (retail, read 2026-10-08; BFME1 donor
// GadgetListBox.cpp:1247, ZH GadgetListBox.cpp:1267). Messages above 0x4017 use a
// jump table at 0x726BBE (msg - 0x4018, 10 entries).
//   GWM_CREATE 1 / GWM_DESTROY 2: DESTROY counts j down from columns-1, `if(!cells) break`.
//   0x1c: calls Rva003248F5Show.  GGM_RESIZED 0x4004 adds a word-wrap re-layout loop
//   and a trailing selection scroll.  GLM_DEL_ENTRY 0x4012: cell loop uses j <= columns.
//   GLM_ADD_ENTRY 0x4011: type 1 -> addEntry(eax=column), type 2 -> addImageEntry;
//   then autoScroll via Rva00324AE5Update(win,1,1) while row >= displayPos+displayHeight,
//   then multiSelect clears selections, else selectPos==row -> -1, Rva003249D2(win,1).
//   0x400C: displayPos = slider userData->+4 minus mData2, Rva00324B39Add(win,0,0).
//   0x4008: up/down buttons; font height when +0x10 set, else Update(win,-1/1,1).
//   GLM_SET_SELECTION 0x4017: +0x48=-1; multi copies list until -1/endPos/empty row;
//   single sets selectPos and sends 0x4014 to the owner if parent style & 0x8000,
//   else jumps to the shared scroll-to-selection tail.
//   Table: GET_TEXT (cell type 1 -> getText via vslot 8, copies color into +4; else
//   empty string 0xe0c898), TOGGLE_MULTI_SELECTION (add/remove via removeSelection),
//   purge-top rows (frees text cells via TheDisplayStringManager slot 0x3c, ??_V the
//   row, memcpy rows down, endPos/insertPos -= n, fix selections, Update(win,-n,1)),
//   GET_SELECTION, SET_UP_BUTTON +0x1c, SET_DOWN_BUTTON +0x20, SET_SLIDER +0x24,
//   SET_BOTTOM (displayPos from row height), SET_ITEM_DATA / GET_ITEM_DATA (+0x10).
// cl: /O1 /G7 /DNDEBUG /MD
typedef int Int;
typedef short Short;
typedef int Color;
typedef bool Bool;
extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);
void *operator new[](unsigned int size);

class Image;
class DisplayString;

class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryCell
{
	Int cellType;
	Int m_field04;
	Color color;
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
	Bool m_disabled;
};

struct ListboxData
{
	Short listLength;
	Short columns;
	unsigned char m_pad04[0x18 - 0x04];
	ListEntryRow *listData;
	unsigned char m_pad1C[0x2C - 0x1C];
	Short endPos;
	Short insertPos;
};

class GlobalData
{
public:
	unsigned char m_pad00[0x30];
	Int m_xResolution;
	Int m_yResolution;
};
extern GlobalData *TheGlobalData;

class DisplayStringManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14)
#undef V
	virtual void freeDisplayString(DisplayString *string) = 0;
};
extern DisplayStringManager *TheDisplayStringManager;

enum { LISTBOX_TEXT = 1, LISTBOX_IMAGE = 2 };

void computeTotalHeight(GameWindow *window);

static Int addImageEntry(const Image *image, Color color, Int row, Int column, GameWindow *window, Int width, Int height)
{
	ListboxData *list = (ListboxData *)window->winGetUserData();
	Int scaledWidth = TheGlobalData->m_xResolution * width / 1024;
	height = TheGlobalData->m_yResolution * height / 768;

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

	ListEntryRow *listRow = &list->listData[row];

	if (!listRow->cell)
	{
		listRow->cell = new ListEntryCell[list->columns];
		memset(listRow->cell, 0, list->columns * sizeof(ListEntryCell));
	}
	if (listRow->cell[column].cellType == LISTBOX_TEXT)
		TheDisplayStringManager->freeDisplayString((DisplayString *)listRow->cell[column].data);

	listRow->cell[column].cellType = LISTBOX_IMAGE;
	listRow->cell[column].m_field04 = 0;
	listRow->cell[column].data = (void *)image;
	listRow->cell[column].color = color;
	listRow->cell[column].height = height;
	listRow->cell[column].width = scaledWidth;

	computeTotalHeight(window);

	return row;
}

Int forceAIE(const Image *image, Color color, Int row, Int column, GameWindow *window, Int width, Int height)
{
	return addImageEntry(image, color, row, column, window, width, height);
}
