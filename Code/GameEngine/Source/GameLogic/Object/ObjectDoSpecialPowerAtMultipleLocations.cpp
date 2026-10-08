// cl: /O1 /DNDEBUG /MD
//
// Object::doSpecialPowerAtMultipleLocations, retail 0x0028E151 (91B), from the
// WorldBuilder lead (Object.cpp) and Zero Hour's Object.cpp: a disabled object
// (BitFlags<11> disabled mask at +0x1C8) does nothing; unless forced, the
// special power store (TheSpecialPowerStore 0x00E02D4C, 0x003B1244) must allow
// the power; then the object's module for the template does the power at the
// locations (module vtable slot 0x34). BFME2 replaces Zero Hour's academy
// bookkeeping with the rowed Object 0x0028C4B6 before the module call.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

template <int NUMBITS> class BitFlags
{
public:
	Bool any() const;

private:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

class SpecialPowerTemplate;
class Object;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void doSpecialPowerAtMultipleLocations(const Coord3D *locations, Int locCount, UnsignedInt commandOptions); // 0x34
};

class SpecialPowerStore
{
public:
	Bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *spTemplate);
};
extern SpecialPowerStore *TheSpecialPowerStore;

class Object
{
public:
	void doSpecialPowerAtMultipleLocations(const SpecialPowerTemplate *spTemplate,
		const Coord3D *locations, Int locCount, UnsignedInt commandOptions, Bool forced);
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *spTemplate) const;
	void rva0028C4B6();
	Bool isDisabled() const { return m_disabledMask.any(); }

private:
	unsigned char m_pad00[0x1C8];
	BitFlags<11> m_disabledMask;
};

void Object::doSpecialPowerAtMultipleLocations(const SpecialPowerTemplate *spTemplate,
	const Coord3D *locations, Int locCount, UnsignedInt commandOptions, Bool forced)
{
	if (isDisabled())
		return;
	if (!forced && !TheSpecialPowerStore->canUseSpecialPower(this, spTemplate))
		return;
	SpecialPowerModuleInterface *mod = getSpecialPowerModule(spTemplate);
	if (mod)
	{
		rva0028C4B6();
		mod->doSpecialPowerAtMultipleLocations(locations, locCount, commandOptions);
	}
}
