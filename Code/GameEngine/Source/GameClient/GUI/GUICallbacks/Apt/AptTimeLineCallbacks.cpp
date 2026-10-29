// cl: /ICode/GameEngine/Include /ICode/GameEngine/Source/Common /Ireference/shims/bfme2_ascii /O1 /GF- /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME2's time line (post-game graph) screen Apt callbacks
// "AptTimeLine::OnButtonContinue", 0x0051F6D7, and 0x0051E3C3, bound by
// those names as member pointers by the screen's registration; that binding
// is their only reference. The class is named for the strings' prefix.
// The per-player variables ("TimeLine:PlayerColor:%d" ...) are bound in a
// loop of the same registration (0x0051FEF5-0x0051FFC1).

// The callbacks call atoi and sprintf through their imports, as <stdlib.h>
// and <stdio.h> declare them with _CRTIMP; /D_CRTIMP= keeps the CRT headers
// included after these direct (_mbscpy goes through its thunk).
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <stdlib.h>
#include <stdio.h>
#undef _CRTIMP
#define _CRTIMP
#include <mbstring.h>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "GameLogicObjectLookupView.h"

// An award (0x40 bytes): its name and description labels and image name.
struct BfmePod40
{
	unsigned char m_pad00[0x10];
	AsciiString m_name; // +0x10
	AsciiString m_description; // +0x14
	AsciiString m_image; // +0x18
	unsigned char m_pad1c[0x40 - 0x1C];
};

// The award store (0x00E02F74) and its rowed lookup by id 0x0040AAD5.
class Rva0040AAD5
{
public:
	struct BfmePod40 *rva0040AAD5(int key);
};

extern class Rva0040AAD5 *TheAwardSystemManager;

// The ids of the awards earned this game (0x00E04920).
// Use the ledger owner for the twelve-byte award vector at VA 0x00E04920.
extern unsigned int g_Va00E04920;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

// The screen's Apt image table at +0x258 and its rowed setter 0x00524725.
class Rva00524306
{
public:
	void rva00524725(const AsciiString &key, const Image *image);
 void rva00524767(const AsciiString &key,const AsciiString &image);
};

// One player's row of the time line (0x50 bytes): the color at +0x08 and
// the faction name at +0x0C (read by the banked PlayerFaction 0x0051EC4E);
// the rest is not read here.
struct AptTimeLinePlayer
{
	unsigned char m_pad00[4];
	UnicodeString m_name; // +0x04
	int m_color; // +0x08
	AsciiString m_faction; // +0x0C
	unsigned char m_pad10[0x50 - 0x10];
};

// AptSaveLoad_OpenScreen.cpp's 0x00434160 and Rva00433D3CClear.cpp's 0x00433D3C.
class AptSaveLoad
{
public:
	static void OpenScreen(int a, int b, bool c);
};
void Rva00433D3CClear();

// TheAudio: vslot 35 stops the given audio kinds, vslot 25 plays an
// event and vslot 78 answers the misc audio (the continue click is its
// +0x9C reference), as AptMainMenuCallbacks.cpp's view.
struct AptTimeLineMiscAudio
{
	unsigned char m_pad00[0x94];
	OpaqueRefElement4 m_open; // +0x94, the sound OpenScreen plays
	unsigned char m_pad98[0x9C - 0x98];
	OpaqueRefElement4 m_continue; // +0x9C
};

class AptTimeLineAudioView
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *event);
	V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34)
	virtual void stopAudio(int a, int b, int c);
	V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
	virtual AptTimeLineMiscAudio *getMiscAudio();
};

class AudioManager;
extern AudioManager *TheAudio;

// The event's +0x49 flag is set through the rowed Weapon::setLeechRangeActive
// body it folds with (as Rva0043A278Slot2.cpp's Weapon-cast).
class Weapon
{
public:
	void setLeechRangeActive(bool value);
};

// The score screen the time line belongs to (0x00E0491C); its +0x284 says
// how the game ended.
struct AptTimeLineScoreScreen
{
	unsigned char m_pad000[0x284];
	int m_mode; // +0x284
};

class Rva005202C8 { public: static Rva005202C8 *s_instance; };

// TheLivingWorldLogic (0x00DFEF10): the pinned 0x002B3740 and rowed
// 0x002B3753 queries.
class Rva002E2903Player;
class LivingWorldPlayer;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *GetPlayerAtIndex(int);
	char m_pad00[0x8C];
	_STL::vector<LivingWorldPlayer*> m_players; // +0x8C
};

class Rva002B3753
{
public:
	int rva002B3753();
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// The main menu (OpaqueScalarDeletingDtorsB12.cpp's g_Va00E048DC); its
// verified 0x005158A7 picks the credits menu.
class AptMainMenu
{
public:
	void rva005158A7();
};

extern int g_Va00E048DC;

extern GameLogic *TheGameLogic;

// TheShell (the ledger's g_Va00A01E48): +0x54.
struct AptTimeLineShell
{
	unsigned char m_pad00[0x54];
	bool m_54; // +0x54
};

class Shell;
extern Shell *TheShell;

class Rva00222479ByteOneSetter
{
public:
	void enable();
};

class Rva00222A8BTarget
{
public:
	void rva002233A6(int);
};



class Mouse
{
private:
	void commitPendingCursor();
    friend class AptTimeLine;
};

extern Mouse *TheMouse;

// A counted callback holder (Rva00080221Ctor.cpp's view); the verified
// 0x003FE7E6 registers one and answers its id through the pointer, and
// 0x003FEC05 is the callback registered here (both pinned by address).
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva00211E75
{
public:
	Rva00211E75(const int *arg);
    Rva00211E75(const Rva00211E75 &other) : m_impl(other.m_impl) { if(m_impl) ++m_impl->references; }
    // Keep inline cleanup; GameEngineControl.cpp owns the external destructor.
    __declspec(dllimport) __forceinline ~Rva00211E75() { if(m_impl) ReleaseTreeHintRef00217D4C(m_impl); }

private:
	TargetRef00217D4C *m_impl;
};

class Rva00211E75Callback : public Rva00211E75 { public: Rva00211E75Callback(const int*p) : Rva00211E75(p) {} };
bool __cdecl Rva003FE7E6(Rva00211E75Callback callback, int *id);
int __cdecl Rva003FEC05FadeScreenRegionToMapBlack(int,bool);

extern int g_00E02EC4;

class AptTimeLine
{
public:
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save":
	// one body or two folded, so it keeps its address.
	void rva0051E3C3(const char *unused);
	void GraphFocus(int index, const char *value, bool set);
	void PlayerColor(int index, char *value, bool set);
	void PlayerFaction(int index, char *value, bool set);
	void CaHAwardNumber(const char *value);
 void CollectAllPlayerData();

	// Retail 0x0051ED7E (345 bytes), the continue action shared by two callbacks.
	void rva0051ED7E();

private:
	unsigned char m_pad000[0x258];
	Rva00524306 m_images; // +0x258
	unsigned char m_pad259[0x288 - 0x259];
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	unsigned char m_pad294[0x2B8 - 0x294];
	_STL::vector<float> m_focus; // +0x2B8, the per-player focus weights
};

// Retail 0x0051E3C3, 22 bytes: bound as "AptTimeLine::OnButtonSaveReplay"
// and "AptScoreScreen::Save".
void AptTimeLine::rva0051E3C3(const char *unused)
{
	AptSaveLoad::OpenScreen(3, 4, false);
	Rva00433D3CClear();
}


// Retail 0x0051EA7A, 86 bytes: "TimeLine:GraphFocus:%d" for each player,
// an Apt variable Apt writes: the value (a percentage) becomes the player's
// focus weight.
void AptTimeLine::GraphFocus(int index, const char *value, bool set)
{
	if (!set)
		return;
	if (m_focus.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_focus.size())
		m_focus[index] = atoi(value) * 0.01f;
}

// Retail 0x0051E8C8, 113 bytes: "TimeLine:PlayerColor:%d" for each player,
// an Apt variable read as the player's color in hex ("0" when out of
// range).
void AptTimeLine::PlayerColor(int index, char *value, bool set)
{
	if (set)
		return;
	_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>("0"));
	if (m_players.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_players.size())
		sprintf(value, "%#x", m_players[index].m_color & 0xFFFFFF);
}

// Retail 0x0051EC4E, 117 bytes: "TimeLine:PlayerFaction:%d" for each player,
// an Apt variable read as the player's faction name ("" when out of range).
// The unit is built without string pooling (/GF-): retail pushes the first
// "" literal and materialises str()'s empty-string arm separately instead of
// keeping one pooled "" address in EDI.
void AptTimeLine::PlayerFaction(int index, char *value, bool set)
{
	if (set)
		return;
	_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(""));
	if (m_players.empty())
		return;
	if (index >= 0 && (unsigned int)index < m_players.size())
		_mbscpy(reinterpret_cast<unsigned char *>(value), reinterpret_cast<const unsigned char *>(m_players[index].m_faction.str()));
}


// Retail 0x0051EAD3, 350 bytes: "AptTimeLine::CaHAwardNumber" shows the
// given (1-based) earned award's name, description and image.
void AptTimeLine::CaHAwardNumber(const char *value)
{
	unsigned int index = atoi(value) - 1;
	if (index >= ((_STL::vector<int> *)&g_Va00E04920)->size())
		return;
	BfmePod40 *award = TheAwardSystemManager->rva0040AAD5((*(_STL::vector<int> *)&g_Va00E04920)[index]);
	if (!award)
		return;
	if (((StringBase<char> *)&award->m_name)->isEmpty())
		return;
	{
		AsciiString name("APT:CaH_AwardEarned_Name");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(award->m_name), false);
	}
	{
		AsciiString name("APT:CaH_AwardDescription");
		g_bfmeAptWindowManager->bfmeSetText(name, TheGameText->fetch(award->m_description), false);
	}
	if (TheMappedImageCollection)
	{
		const Image *image = TheMappedImageCollection->findImageByName(award->m_image);
		m_images.rva00524725(AsciiString("TimeLine::CahAwardImage"), image);
	}
}

// Complete native51FA13..51FAFC updates each row's name and faction icon;
// WB's weak CollectAllPlayerData lead names a different larger body, so
// retain an address spelling. The twelve-byte concatenation node uses an
// empty default constructor to construct the returned expression in place.
struct Rva002226E5TextPlusString {
 Rva002226E5TextPlusString() {}
 const char *text;int length;const AsciiString *string;
 operator AsciiString();
};
Rva002226E5TextPlusString operator+(const char*,const AsciiString&);
// WorldBuilder AptTimeLine::CollectAllPlayerData, WB VA 0x013DE230 (strings lead, score 2.25).
void AptTimeLine::CollectAllPlayerData() {
 for(_STL::vector<AptTimeLinePlayer>::iterator row=m_players.begin();row!=m_players.end();++row) {
  AsciiString key;
  key.format("TimeLine:PlayerName:%d",row-m_players.begin());
  g_bfmeAptWindowManager->bfmeSetText(key,row->m_name,false);
  key.format("TimeLine:PlayerFactionIcon:%d",row-m_players.begin());
  m_images.rva00524767(key,"AptIcon"+row->m_faction);
 }
}


// AptTimeLine::OpenScreen (WB 0x013DB420, AptTimeLine.cpp; static bool),
// retail 0x00520F7D (367 bytes), kept under the address name the rowed caller
// GameLogic 0x00376E92 already calls. Unless the screen is up, it picks the
// time-line mode: 5 for a replay playback, 1 for the 0x0023C666 game, then from
// the game type (TheGameLogic +0x114) and TheLivingWorldLogic's selection
// lock 8, 6 or 7, else from the game mode (+0x110) 4, 3 or 2 (any other mode
// opens nothing). It plays the misc-audio +0x94 sound, pushes TimeLine.apt
// and hands the mode to the new screen (+0x284) before 0x00520CD1.
// WB reads TheGameLogic at every use; visible noinline copies of the two small
// rowed predicates let cl 7.1 keep it (and the game type) in registers across
// those calls, as retail does.
enum RecorderModeType { RECORDERMODETYPE_RECORD, RECORDERMODETYPE_PLAYBACK };
class RecorderClass { public: RecorderModeType getMode(); };	// 0x0030F2C7
extern RecorderClass *TheRecorder;

class Rva0023C666 { public: bool rva0023C666(); };

// ?get@Rva00210C66CmpBoolField@@QBE_NXZ, rowed 0x00210C66 (LivingWorldLogic.cpp)
class Rva00210C66CmpBoolField
{
public:
	__declspec(noinline) bool get() const { int value = *(const int *)((const char *)this + 0x114); return value == 1 || value == 2; }
};

// ?isSelectionLocked@BfmeSelectionState@@QBE_NXZ, rowed 0x0004253A
class BfmeSelectionState
{
public:
	__declspec(noinline) bool isSelectionLocked() const { return m_first != 0 && m_second != 0; }
private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};

struct AptTimeLineGameLogicView { unsigned char m_pad[0x110]; int m_mode; int m_gameType; };

class Shell
{
public:
	void rva0035BF4C(bool show);
};

class AptTimeLineScreen { public: void rva00520CD1(); };

