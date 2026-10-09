// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/GameEngine/Source/Common /ICode/GameEngine/Include
//
// ?init@AptLoadScreen@@UAEXPAVGameInfo@@@Z
// retail 0x0043A5F6..0x0043AE0C (2070 bytes) thiscall RET 4.
//
// AptLoadScreen::init (WorldBuilder name 0x0129FA00, AptLoadScreen.cpp lines
// 212..434), slot 2 of the screen's vftable 0x00C3D50C (absolute reference
// 0x0083D514). It keeps the game at +0x88, blanks the eight
// "LoadingScreen::Rank%d" texts, clears the map preview (+0x18) and for each
// occupied slot fills the next row's player name, team and army texts, picks
// the row's rank image (the AI difficulty icon; the GameSpy player's rank
// icon from the 0x00E05FCC/0x00E06000 tables; the ranked GameSpy slot's
// "LoadingScreen::Rank%d" text; the skirmish profile's strategic or real time
// stats icon) and the fellowship clip for a good player, records the slot and
// row (+0xB0/+0x90) and reports progress 0 through vslot 4. The unused rows
// are blanked, the local player's faction load music is played, the game
// logic is told (0x0023CF8B) and a GameSpy staging room gets vslot 47.
#include "ascii_string.h"
#include "unicode_string.h"

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &text, bool flag);
	void rva00225375(const AsciiString &key, const AsciiString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

// The Apt clip image setter (rowed 0x002239E2 on its placeholder class).
class Rva002239B2
{
public:
	void rva002239E2(const AsciiString &clip, const Image *image);
};

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

// The GameSpy view of a slot: the two ladder ranks.
struct GameSpySlotView
{
	unsigned char m_pad000[0x1D0];
	int m_rank1D0; // +0x1D0
	int m_rank1D4; // +0x1D4
};

class GameSlot
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual GameSpySlotView *gameSpySlot(); // slot 6

	bool isOccupied() const;
	bool isAI() const;
	UnicodeString getApparentPlayerTemplateDisplayName() const;

	int m_state;				// +0x04
	unsigned char m_pad08[0x18 - 0x08];
	int m_playerTemplate;	   // +0x18
	int m_teamNumber;		   // +0x1C
	unsigned char m_pad20[0x30 - 0x20];
	UnicodeString m_name;	   // +0x30
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum(); // slot 13

	GameSlot *getSlot(int index);

	unsigned char m_pad04[0x5C - 0x04];
	int m_gameMode; // +0x5C
};

extern GameInfo *TheGameInfo;
extern GameInfo *TheSkirmishGameInfo;

class GameSpyStagingRoom
{
public:
	unsigned char m_pad000[0xFEC];
	bool m_fec;		 // +0xFEC
	unsigned char m_padFED[0xFF4 - 0xFED];
	bool m_isRanked;	// +0xFF4
	unsigned char m_padFF5[0xFF8 - 0xFF5];
	int m_ladderType;   // +0xFF8
};

extern GameSpyStagingRoom *TheGameSpyGame;

// The GameSpy player record: +0x14 and the rank at +0x1C.
struct GameSpyPlayerInfoView
{
	unsigned char m_pad00[0x14];
	int m_14;   // +0x14
	unsigned char m_pad18[0x1C - 0x18];
	int m_rank; // +0x1C
};

class GameSpyInfoInterface
{
public:
#define V(n) virtual void gs##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
	V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
	V(20) V(21)
	virtual GameSpyPlayerInfoView *findPlayerInfo(const char *name) = 0; // slot 22
	V(23) V(24) V(25) V(26) V(27) V(28) V(29)
	V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46)
	virtual void gs47() = 0;							 // slot 47
	V(48) V(49) V(50) V(51) V(52)
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0; // slot 53
	V(54) V(55) V(56) V(57) V(58) V(59)
	V(60) V(61) V(62) V(63) V(64) V(65) V(66) V(67) V(68) V(69)
	V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89)
	virtual bool gs90(int value) = 0;					// slot 90
#undef V
};

extern GameSpyInfoInterface *TheGameSpyInfo;

// The rank image tables (Rva00559AC1.cpp) by their ledger names.
class Rva00559AC1
{
public:
	const Image *rva00559C25(int side, int rank);
};

extern unsigned int g_Va00E05FCC;
extern unsigned int g_Va00E06000;
extern char *g_00E06034;
extern char *g_rva005C1A8DDefault;

const Image *Rva00559B64GetImage(int side, int difficulty);
int Rva0033A3F4Lookup(const AsciiString &armyName);
UnicodeString Rva0043A568Get(int rank);

class UserPreferences
{
public:
	virtual ~UserPreferences();
	int rva005358C3(AsciiString key);

private:
	unsigned char m_rest[0x14 - 0x04];
};

class StrategicStatsPreferences : public UserPreferences
{
public:
	StrategicStatsPreferences(const UnicodeString &profilePath);
	virtual ~StrategicStatsPreferences();
};

class RealTimeStatsPreferences : public UserPreferences
{
public:
	RealTimeStatsPreferences(const UnicodeString &profilePath);
	virtual ~RealTimeStatsPreferences();
};

class SkirmishPreferences
{
public:
	SkirmishPreferences(int profileIndex);
	virtual ~SkirmishPreferences();
	UnicodeString Rva0043B9F5();

private:
	unsigned char m_rest[0x20 - 0x04];
};

class PlayerTemplate
{
public:
	unsigned char m_pad000[0x14C];
	AsciiString m_loadScreenMusic; // +0x14C
};

enum NameKeyType;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int index) const;
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

#include "Common/BfmeAudioEventPrefix136.h"

// Owning AudioEventInfo reference returned by the slot-75 lookup
// (MilesAudioManager.cpp).
class AudioEventInfoRef
{
public:
	~AudioEventInfoRef() { if (m_ptr) m_ptr->Release_Ref(); }
	bool isValid() const { return m_ptr != 0; }
	const OpaqueRefElement4 &element() const { return *(const OpaqueRefElement4 *)this; }

private:
	OpaqueRefCounted *m_ptr;
};

template <int N> class AptLoadScreenAudioSlots : public AptLoadScreenAudioSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AptLoadScreenAudioSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class AudioManager : public AptLoadScreenAudioSlots<10>
{
public:
	virtual void slot10();														// +0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23(); virtual void slot24();
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);			// +0x64
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34();
	virtual void slot35(int a, int b, int c);									// +0x8C
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &name) const;	// +0x12C
};

extern AudioManager *TheAudio;

// The event's flag setter is identical-code-folded with the rowed
// Weapon::setLeechRangeActive.
class Weapon
{
public:
	void setLeechRangeActive(bool active);
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

// The embedded map preview (+0x18).
class Rva0057E3DB
{
public:
	void rva0057C7BA(int value);
};

class AptLoadScreen
{
public:
	virtual ~AptLoadScreen();
	virtual void update(int percent);
	virtual void init(GameInfo *game);
	virtual void reset();
	virtual void processProgress(int playerId, int percentage);

private:
	unsigned char m_pad004[0x18 - 0x04];
	Rva0057E3DB m_mapPreview;	// +0x18
	unsigned char m_pad019[0x88 - 0x19];
	GameInfo *m_game;			// +0x88
	int m_level;				// +0x8C
	int m_rowSlot[8];			// +0x90
	int m_slotRow[8];			// +0xB0
};

void AptLoadScreen::init(GameInfo *game)
{
	if (!game)
		return;

	m_game = game;
	AsciiString key;
	AsciiString teamText;
	AsciiString clipName;
	int row = 0;
	const Image *fellowshipImage = TheMappedImageCollection->findImageByName(AsciiString("Aptfellowship_clup"));
	bool isRanked = TheGameSpyGame && TheGameSpyGame->m_isRanked;

	for (int rank = 0; rank <= 7; ++rank)
	{
		AsciiString rankKey;
		rankKey.format("LoadingScreen::Rank%d", rank);
		g_bfmeAptWindowManager->bfmeSetText(rankKey, UnicodeString(L" "), false);
	}

	int gameMode = TheGameInfo ? TheGameInfo->m_gameMode : 0;
	m_mapPreview.rva0057C7BA(0);

	int i;
	for (i = 0; i < 8; ++i)
	{
		GameSlot *slot = m_game->getSlot(i);
		if (!slot || !slot->isOccupied())
			continue;
		if (row == 8)
			break;

		key.format("LoadingScreen::PlayerName%d", row);
		g_bfmeAptWindowManager->bfmeSetText(key, slot->m_name, false);
		key.format("LoadingScreen::TeamNumber%d", row);
		if (slot->isAI() && slot->m_teamNumber == -1)
			teamText = "Team:0";
		else
			teamText.format("Team:%d", slot->m_teamNumber + 1);
		g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch(teamText), false);
		key.format("LoadingScreen::ArmyName%d", row);
		UnicodeString armyName = slot->getApparentPlayerTemplateDisplayName();
		g_bfmeAptWindowManager->bfmeSetText(key, armyName, false);

		bool isGood = false;
		const Image *rankImage = 0;
		AsciiString armyText(armyName);
		int side = Rva0033A3F4Lookup(armyText);
		if (slot->isAI() && (TheSkirmishGameInfo || TheGameSpyInfo) && !isRanked)
		{
			switch (slot->m_state)
			{
			case 2:
				rankImage = Rva00559B64GetImage(side, 1);
				break;
			case 3:
				rankImage = Rva00559B64GetImage(side, 4);
				break;
			case 4:
				rankImage = Rva00559B64GetImage(side, 6);
				break;
			case 5:
				rankImage = Rva00559B64GetImage(side, 9);
				break;
			}
		}
		else if (TheGameSpyInfo && !isRanked)
		{
			AsciiString playerName(slot->m_name);
			GameSpyPlayerInfoView *info = TheGameSpyInfo->findPlayerInfo(playerName.str());
			if (info)
			{
				isGood = TheGameSpyInfo->gs90(info->m_14);
				Rva00559AC1 *table = gameMode == 1 ? (Rva00559AC1 *)&g_Va00E05FCC : (Rva00559AC1 *)&g_Va00E06000;
				rankImage = table->rva00559C25(side, info->m_rank);
			}
			else
			{
				rankImage = TheMappedImageCollection->findImageByName(AsciiString("AptRankIcon0"));
			}
		}
		else if (TheGameSpyInfo && isRanked)
		{
			GameSpySlotView *gsSlot = slot->gameSpySlot();
			int ladderRank = TheGameSpyGame->m_ladderType == 2 ? gsSlot->m_rank1D4 : gsSlot->m_rank1D0;
			UnicodeString rankText = Rva0043A568Get(ladderRank);
			AsciiString rankKey;
			rankKey.format("LoadingScreen::Rank%d", i);
			g_bfmeAptWindowManager->bfmeSetText(rankKey, UnicodeString(rankText), false);
		}
		else if (TheSkirmishGameInfo)
		{
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(slot->m_playerTemplate);
			if (pt)
			{
				SkirmishPreferences prefs(gameMode);
				if (gameMode == 1)
				{
					StrategicStatsPreferences stats(prefs.Rva0043B9F5());
					rankImage = ((Rva00559AC1 *)&g_00E06034)->rva00559C25(side, stats.rva005358C3(armyText));
				}
				else
				{
					RealTimeStatsPreferences stats(prefs.Rva0043B9F5());
					rankImage = ((Rva00559AC1 *)&g_rva005C1A8DDefault)->rva00559C25(side, stats.rva005358C3(armyText));
				}
			}
		}

		clipName.format("UIClip/Level/%d", row);
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(clipName, rankImage);
		clipName.format("UIClip/Fellowship/%d", row);
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(clipName, isGood ? fellowshipImage : 0);
		m_slotRow[i] = row;
		m_rowSlot[row] = i;
		++row;
		processProgress(i, 0);
	}

	for (; row < 8; ++row)
	{
		key.format("LoadingScreen::PlayerName%d", row);
		g_bfmeAptWindowManager->rva00225375(key, AsciiString(" "), false);
		key.format("LoadingScreen::TeamNumber%d", row);
		g_bfmeAptWindowManager->rva00225375(key, AsciiString(" "), false);
		key.format("LoadingScreen::ArmyName%d", row);
		g_bfmeAptWindowManager->rva00225375(key, AsciiString(" "), false);
		clipName.format("UIClip/Level/%d", i);
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(clipName, 0);
		clipName.format("UIClip/Fellowship/%d", i);
		((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(clipName, 0);
	}

	GameSlot *localSlot = game->getSlot(game->getLocalSlotNum());
	if (localSlot)
	{
		const PlayerTemplate *pt;
		if (localSlot->m_playerTemplate >= 0)
			pt = ThePlayerTemplateStore->getNthPlayerTemplate(localSlot->m_playerTemplate);
		else
			pt = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver"));
		AsciiString music = pt->m_loadScreenMusic;
		AudioEventInfoRef info = TheAudio->findAudioEventInfo(music);
		if (info.isValid())
		{
			TheAudio->slot35(2, 1, 1);
			BfmeAudioEventPrefix136 event(info.element(), 2);
			((Weapon *)&event)->setLeechRangeActive(false);
			TheAudio->addAudioEvent(&event);
			TheAudio->slot10();
		}
	}

	TheGameLogic->rva0023CF8B();
	if (TheGameSpyInfo)
	{
		GameSpyStagingRoom *room = TheGameSpyInfo->getCurrentStagingRoom();
		if (room && room->m_fec)
			TheGameSpyInfo->gs47();
	}
}
