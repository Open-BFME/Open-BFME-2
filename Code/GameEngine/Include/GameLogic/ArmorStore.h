// ArmorStore: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_ARMORSTORE_H
#define CANONICAL_ARMORSTORE_H

class Armor;
class ArmorTemplate;
class AsciiString;

class ArmorStore
{
public:
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;
	Armor makeArmor(const AsciiString &name) const;
	const ArmorTemplate *rva0041F474(const AsciiString &name) const;
};

#endif // CANONICAL_ARMORSTORE_H
