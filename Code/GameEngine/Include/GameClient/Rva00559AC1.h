// Rva00559AC1: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00559AC1_H
#define CANONICAL_RVA00559AC1_H

class Image;

class Rva00559AC1
{
public:
	float PercentDoneUntilNextRank(int);
	int rva00559AC1(int);
	int rva00559ADC(int);
	const Image *rva00559C25(int side, int rank);
};

#endif // CANONICAL_RVA00559AC1_H
