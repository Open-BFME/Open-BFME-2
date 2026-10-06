// cl: /MD
// ?getCostPerTick@AIUpgrade@@UAEMPAX@Z @0x00597476 86B: slot8 cost ratio via UpgradeTemplate calcCostToBuild and rva0026EE30 with idiv and fild; vtable 0x00870BD0
enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	char m_pad[4];
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
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
	UpgradeTemplate *tmpl = m_30->m_24;
	Object *o1 = TheGameLogic->findObjectByID(m_08);
	unsigned int cost = tmpl->calcCostToBuild((Player *)p, (unsigned int)o1);
	Object *o2 = TheGameLogic->findObjectByID(m_08);
	int denom = tmpl->rva0026EE30(p, o2);
	int quot = (int)cost / denom;
	float f = (float)quot;
	return f;
}
