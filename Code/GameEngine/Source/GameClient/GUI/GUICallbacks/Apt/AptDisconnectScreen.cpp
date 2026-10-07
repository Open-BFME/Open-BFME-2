// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's in-game disconnect screen (DisconnectScreen.apt, built by the
// 0x290-byte factory at 0x002D1EC9): its constructor, which becomes the
// open disconnect menu and binds the callbacks of
// AptDisconnectScreenKick.cpp by name, its destructor and its kick-button
// refresh. BFME 1's AptScreenFactories.cpp (BfmeAptScreenDisconnectScreen,
// 0x00104D40's constructor) is the donor.

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
	void rva002233A6(int mode);
};

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
void _bfme_closeAptScreen(const AsciiString &name);

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

// The open disconnect menu (VA 0x00E048D0; BFME 1's TheDisconnectMenu).
extern int g_Va00E048D0;

// Rva00512CE9Kick.cpp's view of this screen: shows or hides a slot's kick
// button and records it at +0x286.
class Rva00512CE9
{
public:
	void rva00512CE9(int player, bool show);
};

class AptDisconnectScreen : public _bfme_AptGameWindow
{
public:
	AptDisconnectScreen(void *context);
	virtual ~AptDisconnectScreen();

	// AptDisconnectScreenKick.cpp and AptLobbyScreenInitCallbacks.cpp.
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	void OnInitialized(const char *unused);
	void Quit(const char *unused);
	void Kick(const char *slot);
	void OnBttnEnterText(const char *unused);
	void PlayerColor(int slot, char *result, bool skip);
	// Unrowed 0x00512EDD: empties a slot's name (BFME 1's
	// DisconnectMenu::removePlayer), pinned by address.
	void rva00512EDD(int slot, UnicodeString name);
	// Vslot 5: re-applies the kick buttons once they changed.
	int rva00512DB1();

private:
	GameWindow *m_chatBox; // +0x27C
	GameWindow *m_chatEntry; // +0x280
	bool m_kickButtonsDirty; // +0x284
	bool m_quit; // +0x285
	bool m_kickButtons[8]; // +0x286
};

// Retail 0x00513558, 699 bytes: the screen's constructor. The first one
// becomes the open disconnect menu, switches the window manager's
// background, binds InitGadgets as its screen reference, the OnInitialized,
// Quit, Kick and chat commands and "DisconnectScreen:PlayerColor:0".."7",
// emptying each slot's name.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptDisconnectScreen::AptDisconnectScreen(void *context)
	: _bfme_AptGameWindow(context),
	  m_chatBox(0),
	  m_chatEntry(0),
	  m_kickButtonsDirty(false),
	  m_quit(false)
{
	if (g_Va00E048D0 != 0)
		return;
	g_Va00E048D0 = (int)this;
	memset(m_kickButtons, 0, sizeof(m_kickButtons));
	((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002233A6(2);
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::InitGadgets);
		AsciiString screen("DisconnectScreen::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::OnInitialized);
		AsciiString name("AptDisconnectScreen::OnInitialized");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::Quit);
		AsciiString name("AptDisconnectScreen::Quit");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::Kick);
		AsciiString name("AptDisconnectScreen::Kick");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::OnBttnEnterText);
		AsciiString name("AptDisconnectScreen::Chat::OnBttnEnterText");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	AsciiString name;
	{
		int slot = 0;
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptDisconnectScreen::PlayerColor);
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		for (; slot < 8; ++slot)
		{
			name.format("DisconnectScreen:PlayerColor:%d", slot);
			m_externHandlers.AddExternHandler(name, slot, AptRef<AptExternHandler>(binding));
			rva00512EDD(slot, UnicodeString::TheEmptyString);
		}
	}
}

// Retail 0x00512E49, 137 bytes: the open menu clears itself, restores the
// window manager's background unless it is quitting and closes its screen
// reference.
AptDisconnectScreen::~AptDisconnectScreen()
{
	if ((AptDisconnectScreen *)g_Va00E048D0 == this)
	{
		g_Va00E048D0 = 0;
		if (!m_quit)
			((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(false);
		_bfme_closeAptScreen(AsciiString("DisconnectScreen::InitGadgets"));
	}
}

// Retail 0x00512DB1, 48 bytes: vslot 5 of the vftable 0x00C65B6C.
int AptDisconnectScreen::rva00512DB1()
{
	if (m_kickButtonsDirty)
	{
		m_kickButtonsDirty = false;
		for (int slot = 0; slot < 8; ++slot)
			((Rva00512CE9 *)this)->rva00512CE9(slot, m_kickButtons[slot]);
	}
	return 1;
}
