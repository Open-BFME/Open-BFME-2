// cl: /O1 /G7 /arch:SSE /MD /EHsc /I. /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00520CD1@AptTimeLine@@QAEXXZ retail 0x00520CD1 684B (native 00520CD1..00520F7D RET0).
// WB 0x013DE230 AptTimeLine::CollectAllPlayerData holds this body plus the tail retail split
// out to CollectAllPlayerData 0x0051FA13, so the address name stays. GameSlot's template is read
// through an inline accessor in the j loop: the accessor temp, not a direct member read, gives
// retail's allocation (slot in EDI after the loop, tactical in [ebp-0x1c]).
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include "../../../../../../Libraries/Include/Lib/RGBColor.h"
class BfmeWideString000543F5
{
public:
	~BfmeWideString000543F5();

private:
	char *m_text;
};

class Rva0039C151Subobject
{
public:
	~Rva0039C151Subobject();

private:
	char m_pad[12];
};

class Rva004EE501Subobject
{
public:
	~Rva004EE501Subobject();

private:
	char m_pad[12];
};

void __cdecl Rva00030830GameFree(void *);

struct Rva00520211FreeOwner
{
	void *m_block;
	int m_unused04;
	int m_unused08;

	~Rva00520211FreeOwner()
	{
		if (m_block != 0)
			Rva00030830GameFree(m_block);
	}
};

// Native destroy/fill helpers advance by 0x50; field identities stay opaque.
struct Rva00520211Element
{
	int m_unknown00;
	BfmeWideString000543F5 m_wide04;
	int m_unknown08;
	AsciiString m_ascii0C;
	int m_unknown10;
	Rva0039C151Subobject m_subobject14;
	Rva004EE501Subobject m_subobject20;
	Rva00520211FreeOwner m_owned2C;
	Rva00520211FreeOwner m_owned38;
	Rva00520211FreeOwner m_owned44;
	Rva00520211Element(const Rva00520211Element &);
	Rva00520211Element &operator=(const Rva00520211Element &);
	~Rva00520211Element();
};
// Declared only: the rowed range erase and reserve serve these calls.
namespace _STL {
template <> Rva00520211Element *vector<Rva00520211Element>::erase(Rva00520211Element *, Rva00520211Element *);
template <> void vector<Rva00520211Element>::reserve(unsigned int);
}
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
struct Rva0051C0E7;
class AptScoreScreen {public: static void PreCollectGameData(Rva0051C0E7*);};
class IDBufferClass {public:void Enable_Two_Sided_Rendering(bool);};
enum NameKeyType {NAMEKEY_INVALID=0};
class Player;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerList {public:Player *findPlayerWithNameKey(NameKeyType);char pad00[0x10];Player *m_local;};
extern PlayerList *ThePlayerList;
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
class GameInfo {public:GameSlot *getSlot(int);};
extern GameInfo *TheGameInfo;
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
class LivingWorldPlayer;
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *GetPlayerAtIndex(int);
	char m_pad00[0x8C];
	_STL::vector<LivingWorldPlayer*> m_players; // +0x8C
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva0051F7ADRecord;
struct Rva0026F4F4Element;
struct Rva00520923Faction
{
	unsigned char m_pad00[4];
	AsciiString m_name; // +0x04, the player template's name
};

class LivingWorldPlayer
{
public:
	unsigned char m_pad000[0x14];
	void *m_template; // +0x14
	unsigned char m_pad018[0x40 - 0x18];
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
	bool m_3C5; // +0x3C5, set once the player has left
	bool hasLeft() const { return m_3C5; }
};
class Rva002E0687
{
public:
	bool rva002E0687() const; // the local (observing) player
};
class GameSpyStagingRoom;
extern GameSpyStagingRoom *TheGameSpyGame;
class StatsReporter
{
public:
	static void ProcessStrategicSinglePlayerGame(LivingWorldPlayer *player);
	static void ProcessOnlineGameResults(class Player *player);
};
class Rva00520923Source;
class Image;

template <class T> class AptRef;
class AptCommandMap;
class AptExternHandler;
class AptOverButtonHandler;

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

class AptOverButtonHandlerAdder
{
public:
	void AddOverButtonHandler(const AsciiString &name, AptRef<AptOverButtonHandler> handler);
private:
	_STL::vector<AsciiString> m_names;
};

// The image binder at +0x40 of the Apt window half (0x00524306 family), +0x258
// of the screen: window name to image name, with its rowed setter 0x00524725.
class Rva00524306
{
public:
	void rva00524725(const AsciiString &key, const Image *image);
	void rva00524767(const AsciiString &key, const AsciiString &image);
private:
	_STL::vector<AsciiString> m_names;
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
	AptCommandMapAdder m_commandMaps; // +0x04
	AptExternHandlerAdder m_externHandlers; // +0x10
	AptOverButtonHandlerAdder m_overButtonHandlers; // +0x1C
private:
	unsigned char m_pad028[0x40 - 0x28];
public:
	Rva00524306 m_imageAdder; // +0x40
private:
	unsigned char m_pad04C[0x58 - 0x4C];
};

class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
	char m_pad04[0x214];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270; // +0x270
	int m_274; // +0x274
	char m_278; // +0x278
	char m_pad279[0x3];
};

struct Pair0051E31A;
struct Rva0051F7ADRecord;
struct Rva0026F4F4Element;
class AptTimeLineStats;
class LivingWorldPlayer;
class Rva00520923Source;

// One player's row of the time line (0x50 bytes): name, color, faction name,
// status, and the score vectors; m_eventsA and m_eventsB hold the graph's event frames.
struct AptTimeLinePlayer
{
	unsigned char m_pad00[4];
	UnicodeString m_name;        // +0x04
	int m_color;                 // +0x08
	AsciiString m_faction;       // +0x0C, read by PlayerFaction 0x0051EC4E
	int m_side;                  // +0x10: 0 won, 1 dead, 2 left, 3 (0x002E1046)
	unsigned char m_pad14[0x20 - 0x14];
	_STL::vector<Rva0051F7ADRecord> m_20; // +0x20
	_STL::vector<Rva0026F4F4Element> m_eventsA; // +0x2C
	_STL::vector<Rva0026F4F4Element> m_eventsB; // +0x38
	_STL::vector<Rva0026F4F4Element> m_44; // +0x44
};

class AptTimeLine : public _bfme_AptGameWindow
{
public:
	virtual void rva0051FCA2();
	void OnButtonContinue(const char *unused);
	// Bound as "AptTimeLine::OnButtonSaveReplay" and "AptScoreScreen::Save":
	// one body or two folded, so it keeps its address.
	void rva0051E3C3(const char *unused);
	void GraphFocus(int index, const char *value, bool set);
	void PlayerColor(int index, char *value, bool set);
	void PlayerFaction(int index, char *value, bool set);
	void CaHAwardNumber(const char *value);
	void CollectAllPlayerData();
	void RenderGraph(const Pair0051E31A &position, const Pair0051E31A &size, int unused, const char *params);
	void CollectPlayerData(class Player *player, const class GameSlot *slot);
	void CollectPlayerData(LivingWorldPlayer *player, Rva00520923Source *source);
	void rva00520CD1();

	// Retail 0x0051ED7E (345 bytes), the continue action shared by two callbacks.
	void rva0051ED7E();

private:
	unsigned char m_pad27C[0x280 - 0x27C];
	AptTimeLineStats *m_stats;          // +0x280
	int m_gameType;                     // +0x284, 6 for a strategic single-player game
	_STL::vector<AptTimeLinePlayer> m_players; // +0x288
	bool m_observer;                    // +0x294
	unsigned char m_pad295[0x298 - 0x295];
	Image *m_sideImages[4];             // +0x298
	Image *m_eventImageA;               // +0x2A8
	Image *m_eventImageB;               // +0x2AC
	float m_lastMaximum;                // +0x2B0
	int m_lastFrames;                   // +0x2B4
	_STL::vector<float> m_focus;        // +0x2B8, one focus weight per player
	char m_extra[48];                   // +0x2C4
};
void AptTimeLine::rva00520CD1()
{
	reinterpret_cast<_STL::vector<Rva00520211Element> *>(&m_players)->clear();
	reinterpret_cast<_STL::vector<Rva00520211Element> *>(&m_players)->reserve(8);
	m_observer=false;
	reinterpret_cast<IDBufferClass*>(m_stats)->Enable_Two_Sided_Rendering(false);
	if(m_gameType==6 || m_gameType==7){
		reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
		GameInfo *game=0;
		if(m_gameType==6)game=reinterpret_cast<GameInfo*>(TheSkirmishGameInfo);
		else if(m_gameType==7)game=TheGameInfo;
		if(game) {
			for(int i=0;i<(int)reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->m_players.size();++i) {
				LivingWorldPlayer *player=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->GetPlayerAtIndex(i));
				GameSlot * slot = 0;
				for(int j=0;j<8;++j) {
					if(game->getSlot(j)->getTemplate()==player->m_template) {slot=game->getSlot(j);break;}
				}
				if(TheGameSpyGame && reinterpret_cast<Rva002E0687*>(player)->rva002E0687() && m_gameType==7) {
					AsciiString name=slot->m_name;
					Player *tactical=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
					if(tactical && !tactical->isPlayerObserver())StatsReporter::ProcessOnlineGameResults(tactical);
				}
				CollectPlayerData(player,reinterpret_cast<Rva00520923Source*>(slot));
			}
		}
	}else{
		if(TheGameInfo) {
			m_observer=ThePlayerList->m_local->isPlayerObserver();
			reinterpret_cast<IDBufferClass*>(m_stats)->Enable_Two_Sided_Rendering(m_observer);
			if(!m_observer)reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
			for(int i=0;i<8;++i) {
				GameSlot *slot=TheGameInfo->getSlot(i);
				if(slot->isOccupied()) {
					AsciiString name=slot->m_name;
					if(!name.isEmpty()) {
						Player *player=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name));
						if(player && !player->isPlayerObserver())CollectPlayerData(player,slot);
					}
				}
			}
		} else {
			reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
			Player *player=ThePlayerList->m_local;
			if(!player)return;
			CollectPlayerData(player,0);
		}
	}
	if(m_gameType==1||m_gameType==6||m_gameType==7)AptScoreScreen::PreCollectGameData(reinterpret_cast<Rva0051C0E7*>(m_extra));
	CollectAllPlayerData();
}
