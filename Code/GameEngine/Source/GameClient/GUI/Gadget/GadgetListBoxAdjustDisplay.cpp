// cl: /O1 /DNDEBUG /MD
// ?Rva00324AE5Update@@YAXPAVGameWindow@@H_N@Z @0x00324AE5 84B: the list box
// display adjustment, called by the list box input callbacks with the window,
// a row delta and a slider flag. Reference semantics: Zero Hour
// GadgetListBox.cpp adjustDisplay (the address name is kept; the donor name
// is not proven here). Target facts: when the flag is set, the top entry
// from the fastcall 0x00323F78 plus the delta is clamped to [0, endPos - 1]
// (endPos the short at +0x2C) and the display position (short at +0x44)
// becomes that 16-byte row's listHeight (+0) less its height (short at +4),
// indexing the row array at +0x18; 0x003249D2 then refreshes the display.
typedef int Int;
typedef short Short;
typedef bool Bool;

class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryRow
{
	Int listHeight;
	Short height;
	Short m_pad06;
	void *cell;
	void *colors;
};

typedef struct _ListboxData
{
	unsigned char m_pad00[0x18];
	ListEntryRow *listData;
	unsigned char m_pad1C[0x2C - 0x1C];
	Short endPos;
	unsigned char m_pad2E[0x44 - 0x2E];
	Short displayPos;
} ListboxData;

Int __fastcall Rva0032378(_ListboxData *listData);
void Rva003249D2(GameWindow *window, Bool updateSlider);

void Rva00324AE5Update(GameWindow *window, Int adjustment, Bool updateSlider)
{
	Int entry;
	ListboxData *list = (ListboxData *)window->winGetUserData();

	if (updateSlider)
	{
		entry = Rva0032378(list) + adjustment;
		if (entry <= 0)
			entry = 0;
		else if (entry >= list->endPos)
			entry = list->endPos - 1;
		list->displayPos = list->listData[entry].listHeight - list->listData[entry].height;
	}
	Rva003249D2(window, updateSlider);
}
