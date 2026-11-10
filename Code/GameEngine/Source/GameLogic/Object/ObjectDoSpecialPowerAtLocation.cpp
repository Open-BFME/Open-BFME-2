// cl: /O1 /DNDEBUG /MD
// Object::doSpecialPowerAtLocation, retail 0x0028E0F9 (88 bytes):
// ?doSpecialPowerAtLocation@Object@@QAEXPBVSpecialPowerTemplate@@PBUCoord3D@@I_N@Z
// Identity (target): WorldBuilder's debug Object.cpp
// Object::doSpecialPowerAtLocation calls, in retail's order, the disabled
// mask test (BitFlags<11>::any on +0x1C8),
// SpecialPowerStore::canUseSpecialPower (0x003B1244),
// Object::getSpecialPowerModule (0x0028BB9E), Object::rva0028C4B6 and the
// module's virtual slot 0x30.
// Donor (Zero Hour Object::doSpecialPowerAtLocation): nothing while
// disabled; scripts may force a power the object cannot otherwise use; the
// object's module for the template does the work. BFME 2 delta (target):
// the module call takes (location, options) without an angle, after the
// rowed Object::rva0028C4B6.
class SpecialPowerTemplate;
class Object;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Include/Common/BitFlagsTemplate.h"

typedef BitFlags<11> DisabledMaskType;

class SpecialPowerStore
{
public:
	bool canUseSpecialPower(Object*,const SpecialPowerTemplate*);
};

extern SpecialPowerStore *TheSpecialPowerStore;

#include "../../../Include/GameLogic/Module/SpecialPowerModule.h"

class Object
{
public:
	void doSpecialPowerAtLocation(const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc,
		unsigned int commandOptions, bool forceUsable);
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
	void rva0028C4B6();

private:
	unsigned char m_pad000[0x1C8];
	DisabledMaskType m_disabledMask; // +0x1C8
};

void Object::doSpecialPowerAtLocation(const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc, unsigned int commandOptions, bool forceUsable)
{
	if (m_disabledMask.any())
		return;
	if (!forceUsable && !TheSpecialPowerStore->canUseSpecialPower(this, specialPowerTemplate))
		return;
	SpecialPowerModuleInterface *mod = getSpecialPowerModule(specialPowerTemplate);
	if (mod)
	{
		rva0028C4B6();
		mod->doSpecialPowerAtLocation(loc, commandOptions);
	}
}
