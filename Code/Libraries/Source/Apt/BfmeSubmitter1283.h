// BfmeSubmitter1283: canonical declarations for the members 8 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMESUBMITTER1283_H
#define CANONICAL_BFMESUBMITTER1283_H

class AptCIH;

class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(AptCIH *a1, int a2, int a3, int a4, int a5, int a6, int a7, float *colors, int a9, int a10, int a11, int zero);
	void bfmeSubmitColors1283(int character, int depth, int pCharacter, int name, int parent, int replace, int clipDepth, const unsigned int *colors, int matrix, int actions, int ratio);
};

#endif // CANONICAL_BFMESUBMITTER1283_H
