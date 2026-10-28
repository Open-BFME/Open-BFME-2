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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
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
	void bfmeSetText(const AsciiString &name, const UnicodeString &text, bool flag);
};

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../../../../../Libraries/Include/Lib/RGBColor.h"
// Suppress this TU's non-retail copy of ??4?$vector@URva0026F4F4Element@@V?$allocator@URva0026F4F4Element@@@_STL@@@_STL@@QAEAAV01@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0026F4F4Element;
namespace _STL { template <> vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > & vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> >::operator=(vector<Rva0026F4F4Element,allocator<Rva0026F4F4Element> > const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@IAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> void vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_M_allocate_and_copy@PBURva0051F7ADRecord@@@?$vector@URva0051F7ADRecord@@V?$allocator@U:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> template <> Rva0051F7ADRecord * vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::_M_allocate_and_copy<Rva0051F7ADRecord const *>(unsigned int,Rva0051F7ADRecord const *,Rva0051F7ADRecord const *); }
// Suppress this TU's non-retail copy of ??4?$vector@URva0051F7ADRecord@@V?$allocator@URva0051F7ADRecord@@@_STL@@@_STL@@QAEAAV01@AB:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > & vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> >::operator=(vector<Rva0051F7ADRecord,allocator<Rva0051F7ADRecord> > const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PBURva0051F7ADRecord@@PAU1@@_STL@@YAPAURva0051F7ADRecord@@PBU1@0PA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> Rva0051F7ADRecord * __uninitialized_copy<Rva0051F7ADRecord const *,Rva0051F7ADRecord *>(Rva0051F7ADRecord const *,Rva0051F7ADRecord const *,Rva0051F7ADRecord *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$_Construct@URva0051F7ADRecord@@U1@@_STL@@YAXPAURva0051F7ADRecord@@ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> void _Construct<Rva0051F7ADRecord,Rva0051F7ADRecord>(Rva0051F7ADRecord *,Rva0051F7ADRecord const &); }
// Suppress this TU's non-retail copy of ??$__copy@PBURva0051F7ADRecord@@PAU1@H@_STL@@YAPAURva0051F7ADRecord@@PBU1@0PAU1@ABUrandom_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0051F7ADRecord;
namespace _STL { template <> Rva0051F7ADRecord * __copy<Rva0051F7ADRecord const *,Rva0051F7ADRecord *,int>(Rva0051F7ADRecord const *,Rva0051F7ADRecord const *,Rva0051F7ADRecord *,random_access_iterator_tag const &,int *); }

// Element types of the four per-player score vectors.
struct Rva0051F7ADRecord
{
	unsigned int m_words[2];
};
// The records' range destroy is the rowed 0x0052C37A body.
struct Rva0052BFB5Elem;
void __cdecl Rva0052C37ADestroyRange(Rva0052BFB5Elem *, Rva0052BFB5Elem *);
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy<Rva0051F7ADRecord *>(Rva0051F7ADRecord *first, Rva0051F7ADRecord *last)
{ Rva0052C37ADestroyRange((Rva0052BFB5Elem *)first, (Rva0052BFB5Elem *)last); }
}

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
	static void ProcessOnlineGameResults(class Player *player);
};

class AptTimeLineStats
{
public:
	void rva005BF177();
	void CollectPlayerData(int index, LivingWorldPlayer *player);
	void CollectPlayerData(int index, class Player *player);
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
	void CollectPlayerData(class Player *player, const class GameSlot *slot);
private:
	unsigned char m_pad000[0x258];
	Rva00524306 m_images; // +0x258
	unsigned char m_pad259[0x280 - 0x259];
	AptTimeLineStats *m_stats; // +0x280
	int m_284; // +0x284, 6 for a strategic single-player game
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
};

// resize(n) is the rowed 0x0052076F body.
struct Rva005205DAElement;
class Rva00520703Vector
{
public:
	void resize(unsigned count,Rva005205DAElement value);
	void resize(unsigned count);
private:
	Rva005205DAElement *start; // +0x00
	Rva005205DAElement *finish; // +0x04
	Rva005205DAElement *end; // +0x08
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
		reinterpret_cast<Rva00520703Vector *>(&m_players)->resize(index + 1);
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

// RTS CollectPlayerData: native 0x00520792..0x00520923 is a complete
// 401B RET8 body. WB 0x013DE9F0 names the overload (AptTimeLine.cpp:1312,
// 1321), and independently shows the local-player row and results reporting.
// Target fields: Player name38/side58/color280, graph vectors6D8/6E4;
// timeline stats280/mode284/80B rows288. The existing strategic overload
// supplies the row ABI only; its LivingWorldPlayer layout is kept separate.
// All direct calls use their admitted provider names. The flag reader and
// victory interface retain consuming views; their original types are unknown.
class Player
{
public:
	bool isLocalPlayer() const;
	bool isPlayerObserver()const;
};
class GameSlot
{
public:
	bool disconnected() const;
	bool isOccupied()const;
	void *getTemplate()const{return m_template;}
	char m_pad00[0x34];
	AsciiString m_name; // +0x34
	char m_pad38[0x14];
	void *m_template; // +0x4C
};
class Rva0051F6DF { public: Rva0051F6DF &operator=(const Rva0051F6DF &); };
class Rva001EB0CAHolder { public: unsigned char rva001EB0D9(); };
class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;
class VictoryConditionsInterface; extern VictoryConditionsInterface *TheVictoryConditions;
class TimelineVictoryView {
public:
#define TIMELINE_VS(N) virtual void v##N();
 TIMELINE_VS(0) TIMELINE_VS(1) TIMELINE_VS(2) TIMELINE_VS(3)
 TIMELINE_VS(4) TIMELINE_VS(5) TIMELINE_VS(6) TIMELINE_VS(7)
 TIMELINE_VS(8) TIMELINE_VS(9) TIMELINE_VS(10) TIMELINE_VS(11)
 TIMELINE_VS(12) TIMELINE_VS(13)
 virtual bool hasWon(Player*); TIMELINE_VS(15) virtual bool hasLost(Player*);
#undef TIMELINE_VS
};
struct TimelineRTSPlayerView {
 unsigned char pad000[0x38]; UnicodeString name;
 unsigned char pad03C[0x58-0x3C]; AsciiString side;
 unsigned char pad05C[0x280-0x5C]; int color;
 unsigned char pad284[0x6D8-0x284];
 unsigned char graph[12]; _STL::vector<Rva0026F4F4Element> values;
};
void __cdecl Rva005BF4BCProcess(Player*);
void AptTimeLine::CollectPlayerData(Player *player, const GameSlot *slot)
{
 if (!player) return;
 Bool isLocal=player->isLocalPlayer();
 int index=m_players.size();
 if(isLocal) index=0;
 else reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(index+1);
 _STL::vector<AptTimeLinePlayer>::iterator row=isLocal?m_players.begin():m_players.end()-1;
 TimelineRTSPlayerView *rts=reinterpret_cast<TimelineRTSPlayerView*>(player);
 if(m_284!=1)row->m_name=rts->name;
 else row->m_name=TheGameText->fetch("GUI:Player");
 row->m_color=rts->color;
 row->m_faction=rts->side;
 if(m_284!=1) {
  row->m_status=3;
  if(slot && slot->disconnected()) row->m_status=2;
  else if(reinterpret_cast<TimelineVictoryView*>(TheVictoryConditions)->hasLost(player))row->m_status=1;
  else if(reinterpret_cast<TimelineVictoryView*>(TheVictoryConditions)->hasWon(player))row->m_status=0;
 } else {
  row->m_status=1;
  if(TheLinearCampaignManager && reinterpret_cast<Rva001EB0CAHolder*>(TheLinearCampaignManager)->rva001EB0D9())row->m_status=0;
 }
 *reinterpret_cast<Rva0051F6DF*>(reinterpret_cast<char*>(&*row)+0x14)=*reinterpret_cast<const Rva0051F6DF*>(rts->graph);
 row->m_2C=rts->values;
 if(isLocal) {
  if(m_284==2)Rva005BF4BCProcess(player);
  if(m_284==4)StatsReporter::ProcessOnlineGameResults(player);
 }
 if(m_stats)m_stats->CollectPlayerData(index,player);
}
