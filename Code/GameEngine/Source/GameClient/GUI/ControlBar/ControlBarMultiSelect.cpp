// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Adapted clean BFME1 ba7ddda7 ControlBarMultiSelect.cpp and the whole ZH file.
// Native 53DF0A..53E17E (628B), independently named WB1125550 at
// ControlBarMultiSelect.cpp lines 431..437, establish this+6C selection,
// windows DC, common commands 15C, color208 and InGameUI vslot73.
// Field labels follow donor workflow; the observed native offsets are target facts.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" void *__cdecl memset(void *dst, int value, unsigned int size);

enum { MAX_COMMANDS_PER_SET = 32 };

class ThingTemplate;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	Int getOptions() const
	{
		return *(const Int *)((const char *)this + 0x1C);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide(bool hide);
	Bool winIsHidden(void);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
	Int winEnable(Bool enable);
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	Object *getObject(void) { return m_object; }

private:
	char m_slice_pad[0xFC];					// retail this+0x00 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

// BFME list layout: the list holds its sentinel node at +0; nodes link next/prev
// at +0/+4 and carry the drawable at +8.
struct BfmeControlBarDrawableListNode
{
	BfmeControlBarDrawableListNode *next;
	BfmeControlBarDrawableListNode *prev;
	Drawable *value;
};

struct BfmeControlBarDrawableList
{
	BfmeControlBarDrawableListNode *head;
};

class InGameUI;
extern InGameUI *TheInGameUI;

#define BFME_CONTROLBAR_INGAME_SLOT(n) virtual void slot##n(void) = 0;
class BfmeControlBarInGameUISelectionView
{
public:
	BFME_CONTROLBAR_INGAME_SLOT(0)  BFME_CONTROLBAR_INGAME_SLOT(1)
	BFME_CONTROLBAR_INGAME_SLOT(2)  BFME_CONTROLBAR_INGAME_SLOT(3)
	BFME_CONTROLBAR_INGAME_SLOT(4)  BFME_CONTROLBAR_INGAME_SLOT(5)
	BFME_CONTROLBAR_INGAME_SLOT(6)  BFME_CONTROLBAR_INGAME_SLOT(7)
	BFME_CONTROLBAR_INGAME_SLOT(8)  BFME_CONTROLBAR_INGAME_SLOT(9)
	BFME_CONTROLBAR_INGAME_SLOT(10) BFME_CONTROLBAR_INGAME_SLOT(11)
	BFME_CONTROLBAR_INGAME_SLOT(12) BFME_CONTROLBAR_INGAME_SLOT(13)
	BFME_CONTROLBAR_INGAME_SLOT(14) BFME_CONTROLBAR_INGAME_SLOT(15)
	BFME_CONTROLBAR_INGAME_SLOT(16) BFME_CONTROLBAR_INGAME_SLOT(17)
	BFME_CONTROLBAR_INGAME_SLOT(18) BFME_CONTROLBAR_INGAME_SLOT(19)
	BFME_CONTROLBAR_INGAME_SLOT(20) BFME_CONTROLBAR_INGAME_SLOT(21)
	BFME_CONTROLBAR_INGAME_SLOT(22) BFME_CONTROLBAR_INGAME_SLOT(23)
	BFME_CONTROLBAR_INGAME_SLOT(24) BFME_CONTROLBAR_INGAME_SLOT(25)
	BFME_CONTROLBAR_INGAME_SLOT(26) BFME_CONTROLBAR_INGAME_SLOT(27)
	BFME_CONTROLBAR_INGAME_SLOT(28) BFME_CONTROLBAR_INGAME_SLOT(29)
	BFME_CONTROLBAR_INGAME_SLOT(30) BFME_CONTROLBAR_INGAME_SLOT(31)
	BFME_CONTROLBAR_INGAME_SLOT(32) BFME_CONTROLBAR_INGAME_SLOT(33)
	BFME_CONTROLBAR_INGAME_SLOT(34) BFME_CONTROLBAR_INGAME_SLOT(35)
	BFME_CONTROLBAR_INGAME_SLOT(36) BFME_CONTROLBAR_INGAME_SLOT(37)
	BFME_CONTROLBAR_INGAME_SLOT(38) BFME_CONTROLBAR_INGAME_SLOT(39)
	BFME_CONTROLBAR_INGAME_SLOT(40) BFME_CONTROLBAR_INGAME_SLOT(41)
	BFME_CONTROLBAR_INGAME_SLOT(42) BFME_CONTROLBAR_INGAME_SLOT(43)
	BFME_CONTROLBAR_INGAME_SLOT(44) BFME_CONTROLBAR_INGAME_SLOT(45)
	BFME_CONTROLBAR_INGAME_SLOT(46) BFME_CONTROLBAR_INGAME_SLOT(47)
	BFME_CONTROLBAR_INGAME_SLOT(48) BFME_CONTROLBAR_INGAME_SLOT(49)
	BFME_CONTROLBAR_INGAME_SLOT(50) BFME_CONTROLBAR_INGAME_SLOT(51)
	BFME_CONTROLBAR_INGAME_SLOT(52) BFME_CONTROLBAR_INGAME_SLOT(53)
	BFME_CONTROLBAR_INGAME_SLOT(54) BFME_CONTROLBAR_INGAME_SLOT(55)
	BFME_CONTROLBAR_INGAME_SLOT(56) BFME_CONTROLBAR_INGAME_SLOT(57)
	BFME_CONTROLBAR_INGAME_SLOT(58) BFME_CONTROLBAR_INGAME_SLOT(59)
	BFME_CONTROLBAR_INGAME_SLOT(60) BFME_CONTROLBAR_INGAME_SLOT(61)
	BFME_CONTROLBAR_INGAME_SLOT(62)
	BFME_CONTROLBAR_INGAME_SLOT(63)
	BFME_CONTROLBAR_INGAME_SLOT(64)
	BFME_CONTROLBAR_INGAME_SLOT(65)
	BFME_CONTROLBAR_INGAME_SLOT(66)
	BFME_CONTROLBAR_INGAME_SLOT(67)
	BFME_CONTROLBAR_INGAME_SLOT(68)
	BFME_CONTROLBAR_INGAME_SLOT(69)
	BFME_CONTROLBAR_INGAME_SLOT(70)
	BFME_CONTROLBAR_INGAME_SLOT(71)
	BFME_CONTROLBAR_INGAME_SLOT(72)
	virtual const BfmeControlBarDrawableList *getAllSelectedDrawables(void) const = 0;
};
#undef BFME_CONTROLBAR_INGAME_SLOT

void *GadgetButtonGetData(GameWindow *window);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *window, Bool checked);
void Rva003284B9(GameWindow *window, Int percent, Int color);
void GadgetButtonSetDisallowed(GameWindow *, Int);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void rva0053DF0A(void);
    void rva0053CF65();
    Int rva0053BD66(const CommandButton *, GameWindow *, Object *, Real *, Bool) const;

private:
	char m_slice_pad[0x6C];					// retail this+0x00 .. +0x6B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x6C
	char m_slice_padC[0xDC - 0x70];			// this+0x70 .. +0xDB, untouched
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];	// this+0xDC
	const CommandButton *m_commonCommands[MAX_COMMANDS_PER_SET];	// this+0x15C
	char m_slice_padE[0x208 - (0x15C + MAX_COMMANDS_PER_SET * 4)];
	Int m_buildUpClockColor;				// this+0x208
};

// ?rva0053DF0A@ControlBar@@QAEXXZ
// WB identifies the operation as updateContextMultiSelect. Retain the existing
// address-derived external spelling so the owned ControlBar::update caller
// uses this actual provider; target original access and declaration unasserted.
void ControlBar::rva0053DF0A(void)
{
	Drawable *draw;
	Object *obj;
	const CommandButton *command;
	GameWindow *win = 0;
	Int objectsThatCanDoCommand[MAX_COMMANDS_PER_SET];
	Int i;

	if (m_currentSelectedDrawable != 0)
	{
		rva0053CF65();
		return;
	}

	memset(objectsThatCanDoCommand, 0, sizeof(objectsThatCanDoCommand));

	const BfmeControlBarDrawableList *selectedDrawables =
		((BfmeControlBarInGameUISelectionView *)TheInGameUI)->getAllSelectedDrawables();

	for (BfmeControlBarDrawableListNode *it = selectedDrawables->head->next;
		it != selectedDrawables->head; it = it->next)
	{
		draw = it->value;

		// Native template mask at +0x10C: donor KINDOF_IGNORED_IN_GUI bit 15.
		obj = draw->getObject();
		const ThingTemplate *thingTemplate = *(const ThingTemplate *const *)((const char *)draw->getObject() + 4);
		if (*(const UnsignedInt *)((const char *)thingTemplate + 0x10C) & 0x8000)
			continue;

		if (obj == 0)
			continue;

		for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
		{
			win = m_commandWindows[i];
			if (!win)
				continue;

			if (win->winIsHidden() == true)
				continue;

			command = (const CommandButton *)GadgetButtonGetData(win);
			if (command == 0)
				continue;

			Real percent;
			Int availability = rva0053BD66(command, win, obj, &percent, false);

			win->winClearStatus(0x00400000);
			win->winClearStatus(0x01000000);
			win->winClearStatus(0x40000000);
			win->winClearStatus(0x80000000);

			GadgetButtonSetDisallowed(win, false);
			Int color = 0;
			switch (availability)
			{
				case 3:
					win->winHide(true);
					break;

				case 0:
				case 4:
				case 8:
					win->winEnable(false);
					win->winSetStatus(0x80000000);
					if (availability == 4)
						GadgetButtonSetDisallowed(win, true);
					if (availability == 8)
						win->winSetStatus(0x01000000);
					break;

				case 5:
					color = m_buildUpClockColor;
					win->winEnable(false);
					win->winSetStatus(0x00400000);
					break;

				case 6:
				case 7:
					win->winEnable(false);
					win->winSetStatus(0x01000000);
					break;

				default:
					win->winEnable(true);
					break;
			}

			if (percent < 1.0f)
				Rva003284B9(win, (Int)(percent * 100.0f), color);

			if ((command->getOptions() & 0x400) != 0)
				GadgetCheckLikeButtonSetVisualCheck(win, availability == 2);

			if (availability == 1 || availability == 2)
				objectsThatCanDoCommand[i]++;
		}
	}

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		win = m_commandWindows[i];
		if (!win)
			continue;

		if (win->winIsHidden() == true)
			continue;

		if (m_commonCommands[i] == 0)
			continue;

		if (objectsThatCanDoCommand[i] > 0)
		{
			win->winEnable(true);
			win->winClearStatus(0x80000000);
			win->winClearStatus(0x01000000);
		}
		else
			win->winEnable(false);
	}
}
