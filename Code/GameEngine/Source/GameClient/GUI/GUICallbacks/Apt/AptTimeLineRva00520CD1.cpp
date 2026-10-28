// cl: /O1 /G7 /arch:SSE /MD /EHsc /I. /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00520CD1@AptTimeLine@@QAEXXZ retail 0x00520CD1 684B (native 00520CD1..00520F7D RET0).
// WB 0x013DE230 AptTimeLine::CollectAllPlayerData holds this body plus the tail retail split
// out to CollectAllPlayerData 0x0051FA13, so the address name stays. GameSlot's template is read
// through an inline accessor in the j loop: the accessor temp, not a direct member read, gives
// retail's allocation (slot in EDI after the loop, tactical in [ebp-0x1c]).
#include "ascii_string.h"
#include <vector>
struct Rva00520211Element { char storage[80]; };
extern template Rva00520211Element *_STL::vector<Rva00520211Element>::erase(Rva00520211Element *,Rva00520211Element *);
extern template void _STL::vector<Rva00520211Element>::reserve(unsigned);
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
class LivingWorldPlayer {public:char pad00[0x14];void *m_template;};
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
class AptTimeLine {public:
	void rva00520CD1();void CollectPlayerData(Player*,const GameSlot*);
	void CollectPlayerData(LivingWorldPlayer*,Rva00520923Source*);
	void CollectAllPlayerData();
	char pad000[0x280];void *m_stats;int m_mode;
	_STL::vector<Rva00520211Element> m_players;
	bool m_observer;char pad295[0x2c4-0x295];char m_extra[48];
};
void AptTimeLine::rva00520CD1()
{
	m_players.clear();
	m_players.reserve(8);
	m_observer=false;
	reinterpret_cast<IDBufferClass*>(m_stats)->Enable_Two_Sided_Rendering(false);
	if(m_mode==6 || m_mode==7){
		reinterpret_cast<Rva00520703Vector*>(&m_players)->resize(1);
		GameInfo *game=0;
		if(m_mode==6)game=reinterpret_cast<GameInfo*>(TheSkirmishGameInfo);
		else if(m_mode==7)game=TheGameInfo;
		if(game) {
			for(int i=0;i<(int)reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->m_players.size();++i) {
				LivingWorldPlayer *player=reinterpret_cast<LivingWorldPlayer*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->GetPlayerAtIndex(i));
				GameSlot * slot = 0;
				for(int j=0;j<8;++j) {
					if(game->getSlot(j)->getTemplate()==player->m_template) {slot=game->getSlot(j);break;}
				}
				if(TheGameSpyGame && reinterpret_cast<Rva002E0687*>(player)->rva002E0687() && m_mode==7) {
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
	if(m_mode==1||m_mode==6||m_mode==7)AptScoreScreen::PreCollectGameData(reinterpret_cast<Rva0051C0E7*>(m_extra));
	CollectAllPlayerData();
}
