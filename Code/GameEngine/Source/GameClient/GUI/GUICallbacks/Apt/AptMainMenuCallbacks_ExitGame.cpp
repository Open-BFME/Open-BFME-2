// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
// Split from AptMainMenuCallbacks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// BFME2's main menu screen Apt callbacks, 0x00514A9B onward. The screen's
// registration binds each by the name it carries here ("AptMainMenu::
// LoadGame" ...) as a member pointer, which is the only reference to them,
// so the names are the binding strings' and the class is named for their
// prefix (BFME1 calls the screen BfmeAptScreenMainMenu). Most of them
// leave the menu: state +0x288 becomes 9 and +0x28C names the screen to
// open next.

extern "C" int __cdecl strcmp(const char *left, const char *right);

#include "unicode_string.h"

// TheGameState (VA 0x00DFF08C); its rowed 0x002DCCFB tells whether a save
// file exists (Rva002DC267Get.cpp's view).
class GameState;
extern GameState *TheGameState;

class Rva002DCCFB
{
public:
	bool rva002DCCFB(UnicodeString filename);
};

#include "ascii_string.h"

// The script event the exit button fires: the .data pointer at 0x009C108C to
// "ShellMainMenuExitPushed" (0x0081F154), defined here (no owner unit yet).
const char *g_009C108C = "ShellMainMenuExitPushed";

#include "../../../../../Include/GameLogic/ScriptEngine.h"

extern ScriptEngine *TheScriptEngine;

#include "Common/BfmeAudioEventPrefix136.h"

// TheAudio: vslot 35 stops the given audio kinds.
class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34();
	virtual void v35(int a, int b, int c);
};

extern AudioManager *TheAudio;

// TheAudio's misc audio (vslot 78) and addAudioEvent (vslot 25), as
// Rva00323E1CMethod.cpp's view; the credits event is the misc audio's
// +0xA4 reference and the sub-menu entry sound its +0x9C one.
struct AptMainMenuMiscAudio
{
	unsigned char m_pad00[0x9C];
	OpaqueRefElement4 m_9c; // +0x9C
	unsigned char m_padA0[0xA4 - 0xA0];
	OpaqueRefElement4 m_credits; // +0xA4
};

class AptMainMenuAudioView
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
	V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
	virtual AptMainMenuMiscAudio *getMiscAudio();
};

// The event's +0x49 flag is set through the rowed Weapon::setLeechRangeActive
// body it folds with (as Rva0043A278Slot2.cpp's Weapon-cast).
class Weapon
{
public:
	void setLeechRangeActive(bool value);
};

class Shell
{
public:
	// Rowed 0x0035BEC7; unrowed 0x0035BD5D (a byte query) and 0x0035C2B9,
	// pinned by address.
	void pop();
	bool rva0035BD5D();
	void rva0035C2B9();
	void rva0035BF4C(bool hide);	// rowed; Zero Hour's Shell::hide

	unsigned char m_pad00[0x5D];
	bool m_5d; // +0x5D
	unsigned char m_pad5E[0x6C - 0x5E];
	bool m_6c; // +0x6C, set when a campaign starts
};

// The shell's rowed 0x0035BD3F (its own address class).
class Rva0035BD3F
{
public:
	void rva0035BD3F();
};

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, bool immediate);
	void reverse(AsciiString groupName);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual void setBool(const AsciiString &key, bool value);
	virtual bool write();
};

// The options file (its destructor is rowed as ??1Rva002E4272, pinned
// here under this name).
class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

	unsigned char m_rest[0x14 - 0x04];
};

extern Shell *TheShell;

// TheGameEngine: vslot 20 (Zero Hour's setQuitting position moved).
class GameEngine
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(bool value);
};

extern GameEngine *TheGameEngine;

// TheGlobalData's +0x28 (the frame rate TheGameEngine vslot 18 takes back).
class GlobalData;
extern class GlobalData *TheWritableGlobalData;

// OpaqueScalarDeletingDtorsB12.cpp's g_Va00E048DC (the open resource
// holder).
extern int g_Va00E048DC;

struct AptMainMenuGlobalData
{
	unsigned char m_pad00[0x28];
	int m_28; // +0x28
	unsigned char m_pad2C[0x9AD - 0x2C];
	bool m_9ad; // +0x9AD
	unsigned char m_pad9AE[0xAF4 - 0x9AE];
	bool m_af4; // +0xAF4, cleared when the map roll starts or ends
};

class GameEngineRate
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual void v18(int value);
};

// The credits roll (0x00E06474): vslot 9 stops it; deleted through vslot 0
// and a separate operator delete.
class AptMainMenuCredits
{
public:
	virtual void *deleteInstance(int flags);
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09();
};


// The credits roll's class (0x48 bytes; Rva005B77F1Dtor.cpp's rowed
// constructor 0x005B776E).
class Rva005B77F1
{
public:
	Rva005B77F1();

private:
	unsigned char m_pad00[0x48];
};

// Zero Hour's GameMessage; appendIntegerArgument is rowed (0x0030F936).
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

// Zero Hour's TheMessageStream (VA 0x00E00950, the ledger's
// MessageStreamSubsystem); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);
};

extern class MessageStream *TheMessageStream;

// The game mode TheGameLogic (0x00DFE78C) keeps at +0x110.
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct AptMainMenuGameLogic
{
	unsigned char m_pad000[0x110];
	int m_mode; // +0x110
};

// The window the game runs in and the Win32 calls that size it.
struct HWND__
{
	int unused;
};

typedef HWND__ *HWND;

struct tagRECT
{
	long left;
	long top;
	long right;
	long bottom;
};

extern "C" __declspec(dllimport) int __stdcall GetClientRect(HWND window, tagRECT *rect);
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(HWND window, int index);
extern "C" __declspec(dllimport) int __stdcall AdjustWindowRect(tagRECT *rect, unsigned long style, int menu);
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(HWND window, HWND after, int x, int y, int width, int height, unsigned int flags);

// WinMain.cpp defines the window handle as a void * (?ApplicationHWnd@@3PAXA).
extern void *ApplicationHWnd;

// TheDisplay: windowed (vslot 21), width (16) and height (17).
class Display
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual int getWidth();
	virtual int getHeight();
	virtual void v18(); virtual void v19(); virtual void v20();
	virtual bool getWindowed();
	virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
	virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
	virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
	virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61();
	virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65();
	virtual bool playMovie(AsciiString name, int flags, int a, int b);	// slot 66
	virtual void v67(); virtual void v68();
	virtual bool rva_slot69();		// +0x114, consulted when a campaign is not started
	virtual void v70();
	virtual bool rva_slot71();		// +0x11C

	void rva002B2466(float a, float b, float c, float d);	// rowed

	unsigned char m_pad04[0x114 - 0x04];
	bool m_114;						// +0x114, set when a campaign starts
};

extern Display *TheDisplay;

// TheMouse's call here lands on the shared empty body 0x000B3FD0 (name
// unknown, pinned by address).
class Mouse
{
public:
	void rva000B3FD0();
	void _bfme_setEngineVisibility(bool visible);	// rowed 0x001EE5BE
};

extern Mouse *TheMouse;

// TheInGameUI's vslot 108 refreshes the layout after a resolution change.
class InGameUI
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	V(90) V(91) V(92) V(93) V(94) V(95) V(96) V(97) V(98) V(99)
	V(100) V(101) V(102) V(103) V(104) V(105) V(106) V(107)
#undef V
	virtual void v108();
};

extern InGameUI *TheInGameUI;

// Unrowed 0x0041267F (10 bytes: two calls), pinned by address.
void Rva0041267F();

class AptMainMenu
{
public:
	void OnTutorial(const char *params);
	void LoadGame(const char *unused);
	void Options(const char *value);
	void Credits(const char *unused);
	void GoodCampaign(const char *value);
	void EvilCampaign(const char *value);
	void CreateAHero(const char *unused);
	void WarOfTheRing(const char *unused);
	void LoadCampaign(const char *unused);
	void Skirmish(const char *unused);
	void LoadReplay(const char *unused);
	void StopGameMovie(const char *unused);
	void ContinueCampaign(const char *unused);
	void OnInitialized(const char *unused);
	void ExitGame(const char *unused);
	void BattleSchool(const char *unused);
	void CreditsExit(const char *unused);

	void ResetResolution(const char *unused);

	static int LinearCampaignStart(const AsciiString &campaign, float time, bool start);

	// Bound without a name by the LAN and online openers (0x00515C64,
	// 0x005160DE) and the tutorial prompt (0x00515980); they keep their
	// addresses.
	void rva00514B8D();
	void rva00514BA1();
	void rva00514BB5();
	void rva00514DC0(int button);
	virtual int rva00514950(int msg, int p1, int p2);
	void rva00514F2E();
	void rva00514FE9();
	void rva00515980();
	void rva005158A7();
	// 0x00515633 (rowed as the free Rva00515633Delete; it ignores ECX but
	// is called with the menu in it), pinned under this name.
	void rva00515633();

private:
	unsigned char m_pad04[0x274 - 4];
	void *m_274; // +0x274, the screen's Apt movie level
	unsigned char m_pad278[0x27C - 0x278];
	bool m_initialized; // +0x27C
	bool m_pendingRestart; // +0x27D
	bool m_restart; // +0x27E
	bool m_27f;
	bool m_280;
	bool m_tutorialPending; // +0x281
	bool m_282; // +0x282
	unsigned char m_pad283[0x288 - 0x283];
	int m_state; // +0x288
	int m_next; // +0x28C
	unsigned char m_pad290[0x2A4 - 0x290];
	AsciiString m_2a4; // +0x2A4
	char m_side; // +0x2A8
};












// Retail 0x00514E76, 42 bytes: "AptMainMenu::OnInitialized".
void AptMainMenu::OnInitialized(const char *unused)
{
	ResetResolution(0);
	m_initialized = true;
	if (m_pendingRestart)
	{
		m_restart = true;
		m_pendingRestart = false;
	}
}

// Retail 0x005152E7, 114 bytes: "AptMainMenu::ExitGame" fires the
// "ShellMainMenuExitPushed" script event, stops audio, runs the shell's
// 0x0035BEC7 and sets TheGameEngine's vslot 20.
void AptMainMenu::ExitGame(const char *unused)
{
	{
		AsciiString name(g_009C108C);
		TheScriptEngine->rva00357DD2(name);
	}
	TheAudio->v35(2, 1, 0);
	TheShell->pop();
	TheGameEngine->v20(true);
}



// Retail 0x005158A7, 27 bytes. Name unknown: picks the credits menu
// (+0x2A4 = "CreditsMenu") and runs 0x00515633; the time line's continue
// 0x0051ED7E calls it on the main menu.
void AptMainMenu::rva005158A7()
{
	m_2a4 = "CreditsMenu";
	rva00515633();
}








// Retail 0x00514C15, 214 bytes: "AptMainMenu::ResetResolution" resizes a
// windowed game's window to the display's resolution when they differ.
void AptMainMenu::ResetResolution(const char *unused)
{
	if (!TheDisplay->getWindowed())
		return;
	int width = TheDisplay->getWidth();
	int height = TheDisplay->getHeight();
	tagRECT rect = {0};
	GetClientRect((HWND)ApplicationHWnd, &rect);
	if (rect.right - rect.left != width || rect.bottom - rect.top != height)
	{
		rect.left = 0;
		rect.top = 0;
		rect.right = width;
		rect.bottom = height;
		unsigned long style = GetWindowLongA((HWND)ApplicationHWnd, -16);
		AdjustWindowRect(&rect, style, 0);
		SetWindowPos((HWND)ApplicationHWnd, 0, 0, 0, rect.right - rect.left, rect.bottom - rect.top, 6);
		TheMouse->rva000B3FD0();
		Rva0041267F();
		TheInGameUI->v108();
	}
}

// AptMainMenu::LinearCampaignStart, retail 0x00514D05..0x00514DC0 (187 bytes,
// cdecl static). WorldBuilder names it in AptMainMenu.cpp and asserts
// "Cannot find campaign '...' to start. Ignoring" on a failed lookup. Without
// start it answers 1, or 3 when TheDisplay's slot 69 says no. With start the
// Apt focus and background are dropped, the shell hidden and flagged (+0x6C),
// TheDisplay's +0x114 set, video stopped (TheVideoPlayer slot 28), the logic
// cleared (GameLogic 0x00376E92) and, for a campaign TheLinearCampaignManager
// knows, a message 0x20 carries its index and the global at 0x00DD1538.
// Callers 0x0051590C/0x0051596B pass the float second argument; it is unused.
class AptFocusTarget;
class AptPlayer
{
public:
	void PopFocus(AptFocusTarget *target);	// 0x00222A33
};
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);	// rowed 0x00222A8B
	void rva00222F55(bool show);			// 0x00222F55, AptPlayer::HideBackground
};

class VideoPlayerInterface
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27)
#undef V
	virtual void stopAllVideo();			// slot 28
};
extern VideoPlayerInterface *TheVideoPlayer;

class Rva001EB8D7
{
public:
	int rva001EB8D7(const StringBase<char> &name);	// campaign index, -1 if unknown
};
class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;

extern int g_Va00DD1538;



extern "C" int __cdecl abs(int value);


// Native515359..515633 complete730B RET4; WB1459300 and the rowed
// main-menu constructor bind AptMainMenu::OnTutorial independently.
// Strategic selects WOTRTutorial through the rowed campaign lookup.
// Basic/Advanced select native36B records1114/1138; selected pointer115C.
// Map/sound uses are proved by the retained string and slot75 audio APIs.
// Fields4/8/20 and the DF EF18 slot10 receiver remain target-only views;
// neither original field names nor that receiver's class identity are known.
// BFME1 10b888 main-menu callbacks provide subsystem/API context only;
// this BFME2-specific callback is reconstructed from retail and WB evidence.
class LivingWorldCampaignManager {public:int rva003B8F20();};
class Rva00E02D6C;extern Rva00E02D6C *TheCampaignManager;
class LivingWorldManager {public:void rva0021427A();};
extern LivingWorldManager *TheLivingWorldManager;
class Rva002D3627Host;class LivingWorld; extern LivingWorld *TheLivingWorld;
class TutorialControlView {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
 virtual void slot10(int);
};
class TutorialShellView {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
#undef V
 virtual void slot10();
};
class AudioEventInfoRef {public:
 AudioEventInfoRef(){value.referent=0;}
 ~AudioEventInfoRef(){if(value.referent)value.referent->Release_Ref();}
 AudioEventInfoRef &operator=(const AudioEventInfoRef &other){value=other.value;return *this;}
 private:OpaqueRefElement4 value;
};
class TutorialAudioView {public:
#define V(n) virtual void pad##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
 V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
 V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
 V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
 V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
 V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
 V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
 V(70) V(71) V(72) V(73) V(74)
#undef V
 virtual AudioEventInfoRef findInfo(const AsciiString &);
};
struct TutorialConfig {AsciiString mapName,field4,field8,soundC,sound10;char unknown14[12];int field20;};
struct TutorialGlobalView {
 char unknown0[0xAC0];AsciiString mapAC0;
 char unknownAC4[0x1114-0xAC4];TutorialConfig basic,advanced;
 TutorialConfig *selected;
};
class Rva0023DC8E {public:void rva0023DC8E(const AsciiString &);};
class Rva0023DCCE {public:void rva0023DCCE(const AsciiString &,const OpaqueRefElement4 &,const OpaqueRefElement4 &);};
struct TutorialLogicView {char unknown0[0x90];int field90;};


// Retail 0x00515980..0x00515B0A (394 bytes, RET0; EH). Name unknown: the
// screen's leave/shutdown step (WB 1457450 is its unnamed debug twin).
// TheGameInfo is dropped and TheSkirmishGameInfo deleted; unless the menu
// is leaving for "CreditsMenu" it backs out of the sub-menu (0x00514FE9) or
// reverses the parchment fade, clears/sets the shell's +0x5D/+0x6C bytes and,
// in state 8, asks for display-mode confirmation: a two-button message box
// whose callbacks are 0x00514DC0 (records button 2) and 0x00514DDA, then
// the 10-second timer 0x00437EC4 and the engine mouse shown again.
class GameInfo
{
public:
	virtual ~GameInfo();
};
extern GameInfo *TheGameInfo;
// Defined as a SkirmishGameInfo * in SkirmishGameOptionsMenu.cpp.
class GameInfo; class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;

// TheGameText's vslot 15 fetch (Rva00515C64's view).
class GameTextInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);	// +0x3C
};
extern GameTextInterface *TheGameText;

// The Apt callback functors (as Rva0043F483PopulatePlayerCombo.cpp): a
// binding of an object and an eight-byte member pointer (code pointer and
// this-adjustment; both callbacks here are plain members, adjustment 0), the
// refcounted holder rowed 0x0057BC63 builds from it, and AptMessageBox.cpp's
// by-value reference the box releases through 0x0007DEEF.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding
{
	template <class T, class M> FunctorBinding(T *target, M method)
		: m_target(reinterpret_cast<FunctorTarget *>(target)), m_method(reinterpret_cast<FunctorMethod>(method)) {}
	FunctorTarget *m_target;
	unsigned int m_pad;
	FunctorMethod m_method;
};
// The generic member pointer is the eight-byte multiple-inheritance form; a
// plain member converts to it through a derived class of that form.
struct TargetRef00217D4C { virtual void *destroy(unsigned int); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount(0) {}
	virtual void anchor();
	int m_refCount; // +0x04
};
class Rva0057BC63FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
	void invoke();
	FunctorBinding m_binding;
};
void *__cdecl operator new(unsigned int size);
// The holder constructor (row 0x0057BC63) is defined here inline (never
// inlined), as AptOptionsConstructor.cpp does: retail's compiler saw that it
// only reads its binding, so both callback bindings below share one slot
// pair ([ebp-0x2c]/[ebp-0x3c]). Declared out of line, the second binding's
// copy takes its own slot and the frame grows from 0x30 to 0x40.
class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding)
	{
		m_ptr = (TargetRef00217D4C *)new Rva0057BC63FunctorWrapper(binding);
		if (m_ptr != 0)
			m_ptr->references++;
	}
	TargetRef00217D4C *m_ptr;
};
struct TreeHintRef00217D4C : public Rva0057BC63FunctorHolder
{
	TreeHintRef00217D4C(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &v) : Rva0057BC63FunctorHolder(v)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~TreeHintRef00217D4C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class AptMessageBox
{
public:
	static void Show(int type, const UnicodeString &text, const UnicodeString &title, TreeHintRef00217D4C callback, TreeHintRef00217D4C callback2);
};
class Rva00514DDA
{
public:
	void rva00514DDA(int button);
private:
	int m_unknown00;
};
void __cdecl Rva00437EC4Set(float seconds);
// The generic member pointer is the eight-byte multiple-inheritance form; a
// plain member converts to it through a derived class of that form.
struct AptMainMenuWide : public AptMainMenu, public FunctorBinding {};
struct Rva00514DDAWide : public Rva00514DDA, public FunctorBinding {};

void AptMainMenu::rva00515980()
{
	TheGameInfo = 0;
	if (((GameInfo *)TheSkirmishGameInfo))
	{
		::delete ((GameInfo *)TheSkirmishGameInfo);
		(*(GameInfo **)&TheSkirmishGameInfo) = 0;
	}
	if (m_2a4.compare("CreditsMenu") != 0)
	{
		if (m_27f)
			rva00514FE9();
		else if (m_280)
			TheTransitionHandler->reverse(AsciiString("PreParchmentMapFade_StartNew"));
		TheShell->m_5d = false;
		TheShell->m_6c = true;
		if (m_state == 8)
		{
			m_282 = false;
			AptMessageBox::Show(2, TheGameText->fetch("GUI:ValidateDisplayModeTitle"), TheGameText->fetch("GUI:ValidateDisplayModeMessage"),
				TreeHintRef00217D4C(FunctorBinding(this, static_cast<void (AptMainMenuWide::*)(int)>(&AptMainMenu::rva00514DC0))),
				TreeHintRef00217D4C(FunctorBinding(this, static_cast<void (Rva00514DDAWide::*)(int)>(&Rva00514DDA::rva00514DDA))));
			Rva00437EC4Set(10.0f);
			TheMouse->_bfme_setEngineVisibility(true);
		}
	}
}
