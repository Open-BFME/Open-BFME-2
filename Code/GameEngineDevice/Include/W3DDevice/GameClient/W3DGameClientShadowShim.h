// W3DGameClientShadowShim: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DGAMECLIENTSHADOWSHIM_H
#define CANONICAL_W3DGAMECLIENTSHADOWSHIM_H

class W3DGameClientShadowShim
{
public:
	void setLightPosition(int lightIndex, float x, float y, float z);
};

#endif // CANONICAL_W3DGAMECLIENTSHADOWSHIM_H
