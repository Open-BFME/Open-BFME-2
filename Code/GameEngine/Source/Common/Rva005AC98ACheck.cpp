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

class PlayerList
{
public:
	Player *getNthPlayer(int index);
	char m_pad[0x14];
	unsigned int m_count;
};

class Player
{
public:
	Relationship getRelationship(const Player *other) const;
	bool rva002AB87D(const UpgradeTemplate *upgrade) const;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern PlayerList *ThePlayerList;
extern "C" UpgradeCenter *TheUpgradeCenter;

class AIRingHeroTactic
{
public:
	bool enemyHasRingHeroUpgrade();
private:
	char m_pad[0x24];
	Player *m_player;
	char m_pad2[0x5C - 0x24 - 4];
	Player *m_cur;
};

bool AIRingHeroTactic::enemyHasRingHeroUpgrade()
{
	unsigned int count = ThePlayerList->m_count;
	for (unsigned int i = 0; i < count; ++i)
	{
		Player *p = ThePlayerList->getNthPlayer(i);
		m_cur = p;
		if (p == m_player)
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
