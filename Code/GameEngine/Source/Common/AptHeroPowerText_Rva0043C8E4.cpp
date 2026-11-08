// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// stlport
// platformsdk
// Ticker and spell-button display functions; the GameSpy response pump is
// isolated in AptTickerGameSpyUpdate.cpp until its shared handler is matched.
// Hero power panel texts. Each builds a UnicodeString through a formatter
// and hands it to the rowed bfmeSetText. Both formatters return a
// UnicodeString by value through a hidden pointer; 0x005B2376 and
// 0x005B2446 are defined below.
//
// ?Rva005B23D7HeroPowersDescription@@YAXPAXABVAsciiString@@1@Z @0x005B23D7 111B
//   APT:HeroPowersDescription with the description text
// ?Rva005B24CDHeroPowerText@@YAXPAXPBDH@Z                      @0x005B24CD 114B
//   APT:%s_%d keyed by the prefix and the 1-based index
// Names are address-derived; the keys are the retail strings.
#include <windows.h>

#include <stdio.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheRva00222A8BTarget ((Rva00222A8BTarget *)g_bfmeAptWindowManager)

UnicodeString __cdecl Rva005B2376Describe(void *power, const AsciiString &unused, const AsciiString &fallback);
UnicodeString __cdecl Rva005B2446Describe(void *power);



// ?rva005B2295@@YA_NPBVCommandButton@@PBDHH@Z @0x005B2295 225B: points the
// Apt image key "%s_%d" (or "%s_%d_%d" for a page >= 0; both 1-based) at the
// button's image, falling back to CircleRed_42x42, and returns whether the
// key changed; with no button the key is cleared. Callers: the level labeller
// AptMyHero::rva005B0416 and the AptCreateAHero power panel. WorldBuilder's
// twin 0x0157F330 is unnamed; the name is address-derived.
#include "../../Include/GameClient/Image.h"
// ?rva005B9378@Rva005B9378@@QAEXHABVUnicodeString@@@Z @0x005B9378 178B: one
// ticker row. The field text is the game-text label for the row's entry in
// the label table at VA 0x00DD3B90, fetched through TheGameText's
// fetch(const char *, bool *) (slot 0x3C), with L":" appended. It is set under
// APT:TickerField_%d, then the caller's value under APT:TickerValue_%d. Callers
// (0x005B945D and four more) pass this in ecx, which the body never reads.
#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;


// Six ticker labels precede the separate SIDE label table at VA DD3BA8.
const char *g_00DD3B90[6] = {
    "APT:Date", "APT:Time", "APT:1v1RankLabel", "APT:2v2RankLabel",
    "APT:PlayersOnline", "APT:GamesInProgress"
};
extern const unsigned short g_Va007C9260[];

class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
	void rva005B942A(int index, int value);
	void rva005BA02B();
};

void Rva005B9378::rva005B9378(int index, const UnicodeString &value)
{
	AsciiString key;
	key.format("APT:TickerField_%d", index);
	UnicodeString fieldText = TheGameText->fetch(g_00DD3B90[index], 0);
	fieldText.concat(L":");
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, fieldText, false);
	key.format("APT:TickerValue_%d", index);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
}

// ?rva005B942A@Rva005B9378@@QAEXHH@Z @0x005B942A 83B: one ticker numeric row.
// Formats the integer value with L"%d" (g_Va007C9260) into a UnicodeString
// temp, then hands it to rva005B9378 under the same index. Callers
// (0x005B9591 with index 2 and 0x005B95A4 with index 3, plus 0x005BA0CB/E3)
// pass this in ecx, which both bodies forward untouched.
void Rva005B9378::rva005B942A(int index, int value)
{
	UnicodeString text;
	text.format(g_Va007C9260, value);
	rva005B9378(index, text);
}

// ?rva00513497@Rva00513497@@QAEXHVUnicodeString@@@Z @0x00513497 193B: the
// disconnect screen's player name. It is set under
// DisconnectScreen::PlayerName%d, or L" " when the name is null or empty
// (inline length test at +4). The slot then goes through the rowed bar update
// 0x00513040 with 0 or, for a real name, the rowed 0x00512CE9 (false) and the
// bar update with 100. 0x00512CE9 is AptDisconnectScreen's; the bar update
// keeps an address-named view of this same object.
class AptDisconnectScreen
{
public:
	void rva00512CE9(int slot, bool b);
};

// StringBase<unsigned short>::isEmpty, inline here as retail expands it.
static inline bool Rva00513497IsEmpty(const UnicodeString &unicodeString)
{
	const char *data = *(const char *const *)&unicodeString;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

class Rva00513497
{
public:
	void rva00513497(int slot, UnicodeString name);
};


// ?rva0057F538@Rva0057F538@@QAEXVUnicodeString@@@Z @0x0057F538 181B: the clan
// error text. An unchanged message is skipped. Otherwise it runs the Apt
// ResetClanErrorMessage callback on the owner (virtual slot 2) through the
// rowed Rva0043DB23, keeps the message at +0xB0, and sets CLAN:Error to it
// (L" " when empty).
int Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);

class Rva0057F538
{
public:
	virtual void v00();
	virtual void v04();
	virtual void *v08();
	void rva0057F538(UnicodeString message);
private:
	char m_pad04[0xAC];
	UnicodeString m_error;		// +0xB0
};


// ?rva0051C2E2@Rva0051C2E2@@QAEXPAHABVAsciiString@@H@Z @0x0051C2E2 201B: one
// score-screen region bonus row, APT:ScoreRegionBonus%d keyed by the running
// row counter. A positive bonus formats the label's game-text format string
// (TheGameText slot 0x40, as in Rva0052906BUpdate.cpp) with it. A negative
// bonus sets L" ". Either way the counter advances. A zero bonus sets
// nothing. Callers pass this in ecx, which the body never reads.
class Rva0051C2E2
{
public:
	void rva0051C2E2(int *row, const AsciiString &label, int bonus);
};


// ?ProcessProgress@AptFileTransferPopup@@QAEXHHVUnicodeString@@@Z @0x00583121 225B: one
// file-transfer row. For a valid player (0..7) whose Apt slot at +0x5C is
// assigned (-1 means none), it sets FileTransfer::Status%d to the text, then
// calls SetBarTo with the slot and the percentage as "%d" strings through
// the rowed Rva00222A8BTarget::invoke (owner 13, two arguments).

class AptFileTransferPopup
{
public:
	void ProcessProgress(int player, int percent, UnicodeString text);
private:
	char m_pad00[0x5C];
	int m_slots[8];				// +0x5C
};


// ?rva0057C7BA@Rva0057E3DB@@QAEXH@Z @0x0057C7BA 216B: the lobby map title
// (the existing pin's class, the AptMpGameSetup panel's +0x60 member). It keeps
// the game type at +0x1C and sets APT:LobbyMapTiltle (the retail spelling)
// to that label's own game text for type 0 and GUI:GameTypeScenario for
// type 1.
class Rva0057E3DB
{
public:
	void rva0057C7BA(int type);
private:
	char m_pad00[0x1C];
	int m_type;					// +0x1C
};


// ?rva0043C8E4@AptSpellStore@@QAEXHH@Z @0x0043C8E4 79B: one spell button's
// state. SetSpellButtonState receives the 1-based button number as "%d" and
// the state's name from the table at VA 0x00C3D700. It goes through the
// rowed invoke on the owner the rowed Rva00222547Get resolves for this
// window. The number buffer reuses the index parameter's slot, as in retail.
class GameWindow;
#include "../../../Libraries/Source/Apt/AptPlayerClass.h"
// Retail spell-button state names, VA C3D700 through C3D717.
const char *g_00C3D700[6] = {
    "_unused", "_disabled", "_disabled_level", "_already_purchased",
    "_purchased", "_active"
};

#include "../../Include/GameClient/AptSpellStore.h"

void AptSpellStore::rva0043C8E4(int index, int state)
{
	char buttonNumberText[4];
	sprintf(buttonNumberText, "%d", index + 1);
	TheRva00222A8BTarget->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "SetSpellButtonState", 2, buttonNumberText, (void *)g_00C3D700[state], 0, 0, 0);
}

// ??1Rva00582FC1@@UAE@XZ @0x00582FC1 84B (the existing pin's name): the file
// transfer popup's destructor. It closes the popup through the rowed invoke
// (owner 13, FileTransferPopUpClose, no arguments), clears the instance
// global at VA 0x00E06398, then the rowed base destructor 0x005248D0 runs.
#include "../../Include/GameClient/Rva005248D0.h"

class Rva00582FC1 : public Rva005248D0
{
public:
	virtual ~Rva00582FC1();
};

// The ledger's name for VA 0x00E06398 (ColdGlobalDwordGetters.cpp).
extern int g_Va00E06398;


// ?processProgress@AptLoadScreen@@UAEXHH@Z @0x0043A15D 99B: SetBarTo on the panel's
// Apt owner (+0x8C) with the slot's id from the table at +0xB0 and the
// percentage, both formatted by sprintf "%d".
#include "../../Include/GameClient/AptLoadScreen.h"

