// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// Retail 0x0035B0F0 (34 bytes, RET 4), between the rowed CommandButton
// isValidObjectTarget overloads: look the button's special power template
// (+0x44, as CommandButton::isReady 0x0035B069 reads it) up on the source
// object through the rowed Object::getSpecialPowerModule 0x0028BB9E and
// return the module's vslot 2 (getPercentReady in Zero Hour's interface),
// or -1.0 when the object has no such module. The method's original name is
// not established; it is address-derived.
typedef float Real;

class SpecialPowerTemplate;

class SpecialPowerModuleInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual Real getPercentReady() const = 0; // vslot 2
};

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

#include "../../../../Include/GameClient/CommandButton.h"

Real CommandButton::getSpecialPowerPercentReady(const Object *obj) const
{
	SpecialPowerModuleInterface *module = obj->getSpecialPowerModule(m_specialPower);
	if (module == 0)
		return -1.0f;
	return module->getPercentReady();
}
