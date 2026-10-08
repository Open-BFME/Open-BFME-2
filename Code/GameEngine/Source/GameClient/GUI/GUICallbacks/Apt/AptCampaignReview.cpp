// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's campaign review screen (CampaignReview.apt, built by the
// 0x27C-byte factory at 0x002D1E8F): its constructor, which becomes the
// open review screen and binds its callbacks by name (Continue and
// playerSideType are in AptLobbyScreenInitCallbacks.cpp), the campaign
// result text it sets and its TotalCampaignScore query. BFME 1's
// AptScreenFactories.cpp (BfmeAptScreenCampaignReview) is the donor.

#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

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

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

// RvaSingletonFwdMisc.cpp's view of the window manager.
class Rva00224BC9Owner
{
public:
	bool check();
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

// The open campaign review screen (VA 0x00E048C8).
extern void *g_obj12F495C;

// The living world (VA 0x00DFEF10) and Rva002B4DE2.cpp's view of it: the
// campaign result, 2, 1 or 0.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002B4DE2
{
public:
	int rva002B4DE2();
	int rva002B5C1D();
};

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

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

class AptCampaignReview : public _bfme_AptGameWindow
{
public:
	AptCampaignReview(void *context);
	virtual ~AptCampaignReview();

	// AptLobbyScreenInitCallbacks.cpp.
	void Continue(const char *unused);
	void playerSideType(int unused, char *result, bool skip);
	void TotalCampaignScore(int unused, char *result, bool skip);
	// InitGadgets is empty; it folded into the shared three-argument empty
	// body 0x000D1407 and is pinned by that address.
	void rva000D1407(const char *name, void *argument, GameWindow *window);
	void DisplayVictoryLevel();
};

// Retail 0x00512AC8, 442 bytes: the screen's constructor. The first one
// becomes the open review screen, binds its Continue command, its (empty)
// InitGadgets screen reference and the TotalCampaignScore and playerSideType
// queries, sets the campaign result text and refreshes the window manager.
#pragma pointers_to_members(full_generality, multiple_inheritance)
AptCampaignReview::AptCampaignReview(void *context)
	: _bfme_AptGameWindow(context)
{
	if (g_obj12F495C != 0)
		return;
	g_obj12F495C = this;
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignReview::Continue);
		AsciiString name("AptCampaignReview::Continue");
		m_commandMaps.AddCommandMap(name, AptRef<AptCommandMap>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignReview::rva000D1407);
		AsciiString screen("AptCampaignReview::InitGadgets");
		_bfme_setAptScreenRef(screen, AptRef<AptScreenInitGadgets>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignReview::TotalCampaignScore);
		AsciiString name("TotalCampaignScore");
		m_externHandlers.AddExternHandler(name, 0, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	{
		FunctorMethod method = reinterpret_cast<FunctorMethod>(&AptCampaignReview::playerSideType);
		AsciiString name("playerSideType");
		m_externHandlers.AddExternHandler(name, 1, AptRef<AptExternHandler>(MakeBinding(method, reinterpret_cast<FunctorTarget *>(this))));
	}
	DisplayVictoryLevel();
	((Rva00224BC9Owner *)g_bfmeAptWindowManager)->check();
}

// Retail 0x00512948, 356 bytes: "APT:CmpgnRevResult" names the campaign
// result, total victory, victory or survived, and is empty without a living
// world or for any other result.
void AptCampaignReview::DisplayVictoryLevel()
{
	if (TheLivingWorldLogic == 0)
	{
		g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:CmpgnRevResult"), UnicodeString::TheEmptyString, false);
		return;
	}
	int result = ((Rva002B4DE2 *)TheLivingWorldLogic)->rva002B4DE2();
	if (result == 2)
	{
		AsciiString name("APT:CmpgnRevResult");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:TotalVictoryCaps", 0), false);
	}
	else if (result == 1)
	{
		AsciiString name("APT:CmpgnRevResult");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:VictoryCaps", 0), false);
	}
	else if (result == 0)
	{
		AsciiString name("APT:CmpgnRevResult");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch("APT:SurvivedCaps", 0), false);
	}
	else
	{
		AsciiString name("APT:CmpgnRevResult");
		g_bfmeAptWindowManager->bfmeSetText(name, UnicodeString::TheEmptyString, false);
	}
}

// Retail 0x00512838, 44 bytes: the TotalCampaignScore query the constructor
// binds with argument 0 prints the living world's campaign score.
void AptCampaignReview::TotalCampaignScore(int unused, char *result, bool skip)
{
	if (skip)
		return;
	if (TheLivingWorldLogic == 0)
		return;
	sprintf(result, "%d", ((Rva002B4DE2 *)TheLivingWorldLogic)->rva002B5C1D());
}
