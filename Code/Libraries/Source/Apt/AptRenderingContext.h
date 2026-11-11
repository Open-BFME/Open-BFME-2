// AptRenderingContext: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_APTRENDERINGCONTEXT_H
#define CANONICAL_APTRENDERINGCONTEXT_H

class AptRenderingContext
{
public:
	void popColourTransform();
	void popVertexMatrix();
	void pushColourTransform();
	void pushVertexMatrix();
};

#endif // CANONICAL_APTRENDERINGCONTEXT_H
