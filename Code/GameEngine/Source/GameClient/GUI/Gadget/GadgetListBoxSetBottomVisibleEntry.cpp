// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// GadgetListBoxSetBottomVisibleEntry, retail 0x003253FD, 79 bytes: after the null and
// user-data guards it bounds-checks the requested row against the display height,
// sets the display position from that row height and refreshes the display through
// Rva003249D2 (the ZH source calls this adjustDisplay; that identity is not proven
// here, so the existing address-derived ledger name is used). The struct layouts below
// are the minimum the body needs.

typedef bool Bool;
typedef int Int;
typedef short Short;

#include "unicode_string.h"


class GameWindow
{
public:
	void *winGetUserData();
};

struct ListEntryRow
{
	Int listHeight;
	short rowTop;
	short m_unused06;
	void *cell;
	Int m_unmodelled0C;
};

struct ListboxData
{
	short listLength;
	short columns;
	unsigned char m_unmodelled04[9];
	Bool scrollIfAtEnd;
	unsigned char m_unmodelled0E[0x0A];
	ListEntryRow *listData;
	unsigned char m_unmodelled1C[0x10];
	short endPos;
	unsigned char m_unmodelled2E[0x0E];
	Short displayHeight;
	unsigned char m_unmodelled3E[0x06];
	Short displayPos;
};

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

class GameWindowManager
{
public:
	virtual ~GameWindowManager() {}
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad0A() = 0;
	virtual void pad0B() = 0;
	virtual void pad0C() = 0;
	virtual void pad0D() = 0;
	virtual void pad0E() = 0;
	virtual void pad0F() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual void pad15() = 0;
	virtual void pad16() = 0;
	virtual void pad17() = 0;
	virtual void pad18() = 0;
	virtual void pad19() = 0;
	virtual void pad1A() = 0;
	virtual void pad1B() = 0;
	virtual void pad1C() = 0;
	virtual void pad1D() = 0;
	virtual void pad1E() = 0;
	virtual void pad1F() = 0;
	virtual void pad20() = 0;
	virtual void pad21() = 0;
	virtual void pad22() = 0;
	virtual void pad23() = 0;
	virtual void pad24() = 0;
	virtual void pad25() = 0;
	virtual void pad26() = 0;
	virtual void pad27() = 0;
	virtual void pad28() = 0;
	virtual void pad29() = 0;
	virtual void pad2A() = 0;
	virtual void pad2B() = 0;
	virtual void pad2C() = 0;
	virtual void pad2D() = 0;
	virtual void pad2E() = 0;
	virtual void pad2F() = 0;
	virtual void pad30() = 0;
	virtual void pad31() = 0;
	virtual void pad32() = 0;
	virtual void pad33() = 0;
	virtual void pad34() = 0;
	virtual void pad35() = 0;
	virtual void pad36() = 0;
	virtual void pad37() = 0;
	virtual void pad38() = 0;
	virtual Int winSendSystemMsg(GameWindow *window, unsigned int message,
		unsigned int data1, unsigned int data2) = 0;
};

extern GameWindowManager *TheWindowManager;

void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, int newPos);
void Rva003249D2(GameWindow *window, Bool updateSlider);

void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, Int newPos)
{
	if (!window)
		return;

	if (!window->winGetUserData())
		return;

	ListboxData *listData = (ListboxData *)window->winGetUserData();

	if (newPos < 0)
		return;

	if (listData->listData[newPos].listHeight <= listData->displayHeight)
		return;

	if (listData->listData[newPos].listHeight <= listData->displayHeight)
		return;

	listData->displayPos = listData->listData[newPos].listHeight - listData->displayHeight + 1;

	Rva003249D2(window, true);
}
