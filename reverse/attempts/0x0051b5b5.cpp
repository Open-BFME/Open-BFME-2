// ?OnInitialized@AptQuitMenu@@QAEXPBD@Z
// partial score=0.96 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// BFME2's in-game quit menu Apt callbacks, 0x0051AFB9 onward, bound by
// these names ("AptQuitMenu::RestartMission" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix.

#include "ascii_string.h"
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

// TheRecorder (0x00E02290, the ledger's g_bfme939Helper): its rowed mode
// getter 0x0030F2C7 answers 1 while a replay plays back.
struct Bfme939Helper
{
	int get() const;
};

extern Bfme939Helper *g_bfme939Helper;

// The living-world logic's rowed readers on the same object: the
// player count 0x002B5256 and the check 0x002B254F, whose int callers read
// only its low byte.
class Rva002BA8F1Logic
{
public:
	int rva002B5256(bool flag);
};

class Rva002B254F
{
public:
	int rva002B254F();
};

// The 0x00DFEF18 singleton (address-named view) and its +0x14 dword.
class Rva002D3627Host
{
public:
	unsigned char m_pad000[0x14];
	int m_14; // +0x14
};

extern Rva002D3627Host *g_00DFEF18;

// Rva00222547Get.cpp's 0x00222547 (the window whose Apt movie this one
// plays in) and the Apt player's rowed call 0x00222A8B on its level.
class GameWindow;
GameWindow *Rva00222547Get(GameWindow *window);

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// MpGameSetupSlots.cpp): a binding of an object and an eight-byte
// multiple-inheritance member pointer, and the refcounted holder rowed
// 0x0057BC63 builds from it.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);

struct FunctorBinding
{
	FunctorBinding(FunctorMethod method, FunctorTarget *target) : m_target(target), m_method(method) {}

	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};

class FunctorWrapperHead
{
public:
	void *m_vtbl;
	int m_refCount; // +0x04
};

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);
	Rva0057BC63FunctorHolder(const Rva0057BC63FunctorHolder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}

	FunctorWrapperHead *m_ptr;
};

// Builds a binding by value: the named result is copied out, which is the
// second sixteen-byte slot every registration in the constructor fills.
__forceinline FunctorBinding MakeBinding(FunctorMethod method, FunctorTarget *target)
{
	FunctorBinding binding(method, target);
	return binding;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

template <class T> class AptRef : public Rva0057BC63FunctorHolder
{
public:
	AptRef(const FunctorBinding &binding) : Rva0057BC63FunctorHolder(binding) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}
};

class AptCommandMap;
class AptExternHandler;
class AptOverButtonHandler;

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

// The adders (AptCallbackAdders.cpp, all rowed): each registers with the
// Apt player and remembers the name.
class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	_STL::vector<AsciiString> m_names;
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	_STL::vector<AsciiString> m_names;
};

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);

private:
	_STL::vector<AsciiString> m_names;
};

// The Apt player (0x00DFE4CC): the rowed background switch 0x002233A6
// and text setter 0x00225301.
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool usePlaceholder);
};

class WindowManager
{
public:
	void bfme_showBackground(int kind);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry whose adders
// sit at +0x04, +0x10 and +0x1C.
class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C

private:
	unsigned char m_pad028[0x58 - 0x28];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();

private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class AptQuitMenu : public _bfme_AptGameWindow
{
public:
	AptQuitMenu(void *context);

	void OnInitialized(const char *unused);
	void RestartMission(const char *unused);
	void ExitMission(const char *unused);
	void OptionsScreen(const char *unused);
	void ReturnToGame(const char *unused);
	void SaveMenu(const char *unused);
	void LoadMenu(const char *unused);
	// Bound under the button clip "QuitMenu/Restart/TheButton" (0x0051BD98)
	// rather than a method name, so it keeps its address.
	void HandleOverRestartButton(const char *unused);
	// Retail 0x0051AF46, 115 bytes: Apt query answering the quit-menu
	// restart-button label: count "1" for query 0, and for query 1 the
	// Restart/Forfeit/Surrender word matching HandleOverRestartButton's tooltip pick.
	void Externs(int query, char *value, bool set);

private:
	bool m_exit; // +0x27C
	bool m_27d;
	bool m_restart; // +0x27E
	int m_280;
};

// The open quit menu (0x00E04910), set by its constructor.
extern AptQuitMenu *TheAptQuitMenu;

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
// Restart/Forfeit/Surrender word matching HandleOverRestartButton's tooltip pick.
void AptQuitMenu::Externs(int query, char *value, bool set)
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
void AptQuitMenu::HandleOverRestartButton(const char *unused)
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

// Greys out the named button of a screen's Apt movie.
static __forceinline void DisableButton(GameWindow *window, const char *button)
{
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(Rva00222547Get(window), "disableButton", 1, button, 0, 0, 0, 0);
}

// Retail 0x0051B5B5, 821 bytes: "AptQuitMenu::OnInitialized". Disables
// what the current game cannot do -- in a multiplayer game or a replay
// restart (or, in a war of the ring game, exit), save unless a saveable war
// of the ring game still has players to lose, and load; in a war of the
// ring game restart and the save buttons by the living world's state --
// then labels the restart button Restart, Forfeit or Surrender.
void AptQuitMenu::OnInitialized(const char *unused)
{
	if ((TheGameLogic && TheGameLogic->isInMultiplayerGame())
		|| (g_bfme939Helper && g_bfme939Helper->get() == 1))
	{
		if (TheGameLogic->m_114 != 3)
		{
			if (g_009FEF10 && g_009FEF10->isSelectionLocked())
				DisableButton(this, "ExitMission");
		}
		else
			DisableButton(this, "Restart");
		if (!((Rva00210C66CmpBoolField *)TheGameLogic)->get() || !g_009FEF10 || !g_009FEF10->isSelectionLocked())
			DisableButton(this, "Save");
		if (((Rva00210C66CmpBoolField *)TheGameLogic)->get() && g_009FEF10)
		{
			if (((Rva002BA8F1Logic *)g_009FEF10)->rva002B5256(false) < ((Rva002BA8F1Logic *)g_009FEF10)->rva002B5256(true))
				DisableButton(this, "Save");
		}
		DisableButton(this, "Load");
	}
	else
	{
		BfmeSelectionState *livingWorld = g_009FEF10;
		if (livingWorld && livingWorld->isSelectionLocked())
		{
			if (!TheGameLogic || TheGameLogic->m_114 == 3
				|| (unsigned char)((Rva002B254F *)livingWorld)->rva002B254F() != 0)
				DisableButton(this, "Restart");
			int count = g_00DFEF18->m_14;
			if (count == 0)
			{
				DisableButton(this, "Save");
				DisableButton(this, "Load");
			}
			if ((unsigned char)((Rva002B254F *)g_009FEF10)->rva002B254F() != 0)
				DisableButton(this, "Save");
		}
	}
	if (TheGameLogic && TheGameLogic->m_114 != 3)
	{
		if (g_009FEF10 && g_009FEF10->isSelectionLocked())
		{
			AsciiString key("APT:RestartOrSurrender");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Surrender"), false);
		}
		else
		{
			AsciiString key("APT:RestartOrSurrender");
			g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Forfeit"), false);
		}
	}
	else
	{
		AsciiString key("APT:RestartOrSurrender");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Restart"), false);
	}
}

// The extern handlers' names, by query (0x00C66BF8).
static const char *const s_externNames[] = { "HasFocus", "AptQuitMenu::RestartPopupType" };

// Retail 0x0051BADF, 1016 bytes: the quit menu's constructor. The first
// one opened becomes TheAptQuitMenu and binds its callbacks by name
// ("AptQuitMenu::OnInitialized" ... "AptQuitMenu::LoadMenu", the restart
// button's tooltip and the two Externs queries), switches the Apt player
// to background 2 and, in a multiplayer game, relabels "APT:Pause" with
// "GUI:Menu". As BFME1's BfmeAptScreenQuitMenu constructor
// (BfmeAptScreenQuitMenuConstructor.cpp) with BFME2's adders.
// The handlers are bound as eight-byte multiple-inheritance member pointers.
// The Externs loop's counter is declared before its binding is copied out,
// which keeps it in the dead context slot rather than a register.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptQuitMenu::AptQuitMenu(void *context) : _bfme_AptGameWindow(context)
{
	m_exit = false;
	m_27d = false;
	m_restart = false;
	m_280 = 0;
	if (TheAptQuitMenu != 0)
		return;
	TheAptQuitMenu = this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::OnInitialized);
		AsciiString name("AptQuitMenu::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::RestartMission);
		AsciiString name("AptQuitMenu::RestartMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::ExitMission);
		AsciiString name("AptQuitMenu::ExitMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::OptionsScreen);
		AsciiString name("AptQuitMenu::OptionsScreen");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::ReturnToGame);
		AsciiString name("AptQuitMenu::ReturnToGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::SaveMenu);
		AsciiString name("AptQuitMenu::SaveMenu");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::LoadMenu);
		AsciiString name("AptQuitMenu::LoadMenu");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::HandleOverRestartButton);
		AsciiString name("QuitMenu/Restart/TheButton");
		m_overButtonHandlers.AddOverButtonHandler(name, AptRef<AptOverButtonHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptQuitMenu::Externs);
		int query = 0;
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; query < 2; ++query)
		{
			AsciiString name(s_externNames[query]);
			m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(binding));
		}
	}
	((WindowManager *)g_bfmeAptWindowManager)->bfme_showBackground(2);
	if (TheGameLogic && TheGameLogic->isInMultiplayerGame())
	{
		AsciiString key("APT:Pause");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("GUI:Menu"), false);
	}
}
