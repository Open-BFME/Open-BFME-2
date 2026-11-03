// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// AIRingHeroTactic::enemyHasRingHeroUpgrade retail 0x005AC98A 158B (WorldBuilder
// name; same getNthPlayer walk, findUpgrade, getRelationship, upgrade test)
// Evidence: unlock lane; loops ThePlayerList players skipping m_player; finds Upgrade_RingHero via TheUpgradeCenter and checks enemy relationship plus Player::rva002AB87D; returns al 0/1 so bool; ecx combos plus [esi+0x24]/[esi+0x5c] Player slots.
#include "ascii_string.h"

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

class AIRingHeroTactic
{
public:
	bool enemyHasRingHeroUpgrade();
	bool rva005ACA28();
private:
	char m_pad[0x24];
	Player *m_player;
	char m_pad2[0x5C - 0x24 - 4];
	Player *m_cur;
};

bool AIRingHeroTactic::enemyHasRingHeroUpgrade()
{
	unsigned int count = ThePlayerList->m_playerCount;
	for (unsigned int i = 0; i < count; ++i)
	{
		Player *player = ThePlayerList->getNthPlayer(i);
		m_cur = player;
		if (player == m_player)
			continue;
		const UpgradeTemplate *upgrade;
		{
			AsciiString name("Upgrade_RingHero");
			upgrade = TheUpgradeCenter->findUpgrade(name);
		}
		if (m_player->getRelationship(m_cur) != 0)
			continue;
		if (m_cur->rva002AB87D(upgrade))
			return true;
	}
	m_cur = 0;
	return false;
}

// 0x005ACA28 5B, directly after the body it enters (tail jump into enemyHasRingHeroUpgrade); no referencing site found in
// this pass; address-named.
bool AIRingHeroTactic::rva005ACA28()
{
	return enemyHasRingHeroUpgrade();
}
