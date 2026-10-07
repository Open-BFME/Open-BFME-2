// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE /G7
// ?rva0021B3FA@Rva0021B3FA@@QAEXXZ @0x0021B3FA 122B.
// Grant upgrade named at +0x190 to each player whose slot is found and set.
// Evidence: chain from 0x0021B37A Find plus caller 0x00248558; getNthPlayer row plus Find row plus isEmpty row plus findUpgrade row plus Player rva002AE329 row; prev Find and next GetHeroForPlayer same ascii flags.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

class GameSlot
{
public:
	char m_pad00[0x34];
	AsciiString m_name34;
	char m_pad38[0x50 - 0x38];
	Int m_50;
};

class Player;
class UpgradeTemplate;
class Upgrade;

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int i);
	unsigned char m_pad[0x14];
	Int m_playerCount;
};

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x);
};

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
		if (slot->m_50 == 0)
			continue;
		if (((const StringBase<char> *)&m_str190)->isEmpty())
			continue;
		const UpgradeTemplate *tmpl = TheUpgradeCenter->findUpgrade(m_str190);
		player->rva002AE329(tmpl, UPGRADE_STATUS_COMPLETE, 1);
	}
}
