// cl: /MD
// ?getCostPerTick@AIUpgrade@@UAEMPAX@Z @0x00597476 86B: slot8 cost ratio via UpgradeTemplate calcCostToBuild and rva0026EE30 with idiv and fild; vtable 0x00870BD0
#include "GameLogicObjectLookupView.h"

class CommandButton;
class AsciiString;
#include "../GameLogic/Object/object.h"


extern GameLogic *TheGameLogic;

class Player;
#include "../../Include/Common/Upgrade.h"

class Holder
{
public:
	char m_pad00[0x24];
	UpgradeTemplate *m_24;
};

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
protected:
	float m_04;
	ObjectID m_08;
	char m_pad0c[0x2c - 0x0c];
};

class AIUpgrade : public Rva0055B0CC
{
public:
	virtual float getCostPerTick(void *p);
private:
	int m_2C;
	Holder *m_30;
};

float AIUpgrade::getCostPerTick(void *p)
{
	UpgradeTemplate *upgradeTemplate = m_30->m_24;
	Object *costObject = TheGameLogic->findObjectByID(m_08);
	unsigned int cost = upgradeTemplate->calcCostToBuild((Player *)p, (unsigned int)costObject);
	Object *divisorObject = TheGameLogic->findObjectByID(m_08);
	int costDivisor = upgradeTemplate->rva0026EE30(p, divisorObject);
	int integerCostPerTick = (int)cost / costDivisor;
	float costPerTick = (float)integerCostPerTick;
	return costPerTick;
}
