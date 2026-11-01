// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE /G7
// ?rva0021B3FA@Rva0021B3FA@@QAEXXZ @0x0021B3FA 122B.
// Grant upgrade named at +0x190 to each player whose slot is found and set.
// Evidence: chain from 0x0021B37A Find plus caller 0x00248558; getNthPlayer row plus Find row plus isEmpty row plus findUpgrade row plus Player addUpgrade row; prev Find and next GetHeroForPlayer same ascii flags.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../../Include/GameNetwork/GameInfo.h"

class Player;
class UpgradeTemplate;
class Upgrade;

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

#include "../../../Include/Common/Upgrade.h"

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
	unsigned char m_pad[0x14];
	Int m_playerCount;
};

#include "../../../Include/Common/Player.h"

class GameInfo;

extern GameInfo *TheGameInfo;
extern PlayerList *ThePlayerList;
extern UpgradeCenter *TheUpgradeCenter;

GameSlot *Rva0021B37AFind(const Player *player);

class Rva0021B3FA
{
public:
	void rva0021B3FA();

private:
	char m_pad00[0x190];
	AsciiString m_str190;
};

// ?rva0021B3FA@Rva0021B3FA@@QAEXXZ
void Rva0021B3FA::rva0021B3FA()
{
	if (TheGameInfo == 0)
		return;
	for (UnsignedInt i = 0; i < (UnsignedInt)ThePlayerList->m_playerCount; ++i)
	{
		Player *player = ThePlayerList->getNthPlayer((Int)i);
		if (player == 0)
			continue;
		GameSlot *slot = Rva0021B37AFind(player);
		if (slot == 0)
			continue;
		if (slot->m_field50 == 0)
			continue;
		if (((const StringBase<char> *)&m_str190)->isEmpty())
			continue;
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade(m_str190);
		player->addUpgrade(upgradeTemplate, UPGRADE_STATUS_COMPLETE, 1);
	}
}
