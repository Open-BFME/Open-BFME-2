// ?GadgetListBoxSetBottomVisibleEntry@@YAXPAVGameWindow@@H@Z
// partial score=0.96 date=2026-09-21
// cl: /O1 /DNDEBUG /MD /EHsc
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
typedef short Short;

template <typename T> class StringBase
{
	friend class UnicodeString;
	friend int GadgetListBoxAddEntryText(class GameWindow *, class UnicodeString, int, int, int, bool);
public:
	int getLength() const { return m_data ? m_data->length : 0; }
	void set(const StringBase<T> &other);
private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T text[1];
	};
	Header *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
	friend int GadgetListBoxAddEntryText(class GameWindow *, UnicodeString, int, int, int, bool);
public:
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &source)
	{
		set(*(const StringBase<unsigned short> *)&source);
		return *this;
	}
};

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

int Rva00324807(GameWindow *listbox);
bool GadgetListBoxIsFull(GameWindow *window);
void GadgetListBoxSetBottomVisibleEntry(GameWindow *window, int newPos);
void adjustDisplay(GameWindow *window, Bool updateSlider);

int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
	int color, int row, int column, bool overwrite)
{
	if (!listbox)
		return -1;

	if (text.m_data == 0 || text.m_data->length == 0)
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

	adjustDisplay(window, true);
}
