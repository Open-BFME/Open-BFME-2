// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// AIRingHeroTactic::enemyHasRingHeroUpgrade retail 0x005AC98A 158B (WorldBuilder
// name; same getNthPlayer walk, findUpgrade, getRelationship, upgrade test)
// Evidence: unlock lane; loops ThePlayerList players skipping m_player; finds Upgrade_RingHero via TheUpgradeCenter and checks enemy relationship plus Player::rva002AB87D; returns al 0/1 so bool; ecx combos plus [esi+0x24]/[esi+0x5c] Player slots.
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include "../../Include/Common/AITactic.h"
#include "../../Include/Common/AITacticOffensive.h"

class Player;
class PlayerList;
class UpgradeCenter;
class UpgradeTemplate;

enum Relationship
{
	REL_0 = 0
};

#include "../../Include/Common/PlayerList.h"

#include "../../Include/Common/Player.h"

#include "../../Include/Common/Upgrade.h"

extern PlayerList *ThePlayerList;
extern UpgradeCenter *TheUpgradeCenter;

class AIRingHeroTactic : public AITacticOffensive
{
public:
	virtual ~AIRingHeroTactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual bool initializeTeamTemplate(void *unit, int count);
	virtual void run();
	virtual void update();
	bool weHaveGollum();
	bool rva005ACA92();
	bool enemyHasRingHeroUpgrade();
	bool rva005ACA28();
private:
	ObjectID m_hero;	// +0x58
	Player *m_5C;		// +0x5C
	bool m_escorting;	// +0x60
	unsigned char m_pad61[3];
	Object *m_escort;	// +0x64
};

bool AIRingHeroTactic::enemyHasRingHeroUpgrade()
{
	unsigned int count = ThePlayerList->m_playerCount;
	for (unsigned int i = 0; i < count; ++i)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		m_5C = player;
		if (player == (Player *)m_field24)
			continue;
		const UpgradeTemplate *upgrade;
		{
			AsciiString name("Upgrade_RingHero");
			upgrade = TheUpgradeCenter->findUpgrade(name);
		}
		if (((Player *)m_field24)->getRelationship(m_5C) != 0)
			continue;
		if (m_5C->rva002AB87D(upgrade))
			return true;
	}
	m_5C = 0;
	return false;
}

// 0x005ACA28 5B, directly after the body it enters (tail jump into enemyHasRingHeroUpgrade); no referencing site found in
// this pass; address-named.
bool AIRingHeroTactic::rva005ACA28()
{
	return enemyHasRingHeroUpgrade();
}
