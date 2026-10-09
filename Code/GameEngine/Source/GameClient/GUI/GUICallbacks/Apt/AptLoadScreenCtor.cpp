// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0AptLoadScreen@@QAE@PAX@Z
// retail 0x0043AE44..0x0043B0B0 (621 bytes) thiscall RET 4.
//
// AptLoadScreen::AptLoadScreen (WorldBuilder name 0x0129F110,
// AptLoadScreen.cpp lines 77..102; one caller 0x0023E02A). Over the window
// base Rva00355D66 (rowed constructor 0x00355D4E): the screen's vftable
// 0x00C3D50C, its owner argument at +0x14, the embedded AptMapPreview at
// +0x18 (rowed constructor 0x0057CF43) built over a new 12-byte reference
// object (vftable 0x00C3D490, inline here), the per-slot ids at +0x90/+0xB0
// cleared to -1 and the instance global 0x00E0330C. It registers the
// "GameLoading:PlayerColor:%d" (0..7) and "GameLoadingType" Apt extern
// handlers (methods 0x0043A1C0 and 0x0043A242, bound through the rowed
// delegate constructor 0x00579E47), runs the preview's registration
// 0x0057E45C, creates "LoadScreen.apt" through TheWindowManager slot 32 and,
// with its first window, stores the window (+0x08) and its Apt level
// (0x00222547) at +0x8C, sets "GUI:Level" to a blank outside skirmish and
// online play and to "GUI:Rank" in a ranked GameSpy game (+0xFF4), and
// stops the window transitions (0x001DBB87).
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;

class GameWindow;
class Rva0043DA65;

// The window base: Gen_004902A0 (vptr, list link) then the window (+0x08)
// and a flag (+0x0C); rowed constructor 0x00355D4E.
class Rva00355D66
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
protected:
	void *m_next;			// +0x04
	GameWindow *m_win;		// +0x08
	Bool m_flag;			// +0x0C
};

// The reference-counted object the preview is handed (vftable 0x00C3D490):
// the base clears +0x04, the class +0x08.
class Rva0043A340Base
{
public:
	Rva0043A340Base() : m_refs(0) {}
	virtual ~Rva0043A340Base() {}
	Int m_refs;			// +0x04
};
class Rva0043A340 : public Rva0043A340Base
{
public:
	Rva0043A340() : m_08(0) {}
	virtual ~Rva0043A340() {}
	Int m_08;			// +0x08
};

class AptMapPreview
{
public:
	AptMapPreview(Rva0043DA65 *game);	// 0x0057CF43
	~AptMapPreview();			// 0x0057CF0B
	void rva0057E45C();			// 0x0057E45C, the preview's Apt registration
private:
	unsigned char m_data[0x70];
};

class __single_inheritance AptLoadScreen;
typedef void (AptLoadScreen::*AptLoadScreenHandler)(void);

struct DelegateDesc
{
	DelegateDesc(AptLoadScreen *object, AptLoadScreenHandler method) : m_object(object), m_method(method) {}

	AptLoadScreen *m_object;
	AptLoadScreenHandler m_method;
};

// The color handlers' delegate goes through a by-value copy and is built once
// for the loop (retail loads the method address into eax for that copy).
static __forceinline DelegateDesc byValue(DelegateDesc desc) { return desc; }

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(DelegateDesc desc) : Rva00579E47(desc) {}
	AptRef(const DelegateDesc *desc) : Rva00579E47(*desc) {}	// built from a delegate kept outside a loop
};

class AptExternHandler;

template <int N> class AptLoadScreenSlots : public AptLoadScreenSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class AptLoadScreenSlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

// The Apt player / window manager (0x00DFE4CC).
class AptPlayer : public AptLoadScreenSlots<19>
{
public:
	static int GetLevelIndex(GameWindow *window);
	virtual void slot19(Int value);				// +0x4C
	void AddExternHandler(const AsciiString &name, Int arg, AptRef<AptExternHandler> handler);	// 0x0022445D
};

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool flag);	// 0x00225301
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheAptPlayer ((AptPlayer *)g_bfmeAptWindowManager)

// The level index of a window (WorldBuilder AptPlayer::GetLevelIndex).


class WindowLayout
{
public:
	virtual void hide(Bool hide);				// slot 0
	void *m_04;
	GameWindow *m_firstWindow;				// +0x08
};

class GameWindowManager : public AptLoadScreenSlots<32>
{
public:
	virtual WindowLayout *winCreateLayout(AsciiString filename);	// +0x80
};
extern GameWindowManager *TheWindowManager;

class GameTextInterface : public AptLoadScreenSlots<15>
{
public:
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);	// +0x3C
};
extern GameTextInterface *TheGameText;

class GameInfo;
class GameSpyInfoInterface;
extern GameInfo *TheSkirmishGameInfo;
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyStagingRoom
{
public:
	unsigned char m_pad000[0xFF4];
	Bool m_isRanked;					// +0xFF4
};
extern GameSpyStagingRoom *TheGameSpyGame;

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva001DBB87ZeroSetter
{
public:
	void disable();						// 0x001DBB87
};

class AptLoadScreen : public Rva00355D66
{
public:
	AptLoadScreen(void *owner);
	virtual ~AptLoadScreen();

	void PlayerColor(Int index, char *value, Bool set);	// 0x0043A1C0
	void GameLoadingType(Int index, char *value, Bool set);	// 0x0043A242

private:
	WindowLayout *m_layout;					// +0x10
	void *m_owner;						// +0x14
	AptMapPreview m_mapPreview;				// +0x18
	Int m_88;						// +0x88
	Int m_level;						// +0x8C
	Int m_90[8];						// +0x90
	Int m_ids[8];						// +0xB0
	Bool m_D0;						// +0xD0
};

// The load screen instance (data ledger ?g_Va00E0330C@@3HA).
extern int g_Va00E0330C;

AptLoadScreen::AptLoadScreen(void *owner)
	: m_layout(0), m_owner(owner), m_mapPreview((Rva0043DA65 *)new Rva0043A340), m_88(0), m_level(-1), m_D0(false)
{
	g_Va00E0330C = (int)this;
	for (Int i = 0; i < 8; ++i)
	{
		m_90[i] = -1;
		m_ids[i] = -1;
	}

	AsciiString colorName;
	AsciiString unused;
	{
		Int slot = 0;
		DelegateDesc colorHandler = byValue(DelegateDesc(this, reinterpret_cast<AptLoadScreenHandler>(&AptLoadScreen::PlayerColor)));
		for (; slot < 8; ++slot)
		{
			colorName.format("GameLoading:PlayerColor:%d", slot);
			TheAptPlayer->AddExternHandler(colorName, slot, AptRef<AptExternHandler>(&colorHandler));
		}
	}
	{
		AsciiString typeName("GameLoadingType");
		TheAptPlayer->AddExternHandler(typeName, 0, AptRef<AptExternHandler>(DelegateDesc(this, reinterpret_cast<AptLoadScreenHandler>(&AptLoadScreen::GameLoadingType))));
	}
	m_mapPreview.rva0057E45C();

	m_layout = TheWindowManager->winCreateLayout(AsciiString("LoadScreen.apt"));
	m_layout->hide(false);
	GameWindow *win = m_layout->m_firstWindow;
	if (!win)
		return;
	m_win = win;
	m_level = AptPlayer::GetLevelIndex(win);
	TheAptPlayer->slot19(0);

	if (!TheSkirmishGameInfo && !TheGameSpyInfo)
	{
		UnicodeString blank(L" ");
		AsciiString key("GUI:Level");
		g_bfmeAptWindowManager->bfmeSetText(key, blank, false);
	}
	if (TheGameSpyGame && TheGameSpyGame->m_isRanked)
	{
		AsciiString key("GUI:Level");
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch("GUI:Rank"), false);
	}
	((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
}
