// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// AIBuildableUnit.cpp -- AIBuildableUnit members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names each function
// (constructor, and canMake/build by vtable pairing); retail supplies the
// bytes.
//
// Layout (target evidence): factory object id at +0x08, unit template name at
// +0x0C, three floats at +0x2C..+0x34, two ints at +0x38/+0x3C, the
// constructor argument at +0x40; the base is the rowed Rva0055B0CC
// buildable (ctor 0x0055B048, virtual dtor). The factory's production
// interface comes from Object 0x0028BC58 (rowed under a placeholder name);
// the player's production-quantity table is at Player +0x738.
#include "ascii_string.h"
#include "../../../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

enum CanMakeType { CANMAKE_OK = 0, CANMAKE_NO_PREREQ, CANMAKE_NO_MONEY, CANMAKE_FACTORY_IS_DISABLED, CANMAKE_QUEUE_FULL };

class ThingTemplate;

class Object
{
public:
	void *rva0028BC58(Int which);			// 0x0028BC58, production update interface
};

class ProductionUpdateInterface
{
public:
	virtual Int queueSize() = 0;			// +0x00
	virtual void s01() = 0;
	virtual Int requestUniqueUnitID(Int a, Int b, Int *c, Int d) = 0;	// +0x08
	virtual void s03() = 0; virtual void s04() = 0; virtual void s05() = 0;
	virtual void s06() = 0; virtual void s07() = 0;
	virtual Bool queueCreateUnit(const ThingTemplate *unitType, Int quantity, Int productionID) = 0;	// +0x20
};

class Rva0037EE4C
{
public:
	Int rva0037EE4C(const ThingTemplate *unitType, Int a, Int b);	// 0x0037EE4C
};

class Player
{
public:
	unsigned char m_pad000[0x738];
	Rva0037EE4C m_productionQuantities;		// +0x738
};


extern GameLogic *TheGameLogic;

// Use the verified 2D06CA owner rather than a declaration with no definition.
// Its target payload is the template consumed by the production interface.
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};

extern Rva002D06CA *TheThingFactory;

class Rva00A027B8
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual CanMakeType canMakeUnit(Object *builder, const ThingTemplate *whatToBuild, Int quantity);	// +0x60
};

extern Rva00A027B8 *g_00A027B8;	// Existing typed data owner at VA 0x00E027B8

class Rva0055B0CC
{
public:
	Rva0055B0CC();					// 0x0055B048
	virtual ~Rva0055B0CC();				// 0x0055B0CC

protected:
	unsigned char m_pad04[4];
	ObjectID m_factoryID;				// +0x08
	AsciiString m_templateName;			// +0x0C
	unsigned char m_pad10[0x2c - 0x10];
};

struct AIBuildableVector
{
	AIBuildableVector() : x(0.0f), y(0.0f), z(0.0f) {}

	Real x, y, z;
};

class AIBuildableUnit : public Rva0055B0CC
{
public:
	AIBuildableUnit(Int arg);
	virtual CanMakeType canMake(Player *player);
	virtual Bool build(Player *player);

private:
	AIBuildableVector m_2C;				// +0x2C
	Int m_38;					// +0x38
	Int m_productionID;				// +0x3C
	Int m_40;					// +0x40
};

// AIBuildableUnit::AIBuildableUnit, retail 0x005DAC38.
AIBuildableUnit::AIBuildableUnit(Int arg)
	: m_38(0), m_productionID(0), m_40(arg)
{
}

// AIBuildableUnit::build, retail 0x005DADED.
Bool AIBuildableUnit::build(Player *player)
{
	Object *factory = TheGameLogic->findObjectByID(m_factoryID);
	const ThingTemplate *unitType = (const ThingTemplate *)TheThingFactory->rva002D06CA(&m_templateName);
	if (factory == 0 || unitType == 0)
		return false;
	ProductionUpdateInterface *pui = (ProductionUpdateInterface *)factory->rva0028BC58(0);
	if (pui == 0)
		return false;
	Int quantity = player->m_productionQuantities.rva0037EE4C(unitType, -1, 0);
	return pui->queueCreateUnit(unitType, quantity, pui->requestUniqueUnitID(-1, 0, &m_productionID, 0));
}

// AIBuildableUnit::canMake, retail 0x005DAE6F.
CanMakeType AIBuildableUnit::canMake(Player *player)
{
	Object *factory = TheGameLogic->findObjectByID(m_factoryID);
	if (factory)
	{
		ProductionUpdateInterface *pui = (ProductionUpdateInterface *)factory->rva0028BC58(0);
		if (pui && pui->queueSize() == 0)
		{
			const ThingTemplate *unitType = (const ThingTemplate *)TheThingFactory->rva002D06CA(&m_templateName);
			Int quantity = player->m_productionQuantities.rva0037EE4C(unitType, -1, 0);
			return g_00A027B8->canMakeUnit(factory, unitType, quantity);
		}
		return CANMAKE_QUEUE_FULL;
	}
	return CANMAKE_FACTORY_IS_DISABLED;
}
