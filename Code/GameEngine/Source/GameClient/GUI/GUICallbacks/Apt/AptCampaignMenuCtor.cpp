// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
//
// ??0Rva005212FC@@QAE@PAX@Z @0x005212FC 807B: BFME2's campaign menu screen
// constructor (0x288-byte factory 0x002D2181). Target evidence: rowed
// _bfme_AptGameWindow base ctor 0x0051268C; vptrs 0x00C67720 and 0x00C6771C
// at +0x218 (the class whose dtor is rowed at 0x00521206); the +0x27C member
// (two AsciiStrings whose dtor is rowed at 0x005211D1) and the +0x284 flag
// cleared; the first instance becomes the open campaign menu (VA 0x00E0492C)
// and binds the five AptCampaignMenu::OnBttn* commands (rowed 0x00521172..)
// and the Victorious query (0x0052112F) named by the .data table 0x00DD1728;
// TheLinearCampaignManager fills the +0x27C member (rowed 0x001EB74B); the
// first string prefixed "CampaignName:" is fetched as the mission name text
// and the second names the campaign image. Pattern from AptCampaignReview.cpp.
// The callback names identify the class as AptCampaignMenu; the row keeps
// the pinned address name.

#include "ascii_string.h"
#include "unicode_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();

private:
	unsigned char m_pad004[0x218 - 4];
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

class Rva00222A8BTarget
{
public:
	void rva002239FA(const AsciiString &name, const AsciiString &value);
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

class AptCommandMapAdder
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

private:
	unsigned char m_names[0xC];
};

class AptExternHandlerAdder
{
public:
	void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);

private:
	unsigned char m_names[0xC];
};

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

// The campaign menu content TheLinearCampaignManager fills: mission name and
// image name (dtor rowed 0x005211D1).
struct Rva001EB6A5Out;

class Rva005211D1
{
public:
	Rva005211D1() : m_victorious(false) {}
	~Rva005211D1();

	AsciiString m_missionName;
	AsciiString m_image;
	bool m_victorious; // +0x08
};

class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;

class Rva001EB74B
{
public:
	bool rva001EB74B(Rva001EB6A5Out *out);
};

class GameTextInterface
{
public:
#define TEXT_SLOT(N) virtual void slot##N();
	TEXT_SLOT(00) TEXT_SLOT(01) TEXT_SLOT(02) TEXT_SLOT(03) TEXT_SLOT(04) TEXT_SLOT(05) TEXT_SLOT(06)
	TEXT_SLOT(07) TEXT_SLOT(08) TEXT_SLOT(09) TEXT_SLOT(10) TEXT_SLOT(11) TEXT_SLOT(12) TEXT_SLOT(13)
#undef TEXT_SLOT
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

// The open campaign menu (VA 0x00E0492C).
extern int g_Va00E0492C;

// .data name table 0x00DD1728: { "CampaignMenu:Victorious", 0 }.
extern const char *g_00DD1728[];

class AptCampaignMenu
{
public:
	void OnBttnMainMenu(const char *unused);
	void OnBttnSaveGame(const char *unused);
	void OnBttnLoadGame(const char *unused);
	void OnBttnLastMission(const char *unused);
	void OnBttnNextMission(const char *unused);
	void Victorious(int query, char *result, bool skip);
};

class Rva005212FC : public _bfme_AptGameWindow
{
public:
	Rva005212FC(void *context);
	virtual ~Rva005212FC();

private:
	Rva005211D1 m_content; // +0x27C
};

#pragma pointers_to_members(full_generality, multiple_inheritance)
Rva005212FC::Rva005212FC(void *context)
	: _bfme_AptGameWindow(context)
{
	if (g_Va00E0492C != 0)
		return;
	g_Va00E0492C = (int)this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::OnBttnMainMenu);
		AsciiString name("AptCampaignMenu::OnBttnMainMenu");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::OnBttnSaveGame);
		AsciiString name("AptCampaignMenu::OnBttnSaveGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::OnBttnLoadGame);
		AsciiString name("AptCampaignMenu::OnBttnLoadGame");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::OnBttnLastMission);
		AsciiString name("AptCampaignMenu::OnBttnLastMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::OnBttnNextMission);
		AsciiString name("AptCampaignMenu::OnBttnNextMission");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignMenu::Victorious);
		FunctorBinding binding = MakeBinding(method, reinterpret_cast<FunctorTarget *>(this));
		AsciiString name(g_00DD1728[0]);
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(binding));
	}
	((Rva001EB74B *)TheLinearCampaignManager)->rva001EB74B((Rva001EB6A5Out *)&m_content);
	AsciiString label("CampaignName:");
	label.concat(m_content.m_missionName);
	{
		AsciiString name("APT:CampaignMissionName");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(label, 0), false);
	}
	{
		AsciiString name("AptCampaign::LoadImage");
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva002239FA(name, m_content.m_image);
	}
}
