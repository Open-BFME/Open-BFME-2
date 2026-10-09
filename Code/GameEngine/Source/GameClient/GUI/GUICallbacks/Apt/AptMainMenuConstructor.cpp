// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptMainMenu::AptMainMenu, retail 0x00516211 (2802 bytes).
//
// Identity (target evidence): the main menu constructor (strings
// "AptMainMenu::...", vftables 0x00C65F10/0x00C65F0C over the Apt window
// base 0x0051268C, singleton 0x00E048DC). It binds the logo image, the 21
// "AptMainMenu::..." commands to the rowed handlers, the three main menu
// field queries (0x0051569F) and the credits renderer, labels the game from
// the executable path, hides the engine mouse and counts the
// "TimesInGame" option to retire the tutorial flash. The binding idiom is
// the matched Apt screen constructors'.

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


class AptCustomRender;

class AptCustomRenderAdder
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};

class AptScreenInitGadgets;

class Rva00222A8BTarget
{
public:
	void rva002239FA(const AsciiString &window, const AsciiString &image);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

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

class GameClient
{
public:
	unsigned char m_pad000[0xCA];
	bool m_CA; // +0xCA
};

extern GameClient *TheGameClient;

class GlobalData
{
public:
	unsigned char m_pad000[0xAF0];
	bool m_AF0; // +0xAF0
	unsigned char m_padAF1[0xD36 - 0xAF1];
	bool m_D36; // +0xD36
};

extern GlobalData *TheWritableGlobalData;

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

extern Mouse *TheMouse;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual int getInt(const AsciiString &key, int defaultValue) const;
	virtual void setInt(const AsciiString &key, int value);
	virtual bool getBool(const AsciiString &key, bool defaultValue) const;
	virtual void setBool(const AsciiString &key, bool value);
	virtual bool write();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
};

// The menu's title/version text block at +0x290 (constructor 0x005B6ED1).
class BfmeThingTTD
{
public:
	BfmeThingTTD();
	~BfmeThingTTD();
private:
	unsigned char m_pad[0x14];
};

class Rva005B6F1E
{
public:
	void rva005B6F1E(const unsigned short *title, const unsigned short *path);
};

class Rva0051569FMainMenuFields
{
public:
	void access(int query, char *value, bool set);
};

extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameW(void *module, unsigned short *path, unsigned long size);

extern int g_Va00E048DC; // the first main menu

class AptMainMenu : public _bfme_AptGameWindow
{
public:
	AptMainMenu(void *context);
	virtual ~AptMainMenu();
	void OnInitialized(const char *unused);
	void GoodCampaign(const char *unused);
	void EvilCampaign(const char *unused);
	void WarOfTheRing(const char *unused);
	void ContinueCampaign(const char *unused);
	void LoadCampaign(const char *unused);
	void Skirmish(const char *unused);
	void Options(const char *unused);
	void CreateAHero(const char *unused);
	void Credits(const char *unused);
	void CreditsExit(const char *unused);
	void ExitGame(const char *unused);
	void LoadGame(const char *unused);
	void LoadReplay(const char *unused);
	void LevelSelect(const char *unused);
	void LAN(const char *unused);
	void OnlineButtonPressed(const char *unused);
	void BattleSchool(const char *unused);
	void StopGameMovie(const char *unused);
	void ResetResolution(const char *unused);
	void OnTutorial(const char *unused);
	void RenderCredits(void *a, void *b, void *c, void *d);
private:
	bool m_27C;
	bool m_27D;
	bool m_27E;
	bool m_27F;
	bool m_280;
	bool m_281; // flash the tutorial button
	bool m_282;
	unsigned char m_pad283[0x288 - 0x283];
	int m_288;
	int m_28C;
	BfmeThingTTD m_title; // +0x290
	AsciiString m_2A4;
	char m_2A8;
};

// The custom renderers' adder sits at +0x34 of the Apt window half.
class Rva005248D0CustomRenders
{
public:
	unsigned char m_pad[0x34];
	AptCustomRenderAdder m_customRenders; // +0x34
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
AptMainMenu::AptMainMenu(void *context)
	: _bfme_AptGameWindow(context),
	  m_27C(false),
	  m_27D(false),
	  m_27E(false),
	  m_27F(false),
	  m_280(false),
	  m_281(false),
	  m_282(false),
	  m_288(TheGameClient && TheGameClient->m_CA ? 8 : 0),
	  m_28C(0),
	  m_2A8('E')
{
	if (g_Va00E048DC != 0)
		return;
	g_Va00E048DC = (int)this;
	{
		AsciiString image("LogoWithShadow");
		AsciiString window("Image");
		TheRva00222A8BTarget->rva002239FA(window, image);
	}
#define BIND_COMMAND(handler, label) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMainMenu::handler); \
		AsciiString name(label); \
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}
	BIND_COMMAND(OnInitialized, "AptMainMenu::OnInitialized")
	BIND_COMMAND(GoodCampaign, "AptMainMenu::GoodCampaign")
	BIND_COMMAND(EvilCampaign, "AptMainMenu::EvilCampaign")
	BIND_COMMAND(WarOfTheRing, "AptMainMenu::WarOfTheRing")
	BIND_COMMAND(ContinueCampaign, "AptMainMenu::ContinueCampaign")
	BIND_COMMAND(LoadCampaign, "AptMainMenu::LoadCampaign")
	BIND_COMMAND(Skirmish, "AptMainMenu::Skirmish")
	BIND_COMMAND(Options, "AptMainMenu::Options")
	BIND_COMMAND(CreateAHero, "AptMainMenu::CreateAHero")
	BIND_COMMAND(Credits, "AptMainMenu::Credits")
	BIND_COMMAND(CreditsExit, "AptMainMenu::CreditsExit")
	BIND_COMMAND(ExitGame, "AptMainMenu::ExitGame")
	BIND_COMMAND(LoadGame, "AptMainMenu::LoadGame")
	BIND_COMMAND(LoadReplay, "AptMainMenu::LoadReplay")
	BIND_COMMAND(LevelSelect, "AptMainMenu::LevelSelect")
	BIND_COMMAND(LAN, "AptMainMenu::LAN")
	BIND_COMMAND(OnlineButtonPressed, "AptMainMenu::OnlineButtonPressed")
	BIND_COMMAND(BattleSchool, "AptMainMenu::BattleSchool")
	BIND_COMMAND(StopGameMovie, "AptMainMenu::StopGameMovie")
	BIND_COMMAND(ResetResolution, "AptMainMenu::ResetResolution")
	BIND_COMMAND(OnTutorial, "AptMainMenu::OnTutorial")
#undef BIND_COMMAND
#define BIND_FIELD(label, query) \
	{ \
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&Rva0051569FMainMenuFields::access); \
		AsciiString name(label); \
		m_externHandlers.AddExternHandler(name, query, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this)))); \
	}
	BIND_FIELD("MainMenuLevel", 0)
	BIND_FIELD("MainMenuContinueCampaign", 1)
	BIND_FIELD("BlinkBattleSchoolOff", 3)
#undef BIND_FIELD
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptMainMenu::RenderCredits);
		AsciiString name("AptMainMenu::RenderCredits");
		((Rva005248D0CustomRenders *)static_cast<Rva005248D0 *>(this))->m_customRenders.AddCustomRender(name, AptRef<AptCustomRender>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	unsigned short path[260] = { 0 };
	GetModuleFileNameW(0, path, sizeof(path));
	((Rva005B6F1E *)&m_title)->rva005B6F1E(TheGameText->fetch("GUI:Command&ConquerGenerals").str(), path);
	TheWritableGlobalData->m_D36 = false;
	TheMouse->_bfme_setEngineVisibility(false);
	OptionPreferences preferences;
	int timesInGame = preferences.getInt(AsciiString("TimesInGame"), 0) + 1;
	preferences.setInt(AsciiString("TimesInGame"), timesInGame);
	m_281 = preferences.getBool(AsciiString("FlashTutorial"), true);
	if (timesInGame > 5 && m_281)
	{
		m_281 = false;
		preferences.setBool(AsciiString("FlashTutorial"), false);
	}
	preferences.write();
	if (!TheWritableGlobalData->m_AF0)
		m_27E = true;
}
