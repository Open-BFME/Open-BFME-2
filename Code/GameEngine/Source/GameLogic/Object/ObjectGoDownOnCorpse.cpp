// cl: /O1 /DNDEBUG /MD
//
// Object::goDownOnCorpse, retail 0x002922A9 (48B), from the WorldBuilder lead
// (Object.cpp; its "missing the appropriate special power" debug message at
// line 9012 is compiled out of retail): find the special power module of
// type 0x8B and hand what its vtable slot 0x18 builds for the corpse's
// position (Object +0x38; with 2 and 0) to Object::doSpecialPowerAtLocation
// (WorldBuilder's name for 0x0028E0F9, which takes that one pointer here).
//
// Target facts: the slot's parameter and result types are not established;
// the result is passed through opaquely.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum SpecialPowerType
{
	SPECIAL_POWER_0x8B = 0x8B
};

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void *rva002922A9Slot18(const Coord3D *pos, int a, int b); // slot 0x18
};

class Object
{
public:
	void goDownOnCorpse(Object *corpse);
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
	void doSpecialPowerAtLocation(void *command);
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

void Object::goDownOnCorpse(Object *corpse)
{
	SpecialPowerModuleInterface *sp = findSpecialPowerModuleInterface(SPECIAL_POWER_0x8B);
	if (sp)
		doSpecialPowerAtLocation(sp->rva002922A9Slot18(corpse->getPosition(), 2, 0));
}
