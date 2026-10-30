// cl: /MD
// ?getCostPerTick@AIUpgrade@@UAEMPAX@Z @0x00597476 86B: slot8 cost ratio via UpgradeTemplate calcCostToBuild and rva0026EE30 with idiv and fild; vtable 0x00870BD0
#include "GameLogicObjectLookupView.h"

class CommandButton;
class AsciiString;
class Object
{
public:
	void doCommandButton(const CommandButton *commandButton, int cmdSource, bool flags);
	void *rva0028BC58(int which);
	const AsciiString *rva00290E67() const;
	char m_pad00[0x4];
};


extern GameLogic *TheGameLogic;

class Player;
class UpgradeTemplate
{
public:
	unsigned int calcCostToBuild(Player *p, unsigned int u) const;
	int rva0026EE30(void *a, void *b);
};

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
	Object *object = TheGameLogic->findObjectByID(m_08);
	unsigned int cost = upgradeTemplate->calcCostToBuild((Player *)p, (unsigned int)object);
	Object *o2 = TheGameLogic->findObjectByID(m_08);
	int denom = upgradeTemplate->rva0026EE30(p, o2);
	int quot = (int)cost / denom;
	float f = (float)quot;
	return f;
}
