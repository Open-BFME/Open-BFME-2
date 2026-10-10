// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
// AptSkirmish::AptSkirmish, retail 0x00522B0E (1595 bytes).
//
// Identity (target evidence): WorldBuilder names the body
// AptSkirmish::AptSkirmish; it builds the Apt window base (0x0051268C) and
// the game-setup owner base 0x004444D2 at +0x27C, installs the three
// vftables 0x00C67910/0x00C6790C/0x00C678B0, constructs the game setup
// (+0x288), the 0x005C19B6 member (+0x668), the skirmish preferences
// (+0x698) and the 0x00521623 member (+0x6C8), and for the first instance
// (0x00E04930) binds the 14 "AptSkirmish::..." commands to the rowed
// handlers, the InitGadgets screen reference and the screen title.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

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
class AptOverButtonHandler;

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

// The image binder at +0x40 of the Apt window half (0x00524306 family):
// window name to image name.
class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
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


class AptScreenInitGadgets;
void _bfme_setAptScreenRef(const AsciiString &name, AptRef<AptScreenInitGadgets> ref);

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	// Overloaded virtuals are laid out in reverse declaration order: the
	// AsciiString fetch is vslot 14, the char one vslot 15.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

extern int g_00E04930; // the first skirmish screen

// The game-setup owner interface (constructor 0x004444AE).
class Rva004444D2
{
public:
	Rva004444D2();
	virtual ~Rva004444D2();
private:
	unsigned char m_pad04[0x0C - 0x04];
};

class MpGameSetupOwner;

class AptMpGameSetup
{
public:
	AptMpGameSetup(MpGameSetupOwner *owner, int flags);
	~AptMpGameSetup();
	void rva004422B4(int arg);
private:
	unsigned char m_pad[0x668 - 0x288];
};

class Rva005C19B6
{
public:
	Rva005C19B6(Rva005248D0 *window, int arg);
	~Rva005C19B6();
private:
	unsigned char m_pad[0x698 - 0x668];
};

class SkirmishPreferences
{
public:
	SkirmishPreferences(int arg);
	~SkirmishPreferences();
private:
	unsigned char m_pad[0x6B8 - 0x698];
};

// Input-route member: constructor 0x00521623, destructor 0x0052163E,
// vftable 0x00C67840.
class Rva0052163E
{
public:
	Rva0052163E(int count);
	virtual ~Rva0052163E();
private:
	unsigned char m_pad[0x6D8 - 0x6C8 - 4];
};

class GameWindow;

class __multiple_inheritance AptSkirmish : public _bfme_AptGameWindow, public Rva004444D2
{
public:
	AptSkirmish(void *context, int arg);
	virtual ~AptSkirmish();
	void OnInitialized(const char *unused);
	void OnClosed(const char *unused);
	void rva0052174E(const char *unused); // "Exit" and "Back"
	void StartGame(const char *unused);
	void OnDeleteProfile(const char *unused);
	void OnStatsMenu(const char *unused);
	void OnNewProfileMenu(const char *unused);
	void OnDeleteProfileMenu(const char *unused);
	void OnChangeProfileMenu(const char *unused);
	void OnChangeProfile(const char *unused);
	void OnExitStatsScreen(const char *unused);
	void OnAddProfileAccept(const char *unused);
	void OnProfilePopupCancel(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
private:
	AptMpGameSetup m_setup; // +0x288
	Rva005C19B6 m_668;
	SkirmishPreferences m_preferences; // +0x698
	int m_6B8;
	int m_6BC;
	bool m_6C0;
	bool m_6C1;
	bool m_6C2;
	int m_6C4;
	Rva0052163E m_6C8;
	AsciiString m_6D8;
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptSkirmish::AptSkirmish(void *context, int arg)
	: _bfme_AptGameWindow(context),
	  m_setup((MpGameSetupOwner *)static_cast<Rva004444D2 *>(this), 0x10000007),
	  m_668(static_cast<Rva005248D0 *>(this), arg),
	  m_preferences(arg),
	  m_6B8(0),
	  m_6C0(true),
	  m_6C1(false),
	  m_6C2(false),
	  m_6C4(0),
	  m_6C8(10)
{
	m_setup.rva004422B4(arg);
	if (g_00E04930 != 0)
		return;
	g_00E04930 = (int)this;
#define BIND_COMMAND(handler, label) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSkirmish::handler); \
		AsciiString name(label); \
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}
	BIND_COMMAND(OnInitialized, "AptSkirmish::OnInitialized")
	BIND_COMMAND(OnClosed, "AptSkirmish::OnClosed")
	BIND_COMMAND(rva0052174E, "AptSkirmish::Exit")
	BIND_COMMAND(rva0052174E, "AptSkirmish::Back")
	BIND_COMMAND(StartGame, "AptSkirmish::StartGame")
	BIND_COMMAND(OnDeleteProfile, "AptSkirmish::OnDeleteProfile")
	BIND_COMMAND(OnStatsMenu, "AptSkirmish::OnStatsMenu")
	BIND_COMMAND(OnNewProfileMenu, "AptSkirmish::OnNewProfileMenu")
	BIND_COMMAND(OnDeleteProfileMenu, "AptSkirmish::OnDeleteProfileMenu")
	BIND_COMMAND(OnChangeProfileMenu, "AptSkirmish::OnChangeProfileMenu")
	BIND_COMMAND(OnChangeProfile, "AptSkirmish::OnChangeProfile")
	BIND_COMMAND(OnExitStatsScreen, "AptSkirmish::OnExitStatsScreen")
	BIND_COMMAND(OnAddProfileAccept, "AptSkirmish::OnAddProfileAccept")
	BIND_COMMAND(OnProfilePopupCancel, "AptSkirmish::OnProfilePopupCancel")
#undef BIND_COMMAND
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptSkirmish::InitGadgets);
		AsciiString name("AptSkirmish::InitGadgets");
		_bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		AsciiString window("APT:OnlineOrNetwork");
		g_bfmeAptWindowManager->bfmeSetText(window, TheGameText->fetch("APT:Skirmish"), false);
	}
}
