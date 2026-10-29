// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BB1A4Grant@ScriptActions@@QAEXABVAsciiString@@0@Z, retail 0x003BB1A4, 91 bytes.
// Grant upgrade to players matching name mask.
// Evidence: leaf lane; callees ScriptEngine rva00357475 getEachPlayerFromMask findUpgrade Player addUpgrade; caller 0x003CA957.
#include "ascii_string.h"
#include "../../Common/RTS/PlayerUpgradeStatus.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern class ScriptEngine *TheScriptEngine;
class Player;
class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
class UpgradeTemplate
{
public:
	char m_pad00[4];
	int m_val04;
};
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;
class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *tpl, UpgradeStatusType a2, int a3);
};
void ScriptActions::Rva003BB1A4Grant(const AsciiString &playerName, const AsciiString &upgradeName)
{
	int mask = TheScriptEngine->rva00357475(playerName, 0);
	if (mask == 0)
		return;
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player != 0) {
			const UpgradeTemplate *tpl = TheUpgradeCenter->findUpgrade(upgradeName);
			if (tpl->m_val04 == 0)
				player->addUpgrade(tpl, UPGRADE_STATUS_COMPLETE, 0);
		}
	}
}
