// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G6 /arch:SSE
// stlport
//
// AptTimeLine::CollectPlayerData, retail 0x00520923 (942 bytes).
//
// Identity (target evidence): WorldBuilder's AptTimeLine.cpp names the body
// (asserts "!player" at line 1407 and the observer check at 1416); its only
// caller 0x00520F20 walks the living-world players. It appends (or, for the
// local player, reuses the first) 0x50-byte row of the time line at +0x288,
// copies the player's name, colour, side, status and four score vectors,
// sets the end-game texts and image for the local player, and forwards the
// player to the stats panel (AptTimeLineStats::CollectPlayerData).
//
// No Zero Hour counterpart; field names beyond the rowed callees' are
// address-derived.

#include <vector>
#include "unicode_string.h"
#include "ascii_string.h"

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class PlayerTemplate
{
public:
	unsigned char m_pad000[0x18];
	AsciiString m_side; // +0x18
	unsigned char m_pad01C[0x1BC - 0x1C];
	Bool m_isEvil; // +0x1BC
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate(NameKeyType key) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

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

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool placeholder);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class RGBColor
{
public:
	int getAsInt() const;
	float red, green, blue;
};

// Element types of the four per-player score vectors.
struct Rva0051F7ADRecord
{
	unsigned int m_words[2];
};

struct Rva0026F4F4Element
{
	unsigned int m_value;
};

struct Rva00520923Faction
{
	unsigned char m_pad00[4];
	AsciiString m_name; // +0x04, the player template's name
};

class LivingWorldPlayer
{
public:
	unsigned char m_pad000[0x40];
	Rva00520923Faction *m_faction; // +0x40
	unsigned char m_pad044[0x190 - 0x44];
	RGBColor m_color; // +0x190
	unsigned char m_pad19C[0x2F0 - 0x19C];
	_STL::vector<Rva0051F7ADRecord> m_2F0; // +0x2F0
	_STL::vector<Rva0026F4F4Element> m_2FC; // +0x2FC
	_STL::vector<Rva0026F4F4Element> m_308; // +0x308
	_STL::vector<Rva0026F4F4Element> m_314; // +0x314
	unsigned char m_pad320[0x3C4 - 0x320];
	unsigned char m_3C4; // +0x3C4, nonzero once the player is dead
	Bool m_3C5; // +0x3C5, set once the player has left
	Bool hasLeft() const { return m_3C5; }
};

class Rva002E0687
{
public:
	bool rva002E0687() const; // the local (observing) player
};

class Rva002E1046
{
public:
	bool rva002E1046();
};

class StatsReporter
{
public:
	static void ProcessStrategicSinglePlayerGame(LivingWorldPlayer *player);
};

class AptTimeLineStats
{
public:
	void CollectPlayerData(int index, LivingWorldPlayer *player);
};

// The caller's second argument: its display name is at +0x30.
class Rva00520923Source
{
public:
	unsigned char m_pad00[0x30];
	UnicodeString m_displayName; // +0x30
};

class Rva003F83B5
{
public:
	UnicodeString rva003F83B5();
};

class Rva004FCBA9
{
public:
	UnicodeString rva004fcba9();
};

struct Rva00520923Scenario
{
	unsigned char m_pad00[4];
	AsciiString m_name; // +0x04
};

struct Rva00520923Campaign
{
	unsigned char m_pad00[0x1C];
	Rva00520923Scenario *m_scenario; // +0x1C
};

class Rva00E02D6C
{
public:
	unsigned char m_pad00[0x10];
	int m_current; // +0x10
	Rva00520923Campaign **m_campaigns; // +0x14
	Rva00520923Campaign **getCampaigns() const { return m_campaigns; }
};

extern Rva00E02D6C *TheCampaignManager;

class Rva00524306
{
public:
	void rva00524767(const AsciiString &name, const AsciiString &image);
};

// One player's row of the time line (0x50 bytes).
struct AptTimeLinePlayer
{
	unsigned char m_pad00[4];
	UnicodeString m_name; // +0x04
	int m_color; // +0x08
	AsciiString m_faction; // +0x0C
	int m_status; // +0x10: 0 won, 1 dead, 2 left, 3 (0x002E1046)
	unsigned char m_pad14[0x20 - 0x14];
	_STL::vector<Rva0051F7ADRecord> m_20; // +0x20
	_STL::vector<Rva0026F4F4Element> m_2C; // +0x2C
	_STL::vector<Rva0026F4F4Element> m_38; // +0x38
	_STL::vector<Rva0026F4F4Element> m_44; // +0x44
};

class AptTimeLine
{
public:
	void CollectPlayerData(LivingWorldPlayer *player, Rva00520923Source *source);
private:
	unsigned char m_pad000[0x258];
	Rva00524306 m_images; // +0x258
	unsigned char m_pad259[0x280 - 0x259];
	AptTimeLineStats *m_stats; // +0x280
	int m_284; // +0x284, 6 for a strategic single-player game
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
};

void AptTimeLine::CollectPlayerData(LivingWorldPlayer *player, Rva00520923Source *source)
{
	if (player == 0)
		return;
	Bool isLocal = ((const Rva002E0687 *)player)->rva002E0687();
	int index = m_players.size();
	if (isLocal)
		index = 0;
	else
		m_players.resize(index + 1);
	_STL::vector<AptTimeLinePlayer>::iterator row = isLocal ? m_players.begin() : m_players.end() - 1;
	if (source)
		row->m_name = source->m_displayName;
	row->m_color = player->m_color.getAsInt() | 0xff000000;
	Bool isEvil = false;
	if (ThePlayerTemplateStore)
	{
		const PlayerTemplate *playerTemplate = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey(player->m_faction->m_name));
		if (playerTemplate)
		{
			row->m_faction = playerTemplate->m_side;
			isEvil = playerTemplate->m_isEvil;
		}
	}
	row->m_status = 0;
	if (player->hasLeft())
		row->m_status = 2;
	else if (player->m_3C4)
		row->m_status = 1;
	else if (((Rva002E1046 *)player)->rva002E1046())
		row->m_status = 3;
	row->m_20 = player->m_2F0;
	row->m_2C = player->m_314;
	row->m_38 = player->m_2FC;
	row->m_44 = player->m_308;

	if (isLocal)
	{
		if (m_284 == 6)
			StatsReporter::ProcessStrategicSinglePlayerGame(player);
		if (row->m_status == 0 || row->m_status == 1)
		{
			UnicodeString winLoss = TheGameText->fetch(row->m_status == 0 ? "APT:EndVictorious" : "APT:EndDefeat");
			g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:StrategicWinLossTitle"), winLoss, false);
			UnicodeString scenarioName;
			UnicodeString description;
			Rva00520923Campaign *campaign = TheCampaignManager->getCampaigns()[TheCampaignManager->m_current];
			Rva00520923Scenario *scenario = campaign->m_scenario;
			if (scenario)
			{
				scenarioName = TheGameText->fetch(scenario->m_name);
				description = row->m_status == 0
					? ((Rva003F83B5 *)scenario)->rva003F83B5()
					: ((Rva004FCBA9 *)scenario)->rva004fcba9();
			}
			g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:StrategicScenarioName"), scenarioName, false);
			g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:StrategicWinLossConditionDescription"), description, false);
			const char *image;
			if (isEvil)
				image = row->m_status == 0 ? "StrategicEndGameEvilWin" : "StrategicEndGameEvilLose";
			else
				image = row->m_status == 0 ? "StrategicEndGameGoodWin" : "StrategicEndGameGoodLose";
			m_images.rva00524767(AsciiString("StrategicWinLossImage"), AsciiString(image));
		}
	}
	if (m_stats)
		m_stats->CollectPlayerData(index, player);
}
