// Rva00358752Opaque: canonical declarations for the members 22 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00358752OPAQUE_H
#define CANONICAL_RVA00358752OPAQUE_H

class AsciiString;
class Object;

class Rva00358752Opaque
{
public:
	Object *lookupUnitByValue(AsciiString name);
};

#endif // CANONICAL_RVA00358752OPAQUE_H
