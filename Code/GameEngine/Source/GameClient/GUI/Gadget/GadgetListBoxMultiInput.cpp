// cl: /O1 /DNDEBUG /MD
// List box hit testing, the Zero Hour GadgetListBox.cpp statics BFME2 keeps:
// getListboxEntryBasedOnCoord @0x00323E95 218B (cdecl; the only body the
// GadgetListBoxGetEntryBasedOnXY wrapper @0x00323F6F tail-jumps to) maps a
// screen point to the row under it and the column whose running width
// passes it. Target facts: the title adjustment through
// WinInstanceData::getTextLength and manager slot 72 (winFontHeight) of the
// font at instance +0x184; columns short +2, column widths +0x14, 16-byte
// rows at +0x18 (listHeight +0), endPos short +0x2C, displayHeight short
// +0x3C, displayPos short +0x44.
typedef int Int;
typedef short Short;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt WindowMsgData;

class GameFont;

class WinInstanceData
{
public:
	Int getTextLength();
	GameFont *getFont() { return m_font; }

	unsigned char m_pad00[0x184];
	GameFont *m_font;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	Int winGetScreenPosition(Int *x, Int *y);
};

struct ListEntryRow
{
	Int listHeight;
	Short height;
	Short m_pad06;
	void *cell;
	Bool m_disabled;
};

struct ListboxData
{
	Short listLength;
	Short columns;
	unsigned char m_pad04[0x14 - 0x04];
	Int *columnWidth;
	ListEntryRow *listData;
	unsigned char m_pad1C[0x2C - 0x1C];
	Short endPos;
	unsigned char m_pad2E[0x3C - 0x2E];
	Short displayHeight;
	unsigned char m_pad3E[0x44 - 0x3E];
	Short displayPos;
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
#undef V
	virtual Int winFontHeight(GameFont *font) = 0;
};

extern GameWindowManager *TheWindowManager;

static Int getListboxEntryBasedOnCoord(GameWindow *window, Int x, Int y, Int &row, Int &column)
{
	Int pos;
	Int winx, winy, i;
	WinInstanceData *instData = window->winGetInstanceData();
	ListboxData *list = (ListboxData *)window->winGetUserData();

	window->winGetScreenPosition(&winx, &winy);

	// Adjust for title if present
	if (instData->getTextLength())
		winy += TheWindowManager->winFontHeight(instData->getFont()) + 1;

	pos = -2;

	for (i = 0; ; i++)
	{
		if (i > 0)
			if (list->listData[i - 1].listHeight >
					(list->displayPos + list->displayHeight))
			{
				pos = -1;
				break;
			}

		if (i == list->endPos)
		{
			pos = -1;
			break;
		}

		if (list->listData[i].listHeight > (y - winy + list->displayPos))
			break;
	}

	column = -1;
	if (pos == -2)
	{
		pos = i;
		Int total = 0;
		for (i = 0; i < list->columns; i++)
		{
			total += list->columnWidth[i];
			if (x - winx < total)
			{
				column = i;
				break;
			}
		}
	}
	row = pos;
	return pos;
}

Int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, Int x, Int y, Int &row, Int &column)
{
	return getListboxEntryBasedOnCoord(listbox, x, y, row, column);
}
