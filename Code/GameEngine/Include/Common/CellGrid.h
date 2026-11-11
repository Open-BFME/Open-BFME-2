// CellGrid: canonical declarations for the members 14 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_CELLGRID_H
#define CANONICAL_CELLGRID_H

class Xfer;

class CellGrid
{
public:
	void rva0056C065();
	bool rva0056C50E(Xfer *);
};

#endif // CANONICAL_CELLGRID_H
