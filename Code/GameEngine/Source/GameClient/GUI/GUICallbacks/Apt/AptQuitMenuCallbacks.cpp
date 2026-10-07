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
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);
	void rva0023D0E3(bool selfDestruct);

	unsigned char m_pad000[0x40];
	unsigned int m_40; // +0x40
	unsigned char m_pad044[0x110 - 0x44];
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
	friend class AptQuitMenu;

public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);

private:
	void commitPendingCursor();
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

// The living-world logic's player at +0x98 and its byte +0x3C5.
struct LivingWorldPlayer
{
	unsigned char m_pad000[0x3C5];
	bool m_3c5; // +0x3C5
};

struct LivingWorldLocal
{
	unsigned char m_pad000[0x98];
	LivingWorldPlayer *m_98; // +0x98
};

class Rva002B2B66
{
public:
	int rva002B2B66();
};

// TheInGameUI (0x00DFEDF0): vslot 94 hides the quit menu (BFME1's slot 84).
class InGameUI
{
public:
#define IGUI_SLOT(N) virtual void slot##N();
	IGUI_SLOT(00) IGUI_SLOT(01) IGUI_SLOT(02) IGUI_SLOT(03) IGUI_SLOT(04)
	IGUI_SLOT(05) IGUI_SLOT(06) IGUI_SLOT(07) IGUI_SLOT(08) IGUI_SLOT(09)
	IGUI_SLOT(10) IGUI_SLOT(11) IGUI_SLOT(12) IGUI_SLOT(13) IGUI_SLOT(14)
	IGUI_SLOT(15) IGUI_SLOT(16) IGUI_SLOT(17) IGUI_SLOT(18) IGUI_SLOT(19)
	IGUI_SLOT(20) IGUI_SLOT(21) IGUI_SLOT(22) IGUI_SLOT(23) IGUI_SLOT(24)
	IGUI_SLOT(25) IGUI_SLOT(26) IGUI_SLOT(27) IGUI_SLOT(28) IGUI_SLOT(29)
	IGUI_SLOT(30) IGUI_SLOT(31) IGUI_SLOT(32) IGUI_SLOT(33) IGUI_SLOT(34)
	IGUI_SLOT(35) IGUI_SLOT(36) IGUI_SLOT(37) IGUI_SLOT(38) IGUI_SLOT(39)
	IGUI_SLOT(40) IGUI_SLOT(41) IGUI_SLOT(42) IGUI_SLOT(43) IGUI_SLOT(44)
	IGUI_SLOT(45) IGUI_SLOT(46) IGUI_SLOT(47) IGUI_SLOT(48) IGUI_SLOT(49)
	IGUI_SLOT(50) IGUI_SLOT(51) IGUI_SLOT(52) IGUI_SLOT(53) IGUI_SLOT(54)
	IGUI_SLOT(55) IGUI_SLOT(56) IGUI_SLOT(57) IGUI_SLOT(58) IGUI_SLOT(59)
	IGUI_SLOT(60) IGUI_SLOT(61) IGUI_SLOT(62) IGUI_SLOT(63) IGUI_SLOT(64)
	IGUI_SLOT(65) IGUI_SLOT(66) IGUI_SLOT(67) IGUI_SLOT(68) IGUI_SLOT(69)
	IGUI_SLOT(70) IGUI_SLOT(71) IGUI_SLOT(72) IGUI_SLOT(73) IGUI_SLOT(74)
	IGUI_SLOT(75) IGUI_SLOT(76) IGUI_SLOT(77) IGUI_SLOT(78) IGUI_SLOT(79)
	IGUI_SLOT(80) IGUI_SLOT(81) IGUI_SLOT(82) IGUI_SLOT(83) IGUI_SLOT(84)
	IGUI_SLOT(85) IGUI_SLOT(86) IGUI_SLOT(87) IGUI_SLOT(88) IGUI_SLOT(89)
	IGUI_SLOT(90) IGUI_SLOT(91) IGUI_SLOT(92) IGUI_SLOT(93)
#undef IGUI_SLOT
	virtual void slot94(bool visible);
};

extern InGameUI *TheInGameUI;

// TheShell (0x00E01E48) and its rowed 0x0035BF4C (BFME1's Shell::hide).
class Shell
{
public:
	void rva0035BF4C(bool flag);
};

extern Shell *TheShell;

// TheNetwork (0x00DFEA28): vslot 37 quits the network game.
class NetworkInterface
{
public:
#define NET_SLOT(N) virtual void slot##N();
	NET_SLOT(00) NET_SLOT(01) NET_SLOT(02) NET_SLOT(03) NET_SLOT(04)
	NET_SLOT(05) NET_SLOT(06) NET_SLOT(07) NET_SLOT(08) NET_SLOT(09)
	NET_SLOT(10) NET_SLOT(11) NET_SLOT(12) NET_SLOT(13) NET_SLOT(14)
	NET_SLOT(15) NET_SLOT(16) NET_SLOT(17) NET_SLOT(18) NET_SLOT(19)
	NET_SLOT(20) NET_SLOT(21) NET_SLOT(22) NET_SLOT(23) NET_SLOT(24)
	NET_SLOT(25) NET_SLOT(26) NET_SLOT(27) NET_SLOT(28) NET_SLOT(29)
	NET_SLOT(30) NET_SLOT(31) NET_SLOT(32) NET_SLOT(33) NET_SLOT(34)
	NET_SLOT(35) NET_SLOT(36)
#undef NET_SLOT
	virtual void quitGame();
};

extern NetworkInterface *TheNetwork;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendBooleanArgument(bool arg);
};

// MessageStreamSubsystem (0x00A00950); appendMessage is vslot 18.
class MessageStream
{
public:
#define MSG_SLOT(N) virtual void slot##N();
	MSG_SLOT(00) MSG_SLOT(01) MSG_SLOT(02) MSG_SLOT(03) MSG_SLOT(04)
	MSG_SLOT(05) MSG_SLOT(06) MSG_SLOT(07) MSG_SLOT(08) MSG_SLOT(09)
	MSG_SLOT(10) MSG_SLOT(11) MSG_SLOT(12) MSG_SLOT(13) MSG_SLOT(14)
	MSG_SLOT(15) MSG_SLOT(16) MSG_SLOT(17)
#undef MSG_SLOT
	virtual GameMessage *appendMessage(int type);
};

extern MessageStream *MessageStreamSubsystem;

// The network quit's frame limit (.rdata 0x007ED97C).
extern unsigned int g_007ED97C;

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
	void bfme_hideBackground(bool flag);
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
	virtual ~AptQuitMenu();

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

// Retail 0x0051B15E, 512 bytes: the quit menu's destructor, as BFME1's
// ~BfmeAptScreenQuitMenu (AptQuitMenu.cpp there). The open menu hides
// itself, unpauses a single player game and, when exiting, quits the
// network game, ends the war of the ring battle (0x448 surrender unless
// selection is locked, then 0x6B8 with the rowed 0x002B2B66) or runs
// GameLogic's exit tail 0x0023D0E3, and shows background 1; otherwise it
// hides the background unless +0x27D. Then "APT:Pause" is relabelled.
// Retail reads TheGameLogic once, keeps it across isInMultiplayerGame and
// rereads it only after the three calls that can change it; the rereads
// are spelled out.
AptQuitMenu::~AptQuitMenu()
{
	if (this != TheAptQuitMenu)
		return;
	TheAptQuitMenu = 0;
	if (TheInGameUI)
		TheInGameUI->slot94(false);
	GameLogic *logic = TheGameLogic;
	if (logic && !logic->isInMultiplayerGame())
	{
		logic->rva0023CD9E(false, m_280, true);
		logic = TheGameLogic;
	}
	if (TheMouse)
	{
		TheMouse->commitPendingCursor();
		logic = TheGameLogic;
	}
	if (TheShell && !m_exit)
	{
		TheShell->rva0035BF4C(false);
		logic = TheGameLogic;
	}
	if (logic && m_exit)
	{
		if (logic->m_40 < g_007ED97C && (logic->m_110 == 1 || logic->m_110 == 5) && TheNetwork)
			TheNetwork->quitGame();
		else if (logic->m_114 != 3 && g_009FEF10)
		{
			if (((LivingWorldLocal *)g_009FEF10)->m_98)
				((LivingWorldLocal *)g_009FEF10)->m_98->m_3c5 = true;
			if (!g_009FEF10->isSelectionLocked())
			{
				GameMessage *surrender = MessageStreamSubsystem->appendMessage(0x448);
				surrender->appendBooleanArgument(true);
			}
			GameMessage *msg = MessageStreamSubsystem->appendMessage(0x6B8);
			msg->appendIntegerArgument(((Rva002B2B66 *)g_009FEF10)->rva002B2B66());
		}
		else
			logic->rva0023D0E3(true);
		if (g_bfmeAptWindowManager)
			((WindowManager *)g_bfmeAptWindowManager)->bfme_showBackground(1);
	}
	else if (!m_27d && g_bfmeAptWindowManager)
		((WindowManager *)g_bfmeAptWindowManager)->bfme_hideBackground(false);
	AsciiString key("APT:Pause");
	g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("APT:Pause"), false);
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
