// ?rva00521CFF@AptSkirmish@@QAEXXZ
// partial score=0.8 date=2026-10-08
// ?rva00521CFF@AptSkirmish@@QAEXXZ
// partial score=0.8 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's skirmish screen Apt callbacks, 0x00521741 onward, bound by these
// names ("AptSkirmish::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x6B8 is the screen's state, +0x6D0
// its profile name entry, +0x698 its SkirmishPreferences (whose user name
// list the profile callbacks walk; STLport and /EHsc are for them).

#include "unicode_string.h"
#include "ascii_string.h"

#include <list>

// Retail's string comparisons register no unwind state for their
// temporaries: StringBase<unsigned short>'s compare and compareNoCase are
// taken not to throw (as the throw() view in stlport_sort_mapmetadata.cpp).
template <> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &str) const throw();
template <> int StringBase<unsigned short>::compareNoCase(const StringBase<unsigned short> &str) const throw();

// The user name list's base destructor is the rowed out-of-line 0x00433BD7.
extern template _STL::_List_base<UnicodeString, _STL::allocator<UnicodeString> >::~_List_base();

class GameWindow;

class GameWindowManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48)
#undef V
	virtual int winSetFocus(GameWindow *window) = 0;
};

extern GameWindowManager *TheWindowManager;

void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void GadgetListBoxGetSelected(GameWindow *listBox, int *selectIndex);
UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);
void GadgetListBoxSetSelected(GameWindow *listBox, int selectIndex);
void GadgetListBoxReset(GameWindow *listBox);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text, int color, int row, int column, bool overwrite);

extern "C" int __cdecl strcmp(const char *left, const char *right);

class BfmeKeyLC;
class BfmeObjENK;
void bfmeGo924F(BfmeKeyLC *textEntry, unsigned short maxLength);
void bfmeGoENK(BfmeObjENK *listBox, char flag);

// The name entry link at +0x6C8 (as the LAN lobby's +0x6AC one): vslot 1
// attaches the window, kept at its +0x08.
class AptSkirmishEntryLink
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);

	void *m_04;
	GameWindow *m_window; // +0x08
};

// The skirmish screen instance (Rva0052192DInit.cpp's g_00E04930).
extern int g_00E04930;

class AptPlayer;
extern class AptPlayer *TheAptPlayer;

// MpGameSetupSlots.cpp's 0x0043DB23 runs an Apt function on a movie.
void Rva0043DB23(AptPlayer *target, void *owner, const char *name);

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

class AptSkirmish
{
public:
	void OnInitialized(const char *unused);
	// Bound under both "AptSkirmish::Back" and "AptSkirmish::Exit" (one
	// body or two folded), so it keeps its address.
	void rva0052174E(const char *unused);
	void StartGame(const char *unused);
	void OnStatsMenu(const char *unused);
	void rva00521770(const char *unused);
	void OnExitStatsScreen(const char *unused);
	void OnClosed(const char *unused);
	void OnNewProfileMenu(const char *unused);
	void OnDeleteProfileMenu(const char *unused);
	void OnChangeProfileMenu(const char *unused);
	void InitGadgets(const char *name, void *argument, GameWindow *window);
	UnicodeString rva00522697();
	void OnChangeProfile(const char *unused);
	void OnDeleteProfile(const char *unused);
	void OnAddProfileAccept(const char *unused);

	// Unrowed 0x00521CFF (358 bytes), pinned by address; 0x00522556 is
	// defined below.
	void rva00521CFF();
	void rva00522556();

private:
	unsigned char m_pad000[0x274];
	void *m_274; // +0x274, the screen's Apt movie
	unsigned char m_pad278[0x304 - 0x278];
	int m_304; // +0x304
	unsigned char m_pad308[0x6B8 - 0x308];
	int m_state; // +0x6B8
	unsigned char m_pad6bc[0x6C1 - 0x6BC];
	bool m_6c1; // +0x6C1
	bool m_6c2; // +0x6C2
	unsigned char m_pad6c3[0x6C4 - 0x6C3];
	GameWindow *m_profiles; // +0x6C4
	AptSkirmishEntryLink m_nameEntry; // +0x6C8 (the window at +0x6D0)
};

// Retail 0x00521643, 21 bytes. Name unknown. With the skirmish screen up,
// the Apt window manager's 0x00222479 (as Rva00433D27Enable and its twins).
void Rva00521643Enable()
{
	if (g_00E04930 == 0)
		return;
	((Rva00222479ByteOneSetter *)TheAptPlayer)->enable();
}

// Retail 0x00521741, 13 bytes: "AptSkirmish::OnInitialized".
void AptSkirmish::OnInitialized(const char *unused)
{
	m_state = 1;
}

// Retail 0x0052174E, 8 bytes: bound as "AptSkirmish::Back" and
// "AptSkirmish::Exit".
void AptSkirmish::rva0052174E(const char *unused)
{
	Rva00521643Enable();
}

// Retail 0x00521756, 13 bytes: "AptSkirmish::StartGame".
void AptSkirmish::StartGame(const char *unused)
{
	m_state = 10;
}

class SkirmishPreferences
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3slotC();
	bool Rva0043B9E8();
	_STL::list<UnicodeString> getUserNames_Rva0043C2D0();
	UnicodeString Rva0043B9F5();
	UnicodeString Rva0043BB88();
	void Rva0043C2EB(const UnicodeString &name);
	int Rva0043BBB6(UnicodeString name);
	void rva0043C612(const UnicodeString &name);
	void setCurrentUserName(const UnicodeString &name);
	// Unrowed 0x0043BE7C, pinned by address.
	void rva0043BE7C();
};

// The screen's member at +0x668; its unrowed 0x005C1ABA takes the current
// user name, pinned by address.
class Rva005C1ABA
{
public:
	void rva005C1ABA(const UnicodeString &name);
};
// TheSkirmishGameInfo: slot 11 sits where Zero Hour's GameInfo has
// startGame; the seed at +0x50 and the +0x58 value go to the new game.
class GameInfo
{
public:
	virtual void *v0slot0(int v);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void startGame(int gameID);

	AsciiString getMap() const;

	unsigned char m_pad004[0x50 - 0x4];
	unsigned int m_seed; // +0x50
	unsigned char m_pad054[0x58 - 0x54];
	int m_58; // +0x58
};
extern GameInfo *TheSkirmishGameInfo;
extern int g_Va00E0333C;
void __cdecl operator delete(void *p);
class Panel00E0333C
{
public:
	virtual void p0();
	virtual void p1slot4();
};
void Rva00521643Enable();

// TheGameLogic; its unrowed 0x00376E92 is pinned by address.
class GameLogic
{
public:
	void rva00376E92(int a, int b);
};

extern GameLogic *TheGameLogic;

// TheWritableGlobalData: the map name at +0x0C.
class GlobalData
{
public:
	unsigned char m_pad00[0xC];
	AsciiString m_mapName; // +0x0C
};

extern GlobalData *TheWritableGlobalData;

void InitGameLogicRandom(unsigned int seed);

// The Apt window manager's rowed 0x00222F55 and unrowed 0x00222A33 (pinned).
class AptPlayer
{
public:
	void PopFocus(class AptFocusTarget *value);
	
};

class Rva00222A8BTarget { public: void rva00222F55(bool); };
class Shell
{
public:
	void rva0035BF4C(bool value);
};

extern Shell *TheShell;

class Display
{
public:
	unsigned char m_pad000[0x114];
	bool m_114; // +0x114
};

extern Display *TheDisplay;

class VideoPlayerInterface
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27)
#undef V
	virtual void v28() = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

// The object at 0x00DFEF18 (Rva003BCC94Do.cpp's view): slot 10 with 1.
class Rva002D3627Host
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9)
#undef V
	virtual void slot10(int value) = 0;
};

extern Rva002D3627Host *g_00DFEF18;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

// Zero Hour's TheMessageStream (the ledger's TheMessageStream at
// 0x00E00950): appendMessage is slot 18.
class MessageStream
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17)
#undef V
	virtual GameMessage *appendMessage(int type) = 0;
};

extern MessageStream *TheMessageStream;

class MapMetaData
{
public:
	unsigned char m_pad00[0x24];
	bool m_24; // +0x24
};

class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

extern MapCache *TheMapCache;

// Retail 0x00521CFF, 358 bytes: starts the skirmish game on the chosen
// map: a new-game message (0x1F) when the screen's +0x304 mode is 1,
// else a 0x1E message whose first argument is 2 for maps flagged at
// +0x24 (and for maps the cache does not know).
void AptSkirmish::rva00521CFF()
{
	TheGameLogic->rva00376E92(0, 0);
	TheWritableGlobalData->m_mapName = TheSkirmishGameInfo->getMap();
	TheSkirmishGameInfo->startGame(0);
	InitGameLogicRandom(TheSkirmishGameInfo->m_seed);
	AptSkirmish *screen = (AptSkirmish *)g_00E04930;
	if (!screen)
		return;
	if (screen->m_304 == 1)
	{
		TheAptPlayer->PopFocus((AptFocusTarget*)-1);
		((Rva00222A8BTarget*)TheAptPlayer)->rva00222F55(false);
		TheShell->rva0035BF4C(true);
		TheDisplay->m_114 = true;
		TheVideoPlayer->v28();
		TheGameLogic->rva00376E92(0, 0);
		g_00DFEF18->slot10(1);
		GameMessage *msg = TheMessageStream->appendMessage(0x1F);
		if (msg)
		{
			msg->appendIntegerArgument(TheSkirmishGameInfo->m_58);
			msg->appendIntegerArgument(0);
		}
	}
	else
	{
		bool flagged = true;
		const MapMetaData *map = TheMapCache->findMap(TheSkirmishGameInfo->getMap());
		if (map)
			flagged = map->m_24;
		GameMessage *msg = TheMessageStream->appendMessage(0x1E);
		msg->appendIntegerArgument(flagged ? 2 : 0);
		msg->appendIntegerArgument(1);
		msg->appendIntegerArgument(0);
	}
}
