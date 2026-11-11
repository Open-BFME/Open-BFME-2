// Rva004CE56D: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA004CE56D_H
#define CANONICAL_RVA004CE56D_H

class Xfer;

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

#endif // CANONICAL_RVA004CE56D_H
