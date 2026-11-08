// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x003C4070 (RVA 0x003C4070) size 213: ScriptActions skirmish power sweep.
// Evidence: ScriptEngine 0xDFE16C getSkirmishEnemyPlayer then SpecialPowerStore 0xE02D4C findSpecialPowerTemplate then Overridable 0x54 range vs 50.0f then PlayerList mask loop then Player vtable+0x10 then ScriptActions::FireSpecialPowerAtPosition 0x3C069B (WB callgraph caller of it).
#include "ascii_string.h"

class Player;
class Object;
class SpecialPowerTemplate;
struct Coord3D;

#include "../../Include/GameLogic/ScriptEngine.h"

extern class ScriptEngine *TheScriptEngine;

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

extern SpecialPowerStore *TheSpecialPowerStore;

#include "../../Include/Common/Overridable.h"
#include "../../Include/Common/SpecialPower.h"

#include "../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

#include "../../Include/Common/Player.h"

class ScriptActions
{
public:
	void doSkirmishFireSpecialPowerAtMostCost(const AsciiString &a, const AsciiString &powerName);
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();
};

void ScriptActions::doSkirmishFireSpecialPowerAtMostCost(const AsciiString &asciiString, const AsciiString &powerName)
{
	Player *enemy = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemy == 0)
		return;
	int unk54 = enemy->m_playerIndex;
	const SpecialPowerTemplate *specialPowerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate(powerName);
	if (specialPowerTemplate == 0)
		return;
	float costLimit = 50.0f;
	const SpecialPowerTemplate *ov = (const SpecialPowerTemplate *)specialPowerTemplate->friend_getFinalOverride();
	float g = ov->m_radiusCursorRadius;
	if (g > 50.0f) {
		ov = (const SpecialPowerTemplate *)specialPowerTemplate->friend_getFinalOverride();
		costLimit = ov->m_radiusCursorRadius;
	}
	int mask = TheScriptEngine->rva00357475(asciiString, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player != 0) {
			char out[12];
			player->computeSuperweaponTarget(specialPowerTemplate, (Coord3D *)out, unk54, costLimit);
			if (FireSpecialPowerAtPosition(asciiString, specialPowerTemplate, (const Coord3D *)out))
				return;
		}
	} while (mask != 0);
}
