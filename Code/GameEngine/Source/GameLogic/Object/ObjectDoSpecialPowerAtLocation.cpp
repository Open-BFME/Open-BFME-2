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

template <int NUMBITS>
class BitFlags
{
public:
	bool any() const;

private:
	unsigned int m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<11> DisabledMaskType;

class SpecialPowerStore
{
public:
	bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *specialPowerTemplate);
};

extern SpecialPowerStore *TheSpecialPowerStore;

class SpecialPowerModuleInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void doSpecialPowerAtLocation(const Coord3D *loc, unsigned int commandOptions); // slot 0x30
};

class Object
{
public:
	void doSpecialPowerAtLocation(const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc,
		unsigned int commandOptions, bool forceUsable);
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *specialPowerTemplate) const;
	void rva0028C4B6();
	bool isDisabled() const { return m_disabledMask.any(); }

private:
	unsigned char m_pad000[0x1C8];
	DisabledMaskType m_disabledMask; // +0x1C8
};

void Object::doSpecialPowerAtLocation(const SpecialPowerTemplate *specialPowerTemplate, const Coord3D *loc, unsigned int commandOptions, bool forceUsable)
{
	if (isDisabled())
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
