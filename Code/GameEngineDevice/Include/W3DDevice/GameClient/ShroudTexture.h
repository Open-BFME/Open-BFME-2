// ShroudTexture: canonical declarations for the members 19 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_SHROUDTEXTURE_H
#define CANONICAL_SHROUDTEXTURE_H

class ShroudFilter;

class ShroudTexture
{
public:
	ShroudFilter *getFilter();
};

#endif // CANONICAL_SHROUDTEXTURE_H
