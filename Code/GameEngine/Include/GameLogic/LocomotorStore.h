// LocomotorStore: canonical declarations for the members 13 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LOCOMOTORSTORE_H
#define CANONICAL_LOCOMOTORSTORE_H

class AsciiString;
class Locomotor;
class LocomotorTemplate;

class LocomotorStore
{
public:
	~LocomotorStore();
	LocomotorTemplate *findLocomotorTemplate(const AsciiString &name);
	LocomotorTemplate *findLocomotorTemplate(int key);
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl, bool flag);
	LocomotorTemplate *newOverride(LocomotorTemplate *original);
};

#endif // CANONICAL_LOCOMOTORSTORE_H
