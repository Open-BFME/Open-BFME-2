// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00326BEC, 260 bytes (the reloc size 10 is stale).
// GadgetListBoxAddEntryText, the listbox text insertion body called by
// AptMapPreview::bfmeSetMapDescription. Ported from Open-BFME-1
// (Code/GameEngine/Source/Common/GadgetListBoxAddEntryText_Thunk.cpp,
// retail 0x004BB4B0, 357 bytes): null window guards -1, empty text takes
// L" ", the AddMessageStruct carries row/column/text-pointer/type-1/
// overwrite/-1/-1, then the scroll-if-at-end tail. Three pins batch with the
// row: winGetUserData (pre-existing), the B1 cdecl IsFull and
// SetBottomVisibleEntry names (both fit the observed arities), and an opaque
// Rva00324807 for the null-guarded bottom-entry delegate (its true name is
// unknown; it wraps winGetUserData with a tail jump to 0x323F9C). The empty
// test reads the length field directly, not via getLength(); isEmpty stays
// undefined because it owns no row. Out-of-line copies fold with the string
// rows like the sibling TUs.

typedef bool Bool;
typedef int Int;

#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"

// StringBase keeps m_data private; the empty test reads the buffer header's
// length field directly (not getLength()), so view the string's one pointer.
struct UnicodeStringBufferView
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
	};
	Header *m_data;
};


#include "../../../Include/GameClient/Bfme2GameWindow.h"

#include "../../../Include/GameClient/ListboxData.h"

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

#include "../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

int Rva00324807(GameWindow *listbox);
bool GadgetListBoxIsFull(GameWindow *window);
void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, int newPos);

int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite)
{
	if (!listbox)
		return -1;

	const UnicodeStringBufferView &buffer = (const UnicodeStringBufferView &)text;
	if (buffer.m_data == 0 || buffer.m_data->length == 0)
		text = UnicodeString(L" ");

	AddMessageStruct addInfo;
	addInfo.row = row;
	addInfo.column = column;
	addInfo.type = 1;
	addInfo.data = &text;
	addInfo.overwrite = overwrite;
	addInfo.height = -1;
	addInfo.width = -1;

	ListboxData *listData = (ListboxData *)listbox->winGetUserData();
	Bool wasFull = listData->listLength <= listData->endPos;
	Int newEntryOffset = wasFull ? 0 : 1;

	Int oldBottomIndex = Rva00324807(listbox);

	Int index = TheWindowManager->winSendSystemMsg(listbox, 0x4011,
		(unsigned int)&addInfo, (unsigned int)color);

	if (listData->scrollIfAtEnd && index - oldBottomIndex == newEntryOffset &&
		GadgetListBoxIsFull(listbox))
		GadgetListBoxSetBottomVisibleEntry(listbox, index);

	return index;
}
