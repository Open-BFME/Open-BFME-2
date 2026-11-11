// AnimationAsset: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_ANIMATIONASSET_H
#define CANONICAL_ANIMATIONASSET_H

class HAnimClass;

class AnimationAsset
{
public:
	static HAnimClass *GetAnim(const char *name);
};

#endif // CANONICAL_ANIMATIONASSET_H
