// cl: /O1 /DNDEBUG /MD
//
// BFME2's in-game quit menu Apt callbacks, 0x0051AFB9 onward, bound by
// these names ("AptQuitMenu::RestartMission" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix.

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

class AptQuitMenu
{
public:
	void RestartMission(const char *unused);
	void ExitMission(const char *unused);
	void OptionsScreen(const char *unused);
	void ReturnToGame(const char *unused);
	void SaveMenu(const char *unused);
	void LoadMenu(const char *unused);

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
