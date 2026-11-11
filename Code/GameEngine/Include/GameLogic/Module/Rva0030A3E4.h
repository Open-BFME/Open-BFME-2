// Rva0030A3E4: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA0030A3E4_H
#define CANONICAL_RVA0030A3E4_H

class Matrix3D;

class Rva0030A3E4
{
public:
	void _setTransformMatrix(const Matrix3D *mtx);
};

#endif // CANONICAL_RVA0030A3E4_H
