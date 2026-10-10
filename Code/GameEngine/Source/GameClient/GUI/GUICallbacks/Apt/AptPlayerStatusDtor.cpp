// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1AptPlayerStatus@@UAE@XZ
// stlport
//
// ??1AptPlayerStatus@@UAE@XZ, retail 0x004E4655..0x004E4745 (240 bytes, EH).
// The player status / objectives screen destructor (class and views as in
// AptPlayerStatusScreen.cpp; the deleting destructor 0x004E4750 kept the
// address-derived name Rva004E4655): when this is the open screen
// (0x00A04450) it clears the global, closes the in-game UI menu, unpauses a
// single player game outside mode 6, hides the shell and the background and
// closes its InitGadgets screen reference; then the color list and the Apt
// window base go.

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

// The Apt window manager (VA 0x00DFE4CC) and its background switch.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	void rva00222F55(bool show);
};

class Shell
{
public:
	void rva0035BF4C(bool shutdownImmediate);
};
extern Shell *TheShell;

void _bfme_closeAptScreen(const AsciiString &name);


// The Apt callback functors (Rva0057BC63FunctorHolder.cpp, as in
// AptScoreScreenCallbacks.cpp).
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

class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

// The Apt screen base (BfmeAptGameWindowDestructor.cpp): a 0x218-byte
// GameWindow and, at +0x218, the 0x58-byte callback registry.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();

	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10

private:
	unsigned char m_pad01C[0x58 - 0x1C];
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

// The colors' element: a 4-byte value whose push_back is the folded copy
// at 0x002E01C6, not vector<int>'s (0x00688940); its type is unknown.
enum Rva004E476CColor
{
};

// The open player status screen (VA 0x00E04450).
struct GlobalA04450;
extern GlobalA04450 *g_Va00A04450;

class GameWindow;

class AptPlayerStatus : public _bfme_AptGameWindow
{
public:
	AptPlayerStatus(void *context);
	virtual ~AptPlayerStatus();

	// AptPlayerStatusCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void rva004E4A34(const char *unused);
	void PlayerColor(int slot, char *result, bool set);
	void Objective(int row, char *result, bool skip);
	// "AptObjectivesMenu::ReturnToGame" (rowed as the stdcall
	// Rva004E40A6Enable), pinned by address.
	void rva004E40A6(const char *unused);
	// Unrowed 0x004E434C: "NumOfPlayers", "InSkirmish" and
	// "AptObjectivesMenu::InputEnabled" by index, pinned by address.
	void rva004E434C(int query, char *result, bool set);
	// "Objective%d", the row's objective text
	// (AptPlayerStatusObjectiveText.cpp).
	void rva004E4553(int row, char *result, bool set);
	// Unrowed 0x004E476C: fills the player table from the game slots.
	void rva004E476C();
	// "PlayerTable:<row>:<column>" (rowed as the stdcall
	// Rva004E44FBSet; it ignores this), pinned by address.
	void rva004E44FB(int row, int column, const UnicodeString &text);

private:
	friend void Rva004E41AB();

	_STL::vector<Rva004E476CColor> m_colors; // +0x27C
	int m_state; // +0x288
	GameWindow *m_mute[8]; // +0x28C
	signed char m_slot[8]; // +0x2AC
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The game mode at +0x110 (2 skirmish, 6 the one where the UI's +0x16
// flag decides whether input is enabled) is GameLogic::m_110.
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Rva0023C902
{
public:
	int rva0023C902();
};

// The +0x10 view TheInGameUI's 0x000CF155 returns and the folded forwarder
// to its vslot 3 (0x005CB265), both pinned (as in AptQuitMenuCallbacks.cpp).
class Rva005CB260;

class Rva005CB265
{
public:
	virtual int rva005CB265();
};

// TheInGameUI (0x00DFEDF0): vslot 94 shows or hides the menu, vslot 95
// reports one already up.
class InGameUI
{
public:
#define UI_SLOT(N) virtual void slot##N();
	UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05) UI_SLOT(06) UI_SLOT(07)
	UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15)
	UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29) UI_SLOT(30) UI_SLOT(31)
	UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35) UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39)
	UI_SLOT(40) UI_SLOT(41) UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
	UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63)
	UI_SLOT(64) UI_SLOT(65) UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
	UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
	UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83) UI_SLOT(84) UI_SLOT(85) UI_SLOT(86) UI_SLOT(87)
	UI_SLOT(88) UI_SLOT(89) UI_SLOT(90) UI_SLOT(91) UI_SLOT(92) UI_SLOT(93)
#undef UI_SLOT
	virtual void slot94(bool visible);
	virtual bool slot95();

	Rva005CB260 *rva000CF155();

	unsigned char m_pad04[0x16 - 4];
	bool m_16; // +0x16
};

extern InGameUI *TheInGameUI;

// The extern queries' names, by index (0x00C621A8).
static const char *const s_externNames[] = { "NumOfPlayers", "InSkirmish", "AptObjectivesMenu::InputEnabled" };


AptPlayerStatus::~AptPlayerStatus()
{
	if (this == (AptPlayerStatus *)g_Va00A04450)
	{
		g_Va00A04450 = 0;
		if (TheInGameUI)
			TheInGameUI->slot94(false);
		GameLogic *logic = TheGameLogic;
		if (logic && !logic->isInMultiplayerGame() && (logic->m_110?logic->m_110:logic->m_110) != 6)
			logic->rva0023CD9E(false, 0, true);
		if (TheShell)
			TheShell->rva0035BF4C(false);
		if (g_bfmeAptWindowManager)
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(false);
		_bfme_closeAptScreen(AsciiString("AptPlayerStatus::InitGadgets"));
	}
}
