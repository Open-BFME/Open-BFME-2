// cl: /DNDEBUG /MD
// Retail RVA 0x00324822, 62 bytes.
// GadgetListBoxIsFull, the listbox fullness test feeding the insert tail.
// Ported from Open-BFME-1 GadgetListBox.cpp with an explicit rows temporary:
// the temporary pins the rows load ahead of the bottom-entry call exactly as
// retail does (B1 spells it inline). B2 rows stride 16, not B1's 12, and the
// comparison returns directly (setge). One opaque pin batches with the row:
// the reg-arg bottom-entry worker (B1 static role, true name unknown). The
// TU defines only this body.

typedef int Int;
typedef short Short;
typedef bool Bool;

class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryRowBFME
{
	int listHeight;
	short rowTop;
	short unused6;
	void *cell;
	int unused0C;
};

struct ListboxDataBFME
{
	char unused00[0x18];
	ListEntryRowBFME *listData;
	char unused1c[0x10];
	short endPos;
	char unused2e[0x0e];
	short displayHeight;
	char unused3e[6];
	short displayPos;
};

struct _ListboxData
{
	char unused00[0x18];
	ListEntryRowBFME *listData;
	char unused1c[0x10];
	short endPos;
	char unused2e[0x0e];
	short displayHeight;
	char unused3e[6];
	short displayPos;
};
typedef struct _ListboxData ListboxData;

int __fastcall Rva00323F9C(ListboxData *list);

bool GadgetListBoxIsFull(GameWindow *window)
{
	if (!window)
		return false;
	ListboxDataBFME *listData = (ListboxDataBFME *)window->winGetUserData();
	if (!listData)
		return false;

	ListEntryRowBFME *rows = listData->listData;
	Int entry = Rva00323F9C((ListboxData *)listData);
	if (rows[entry].listHeight >=
		listData->displayPos + listData->displayHeight - 5)
		return true;
	else
		return false;
}
