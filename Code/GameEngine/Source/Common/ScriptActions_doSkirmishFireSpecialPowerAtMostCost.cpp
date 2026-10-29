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

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	char m_pad[0x54];
	float m_54;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};

extern PlayerList *ThePlayerList;

class Player
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual bool v04(const SpecialPowerTemplate *tmpl, void *out, void *unk, float f);
};

class ScriptActions
{
public:
	void doSkirmishFireSpecialPowerAtMostCost(const AsciiString &a, const AsciiString &b);
	bool FireSpecialPowerAtPosition(const AsciiString &playerName,
		const SpecialPowerTemplate *power, const Coord3D *position) throw();
};

void ScriptActions::doSkirmishFireSpecialPowerAtMostCost(const AsciiString &asciiString, const AsciiString &b)
{
	Player *enemy = TheScriptEngine->getSkirmishEnemyPlayer();
	if (enemy == 0)
		return;
	void *unk54 = *(void **)((char *)enemy + 0x54);
	const SpecialPowerTemplate *specialPowerTemplate = TheSpecialPowerStore->findSpecialPowerTemplate(b);
	if (specialPowerTemplate == 0)
		return;
	float f = 50.0f;
	const Overridable *ov = ((const Overridable *)specialPowerTemplate)->friend_getFinalOverride();
	float g = ov->m_54;
	if (g > 50.0f) {
		ov = ((const Overridable *)specialPowerTemplate)->friend_getFinalOverride();
		f = ov->m_54;
	}
	int mask = TheScriptEngine->rva00357475(asciiString, 0);
	if (mask == 0)
		return;
	Player *player;
	do {
		player = ThePlayerList->getEachPlayerFromMask(mask);
		if (player != 0) {
			char out[12];
			player->v04(specialPowerTemplate, out, unk54, f);
			if (FireSpecialPowerAtPosition(asciiString, specialPowerTemplate, (const Coord3D *)out))
				return;
		}
	} while (mask != 0);
}
