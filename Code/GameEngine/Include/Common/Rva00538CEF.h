// Rva00538CEF: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA00538CEF_H
#define CANONICAL_RVA00538CEF_H

class Rva0020E89C;
struct Rva00538CEFPair;

class Rva00538CEF
{
public:
	Rva0020E89C *rva00538CEF();
	bool rva00538D17(Rva00538CEFPair *out);
	void rva00538D3B(int value);
	void rva00538DC1(const Rva00538CEFPair *, int);
};

#endif // CANONICAL_RVA00538CEF_H
