// ?rva0051C452@AptScoreScreen@@QAEHHII@Z
// partial score=0.96 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" int __cdecl strcmp(const char *left, const char *right);
extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The objectives summary at +0x288: a count at +4 and up to eight
// checked flags at +0x28.
struct AptScoreObjectives
{
	unsigned char m_pad00[4];
	int m_count; // +0x04
	unsigned char m_pad08[0x28 - 0x08];
	bool m_checked[8]; // +0x28
};

class BfmeKeyLC;

// The list box user data byte +0x12 the score screen sets.
struct AptScoreListData
{
	unsigned char m_pad[0x12];
	bool m_12; // +0x12
};

class GameWindow
{
public:
	int winEnable(bool enable);
	void *winGetUserData();
	void winSetUserData(void *data);
};

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, int x, int y, int &row, int &column);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);

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
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

// The Apt player's rowed call 0x00222A8B on a movie's level.
class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

extern class Rva00222A8BTarget *TheRva00222A8BTarget;

// TheGameText's fetch by label (vslot 14).
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

// TheMouse's rowed tooltip setter 0x001EEA6D (MouseRva001EEA6D.cpp).
struct RGBColor
{
	float red, green, blue;
};

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

// TheThingFactory's rowed template lookup 0x002D06CA; the template's
// display name at +0x30 and its flag byte +0x113, whose bit 2 marks a hero.
struct Rva002D06CATemplate
{
	unsigned char m_pad000[0x30];
	UnicodeString m_displayName; // +0x30
	unsigned char m_pad034[0x113 - 0x34];
	unsigned char m_113; // +0x113
};

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern Rva002D06CA *TheThingFactory;

// A persistent unit's list box item data: its template name at +4 and the
// player's name for it at +0xA0.
struct AptScorePersistentUnit
{
	unsigned char m_pad00[4];
	AsciiString m_templateName; // +0x04
	unsigned char m_pad08[0xA0 - 0x08];
	UnicodeString m_customName; // +0xA0
};

// The Apt screen base's rowed window message handler 0x0051274F.
class Rva005126F5
{
public:
	int rva0051274F(int message, unsigned int wParam, unsigned int lParam);
};

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

// TheLivingWorldLogic (VA 0x00DFEF10, the ledger's g_009FEF10); its
// unrowed 0x002B3740 returns a byte of its current entry, pinned by
// address.
class Rva002BA8F1Logic
{
public:
	bool rva002B3740();
};

extern class Rva002BA8F1Logic *g_009FEF10;

class AptScoreScreen
{
public:
	void OnInitialized(const char *unused);
	void Timeline(const char *unused);
	void RestartGame(const char *unused);
	void Continue(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void RenameCancel(const char *unused);
	void objectiveChecked(int index, char *result, bool skip);
	void heroVetUpgrade(int index, char *result, bool skip);
	void OnButtonRenameAccept(int unused);
	int rva0051C452(int message, unsigned int wParam, unsigned int lParam);

private:
	unsigned char m_pad000[0x274];
	void *m_movie; // +0x274
	unsigned char m_pad278[0x27C - 0x278];
	int m_state; // +0x27C
	unsigned char m_pad280[0x288 - 0x280];
	AptScoreObjectives *m_objectives; // +0x288
	_STL::vector<bool> m_heroUpgrades; // +0x28C
	GameWindow *m_units; // +0x2A0
	GameWindow *m_rename; // +0x2A4
	AptScorePersistentUnit *m_renaming; // +0x2A8
	int m_renameIndex; // +0x2AC
	unsigned char m_pad2b0[0x2B4 - 0x2B0];
	int m_lastX; // +0x2B4
	int m_lastY; // +0x2B8
	int m_hoverFrames; // +0x2BC
	AsciiString m_tooltip; // +0x2C0
};

// Retail 0x0051BF75, 38 bytes: "AptScoreScreen::OnInitialized" focuses
// the screen's window unless a restart is pending.
void AptScoreScreen::OnInitialized(const char *unused)
{
	if (m_state != 3)
	{
		TheWindowManager->winSetFocus((GameWindow *)this);
		m_state = 1;
	}
}

// Retail 0x0051BF9B, 14 bytes: "AptScoreScreen::Timeline".
void AptScoreScreen::Timeline(const char *unused)
{
	((Rva00222479ByteOneSetter *)TheRva00222A8BTarget)->enable();
}

// Retail 0x0051BFA9, 13 bytes: "AptScoreScreen::RestartGame".
void AptScoreScreen::RestartGame(const char *unused)
{
	m_state = 3;
}

// Retail 0x0051BFB6, 28 bytes: "AptScoreScreen::Continue".
void AptScoreScreen::Continue(const char *unused)
{
	g_009FEF10->rva002B3740();
	m_state = 3;
}

// Retail 0x0051C7CC, 124 bytes: "AptScoreScreen::InitGadgets" keeps the
// "PersistentUnitsListBox" (flagging its data's +0x12) and the emptied
// "RenameUnitsTextEntry" (at most 20 characters).
void AptScoreScreen::InitGadgets(const char *name, void *argument, GameWindow *window)
{
	if (!window)
		return;
	if (strcmp(name, "PersistentUnitsListBox") == 0)
	{
		m_units = window;
		AptScoreListData *data = (AptScoreListData *)window->winGetUserData();
		data->m_12 = true;
		window->winSetUserData(data);
	}
	else if (strcmp(name, "RenameUnitsTextEntry") == 0)
	{
		m_rename = window;
		GadgetTextEntrySetText(window, UnicodeString::TheEmptyString);
		GadgetTextEntrySetMaxChars((BfmeKeyLC *)window, 20);
	}
}

// Retail 0x0051BFD2, 34 bytes: "AptScoreScreen::RenameCancel" drops the
// rename and enables the units list again.
void AptScoreScreen::RenameCancel(const char *unused)
{
	m_renaming = 0;
	m_renameIndex = -1;
	if (m_units)
		m_units->winEnable(true);
}

// Retail 0x0051BFF4, 86 bytes: "objectiveChecked%d" for each objective,
// an Apt query answering whether it was checked off.
void AptScoreScreen::objectiveChecked(int index, char *result, bool skip)
{
	if (skip)
		return;
	strcpy(result, "0");
	AptScoreObjectives *objectives = m_objectives;
	if (objectives && index >= 0 && index < objectives->m_count && index < 8)
		sprintf(result, "%d", objectives->m_checked[index] != 0);
}

// Retail 0x0051C452, 890 bytes: the score screen's window messages (its
// vftable slot at 0x00C663B4) ahead of the Apt screen base 0x0051274F.
// Resting the mouse on a persistent unit for ten frames shows whether it
// may be renamed (heroes may not) and keeps that tooltip up after eight;
// selecting one opens the rename entry on its current name, and the
// entry's GEM_EDIT_DONE accepts it.
int AptScoreScreen::rva0051C452(int message, unsigned int wParam, unsigned int lParam)
{
	switch (message)
	{
	case 0x18: // GWM_MOUSE_POS
	{
		if ((GameWindow *)wParam != m_units)
			break;
		int x = lParam & 0xFFFF;
		int y = lParam >> 16;
		if (x == m_lastX && y == m_lastY)
			++m_hoverFrames;
		else
			m_hoverFrames = 0;
		int row;
		int column;
		GadgetListBoxGetEntryBasedOnXY((GameWindow *)wParam, x, y, row, column);
		if (m_hoverFrames == 10)
		{
			if (column != 0)
			{
				AsciiString label("APT:NULL");
				TheMouse->rva001EEA6D(TheGameText->fetch(label), -1, 0, 1.0f);
				m_tooltip = label;
			}
			if (column == 0)
			{
				AsciiString label;
				m_renaming = (AptScorePersistentUnit *)GadgetListBoxGetItemData(m_units, row, 0);
				if (m_renaming)
				{
					Rva002D06CATemplate *unitTemplate;
					if (TheThingFactory
						&& (unitTemplate = (Rva002D06CATemplate *)TheThingFactory->rva002D06CA(&m_renaming->m_templateName)) != 0
						&& (unitTemplate->m_113 & 4))
						label = "TOOLTIP:YouMayNotRenameAHero";
					else
						label = "TOOLTIP:ClickToRenameThisUnit";
					TheMouse->rva001EEA6D(TheGameText->fetch(label), -1, 0, 1.0f);
				}
				m_tooltip = label;
			}
		}
		else if (m_hoverFrames > 7 && column == 0)
		{
			TheMouse->rva001EEA6D(TheGameText->fetch(m_tooltip), -1, 0, 1.0f);
		}
		m_lastX = x;
		m_lastY = y;
		break;
	}
	case 0x4014: // GLM_SELECTED
	{
		if ((GameWindow *)wParam != m_units || !m_units || !m_rename || (int)lParam < 0)
			break;
		m_renaming = (AptScorePersistentUnit *)GadgetListBoxGetItemData(m_units, lParam, 0);
		if (!m_renaming)
			break;
		m_renameIndex = lParam;
		Rva002D06CATemplate *unitTemplate = 0;
		if (TheThingFactory)
		{
			unitTemplate = (Rva002D06CATemplate *)TheThingFactory->rva002D06CA(&m_renaming->m_templateName);
			if (unitTemplate && (unitTemplate->m_113 & 4))
			{
				m_renameIndex = -1;
				m_renaming = 0;
				break;
			}
		}
		UnicodeString name;
		UnicodeString &customName = m_renaming->m_customName;
		if (!customName.isEmpty())
			name = customName;
		else if (unitTemplate)
			name = unitTemplate->m_displayName;
		GadgetTextEntrySetText(m_rename, name);
		TheWindowManager->winSetFocus(m_rename);
		m_units->winEnable(false);
		void *movie = m_movie;
		TheRva00222A8BTarget->invoke(movie, "openRenamePersistentUnit", 0, 0, 0, 0, 0, 0);
		break;
	}
	case 0x4031: // GEM_EDIT_DONE
		if ((GameWindow *)wParam == m_rename && lParam == 0 && m_renaming)
		{
			OnButtonRenameAccept(0);
			TheRva00222A8BTarget->invoke(m_movie, "closeRenamePersistentUnit", 0, 0, 0, 0, 0, 0);
		}
		break;
	default:
		return ((Rva005126F5 *)this)->rva0051274F(message, wParam, lParam);
	}
	return 1;
}

// Retail 0x0051C992, 122 bytes: "heroVetUpgrade%d" for each of twelve
// heroes, an Apt query answering whether the hero's veterancy upgraded.
void AptScoreScreen::heroVetUpgrade(int index, char *result, bool skip)
{
	if (skip)
		return;
	strcpy(result, "0");
	if (index >= 0 && (unsigned int)index < m_heroUpgrades.size() && index < 12)
		sprintf(result, "%d", m_heroUpgrades[index] ? 1 : 0);
}

// Retail's strcpy call lands on the import thunk rowed as ji_00629176.
#pragma comment(linker, "/alternatename:_strcpy=?ji_00629176@@YAXXZ")
