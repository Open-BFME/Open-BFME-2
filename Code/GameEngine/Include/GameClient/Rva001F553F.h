// Rva001F553F: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA001F553F_H
#define CANONICAL_RVA001F553F_H

struct Coord3D;

class Rva001F553F
{
public:
	float rva001F534C();
	float rva001F53CE();
	float rva001F5401();
	float rva001F5423();
	float rva001F5445();
	Coord3D *rva001F553F(Coord3D *result, unsigned int a, unsigned int b);
};

#endif // CANONICAL_RVA001F553F_H
