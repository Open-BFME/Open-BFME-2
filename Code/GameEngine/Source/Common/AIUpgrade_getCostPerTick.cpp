// cl: /MD
// ?getCostPerTick@AIUpgrade@@UAEMPAX@Z @0x00597476 86B: slot8 cost ratio via UpgradeTemplate calcCostToBuild and rva0026EE30 with idiv and fild; vtable 0x00870BD0
#include "GameLogicObjectLookupView.h"

#include "../../Include/GameClient/CommandButton.h"
#include "../GameLogic/Object/object.h"


extern GameLogic *TheGameLogic;

class Player;
#include "../../Include/Common/Upgrade.h"

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void Rva0055AED6(Xfer *x, void *p);
	float m_04; // +0x04
	ObjectID m_builderID; // +0x08
	AsciiString m_0C; // +0x0C
	int m_remaining10; // +0x10
	char m_pad14[0x4];
	float m_18; // +0x18
	char m_pad1C[0x4];
	bool m_20; // +0x20
	bool m_21; // +0x21
	char m_pad22[0x2];
	ObjectID m_24; // +0x24
	bool m_28; // +0x28
	char m_pad29[0x3];
};

// Table 0x00870BD0 places getCostPerTick at slot 8, DoXfer at slot 12 and
// build at slot 15; the base slots between them are not recovered, so the
// declaration order states no slot positions.
class AIUpgrade : public Rva0055B0CC
{
public:
	AIUpgrade();
	virtual ~AIUpgrade();
	virtual float getCostPerTick(void *p);
	virtual void DoXfer(Xfer *x, void *p);
	virtual bool build(void *context);
	int rva005973D8();
	void rva005975C0();
	int m_2C; // +0x2C
	const CommandButton *m_commandButton; // +0x30
};

float AIUpgrade::getCostPerTick(void *p)
{
	UpgradeTemplate *upgradeTemplate = const_cast<UpgradeTemplate *>(m_commandButton->getUpgradeTemplate());
	Object *costObject = TheGameLogic->findObjectByID(m_builderID);
	unsigned int cost = upgradeTemplate->calcCostToBuild((Player *)p, (unsigned int)costObject);
	Object *divisorObject = TheGameLogic->findObjectByID(m_builderID);
	int costDivisor = upgradeTemplate->rva0026EE30(p, divisorObject);
	int integerCostPerTick = (int)cost / costDivisor;
	float costPerTick = (float)integerCostPerTick;
	return costPerTick;
}
