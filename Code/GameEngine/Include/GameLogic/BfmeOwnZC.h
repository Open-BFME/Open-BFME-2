// BfmeOwnZC: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEOWNZC_H
#define CANONICAL_BFMEOWNZC_H

class BfmeRoomZC;

class BfmeOwnZC
{
public:
	void *bfmeCallZC(const BfmeRoomZC &name, void *extra);
	void *bfmeRunZC(BfmeRoomZC name, void *extra);
};

#endif // CANONICAL_BFMEOWNZC_H
