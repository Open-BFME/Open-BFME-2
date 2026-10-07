// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
#include "ascii_string.h"
// CreateAHeroManager::UnbindHeroFromObjectAndUpdate, retail 0x00219757, 79
// bytes (WorldBuilder name; WB's body asserts the object, tests the same
// KindOf bit, then findUpgrade(this+0x190) and the player call with 2, 1).
// Leaf: grants upgrade from this+0x190 AsciiString via UpgradeCenter to
// controlling player when Object+4 flag 0x11F has 0x40 and globals allow.
// Evidence: rowed getControllingPlayer 0x0028AFA9 and findUpgrade 0x0026F26D
// plus pin Player::rva002AE329 and callers at 0x0029856F.

#include "RTS/PlayerUpgradeStatus.h"

class UpgradeTemplate;
class Player;
class GameInfo;
extern GameInfo *TheGameInfo;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

class ObjectP04Flags00219757
{
public:
	unsigned char m_pad[0x11F];
	unsigned char m_flag11F;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad0[4];
	ObjectP04Flags00219757 *m_p04;
};

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *upgrade, UpgradeStatusType a, int b);
};

class CreateAHeroManager
{
public:
	void UnbindHeroFromObjectAndUpdate(Object *obj);
private:
	unsigned char m_pad[0x190];
	AsciiString m_upgrade;
};

void CreateAHeroManager::UnbindHeroFromObjectAndUpdate(Object *obj)
{
	if (!obj)
		return;
	if ((obj->m_p04->m_flag11F & 0x40) == 0)
		return;
	if (TheGameInfo == 0)
		return;
	Player *player = obj->getControllingPlayer();
	if (!player)
		return;
	const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_upgrade);
	player->rva002AE329(upgrade, UPGRADE_STATUS_COMPLETE, 1);
}
