// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
//
// ?calcCostToBuild@UpgradeTemplate@@QBEIPAVPlayer@@I@Z, retail 0x0026EF50
// (315 bytes, RET 8; WB 0x00BE5950 names it). Zero Hour's
// UpgradeTemplate::calcCostToBuild with BFME 2's additions. An upgrade that
// names a build template (+0x7C) costs what that template costs the player
// (ThingTemplate 0x0033A69A with the upgrade's own cost +0x34). Otherwise the
// cost is +0x34, summed over the prerequisite upgrades (the vector at
// +0x1C/+0x20) that the requesting object accepts (its 0x0029439D interface,
// slot 43; a null object accepts all) for a player: each prerequisite is
// costed without player or object. A player-type upgrade (+0x04 == 1, +0x79
// clear) is scaled by 1 + the player's upgrade-discount change for its name
// (+0x08; Player 0x002ADC82), and under difficulty 3 (0x002A9BF2) the
// skirmish manager (0x00DFEEF8; 0x002A8AB1 over the player) takes the
// fraction of the cost its +0x850 float (capped at one) names off again. The
// second argument is the requesting Object, spelled as the pinned unsigned
// the rowed caller 0x00597476 passes it as.
#include "ascii_string.h"
#include <vector>
// stlport
// The resolved sub-upgrade vector is independently established by the matched
// friend_resolveSubUpgradeNames at 0x0026F8D6. Keeping its real vector helpers
// visible reproduces the native early tests without scheduling barriers.

class Player;
class Object;
class UpgradeTemplate;
class ThingTemplate;

#include "../../../Include/Common/ThingFactory.h"
extern ThingFactory *TheThingFactory;

#include "../../../Include/Common/ThingTemplate.h"

class ObjectUpgradeInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0A(); virtual void s0B();
	virtual void s0C(); virtual void s0D(); virtual void s0E(); virtual void s0F();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
	virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18(); virtual void s19(); virtual void s1A(); virtual void s1B();
	virtual void s1C(); virtual void s1D(); virtual void s1E(); virtual void s1F();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s2A();
	virtual bool acceptsUpgrade(const UpgradeTemplate *upgrade); // slot 43 (+0xAC)
};

class Object
{
public:
	void *rva0029439D(); // 0x0029439D
};

#include "../../../Include/Common/Rva002A9BF2.h"

#include "../../../Include/Common/Player.h"

struct Rva002A8AB1Record;

#include "../../../Include/GameLogic/Rva002A8F24.h"
extern Rva002A8F24 *TheSkirmishAIManager;

class UpgradeTemplate
{
public:
	unsigned int calcCostToBuild(Player *player, unsigned int requester) const;
private:
	char m_pad00[0x04];
	int m_type; // +0x04
	AsciiString m_name; // +0x08
	char m_pad0C[0x1C - 0x0C];
	_STL::vector<const UpgradeTemplate *> m_prerequisites;
	char m_pad28[0x34 - 0x28];
	int m_cost; // +0x34
	char m_pad38[0x79 - 0x38];
	bool m_noUpgradeDiscount; // +0x79
	char m_pad7A[0x7C - 0x7A];
	AsciiString m_buildTemplateName; // +0x7C
};

unsigned int UpgradeTemplate::calcCostToBuild(Player *player, unsigned int requester) const
{
	if (!m_buildTemplateName.isEmpty())
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_buildTemplateName);
		if (thingTemplate)
			return thingTemplate->rva0033A69A(player, (int)requester, m_cost);
	}

	int cost = m_cost;
	if (player == 0)
		return cost;

	Object *object = (Object *)requester;
	if (!m_prerequisites.empty())
	{
		cost = 0;
		for (_STL::vector<const UpgradeTemplate *>::const_iterator it = m_prerequisites.begin(); it != m_prerequisites.end(); ++it)
		{
			const UpgradeTemplate *prerequisite = *it;
			if (!object || !object->rva0029439D()
				|| ((ObjectUpgradeInterface *)object->rva0029439D())->acceptsUpgrade(prerequisite))
				cost += prerequisite->calcCostToBuild(0, 0);
		}
	}

	float multiplier = 1.0f;
	if (m_type == 1 && !m_noUpgradeDiscount)
		multiplier = player->getProductionCostChangeBasedOnUpgradeDiscount(m_name) + 1.0f;
	int scaled = (int)((float)cost * multiplier);

	if ((int)((Rva002A9BF2 *)player)->rva002A9BF2() == 3 && TheSkirmishAIManager->rva002A8AB1(player))
	{
		const float one = 1.0f;
		float change = TheSkirmishAIManager->field_850 < one ? TheSkirmishAIManager->field_850 : one;
		return (int)((1.0f - change) * (float)scaled);
	}
	return scaled;
}
