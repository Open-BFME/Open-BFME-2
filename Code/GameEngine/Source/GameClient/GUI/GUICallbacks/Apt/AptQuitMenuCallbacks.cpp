// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's in-game quit menu Apt callbacks, 0x0051AFB9 onward, bound by
// these names ("AptQuitMenu::RestartMission" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix.

#include "unicode_string.h"

extern "C" char *__cdecl strcpy(char *destination, const char *source);

void __cdecl Rva00434160Init(int a, int b, bool c);
void __cdecl Rva00511730(int value);
void __cdecl Rva0051AF0BEnable(int value);
void __cdecl Rva005185D8Init(bool a, bool b, bool c, bool d);

// TheGameLogic (0x00DFE78C): the mode at +0x110, +0x114 and the rowed
// readers this unit calls.
class GameLogic
{
public:
	bool isInMultiplayerGame();

	unsigned char m_pad000[0x110];
	int m_110; // +0x110
	int m_114; // +0x114
};

extern GameLogic *TheGameLogic;

// The rowed bool field reader 0x00210C66 on the same object.
class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

// TheGameText's fetch (vslot 15).
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
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
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

// TheLivingWorldLogic (the ledger's g_009FEF10); its rowed
// isSelectionLocked 0x0004253A tells a war of the ring game apart.
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

extern BfmeSelectionState *g_009FEF10;

class AptQuitMenu
{
public:
	void RestartMission(const char *unused);
	void ExitMission(const char *unused);
	void OptionsScreen(const char *unused);
	void ReturnToGame(const char *unused);
	void SaveMenu(const char *unused);
	void LoadMenu(const char *unused);
	// Bound under the button clip "QuitMenu/Restart/TheButton" (0x0051BD98)
	// rather than a method name, so it keeps its address.
	void rva0051B50E(const char *unused);
	// Retail 0x0051AF46, 115 bytes: Apt query answering the quit-menu
	// restart-button label: count "1" for query 0, and for query 1 the
	// Restart/Forfeit/Surrender word matching rva0051B50E's tooltip pick.
	void rva0051AF46(int query, char *value, bool set);

private:
	unsigned char m_pad000[0x27C];
	bool m_exit; // +0x27C
	bool m_27d;
	bool m_restart; // +0x27E
};

// Retail 0x0051AFB9, 10 bytes: "AptQuitMenu::RestartMission".
void AptQuitMenu::RestartMission(const char *unused)
{
	m_restart = true;
}

// Retail 0x0051AFC3, 26 bytes: "AptQuitMenu::ExitMission".
void AptQuitMenu::ExitMission(const char *unused)
{
	m_exit = true;
	Rva00511730(0);
	Rva0051AF0BEnable(2);
}

// Retail 0x0051AFDD, 17 bytes: "AptQuitMenu::OptionsScreen".
void AptQuitMenu::OptionsScreen(const char *unused)
{
	Rva005185D8Init(false, false, false, false);
}

// Retail 0x0051AFEE, 11 bytes: "AptQuitMenu::ReturnToGame".
void AptQuitMenu::ReturnToGame(const char *unused)
{
	Rva0051AF0BEnable(0);
}

// Retail 0x0051AFF9, 81 bytes: "AptQuitMenu::SaveMenu" opens the save
// screen (3) in the current game's mode: 8 without +0x114, 16 by the
// 0x00210C66 field, 4 in a multiplayer game, else 2 in mode 2 and 1.
void AptQuitMenu::SaveMenu(const char *unused)
{
	GameLogic *logic = TheGameLogic;
	int kind;
	if (logic->m_114 == 0)
		kind = 8;
	else if (((Rva00210C66CmpBoolField *)logic)->get())
		kind = 16;
	else if (logic->isInMultiplayerGame())
		kind = 4;
	else
		kind = (logic->m_110 == 2) + 1;
	Rva00434160Init(3, kind, true);
}

// Retail 0x0051B04A, 81 bytes: "AptQuitMenu::LoadMenu", the same for the
// load screen (2).
void AptQuitMenu::LoadMenu(const char *unused)
{
	GameLogic *logic = TheGameLogic;
	int kind;
	if (logic->m_114 == 0)
		kind = 8;
	else if (((Rva00210C66CmpBoolField *)logic)->get())
		kind = 16;
	else if (logic->isInMultiplayerGame())
		kind = 4;
	else
		kind = (logic->m_110 == 2) + 1;
	Rva00434160Init(2, kind, true);
}

// Retail 0x0051AF46, 115 bytes: Apt query answering the quit-menu
// restart-button label: count "1" for query 0, and for query 1 the
// Restart/Forfeit/Surrender word matching rva0051B50E's tooltip pick.
void AptQuitMenu::rva0051AF46(int query, char *value, bool set)
{
	if (!set)
	{
		value[0] = '0';
		value[1] = 0;
	}
	switch (query)
	{
	case 0:
		if (set)
			return;
		value[0] = '1';
		return;
	case 1:
		break;
	default:
		return;
	}
	if (set)
		return;
	const char *label;
	GameLogic *logic = TheGameLogic;
	if (logic == 0 || logic->m_114 == 3)
		label = "Restart";
	else if (g_009FEF10 != 0 && g_009FEF10->isSelectionLocked())
		label = "Surrender";
	else
		label = "Forfeit";
	strcpy(value, label);
}

// Retail 0x0051B50E, 167 bytes. Name unknown. Shows the restart button's
// tooltip: restart in a campaign (mode 3) or without a game, else forfeit,
// or surrender in a war of the ring game.
void AptQuitMenu::rva0051B50E(const char *unused)
{
	const char *label;
	if (TheGameLogic && TheGameLogic->m_114 != 3)
	{
		if (g_009FEF10 && g_009FEF10->isSelectionLocked())
			label = "TOOLTIP:QuitMenu/Surrender/WOTRSurrender";
		else
			label = "TOOLTIP:QuitMenu/Forfeit/WOTRForfeit";
	}
	else
		label = "TOOLTIP:QuitMenu/Restart/TheButton";
	bool exists = false;
	UnicodeString tooltip = TheGameText->fetch(label, &exists);
	if (exists)
		TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
}
