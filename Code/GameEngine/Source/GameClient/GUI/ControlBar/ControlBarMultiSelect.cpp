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
class ExperienceLevelList;
struct ExperienceLevelHandle {
    ExperienceLevelHandle() {}
    ExperienceLevelHandle(const ExperienceLevelHandle &other) : m_list(other.m_list), m_iter(other.m_iter) {}
    ExperienceLevelList *m_list;
    void *m_iter;
};
class ExperienceTracker {
public:
    ExperienceLevelHandle rva0039AC0C() const;
};
class ExperienceLevelStore {
public:
    bool IsValid(ExperienceLevelHandle) const;
    int GetLevelRank(ExperienceLevelHandle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class Image;
class Rva0053DB02 { public: void rva0053DB02(); };
class Gen_003bcb40 { public: void m(int); };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D363EOwner { public: void rva002D363E(int); };
class Rva0053ED1A { public: void rva0053EF2E(); };


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class Object;
class CommandButton
{
public:
    void rva0035B5C2(Object *, bool);
    Int getCommandType() const { return *(const Int *)((const char *)this + 0x14); }
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

class AsciiString;
enum ObjectStatusTypes { MULTISELECT_SOLD = 0x13 };
class Object {
public:
    const AsciiString *rva00290E67() const;
    const Image *getObjectSelectedPortraitImage();
    Object *rva002931F5(bool);
    void *rva0028C197() const;
    bool testStatus(ObjectStatusTypes) const;
};
class CommandSet {
public:
    const CommandButton *getCommandButton(int) const;
};
class Rva0031D5F8 {
public:
    void *rva0031D5F8(const AsciiString *);
};
class Rva0035B424 {
public:
    void rva0035B424(int);
};
class MultiSelectModeView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual bool currentMode(); // target vslot59, original name/type unasserted
};

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
protected:
    void addCommonCommands(Drawable *, bool);
public:
	void rva0053DF0A(void);
    void rva0053DD53();
    void rva0053D355(Object *, bool);
    void rva0053CF65();
    void rva0031B641(GameWindow *, const CommandButton *);
    Int rva0053BD66(const CommandButton *, GameWindow *, Object *, Real *, Bool) const;

private:
	char m_slice_pad[0x6C];					// retail this+0x00 .. +0x6B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x6C
	char m_slice_padC[0xDC - 0x70];			// this+0x70 .. +0xDB, untouched
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];	// this+0xDC
	const CommandButton *m_commonCommands[MAX_COMMANDS_PER_SET];	// this+0x15C
	char m_slice_padE[0x208 - (0x15C + MAX_COMMANDS_PER_SET * 4)];
	Int m_buildUpClockColor;				// this+0x208
    char unknown20C[0x2A0-0x20C];
    Rva0053ED1A *overlaySink; // target2A0
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

// ?addCommonCommands@ControlBar@@IAEXPAVDrawable@@_N@Z
// Native53DB2D..53DD53 (550B), WB1124A40 names ControlBarMultiSelect.cpp;
// ZH supplies common-command intersection. Target adds the type24 selection
// vote through the owned Object helpers and vslot59, then chooses index0/1
// through the owned 35B424 setter. Those operation names remain unasserted.
void ControlBar::addCommonCommands(Drawable *draw, bool firstDrawable)
{
    Int i;
    const CommandButton *command;
    if (draw == 0) return;
    Object *obj = draw->getObject();
    if (!obj) return;
    if (*(const unsigned int *)((const char *)*(const void *const *)((const char *)obj + 4) + 0x10C) & 0x8000)
        return;
    const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)this)->rva0031D5F8(obj->rva00290E67());
    if (commandSet == 0) {
        for (i = 0; i < MAX_COMMANDS_PER_SET; i++) {
            m_commonCommands[i] = 0;
            if (m_commandWindows[i]) m_commandWindows[i]->winHide(true);
        }
        return;
    }
    if (firstDrawable == true) {
        for (i = 0; i < MAX_COMMANDS_PER_SET; i++) {
            command = commandSet->getCommandButton(i);
            if (command && (command->getOptions() & 0x100) != 0) {
                m_commonCommands[i] = command;
                if (m_commandWindows[i]) {
                    m_commandWindows[i]->winHide(false);
                    m_commandWindows[i]->winEnable(true);
                    if (command->getCommandType() == 0x24) {
                        int modeVote = 0;
                        const BfmeControlBarDrawableList *selected =
                            ((BfmeControlBarInGameUISelectionView *)TheInGameUI)->getAllSelectedDrawables();
                        for (BfmeControlBarDrawableListNode *it = selected->head->next;
                             it != selected->head; it = it->next) {
                            Drawable *selectedDraw = it->value;
                            if (!selectedDraw || !selectedDraw->getObject()) continue;
                            Object *selectedObject = selectedDraw->getObject();
                            if (*(const unsigned int *)((const char *)*(const void *const *)((const char *)selectedObject + 4) + 0x10C) & 0x8000)
                                continue;
                            if (selectedObject->testStatus(MULTISELECT_SOLD)) continue;
                            Object *resolved = selectedObject->rva002931F5(false);
                            if (!resolved) continue;
                            MultiSelectModeView *mode = (MultiSelectModeView *)resolved->rva0028C197();
                            if (!mode) continue;
                            if (mode->currentMode()) --modeVote;
                            else ++modeVote;
                        }
                        ((Rva0035B424 *)command)->rva0035B424(modeVote >= 0);
                    } else {
                        const_cast<CommandButton *>(command)->rva0035B5C2(obj, false);
                    }
                    rva0031B641(m_commandWindows[i], command);
                }
            }
        }
    } else {
        for (i = 0; i < MAX_COMMANDS_PER_SET; i++) {
            command = commandSet->getCommandButton(i);
            bool attackMove = (command && command->getCommandType() == 0xA) ||
                (m_commonCommands[i] && m_commonCommands[i]->getCommandType() == 0xA);
            if (attackMove && !m_commonCommands[i]) {
                m_commonCommands[i] = command;
                if (m_commandWindows[i]) {
                    m_commandWindows[i]->winHide(false);
                    m_commandWindows[i]->winEnable(true);
                    rva0031B641(m_commandWindows[i], command);
                }
            } else if (command != m_commonCommands[i] && !attackMove) {
                m_commonCommands[i] = 0;
                if (m_commandWindows[i]) m_commandWindows[i]->winHide(true);
            }
        }
    }
}

// ?rva0053DD53@ControlBar@@QAEXXZ
// Native53DD53..53DF0A439B. WB1124EB0 names populateMultiSelect at
// ControlBarMultiSelect.cpp270..339. ZH supplies the common-command and
// portrait pass; target adds a highest-rank selection pass, breaking ties
// by the lower native ObjectID74. Original access/declaration remain unasserted.
void ControlBar::rva0053DD53()
{
    const BfmeControlBarDrawableList *selected =
        ((BfmeControlBarInGameUISelectionView *)TheInGameUI)->getAllSelectedDrawables();
    Drawable *best = 0;
    int bestRank = 0;
    for (BfmeControlBarDrawableListNode *it = selected->head->next;
         it != selected->head; it = it->next) {
        Drawable *draw = it->value;
        Object *object = draw->getObject();
        if (!object) continue;
        const char *objectTemplate = *(const char *const *)((const char *)object + 4);
        if (!(*(const unsigned int *)(objectTemplate + 0x110) & 0x04000000) ||
            (*(const unsigned int *)(objectTemplate + 0x10C) & 0x8000))
            continue;
        ExperienceLevelHandle handle = (*(ExperienceTracker *const *)((const char *)object + 0x264))->rva0039AC0C();
        if (!((ExperienceLevelStore *)TheExperienceLevelSystem)->IsValid(handle)) continue;
        int rank = ((ExperienceLevelStore *)TheExperienceLevelSystem)->GetLevelRank(handle);
        if (!best || rank > bestRank) {
            best = draw;
            bestRank = rank;
        } else if (best && rank == bestRank) {
            Object *oldObject = best->getObject();
            if (*(const int *)((const char *)object + 0x74) < *(const int *)((const char *)oldObject + 0x74)) {
                best = draw;
                bestRank = rank;
            }
        }
    }
    if (best) {
        m_currentSelectedDrawable = best;
        rva0053D355(best->getObject(), false);
        return;
    }
    bool firstDrawable = true;
    bool portraitSet = false;
    const Image *portrait = 0;
    Object *portraitObject = 0;
    ((Rva0053DB02 *)this)->rva0053DB02();
    for (int i = 0; i < MAX_COMMANDS_PER_SET; ++i)
        if (m_commandWindows[i]) m_commandWindows[i]->winHide(true);
    for (BfmeControlBarDrawableListNode *it = selected->head->next;
         it != selected->head; it = it->next) {
        Drawable *draw = it->value;
        Object *object = draw->getObject();
        if (*(const unsigned int *)((const char *)*(const void *const *)((const char *)object + 4) + 0x10C) & 0x8000)
            continue;
        if (draw && draw->getObject() && !draw->getObject()->testStatus(MULTISELECT_SOLD)) {
            addCommonCommands(draw, firstDrawable);
            firstDrawable = false;
            if (!portraitSet) {
                portraitObject = draw->getObject();
                portrait = portraitObject->getObjectSelectedPortraitImage();
                portraitSet = true;
            } else if (draw->getObject()->getObjectSelectedPortraitImage() != portrait) {
                portrait = 0;
            }
        }
    }
    ((Gen_003bcb40 *)this)->m((int)portraitObject);
    if (theRadarWindowOverrideSource)
        ((Rva002D363EOwner *)theRadarWindowOverrideSource)->rva002D363E(0);
    overlaySink->rva0053EF2E();
}
