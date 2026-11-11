// Rva00463235: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00463235_H
#define CANONICAL_RVA00463235_H

class AsciiString;
class Thing;

class Rva00463235
{
public:
	AsciiString rva00463235(Thing *thing);
};

#endif // CANONICAL_RVA00463235_H
