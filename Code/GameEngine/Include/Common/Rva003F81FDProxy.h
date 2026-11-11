// Rva003F81FDProxy: canonical declarations for the members 7 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA003F81FDPROXY_H
#define CANONICAL_RVA003F81FDPROXY_H

class Matrix3D;
class Rva003F7D86Inner;

class Rva003F81FDProxy
{
public:
	Rva003F7D86Inner *rva003F81B0();
	void rva003F830F(void *p);
	void rva003F8361(const Matrix3D *transform);
	void rva003F8374();
	void rva003F8385();
	unsigned char rva003F85C6();
	void rva003F9037();
};

#endif // CANONICAL_RVA003F81FDPROXY_H
