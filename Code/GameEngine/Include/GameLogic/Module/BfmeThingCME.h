// BfmeThingCME: canonical declarations for the members 16 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMETHINGCME_H
#define CANONICAL_BFMETHINGCME_H

struct Coord3D;
class PolygonTrigger;

class BfmeThingCME
{
public:
	int bfmeGoCME(void *what);
	int rva0027F108(void *pos, float radius, int a, int b);
	int rva0027F171(PolygonTrigger *trigger);
	void rva0027F1DD(Coord3D *position, float radius);
	void rva0027F2B2(Coord3D *center, float radius, unsigned char value);
};

#endif // CANONICAL_BFMETHINGCME_H
