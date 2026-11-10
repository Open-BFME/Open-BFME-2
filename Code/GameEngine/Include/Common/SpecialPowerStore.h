// SpecialPowerStore: canonical declarations for the members 28 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SPECIALPOWERSTORE_H
#define CANONICAL_SPECIALPOWERSTORE_H

class AsciiString;
class INI;
class Object;
class SpecialPowerTemplate;

class SpecialPowerStore
{
public:
	bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *specialPowerTemplate);
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
	const SpecialPowerTemplate *findSpecialPowerTemplateByID(unsigned int id);
	static void parseSpecialPowerDefinition(INI *);
};

#endif // CANONICAL_SPECIALPOWERSTORE_H
