// cl: /O1 /DNDEBUG /MD
//
// Object::goDownOnCorpse, retail 0x002922A9 (48B), from the WorldBuilder lead
// (Object.cpp; its "missing the appropriate special power" debug message at
// line 9012 is compiled out of retail): find the special power module of
// type 0x8B and do that module's power (interface slot 6, its template) at
// the corpse's position (Object +0x38) with options 2, not forced, through
// Object::doSpecialPowerAtLocation (0x0028E0F9, its rowed signature).

#include "../../../../Libraries/Include/Lib/Coord3D.h"

enum SpecialPowerType
{
	SPECIAL_POWER_0x8B = 0x8B
};

#include "../../../Include/GameLogic/Module/SpecialPowerModule.h"

class Object
{
public:
	void goDownOnCorpse(Object *corpse);
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(SpecialPowerType type) const;
	void doSpecialPowerAtLocation(const SpecialPowerTemplate *spTemplate, const Coord3D *loc, unsigned int commandOptions, bool forced);
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

void Object::goDownOnCorpse(Object *corpse)
{
	SpecialPowerModuleInterface *sp = findSpecialPowerModuleInterface(SPECIAL_POWER_0x8B);
	if (sp)
		doSpecialPowerAtLocation(sp->getSpecialPowerTemplate(), corpse->getPosition(), 2, false);
}
